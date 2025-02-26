/** @file
 *
 * @par History
 * - 2005/01/24 Shinigami: added ObjMember character.spyonclient2 to get data from packet 0xd9 (Spy
 * on Client 2)
 * - 2005/03/09 Shinigami: added Prop Character::Delay_Mod [ms] for WeaponDelay
 * - 2005/04/04 Shinigami: added Prop Character::CreatedAt [PolClock]
 * - 2005/08/29 Shinigami: character.spyonclient2 renamed to character.clientinfo
 * - 2005/10/02 Shinigami: added Prop Script.attached_to and Script.controller
 * - 2005/12/09 MuadDib:   added member uclang for storing Unicode Language sent during logon.
 * - 2006/05/16 Shinigami: added Prop Character.Race [RACE_* Constants] to support Elfs
 * - 2007/07/09 Shinigami: added Prop Character.isUOKR [bool] - UO:KR client used?
 * - 2008/07/08 Turley:    Added character.movemode - returns the MoveMode like given in NPCDesc
 * - Added item.stackable - Is item stackable?
 * - 2008/12/17 MuadDub:   Added item.tile_layer - returns layer entry from tiledata/tiles.cfg
 * - 2009/08/06 MuadDib:   Removed PasswordOnlyHash support
 * - 2009/08/19 Turley:    Added character.uo_expansion_client
 * - 2009/09/06 Turley:    Removed chr.isUOKR added chr.ClientType
 * - 2009/10/14 Turley:    Added char.deaf() methods & char.deafened member
 * - 2011/12/13 Tomi:    Boat members MBR_COMPONENT, MBR_HULL, MBR_ROPE, MBR_SAILS, MBR_WHEEL,
 * MBR_TILLER, MBR_RUDDER, MBR_STORAGE, MBR_WEAPONSLOT
 * - 2012/02/02 Tomi:    Multi member MBR_MULTIID
 * - 2012/03/26 Tomi:    Added MBR_LASTCOORD
 * - 2012/04/14 Tomi:    Added MBR_FACETID for new map message packet
 * - 2012/04/15 Tomi:    Added MBR_EDITABLE for maps
 * - 2012/06/02 Tomi:    Added MBR_ACTIVE_SKILL and MBR_CASTING_SPELL for characters
 */


