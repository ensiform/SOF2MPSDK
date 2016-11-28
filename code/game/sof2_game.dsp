# Microsoft Developer Studio Project File - Name="SoF2game" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=SoF2game - Win32 SH Debug SoF2
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "sof2_game.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "sof2_game.mak" CFG="SoF2game - Win32 SH Debug SoF2"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SoF2game - Win32 Release SoF2" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SoF2game - Win32 Debug SoF2" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SoF2game - Win32 Release SoF2"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "SoF2game___Win32_Release_TA"
# PROP BASE Intermediate_Dir "SoF2game___Win32_Release_TA"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../Release"
# PROP Intermediate_Dir "../Release/SoF2game"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G6 /W4 /GX /O2 /D "WIN32" /D "NDebug SoF2" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /G6 /W4 /GX /Zi /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "MISSIONPACK" /D "QAGAME" /D "_SOF2" /YX /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDebug SoF2" /mktyplib203 /win32
# ADD MTL /nologo /D "NDebug SoF2" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDebug SoF2"
# ADD RSC /l 0x409 /d "NDebug SoF2"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib winmm.lib /nologo /base:"0x20000000" /subsystem:windows /dll /map /machine:I386 /out:"..\Release/qaSoF2gamex86.dll"
# SUBTRACT BASE LINK32 /incremental:yes /debug
# ADD LINK32 kernel32.lib user32.lib winmm.lib /nologo /base:"0x20000000" /subsystem:windows /dll /map:"../Release/sof2mp_gamex86.map" /debug /machine:I386 /def:".\SoF2_game.def" /out:"../Release/sof2mp_gamex86.dll"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "SoF2game - Win32 Debug SoF2"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "SoF2game___Win32_Debug_TA"
# PROP BASE Intermediate_Dir "SoF2game___Win32_Debug_TA"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\Debug"
# PROP Intermediate_Dir "..\Debug\SoF2game"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_Debug SoF2" /D "_WINDOWS" /D "BUILDING_REF_GL" /D "Debug SoF2" /FR /YX /FD /c
# ADD CPP /nologo /G5 /MTd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "BUILDING_REF_GL" /D "Debug SoF2" /D "WIN32" /D "_WINDOWS" /D "MISSIONPACK" /D "QAGAME" /D "_SOF2" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "_Debug SoF2" /mktyplib203 /win32
# ADD MTL /nologo /D "_Debug SoF2" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_Debug SoF2"
# ADD RSC /l 0x409 /d "_Debug SoF2"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib winmm.lib /nologo /base:"0x20000000" /subsystem:windows /dll /map /debug /machine:I386 /out:"..\Debug/qaSoF2gamex86.dll"
# SUBTRACT BASE LINK32 /incremental:no
# ADD LINK32 kernel32.lib user32.lib winmm.lib /nologo /base:"0x20000000" /subsystem:windows /dll /map:"..\Debug\sof2mp_gamex86.map" /debug /machine:I386 /def:".\SoF2_game.def" /out:"..\Debug\sof2mp_gamex86.dll"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "SoF2game - Win32 Release SoF2"
# Name "SoF2game - Win32 Debug SoF2"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\ai_main.c
# End Source File
# Begin Source File

SOURCE=.\ai_util.c
# End Source File
# Begin Source File

SOURCE=.\ai_wpnav.c
# End Source File
# Begin Source File

SOURCE=.\bg_gametype.c
# End Source File
# Begin Source File

SOURCE=.\bg_lib.c
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\bg_misc.c
# End Source File
# Begin Source File

SOURCE=.\bg_player.c
# End Source File
# Begin Source File

SOURCE=.\bg_pmove.c
# End Source File
# Begin Source File

SOURCE=.\bg_slidemove.c
# End Source File
# Begin Source File

SOURCE=.\bg_weapons.c
# End Source File
# Begin Source File

SOURCE=.\g_active.c
# End Source File
# Begin Source File

SOURCE=.\g_antilag.c
# End Source File
# Begin Source File

