#!/usr/local/bin/python
# -*- coding: utf-8 -*-
# ======================================================================
#  SYNOPSIS:
#	python cmake_sync.py [options] spr_blddir app_blddir app_name projs
#	arguments:
#	    spr_blddir	"${SPR_SRC_DIR}/${OOS_BLD_DIR}"
#	    app_blddir	"${CMAKE_BINARY_DIR}"
#	    app_name	Application name (used in solution file name)
#	    projs	"${SPR_PROJS}"	(dependent projects cmake-list)
#
#  DESCRIPTION:
#	�w�肳�ꂽ�v���W�F�N�g�ɂ��āASpringhead ���� application ��
#	�Ƃ̊Ԃœ������Ƃ�B
#
# ----------------------------------------------------------------------
#  VERSION:
#	Ver 1.0  2019/06/10 F.Kanehori	First version.
# ======================================================================
version = 1.0

import sys
import os
import subprocess
import shutil
import re
from collections import deque
from optparse import OptionParser

# ----------------------------------------------------------------------
#  Constants
#
prog = sys.argv[0].split(os.sep)[-1].split('.')[0]
spr_prev_suffix = 'prev.spr'
app_prev_suffix = 'prev.app'

# ----------------------------------------------------------------------
#  Helper methods
#

#  �t�@�C���̃^�C���X�^���v���r����
#	file1 �̕����V������� True ���A�����Ȃ���� False ��Ԃ�
#	�^�C���X�^���v�� stat.st_mtime ���g�p����
#
def is_newer_file(file1, file2):
	stat1 = os.stat(file1)
	stat2 = os.stat(file2)
	result = stat1.st_mtime > stat2.st_mtime
	if verbose > 1:
		msg = 'NEWER' if result else 'OLDER'
		print('  %s is %s than %s' % (file1, msg, file2))
	return result

#  makefile/projectfile ���r����
#	���̉��ꂩ�ɕύX������� True ���A�����Ȃ���� False ��Ԃ�
#	�Eplatform ���� configuration �̉��ꂩ
#	�E�ˑ�����\�[�X�t�@�C��
#
def is_config_changed(file1, file2):
	if is_unix():
		return is_config_changed_unix(file1, file2)
	else:
		return is_config_changed_win(file1, file2)

def is_config_changed_unix(file1, file2):
	#  ������
	#
	return False

def is_config_changed_win(file1, file2):
	patterns = ['<ProjectConfiguration', '<ClCompile Include=']
	grep1 = grep(patterns, file1)
	grep2 = grep(patterns, file2)
	if grep1 is None or grep2 is None:
		return True
	if verbose == 0:
		return grep1 != grep2

	#  �ȉ��̓e�X�g�p
	#
	result = False
	try:
		str1 = grep1.popleft()
		str2 = grep2.popleft()
		while (str1 and str2):
			if str1 != str2:
				if verbose > 2:
					print('  < %s' % str1)
					print('  > %s' % str2)
				result = True
				break
			str1 = grep1.popleft()
			str2 = grep2.popleft()
	except:
		pass
	return result

#  �v���W�F�N�g�t�@�C���� GUID �𒲂ׂ�
#
def collect_guid(blddir, projs):
	#
	pattern = ['<ProjectGuid>{(.+)}</ProjectGuid>']
	guids = {}
	for proj in projs:
		fname = '%s/%s.vcxproj' % (proj, proj)
		guid = grep(pattern, fname, extract='match')
		guids[proj] = guid.popleft()
	if verbose > 1:
		print('collect_guid: %s' % guids)
	#
	return guids

#  �Ȉ� grep
#	�^����ꂽ������z��̒�����w�肳�ꂽ�p�^�[�����܂ލs�𔲂��o���ĕԂ�
#	�Ԃ��̂� list �ł͂Ȃ��� collections.deque (�������ǂ�)
#
def grep(patterns, fname, extract='line'):
	lines = read_file(fname)
	if lines is None:
		return None
	#
	greps = deque()
	for line in lines:
		match = False
		for patt in patterns:
			m = re.search(patt, line)
			if m:
				match = True
				break
		if match:
			if extract == 'line':
				greps.appendleft(line.strip())
			elif extract == 'match':
				greps.appendleft(m.group(1))
	return greps

