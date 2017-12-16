@echo off
setlocal enabledelayedexpansion
:: ============================================================================
::  SYNOPSIS
::	BuildVC args (see below)
::
::  DESCRIPTION
::	���� solution �Ŏw�肵���\�����[�V�����t�@�C���ɂ��� Build (and Run)
::	�e�X�g���s�Ȃ�.
::
::  ARGUMENTS
::	toolset_id	�c�[���Z�b�g�̎��� { 10.0 | 11.0 | .. }
::	testset		�e�X�g�Z�b�g���i�\���p�j
::	category	�e�X�g�J�e�S���[���i�\���p�j
::	solution_dir	�\�����[�V�������i�f�B���N�g�����j
::	build_conf	�r���h�I�v�V�����i�\���j
::	build_plat	�r���h�I�v�V�����i�v���b�g�t�H�[���j
::	do_build	�r���h�w�� { yes | no }
::	do_run		���s�w�� { yes | no }
::	log_1		�r���h���ʂ̃��O�t�@�C�����i�ǋL�`���j
::	log_2		�r���h�G���[�̃��O�t�@�C�����i�ǋL�`���j
::	log_3		���s���ʂ̃��O�t�@�C�����i�ǋL�`���j
::	log_4		���s�G���[�̃��O�t�@�C�����i�ǋL�`���j
::	python_ver	Python �̃o�[�W����
::
::  CAUTION
::	���s�ɕK�v�� PATH ���������ݒ肳��Ă��邱��.
::	���̊��ϐ��͌ďo�����Ƌ��L����̂Œ��ӂ��邱��.
::	    BLD_SUCC, BLD_FAIL, BLD_SUCC_LIST, BLD_FAIL_LIST
::	    RUN_SUCC, RUN_FAIL, RUN_SUCC_LIST, RUN_FAIL_LIST
::	Visual Studio 10.0 �ȍ~�݂̂ɑΉ�
::
::  VERSION
::	Ver 1.0  2013/09/18 F.Kanehori	�o�b�`�t�@�C���̍č\��
::	Ver 1.1  2013/12/05 F.Kanehori	Visual Studio 2008 �Ή�
::	Ver 1.2	 2014/06/11 F.Kanehori	�\�����[�V�����t�@�C���̕ʖ�����
::	Ver 1.3	 2014/10/23 F.Kanehori	�o�̓f�B���N�g���w��t�@�C���̓���
::	Ver 1.4	 2014/11/20 F.Kanehori	�r���h�\���� python_ver �𔽉f
::	Ver 1.5  2016/06/02 F.Kanehori	Visual Studio 2015 �Ή�
::	Ver 1.6  2017/07/27 F.Kanehori	EmbPython configuration �̕ύX
::	Ver 1.7  2017/07/27 F.Kanehori	�f�B���N�g�����ύX�ɑΉ� (->dependency)
:: ============================================================================
call :leaf_name PROG %0
set CWD=%cd%
set RET=0

::----------------------------------------------
:: �����̏���
::
call bat\BuildVC_ArgCheck.bat %*
if not %$status% == 0 goto :done

set TOOLSETID=%1&& shift
set TESTSET=%1&& shift
set CATEGORY=%1&& shift
(set SOLUTIONDIR=%1&& set SOLUTION=%~n1) && shift
set CONFIGURATION=%1&& shift
set PLATFORM=%1&& shift
set DO_BLD=%1&& shift
set DO_RUN=%1&& shift
set LOG_BLD=%1&& shift
set LOG_BLDERROR=%1&& shift
set LOG_RUN=%1&& shift
set LOG_RUNERROR=%1&& shift
rem call :vars_dump TOOLSETID TESTSET CATEGORY SOLUTIONDIR CONFIGURATION
rem call :vars_dump PLATFORM DO_BLD DO_RUN LOG_BLD LOG_BLDERROR
rem call :vars_dump LOG_RUN LOG_RUNERROR

set VS_DIR=%TOOLSETID%
if "%TOOLSETID%" equ "9" set VS_DIR=9.0
if "%TOOLSETID%" equ "9.0" set TOOLSETID=9
if "%TOOLSETID%" equ "10" set VS_DIR=10.0
if "%TOOLSETID%" equ "10.0" set TOOLSETID=10
if "%TOOLSETID%" equ "12" set VS_DIR=12.0
if "%TOOLSETID%" equ "12" set TOOLSETID=12.0
if "%TOOLSETID%" equ "14" set TOOLSETID=14.0

::----------------------------------------------
:: PATH �̊m�F
::
set VS_PATH=Microsoft Visual Studio %VS_DIR%
rem if not exist "C:\Program Files\Microsoft Visual Studio %VS_DIR%\" (
if not exist "C:\Program Files\%VS_PATH%\" (
	if not exist "C:\Program Files (x86)\%VS_PATH%\" (
		echo %PROG%: bad toolset ID [%TOOLSETID%]
		set RET=-1
		goto :done
	)
)

::----------------------------------------------
:: �����J�n
::
call :fixed STR %SOLUTION%
set /p=.  %TESTSET%: %CATEGORY%: %STR%	.< NUL
cd %SOLUTIONDIR%

rem ** ���L�t�@�C���̑��ݗL���Ŏ��s�𐧌�ł��� **
rem **** ������, FORCE_DONT_xx �̕����D�悷�� ****
set FOECE_DO_BLD=dailybuild.do.build
set FORCE_DO_RUN=dailybuild.do.run
set FORCE_DONT_BLD=dailybuild.dont.build
set FORCE_DONT_RUN=dailybuild.dont.run
if exist %FOECE_DO_BLD% set DO_BLD=yes
if exist %FORCE_DO_RUN% set DO_RUN=yes
if exist %FORCE_DONT_BLD% set DO_BLD=no
if exist %FORCE_DONT_RUN% set DO_RUN=no

rem **** �o�̓f�B���N�g���̎w�� *******************************************
rem **** �w�肪�Ȃ���� "$TOOLSET/$PLATFORM/$CONFIGURATION" �Ɖ��肷�� ****
rem **** �w��̒��� $PYTHON_VERSION ���܂܂�Ă����Ȃ�΁A�r���h�\���� ****
rem **** %CONFIGURATION%_Py%PYTHOON_VERSION% �ɕύX���� *******************
set OUTDIR_ALIAS_FILE=dailybuild.outdir

set OUTDIRSPEC=$TOOLSET/$PLATFORM/$CONFIGURATION
if exist %OUTDIR_ALIAS_FILE% (
	for /f %%l in (%OUTDIR_ALIAS_FILE%) do set OUTDIRSPEC=%%l
	rem if "%PYTHON_VERSION%" neq "32" (
	rem 	rem ������ python32 �����͗�O
	rem 	set CONFIGURATION=%CONFIGURATION%_Py%PYTHON_VERSION%
	rem 	set /p <nul=!CONFIGURATION! 
	rem )
	rem echo OUTDIRSPEC=[!OUTDIRSPEC!]
)
call set OUTDIRSPEC=%%OUTDIRSPEC:$TOOLSET=%TOOLSETID%%%
call set OUTDIRSPEC=%%OUTDIRSPEC:$PLATFORM=%PLATFORM%%%
call set OUTDIRSPEC=%%OUTDIRSPEC:$CONFIGURATION=%CONFIGURATION%%%
call set OUTDIRSPEC=%%OUTDIRSPEC:$PYTHON_VERSION=py%PYTHON_VERSION%%%

rem **** �\�����[�V�����t�@�C�����̎w�� ******************
rem **** �w�肪�Ȃ���΃f�B���N�g�����Ɠ����Ɖ��肷�� ****
set SOLUTION_ALIAS_FILE=dailybuild.alias

set SOLUTIONNAME=%SOLUTION%
if exist %SOLUTION_ALIAS_FILE% (
	for /f %%l in (%SOLUTION_ALIAS_FILE%) do set SOLUTIONNAME=%%l
)

set BUILD_OPTION="%CONFIGURATION%|%PLATFORM%"
set OUTDIR=%OUTDIRSPEC:/=\%
set EXEFILE=%OUTDIR%\%SOLUTIONNAME%.exe

::----------------------------------------------
:: �r���h
::
if /i "%DO_BLD%" equ "yes" (
	set SOLUTIONFILE=%SOLUTIONNAME%%TOOLSETID%.sln
	if not exist !SOLUTIONFILE! (
		rem echo %PROG%: can't find solution file "!SOLUTIONFILE!"
		set RET=-1
		goto :done
	)
	set LOG=%CWD%\%LOG_BLD%
	set ERRORLOG=%CWD%\%LOG_BLDERROR%
	set /p=build.< NUL

	rem �r���h�����Č��ʂ����O�t�@�C���ɏo��
	echo *** %CATEGORY%: %SOLUTION% *** >> !LOG!
	echo %% devenv !SOLUTIONFILE! /build %BUILD_OPTION% > !LOG!.tmp
	devenv !SOLUTIONFILE! /build %BUILD_OPTION% >> !LOG!.tmp
	type !LOG!.tmp >> !LOG!
	echo. >> !LOG!
	echo. >> !LOG!

	rem �G���[������s�������G���[���O�t�@�C���ɏo��
	echo *** %CATEGORY%: %SOLUTION% *** >> !ERRORLOG!
	type !LOG!.tmp | find " error " >> !ERRORLOG!
	echo. >> !ERRORLOG!
	echo. >> !ERRORLOG!
	del !LOG!.tmp

	if exist %EXEFILE% (
		set BLD_SUCC=�r���h����
		set BLD_SUCC_LIST=%BLD_SUCC_LIST%%CATEGORY%:%SOLUTION%,
	)
	if not exist %EXEFILE% (
		set BLD_FAIL=�r���h���s
		set BLD_FAIL_LIST=%BLD_FAIL_LIST%%CATEGORY%:%SOLUTION%,
	)
) else (
	set /p=.< NUL
)

::----------------------------------------------
:: ���s
::
if /i "%DO_RUN%" equ "yes" (
	if not exist %EXEFILE% goto :done

	set BINBASE=%CWD%\..\bin
	set LIBSBASE=%CWD%\..\..\dependency\bin
	if "%PLATFORM%" equ "x64" (
		set TMPPATH=!LIBSBASE!\win64;!LIBSBASE!\win32
		set TMPPATH=!TMPPATH!;!BINBASE!\win64;!BINBASE!\win32
	) else (
		set TMPPATH=!LIBSBASE!\win32;!BINBASE!\win32
	)
	set PATH=!TMPPATH!;!PATH!
	set LOG=%CWD%\%LOG_RUN%
	set ERRORLOG=%CWD%\%LOG_RUNERROR%
	set /p=run< NUL

	rem ���s�����Č��ʂ����O�t�@�C���ɏo��
	echo *** %CATEGORY%: %SOLUTION% *** >> !LOG!
	rem set ERRORLEVEL=
	%EXEFILE% > !LOG!.tmp
	set ERROR=%ERRORLEVEL%
	type !LOG!.tmp >> !LOG!
	echo. >> !LOG!
	echo. >> !LOG!

	rem �G���[������s�������G���[���O�t�@�C���ɏo��
	echo *** %CATEGORY%: %SOLUTION% *** >> !ERRORLOG!
	if not !ERROR! == 0 (
		type !LOG!.tmp | find " error " >> !ERRORLOG!
	)
	echo. >> !ERRORLOG!
	echo. >> !ERRORLOG!
	del !LOG!.tmp

	if !ERROR! == 0 (
		set RUN_SUCC=���s����
		set RUN_SUCC_LIST=%RUN_SUCC_LIST%%CATEGORY%:%SOLUTION%,
	)
	if not !ERROR! == 0 (
		set RUN_FAIL=���s���s
		set RUN_FAIL_LIST=%RUN_FAIL_LIST%%CATEGORY%:%SOLUTION%,
	)
)

:done
echo .
(
	endlocal
	set BLD_SUCC=%BLD_SUCC%
	set BLD_FAIL=%BLD_FAIL%
	set BLD_SUCC_LIST=%BLD_SUCC_LIST%
	set BLD_FAIL_LIST=%BLD_FAIL_LIST%
	set RUN_SUCC=%RUN_SUCC%
	set RUN_FAIL=%RUN_FAIL%
	set RUN_SUCC_LIST=%RUN_SUCC_LIST%
	set RUN_FAIL_LIST=%RUN_FAIL_LIST%
	set $status=%RET%
)
exit /b


::----------------------------------------------
:: ���[�t���̎�o��
::	arg1:	�l��Ԃ����ϐ���
::	arg2:	�p�X��
::
:leaf_name
	set %1=%~n2
exit /b

::----------------------------------------------
:: �����񒷂��Œ�ɂ���i�\���p�F�ėp���Ȃ��j
::	arg1:	�l��Ԃ����ϐ���
::	arg2:	������
::
:fixed
	setlocal
	set STR1=%2,,,,,,,,,,,,,,,,,,,,,,,,
	set STR2=%STR1:~0,24%
	set STR3=%STR2:,= %
	endlocal && set %1=%STR3%
exit /b

::----------------------------------------------
:: �ϐ��̃_���v
::	arg1:	�ϐ��̃��X�g
::
:vars_dump
	setlocal
	for %%v in (%*) do (
		set VAR=%%v
		call set VAL=%%!VAR!%%
		set VAR=!VAR!                +
		set VAR=!VAR:~0,16!
		echo !VAR!: [!VAL!]
	)
	endlocal
exit /b

::end BuildVC.bat
