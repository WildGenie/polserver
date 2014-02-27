/*
History
=======
 2003/07/10 Dave: armordesc expects string zone names

Notes
=======

*/

#include "../../clib/stl_inc.h"

#ifdef _MSC_VER
#pragma warning( disable: 4786 )
#endif

#include "../../bscript/bstruct.h"
#include "../../bscript/impstr.h"
#include "../../bscript/objmembers.h"

#include "../../clib/cfgelem.h"
#include "../../clib/endian.h"
#include "../../clib/logfacility.h"
#include "../../plib/pkg.h"

#include "../tiles.h"
#include "../clidata.h"
#include "../layers.h"
#include "../ufunc.h"

#include "armor.h"
#include "itemdesc.h"
#include <climits>

namespace Pol {
  namespace Mobile {
    const char* zone_to_zone_name( unsigned short zone );
    unsigned short layer_to_zone( unsigned short layer );
    unsigned short zone_name_to_zone( const char *zname );
  }
  namespace Items {

	
	

	ArmorDesc::ArmorDesc( u32 objtype, Clib::ConfigElem& elem, const Plib::Package* pkg ) :
	  EquipDesc( objtype, elem, ARMORDESC, pkg ),
	  ar( elem.remove_ushort( "AR", 0 ) ),
	  zones(),
	  on_hit_script( elem.remove_string( "ONHITSCRIPT", "" ), pkg, "scripts/items/" )
	{
	  string coverage;
	  while ( elem.remove_prop( "COVERAGE", &coverage ) )
	  {
		try
		{
		  zones.insert( Mobile::zone_name_to_zone( coverage.c_str() ) );
		}
		catch ( runtime_error& )
		{
			fmt::Writer tmp;
			tmp.Format( "Error in Objtype 0x{:X}" ) << objtype;
			if ( pkg == NULL )
				tmp << "config/itemdesc.cfg\n";
			else
				tmp << pkg->dir( ) << "itemdesc.cfg\n";

			ERROR_PRINT << tmp.c_str();
			throw;
		}
	  }

	  if ( zones.empty() )
	  {
		// No 'COVERAGE' entries existed.
		// default coverage based on object type/layer
		unsigned short layer = Core::tile[graphic].layer;
		// special case for shields - they effectively have no coverage.
		if ( layer != Core::LAYER_HAND1 && layer != Core::LAYER_HAND2 )
		{
		  try
		  {
			zones.insert( Mobile::layer_to_zone( layer ) );
		  }
		  catch ( runtime_error& )
		  {
			fmt::Writer tmp;
			tmp.Format( "Error in Objtype 0x{:X}" ) << objtype;
			if ( pkg == NULL )
				tmp << "config/itemdesc.cfg\n";
			else
				tmp << pkg->dir( ) << "itemdesc.cfg\n";

			ERROR_PRINT << tmp.c_str();
			throw;
		  }
		}
	  }
	}

	void ArmorDesc::PopulateStruct( Bscript::BStruct* descriptor ) const
	{
	  base::PopulateStruct( descriptor );
	  descriptor->addMember( "OnHitScript", new Bscript::String( on_hit_script.relativename( pkg ) ) );
	  descriptor->addMember( "AR", new Bscript::BLong( ar ) );

	  std::unique_ptr<Bscript::ObjArray> arr_zones( new Bscript::ObjArray( ) );
	  std::set<unsigned short>::const_iterator itr;
	  for ( itr = zones.begin(); itr != zones.end(); ++itr )
		arr_zones->addElement( new Bscript::String( Mobile::zone_to_zone_name( *itr ) ) );


	  if ( arr_zones->ref_arr.size() > 0 )
		descriptor->addMember( "Coverage", arr_zones.release() );
	}

	UArmor::UArmor( const ArmorDesc& descriptor, const ArmorDesc* permanent_descriptor ) :
	  Equipment( descriptor, CLASS_ARMOR ),
	  tmpl( permanent_descriptor ),
	  onhitscript_( descriptor.on_hit_script )
	{}

	unsigned short UArmor::ar() const
	{
	  short ar_mod = getmember<s16>( Bscript::MBR_AR_MOD );
	  int ar = tmpl->ar * hp_ / maxhp();
	  if ( ar_mod != 0 )
	  {
		ar += ar_mod;
	  }

	  if ( ar < 0 )
		return 0;
	  else if ( ar <= USHRT_MAX )
		return static_cast<unsigned short>( ar );
	  else
		return USHRT_MAX;
	}

	bool UArmor::covers( unsigned short layer ) const
	{
	  return tmpl->zones.find( layer ) != tmpl->zones.end();
	}

	Item* UArmor::clone() const
	{
	  UArmor* armor = static_cast<UArmor*>( base::clone() );
	  armor->setmember<s16>( Bscript::MBR_AR_MOD, this->getmember<s16>( Bscript::MBR_AR_MOD ) );
	  armor->onhitscript_ = onhitscript_;
	  armor->tmpl = tmpl;
	  return armor;
	}

	void UArmor::printProperties( Clib::StreamWriter& sw ) const
	{
	  base::printProperties( sw );
	  short ar_mod_ = getmember<s16>( Bscript::MBR_AR_MOD );
	  if ( ar_mod_ )
		sw() << "\tAR_mod\t" << ar_mod_ << pf_endl;
	  if ( !( onhitscript_ == tmpl->on_hit_script ) )
		sw() << "\tOnHitScript\t" << onhitscript_.relativename( tmpl->pkg ) << pf_endl;
	}

	void UArmor::readProperties( Clib::ConfigElem& elem )
	{
	  base::readProperties( elem );
	  setmember<s16>( Bscript::MBR_AR_MOD, static_cast<short>( elem.remove_int( "AR_MOD", 0 ) ) );
	  set_onhitscript( elem.remove_string( "ONHITSCRIPT", "" ) );
	}

	void UArmor::set_onhitscript( const string& scriptname )
	{
	  if ( scriptname.empty() )
	  {
		onhitscript_.clear();
	  }
	  else
	  {
		onhitscript_.config( scriptname,
							 itemdesc().pkg,
							 "scripts/items/",
							 true );
	  }
	}
  }
}