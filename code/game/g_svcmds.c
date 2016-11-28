// Copyright (C) 2001-2002 Raven Software
//

// this file holds commands that can be executed by the server console, but not remote clients

#include "g_local.h"

char	*ConcatArgs( int start );

/*
===================
Svcmd_EntityList_f
===================
*/
void	Svcmd_EntityList_f (void) {
	int			e;
	gentity_t		*check;

	check = g_entities+1;
	for (e = 1; e < level.num_entities ; e++, check++) {
		if ( !check->inuse ) {
			continue;
		}
		Com_Printf("%3i:", e);
		switch ( check->s.eType ) {
		case ET_GENERAL:
			Com_Printf("ET_GENERAL          ");
			break;
		case ET_PLAYER:
			Com_Printf("ET_PLAYER           ");
			break;
		case ET_ITEM:
			Com_Printf("ET_ITEM             ");
			break;
		case ET_MISSILE:
			Com_Printf("ET_MISSILE          ");
			break;
		case ET_MOVER:
			Com_Printf("ET_MOVER            ");
			break;
		case ET_BEAM:
			Com_Printf("ET_BEAM             ");
			break;
		case ET_PORTAL:
			Com_Printf("ET_PORTAL           ");
			break;
		case ET_SPEAKER:
			Com_Printf("ET_SPEAKER          ");
			break;
		case ET_PUSH_TRIGGER:
			Com_Printf("ET_PUSH_TRIGGER     ");
			break;
		case ET_TELEPORT_TRIGGER:
			Com_Printf("ET_TELEPORT_TRIGGER ");
			break;
		case ET_INVISIBLE:
			Com_Printf("ET_INVISIBLE        ");
			break;
		case ET_GRAPPLE:
			Com_Printf("ET_GRAPPLE          ");
			break;
		default:
			Com_Printf("%3i                 ", check->s.eType);
			break;
		}

		if ( check->classname ) {
			Com_Printf("%s", check->classname);
		}
		Com_Printf("\n");
	}
}


void Svcmd_ExtendTime_f (void) 
{
	char str[MAX_TOKEN_CHARS];
	int	 time;

	if ( trap_Argc() < 2 ) 
	{
		Com_Printf("Usage:  extendtime <minutes>\n");
		return;
	}

	trap_Argv( 1, str, sizeof( str ) );

	time = atoi(str);
	level.timeExtension += time;

	G_LogPrintf ( "timelimit extended by %d minutes\n", time );

	trap_SendServerCommand( -1, va("print \"timelimit extended by %d minutes\n\"", time) );
}

void Svcmd_AutoKickList_f ( void )
{
	int i;

	for ( i = 0; i < level.autokickedCount; i ++ )
	{
		Com_Printf ( "%16s - %s\n", level.autokickedIP[i], level.autokickedName[i] );
	}
}

void Svcmd_Mute_f ( void )
{
	char str[MAX_TOKEN_CHARS];
	int	 clientnum;

	if ( trap_Argc() < 2 ) 
	{
		Com_Printf("Usage:  mute <clientid>\n");
		return;
	}
	
	trap_Argv( 1, str, sizeof( str ) );
	clientnum = atoi ( str );

	if ( clientnum < 0 || clientnum > MAX_CLIENTS )
	{
		Com_Printf("invalid client id\n");
		return;
	}

	if ( level.clients[clientnum].pers.connected != CON_CONNECTED )
	{
		Com_Printf("no client connected with that client id\n" );
		return;
	}

	level.clients[clientnum].sess.muted = level.clients[clientnum].sess.muted ? qfalse : qtrue;

	if ( level.clients[clientnum].sess.muted )
	{
		Com_Printf("client %d muted\n", clientnum );
	}
	else
	{
		Com_Printf("client %d unmuted\n", clientnum );
	}	
}

