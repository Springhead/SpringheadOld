@echo off
:: ***********************************************************************************
::  SYNOPSIS:	RunSwig_CSharp target
::
::  ARGUMENTS:
::	target		�����N����v���W�F�N�g�̎w��
::	    ALL		���ׂẴv���W�F�N�g���܂ލ\���Ƃ���.
::	    Physics	Physics ���܂ލŏ��̍\���Ƃ�����܂ލ\���Ƃ���.
::	
::  DESCRIPTION:
::      �t�@�C���̈ˑ��֌W�𒲂ׂāACSharpSWig.bat ���œK�Ɏ��s����.
::	�� ���̃X�N���v�g�ō쐬���� makefile �����s����.
::
::    �@���s����v���W�F�N�g�� ..\..\src\RunSwig\do_swigall.projs �ɒ�`����Ă���
::      ���̂��g�p����. �������v���W�F�N�g Base �͒�`�̗L���Ɋւ��Ȃ����s����.
::
:: ***********************************************************************************
::  Version:
::	Ver 1.0	 2015/03/18 F.Kanehori  ����
::	Ver 2.0	 2016/02/08 F.Kanehori  wrapper file ����
::	Ver 3.0	 2016/12/07 F.Kanehori  �����N�\���w�����
::	Ver 3.1  2016/12/15 F.Kanehori	���b�p�t�@�C���쐬�����ύX
::	Ver 3.2	 2017/01/16 F.Kanehori	NameManger ����
::	Ver 3.3  2017/08/07 F.Kanehori	Bug fixed.
::	Ver 3.3a 2019/07/25 F.Kanehori	�g�p nmake �̕\�� (�f�o�b�O�p)
:: ***********************************************************************************
setlocal enabledelayedexpansion
set PROG=%~n0
set CWD=%cd%
set DEBUG=1

:: ------------
::  �����̏���
:: ------------
set TARGET=%1
if "%TARGET%" equ "" (
    echo Usage: %PROG% target
    echo     target     ALL ^| Physics ^| ...
    exit /b
)
if %DEBUG% == 1 (
    echo TARGET: [%TARGET%]
)

:: ------------------------
::  ���ʊ��ϐ���ǂݍ���
:: ------------------------
call ..\NameManager\NameManager.bat
if %DEBUG% == 1 (
    echo %~nx0
    call :show_abspath INCDIR %INCDIR%
    call :show_abspath SRCDIR %SRCDIR%
    call :show_abspath ETCDIR %ETCDIR%
    call :show_abspath CS_SRC %CS_SRC%
    call :show_abspath CS_IMP %CS_IMP%
    call :show_abspath CS_EXP %CS_EXP%
    call :show_abspath TARGETFILE %TARGETFILE%
    echo. 
)

:: �ˑ��֌W�ɂ͂Ȃ��ƌ��􂷃t�@�C���̈ꗗ
::
set EXCLUDES=

:: makefile �ɏo�͂���Ƃ��̃p�X
set INCDIROUT=..\..\include
set SRCDIROUT=..\..\src
set CSHARPSWIG=RunSwig_CSharp\%CSHARPSWIG%

:: �g�p����t�@�C����
::
set MAKEFILE=Makefile_CSharp.swig

:: �g�p����p�X
::
call ..\NameManager\SetMakePath.bat
if not exist %MAKEPATH% (
    echo %PROG%: Error: can not find '%MAKE%' path.
    exit /b
)
echo using %MAKEPATH%\nmake.exe

