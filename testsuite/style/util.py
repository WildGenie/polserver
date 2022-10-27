
'''
Common utlities for testsuite

@author Bodom
'''

import os
import abc
import subprocess


class Skip():
	''' Empty constant util class '''
	pass


class SourceChecker(metaclass=abc.ABCMeta):
	''' A generic script running checks over the whole source tree '''

	# Folders to ignore, relative to root
	IGNORE = ('.git', 'bin-build', 'bin', 'lib', 'doc', 'testsuite')

	# Description of what is being checked
	WHAT = ''
	SKIP = Skip()

	def __init__(self, quiet=False):
		self.quiet = quiet

		mydir = os.path.dirname(os.path.realpath(__file__))
		self.polroot = os.path.realpath(os.path.join(mydir, '..', '..', 'pol-core'))

	def isIgnored(self, full):
		rel = os.path.relpath(full, self.polroot)
		return any(rel.startswith(ign) for ign in self.IGNORE)

	def walk(self, path):
		''' Like os.walk() but accounts for self.IGNORE '''

		for entry in os.listdir(path):
			full = os.path.join(path, entry)

			if self.isIgnored(full):
				continue

			if os.path.isdir(full):
				if self.isGitIgnored(full):
				    continue
				yield from self.walk(full)
			elif os.path.isfile(full):
				yield full
			else:
				raise NotImplementedError()

	def run(self):
		''' Runs checks over all real source files
		@return True on success, False on error
		'''
		print(f"Checking {self.WHAT}, POL root is {self.polroot}")

		analyzed = 0
		ignored = 0
		errors = 0
		for fpath in self.walk(self.polroot):
			if self.isGitIgnored(fpath):
				ignored += 1
				continue

			base, ext = os.path.splitext(fpath)
			res = self.checkFile(fpath, ext)

			if res is self.SKIP:
				continue

			analyzed += 1
			if not res:
				errors += 1

		print()
		print(f"Done. {analyzed} files analyzed, {errors} errors, {ignored} ignored.")
		return not errors

	@abc.abstractmethod
	def checkFile(self, path, ext):
		''' Checks file for validity
		@param path string: The full file path
		@param ext string: The file extension
		@return True on success, self.Skip to skip
		'''
		return False

	def isGitIgnored(self, path):
		''' Checks if file is ignored by git '''

		cmd = ('git', 'check-ignore', '-q', path)
		proc = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
		po, pe = proc.communicate()

		return proc.returncode == 0
