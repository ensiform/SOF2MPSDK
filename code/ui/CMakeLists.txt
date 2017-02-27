#============================================================================
# Copyright (C) 2013 - 2015, OpenJK contributors
#
# This file is part of the OpenJK source code.
#
# OpenJK is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License version 2 as
# published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, see <http://www.gnu.org/licenses/>.
#============================================================================

# Make sure the user is not executing this script directly
if(NOT InOpenJK)
	message(FATAL_ERROR "Use the top-level cmake script!")
endif(NOT InOpenJK)

set(MPUIIncludeDirectories
	"${RootDir}"
	)
if(WIN32)
	set(MPUILibraries "odbc32" "odbccp32") # what are these even?
endif(WIN32)
set(MPUIDefines ${MPSharedDefines} "UI_EXPORTS" "MISSIONPACK")

set(MPUIGameFiles
	"${RootDir}/game/bg_gametype.c"
	"${RootDir}/game/bg_misc.c"
	"${RootDir}/game/bg_player.c"
	"${RootDir}/game/bg_weapons.c"
	"${RootDir}/game/anims.h"
	"${RootDir}/game/bg_local.h"
	"${RootDir}/game/bg_public.h"
	"${RootDir}/game/bg_weapons.h"
	"${RootDir}/game/surfaceflags.h"
	)
source_group("game" FILES ${MPUIGameFiles})
set(MPUIFiles ${MPUIFiles} ${MPUIGameFiles})

set(MPUICommonFiles
	"${RootDir}/game/q_shared.c"
	"${RootDir}/game/q_math.c"
	"${RootDir}/qcommon/disablewarnings.h"
	#"${RootDir}/qcommon/game_version.h"
	"${RootDir}/game/q_shared.h"
	#"${RootDir}/qcommon/qfiles.h"
	"${RootDir}/qcommon/tags.h"
	)
source_group("common" FILES ${MPUICommonFiles})
set(MPUIFiles ${MPUIFiles} ${MPUICommonFiles})

set(MPUIUIFiles
	"${RootDir}/ui/ui_atoms.c"
	#"${RootDir}/ui/ui_cvar.c"
	"${RootDir}/ui/ui_gameinfo.c"
	"${RootDir}/ui/ui_main.c"
	"${RootDir}/ui/ui_players.c"
	"${RootDir}/ui/ui_shared.c"
	"${RootDir}/ui/ui_syscalls.c"
	"${RootDir}/ui/keycodes.h"
	"${RootDir}/../ui/menudef.h"
	"${RootDir}/ui/ui_local.h"
	"${RootDir}/ui/ui_public.h"
	"${RootDir}/ui/ui_shared.h"
	)
source_group("ui" FILES ${MPUIUIFiles})
set(MPUIFiles ${MPUIFiles} ${MPUIUIFiles})

set(MPUIRendererFiles
	"${RootDir}/cgame/tr_types.h"
	)
source_group("rd-common" FILES ${MPUIRendererFiles})
set(MPUIFiles ${MPUIFiles} ${MPUIRendererFiles})

add_library(${MPUI} SHARED ${MPUIFiles})

if(NOT MSVC)
	# remove "lib" prefix for .so/.dylib files
	set_target_properties(${MPUI} PROPERTIES PREFIX "")
endif()

if(MakeApplicationBundles AND BuildMPEngine)
	install(TARGETS ${MPUI}
		LIBRARY
		DESTINATION "${JKAInstallDir}/${MPEngine}.app/Contents/MacOS/base"
		COMPONENT ${JKAMPCoreComponent})
elseif(WIN32)
	#if (WIN64)
		# Don't do this on 32-bit Windows to avoid overwriting
		# vanilla JKA's DLLs
		install(TARGETS ${MPUI}
			RUNTIME
			DESTINATION "base")
			#COMPONENT ${JKAMPCoreComponent})
	#endif()
else()
	install(TARGETS ${MPUI}
		LIBRARY
		DESTINATION "base")
		#COMPONENT ${JKAMPCoreComponent})
endif()

set_target_properties(${MPUI} PROPERTIES COMPILE_DEFINITIONS "${MPUIDefines}")

# Hide symbols not explicitly marked public.
set_property(TARGET ${MPUI} APPEND PROPERTY COMPILE_OPTIONS ${OPENJK_VISIBILITY_FLAGS})

set_target_properties(${MPUI} PROPERTIES INCLUDE_DIRECTORIES "${MPUIIncludeDirectories}")
set_target_properties(${MPUI} PROPERTIES PROJECT_LABEL "MP UI Library")
# no libraries used
if(MPUILibraries)
	target_link_libraries(${MPUI} ${MPUILibraries})
endif(MPUILibraries)
