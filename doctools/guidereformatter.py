#!/usr/bin/env python3

'''
	***INCOMPLETE DRAFT***

	Reformats the e-script guide.
	This is probably a one-shot script that can be deleted
'''

import os
import html.parser


class Parser(html.parser.HTMLParser):
	def __init__(self):
		super().__init__()

		self.status = 'root'

	def handle_starttag(self, tag, attrs):
		attrs = dict(attrs)

		if tag == 'h3' and self.status == 'root':
			self.status = 'newChapterA'
			return
		elif tag == 'a' and self.status == 'newChapterA':
			self.chapAnchor = attrs['name']
			self.status = 'newChapterData'
			self.chapName = ''
			return

		raise RuntimeError(f'Unexpected tag {tag} in status "{self.status}"')

	def handle_endtag(self, tag):

		if tag == 'a' and self.status == 'newChapterData':
			self.newChapter()
			self.status = 'newChapterClose'
			return
		if tag == 'h3' and self.status == 'newChapterClose':
			self.status = 'chapter'
			return

		raise RuntimeError(f'Unexpected end tag {tag} in status "{self.status}"')

	#	print("Encountered an end tag :", tag)
	def handle_data(self, data):
		data = data.strip()
		if not len(data):
			return

		if self.status == 'newChapterData':
			self.chapName += data.strip()
			return

		raise RuntimeError(f'Unexpected data "{data}" in status "{self.status}"')

	def handle_startendtag(self, tag, attrs):
		if tag == 'br' and self.status == 'chapter':
			return

		raise RuntimeError(f'Unexpected full tag {tag} in status "{self.status}"')

	def handle_entityref(self, name):
		raise NotImplementedError()

	def handle_charref(self, name):
		raise NotImplementedError()

	def handle_comment(self, data):
		raise NotImplementedError()

	def handle_decl(self, decl):
		raise NotImplementedError()

	def handle_pi(self, data):
		raise NotImplementedError()

	def unknown_decl(self, data):
		raise NotImplementedError()

	def newChapter(self):
		print(f'<h3><a name="{self.chapAnchor}">{self.chapName}</a></h3>')
		del self.chapAnchor
		del self.chapName



class Main:

	def run(self):
		parser = Parser()
		with open(os.path.join('..','docs','docs.polserver.com','pol100','include','escriptguide.inc')) as f:
			while True:
				if l := f.readline():
					parser.feed(l)
				else:
					break


if __name__ == '__main__':
	Main().run()
