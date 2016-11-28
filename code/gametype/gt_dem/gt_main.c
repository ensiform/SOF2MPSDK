// Copyright (C) 2001-2002 Raven Software.
//

#include "gt_local.h"

							
#define TRIGGER_DEMOSITE_1		200
#define TRIGGER_DEMOSITE_2		201

#define ITEM_BOMB				300
#define ITEM_PLANTED_BOMB		301

void	GT_Init		( void );
void	GT_RunFrame	( int time );
int		GT_Event	( int cmd, int time, int arg0, int arg1, int arg2, int arg3, int arg4 );

gametypeLocals_t	gametype;

typedef struct 
{
	vmCvar_t	*vmCvar;
	char		*cvarName;
	char		*defaultString;
	int			cvarFlags;
	float		mMinValue, mMaxValue;
	int			modificationCount;  // for tracking changes
	qboolean	trackChange;	    // track this variable, and announce if changed
	qboolean	teamShader;			// track and if changed, update shader state

} cvarTable_t;

vmCvar_t	gt_bombFuseTime;
vmCvar_t	gt_bombDefuseTime;
vmCvar_t	gt_bombPlantTime;
vmCvar_t	gt_simpleScoring;

static cvarTable_t gametypeCvarTable[] = 
{
	// don't override the cheat state set by the system
	{ &gt_bombFuseTime,		"gt_bombFuseTime",		"30", CVAR_ARCHIVE, 0.0f, 0.0f, 0, qfalse },
	{ &gt_bombDefuseTime,	"gt_bombDefuseTime",	"3",  CVAR_ARCHIVE|CVAR_LATCH, 0.0f, 0.0f, 0, qfalse },
	{ &gt_bombPlantTime,	"gt_bombPlantTime",		"3",  CVAR_ARCHIVE|CVAR_LATCH, 0.0f, 0.0f, 0, qfalse },
	{ &gt_simpleScoring,	"gt_simpleScoring",		"0",  CVAR_ARCHIVE, 0.0f, 0.0f, 0, qfalse },
	{ NULL, NULL, NULL, 0, 0.0f, 0.0f, 0, qfalse },
};

static int gametypeCvarTableSize = sizeof( gametypeCvarTable ) / sizeof( gametypeCvarTable[0] );

/*
================
vmMain

This is the only way control passes into the module.
This must be the very first function compiled into the .q3vm file
================
*/
int vmMain( int command, int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9, int arg10, int arg11 ) 
{
	switch ( command ) 
	{
		case GAMETYPE_INIT:
			GT_Init ( );
			return 0;

		case GAMETYPE_START:
			gametype.firstFrame    = qtrue;
			gametype.bombPlantTime = 0;
			gametype.bombBeepTime  = 0;
			gametype.roundOver     = qfalse;
			trap_Cmd_SetHUDIcon ( 0, 0 );
			return 0;

		case GAMETYPE_RUN_FRAME:
			GT_RunFrame ( arg0 );
			return 0;

		case GAMETYPE_EVENT:
			return GT_Event ( arg0, arg1, arg2, arg3, arg4, arg5, arg6 );
	}

	return -1;
}

/*
=================
GT_RegisterCvars
=================
*/
void GT_RegisterCvars( void ) 
{
	cvarTable_t	*cv;

	for ( cv = gametypeCvarTable ; cv->cvarName != NULL; cv++ ) 
	{
		trap_Cvar_Register( cv->vmCvar, cv->cvarName, cv->defaultString, cv->cvarFlags, cv->mMinValue, cv->mMaxValue );
		
		if ( cv->vmCvar )
		{
			cv->modificationCount = cv->vmCvar->modificationCount;
		}
	}
}

/*
=================
GT_UpdateCvars
=================
*/
void GT_UpdateCvars( void ) 
{
	cvarTable_t	*cv;

	for ( cv = gametypeCvarTable ; cv->cvarName != NULL; cv++ ) 
	{
		if ( cv->vmCvar ) 
		{
			trap_Cvar_Update( cv->vmCvar );

			if ( cv->modificationCount != cv->vmCvar->modificationCount ) 
			{
				cv->modificationCount = cv->vmCvar->modificationCount;
			}
		}
	}
}

