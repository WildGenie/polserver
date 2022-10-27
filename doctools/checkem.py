#!/usr/bin/env python3

'''
This script will roughly check doc consistency for .em files.
At the moment, problems founds are intended to be solved by hand.
'''

import os
import re
import xml.etree.ElementTree as ET


class EmFile:
	''' Rough .em file parser '''

	CONSTRE = re.compile(r'^const\s+([A-Z0-9_]+)\s*:=\s*(.*);?$')
	FUNCRE = re.compile(r'^([A-Za-z0-9_]+)\s*\(([^)]*)\)\s*;?$')

	def __init__(self, path, name):
		self.path = path
		self.name = name
		self.consts = {}
		self.funcs = {}

		with open(self.path, 'rt') as f:
			for line in f:
				# Clean the line and strip comments
				line = self.stripLine(line)

				if not line:
					continue

				# Check if this is a constant declaration
				name, val = self.__parseConst(line)
				if name:
					self.consts[name] = val
					continue

				# Check if this is a function declaration
				name, args = self.__parseFunc(line)
				if name:
					self.funcs[name] = args
					continue

				raise NotImplementedError(f"Couldn't parse line:\n{line}")

	@staticmethod
	def stripLine(line):
		line = line.strip()
		commentStart = line.find('//')
		if commentStart != -1:
			line = line[:commentStart].strip()
		return line

	def __parseConst(self, line):
		m = self.CONSTRE.match(line)
		return (m.group(1), m.group(2)) if m else (None, None)

	def __parseFunc(self, line):
		m = self.FUNCRE.match(line)
		return (
			(m.group(1), list(map(lambda i: i.strip(), m.group(2).split(','))))
			if m
			else (None, None)
		)

	def __str__(self):
		return f"EMFile<{self.path}, consts: {self.consts}, funcs: {self.funcs}"


class Main:

	def run(self):
		# 1. Load and parse the .em files
		emfiles = {}
		for root, subdirs, files in os.walk(os.path.join('..','pol-core','support','scripts')):
			for f in files:
				if f.endswith('.em'):
					path = os.path.join(root,f)
					name = os.path.splitext(f)[0]
					print(f'Loading {f}...', end='')
					emfiles[name] = EmFile(path, name)
					print('done.')

		# 2. Load and parse the mail modules.xml, start doing some checks
		docPath = os.path.join('..','docs','docs.polserver.com','pol100')
		xmlfiles = {}
		modules = ET.parse(os.path.join(docPath,'modules.xml'))
		modlist = []
		for m in modules.getroot().findall('em'):
			name = m.get('name')[:-2]
			if name not in emfiles.keys():
				print(f"ERROR: unknown module {name} defined in modules.xml")
			modlist.append(name)
		for name in emfiles:
			if name not in modlist:
				print(f"ERROR: module {name} is not defined in modules.xml")

		# 3. Load and parse every module's XML defintion, do rest of the checks
		for modfile in modlist:
			xmldoc = ET.parse(os.path.join(docPath, f'{modfile}em.xml'))

			consts = []
			for const in xmldoc.findall('./fileheader/constant'):
				txt = EmFile.stripLine(const.text.strip())
				if not txt:
					continue
				m = EmFile.CONSTRE.match(txt)
				if not m:
					raise NotImplementedError(f'Unable to parse constant "{txt}"')
				name = m.group(1)
				val = m.group(2)
				consts.append(name)

				if name not in emfiles[modfile].consts.keys():
					print(
						f"ERROR: constant {name} is documented in {modfile}em.xml but no longer existing in {modfile}.em"
					)

				elif val != emfiles[modfile].consts[name]:
					print(
						f'ERROR: constant {name} value differs. em: "{val}", xml: "{emfiles[modfile].consts[name]}"'
					)


			for const in emfiles[modfile].consts.keys():
				if const not in consts:
					print(
						f"ERROR: constant {const} is defined in {modfile}.em but not documented in {modfile}em.xml"
					)


			funcs = []
			for func in xmldoc.getroot().findall('function'):
				proto = EmFile.stripLine(func.find('prototype').text.replace('\n',' '))
				m = EmFile.FUNCRE.match(proto)
				if not m:
					raise NotImplementedError(f'Unable to parse function "{proto}"')
				name = m.group(1)
				args = list(map(lambda i: i.strip(), m.group(2).split(',')))
				funcs.append(name)

				infile = True
				if name not in emfiles[modfile].funcs.keys():
					infile = False
					print(
						f"ERROR: function {name} is documented in {modfile}em.xml but no longer existing in {modfile}.em"
					)

				elif sorted(map(lambda i: i.lower(),args)) != sorted(map(lambda i: i.lower(),emfiles[modfile].funcs[name])):
					print(
						f'ERROR: function {name} args differs. em: "{emfiles[modfile].funcs[name]}", xml: "{args}"'
					)


				if infile:
					parameters = list(map(lambda i: i.get('name').strip().split(' ')[0].split(':')[0].strip().lower(), func.findall('parameter')))
					empars = list(map(lambda i:                 i.strip().split(' ')[0].split(':')[0].strip().lower(), emfiles[modfile].funcs[name]))
					for p in parameters:
						if p and p not in empars:
							print(
								f"ERROR: parameter {p} for function {name} is documented in {modfile}em.xml but no longer existing in {modfile}.em"
							)

					for p in empars:
						if p and p not in parameters:
							print(
								f"ERROR: parameter {p} for function {name} is defined in {modfile}.em but not documented in {modfile}em.xml"
							)


			for func in emfiles[modfile].funcs.keys():
				if func not in funcs:
					print(
						f"ERROR: function {func} is defined in {modfile}.em but not documented in {modfile}em.xml"
					)


		# 4. Done!
		print()
		print("Done. If you didn't see any error above, then em files and their doc seems to be in sync. Good luck.")


if __name__ == '__main__':
	Main().run()
