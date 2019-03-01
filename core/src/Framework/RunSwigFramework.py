﻿#!/usr/local/bin/python
# -*- coding: utf-8 -*-
# ==============================================================================
#  FILE:
#	RunSwigFramework.py
#
#  SYNOPSIS:
#	python RunSwigFramework.py
#
#  DESCRIPTION:
#	以下のファイルを生成するために ShiftJIS の世界で swig を実行する.
#	生成するファイル：
#	    include/SprFWOldSpringheadDecl.hpp
#	    src/FWOldSpringheadDecl.hpp
#	    src/FWOldSpringheadStub.cpp
#	作業ディレクトリ：
#	    Springhead2 の直下に swigtemp というディレクトリを作り使用する.
#
# ==============================================================================
#  Version:
#	Ver 1.0	 2017/05/10 F.Kanehori	Windows batch file から移植.
#	Ver 1.1	 2017/07/06 F.Kanehori	作業ファイルの後始末を追加.
#	Ver 1.1	 2017/07/31 F.Kanehori	Python executable directory moved.
#	Ver 1.2  2017/09/06 F.Kanehori	New python library に対応.
#	Ver 1.3  2017/10/11 F.Kanehori	起動するpythonを引数化.
#	Ver 1.4  2017/11/08 F.Kanehori	Python library path の変更.
#	Ver 1.5  2017/11/15 F.Kanehori	Windows 版の nkf は buildtool を使用.
#	Ver 1.6  2017/11/29 F.Kanehori	pythonlib: buildtool -> src/RunSwig.
#	Ver 1.7  2018/07/03 F.Kanehori	空白を含むユーザ名に対応.
#	Ver 1.8  2019/02/26 F.Kanehori	Cmake環境に対応.
# ==============================================================================
version = 1.7
debug = False
trace = False

import sys
import os
import glob
from optparse import OptionParser

# ----------------------------------------------------------------------
#  Constants
#
prog = sys.argv[0].split(os.sep)[-1].split('.')[0]
if trace:
	print('ENTER: %s: %s' % (prog, sys.argv[1:]))
	sys.stdout.flush()
verbose = 1 if debug else 0
dry_run = 1 if debug else 0

# ----------------------------------------------------------------------
#  Import Springhead2 python library.
#
sys.path.append('../RunSwig')
from FindSprPath import *
spr_path = FindSprPath(prog)
libdir = spr_path.abspath('pythonlib')
sys.path.append(libdir)
from TextFio import *
from FileOp import *
from Error import *
from Util import *
from Proc import *

# ----------------------------------------------------------------------
#  Globals (part 1)
#
util = Util()
unix = util.is_unix()

# ----------------------------------------------------------------------
#  Directories
#
sprtop = spr_path.abspath()
##bindir = spr_path.relpath('bin')
##incdir = spr_path.relpath('inc')
##srcdir = spr_path.relpath('src')
bindir = spr_path.abspath('bin')
incdir = spr_path.abspath('inc')
srcdir = spr_path.abspath('src')
foundation_dir = '%s/%s' % (srcdir, 'Foundation')
framework_dir = '%s/%s' % (srcdir, 'Framework')

# ----------------------------------------------------------------------
#  Files and etc.
#
module = 'FWOldSpringhead'
interfacefile = '%s.i' % module		# in src/Foundation
makefile = '%sStub.mak.txt' % module	# in src/Foundation
stubcpp = '%sStub.cpp' % module		# in src/Framework

# ----------------------------------------------------------------------
#  Local method
# ---------------------------------------------------------------------
def output(fname, lines):
	fobj = TextFio(fname, 'w', encoding='utf8')
	if fobj.open() < 0:
		Error(prog).error(fobj.error())
	if fobj.writelines(lines, '\n') < 0:
		Error(prog).error(fobj.error())
	fobj.close()