/*
================
GT_Init

initializes the gametype by spawning the gametype items and 
preparing them
================
*/
void GT_Init ( void )
{
	gtTriggerDef_t	triggerDef;
	gtItemDef_t		itemDef;

	memset ( &gametype, 0, sizeof(gametype) );

	// Register all cvars for this gametype
	GT_RegisterCvars ( );

	gametype.bombTakenSound    = trap_Cmd_RegisterSound ( "sound/ctf_flag.mp3" );
	gametype.bombExplodedSound = trap_Cmd_RegisterSound ( "sound/ctf_win.mp3" );
	gametype.bombPlantedSound  = trap_Cmd_RegisterSound ( "sound/ctf_base.mp3" );

	gametype.bombExplodeEffect = trap_Cmd_RegisterEffect ( "explosions/mushroom_explosion.efx" );
	gametype.bombBeepSound	   = trap_Cmd_RegisterSound ( "sound/misc/c4/beep" );

	// Register the triggers
	memset ( &triggerDef, 0, sizeof(triggerDef) );
	triggerDef.size		= sizeof(triggerDef);
	triggerDef.use		= qtrue;
	triggerDef.useTime	= gt_bombPlantTime.integer * 1000;
	triggerDef.useIcon	= trap_Cmd_RegisterIcon ( "gfx/menus/hud/tnt" );
	triggerDef.useSound = trap_Cmd_RegisterSound ( "sound/misc/c4/c4_loop" );
	trap_Cmd_RegisterTrigger ( TRIGGER_DEMOSITE_1, "demolition_site_1", &triggerDef );
	trap_Cmd_RegisterTrigger ( TRIGGER_DEMOSITE_2, "demolition_site_2", &triggerDef );

	memset ( &itemDef, 0, sizeof(itemDef) );
	itemDef.size = sizeof(itemDef);
	trap_Cmd_RegisterItem ( ITEM_BOMB, "c4", &itemDef );

	itemDef.use = qtrue;
	itemDef.useTime = gt_bombDefuseTime.integer * 1000;
	itemDef.useSound = triggerDef.useSound;
	itemDef.useIcon	= trap_Cmd_RegisterIcon ( "gfx/menus/hud/wire_cutters" );
	trap_Cmd_RegisterItem ( ITEM_PLANTED_BOMB, "armed_c4", &itemDef );

	gametype.iconBombPlanted[0] = trap_Cmd_RegisterIcon ( "gfx/menus/hud/dem_planted" );
	gametype.iconBombPlanted[1] = trap_Cmd_RegisterIcon ( "gfx/menus/hud/dem_planted1" );
	gametype.iconBombPlanted[2] = trap_Cmd_RegisterIcon ( "gfx/menus/hud/dem_planted2" );
	gametype.iconBombPlanted[3] = trap_Cmd_RegisterIcon ( "gfx/menus/hud/dem_planted3" );
	gametype.iconBombPlanted[4] = trap_Cmd_RegisterIcon ( "gfx/menus/hud/dem_planted4" );
	gametype.iconBombPlanted[5] = trap_Cmd_RegisterIcon ( "gfx/menus/hud/dem_planted5" );
	gametype.iconBombPlanted[6] = trap_Cmd_RegisterIcon ( "gfx/menus/hud/dem_planted6" );
}