#  �t�@�C����ǂݍ���
#
def read_file(fname, encoding='utf-8'):
	try:
		f = open(fname, 'r', encoding=encoding)
	except Exception:
		print('Error: file open error: "%s"' % fname)
		return None
	try:
		lines = f.readlines()
	except Exception as e:
		print('Error: %s: read error: (%s)' % (fname, e))
		return None
	f.close()
	return lines

#  �t�@�C���ɏ�������
#
def write_file(fname, lines):
	try:
		f = open(fname, 'w', encoding='utf-8')
	except Exception:
		print('Error: file open error: "%s"' % fname)
		return None
	try:
		f.writelines(lines)
	except Exception as e:
		print('Error: %s: read error: (%s)' % (fname, e))
		return None
	f.close()
	return 0

#  �t�@�C���𑮐����݂ŃR�s�[����
#
def copy_file(src, dst):
	if verbose > 1:
		print('  copy: %s -> %s' % (src, dst))
	try:
		shutil.copyfile(src, dst)
		shutil.copystat(src, dst)
	except shutil.SameFileError:
		pass
	except Exception as e:
		print(e)

#  �t�@�C�����폜����
#
def remove(fname):
	if verbose > 1:
		print('  remove: %s' % fname)
	try:
		os.remove(fname)
	except:
		pass

#  �t�@�C���̃����N�𒣂�
#	unix �̏ꍇ�� symbolic link
#	Windows �̏ꍇ�� hard link (symbolic link �͌����s���ŗ��p�ł��Ȃ�)
#
def make_link(linkname, target):
	if verbose > 1:
		print('  link: %s -> %s' % (linkname, target))
	if is_unix():
		#  use symbolic link for unix
		cmnd = 'ln -s %s %s' % (upath(target), linkname)
	else:
		#  use hard link for Windows
		cmnd = 'mklink /h %s %s' % (linkname, dpath(target))
	if verbose > 2:
		print('  %% %s' % cmnd)
	proc = subprocess.Popen(cmnd, shell=True)
	stat = proc.wait()
	if stat != 0:
		fatal('link: failed (%d)' % stat)

#  ���p��(OS)�̔���
#
def is_unix():
	return os.name == 'posix'
def is_windows():
	return os.name == 'nt'

#  �p�X�\�L�̕ϊ�
#
def upath(path):
	return path.replace('\\', '/')
def dpath(path):
	return path.replace('/', '\\')

#  �G���[���̈���
#
def fatal(msg, exitcode=1):
	sys.stderr.write('Error: %s\n' % msg)
	sys.exit(exitcode)

# ----------------------------------------------------------------------
#  Options
#
usage = 'Usage: %prog [options] spr_blddir app_blddir projs'
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
verbose = options.verbose
#
spr_blddir = args[0]
app_blddir = args[1]
app_name = args[2]
projs = args[3:]
if verbose:
	print('arguments:')
	print('  spr_blddir: %s' % spr_blddir)
	print('  app_blddir: %s' % app_blddir)
	print('  projs: %s' % projs)
	print()
projs.append('RunSwig')

# ----------------------------------------------------------------------
#  ���C�������J�n
#
cwd = os.getcwd()

if is_windows():
	#  App ���� config ���� GUID ���L�^���Ă���
	#
	org_guids = collect_guid(app_blddir, projs)