# ----------------------------------------------------------------------
#  Main process
# ----------------------------------------------------------------------
#  オプションの定義
#
usage = 'Usage: %prog [options]'
parser = OptionParser(usage = usage)
parser.add_option('-c', '--clean',
			dest='clean', action='store_true', default=False,
			help='execute target clean')
parser.add_option('-d', '--dry_run',
			dest='dry_run', action='store_true', default=False,
			help='dry_run (for debug)')
parser.add_option('-P', '--python',
                        dest='python', action='store', default='python',
                        help='python command name')
parser.add_option('-v', '--verbose',
			dest='verbose', action='count', default=0,
			help='set verbose count')
parser.add_option('-V', '--version',
			dest='version', action='store_true', default=False,
			help='show version')

# ----------------------------------------------------------------------
#  コマンドラインの解析
#
(options, args) = parser.parse_args()
if options.version:
	print('%s: Version %s' % (prog, version))
	sys.exit(0)
if len(args) != 0:
	parser.error("incorrect number of arguments")

clean	= options.clean
verbose	= options.verbose
dry_run	= options.dry_run

# ----------------------------------------------------------------------
#  Scripts
#
if options.python:
	python = options.python
nkf = 'nkf'
swig = 'swig'
make = 'make' if unix else 'nmake'
runswig_foundation = '%s %s/RunSwig.py -P %s' % (python, foundation_dir, python)
addpath = spr_path.abspath('buildtool')

# ----------------------------------------------------------------------
#  Globals (part 2)
#
proc = Proc(verbose=verbose, dry_run=dry_run)
f_op = FileOp(verbose=verbose)

# ----------------------------------------------------------------------
#  src/Foundation へ移って RunSwig を実行する.
#
cmd = '%s Framework Foundation' % runswig_foundation
proc.execute(cmd, shell=True)
status = proc.wait()
if status != 0:
	msg = '%s failed (%d)' % (runswig_foundation, status)
	Error(prog).error(msg)

# ----------------------------------------------------------------------
#  swigtemp 下に SJIS world を作る.
#
swigtmp = Util.upath(os.path.relpath('%s/core/swigtemp' % sprtop))
tmp_inc = '%s/include' % swigtmp
tmp_src = '%s/src' % swigtmp

#  Create directory if not exists.
incdir_names = ['Base', 'Framework']
srcdir_names = ['Foundation', 'Framework']
tmp_incdirs = list(map(lambda x: '%s/%s' % (tmp_inc, x), incdir_names))
tmp_srcdirs = list(map(lambda x: '%s/%s' % (tmp_src, x), srcdir_names))
v_save = verbose
verbose = 1
for dir in tmp_incdirs:
	#print('[%s]' % dir)
	if not os.path.exists(dir):
		if verbose: print('creating %s' % dir)
		os.makedirs(dir)
for dir in tmp_srcdirs:
	#print('[%s]' % dir)
	if not os.path.exists(dir):
		if verbose: print('creating %s' % dir)
		os.makedirs(dir)
verbose = v_save

#  Convert kanji code into SJIS.
incf_names = ['Springhead.h', 'Base/Env.h', 'Base/BaseDebug.h']
srcf_names = ['Foundation/UTTypeDesc.h', 'Framework/FWOldSpringheadNodeHandler.h']
for file in incf_names:
	cmnd = '%s -s -O %s/%s %s/include/%s' % (nkf, incdir, file, swigtmp, file)
	cmnd = util.pathconv(cmnd)
	proc.execute(cmnd, addpath=addpath, shell=True)
	status = proc.wait()
	if status != 0:
		Error(prog).error('"%s" failed (%d)' % (util.pathconv(cmnd, 'unix'), status))
for file in srcf_names:
	cmnd = '%s -s -O %s/%s %s/src/%s' % (nkf, srcdir, file, swigtmp, file)
	cmnd = util.pathconv(cmnd)
	proc.execute(cmnd, addpath=addpath, shell=True)
	status = proc.wait()
	if status != 0:
		Error(prog).error('"%s" failed (%d)' % (util.pathconv(cmnd, 'unix'), status))

