#!/usr/bin/env python
# -*- coding: utf-8 -*-
# ======================================================================
#  CLASS:
#	VersionControlSystem:
#		Wrapper class to get some information like revision
#		number from source code version control system.
#		Currently available systems are:
#		  'Subversion'	    Apache Subversion system
#		  'GitHub'	    GitHub system
#
#  INITIALIZER:
#	obj = VersionControlSystem(system, args=None, verbose=0)
#	arguments:
#	    system:	Version control system name.
#			'Subversion'	Apache Subversion system
#			'GitHub'	GitHub system
#	    args:	Atguments to get system information (dic).
#			  'url':	Url of the repository.
#	    verbose:	Verbose level (int) (0: silent).
#	    
#  METHODS:
#	code, rev, err = revision()
#	    Get revision number string.
#	    returns:
#		code:	    0: success, other: failure (int).
#		rev:	    Revision (str).
#		err:	    Error message got from stderr (str).
#
#	info = revision_info(commit_id='HEAD')
#	    Get commit information.
#	    arguments:
#		commit_id:  Commit short name to retrieve (str).
#			    If 'all', get all commit info.
#	    returns:
#		'all':	    List of triplets.
#		other:	    Triplet [short-id, long-id, date]
#				short_id:   Short form commit id (str).
#				full_id:    Long form commit id (str).
#				date:	    Commit date ('YYYY-MM-DD').
#			    [] if can not get information.
#
#	content = get_file_content(path, commit_id)
#	    Get file contents of specified revision.
#	    arguments:
#		path:	    File path relative to repository top dir (str).
#		commit_id:  Commit id (short form will do) (str).
#	    returns:	    File contents (str).
#
# ----------------------------------------------------------------------
#  VERSION:
#	Ver 1.0  2017/01/11 F.Kanehori	First version (Subversion only).
#	Ver 1.1  2017/09/13 F.Kanehori	Python library revised.
#	Ver 1.2  2017/11/16 F.Kanehori	Python library path �̕ύX.
#	Ver 1.3  2017/12/20 F.Kanehori	GitHub �Ŏ���.
#	Ver 1.4  2018/01/17 F.Kanehori	Add get_file_content().
# ======================================================================
import sys
import os
import re
import datetime
from optparse import OptionParser

# local python library
#
sys.path.append('../../src/RunSwig')
from FindSprPath import *
spr_path = FindSprPath('VersionControlSystem')
libdir = spr_path.abspath('pythonlib')
sys.path.append(libdir)
from Util import *
from Proc import *

# ----------------------------------------------------------------------
#  Class VersionControlSystem
#
class VersionControlSystem:

	#  Class initializer.
	#
	def __init__(self, system, args=None, verbose=0):
		self.clsname = self.__class__.__name__
		self.version = 1.3
		#
		self.system = system
		self.verbose = verbose
		#
		if system == 'Subversion':
			self.obj = self.Subversion(args['url'], verbose)
		elif system == 'GitHub':
			self.obj = self.GitHub(args['url'], verbose)
		#
		if verbose:
			print('VersionControlSystem: %s' % system)

	#  Get revision number.
	#
	def revision(self, dir=None):
		if dir == None:
			revision = self.obj.revision()
		else:
			cwd = os.getcwd()
			os.chdir(dir)
			revision = self.obj.revision()
			os.chdir(cwd)
		return revision

	#  Get revision information.
	#
	def revision_info(self, dir=None, revision='HEAD'):
		if dir:
			cwd = os.getcwd()
			os.chdir(dir)
		if system == 'Subversion':
			r = -1
			s = 'NOT IMPLEMENTED'
			f = None
			d = None
		elif system == 'GitHub':
			revisions = self.obj.revision_info(revision)
		if dir:
			os.chdir(cwd)
		return revisions

	#  Get file contents of specified revision.
	#
	def get_file_content(self, path, revision):
		if system == 'GitHub':
			return self.obj.get_file_content(path, revision)
		# not implemented.
		return None

	#  Subclass: Subversion
	#
	class Subversion:
		def __init__(self, url, verbose):
			self.url = url
			self.verbose = verbose

		def revision(self):
			url = self.url
			cmnd = 'svn info'
			proc = Proc(verbose=self.verbose)
			proc.exec(cmnd, stdout=Proc.PIPE, stderr=Proc.STDOUT)
			status = proc.wait()
			out, err = proc.output()
			#
			revision = "can't get current revision"
			if status == 0:
				lines = out.split('\n')
				pattern = 'Last Changed Rev:\s+(\d+).*'
				for s in lines:
					m = re.match(pattern, s)
					if m:
						revision = m.group(1)
			return status, revision, err

	#  Subclass: GitHub
	#
	class GitHub:
		def __init__(self, url, verbose):
			self.url = url
			self.verbose = verbose

		def revision(self):
			url = self.url
			cmnd = 'git log --abbrev-commit --oneline --max-count=1'
			status, out, err = self.__exec(url, cmnd)
			#
			rev = None
			err = "can't get current revision"
			if status == 0:
				pattern = '(^[0-9a-f]+\s)'
				m = re.match(pattern, out)
				if m:
					rev = m.group(1)
			return status, rev, err

		def revision_info(self, commit_id='HEAD'):
			url = self.url
			cmnd = 'git log'
			status, out, err = self.__exec(url, cmnd)
			if status != 0:
				return []
			#
			infos = []
			for lines in out.split('\\'):
				for line in lines.split('\n'):
					pattern = 'commit\s+([0-9a-f]+)'
					m = re.match(pattern, line)
					if m:
						long_id = m.group(1)
						short_id = long_id[:7]
						continue
					pattern = 'Date:\s+(.+)'
					m = re.match(pattern, line)
					if not m:
						continue
					ifmt = '%a %b %d %H:%M:%S %Y %z'
					ofmt = '%Y-%m%d,%H:%M:%S'
					mstr = m.group(1)
					dt = datetime.strptime(mstr, ifmt)
					date = dt.strftime(ofmt)
					info = [short_id, long_id, date]
					if short_id == commit_id or commit_id == 'HEAD':
						return info
					infos.append(info)
			return infos

		def get_file_content(self, path, commit_id):
			url = self.url
			contents = []
			cmnd = 'git show %s:%s' % (commit_id, path)
			status, out, err = self.__exec(url, cmnd)
			if status != 0:
				return None
			return out

		def __exec(self, url, cmnd):
			cmnd1 = cmnd
			cmnd2 = 'nkf -s'
			proc1 = Proc(verbose=self.verbose)	# git
			proc2 = Proc(verbose=self.verbose)	# nkf
			proc1.exec(cmnd1, stdout=Proc.PIPE, stderr=Proc.STDOUT)
			proc2.exec(cmnd2, stdin=proc1.proc.stdout,
					  stdout=Proc.PIPE, stderr=Proc.STDOUT)
			status1 = 0
			status2 = 0
			#status2 = proc2.wait()		# Why?
			status1 = proc1.wait()
			status = status1 + status2
			out, err = proc2.output()
			return status, out, err

