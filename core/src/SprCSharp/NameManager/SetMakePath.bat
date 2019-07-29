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
:: ============================================================================
set PROG=%~n0

set SCRIPT=..\..\RunSwig\find_path.py

echo %PROG%: wait a moment ..
for /f "usebackq" %%o in (`python %SCRIPT% -s nmake.exe`) do set OUT="%%o"
if "%out%" equ "" (
	set MAKEPATH=
) else (
	set MAKEPATH=!OUT:/= !
)

:done
endlocal && (set MAKEPATH=%MAKEPATH%)
exit /b

::end SetMakePath.bat
