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

set(MPGameIncludeDirectories
	"${RootDir}"
	)
if(WIN32)
	set(MPGameLibraries "winmm")
endif(WIN32)
set(MPGameDefines ${MPSharedDefines} "QAGAME" )
set(MPGameGameFiles
	"${RootDir}/game/ai_main.c"
	"${RootDir}/game/ai_util.c"
	"${RootDir}/game/ai_wpnav.c"
	"${RootDir}/game/bg_gametype.c"
	"${RootDir}/game/bg_misc.c"
	"${RootDir}/game/bg_player.c"
	"${RootDir}/game/bg_pmove.c"
	"${RootDir}/game/bg_slidemove.c"
	"${RootDir}/game/bg_weapons.c"
	"${RootDir}/game/g_active.c"
	"${RootDir}/game/g_antilag.c"
	"${RootDir}/game/g_bot.c"
	"${RootDir}/game/g_client.c"
	"${RootDir}/game/g_cmds.c"
	"${RootDir}/game/g_combat.c"
	"${RootDir}/game/g_gametype.c"
	"${RootDir}/game/g_items.c"
	"${RootDir}/game/g_main.c"
	"${RootDir}/game/g_misc.c"
	"${RootDir}/game/g_missile.c"
	"${RootDir}/game/g_mover.c"
	"${RootDir}/game/g_session.c"
	"${RootDir}/game/g_spawn.c"
	"${RootDir}/game/g_svcmds.c"
	"${RootDir}/game/g_syscalls.c"
	"${RootDir}/game/g_target.c"
	"${RootDir}/game/g_team.c"
	"${RootDir}/game/g_trigger.c"
	"${RootDir}/game/g_utils.c"
	"${RootDir}/game/g_weapon.c"
	"${RootDir}/game/ai_main.h"
	"${RootDir}/game/anims.h"
	"${RootDir}/game/bg_local.h"
	"${RootDir}/game/bg_public.h"
	"${RootDir}/game/bg_weapons.h"
	"${RootDir}/game/chars.h"
	"${RootDir}/game/g_local.h"
	"${RootDir}/game/g_public.h"
	"${RootDir}/game/g_team.h"
	"${RootDir}/game/inv.h"
	"${RootDir}/game/match.h"
	"${RootDir}/game/surfaceflags.h"
	)
source_group("game" FILES ${MPGameGameFiles})
set(MPGameFiles ${MPGameFiles} ${MPGameGameFiles})

set(MPGameCommonFiles
	"${RootDir}/game/q_shared.c"
	"${RootDir}/game/q_math.c"
	"${RootDir}/qcommon/disablewarnings.h"
	"${RootDir}/game/q_shared.h"
	"${RootDir}/qcommon/tags.h"
	)
source_group("common" FILES ${MPGameCommonFiles})
set(MPGameFiles ${MPGameFiles} ${MPGameCommonFiles})

set(MPGameCgameFiles
	"${RootDir}/cgame/animtable.h"
	"${RootDir}/cgame/cg_public.h"
	)
source_group("cgame" FILES ${MPGameCgameFiles})
set(MPGameFiles ${MPGameFiles} ${MPGameCgameFiles})

set(MPGameRendererFiles
	"${RootDir}/cgame/tr_types.h"
	)
source_group("rd-common" FILES ${MPGameRendererFiles})
set(MPGameFiles ${MPGameFiles} ${MPGameRendererFiles})

set(MPGameBotlibFiles
	"${RootDir}/game/be_aas.h"
	"${RootDir}/game/be_ai_char.h"
	"${RootDir}/game/be_ai_chat.h"
	"${RootDir}/game/be_ai_gen.h"
	"${RootDir}/game/be_ai_goal.h"
	"${RootDir}/game/be_ai_move.h"
	"${RootDir}/game/be_ai_weap.h"
	"${RootDir}/game/be_ea.h"
	"${RootDir}/game/botlib.h"
	)
source_group("botlib" FILES ${MPGameBotlibFiles})
set(MPGameFiles ${MPGameFiles} ${MPGameBotlibFiles})

set(MPGameG2Files
	"${RootDir}/ghoul2/G2.h"
	"${RootDir}/ghoul2/G2_gore_shared.h"
	)
source_group("ghoul2" FILES ${MPGameG2Files})
set(MPGameFiles ${MPGameFiles} ${MPGameG2Files})

set(MPGameUiFiles
	"${RootDir}/../ui/menudef.h"
	)
source_group("ui" FILES ${MPGameUiFiles})
set(MPGameFiles ${MPGameFiles} ${MPGameUiFiles})

add_library(${MPGame} SHARED ${MPGameFiles})

if(NOT MSVC)
	# remove "lib" prefix for .so/.dylib files
	set_target_properties(${MPGame} PROPERTIES PREFIX "")
endif()

if(MakeApplicationBundles AND BuildMPEngine)
	install(TARGETS ${MPGame}
		LIBRARY
		DESTINATION "${JKAInstallDir}/${MPEngine}.app/Contents/MacOS/base"
		COMPONENT ${JKAMPCoreComponent})
elseif(WIN32)
	#if (WIN64)
		# Don't do this on 32-bit Windows to avoid overwriting
		# vanilla JKA's DLLs
		install(TARGETS ${MPGame}
			RUNTIME
			DESTINATION "base")
			#COMPONENT ${JKAMPCoreComponent})
	#endif()
else()
	install(TARGETS ${MPGame}
		LIBRARY
		DESTINATION "base")
		#COMPONENT ${JKAMPCoreComponent})
endif()

set_target_properties(${MPGame} PROPERTIES COMPILE_DEFINITIONS "${MPGameDefines}")

# Hide symbols not explicitly marked public.
set_property(TARGET ${MPGame} APPEND PROPERTY COMPILE_OPTIONS ${OPENJK_VISIBILITY_FLAGS})

set_target_properties(${MPGame} PROPERTIES INCLUDE_DIRECTORIES "${MPGameIncludeDirectories}")
set_target_properties(${MPGame} PROPERTIES PROJECT_LABEL "MP Game Library")
# no libraries used
if(MPGameLibraries)
	target_link_libraries(${MPGame} ${MPGameLibraries})
endif(MPGameLibraries)
