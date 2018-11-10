#!/usr/local/bin/python
# -*- coding: utf-8 -*-
# ======================================================================
#  SYNOPSIS:
#	insert_kludge file
#	    file:	Input file name.
#
#  DESCRIPTION:
#	Insert 'kludge' before every location where character code
#	changes from 'ascii' to another multi-byte one.
#
#  VERSION:
#	Ver 1.0  2018/10/30 F.Kanehori	First release version.
# ======================================================================
version = '1.0'

import sys
import os
import re
from optparse import OptionParser

# ----------------------------------------------------------------------
#  Constants
#
prog = sys.argv[0].split(os.sep)[-1].split('.')[0]
#
target_defs = {
	'file': 'chapters.tex',
	'patt': r'\\input\{([a-zA-Z0-9_]+)\}'
}
kludge_code = b'\\KLUDGE '
verbatim_in = r'\\begin\{sourcecode\}'
verbatim_out = r'\\end\{sourcecode\}'

# ----------------------------------------------------------------------
#  Options
#
usage = 'Usage: %prog [options]'
parser = OptionParser(usage = usage)
parser.add_option('-v', '--verbose',
			dest='verbose', action='count', default=0,
			help='set verbose mode')
parser.add_option('-V', '--version',
			dest='version', action='store_true', default=False,
			help='show version')

# ----------------------------------------------------------------------
#  Process for command line
#
(options, args) = parser.parse_args()
if options.version:
	print('%s: Version %s' % (prog, version))
	sys.exit(0)
if len(args) != 0:
	parser.error("incorrect number of arguments")

# get options and input file name
verbose = options.verbose

# ----------------------------------------------------------------------
#  メソッドの定義
# ----------------------------------------------------------------------
#  処理の対象となるファイルを"chapters.tex"から読む
#
def read_targets():
	if verbose:
		print('file: %s' % target_defs['file'])
		print('patt: %s' % target_defs['patt'])
	fnames = []
	for line in open(target_defs['file'], 'r', encoding='utf-8'):
		m = re.match(target_defs['patt'], line)
		if m:
			fname = m.group(1)
			if fname[-4:] != '.tex':
				fname += '.tex'
			fnames.append(fname)
	if verbose:
		print('targets: %s' % fnames)
	return fnames

#  指定されたファイルを処理する
#
def process_onefile(ifname, ofname):
	outf = open(ofname, 'w', encoding='utf-8')
	verbatim = False
	for line in open(ifname, 'r', encoding='utf-8'):
		# verbatim環境の中は処理の対象外とする
		if re.match(verbatim_in, line):
			verbatim = True
		if re.match(verbatim_out, line):
			verbatim = False
		outf.write(process_oneline(line, verbatim))
	outf.close()

#  指定された文字列(1行分)にkludgeコードを挿入する
#
def process_oneline(string, verbatim):
	if verbatim:
		return string

	# bytes型に変換して処理を行なう
	byte = string.encode('utf-8')
	size = len(list(byte))	# byte数
	if verbose:
		print('utf8: %s' % byte)

	# 各文字を表すutf8のバイト数を求める
	mark = []
	ix = 0
	while ix < size:
		leng = codelen(byte[ix])
		mark.append(leng)
		ix += 1
		for n in range(leng-1):
			mark.append(leng)
			ix += 1
	if verbose:
		print('mark: %s' % mark)

	# マルチバイトに変わる場所にKLUDGEを入れる
	bout = bytearray()
	prev = 0
	ix = 0
	while ix < size:
		curr = mark[ix]
		if curr != prev and curr > 1:
			bout.extend(kludge_code)
			if verbose:
				print('  kludge inserted at %d' % ix)
		bout.append(byte[ix])
		prev = curr
		ix += 1

	return bout.decode('utf-8')

#  先頭コードを見てこの文字が何バイトで構成されているかを判断する(utf8)
#
def codelen(code):
	nb = 1
	if   code >= 240: nb = 4
	elif code >= 224: nb = 3
	elif code >= 192: nb = 2
	return nb

# ----------------------------------------------------------------------
#  Main process.
#
fnames = read_targets()
if verbose:
	print('inserting...')
for fn in fnames:
	ifn = fn + '.org'
	ofn = fn
	if not os.path.exists(ifn):
		os.rename(ofn, ifn)	# fn -> fn.org
	if verbose:
		print('  %s' % fn)
	process_onefile(ifn, ofn)

# ----------------------------------------------------------------------
#  End of process.
#
if verbose:
	print('%s: done' % prog)
sys.exit(0)

# end: insert_kludge.py
