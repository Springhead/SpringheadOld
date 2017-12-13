@echo off
setlocal enabledelayedexpansion
:: ============================================================================
::  SYNOPSIS
::	BatchTestAll
::
::  DESCRIPTION
::
::	���ӁFDebug �Ńe�X�g���邽�߂ɂ́APython35_d.lib/dll ���K�v
::	      x64 �͕W�����������AWin32 �̓e�X�g�O�ɃR�s�[����K�v����I�I
::
::  ARGUMENTS
::
::  VERSION
::	Ver 1.0  2017/08/10 F.Kanehori	����
:: ============================================================================
set PROG=%~n0
set CWD=%CD%

:: -------------------------------------------------------------
::  Scripts to use
:: -------------------------------------------------------------
set PYTHON=python
set SCRIPT=BatchTestControl.py

:: -------------------------------------------------------------
::  Test parameters
:: -------------------------------------------------------------
set TOOLSET=-t 14.0
set PLATFORM=-P x64
set CONFIG=-C Release
set DIRS=-d tests -d Samples
set LOG=-l log/dailybuild.log

set PARAMS=%PLATFORM% %CONFIG% -u %LOG%

:: -------------------------------------------------------------
::  Test Go
:: -------------------------------------------------------------
%PYTHON% %SCRIPT% %PARAMS%





endlocal
exit /b

:: end: BatchTestAll.bat