gclient_t	*ClientForString( const char *s ) {
	gclient_t	*cl;
	int			i;
	int			idnum;

	// numeric values are just slot numbers
	if ( s[0] >= '0' && s[0] <= '9' ) {
		idnum = atoi( s );
		if ( idnum < 0 || idnum >= level.maxclients ) {
			Com_Printf( "Bad client slot: %i\n", idnum );
			return NULL;
		}

		cl = &level.clients[idnum];
		if ( cl->pers.connected == CON_DISCONNECTED ) {
			Com_Printf( "Client %i is not connected\n", idnum );
			return NULL;
		}
		return cl;
	}

	// check for a name match
	for ( i=0 ; i < level.maxclients ; i++ ) {
		cl = &level.clients[i];
		if ( cl->pers.connected == CON_DISCONNECTED ) {
			continue;
		}
		if ( !Q_stricmp( cl->pers.netname, s ) ) {
			return cl;
		}
	}

	Com_Printf( "User %s is not on the server\n", s );

	return NULL;
}

/*
===================
Svcmd_ForceTeam_f

forceteam <player> <team>
===================
*/
void Svcmd_ForceTeam_f( void ) 
{
	gclient_t	*cl;
	char		str[MAX_TOKEN_CHARS];

	// find the player
	trap_Argv( 1, str, sizeof( str ) );
	cl = ClientForString( str );
	if ( !cl ) 
	{
		return;
	}

	// set the team
	trap_Argv( 2, str, sizeof( str ) );
	SetTeam( &g_entities[cl - level.clients], str, NULL );
}

/*
===================
Svcmd_CancelVote_f

cancels the vote in progress
===================
*/
void Svcmd_CancelVote_f ( void )
{
	level.voteTime = 0;

	trap_SetConfigstring( CS_VOTE_TIME, "" );	

	trap_SendServerCommand( -1, "print \"Vote cancelled by admin.\n\"" );
}

/*
=================
ConsoleCommand
=================
*/
qboolean ConsoleCommand( void ) 
{
	char cmd[MAX_TOKEN_CHARS];

	trap_Argv( 0, cmd, sizeof( cmd ) );

	if ( Q_stricmp (cmd, "entitylist") == 0 ) 
	{
		Svcmd_EntityList_f();
		return qtrue;
	}

	if ( Q_stricmp (cmd, "forceteam") == 0 ) 
	{
		Svcmd_ForceTeam_f();
		return qtrue;
	}

	if ( Q_stricmp ( cmd, "cancelvote" ) == 0 )
	{
		Svcmd_CancelVote_f();
		return qtrue;
	}

#ifdef _SOF2_BOTS

	if (Q_stricmp (cmd, "addbot") == 0) 
	{
		Svcmd_AddBot_f();
		return qtrue;
	}

	if (Q_stricmp (cmd, "botlist") == 0) 
	{
		Svcmd_BotList_f();
		return qtrue;
	}

#endif

	if (Q_stricmp (cmd, "gametype_restart" ) == 0 )
	{
		trap_Argv( 1, cmd, sizeof( cmd ) );
		G_ResetGametype ( Q_stricmp ( cmd, "full" ) == 0 );
		return qtrue;
	}

	if (Q_stricmp (cmd, "extendtime" ) == 0 )
	{
		Svcmd_ExtendTime_f();
		return qtrue;
	}

	if ( Q_stricmp ( cmd, "autokicklist" ) == 0 )
	{
		Svcmd_AutoKickList_f();
		return qtrue;
	}

	if ( Q_stricmp ( cmd, "mute" ) == 0 )
	{
		Svcmd_Mute_f ( );
		return qtrue;
	}

	if (g_dedicated.integer) 
	{
		if (Q_stricmp (cmd, "say") == 0) 
		{
			trap_SendServerCommand( -1, va("chat -1 \"server: %s\n\"", ConcatArgs(1) ) );
			return qtrue;
		}

		// everything else will also be printed as a say command
		trap_SendServerCommand( -1, va("chat -1 \"server: %s\n\"", ConcatArgs(0) ) );
		return qtrue;
	}

	return qfalse;
}