# ----------------------------------------------------------------------
#  ここからは swigtemp/src/Foundation に移って作業する.
#
oldcwd = os.getcwd()
os.chdir('%s/Foundation' % tmp_src)
if verbose:
	print('  chdir to %s' % util.pathconv(os.getcwd(), 'unix'))

# ----------------------------------------------------------------------
#  swig のインターフェイスファイルを作成する.
#
srcimp = '%s/src/Framework/FWOldSpringheadNodeHandler.h' % swigtmp
srcimpdep = '%s/Framework/FWOldSpringheadNodeHandler.h' % srcdir

print('src files: %s' % srcimp)
lines = []
lines.append('# Do not edit. %s will update this file.' % prog)
lines.append('%%module %s' % module)
for file in incf_names:
	lines.append('%%include "%s/%s"' % (incdir, file))
for file in srcf_names:
	lines.append('%%include "%s/%s"' % (srcdir, file))
if verbose:
	path = '%s/%s' % (os.getcwd(), interfacefile)
	print('  creating "%s"' % util.pathconv(path, 'unix'))
output(interfacefile, lines)

# ----------------------------------------------------------------------
#  makefile を作成する.
#
srcimpdep_rel = os.path.relpath(srcimpdep)
swigdir_rel = Util.upath(os.path.relpath('%s/core/bin/swig' % sprtop))
#
swigargs = '-I%s/Lib' % swigdir_rel
swigargs += ' -spr -w312,325,401,402 -DSWIG_OLDNODEHANDLER -c++'
cp = 'cp' if unix else 'copy'
rm = 'rm' if unix else 'del'
quiet = '>/dev/null 2>&1' if unix else '>NUL 2>&1'
#
lines = []
lines.append('# Do not edit. %s will update this file.' % prog)
lines.append('all:\t../../../src/Framework/%sStub.cpp' % module)
lines.append('../../../src/Framework/%sStub.cpp:\t%s' % (module, srcimpdep_rel))
lines.append('\t%s/%s %s %s' % (swigdir_rel, swig, swigargs, interfacefile))
lines.append('\t%s Spr%sDecl.hpp ../../../include/%s %s' % (cp, module, module, quiet))
lines.append('\t%s %sStub.cpp ../../../src/Framework %s' % (cp, module, quiet))
lines.append('\t%s %sDecl.hpp ../../../src/Framework %s' % (cp, module, quiet))
lines.append('')
lines.append('clean:\t')
lines.append('\t-%s -f ../../../src/Framework/%sStub.cpp %s' % (rm, module, quiet))
lines.append('\t-%s -f ../../../include/%s %s' % (rm, module, quiet))
lines.append('\t-%s -f ../../../src/Framework/%sStub.cpp %s' % (rm, module, quiet))
lines.append('\t-%s -f ../../../src/Framework/%sDecl.hpp %s' % (rm, module, quiet))
if verbose:
	path = '%s/%s' % (os.getcwd(), makefile)
	print('  creating "%s"' % util.pathconv(path, 'unix'))
lines = util.pathconv(lines)
output(makefile, lines)

# ----------------------------------------------------------------------
#  make を実行する.
#
cmd = '%s -f %s' % (make, makefile)
if clean:
	cmd += ' clean'
if trace:
	print('exec: %s' % cmd)
proc.execute(cmd, shell=True)
status = proc.wait()
if status != 0:
	Error(prog).error('%s failed (%d)' % (make, status))

# ----------------------------------------------------------------------
#  ファイルの後始末
#
os.chdir(oldcwd)
f_op.rm('Framework.i')
f_op.rm('FrameworkStub.cpp')
f_op.rm('FrameworkStub.mak.txt')

# ----------------------------------------------------------------------
#  処理終了.
#
if trace:
	print('LEAVE: %s' % prog)
	sys.stdout.flush()
sys.exit(0)

# end: RunSwigFramework.py