#ifndef OBJMEMBERS_H
#define OBJMEMBERS_H
namespace Pol
{
namespace Bscript
{
enum MemberID
{
  MBR_X,  // uobject //0
  MBR_Y,  // 1
  MBR_Z,
  MBR_NAME,
  MBR_OBJTYPE,
  MBR_GRAPHIC,  // 5
  MBR_SERIAL,
  MBR_COLOR,
  MBR_HEIGHT,
  MBR_FACING,
  MBR_DIRTY,  // 10
  MBR_WEIGHT,
  MBR_MULTI,
  MBR_AMOUNT,  // item
  MBR_LAYER,
  MBR_CONTAINER,  // 15
  MBR_USESCRIPT,
  MBR_EQUIPSCRIPT,
  MBR_UNEQUIPSCRIPT,
  MBR_DESC,
  MBR_MOVABLE,  // 20
  MBR_INVISIBLE,
  MBR_DECAYAT,
  MBR_SELLPRICE,
  MBR_BUYPRICE,
  MBR_NEWBIE,  // 25
  MBR_ITEM_COUNT,
  MBR_WARMODE,  // character
  MBR_GENDER,
  MBR_TRUEOBJTYPE,
  MBR_TRUECOLOR,  // 30
  MBR_AR_MOD,
  MBR_HIDDEN,
  MBR_CONCEALED,
  MBR_FROZEN,
  MBR_PARALYZED,  // 35
  MBR_POISONED,
  MBR_STEALTHSTEPS,
  MBR_SQUELCHED,
  MBR_DEAD,
  MBR_AR,  // 40
  MBR_BACKPACK,
  MBR_WEAPON,
  MBR_SHIELD,
  MBR_ACCTNAME,
  MBR_ACCT,  // 45
  MBR_CMDLEVEL,
  MBR_CMDLEVELSTR,
  MBR_CRIMINAL,
  MBR_IP,
  MBR_GOLD,  // 50
  MBR_TITLE_PREFIX,
  MBR_TITLE_SUFFIX,
  MBR_TITLE_GUILD,
  MBR_TITLE_RACE,
  MBR_GUILDID,  // 55
  MBR_GUILD,
  MBR_MURDERER,
  MBR_ATTACHED,
  MBR_CLIENTVERSION,
  MBR_REPORTABLES,  // 60
  MBR_SCRIPT,       // npc
  MBR_NPCTEMPLATE,
  MBR_MASTER,
  MBR_PROCESS,
  MBR_EVENTMASK,  // 65
  MBR_SPEECH_COLOR,
  MBR_SPEECH_FONT,
  MBR_USE_ADJUSTMENTS,
  MBR_RUN_SPEED,
  MBR_LOCKED,      // lockable //70
  MBR_CORPSETYPE,  // corpse
  MBR_TILLERMAN,   // boat
  MBR_PORTPLANK,
  MBR_STARBOARDPLANK,
  MBR_HOLD,  // 75
  MBR_HAS_OFFLINE_MOBILES,
  MBR_COMPONENTS,  // house
  MBR_ITEMS,       // multi
  MBR_MOBILES,
  MBR_XEAST,  // map //80
  MBR_XWEST,
  MBR_YNORTH,
  MBR_YSOUTH,
  MBR_GUMPWIDTH,
  MBR_GUMPHEIGHT,  // 85
  MBR_ISOPEN,      // door
  MBR_QUALITY,     // equipment
  MBR_HP,
  MBR_MAXHP_MOD,
  MBR_MAXHP,    // 90
  MBR_DMG_MOD,  // weapon
  MBR_ATTRIBUTE,
  MBR_INTRINSIC,
  MBR_HITSCRIPT,
  MBR_AR_BASE,  // 95
  MBR_ONHIT_SCRIPT,
  MBR_ENABLED,  // account
  MBR_BANNED,
  MBR_USERNAMEPASSWORDHASH,
  MBR_MEMBERS,  // guild/party //100
  MBR_ALLYGUILDS,
  MBR_ENEMYGUILDS,
  MBR_PID,  // script
  MBR_STATE,
  MBR_INSTR_CYCLES,  // 105
  MBR_SLEEP_CYCLES,
  MBR_CONSEC_CYCLES,
  MBR_PC,
  MBR_CALL_DEPTH,
  MBR_NUM_GLOBALS,  // 110
  MBR_VAR_SIZE,
  MBR_REALM,
  MBR_UO_EXPANSION,
  MBR_CUSTOM,
  MBR_GLOBALS,  // 115
  MBR_FOOTPRINT,
  MBR_CLIENTINFO,
  MBR_DELAY_MOD,
  MBR_CREATEDAT,
  MBR_OPPONENT,  // 120
  MBR_CONNECTED,
  MBR_ATTACHED_TO,
  MBR_CONTROLLER,
  MBR_OWNERSERIAL,
  MBR_DEFAULTCMDLEVEL,  // 125
  MBR_UCLANG,
  MBR_RACE,
  MBR_TRADING_WITH,
  MBR_TRADE_CONTAINER,
  MBR_ALIGNMENT,  // 130
  MBR_CURSOR,
  MBR_GUMP,
  MBR_PROMPT,
  MBR_STACKABLE,
  MBR_MOVEMODE,  // 135
  MBR_HITCHANCE_MOD,
  MBR_EVASIONCHANCE_MOD,
  MBR_TILE_LAYER,
  MBR_CLIENTVERSIONDETAIL,
  MBR_SAVEONEXIT,  // 140
  MBR_FIRE_RESIST,
  MBR_COLD_RESIST,
  MBR_ENERGY_RESIST,
  MBR_POISON_RESIST,
  MBR_PHYSICAL_RESIST,  // 145
  MBR_FIRE_RESIST_MOD,
  MBR_COLD_RESIST_MOD,
  MBR_ENERGY_RESIST_MOD,
  MBR_POISON_RESIST_MOD,
  MBR_PHYSICAL_RESIST_MOD,  // 150
  MBR_STATCAP,
  MBR_SKILLCAP,
  MBR_LUCK,
  MBR_FOLLOWERSMAX,
  MBR_TITHING,  // 155
  MBR_FOLLOWERS,
  MBR_FIRE_DAMAGE,
  MBR_COLD_DAMAGE,
  MBR_ENERGY_DAMAGE,
  MBR_POISON_DAMAGE,  // 160
  MBR_PHYSICAL_DAMAGE,
  MBR_FIRE_DAMAGE_MOD,
  MBR_COLD_DAMAGE_MOD,
  MBR_ENERGY_DAMAGE_MOD,
  MBR_POISON_DAMAGE_MOD,  // 165
  MBR_PHYSICAL_DAMAGE_MOD,
  MBR_PARTY,
  MBR_LEADER,
  MBR_PARTYLOOT,
  MBR_CANDIDATE_OF_PARTY,  // 170
  MBR_CANDIDATES,
  MBR_MOVECOST_WALK,
  MBR_MOVECOST_RUN,
  MBR_MOVECOST_WALK_MOUNTED,
  MBR_MOVECOST_RUN_MOUNTED,  // 175
  MBR_AGGRESSORTO,
  MBR_LAWFULLYDAMAGED,
  MBR_GETGOTTENBY,
  MBR_UO_EXPANSION_CLIENT,
  MBR_CLIENTTYPE,  // 180
  MBR_DEAFENED,
  MBR_CLIENT,
  MBR_TYPE,
  MBR_ATTRIBUTES,
  MBR_EDITING,  // 185
  MBR_HOUSEPARTS,
  MBR_DOUBLECLICKRANGE,
  MBR_MOUNTEDSTEPS,
  // New boat stuff start
  MBR_ROPE,
  MBR_WHEEL,  // 190
  MBR_HULL,
  MBR_TILLER,
  MBR_RUDDER,
  MBR_SAILS,
  MBR_STORAGE,  // 195
  MBR_WEAPONSLOT,
  // New boat stuff end
  MBR_MULTIID,
  MBR_TRADEWINDOW,
  MBR_LASTCOORD,
  MBR_FACETID,  // 200
  MBR_EDITABLE,
  MBR_ACTIVE_SKILL,
  MBR_CASTING_SPELL,
  MBR_CARRYINGCAPACITY_MOD,
  MBR_MAX_ITEMS_MOD,  // 205
  MBR_MAX_WEIGHT_MOD,
  MBR_MAX_SLOTS_MOD,
  MBR_SPEED_MOD,
  MBR_NAME_SUFFIX,
  MBR_TEMPORALLY_CRIMINAL,  // 210
  MBR_LAST_TEXTCOLOR,
  MBR_INSURED,
  MBR_LAST_ACTIVITY_AT,
  MBR_LAST_PACKET_AT,
  MBR_HOUSE,  // 215
  MBR_SPECIFIC_NAME,
  MBR_CARRYINGCAPACITY,
  MBR_NO_DROP,
  MBR_NO_DROP_EXCEPTION,
  MBR_PORT,  // 220
  MBR_LOWER_REAG_COST,
  MBR_SPELL_DAMAGE_INCREASE,
  MBR_FASTER_CASTING,
  MBR_FASTER_CAST_RECOVERY,
  MBR_DEFENCE_CHANCE_INCREASE,  // 225
  MBR_DEFENCE_CHANCE_INCREASE_CAP,
  MBR_LOWER_MANA_COST,
  MBR_FIRE_RESIST_CAP,
  MBR_COLD_RESIST_CAP,
  MBR_ENERGY_RESIST_CAP,  // 230
  MBR_POISON_RESIST_CAP,
  MBR_PHYSICAL_RESIST_CAP,
  MBR_HIT_CHANCE,
  MBR_LOWER_REAG_COST_MOD,
  MBR_SPELL_DAMAGE_INCREASE_MOD,  //  235
  MBR_FASTER_CASTING_MOD,
  MBR_FASTER_CAST_RECOVERY_MOD,
  MBR_DEFENCE_CHANCE_INCREASE_MOD,
  MBR_DEFENCE_CHANCE_INCREASE_CAP_MOD,
  MBR_LOWER_MANA_COST_MOD,  // 240
  MBR_FIRE_RESIST_CAP_MOD,
  MBR_COLD_RESIST_CAP_MOD,
  MBR_ENERGY_RESIST_CAP_MOD,
  MBR_POISON_RESIST_CAP_MOD,
  MBR_PHYSICAL_RESIST_CAP_MOD,  // 245
  MBR_LUCK_MOD,
  MBR_HIT_CHANCE_MOD,
  MBR_PACKAGE,
  MBR_SWING_SPEED_INCREASE,
  MBR_SWING_SPEED_INCREASE_MOD, // 250
  MBR_EXPORTED_FUNCTIONS,
  MBR_DISABLE_INACTIVITY_TIMEOUT,
  MBR_CURSED,
};


typedef struct
{
  MemberID id;
  char code[30];
  bool read_only;
} ObjMember;

extern ObjMember object_members[];
extern int n_objmembers;

ObjMember* getKnownObjMember( const char* token );
ObjMember* getObjMember( int id );
}  // namespace Bscript
}  // namespace Pol
#endif
