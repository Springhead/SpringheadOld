@echo off
:: ***********************************************************************************
::  File:
::      RunSwig_EmbPython.bat
::
::  Description:
::      �t�@�C���̈ˑ��֌W�𒲂ׂāAEmbPythonSwig.bat ���œK�Ɏ��s����.
::
::	    ���s����v���W�F�N�g�� ..\..\src\RunSwig\do_swigall.projs �ɒ�`����Ă���
::      ���̂��g�p����. �������v���W�F�N�g Base �͒�`�̗L���Ɋւ��Ȃ����s����.
::
:: ***********************************************************************************
::  Version:
::	Ver 1.0  2014/10/29 F.Kanehori  ����
::	Ver 1.1  2017/06/15 F.Kanehori  �ˑ����X�g�� ".i" �t�@�C����ǉ�
::	Ver 2.0  2017/10/04 F.Kanehori  Visual Studio 2015 �Ή�
:: ***********************************************************************************
setlocal enabledelayedexpansion
set PROG=%~n0
set CWD=%cd%
set DEBUG=0

:: ----------
::  �e���`
:: ----------
:: �f�B���N�g���̒�`
::
set BASEDIR=..\..
set BINDIR=%BASEDIR%\bin
set SRCDIR=%BASEDIR%\src
set INCDIR=%BASEDIR%\include
set ETCDIR=%SRCDIR%\RunSwig

set EMBPYTHONDIR=.

:: �ˑ��֌W�ɂ͂Ȃ��ƌ��􂷃t�@�C���̈ꗗ
::
set EXCLUDES=

:: makefile �ɏo�͂���Ƃ��̃p�X
set INCDIROUT=..\..\include
set SRCDIROUT=..\..\src
set EMBDIROUT=..\..\src\EmbPython

:: �g�p����t�@�C����
::
set PROJFILE=do_swigall.projs
set MAKEFILE=Makefile_EmbPython.swig

:: �g�p����v���O������
::
set MAKE=nmake
set SWIG=EmbPythonSwig.bat

:: �g�p����p�X
::
set X32=c:\Program Files
set X64=c:\Program Files (x86)
set ARCH=
if exist "%X32%" set ARCH=%X32%
if exist "%X64%" set ARCH=%X64%
set VSVER=
if exist "%ARCH%\Microsoft Visual Studio 14.0" set VSVER=14.0
set MAKEPATH="%ARCH%\Microsoft Visual Studio %VSVER%\VC\bin"
if not exist %MAKEPATH% (
    echo %PROG%: can not find '%MAKE%' path.
    exit /b
)
rem set SWIGPATH=%BINDIR%\swig
set SWIGPATH=%EMBPYTHONDIR%
set PATH=.;%SWIGPATH%;%MAKEPATH%;%PATH%