:: ------------------------------
::  �������郂�W���[���ꗗ���쐬
:: ------------------------------
set PROJECTS=Base
set SWIGMACRO=

if /i "%TARGET%" equ "ALL" (
	for /f "tokens=1,*" %%m in (%PROJSFILE%) do (
    		set PROJECTS=!PROJECTS! %%m
	)
) else (
	for %%t in (%TARGET:,= %) do (
		for /f "tokens=1,*" %%m in (%PROJSFILE%) do (
			if "%%m" equ "%%t" (
	    			set PROJECTS=!PROJECTS! %%n %%m
	    			set PROJECTS=!PROJECTS:,= !
	    			:: �d���v�f����菜��
	    			call :bag_to_set PROJECTS_tmp "!PROJECTS!"
	    			set PROJECTS=!PROJECTS_tmp!
			)
    		)
	)
	:: swig�p�̃}�N�����`����
	if "!TARGET!" equ "!TARGET:,= !" (
		set SWIGMACRO=%TARGET%_ONLY
	) else (
		set SWIGMACRO=!TARGET:,=_and_!
	)
)
if "%PROJECTS%" equ "" (
    echo %PROG%: Error: invalid target name "%TARGET%"
    exit /b
)

:: ------------------------------
::  .i �t�@�C���̈ꗗ���쐬
:: ------------------------------
set IFILES=
for %%p in (%PROJECTS%) do (
    set IFILES=!IFILES! ./%%p.i
)

set IFILES=%IFILES:~1%

echo Projects:  [%PROJECTS%]
echo SWIGMACRO: [%SWIGMACRO%]
echo IFiles:    [%IFILES%]

:: ------------------------------
::  ���W���[���ɂ܂����鏉����
:: ------------------------------
call :truncate_file %SIGNATUREFILE%
del /f %WRAPPERSBUILTFILE% > NUL 2>&1

:: ------------------------------
::  ��ƃf�B���N�g���̍쐬
:: ------------------------------
for %%d in (%CS_SRC% %CS_IMP% %CS_EXP%) do (
	set TMPDIR=%%d\tmp
	if not exist !TMPDIR! (
		echo making directory !TMPDIR!
		mkdir !TMPDIR!
	)
)

:: ----------
::  �����J�n
:: ----------
echo making ...
for %%p in (%PROJECTS%) do (
    echo   Project: %%p
    set MKFILE=%MAKEFILE%.%%p
    call :collect_headers %%p
    call :make_makefile %%p ..\!MKFILE! "!INCHDRS!" "!SRCHDRS!" "%IFILES%"
    cd ..
    if %DEBUG% gtr 1 (
	cmd /c %MAKE% -f !MKFILE!
    ) else (
	cmd /c %MAKE% -f !MKFILE! > NUL 2>&1
    )
    cd %CWD%
)

:: -------------------------
::  wrapper file ���܂Ƃ߂�
:: -------------------------
if exist %WRAPPERSBUILTFILE% (
    echo combining wrapper files
    set WF_SRC=%SUBDIR_SRC:/=\%\%MOD_WRAPPERFILE_SRC%
    set WF_IMP=%SUBDIR_IMP:/=\%\%MOD_WRAPPERFILE_IMP%
    set WF_EXP=%SUBDIR_EXP:/=\%\%MOD_WRAPPERFILE_EXP%
    type ..\!WF_SRC!.prologue > ..\!WF_SRC!
    type ..\!WF_IMP!.prologue > ..\!WF_IMP!
    type ..\!WF_EXP!.prologue > ..\!WF_EXP!
    for %%f in (..\%SUBDIR_SRC:/=\%\tmp\*.cs)  do ( type %%f >> ..\!WF_SRC! )
    for %%f in (..\%SUBDIR_IMP:/=\%\tmp\*.cs)  do ( type %%f >> ..\!WF_IMP! )
    for %%f in (..\%SUBDIR_EXP:/=\%\tmp\*.cpp) do ( type %%f >> ..\!WF_EXP! )
    echo } >> ..\!WF_SRC!
    echo.   } >> ..\!WF_IMP!
    echo } >> ..\!WF_IMP!
    echo } >> ..\!WF_EXP!
)

:: -----------------------------
::  TARGET ���t�@�C���ɋL�^����
:: -----------------------------
echo last target: %TARGET%
echo %TARGET% > %TARGETFILE%

:: ----------
::  �����I��
:: ----------
endlocal
exit /b

:: -----------------------------------------------------------------------------------
::  �t�@�C���̏������i��̃t�@�C���Ƃ���j
:: -----------------------------------------------------------------------------------
:truncate_file
    if exist %1 del /F %1
    type NUL > %1
exit /b

:: -----------------------------------------------------------------------------------
::  �t�@�C���ւ̒ǉ�
:: -----------------------------------------------------------------------------------
:append_file
    if exist %1 type %1 >> %2
exit /b

:: -----------------------------------------------------------------------------------
::  ����1 �ŗ^����ꂽ�v���W�F�N�g�̃w�b�_�������W����
:: -----------------------------------------------------------------------------------
:collect_headers
    set PROJECT=%1

    :: �ˑ��t�@�C�������W�߂�
    ::
    set INCHDRS=
    for %%f in (%INCDIR%\%PROJECT%\*.h) do (
        call :one_of "%EXCLUDES%" %%~nxf
        if "!$result!" equ "no" set INCHDRS=!INCHDRS! %%~nxf
    )
    call :add_prefix "!INCHDRS:~1!" %INCDIROUT%\%PROJECT%
    set INCHDRS=%$string:\=/%
    if %DEBUG% gtr 2 echo INCHDRS  [%INCHDRS%]

    set SRCHDRS=
    for %%f in (%SRCDIR%\%PROJECT%\*.h) do (
        call :one_of "%EXCLUDES%" %%~nxf
        if "!$result!" equ "no" set SRCHDRS=!SRCHDRS! %%~nxf
    )
    call :add_prefix "!SRCHDRS:~1!" %SRCDIROUT%\%PROJECT%
    set SRCHDRS=%$string:\=/%
    if %DEBUG% gtr 2 echo SRCHDRS  [%SRCHDRS%]

exit /b

:: -----------------------------------------------------------------------------------
::  makefile ���쐬����
::      ����1   ���W���[����
::      ����2   makefile ��
::      ����3   "�ˑ��w�b�_�t�@�C�������X�g"
::      ����4   "�ˑ��\�[�X�t�@�C�������X�g"
:: -----------------------------------------------------------------------------------
:make_makefile
    setlocal enabledelayedexpansion
    set MODULE=%1
    set MKFILE=%2
    set INCHDRS=%~3
    set SRCHDRS=%~4
    set INTFILES=%~5
    if %DEBUG% gtr 1 (
        echo MODULE   [%MODULE%]
        echo MKFILE   [%MKFILE%]
        echo INCHDRS  [%INCHDRS%]
        echo SRCHDRS  [%SRCHDRS%]
        echo INTFILES [%INTFILES%]
    )

    set TARGET_SRC=./%SUBDIR_SRC%/CS%MODULE%.cs
    set TARGET_ALL=%TARGET_SRC%
    rem ------------------------------------------------------
    rem set TARGET_IMP=%SUBDIR_IMP%/CS%MODULE%.cs
    rem set TARGET_EXP=%SUBDIR_EXP%/CS%MODULE%.cpp
    rem set TARGET_ALL=%TARGET_SRC% %TARGET_IMP% %TARGET_EXP%
    rem ------------------------------------------------------

    set DEPENDENCIES=%INCHDRS% %SRCHDRS% %INTFILES%
    if %DEBUG% gtr 1 (
        echo TARGET       [%TARGET%]
        echo DEPENDENCIES [%DEPENDENCIES%]
    )

    echo #  Do not edit. RunSwig_CSharp.bat will update this file.   > %MKFILE%
    echo #  File: %MKFILE%	>> %MKFILE%
    echo.			>> %MKFILE%
    echo INCHDRS=\>> %MKFILE%
    for %%f in (%INCHDRS%) do (
        echo %%f \>> %MKFILE%
    )
    echo.			>> %MKFILE%
    echo SRCHDRS=\>> %MKFILE%
    for %%f in (%SRCHDRS%) do (
        echo %%f \>> %MKFILE%
    )
    echo.			>> %MKFILE%
    echo INTFILES=\>> %MKFILE%
    for %%f in (%INTFILES%) do (
        echo %%f \>> %MKFILE%
    )
    echo.			>> %MKFILE%
    echo FIXED_WRAPPERS=\>> %MKFILE%
    echo ./SprCSharp/wrapper.cs		\>> %MKFILE%
    echo ./SprImport/wrapper.cs		\>> %MKFILE%
    echo ./SprExport/wrapper.cpp	\>> %MKFILE%
    echo.			>> %MKFILE%
    echo WRAPPERS=\>> %MKFILE%
    echo ./SprCSharp/module.wrapper.cs	\>> %MKFILE%
    echo ./SprImport/module.wrapper.cs	\>> %MKFILE%
    echo ./SprExport/module.wrapper.cpp	\>> %MKFILE%
    echo.			>> %MKFILE%

    echo all:	%TARGET_ALL%    >> %MKFILE%
    echo.			>> %MKFILE%
    echo %TARGET_SRC%:	$(INCHDRS) $(SRCHDRS) $(INTFILES) $(FIXED_WRAPPERS)>> %MKFILE%
    echo.	call %CSHARPSWIG% %MODULE% %SWIGMACRO%	>> %MKFILE%
    echo.				>> %MKFILE%
    echo $(INCHDRS):			>> %MKFILE%
    echo.				>> %MKFILE%
    echo $(SRCHDRS):			>> %MKFILE%
    echo.				>> %MKFILE%
    echo $(INTFILES):			>> %MKFILE%
    echo.				>> %MKFILE%
    echo $(FIXED_WRAPPERS):		>> %MKFILE%
    echo.				>> %MKFILE%
    echo $(WRAPPERS):			>> %MKFILE%
    echo.				>> %MKFILE%
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

:: -----------------------------------------------------------------------------------
::  �W������d�������v�f����菜��
:: -----------------------------------------------------------------------------------
:bag_to_set
	setlocal enabledelayedexpansion
	set SET=
	for %%b in (%~2) do (
		set IN=0
		for %%s in (!SET!) do (
			if "%%b" equ "%%s" set IN=1
		)
		if !IN! == 0 set SET=!SET! %%b
	)
	endlocal && (set %1=%SET:~1%)
exit /b

:: -----------------------------------------------------------------------------------
::  �f�o�b�O�p
:: -----------------------------------------------------------------------------------
:show_abspath
    echo %1:  [%~f2]
exit /b

::end RunSwig_CSharp.bat
