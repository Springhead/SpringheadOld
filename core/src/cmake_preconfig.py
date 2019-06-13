#!/usr/local/bin/python
# -*- coding: utf-8 -*-
# ======================================================================
#  SYNOPSIS:
#	python cmake_ln.py [options] link=target ...
#	arguments:
#	    link	�쐬���郊���N�̃p�X
#	    target	�����N�̎��̂�u���f�B���N�g���̃p�X
#
#  DESCRIPTION:
#	�w�肳�ꂽ����(link)�̃����N���^�[�Q�b�g�f�B���N�g��(target)
#	��ɍ쐬����B
#	unix �ł� symbolic link ���AWindows �ł� junction ���g�p����B
#
# ----------------------------------------------------------------------
#  VERSION:
#	Ver 1.0  2019/05/23 F.Kanehori	First version.
# ======================================================================
version = 1.0

import sys
import os
import shutil
import glob
import subprocess
from optparse import OptionParser

# ----------------------------------------------------------------------
#  Constants
#
prog = sys.argv[0].split(os.sep)[-1].split('.')[0]
target_mark = '_target_body_'

# ----------------------------------------------------------------------
#  Helper methods
#

#  �t�@�C�������[�u����
#
def move_files(src, dst):
	src = upath(src)
	dst = upath(dst)
	cwd = os.getcwd()
	os.chdir(src)
	for f in glob.glob('*'):
		if os.path.isfile(f):
			if verbose > 1:
				print('  copying %s -> %s' % (f, dst))
			shutil.move(f, dst)
		elif os.path.isdir(f):
			os.makedirs('%s/%s' % (dst, f), exist_ok=True)
			move_files('%s/%s' % (src, f), '%s/%s' % (dst, f))
	os.chdir(cwd)
	if verbose > 1:
		print('  removing directory %s' % src)
	os.rmdir(src)
			
#  ������̔���
#
def is_unix():
	return os.name == 'posix'

#  �p�X�Z�p���[�^�̕ϊ��i�\���p�j
#
def upath(path):
	return path.replace('\\', '/')

#  �G���[���b�Z�[�W��\�����ď����𒆎~����
#
def fatal(msg, exitcode=1):
	sys.stderr.write('Error: %s\n' % msg)
	sys.exit(exitcode)

# ----------------------------------------------------------------------
#  Options
#
usage = 'Usage: %prog [options] texmain'
parser = OptionParser(usage = usage)
#
parser.add_option('-v', '--verbose', dest='verbose',
			action='count', default=0,
			help='set verbose mode')
parser.add_option('-V', '--version', dest='version',
			action='store_true', default=False,
			help='show version')
#
(options, args) = parser.parse_args()
if options.version:
	print('%s: Version %s' % (prog, version))
	sys.exit(0)
#
verbose = options.verbose

# ----------------------------------------------------------------------
#  ���C�������J�n
#

for arg in args:
	link, target = arg.replace(os.sep, '/').split('=')
	if verbose:
		print('making link: %s -> %s' % (link, target))

	# target directory �y�� target mark file �̑��݂�ۏ؂���
	#	Windows �ł͓������Ȃ��� symbolic link ���쐬�ł��Ȃ��B
	#	�d�����Ȃ��̂� junciton ���쐬����̂����Ajunction ��
	#	symbolic link �Ƃ͈قȂ�A�ʏ�� directory �Ƃ̋�ʂ�
	#	�ȒP�ɂ͂ł��Ȃ��B
	#	��ֈĂƂ��āA���� directory �� target mark ��u��
	#	���ƂŊ��� junction �������Ă��邩�ۂ��𔻒肷��B
	#	unix �ł͕K�v�Ȃ����R�[�h���ώG�ɂȂ�̂œ��P����B
	#
	if os.path.exists(target) and not os.path.isdir(target):
		fatal('"%s" is not a directory' % target)
	os.makedirs(target, exist_ok=True)
	if not os.path.exists('%s/%s' % (target, target_mark)):
		f = open('%s/%s' % (target, target_mark), 'w')
		f.close()

	# link �����݂���ꍇ
	#
	if os.path.exists(link):

		# ����̓f�B���N�g���łȂ���΂����Ȃ��B
		#
		if not os.path.isdir(link):
			fatal('"%s" is not a directory' % link)

		# ���ꂪ target (����) ���w���Ă���Ή������Ȃ��Ă悢�B
		#
		if os.path.exists('%s/%s' % (link, target_mark)):
			if verbose > 1:
				print('"%s" already exists' % link)
			continue

		# �����Ȃ���΁A���e�� target �ɃR�s�[������ō폜����B
		#
		move_files(os.path.abspath(link), os.path.abspath(target))

	# link �̖��̂� target �Ƀ����N�𒣂�B
	#	Window �ł� junction, unix �ł� symbolic link ���g���B
	#
	if is_unix():
		cmnd = 'ln -s %s %s' % (target, link)
	else:
		dos_link = link.replace('/', os.sep)
		dos_target = target.replace('/', os.sep)
		cmnd = 'mklink /j %s %s' % (dos_link, dos_target)
	if verbose > 1:
		print('%s %s' % ('%%' if is_unix() else '>', cmnd))
	proc = subprocess.Popen(cmnd, shell=True, stdout=subprocess.DEVNULL)
	stat = proc.wait()
	if stat != 0:
		fatal('%s failed (%d)' % 'ln' if is_unix() else 'mklink')

sys.exit(0)

# end: cmake_ln.py
