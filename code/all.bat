@set include=
@del /q debug\base\mp\vm
@cd game
call game.bat
@cd ..\cgame
call cgame.bat
@cd ..\ui
call ui.bat
@cd ..\gametype\gt_ctf
call gt_ctf.bat
@cd ..\gt_inf
call gt_inf.bat
@cd ..\gt_elim
call gt_elim.bat
@cd ..\gt_dem
call gt_dem.bat
@cd ..\gt_dm
call gt_dm.bat
@cd ..\gt_tdm
call gt_tdm.bat
@cd ..\..

@echo off
echo .
echo .

set bad = 0
if not exist "game\vm\sof2mp_game.qvm" goto badGame
:testcgame
if not exist "cgame\vm\sof2mp_cgame.qvm" goto badCGame
:testui
if not exist "ui\vm\sof2mp_ui.qvm" goto badUI
:testdm
if not exist "gametype\gt_dm\vm\gt_dm.qvm" goto badDM
:testtdm
if not exist "gametype\gt_tdm\vm\gt_tdm.qvm" goto badTDM
:testctf
if not exist "gametype\gt_ctf\vm\gt_ctf.qvm" goto badCTF
:testinf
if not exist "gametype\gt_inf\vm\gt_inf.qvm" goto badINF
:testdem
if not exist "gametype\gt_dem\vm\gt_dem.qvm" goto badDEM
:testelim
if not exist "gametype\gt_elim\vm\gt_elim.qvm" goto badELIM
if %bad == "0" goto goodBuild
goto end

:badGame
echo ***** SoF2MP_game.qvm did not build!
set bad = 1
goto testcgame

:badCGame
echo ***** SoF2MP_cgame.qvm did not build!
set bad = 1
goto testui

:badUI
echo ***** SoF2MP_ui.qvm did not build!
set bad = 1
goto end

:badDM
echo ***** gt_dm.qvm did not build!
set bad = 1
goto end

:badTDM
echo ***** gt_tdm.qvm did not build!
set bad = 1
goto end

:badCTF
echo ***** gt_ctf.qvm did not build!
set bad = 1
goto end

:badINF
echo ***** gt_inf.qvm did not build!
set bad = 1
goto end

:badELIM
echo ***** gt_elim.qvm did not build!
set bad = 1
goto end

:badDEM
echo ***** gt_dem.qvm did not build!
set bad = 1
goto end

:goodBuild
echo VMs were built successfully!

:end
echo .
echo .