:: ------------------------------
::  �������郂�W���[���ꗗ���쐬
:: ------------------------------
set PROJECTS=Base
for /f "tokens=1,*" %%m in (%ETCDIR%\%PROJFILE%) do set PROJECTS=!PROJECTS! %%m
if %DEBUG% == 1 echo Projects are: %PROJECTS%

:: ----------
::  �����J�n
:: ----------
for %%p in (%PROJECTS%) do (
    echo   Project: %%p
    set MKFILE=%MAKEFILE%.%%p
    call :collect_headers %%p
    call :make_makefile %%p !MKFILE! "!INTERFS!" "!INCHDRS!" "!SRCHDRS!"
    cmd /c %MAKE% -f !MKFILE!
)

:: ----------
::  �����I��
:: ----------
endlocal
exit /b

:: -----------------------------------------------------------------------------------
::  ����1 �ŗ^����ꂽ�v���W�F�N�g�̃w�b�_�������W����
:: -----------------------------------------------------------------------------------
:collect_headers
    set PROJECT=%1

    :: �ˑ��t�@�C�������W�߂�
    ::
    ::   swig interface files
    set INTERFS1=
    for %%f in (*.i) do (
        call :one_of "%EXCLUDES%" %%~nxf
        if "!$result!" equ "no" set INTERFS1=!INTERFS1! %%~nxf
    )
    call :add_prefix "!INTERFS1!" %EMBDIROUT%
    set INTERFS1=%$string:\=/%
    set INTERFS2=
    for %%f in (Utility\*.i) do (
        call :one_of "%EXCLUDES%" %%~nxf
        if "!$result!" equ "no" set INTERFS2=!INTERFS2! %%~nxf
    )
    call :add_prefix "!INTERFS2!" %EMBDIROUT%\Utility
    set INTERFS2=%$string:\=/%
    set INTERFS=!INTERFS1! !INTERFS2!
    if %DEBUG% == 1 echo INTERFS [%INTERFS%]

    ::  header files
    set INCHDRS=
    for %%f in (%INCDIR%\%PROJECT%\*.h) do (
        call :one_of "%EXCLUDES%" %%~nxf
        if "!$result!" equ "no" set INCHDRS=!INCHDRS! %%~nxf
    )
    call :add_prefix "!INCHDRS:~1!" %INCDIROUT%\%PROJECT%
    set INCHDRS=%$string:\=/%
    if %DEBUG% == 1 echo INCHDRS [%INCHDRS%]

    ::  source files
    set SRCHDRS=
    for %%f in (%SRCDIR%\%PROJECT%\*.h) do (
        call :one_of "%EXCLUDES%" %%~nxf
        if "!$result!" equ "no" set SRCHDRS=!SRCHDRS! %%~nxf
    )
    call :add_prefix "!SRCHDRS:~1!" %SRCDIROUT%\%PROJECT%
    set SRCHDRS=%$string:\=/%
    if %DEBUG% == 1 echo SRCHDRS [%SRCHDRS%]

exit /b

:: -----------------------------------------------------------------------------------
::  makefile ���쐬����
::      ����1   ���W���[����
::      ����2   makefile ��
::      ����3   "�ˑ��C���^�[�t�F�C�X�t�@�C�������X�g"
::      ����4   "�ˑ��w�b�_�t�@�C�������X�g"
::      ����5   "�ˑ��\�[�X�t�@�C�������X�g"
:: -----------------------------------------------------------------------------------
:make_makefile
    setlocal enabledelayedexpansion
    set MODULE=%1
    set MKFILE=%2
    set INTFILES=%~3
    set INCFILES=%~4
    set SRCFILES=%~5
    if %DEBUG% == 1 (
        echo MODULE   [%MODULE%]
        echo MKFILE   [%MKFILE%]
        echo INTFILES [%INTFILES%]
        echo INCFILES [%INCFILES%]
        echo SRCFILES [%SRCFILES%]
    )

    set TARGET=%EMBPYTHONDIR%/EP%MODULE%.cpp
    set DEPENDENCIES=%INTFILES% %INCFILES% %SRCFILES%
    if %DEBUG% == 1 (
        echo TARGET       [%TARGET%]
        echo DEPENDENCIES [%DEPENDENCIES%]
    )

    echo #  Do not edit. RunSwig_EmbPython.bat will update this file.   > %MKFILE%
    echo #  File: %MKFILE%  >> %MKFILE%
    echo.                   >> %MKFILE%
    echo all:	%TARGET%    >> %MKFILE%
    echo %TARGET%:	%DEPENDENCIES%  >> %MKFILE%
    echo.	call %SWIG% %MODULE%    >> %MKFILE%
    echo.                   >> %MKFILE%
    for %%f in (%DEPENDENCIES%) do (
        echo %%f:	    >> %MKFILE%
    )
    endlocal
exit /b

:: -----------------------------------------------------------------------------------
::  ����2 �ŗ^����ꂽ���O�� ����1 �ŗ^����ꂽ���X�g���ɂ��邩���ׂ�
::  ���ʂ� $result �ɕԂ��iyes �܂��� no�j
:: -----------------------------------------------------------------------------------
:one_of
    set $result=no
    for %%f in (%~1) do (if "%2" equ "%%f" (set $result=yes&& exit /b))
exit /b

:: -----------------------------------------------------------------------------------
::  ����1 �ŗ^����ꂽ�ϐ��ɁA����2 �Ŏw�肳�ꂽ prefix ��ǉ�����
::  ���ʂ� $string �ɕԂ�
:: -----------------------------------------------------------------------------------
:add_prefix
    set $string=
    for %%f in (%~1) do (set $string=!$string! %2\%%f)
    set $string=%$string:~1%
exit /b

::end RunSwig_EmbPython.bat