SOURCE=.\g_bot.c
# End Source File
# Begin Source File

SOURCE=.\g_client.c
# End Source File
# Begin Source File

SOURCE=.\g_cmds.c
# End Source File
# Begin Source File

SOURCE=.\g_combat.c
# End Source File
# Begin Source File

SOURCE=.\g_gametype.c
# End Source File
# Begin Source File

SOURCE=.\g_items.c
# End Source File
# Begin Source File

SOURCE=.\g_main.c
# End Source File
# Begin Source File

SOURCE=.\g_misc.c
# End Source File
# Begin Source File

SOURCE=.\g_missile.c
# End Source File
# Begin Source File

SOURCE=.\g_mover.c
# End Source File
# Begin Source File

SOURCE=.\g_session.c
# End Source File
# Begin Source File

SOURCE=.\g_spawn.c
# End Source File
# Begin Source File

SOURCE=.\g_svcmds.c
# End Source File
# Begin Source File

SOURCE=.\g_syscalls.c
# End Source File
# Begin Source File

SOURCE=.\g_target.c
# End Source File
# Begin Source File

SOURCE=.\g_team.c
# End Source File
# Begin Source File

SOURCE=.\g_trigger.c
# End Source File
# Begin Source File

SOURCE=.\g_utils.c
# End Source File
# Begin Source File

SOURCE=.\g_weapon.c
# End Source File
# Begin Source File

SOURCE=.\q_math.c
# End Source File
# Begin Source File

SOURCE=.\q_shared.c
# End Source File
# Begin Source File

SOURCE=.\SoF2_game.def
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\ai_main.h
# End Source File
# Begin Source File

SOURCE=.\anims.h
# End Source File
# Begin Source File

SOURCE=.\be_aas.h
# End Source File
# Begin Source File

SOURCE=.\be_ai_char.h
# End Source File
# Begin Source File

SOURCE=.\be_ai_chat.h
# End Source File
# Begin Source File

SOURCE=.\be_ai_gen.h
# End Source File
# Begin Source File

SOURCE=.\be_ai_goal.h
# End Source File
# Begin Source File

SOURCE=.\be_ai_move.h
# End Source File
# Begin Source File

SOURCE=.\be_ai_weap.h
# End Source File
# Begin Source File

SOURCE=.\be_ea.h
# End Source File
# Begin Source File

SOURCE=.\bg_local.h
# End Source File
# Begin Source File

SOURCE=.\bg_public.h
# End Source File
# Begin Source File

SOURCE=.\bg_weapons.h
# End Source File
# Begin Source File

SOURCE=.\botlib.h
# End Source File
# Begin Source File

SOURCE=..\cgame\cg_local.h
# End Source File
# Begin Source File

SOURCE=..\cgame\cg_public.h
# End Source File
# Begin Source File

SOURCE=..\cgame\cg_was.h
# End Source File
# Begin Source File

SOURCE=.\chars.h
# End Source File
# Begin Source File

SOURCE=..\qcommon\disablewarnings.h
# End Source File
# Begin Source File

SOURCE=..\ghoul2\G2.h
# End Source File
# Begin Source File

SOURCE=.\g_local.h
# End Source File
# Begin Source File

SOURCE=.\g_public.h
# End Source File
# Begin Source File

SOURCE=.\g_team.h
# End Source File
# Begin Source File

SOURCE=.\inv.h
# End Source File
# Begin Source File

SOURCE=.\match.h
# End Source File
# Begin Source File

SOURCE=..\..\ui\menudef.h
# End Source File
# Begin Source File

SOURCE=.\q_shared.h
# End Source File
# Begin Source File

SOURCE=.\surfaceflags.h
# End Source File
# Begin Source File

SOURCE=.\syn.h
# End Source File
# Begin Source File

SOURCE=..\qcommon\tags.h
# End Source File
# Begin Source File

SOURCE=..\cgame\tr_types.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\game.bat
# End Source File
# Begin Source File

SOURCE=.\game.q3asm
# End Source File
# End Target
# End Project