/*
================
GT_RunFrame

Runs all thinking code for gametype
================
*/
void GT_RunFrame ( int time )
{
	gametype.time = time;

	if ( gametype.firstFrame )
	{
		int clients[MAX_CLIENTS];
		int count;

		count = trap_Cmd_GetClientList ( TEAM_BLUE, clients, 64 );

		if ( count )
		{
			gametype.bombGiveClient = gametype.bombGiveClient % count;

			trap_Cmd_GiveClientItem ( clients[gametype.bombGiveClient], ITEM_BOMB );
			gametype.firstFrame = qfalse;

			// Next time use the next client in the list
			gametype.bombGiveClient = (gametype.bombGiveClient + 1 ) % count;
		}
	}

	if ( gametype.bombPlantTime )
	{
		static const int slowTime = 1000;
		static const int fastTime = 100;

		if ( !gametype.bombBeepTime || gametype.time > gametype.bombBeepTime ) 
		{
			float addTime;

			addTime = (float)(gametype.bombPlantTime - gametype.time) / (float)(gt_bombFuseTime.integer * 1000);
			addTime = fastTime + (addTime * (float)(slowTime - fastTime) );

			gametype.bombBeepTime = gametype.time + (int)addTime;

			trap_Cmd_StartSound ( gametype.bombBeepSound, gametype.bombPlantOrigin );

			addTime = (float)(gametype.bombPlantTime - gametype.time) / (float)(gt_bombFuseTime.integer * 1000);
			addTime = 6.0f - 6.0f * addTime ;
			trap_Cmd_SetHUDIcon ( 0, gametype.iconBombPlanted[ Com_Clamp ( 0, 6, (int)addTime ) ] );
		}
	}

	if ( gametype.bombPlantTime && gametype.time > gametype.bombPlantTime )
	{
		static vec3_t up = {0,0,1};
		int clients[MAX_CLIENTS];
		int count;

		trap_Cmd_PlayEffect ( gametype.bombExplodeEffect, gametype.bombPlantOrigin, up );
		trap_Cmd_UseTargets ( gametype.bombPlantTarget );
		trap_Cmd_ResetItem ( ITEM_PLANTED_BOMB );

		if ( !gametype.roundOver )
		{
			trap_Cmd_AddTeamScore ( TEAM_BLUE, 1 );
			trap_Cmd_TextMessage ( -1, "Blue team has destroyed the target!" );
			trap_Cmd_StartGlobalSound ( gametype.bombExplodedSound );
			trap_Cmd_Restart ( 5 );

			// Give the guy who planted it some props
			if ( !gt_simpleScoring.integer )
			{
				trap_Cmd_AddClientScore ( gametype.bombPlantClient, 10 );
			}
		}

		gametype.bombPlantTime = 0;

		// Get the bomb client # so we can give the bomb to the same guy again
		count = trap_Cmd_GetClientList ( TEAM_BLUE, clients, 64 );
		if ( count )
		{
			for ( count--; count >= 0; count-- )
			{
				if ( clients[count] == gametype.bombPlantClient )
				{
					gametype.bombGiveClient = count;
					break;
				}
			}
		}

		gametype.roundOver = qtrue;
	}

	GT_UpdateCvars ( );
}

