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
::  TODO
::	"src/RunSwig/do_swigall.py" �ɂ����l�̃p�X�ݒ肪����B
::	������Ƃ܂Ƃ߂�K�v����B
::
::  VERSION
::	Ver 1.1  2019/08/25 F.Kanehori	�����p�X�ǉ� (15.0) �y�b��z
::	Ver 1.0  2017/01/16 F.Kanehori	����
:: ============================================================================
set PROG=%~n0

set X32=C:\Program Files
set X64=C:\Program Files (x86)
set ARCH=
if exist "%X32%" set ARCH=%X32%
if exist "%X64%" set ARCH=%X64%

for %%v in (14.0 12.0 10.0) do (
	set MAKEPATH="%ARCH%\Microsoft Visual Studio %%v\VC\bin"
	if exist !MAKEPATH! goto :done
)
set MSVC="%ARCH%\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC"
set CWD=%CD%
for %%v in (15.0) do (
	cd /d %MSVC%
	for /d %%d in (*) do (
		if exist "%X32%" set MAKEPATH=%MSVC%\%%d\bin\Hostx64\x64
		if exist "%X64%" set MAKEPATH=%MSVC%\%%d\bin\Hostx86\x86
		if exist !MAKEPATH!\nmake.exe goto :done
	)
)
set MAKEPATH=

:done
endlocal && (set MAKEPATH=%MAKEPATH%)
exit /b

::end SetMakePath.bat
