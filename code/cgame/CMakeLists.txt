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

set(MPCGameIncludeDirectories
	"${RootDir}"
	)
if(WIN32)
	set(MPCGameLibraries "odbc32" "odbccp32") # what are these even?
endif(WIN32)
set(MPCGameDefines ${SharedDefines} "CGAME" )
set(MPCGameGameFiles
	"${RootDir}/game/bg_gametype.c"
	"${RootDir}/game/bg_misc.c"
	"${RootDir}/game/bg_player.c"
	"${RootDir}/game/bg_pmove.c"
	"${RootDir}/game/bg_slidemove.c"
	"${RootDir}/game/bg_weapons.c"
	"${RootDir}/game/anims.h"
	"${RootDir}/game/bg_local.h"
	"${RootDir}/game/bg_public.h"
	"${RootDir}/game/bg_weapons.h"
	"${RootDir}/game/surfaceflags.h"
	)
source_group("game" FILES ${MPCGameGameFiles})
set(MPCGameFiles ${MPCGameFiles} ${MPCGameGameFiles})

set(MPCGameCgameFiles
	"${RootDir}/cgame/cg_consolecmds.c"
	#"${RootDir}/cgame/cg_cvar.c"
	"${RootDir}/cgame/cg_draw.c"
	"${RootDir}/cgame/cg_drawtools.c"
	"${RootDir}/cgame/cg_effects.c"
	"${RootDir}/cgame/cg_ents.c"
	"${RootDir}/cgame/cg_event.c"
	"${RootDir}/cgame/cg_gametype.c"
	"${RootDir}/cgame/cg_gore.c"
	"${RootDir}/cgame/cg_info.c"
	"${RootDir}/cgame/cg_light.c"
	"${RootDir}/cgame/cg_lights.h"
	"${RootDir}/cgame/cg_localents.c"
	"${RootDir}/cgame/cg_main.c"
	"${RootDir}/cgame/cg_miscents.c"
	#"${RootDir}/cgame/cg_marks.c"
	"${RootDir}/cgame/cg_newDraw.c"
	"${RootDir}/cgame/cg_players.c"
	"${RootDir}/cgame/cg_playerstate.c"
	"${RootDir}/cgame/cg_predict.c"
	"${RootDir}/cgame/cg_scoreboard.c"
	"${RootDir}/cgame/cg_servercmds.c"
	"${RootDir}/cgame/cg_snapshot.c"
	#"${RootDir}/cgame/cg_spawn.c"
	"${RootDir}/cgame/cg_syscalls.c"
	"${RootDir}/cgame/cg_view.c"
	"${RootDir}/cgame/cg_weaponinit.c"
	"${RootDir}/cgame/cg_weapons.c"
	"${RootDir}/cgame/animtable.h"
	"${RootDir}/cgame/cg_local.h"
	"${RootDir}/cgame/cg_public.h"
	)
source_group("cgame" FILES ${MPCGameCgameFiles})
set(MPCGameFiles ${MPCGameFiles} ${MPCGameCgameFiles})

set(MPCGameCommonFiles
	"${RootDir}/game/q_shared.c"
	"${RootDir}/game/q_math.c"
	"${RootDir}/qcommon/disablewarnings.h"
	"${RootDir}/game/q_shared.h"
	#"${RootDir}/qcommon/qfiles.h"
	"${RootDir}/qcommon/tags.h"
	)
source_group("common" FILES ${MPCGameCommonFiles})
set(MPCGameFiles ${MPCGameFiles} ${MPCGameCommonFiles})

set(MPCGameUiFiles
	"${RootDir}/ui/ui_shared.c"
	"${RootDir}/ui/keycodes.h"
	"${RootDir}/../ui/menudef.h"
	"${RootDir}/ui/ui_shared.h"
	)
source_group("ui" FILES ${MPCGameUiFiles})
set(MPCGameFiles ${MPCGameFiles} ${MPCGameUiFiles})

set(MPCGameRendererFiles
	"${RootDir}/cgame/tr_types.h"
	)
source_group("rd-common" FILES ${MPCGameRendererFiles})
set(MPCGameFiles ${MPCGameFiles} ${MPCGameRendererFiles})

set(MPCGameGFiles
	"${RootDir}/ghoul2/G2.h"
	"${RootDir}/ghoul2/G2_gore_shared.h"
	)
source_group("ghoul2" FILES ${MPCGameG2Files})
set(MPCGameFiles ${MPCGameFiles} ${MPCGameG2Files})

add_library(${MPCGame} SHARED ${MPCGameFiles})

if(NOT MSVC)
	# remove "lib" prefix for .so/.dylib files
	set_target_properties(${MPCGame} PROPERTIES PREFIX "")
endif()

if(MakeApplicationBundles AND BuildMPEngine)
	install(TARGETS ${MPCGame}
		LIBRARY
		DESTINATION "${JKAInstallDir}/${MPEngine}.app/Contents/MacOS/base"
		COMPONENT ${JKAMPCoreComponent})
elseif(WIN32)
	#if (WIN64)
		# Don't do this on 32-bit Windows to avoid overwriting
		# vanilla JKA's DLLs
		install(TARGETS ${MPCGame}
			RUNTIME
			DESTINATION "base")
			#COMPONENT ${JKAMPCoreComponent})
	#endif()
else()
	install(TARGETS ${MPCGame}
		LIBRARY
		DESTINATION "base")
		#COMPONENT ${JKAMPCoreComponent})
endif()

set_target_properties(${MPCGame} PROPERTIES COMPILE_DEFINITIONS "${MPCGameDefines}")

# Hide symbols not explicitly marked public.
set_property(TARGET ${MPCGame} APPEND PROPERTY COMPILE_OPTIONS ${OPENJK_VISIBILITY_FLAGS})

set_target_properties(${MPCGame} PROPERTIES INCLUDE_DIRECTORIES "${MPCGameIncludeDirectories}")
set_target_properties(${MPCGame} PROPERTIES PROJECT_LABEL "MP Client Game Library")
# no libraries used
if(MPCGameLibraries)
	target_link_libraries(${MPCGame} ${MPCGameLibraries})
endif(MPCGameLibraries)