# ----------------------------------------------------------------------
#  Test main
#
#  ** CAUTION **
#	This test program is used by DailyBuild task.
#	    "TestAllGit.bat" and "MakeReport{Git|SVN}.bat"
#	So do not DELETE nor MODIFY this program.
# ----------------------------------------------------------------------
if __name__ == '__main__':

	topdir_svn = '../../..'
	topdir_git = '../../../../Springhead'

	# --------------------------------------------------------------
	usage = 'Usage: %prog [options] {HEAD | all | commit-id}'
	parser = OptionParser(usage = usage)
	parser.add_option('-s', '--subversion',
				dest='subversion', action='store_true', default=False,
				help='use Subversion')
	parser.add_option('-g', '--github',
				dest='github', action='store_true', default=False,
				help='use GitHub')
	parser.add_option('-f', '--fname',
				dest='fname', default=None,
				help='get file content')
	parser.add_option('-v', '--verbose',
				dest='verbose', action='count', default=0,
				help='set verbose mode')
	parser.add_option('-V', '--version',
				dest='version', action='store_true', default=False,
				help='show version')
	(options, args) = parser.parse_args()
	if len(args) != 1:
		parser.error("incorrect number of arguments")
	repo_sub = options.subversion
	repo_git = options.github
	verbose = options.verbose
	revision = args[0]

	if repo_sub and repo_git:
		print('invalid combination of arguments (-s and -g)')
		print(usage)
		sys.exit(-1)
	if not repo_sub and not repo_git:
		print('either -s or -g required')
		sys.exit(-1)

	system = 'Subversion' if repo_sub else 'GitHub'

	# --------------------------------------------------------------
	def test(system, args, topdir, verbose):
		vcs = VersionControlSystem(system, args, verbose)
		code, rev, err = vcs.revision(topdir)
		if code == 0:
			print('%s: revision: %s' % (system, rev))
		else:
			print('%s: Error: %s (%s)' % (system, rev, err))
		if system == 'Subversion':
			return
		#
		revisions = vcs.revision_info(topdir)
		print('default: %s' % revisions)
		revisions = vcs.revision_info(topdir, '7813b94')
		print('7813b94: %s' % revisions)
		revisions = vcs.revision_info(topdir, 'all')
		print('all:')
		for rev in revisions:
			print('         %s' % rev)

	def info(system, args, topdir, commit_id):
		vcs = VersionControlSystem(system, args, verbose)
		revs = vcs.revision_info(topdir, commit_id)
		if commit_id == 'all':
			for rev in revs:
				print('%s,%s,%s' % (rev[0], rev[1], rev[2]))
		else:
			print('%s,%s,%s' % (revs[0], revs[1], revs[2]))
		return revs

	def contents(topdir, fname, commit_id):
		vcs = VersionControlSystem(system, args, verbose)
		revs = vcs.revision_info(topdir, commit_id)
		contents = vcs.get_file_content(fname, commit_id)
		print('----[%s]----' % commit_id)
		print(contents)

	# --------------------------------------------------------------
	if system == 'Subversion':
		args = {'url': 'http://springhead.info/spr2/Springhead/trunk/'}
		test(system, args, topdir_svn, verbose)

	if system == 'GitHub':
		args = {'url': 'http://github.com/sprphys/Springhead/'}
		if options.fname:
			contents(topdir_git, options.fname, revision)
		else:
			revisions = info(system, args, topdir_git, revision)

	sys.exit(0)

# end: VersionControlSystem.py