/*
================
GT_Event

Handles all events sent to the gametype
================
*/
int GT_Event ( int cmd, int time, int arg0, int arg1, int arg2, int arg3, int arg4 )
{
	switch ( cmd )
	{
		case GTEV_ITEM_DEFEND:
			if ( !gt_simpleScoring.integer )
			{
				trap_Cmd_AddClientScore ( arg1, 5 );
			}
			return 0;

		case GTEV_ITEM_STUCK:
			break;

		case GTEV_ITEM_DROPPED:
		{
			char clientname[MAX_QPATH];
			trap_Cmd_GetClientName ( arg1, clientname, MAX_QPATH );
			trap_Cmd_TextMessage ( -1, va("%s has dropped the bomb!", clientname ) );
			break;
		}

		case GTEV_ITEM_TOUCHED:			
			if ( arg0 == ITEM_BOMB && arg2 == TEAM_BLUE )
			{
				char clientname[MAX_QPATH];
				trap_Cmd_GetClientName ( arg1, clientname, MAX_QPATH );
				trap_Cmd_TextMessage ( -1, va("%s has taken the bomb!", clientname ) );
				trap_Cmd_StartGlobalSound ( gametype.bombTakenSound );
				trap_Cmd_RadioMessage ( arg1, "got_it" );
				return 1;
			}

			return 0;

		case GTEV_ITEM_CANBEUSED:
			if ( arg0 == ITEM_PLANTED_BOMB && arg2 == TEAM_RED )
			{
				return 1;
			}
			return 0;

		case GTEV_TRIGGER_TOUCHED:
			return 0;

		case GTEV_TRIGGER_CANBEUSED:
			if ( trap_Cmd_DoesClientHaveItem ( arg1, ITEM_BOMB ) )
			{
				return 1;
			}
			return 0;			

		case GTEV_TIME_EXPIRED:
			trap_Cmd_TextMessage ( -1, "Red team has defended the bomb site!" );
			trap_Cmd_AddTeamScore ( TEAM_RED, 1 );
			trap_Cmd_Restart ( 5 );
			gametype.roundOver = qtrue;
			break;

		case GTEV_TEAM_ELIMINATED:
			switch ( arg0 )
			{
				case TEAM_RED:
					trap_Cmd_TextMessage ( -1, "Red team eliminated!" );
					trap_Cmd_AddTeamScore ( TEAM_BLUE, 1 );
					trap_Cmd_Restart ( 5 );
					gametype.roundOver = qtrue;
					break;

				case TEAM_BLUE:

					// If the bomb is planted the defending team MUST defuse it.
					if ( !gametype.bombPlantTime )
					{
						trap_Cmd_TextMessage ( -1, "Blue team eliminated!" );
						trap_Cmd_AddTeamScore ( TEAM_RED, 1 );
						trap_Cmd_Restart ( 5 );
						gametype.roundOver = qtrue;
					}
					break;
			}
			break;

		case GTEV_ITEM_USED:
		{
			char	name[128];
			trap_Cmd_ResetItem ( ITEM_PLANTED_BOMB );
			gametype.bombPlantTime = 0;
			gametype.bombBeepTime = 0;
			trap_Cmd_AddTeamScore ( TEAM_RED, 1 );
			trap_Cmd_GetClientName ( arg1, name, 128 );
			trap_Cmd_TextMessage ( -1, va("%s has defused the bomb!", name ) );
			trap_Cmd_StartGlobalSound ( gametype.bombExplodedSound );
			trap_Cmd_Restart ( 5 );
			gametype.roundOver = qtrue;

			// Give the guy who defused it some props
			if ( !gt_simpleScoring.integer )
			{
				trap_Cmd_AddClientScore ( arg1, 10 );
			}

			return 1;
		}

		case GTEV_TRIGGER_USED:
		{
			char	name[128];
			
			gametype.bombPlantTime = time + gt_bombFuseTime.integer * 1000;
			gametype.bombPlantClient = arg1;
			trap_Cmd_GetClientOrigin ( arg1, gametype.bombPlantOrigin );
			trap_Cmd_TakeClientItem ( arg1, ITEM_BOMB );
			trap_Cmd_SpawnItem ( ITEM_PLANTED_BOMB, gametype.bombPlantOrigin, vec3_origin );
			trap_Cmd_GetClientName ( arg1, name, 128 );
			trap_Cmd_TextMessage ( -1, va("%s has planted the bomb!", name ) );
			trap_Cmd_GetTriggerTarget ( arg0, gametype.bombPlantTarget, sizeof(gametype.bombPlantTarget) );
			trap_Cmd_SetHUDIcon ( 0, gametype.iconBombPlanted[0] );
			trap_Cmd_StartGlobalSound ( gametype.bombPlantedSound );
			return 0;
		}
	}

	return 0;
}

#ifndef GAMETYPE_HARD_LINKED
// this is only here so the functions in q_shared.c and bg_*.c can link (FIXME)

void QDECL Com_Error( int level, const char *msg, ... ) 
{
	va_list		argptr;
	char		text[1024];

	va_start (argptr, msg);
	vsprintf (text, msg, argptr);
	va_end (argptr);

	trap_Error( text );
}

void QDECL Com_Printf( const char *msg, ... ) 
{
	va_list		argptr;
	char		text[1024];

	va_start (argptr, msg);
	vsprintf (text, msg, argptr);
	va_end (argptr);

	trap_Print( text );
}

#endif
