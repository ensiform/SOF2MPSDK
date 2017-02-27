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

set(GTCTF "gt_ctf${Architecture}")
set(GTDEM "gt_dem${Architecture}")
set(GTDM "gt_dm${Architecture}")
set(GTELIM "gt_elim${Architecture}")
set(GTINF "gt_inf${Architecture}")
set(GTTDM "gt_tdm${Architecture}")

set(MPGameTypeIncludeDirectories
	"${RootDir}"
	)
if(WIN32)
	set(MPGameTypeLibraries "winmm")
endif(WIN32)
set(MPGameTypeDefines ${MPSharedDefines} )
set(MPGameTypeSharedFiles
	"${RootDir}/gametype/gt_syscalls.c"
	"${RootDir}/gametype/gt_syscalls.h"
	"${RootDir}/gametype/gt_public.h"
	)
source_group("gametype" FILES ${MPGameTypeSharedFiles})
set(MPGameTypeFiles ${MPGameTypeFiles} ${MPGameTypeSharedFiles})

set(MPGameTypeCommonFiles
	"${RootDir}/game/q_shared.c"
	"${RootDir}/game/q_math.c"
	"${RootDir}/qcommon/disablewarnings.h"
	"${RootDir}/game/q_shared.h"
	"${RootDir}/qcommon/tags.h"
	)
source_group("common" FILES ${MPGameTypeCommonFiles})
set(MPGameTypeFiles ${MPGameTypeFiles} ${MPGameTypeCommonFiles})

function(add_gt_project BinaryName Label GT_Files)
	set(GT_Local_Files ${MPGameTypeFiles} ${GT_Files})
	add_library(${BinaryName} SHARED ${GT_Local_Files})

	if(NOT MSVC)
		# remove "lib" prefix for .so/.dylib files
		set_target_properties(${BinaryName} PROPERTIES PREFIX "")
	endif()

	if(MakeApplicationBundles)
		install(TARGETS ${BinaryName}
			LIBRARY
			DESTINATION "${JKAInstallDir}/${MPEngine}.app/Contents/MacOS/base"
			COMPONENT ${JKAMPCoreComponent})
	elseif(WIN32)
		#if (WIN64)
			# Don't do this on 32-bit Windows to avoid overwriting
			# vanilla JKA's DLLs
			install(TARGETS ${BinaryName}
				RUNTIME
				DESTINATION "base")
				#COMPONENT ${JKAMPCoreComponent})
		#endif()
	else()
		install(TARGETS ${BinaryName}
			LIBRARY
			DESTINATION "base")
			#COMPONENT ${JKAMPCoreComponent})
	endif()

	set_target_properties(${BinaryName} PROPERTIES COMPILE_DEFINITIONS "${MPGameTypeDefines}")

	# Hide symbols not explicitly marked public.
	set_property(TARGET ${BinaryName} APPEND PROPERTY COMPILE_OPTIONS ${OPENJK_VISIBILITY_FLAGS})

	set_target_properties(${BinaryName} PROPERTIES INCLUDE_DIRECTORIES "${MPGameTypeIncludeDirectories}")
	set_target_properties(${BinaryName} PROPERTIES PROJECT_LABEL ${Label})
	# no libraries used
	if(MPGameTypeLibraries)
		target_link_libraries(${BinaryName} ${MPGameTypeLibraries})
	endif(MPGameTypeLibraries)
endfunction(add_gt_project)

set(CTF_Files
	"${RootDir}/gametype/gt_ctf/gt_main.c"
	"${RootDir}/gametype/gt_ctf/gt_local.h"
	)
source_group("gt_ctf" FILES ${CTF_Files})

set(DEM_Files
	"${RootDir}/gametype/gt_dem/gt_main.c"
	"${RootDir}/gametype/gt_dem/gt_local.h"
	)
source_group("gt_dem" FILES ${DEM_Files})

set(DM_Files
	"${RootDir}/gametype/gt_dm/gt_main.c"
	"${RootDir}/gametype/gt_dm/gt_local.h"
	)
source_group("gt_dm" FILES ${DM_Files})

set(ELIM_Files
	"${RootDir}/gametype/gt_elim/gt_main.c"
	"${RootDir}/gametype/gt_elim/gt_local.h"
	)
source_group("gt_elim" FILES ${ELIM_Files})

set(INF_Files
	"${RootDir}/gametype/gt_inf/gt_main.c"
	"${RootDir}/gametype/gt_inf/gt_local.h"
	)
source_group("gt_inf" FILES ${INF_Files})

set(TDM_Files
	"${RootDir}/gametype/gt_tdm/gt_main.c"
	"${RootDir}/gametype/gt_tdm/gt_local.h"
	)
source_group("gt_tdm" FILES ${TDM_Files})

add_gt_project(${GTCTF} "gt_ctf" ${CTF_Files})
add_gt_project(${GTDEM} "gt_dem" ${DEM_Files})
add_gt_project(${GTDM} "gt_dm" ${DM_Files})
add_gt_project(${GTELIM} "gt_elim" ${ELIM_Files})
add_gt_project(${GTINF} "gt_inf" ${INF_Files})
add_gt_project(${GTTDM} "gt_tdm" ${TDM_Files})


