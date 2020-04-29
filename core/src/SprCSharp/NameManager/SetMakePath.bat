@echo off
setlocal enabledelayedexpansion
:: ============================================================================
::  SYNOPSIS	SetMakePath
::
::  ARGUMENTS
::	�Ȃ�
::
::  DESCRIPTION
::	nmake ���g�p���邽�߂� path ������, ���ϐ� MAKEPATH �ɐݒ肷��.
::
::  VERSION
::	Ver 1.0  2017/01/16 F.Kanehori	����
::	Ver 1.1  2019/08/25 F.Kanehori	�����p�X�ǉ� (15.0) �y�b��z
::	Ver 2.0  2019/08/29 F.Kanehori	���������ύX
::	Ver 2.1  2019/09/18 F.Kanehori	Bug fixed (default python ���Ȃ��Ƃ�)
::	Ver 2.2  2020/09/18 F.Kanehori	python_adapter �� do_python �ɓ���ւ�
:: ============================================================================
set PROG=%~n0

set CWD=%CD%
set SRCDIR=..\..
set SPRTOP=%SRCDIR%\..\..
set RUNSWIG_DIR=%SRCDIR%\RunSwig
set PYTHON=do_python.bat
set SCRIPT=%RUNSWIG_DIR%\find_path.py

echo %PROG%: wait a moment ..
cd %SRCDIR%
for /f "usebackq" %%o in (`do_python.bat RunSwig\find_path.py -s nmake.exe`) do set OUT="%%o"
cd %CWD%
if "%OUT%" equ "" (
	set MAKEPATH=
) else (
	set MAKEPATH=!OUT:/= !
)

:done
endlocal && (set MAKEPATH=%MAKEPATH%)
exit /b

::end SetMakePath.bat
