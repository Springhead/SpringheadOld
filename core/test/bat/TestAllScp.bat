rem === �e�X�g�����s���� ===

rem === ���x���t���Ɏg�����ϐ��̏����� ===

set DATESL=%DATE:~2,10%
set DATE=%DATESL:/=.%
set BUILD_S=
set BUILD_F=
set BUILD_LIST=�r���h�����i
set BUILD_F_LIST=�r���h���s�i
set RUN_S=
set RUN_F=
set RUN_LIST=���s�����i
set RUN_F_LIST=���s���s�i

echo ���t : %DATE% > log\Build.log
echo --- �r���h�̃��O ---  >> log\Build.log
echo. >> log\Build.log

echo ���t : %DATE% > log\BuildError.log
echo --- �r���h�G���[�̃��O --- >> log\BuildError.log
echo. >> log\BuildError.log

echo ���t : %DATE% > log\Run.log
echo --- ���s�̃��O ---  >> log\Run.log
echo. >> log\Run.log

echo ���t : %DATE% > log\RunError.log
echo --- ���s�G���[�̃��O --- >> log\RunError.log
echo. >> log\RunError.log

echo ���t : %DATE% > log\History.log
echo --- �X�V�����̃��O --- >> log\History.log
echo. >> log\History.log

rem === �r���h�e�X�g���s��(�e�X�g���s���t�@�C���͈����Ŏw��) ===
rem call bat\BuildVC8(RunDebug).bat (����1) (����2) 
rem (����1) : �v���W�F�N�g�t�@�C���̏ꏊ
rem (����2) : �v���W�F�N�g�t�@�C����(BuildMFC-.dsp�̑O�̕���, BuildBCB-.bpg�̑O�̕���)
for /D %%p in (..\src\tests\*) do for /D %%n in (%%p\*) do call bat\BuildVC8.bat %%n %%~nn
set BUILD_LIST=%BUILD_LIST:~0,-1%�j
set BUILD_F_LIST=%BUILD_LIST:~0,-1%�j
set RUN_LIST=%RUN_LIST:~0,-1%�j
set RUN_F_LIST=%RUN_LIST:~0,-1%�j


if "%BUILD_S%" == "�r���h����" svn copy svn+ssh://sprsvn/export/spr/svn/repository/Springhead2/trunk svn+ssh://sprsvn/export/spr/svn/repository/Springhead2/tags/BuildSucceed%date% -m %BUILD_LIST% %RUN_LIST%

rem === Springhead2�̍X�V������History.log�ɏo�� ===
svn log svn+ssh://sprsvn/export/spr/svn/repository/Springhead2/trunk > log/History.log
if exist log\result.log del log\result.log
if "%BUILD_S%" == "�r���h����" echo %BUILD_LIST% %RUN_LIST%>>log\result.log
if "%BUILD_F%" == "�r���h���s" echo %BUILD_F_LIST% %RUN_F_LIST%>>log\result.log

rem === ���O��Samba�ɃR�s�[���� ===
set PUTTYPROF=spr
set SERVNAME=springhead.info
set DIRPATH=/home/WWW/springhead/springhead2
set WEBBASE=%SERVNAME%:%DIRPATH%
pscp -r -p -load %PUTTYPROF% log\*.log %WEBBASE%/

set PUTTYPROF=seven
set SERVNAME=seven77.ddo.jp
set DIRPATH=/home/springhead/seven_http
set WEBBASE=%SERVNAME%:%DIRPATH%
pscp -r -p -load %PUTTYPROF% log\*.log %WEBBASE%/


rem **** ���O��SVN�ɃR�~�b�g���� ****
cd log 
svn commit -m "Autobuild done."
cd ..

rem **** �g�p�������ϐ��̃N���A **** 
set DATE=
set BUILD_S=
set BUILD_F=
set BUILD_LIST=
set BUILD_F_LIST=
set RUN_LIST=
set RUN_F_LIST=
