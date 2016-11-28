===========================================================================
Title                   : Unofficial SOF2 1.03 MP Source Code *Final*
Date                    : 22/06/03
Version			: 1.0
Filename/s              : sof2_103src2.zip
Author                  : Arkanis
Email                   : arkanis50@yahoo.com

Description             : *** The original release was missing some code which disables
			  the banned weapons in the outfitting menu. This has been 
			  included in this final version. ***

			  For those people who have been asking for the 1.03 MP
			  source code for Soldier Of Fortune 2, you can now download
			  some UNOFFICIAL 1.03 source code for use. THIS IS FILE IS NOT
			  OFFICIALLY FROM RAVEN AND THUS NOT ENDORSED BY RAVEN.

			  Raven promised us that a new 1.03 SDK would be available
			  sometime in March 2003, of course this never eventuated.
			  Since people often ask about being able to download the
			  1.03 source code, I have provided some 1.03 base code I use
			  in my mods for public use. This code is 1.02 code which has 
			  been updated with the 1.03 code changes which were given to
			  us by Raven. A full list of changes can be found in this readme.

			  To the best of my knowledge this code is 100% correct, and is an
			  almost perfect representation of the Raven 1.03 code. The only
			  additions to the code have been to fix a gametype problem 
			  introduced by 1.03. Although don't blame me if something crops
			  up later is doesn't work - use at your own risk.

			  I have also included a tutorial by Sevensins in Word format with
			  the code - this tute is handy for those who are having troubles 
			  setting the compiler up.

			  I accept no responsibility for damage to data, or physical damage 
			  to hardware, caused by the appropriate or inappropriate use of 
			  this code. It is deemed that users who attempt to use this code, 
			  are automatically considered as having read and understood this 			  	  liability clause before using the said code.


===========================================================================
*Code Changes*

If you are using Microsoft Visual C++ or a similar IDE, search for the words
"1.03 CHANGE" and you will find all the commented code changes.

There are 6 sections where code changes have occured:

bg_public.h, line 45 - version number changed
g_main.c, line 172 - Renamed availableWeapons Cvar which might confuse old map cycles
g_main.c, line (484 - 486) - Cvar update for g_availableWeapons made
g_main.c, line (501 - 505) - (unofficial) Fix for base gametype issue
ui_gameinfo.c, line (156 - 157) - (unofficial) Fix for base gametype issue
cg_servercmds.c, line (109 - 110) - (unofficial) fix for disabled weapons showing up in outfitting


Not a great deal of code changes.

===========================================================================
*Instructions*

Backup your old 1.02 code to a new folder and extract this code into your
SOF2SDK directory with directory structure intact- overwrite any old files.
			  

===========================================================================
*Credits*

ReverendTed, Arkule, XMC, godH, slowJusko, Xena, Sevensins etc on the Raven forums

===========================================================================
* Permissions*

All original and composed textures, assets and intellectual property in this tutorial remain 
property of the sources respective owners.

You MAY distribute this tutorial in any not-for-profit electronic format (BBS, Internet,
CD, etc) as long as you contact the author first, and include all files, including this ReadMe 
(readme.txt), intact in the original archive.

You MAY NOT include or distribute this tutorial in any sort of commercial product without 
permission from the author.  If given permission in writing, you must include all files, including this ReadMe (readme.txt), intact in the original archive.

You MAY NOT mass distribute this mod via any non-internet means, including but not limited to, 
compact disks, and floppy disks without permission from the author. If given permission in 
writing, you must include all files, including this ReadMe (readme.txt), intact in the original 
archive.

===========================================================================
* Warning - Must Read and Understand Before Use*

The author/s of this tutorial accept no responsibility for damage to data, or physical damage 
to hardware, caused by the appropriate or inappropriate use of the information in this tutorial. It is deemed that users who attempt to follow this tutorial, are automatically considered as having read and understood this liability clause before attempting the said tutorial.


===========================================================================