for proj in projs:
	os.chdir(proj)
	print('sync: %s' % proj)
	if verbose > 1:
		print('[%s]' % os.getcwd().replace(os.sep, '/'))

	stampfile = 'generate.stamp'
	if is_unix():
		projfile = 'Makefile'
	else:
		projfile = '%s.vcxproj' % proj
	spr_projdir = '%s/%s' % (spr_blddir, proj)
	app_projdir = '.'
	spr_stampfile = '%s/CMakeFiles/%s' % (spr_projdir, stampfile)
	app_stampfile = '%s/CMakeFiles/%s' % (app_projdir, stampfile)
	spr_dependfile = '%s.depend' % spr_stampfile
	app_dependfile = '%s.depend' % app_stampfile
	spr_projfile = '%s/%s' % (spr_projdir, projfile)
	app_projfile = '%s/%s' % (app_projdir, projfile)
	#  �ȉ��̃t�@�C���� app_prohdir �ɒu��
	spr_stamp_prev = '%s.%s' % (app_stampfile, spr_prev_suffix)
	app_stamp_prev = '%s.%s' % (app_stampfile, app_prev_suffix)
	spr_proj_prev = '%s.%s' % (projfile, spr_prev_suffix)
	app_proj_prev = '%s.%s' % (projfile, app_prev_suffix)
	if verbose > 1:
		print('  spr_projfile:   %s (%s)' % (spr_projfile, spr_proj_prev))
		print('  spr_stampfile:  %s (%s)' % (spr_stampfile, spr_stamp_prev))
		print('  spr_dependfile: %s' % spr_dependfile)
		print('  app_projfile:   %s (%s)' % (app_projfile, app_proj_prev))
		print('  app_stampfile:  %s (%s)' % (app_stampfile, app_stamp_prev))
		print('  app_dependfile: %s' % app_dependfile)
	if verbose > 2:
		print('cwd: %s' % os.getcwd().replace(os.sep, '/'))

	#  ���� spr_stamp_prev �����݂��Ȃ����...
	#	���߂Ă�cmake�ł���
	#  Spr ���̃X�^���v�̕��� spr_stamp_prev ���V�������...
	#	Spr ���� cmake ���s�Ȃ�ꂽ
	#	or ���̃A�v���� Spr ���̃X�^���v���X�V����
	#
	if not os.path.exists(spr_stamp_prev) \
	    or is_newer_file(spr_stampfile, spr_stamp_prev):
		#  App ���� Spr ���ɓ���������
		#
		if not os.path.exists(spr_stamp_prev):
			print('  synchronize APP to SPR (no stamp file saved)')
		else:
			print('  synchronize APP to SPR (lib\'s stamp file newer)')
		copy_file(spr_stampfile, spr_stamp_prev)
		copy_file(spr_stampfile, app_stampfile)
		copy_file(spr_dependfile, app_dependfile)

	#  ������������v���W�F�N�g�t�@�C���� Spr ���̂��̂ƈقȂ���e�Ȃ��...
	#	���̃A�v���ŕύX���{����
	#
	elif is_config_changed(app_projfile, spr_projfile):
		#  Spr ���� App ���ɓ���������
		#
		print('  synchronize SPR to APP (makefile/projfile changed)')
		copy_file(projfile, spr_projfile)
		copy_file(app_stampfile, spr_stampfile)
		copy_file(app_dependfile, spr_dependfile)
		copy_file(app_stampfile, spr_stamp_prev)

	#  �����Ȃ���Γ����̕K�v�͂Ȃ�
	#
	else:
		#  App ���̃X�^���v�� Spr ���ɍ��킹�Ă���
		#
		print('  synchronize APP to SPR (project GUID changed)')
		copy_file(spr_stampfile, spr_stamp_prev)
		copy_file(spr_stampfile, app_stampfile)
		copy_file(spr_dependfile, app_dependfile)

	#  ���̃A�v���̍ŐV�̃X�^���v�t�@�C�����Z�[�u���Ă���
	#  makefile/projectfile �̎��̂� Spr ���ւ̃����N�ɕύX����
	#	����s�Ȃ��͖̂��ʂ����Acmake ���t�@�C�������ς��Ă��܂��̂�
	#	�d�����Ȃ�
	#
	remove(app_projfile)
	make_link(projfile, spr_projfile)
	copy_file(app_stampfile, app_stamp_prev)
	os.chdir(cwd)
# endfor

#  Windows (Visual Studio) �̏ꍇ�ɂ͎��̏������K�v�ƂȂ�
#	Solution file �ɋL����Ă���Q�ƃv���W�F�N�g�� GUID ���A�����N�𒣂���
#	��� project file (Spr ��) �� GUID �ɏ���������B
#
if is_windows():
	#  Spr ���Ƀ����N������� GUID �𒲂ׂ�
	#
	lnk_guids = collect_guid(app_blddir, projs)

	#  �\�����[�V�����t�@�C���Ɍ���� GUID �������N��̂��̂ɒu��������
	#	
	sln_fname = '%s/%s.sln' % (app_blddir, app_name)
	new_lines = []
	modified = False
	for line in read_file(sln_fname):
		for proj in projs:
			str1 = org_guids[proj]
			str2 = lnk_guids[proj]
			if line.find(str1):
				line = line.replace(str1, str2)
				modified = True
		new_lines.append(line)
	#
	if modified:
		rc = write_file(sln_fname, new_lines)
		if rc == 0:
			print('solution file is modified (%s)' % upath(sln_fname))
			print('******************************************************')
			print('** Push (R)-button to make solution file up-to-date **')
			print('******************************************************')
# endif is_windows()

sys.exit(0)
