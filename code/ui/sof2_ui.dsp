# Microsoft Developer Studio Project File - Name="ui" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ui - Win32 SH Debug SoF2
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "sof2_ui.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "sof2_ui.mak" CFG="ui - Win32 SH Debug SoF2"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ui - Win32 Debug SoF2" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ui - Win32 Release SoF2" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ui - Win32 Debug SoF2"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ui___Win32_Debug_SoF2"
# PROP BASE Intermediate_Dir "ui___Win32_Debug_SoF2"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\Debug"
# PROP Intermediate_Dir "..\Debug\ui"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G5 /MTd /W3 /Gm /GX /ZI /Od /I "../jk2/game" /I "." /D "WIN32" /D "_Debug JK2" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "UI_EXPORTS" /D "MISSIONPACK" /FR /YX /FD /GZ /c
# ADD CPP /nologo /G5 /MTd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "_USRDLL" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "UI_EXPORTS" /D "MISSIONPACK" /D "_SOF2" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_Debug JK2" /mktyplib203 /win32
# ADD MTL /nologo /D "_Debug JK2" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_Debug JK2"
# ADD RSC /l 0x409 /d "_Debug JK2"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /base:"0x40000000" /dll /map /debug /machine:I386 /out:"../Debug JK2/uix86.dll" /pdbtype:sept
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 /nologo /base:"0x40000000" /dll /map:"..\Debug\of2mp_uix86.map" /debug /machine:I386 /out:"../Debug/sof2mp_uix86.dll" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "ui - Win32 Release SoF2"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ui___Win32_Release_SoF2"
# PROP BASE Intermediate_Dir "ui___Win32_Release_SoF2"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../Release"
# PROP Intermediate_Dir "../Release/ui"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G6 /W4 /GX /Zi /O2 /I "../jk2/game" /I "." /D "WIN32" /D "NDebug JK2" /D "_WINDOWS" /D "_MBCS" /D "_USRDL" /D "UI_EXPORTS" /D "MISSIONPACK" /YX /FD /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /G6 /W4 /GX /Zi /O2 /D "NDEBUG" /D "_USRDL" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "UI_EXPORTS" /D "MISSIONPACK" /D "_SOF2" /YX /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDebug JK2" /mktyplib203 /win32
# ADD MTL /nologo /D "NDebug JK2" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDebug JK2"
# ADD RSC /l 0x409 /d "NDebug JK2"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /base:"0x40000000" /dll /map /debug /machine:I386 /out:"../Release JK2/uix86.dll"
# ADD LINK32 /nologo /base:"0x40000000" /dll /map:"../Release/sof2mp_uix86.map" /debug /machine:I386 /out:"../Release/sof2mp_uix86.dll"

!ENDIF 

# Begin Target

# Name "ui - Win32 Debug SoF2"
# Name "ui - Win32 Release SoF2"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\game\bg_gametype.c
# End Source File
# Begin Source File

SOURCE=..\game\bg_lib.c
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\game\bg_misc.c
# End Source File
# Begin Source File

SOURCE=..\game\bg_player.c
# End Source File
# Begin Source File

SOURCE=..\game\bg_weapons.c
# End Source File
# Begin Source File

SOURCE=..\game\q_math.c
# End Source File
# Begin Source File

SOURCE=..\game\q_shared.c
# End Source File
# Begin Source File

SOURCE=.\ui.def
# End Source File
# Begin Source File

SOURCE=.\ui_atoms.c
# End Source File
# Begin Source File

SOURCE=.\ui_gameinfo.c
# End Source File
# Begin Source File

SOURCE=.\ui_main.c
# End Source File
# Begin Source File

SOURCE=.\ui_players.c
# End Source File
# Begin Source File

SOURCE=.\ui_shared.c
# End Source File
# Begin Source File

SOURCE=.\ui_syscalls.c
# End Source File
# Begin Source File

SOURCE=.\ui_util.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\cgame\animtable.h
# End Source File
# Begin Source File

SOURCE=..\game\bg_local.h
# End Source File
# Begin Source File

SOURCE=..\game\bg_public.h
# End Source File
# Begin Source File

SOURCE=..\game\bg_weapons.h
# End Source File
# Begin Source File

SOURCE=..\qcommon\disablewarnings.h
# End Source File
# Begin Source File

SOURCE=..\ghoul2\G2.h
# End Source File
# Begin Source File

SOURCE=..\game\g_local.h
# End Source File
# Begin Source File

SOURCE=..\game\g_public.h
# End Source File
# Begin Source File

SOURCE=..\game\g_team.h
# End Source File
# Begin Source File

SOURCE=.\keycodes.h
# End Source File
# Begin Source File

SOURCE=..\..\ui\menudef.h
# End Source File
# Begin Source File

SOURCE=..\game\q_shared.h
# End Source File
# Begin Source File

SOURCE=..\game\surfaceflags.h
# End Source File
# Begin Source File

SOURCE=..\qcommon\tags.h
# End Source File
# Begin Source File

SOURCE=..\cgame\tr_types.h
# End Source File
# Begin Source File

SOURCE=.\ui_local.h
# End Source File
# Begin Source File

SOURCE=.\ui_public.h
# End Source File
# Begin Source File

SOURCE=.\ui_shared.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\ui.bat
# End Source File
# Begin Source File

SOURCE=.\ui.q3asm
# End Source File
# End Target
# End Project
