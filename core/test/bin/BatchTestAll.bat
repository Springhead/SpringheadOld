@echo off
setlocal enabledelayedexpansion
:: ============================================================================
::  SYNOPSIS
::	BatchTestAll [-E]
::	  -E:	�V���A���C�Y�f�[�^�t�@�C��������΁A������폜���Ă���
::		�e�X�g�����s����B
::
::  DESCRIPTION
::	src/tests �y�� src/Samples �ɂ��邷�ׂẴ\�����[�V�����ɂ��āA
::	platform �� configuration �̂��ׂĂ̑g�����ɑ΂��ăe�X�g�����{����B
::
::	���ӁF�e�X�g���s���́A�e�X�g���N�������E�B���h�E����t�H�[�J�X���ړ�
::	�@�@�@���Ȃ����ƁB�����Ȃ��ƁA�v���O�����ɓ��̓f�[�^���n��Ȃ����߂�
::	�@�@�@���s���ʂ̔���ɊԈႢ�������鋰�ꂪ��B
::
:: ----------------------------------------------------------------------------
::  VERSION
::	Ver 1.0  2017/09/21 F.Kanehori	����
:: ============================================================================
set PROG=%~n0
set CWD=%CD%

:: -------------------------------------------------------------
::  Constants
:: -------------------------------------------------------------
set SCRIPT=BatchTestControl.py
set REPORT=MakeReport.py
set LOGDIR=log
set LOGFILE=BatchTestAll.log
set CSVFILE=BatchTestAll.csv

:: -------------------------------------------------------------
::  Test parameters
:: -------------------------------------------------------------
set TOOLSET=-t 14.0
set LOG=-l %LOGDIR%/%LOGFILE%
set DIRS=-d src/tests -d src/Samples
set OPTS=
:next_arg
if /i "%1" equ "-h" (call :usage & exit /b)
if    "%1" equ "-E" (set OPTS=!OPTS! -E & shift & goto :next_arg)

set PARAMS=%TOOLSET% %LOG% %OPTS% %DIRS%

:: -------------------------------------------------------------
::  Test Go
:: -------------------------------------------------------------
python %SCRIPT% %PARAMS%
python %REPORT% -o %LOGDIR%/%CSVFILE% %LOGDIR%/%LOGFILE%

endlocal
exit /b

:: -------------------------------------------------------------
::  Print usage
:: -------------------------------------------------------------
:usage
	echo Usage: %prog% [options]
	echo options:
	echo.    -E:     Erase serialized data file before test starts.
	exit /b

:: end: BatchTestAll.bat
