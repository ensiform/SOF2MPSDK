// Copyright (C) 2001-2002 Raven Software.
//
#include "g_local.h"
#include "bg_public.h"

// this file is only included when building a dll
// g_syscalls.asm is included instead when building a qvm

static intptr_t (QDECL *Q_syscall)( intptr_t arg, ... ) = (intptr_t (QDECL *)( intptr_t, ...))-1;

Q_EXPORT void dllEntry( intptr_t (QDECL *syscallptr)( intptr_t arg,... ) ) {
	Q_syscall = syscallptr;
}

int PASSFLOAT( float x ) {
	float	floatTemp;
	floatTemp = x;
	return *(int *)&floatTemp;
}

void	trap_Printf( const char *fmt ) {
	Q_syscall( G_PRINT, fmt );
}

void	trap_Error( const char *fmt ) {
	Q_syscall( G_ERROR, fmt );
	// shut up GCC warning about returning functions, because we know better
	exit(1);
}

int		trap_Milliseconds( void ) {
	return Q_syscall( G_MILLISECONDS ); 
}
int		trap_Argc( void ) {
	return Q_syscall( G_ARGC );
}

void	trap_Argv( int n, char *buffer, int bufferLength ) {
	Q_syscall( G_ARGV, n, buffer, bufferLength );
}

int		trap_FS_FOpenFile( const char *qpath, fileHandle_t *f, fsMode_t mode ) {
	return Q_syscall( G_FS_FOPEN_FILE, qpath, f, mode );
}

void	trap_FS_Read( void *buffer, int len, fileHandle_t f ) {
	Q_syscall( G_FS_READ, buffer, len, f );
}

void	trap_FS_Write( const void *buffer, int len, fileHandle_t f ) {
	Q_syscall( G_FS_WRITE, buffer, len, f );
}

void	trap_FS_FCloseFile( fileHandle_t f ) {
	Q_syscall( G_FS_FCLOSE_FILE, f );
}

int trap_FS_GetFileList(  const char *path, const char *extension, char *listbuf, int bufsize ) {
	return Q_syscall( G_FS_GETFILELIST, path, extension, listbuf, bufsize );
}

void	trap_SendConsoleCommand( int exec_when, const char *text ) {
	Q_syscall( G_SEND_CONSOLE_COMMAND, exec_when, text );
}

void	trap_Cvar_Register( vmCvar_t *cvar, const char *var_name, const char *value, int flags, float MinValue, float MaxValue ) {
	Q_syscall( G_CVAR_REGISTER, cvar, var_name, value, flags, PASSFLOAT(MinValue), PASSFLOAT(MaxValue) );
}

void	trap_Cvar_Update( vmCvar_t *cvar ) {
	Q_syscall( G_CVAR_UPDATE, cvar );
}

void trap_Cvar_Set( const char *var_name, const char *value ) {
	Q_syscall( G_CVAR_SET, var_name, value );
}

int trap_Cvar_VariableIntegerValue( const char *var_name ) {
	return Q_syscall( G_CVAR_VARIABLE_INTEGER_VALUE, var_name );
}

void trap_Cvar_VariableStringBuffer( const char *var_name, char *buffer, int bufsize ) {
	Q_syscall( G_CVAR_VARIABLE_STRING_BUFFER, var_name, buffer, bufsize );
}


void trap_LocateGameData( gentity_t *gEnts, int numGEntities, int sizeofGEntity_t,
						 playerState_t *clients, int sizeofGClient ) {
	Q_syscall( G_LOCATE_GAME_DATA, gEnts, numGEntities, sizeofGEntity_t, clients, sizeofGClient );
}

void trap_RMG_Init(int terrainID)
{
	Q_syscall(G_RMG_INIT, terrainID);
}

void trap_DropClient( int clientNum, const char *reason ) {
	Q_syscall( G_DROP_CLIENT, clientNum, reason );
}

void trap_SendServerCommand( int clientNum, const char *text ) {
	Q_syscall( G_SEND_SERVER_COMMAND, clientNum, text );
}

void trap_SetConfigstring( int num, const char *string ) {
	Q_syscall( G_SET_CONFIGSTRING, num, string );
}

void trap_GetConfigstring( int num, char *buffer, int bufferSize ) {
	Q_syscall( G_GET_CONFIGSTRING, num, buffer, bufferSize );
}

void trap_GetUserinfo( int num, char *buffer, int bufferSize ) {
	Q_syscall( G_GET_USERINFO, num, buffer, bufferSize );
}

void trap_SetUserinfo( int num, const char *buffer ) {
	Q_syscall( G_SET_USERINFO, num, buffer );
}

void trap_GetServerinfo( char *buffer, int bufferSize ) {
	Q_syscall( G_GET_SERVERINFO, buffer, bufferSize );
}

void trap_SetBrushModel( gentity_t *ent, const char *name ) {
	Q_syscall( G_SET_BRUSH_MODEL, ent, name );
}

void trap_SetActiveSubBSP(int index)
{
	Q_syscall( G_SET_ACTIVE_SUBBSP, index );
}

void trap_Trace( trace_t *results, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end, int passEntityNum, int contentmask ) {
	Q_syscall( G_TRACE, results, start, mins, maxs, end, passEntityNum, contentmask, 0, 10 );
}

void trap_TraceCapsule( trace_t *results, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end, int passEntityNum, int contentmask ) {
	Q_syscall( G_TRACECAPSULE, results, start, mins, maxs, end, passEntityNum, contentmask, 0, 10 );
}

int trap_PointContents( const vec3_t point, int passEntityNum ) {
	return Q_syscall( G_POINT_CONTENTS, point, passEntityNum );
}


qboolean trap_InPVS( const vec3_t p1, const vec3_t p2 ) {
	return Q_syscall( G_IN_PVS, p1, p2 );
}

qboolean trap_InPVSIgnorePortals( const vec3_t p1, const vec3_t p2 ) {
	return Q_syscall( G_IN_PVS_IGNORE_PORTALS, p1, p2 );
}

void trap_AdjustAreaPortalState( gentity_t *ent, qboolean open ) {
	Q_syscall( G_ADJUST_AREA_PORTAL_STATE, ent, open );
}

qboolean trap_AreasConnected( int area1, int area2 ) {
	return Q_syscall( G_AREAS_CONNECTED, area1, area2 );
}

void trap_LinkEntity( gentity_t *ent ) {
	Q_syscall( G_LINKENTITY, ent );
}

void trap_UnlinkEntity( gentity_t *ent ) {
	Q_syscall( G_UNLINKENTITY, ent );
}

int trap_EntitiesInBox( const vec3_t mins, const vec3_t maxs, int *list, int maxcount ) {
	return Q_syscall( G_ENTITIES_IN_BOX, mins, maxs, list, maxcount );
}

qboolean trap_EntityContact( const vec3_t mins, const vec3_t maxs, const gentity_t *ent ) {
	return Q_syscall( G_ENTITY_CONTACT, mins, maxs, ent );
}

qboolean trap_EntityContactCapsule( const vec3_t mins, const vec3_t maxs, const gentity_t *ent ) {
	return Q_syscall( G_ENTITY_CONTACTCAPSULE, mins, maxs, ent );
}

int trap_BotAllocateClient( void ) {
	return Q_syscall( G_BOT_ALLOCATE_CLIENT );
}

void trap_BotFreeClient( int clientNum ) {
	Q_syscall( G_BOT_FREE_CLIENT, clientNum );
}

void trap_GetUsercmd( int clientNum, usercmd_t *cmd ) {
	Q_syscall( G_GET_USERCMD, clientNum, cmd );
}

qboolean trap_GetEntityToken( char *buffer, int bufferSize ) {
	return Q_syscall( G_GET_ENTITY_TOKEN, buffer, bufferSize );
}

void *trap_BotGetMemoryGame(int size)
{
	void *ptr;

	ptr = (void *)Q_syscall( G_BOT_GET_MEMORY, size );

	return ptr;
}

void trap_BotFreeMemoryGame(void *ptr)
{
	Q_syscall( G_BOT_FREE_MEMORY, ptr);
}

int trap_DebugPolygonCreate(int color, int numPoints, vec3_t *points) {
	return Q_syscall( G_DEBUG_POLYGON_CREATE, color, numPoints, points );
}

void trap_DebugPolygonDelete(int id) {
	Q_syscall( G_DEBUG_POLYGON_DELETE, id );
}

int trap_RealTime( qtime_t *qtime ) {
	return Q_syscall( G_REAL_TIME, qtime );
}

void trap_SnapVector( float *v ) {
	Q_syscall( G_SNAPVECTOR, v );
}

// BotLib traps start here
int trap_BotLibSetup( void ) {
	return Q_syscall( BOTLIB_SETUP );
}

int trap_BotLibShutdown( void ) {
	return Q_syscall( BOTLIB_SHUTDOWN );
}

int trap_BotLibVarSet(char *var_name, char *value) {
	return Q_syscall( BOTLIB_LIBVAR_SET, var_name, value );
}

int trap_BotLibVarGet(char *var_name, char *value, int size) {
	return Q_syscall( BOTLIB_LIBVAR_GET, var_name, value, size );
}

int trap_BotLibDefine(char *string) {
	return Q_syscall( BOTLIB_PC_ADD_GLOBAL_DEFINE, string );
}

int trap_BotLibStartFrame(float time) {
	return Q_syscall( BOTLIB_START_FRAME, PASSFLOAT( time ) );
}

int trap_BotLibLoadMap(const char *mapname) {
	return Q_syscall( BOTLIB_LOAD_MAP, mapname );
}

int trap_BotLibUpdateEntity(int ent, void /* struct bot_updateentity_s */ *bue) {
	return Q_syscall( BOTLIB_UPDATENTITY, ent, bue );
}

int trap_BotLibTest(int parm0, char *parm1, vec3_t parm2, vec3_t parm3) {
	return Q_syscall( BOTLIB_TEST, parm0, parm1, parm2, parm3 );
}

int trap_BotGetSnapshotEntity( int clientNum, int sequence ) {
	return Q_syscall( BOTLIB_GET_SNAPSHOT_ENTITY, clientNum, sequence );
}

int trap_BotGetServerCommand(int clientNum, char *message, int size) {
	return Q_syscall( BOTLIB_GET_CONSOLE_MESSAGE, clientNum, message, size );
}

void trap_BotUserCommand(int clientNum, usercmd_t *ucmd) {
	Q_syscall( BOTLIB_USER_COMMAND, clientNum, ucmd );
}

void trap_AAS_EntityInfo(int entnum, void /* struct aas_entityinfo_s */ *info) {
	Q_syscall( BOTLIB_AAS_ENTITY_INFO, entnum, info );
}

int trap_AAS_Initialized(void) {
	return Q_syscall( BOTLIB_AAS_INITIALIZED );
}

void trap_AAS_PresenceTypeBoundingBox(int presencetype, vec3_t mins, vec3_t maxs) {
	Q_syscall( BOTLIB_AAS_PRESENCE_TYPE_BOUNDING_BOX, presencetype, mins, maxs );
}

float trap_AAS_Time(void) {
	int temp;
	temp = Q_syscall( BOTLIB_AAS_TIME );
	return (*(float*)&temp);
}

int trap_AAS_PointAreaNum(vec3_t point) {
	return Q_syscall( BOTLIB_AAS_POINT_AREA_NUM, point );
}

int trap_AAS_PointReachabilityAreaIndex(vec3_t point) {
	return Q_syscall( BOTLIB_AAS_POINT_REACHABILITY_AREA_INDEX, point );
}

int trap_AAS_TraceAreas(vec3_t start, vec3_t end, int *areas, vec3_t *points, int maxareas) {
	return Q_syscall( BOTLIB_AAS_TRACE_AREAS, start, end, areas, points, maxareas );
}

int trap_AAS_BBoxAreas(vec3_t absmins, vec3_t absmaxs, int *areas, int maxareas) {
	return Q_syscall( BOTLIB_AAS_BBOX_AREAS, absmins, absmaxs, areas, maxareas );
}

int trap_AAS_AreaInfo( int areanum, void /* struct aas_areainfo_s */ *info ) {
	return Q_syscall( BOTLIB_AAS_AREA_INFO, areanum, info );
}

int trap_AAS_PointContents(vec3_t point) {
	return Q_syscall( BOTLIB_AAS_POINT_CONTENTS, point );
}

int trap_AAS_NextBSPEntity(int ent) {
	return Q_syscall( BOTLIB_AAS_NEXT_BSP_ENTITY, ent );
}

int trap_AAS_ValueForBSPEpairKey(int ent, char *key, char *value, int size) {
	return Q_syscall( BOTLIB_AAS_VALUE_FOR_BSP_EPAIR_KEY, ent, key, value, size );
}

int trap_AAS_VectorForBSPEpairKey(int ent, char *key, vec3_t v) {
	return Q_syscall( BOTLIB_AAS_VECTOR_FOR_BSP_EPAIR_KEY, ent, key, v );
}

int trap_AAS_FloatForBSPEpairKey(int ent, char *key, float *value) {
	return Q_syscall( BOTLIB_AAS_FLOAT_FOR_BSP_EPAIR_KEY, ent, key, value );
}

int trap_AAS_IntForBSPEpairKey(int ent, char *key, int *value) {
	return Q_syscall( BOTLIB_AAS_INT_FOR_BSP_EPAIR_KEY, ent, key, value );
}

int trap_AAS_AreaReachability(int areanum) {
	return Q_syscall( BOTLIB_AAS_AREA_REACHABILITY, areanum );
}

int trap_AAS_AreaTravelTimeToGoalArea(int areanum, vec3_t origin, int goalareanum, int travelflags) {
	return Q_syscall( BOTLIB_AAS_AREA_TRAVEL_TIME_TO_GOAL_AREA, areanum, origin, goalareanum, travelflags );
}

int trap_AAS_EnableRoutingArea( int areanum, int enable ) {
	return Q_syscall( BOTLIB_AAS_ENABLE_ROUTING_AREA, areanum, enable );
}

int trap_AAS_PredictRoute(void /*struct aas_predictroute_s*/ *route, int areanum, vec3_t origin,
							int goalareanum, int travelflags, int maxareas, int maxtime,
							int stopevent, int stopcontents, int stoptfl, int stopareanum) {
	return Q_syscall( BOTLIB_AAS_PREDICT_ROUTE, route, areanum, origin, goalareanum, travelflags, maxareas, maxtime, stopevent, stopcontents, stoptfl, stopareanum );
}

int trap_AAS_AlternativeRouteGoals(vec3_t start, int startareanum, vec3_t goal, int goalareanum, int travelflags,
										void /*struct aas_altroutegoal_s*/ *altroutegoals, int maxaltroutegoals,
										int type) {
	return Q_syscall( BOTLIB_AAS_ALTERNATIVE_ROUTE_GOAL, start, startareanum, goal, goalareanum, travelflags, altroutegoals, maxaltroutegoals, type );
}

int trap_AAS_Swimming(vec3_t origin) {
	return Q_syscall( BOTLIB_AAS_SWIMMING, origin );
}

int trap_AAS_PredictClientMovement(void /* struct aas_clientmove_s */ *move, int entnum, vec3_t origin, int presencetype, int onground, vec3_t velocity, vec3_t cmdmove, int cmdframes, int maxframes, float frametime, int stopevent, int stopareanum, int visualize) {
	return Q_syscall( BOTLIB_AAS_PREDICT_CLIENT_MOVEMENT, move, entnum, origin, presencetype, onground, velocity, cmdmove, cmdframes, maxframes, PASSFLOAT(frametime), stopevent, stopareanum, visualize );
}

void trap_EA_Say(int client, char *str) {
	Q_syscall( BOTLIB_EA_SAY, client, str );
}

void trap_EA_SayTeam(int client, char *str) {
	Q_syscall( BOTLIB_EA_SAY_TEAM, client, str );
}

void trap_EA_Command(int client, char *command) {
	Q_syscall( BOTLIB_EA_COMMAND, client, command );
}

void trap_EA_Action(int client, int action) {
	Q_syscall( BOTLIB_EA_ACTION, client, action );
}

void trap_EA_Gesture(int client) {
	Q_syscall( BOTLIB_EA_GESTURE, client );
}

void trap_EA_Talk(int client) {
	Q_syscall( BOTLIB_EA_TALK, client );
}

void trap_EA_Attack(int client) {
	Q_syscall( BOTLIB_EA_ATTACK, client );
}

void trap_EA_Alt_Attack(int client) {
	Q_syscall( BOTLIB_EA_ALT_ATTACK, client );
}

void trap_EA_ForcePower(int client) {
	Q_syscall( BOTLIB_EA_FORCEPOWER, client );
}

void trap_EA_Use(int client) {
	Q_syscall( BOTLIB_EA_USE, client );
}

void trap_EA_Respawn(int client) {
	Q_syscall( BOTLIB_EA_RESPAWN, client );
}

void trap_EA_Crouch(int client) {
	Q_syscall( BOTLIB_EA_CROUCH, client );
}

void trap_EA_MoveUp(int client) {
	Q_syscall( BOTLIB_EA_MOVE_UP, client );
}

void trap_EA_MoveDown(int client) {
	Q_syscall( BOTLIB_EA_MOVE_DOWN, client );
}

void trap_EA_MoveForward(int client) {
	Q_syscall( BOTLIB_EA_MOVE_FORWARD, client );
}

void trap_EA_MoveBack(int client) {
	Q_syscall( BOTLIB_EA_MOVE_BACK, client );
}

void trap_EA_MoveLeft(int client) {
	Q_syscall( BOTLIB_EA_MOVE_LEFT, client );
}

void trap_EA_MoveRight(int client) {
	Q_syscall( BOTLIB_EA_MOVE_RIGHT, client );
}

void trap_EA_SelectWeapon(int client, int weapon) {
	Q_syscall( BOTLIB_EA_SELECT_WEAPON, client, weapon );
}

void trap_EA_Jump(int client) {
	Q_syscall( BOTLIB_EA_JUMP, client );
}

void trap_EA_DelayedJump(int client) {
	Q_syscall( BOTLIB_EA_DELAYED_JUMP, client );
}

void trap_EA_Move(int client, vec3_t dir, float speed) {
	Q_syscall( BOTLIB_EA_MOVE, client, dir, PASSFLOAT(speed) );
}

void trap_EA_View(int client, vec3_t viewangles) {
	Q_syscall( BOTLIB_EA_VIEW, client, viewangles );
}

void trap_EA_EndRegular(int client, float thinktime) {
	Q_syscall( BOTLIB_EA_END_REGULAR, client, PASSFLOAT(thinktime) );
}

void trap_EA_GetInput(int client, float thinktime, void /* struct bot_input_s */ *input) {
	Q_syscall( BOTLIB_EA_GET_INPUT, client, PASSFLOAT(thinktime), input );
}

void trap_EA_ResetInput(int client) {
	Q_syscall( BOTLIB_EA_RESET_INPUT, client );
}

int trap_BotLoadCharacter(char *charfile, float skill) {
	return Q_syscall( BOTLIB_AI_LOAD_CHARACTER, charfile, PASSFLOAT(skill));
}

void trap_BotFreeCharacter(int character) {
	Q_syscall( BOTLIB_AI_FREE_CHARACTER, character );
}

float trap_Characteristic_Float(int character, int index) {
	int temp;
	temp = Q_syscall( BOTLIB_AI_CHARACTERISTIC_FLOAT, character, index );
	return (*(float*)&temp);
}

float trap_Characteristic_BFloat(int character, int index, float min, float max) {
	int temp;
	temp = Q_syscall( BOTLIB_AI_CHARACTERISTIC_BFLOAT, character, index, PASSFLOAT(min), PASSFLOAT(max) );
	return (*(float*)&temp);
}

int trap_Characteristic_Integer(int character, int index) {
	return Q_syscall( BOTLIB_AI_CHARACTERISTIC_INTEGER, character, index );
}

int trap_Characteristic_BInteger(int character, int index, int min, int max) {
	return Q_syscall( BOTLIB_AI_CHARACTERISTIC_BINTEGER, character, index, min, max );
}

void trap_Characteristic_String(int character, int index, char *buf, int size) {
	Q_syscall( BOTLIB_AI_CHARACTERISTIC_STRING, character, index, buf, size );
}

int trap_BotAllocChatState(void) {
	return Q_syscall( BOTLIB_AI_ALLOC_CHAT_STATE );
}

void trap_BotFreeChatState(int handle) {
	Q_syscall( BOTLIB_AI_FREE_CHAT_STATE, handle );
}

void trap_BotQueueConsoleMessage(int chatstate, int type, char *message) {
	Q_syscall( BOTLIB_AI_QUEUE_CONSOLE_MESSAGE, chatstate, type, message );
}

void trap_BotRemoveConsoleMessage(int chatstate, int handle) {
	Q_syscall( BOTLIB_AI_REMOVE_CONSOLE_MESSAGE, chatstate, handle );
}

int trap_BotNextConsoleMessage(int chatstate, void /* struct bot_consolemessage_s */ *cm) {
	return Q_syscall( BOTLIB_AI_NEXT_CONSOLE_MESSAGE, chatstate, cm );
}

int trap_BotNumConsoleMessages(int chatstate) {
	return Q_syscall( BOTLIB_AI_NUM_CONSOLE_MESSAGE, chatstate );
}

void trap_BotInitialChat(int chatstate, char *type, int mcontext, char *var0, char *var1, char *var2, char *var3, char *var4, char *var5, char *var6, char *var7 ) {
	Q_syscall( BOTLIB_AI_INITIAL_CHAT, chatstate, type, mcontext, var0, var1, var2, var3, var4, var5, var6, var7 );
}

int	trap_BotNumInitialChats(int chatstate, char *type) {
	return Q_syscall( BOTLIB_AI_NUM_INITIAL_CHATS, chatstate, type );
}

int trap_BotReplyChat(int chatstate, char *message, int mcontext, int vcontext, char *var0, char *var1, char *var2, char *var3, char *var4, char *var5, char *var6, char *var7 ) {
	return Q_syscall( BOTLIB_AI_REPLY_CHAT, chatstate, message, mcontext, vcontext, var0, var1, var2, var3, var4, var5, var6, var7 );
}

int trap_BotChatLength(int chatstate) {
	return Q_syscall( BOTLIB_AI_CHAT_LENGTH, chatstate );
}

void trap_BotEnterChat(int chatstate, int client, int sendto) {
	Q_syscall( BOTLIB_AI_ENTER_CHAT, chatstate, client, sendto );
}

void trap_BotGetChatMessage(int chatstate, char *buf, int size) {
	Q_syscall( BOTLIB_AI_GET_CHAT_MESSAGE, chatstate, buf, size);
}

int trap_StringContains(char *str1, char *str2, int casesensitive) {
	return Q_syscall( BOTLIB_AI_STRING_CONTAINS, str1, str2, casesensitive );
}

int trap_BotFindMatch(char *str, void /* struct bot_match_s */ *match, unsigned long int context) {
	return Q_syscall( BOTLIB_AI_FIND_MATCH, str, match, context );
}

void trap_BotMatchVariable(void /* struct bot_match_s */ *match, int variable, char *buf, int size) {
	Q_syscall( BOTLIB_AI_MATCH_VARIABLE, match, variable, buf, size );
}

void trap_UnifyWhiteSpaces(char *string) {
	Q_syscall( BOTLIB_AI_UNIFY_WHITE_SPACES, string );
}

void trap_BotReplaceSynonyms(char *string, unsigned long int context) {
	Q_syscall( BOTLIB_AI_REPLACE_SYNONYMS, string, context );
}

int trap_BotLoadChatFile(int chatstate, char *chatfile, char *chatname) {
	return Q_syscall( BOTLIB_AI_LOAD_CHAT_FILE, chatstate, chatfile, chatname );
}

void trap_BotSetChatGender(int chatstate, int gender) {
	Q_syscall( BOTLIB_AI_SET_CHAT_GENDER, chatstate, gender );
}

void trap_BotSetChatName(int chatstate, char *name, int client) {
	Q_syscall( BOTLIB_AI_SET_CHAT_NAME, chatstate, name, client );
}

void trap_BotResetGoalState(int goalstate) {
	Q_syscall( BOTLIB_AI_RESET_GOAL_STATE, goalstate );
}

void trap_BotResetAvoidGoals(int goalstate) {
	Q_syscall( BOTLIB_AI_RESET_AVOID_GOALS, goalstate );
}

void trap_BotRemoveFromAvoidGoals(int goalstate, int number) {
	Q_syscall( BOTLIB_AI_REMOVE_FROM_AVOID_GOALS, goalstate, number);
}

void trap_BotPushGoal(int goalstate, void /* struct bot_goal_s */ *goal) {
	Q_syscall( BOTLIB_AI_PUSH_GOAL, goalstate, goal );
}

void trap_BotPopGoal(int goalstate) {
	Q_syscall( BOTLIB_AI_POP_GOAL, goalstate );
}

void trap_BotEmptyGoalStack(int goalstate) {
	Q_syscall( BOTLIB_AI_EMPTY_GOAL_STACK, goalstate );
}

void trap_BotDumpAvoidGoals(int goalstate) {
	Q_syscall( BOTLIB_AI_DUMP_AVOID_GOALS, goalstate );
}

void trap_BotDumpGoalStack(int goalstate) {
	Q_syscall( BOTLIB_AI_DUMP_GOAL_STACK, goalstate );
}

void trap_BotGoalName(int number, char *name, int size) {
	Q_syscall( BOTLIB_AI_GOAL_NAME, number, name, size );
}

int trap_BotGetTopGoal(int goalstate, void /* struct bot_goal_s */ *goal) {
	return Q_syscall( BOTLIB_AI_GET_TOP_GOAL, goalstate, goal );
}

int trap_BotGetSecondGoal(int goalstate, void /* struct bot_goal_s */ *goal) {
	return Q_syscall( BOTLIB_AI_GET_SECOND_GOAL, goalstate, goal );
}

int trap_BotChooseLTGItem(int goalstate, vec3_t origin, int *inventory, int travelflags) {
	return Q_syscall( BOTLIB_AI_CHOOSE_LTG_ITEM, goalstate, origin, inventory, travelflags );
}

int trap_BotChooseNBGItem(int goalstate, vec3_t origin, int *inventory, int travelflags, void /* struct bot_goal_s */ *ltg, float maxtime) {
	return Q_syscall( BOTLIB_AI_CHOOSE_NBG_ITEM, goalstate, origin, inventory, travelflags, ltg, PASSFLOAT(maxtime) );
}

int trap_BotTouchingGoal(vec3_t origin, void /* struct bot_goal_s */ *goal) {
	return Q_syscall( BOTLIB_AI_TOUCHING_GOAL, origin, goal );
}

int trap_BotItemGoalInVisButNotVisible(int viewer, vec3_t eye, vec3_t viewangles, void /* struct bot_goal_s */ *goal) {
	return Q_syscall( BOTLIB_AI_ITEM_GOAL_IN_VIS_BUT_NOT_VISIBLE, viewer, eye, viewangles, goal );
}

int trap_BotGetLevelItemGoal(int index, char *classname, void /* struct bot_goal_s */ *goal) {
	return Q_syscall( BOTLIB_AI_GET_LEVEL_ITEM_GOAL, index, classname, goal );
}

int trap_BotGetNextCampSpotGoal(int num, void /* struct bot_goal_s */ *goal) {
	return Q_syscall( BOTLIB_AI_GET_NEXT_CAMP_SPOT_GOAL, num, goal );
}

int trap_BotGetMapLocationGoal(char *name, void /* struct bot_goal_s */ *goal) {
	return Q_syscall( BOTLIB_AI_GET_MAP_LOCATION_GOAL, name, goal );
}

float trap_BotAvoidGoalTime(int goalstate, int number) {
	int temp;
	temp = Q_syscall( BOTLIB_AI_AVOID_GOAL_TIME, goalstate, number );
	return (*(float*)&temp);
}

void trap_BotSetAvoidGoalTime(int goalstate, int number, float avoidtime) {
	Q_syscall( BOTLIB_AI_SET_AVOID_GOAL_TIME, goalstate, number, PASSFLOAT(avoidtime));
}

void trap_BotInitLevelItems(void) {
	Q_syscall( BOTLIB_AI_INIT_LEVEL_ITEMS );
}

void trap_BotUpdateEntityItems(void) {
	Q_syscall( BOTLIB_AI_UPDATE_ENTITY_ITEMS );
}

int trap_BotLoadItemWeights(int goalstate, char *filename) {
	return Q_syscall( BOTLIB_AI_LOAD_ITEM_WEIGHTS, goalstate, filename );
}

void trap_BotFreeItemWeights(int goalstate) {
	Q_syscall( BOTLIB_AI_FREE_ITEM_WEIGHTS, goalstate );
}

void trap_BotInterbreedGoalFuzzyLogic(int parent1, int parent2, int child) {
	Q_syscall( BOTLIB_AI_INTERBREED_GOAL_FUZZY_LOGIC, parent1, parent2, child );
}

void trap_BotSaveGoalFuzzyLogic(int goalstate, char *filename) {
	Q_syscall( BOTLIB_AI_SAVE_GOAL_FUZZY_LOGIC, goalstate, filename );
}

void trap_BotMutateGoalFuzzyLogic(int goalstate, float range) {
	Q_syscall( BOTLIB_AI_MUTATE_GOAL_FUZZY_LOGIC, goalstate, range );
}

int trap_BotAllocGoalState(int state) {
	return Q_syscall( BOTLIB_AI_ALLOC_GOAL_STATE, state );
}

void trap_BotFreeGoalState(int handle) {
	Q_syscall( BOTLIB_AI_FREE_GOAL_STATE, handle );
}

void trap_BotResetMoveState(int movestate) {
	Q_syscall( BOTLIB_AI_RESET_MOVE_STATE, movestate );
}

void trap_BotAddAvoidSpot(int movestate, vec3_t origin, float radius, int type) {
	Q_syscall( BOTLIB_AI_ADD_AVOID_SPOT, movestate, origin, PASSFLOAT(radius), type);
}

void trap_BotMoveToGoal(void /* struct bot_moveresult_s */ *result, int movestate, void /* struct bot_goal_s */ *goal, int travelflags) {
	Q_syscall( BOTLIB_AI_MOVE_TO_GOAL, result, movestate, goal, travelflags );
}

int trap_BotMoveInDirection(int movestate, vec3_t dir, float speed, int type) {
	return Q_syscall( BOTLIB_AI_MOVE_IN_DIRECTION, movestate, dir, PASSFLOAT(speed), type );
}

void trap_BotResetAvoidReach(int movestate) {
	Q_syscall( BOTLIB_AI_RESET_AVOID_REACH, movestate );
}

void trap_BotResetLastAvoidReach(int movestate) {
	Q_syscall( BOTLIB_AI_RESET_LAST_AVOID_REACH,movestate  );
}

int trap_BotReachabilityArea(vec3_t origin, int testground) {
	return Q_syscall( BOTLIB_AI_REACHABILITY_AREA, origin, testground );
}

int trap_BotMovementViewTarget(int movestate, void /* struct bot_goal_s */ *goal, int travelflags, float lookahead, vec3_t target) {
	return Q_syscall( BOTLIB_AI_MOVEMENT_VIEW_TARGET, movestate, goal, travelflags, PASSFLOAT(lookahead), target );
}

int trap_BotPredictVisiblePosition(vec3_t origin, int areanum, void /* struct bot_goal_s */ *goal, int travelflags, vec3_t target) {
	return Q_syscall( BOTLIB_AI_PREDICT_VISIBLE_POSITION, origin, areanum, goal, travelflags, target );
}

int trap_BotAllocMoveState(void) {
	return Q_syscall( BOTLIB_AI_ALLOC_MOVE_STATE );
}

void trap_BotFreeMoveState(int handle) {
	Q_syscall( BOTLIB_AI_FREE_MOVE_STATE, handle );
}

void trap_BotInitMoveState(int handle, void /* struct bot_initmove_s */ *initmove) {
	Q_syscall( BOTLIB_AI_INIT_MOVE_STATE, handle, initmove );
}

int trap_BotChooseBestFightWeapon(int weaponstate, int *inventory) {
	return Q_syscall( BOTLIB_AI_CHOOSE_BEST_FIGHT_WEAPON, weaponstate, inventory );
}

void trap_BotGetWeaponInfo(int weaponstate, int weapon, void /* struct weaponinfo_s */ *weaponinfo) {
	Q_syscall( BOTLIB_AI_GET_WEAPON_INFO, weaponstate, weapon, weaponinfo );
}

int trap_BotLoadWeaponWeights(int weaponstate, char *filename) {
	return Q_syscall( BOTLIB_AI_LOAD_WEAPON_WEIGHTS, weaponstate, filename );
}

int trap_BotAllocWeaponState(void) {
	return Q_syscall( BOTLIB_AI_ALLOC_WEAPON_STATE );
}

void trap_BotFreeWeaponState(int weaponstate) {
	Q_syscall( BOTLIB_AI_FREE_WEAPON_STATE, weaponstate );
}

void trap_BotResetWeaponState(int weaponstate) {
	Q_syscall( BOTLIB_AI_RESET_WEAPON_STATE, weaponstate );
}

int trap_GeneticParentsAndChildSelection(int numranks, float *ranks, int *parent1, int *parent2, int *child) {
	return Q_syscall( BOTLIB_AI_GENETIC_PARENTS_AND_CHILD_SELECTION, numranks, ranks, parent1, parent2, child );
}

int trap_PC_LoadSource( const char *filename ) {
	return Q_syscall( BOTLIB_PC_LOAD_SOURCE, filename );
}

int trap_PC_FreeSource( int handle ) {
	return Q_syscall( BOTLIB_PC_FREE_SOURCE, handle );
}

int trap_PC_ReadToken( int handle, pc_token_t *pc_token ) {
	return Q_syscall( BOTLIB_PC_READ_TOKEN, handle, pc_token );
}

int trap_PC_SourceFileAndLine( int handle, char *filename, int *line ) {
	return Q_syscall( BOTLIB_PC_SOURCE_FILE_AND_LINE, handle, filename, line );
}

int trap_PC_LoadGlobalDefines ( const char* filename )
{
	return Q_syscall( BOTLIB_PC_LOAD_GLOBAL_DEFINES, filename );
}

void trap_PC_RemoveAllGlobalDefines ( void )
{
	Q_syscall( BOTLIB_PC_REMOVE_ALL_GLOBAL_DEFINES );
}

// CG Specific API calls
void trap_G2_ListModelSurfaces(void *ghlInfo)
{
	Q_syscall( G_G2_LISTSURFACES, ghlInfo);
}

void trap_G2_ListModelBones(void *ghlInfo, int frame)
{
	Q_syscall( G_G2_LISTBONES, ghlInfo, frame);
}

void trap_G2_SetGhoul2ModelIndexes(void *ghoul2, qhandle_t *modelList, qhandle_t *skinList)
{
	Q_syscall( G_G2_SETMODELS, ghoul2, modelList, skinList);
}

qboolean trap_G2_HaveWeGhoul2Models(	void *ghoul2)
{
	return (qboolean)(Q_syscall(G_G2_HAVEWEGHOULMODELS, ghoul2));
}

int	trap_G2API_AddBolt(void *ghoul2, const int modelIndex, const char *boneName)
{
	return (int) (Q_syscall(G_G2_ADDBOLT, ghoul2, modelIndex, boneName));
}

void trap_G2API_SetBoltInfo(void *ghoul2, int modelIndex, int boltInfo)
{
	Q_syscall(G_G2_SETBOLTINFO, ghoul2, modelIndex, boltInfo);
}

qboolean trap_G2API_GetBoltMatrix(void *ghoul2, const int modelIndex, const int boltIndex, mdxaBone_t *matrix,
								const vec3_t angles, const vec3_t position, const int frameNum, qhandle_t *modelList, vec3_t scale)
{
	return (qboolean)(Q_syscall(G_G2_GETBOLT, ghoul2, modelIndex, boltIndex, matrix, angles, position, frameNum, modelList, scale));
}

int trap_G2API_InitGhoul2Model(void **ghoul2Ptr, const char *fileName, int modelIndex, qhandle_t customSkin,
						  qhandle_t customShader, int modelFlags, int lodBias)
{
	return Q_syscall(G_G2_INITGHOUL2MODEL, ghoul2Ptr, fileName, modelIndex, customSkin, customShader, modelFlags, lodBias);
}

void trap_G2API_CleanGhoul2Models ( void **ghoul2Ptr )
{
	Q_syscall(G_G2_CLEANMODELS, ghoul2Ptr);
}

void trap_G2API_CollisionDetect ( 
	CollisionRecord_t *collRecMap, 
	void* ghoul2, 
	const vec3_t angles, 
	const vec3_t position,
	int frameNumber, 
	int entNum, 
	vec3_t rayStart, 
	vec3_t rayEnd, 
	vec3_t scale, 
	int traceFlags, 
	int useLod
	)
{
	Q_syscall( G_G2_COLLISIONDETECT, collRecMap, ghoul2, angles, position, frameNumber, entNum, rayStart, rayEnd, scale, traceFlags, useLod );
}

qhandle_t trap_G2API_RegisterSkin ( const char *skinName, int numPairs, const char *skinPairs)
{
	return Q_syscall(G_G2_REGISTERSKIN, skinName, numPairs, skinPairs );
}

qboolean trap_G2API_SetSkin ( void* ghoul2, int modelIndex, qhandle_t customSkin)
{
	return Q_syscall(G_G2_SETSKIN, ghoul2, modelIndex, customSkin );
}

qboolean trap_G2API_GetAnimFileNameIndex ( void* ghoul2, qhandle_t modelIndex, const char* filename )
{
	return Q_syscall(G_G2_GETANIMFILENAMEINDEX, ghoul2, modelIndex, filename );
}

qboolean trap_G2API_SetBoneAngles(void *ghoul2, int modelIndex, const char *boneName, const vec3_t angles, const int flags,
								const int up, const int right, const int forward, qhandle_t *modelList,
								int blendTime , int currentTime )
{
	return (Q_syscall(G_G2_ANGLEOVERRIDE, ghoul2, modelIndex, boneName, angles, flags, up, right, forward, modelList, blendTime, currentTime));
}

qboolean trap_G2API_SetBoneAnim(void *ghoul2, const int modelIndex, const char *boneName, const int startFrame, const int endFrame,
							  const int flags, const float animSpeed, const int currentTime, const float setFrame , const int blendTime )
{
	return Q_syscall(G_G2_PLAYANIM, ghoul2, modelIndex, boneName, startFrame, endFrame, flags, PASSFLOAT(animSpeed), currentTime, PASSFLOAT(setFrame), blendTime);
}

char *trap_G2API_GetGLAName(void *ghoul2, int modelIndex)
{
	return (char *)Q_syscall(G_G2_GETGLANAME, ghoul2, modelIndex);
}

int trap_G2API_CopyGhoul2Instance(void *g2From, void *g2To, int modelIndex)
{
	return Q_syscall(G_G2_COPYGHOUL2INSTANCE, g2From, g2To, modelIndex);
}

int trap_G2API_CopySpecificGhoul2Model(void *g2From, int modelFrom, void *g2To, int modelTo)
{
	return Q_syscall(G_G2_COPYSPECIFICGHOUL2MODEL, g2From, modelFrom, g2To, modelTo);
}

void trap_G2API_DuplicateGhoul2Instance(void *g2From, void **g2To)
{
	Q_syscall(G_G2_DUPLICATEGHOUL2INSTANCE, g2From, g2To);
}

qboolean trap_G2API_RemoveGhoul2Model(void **ghlInfo, int modelIndex)
{
	return Q_syscall(G_G2_REMOVEGHOUL2MODEL, ghlInfo, modelIndex);
}

/*
Ghoul2 Insert End
*/

// CGenericParser2 (void *) routines
TGenericParser2 trap_GP_Parse(char **dataPtr, qboolean cleanFirst, qboolean writeable)
{
	return (TGenericParser2)Q_syscall(G_GP_PARSE, dataPtr, cleanFirst, writeable);
}

TGenericParser2 trap_GP_ParseFile(char *fileName, qboolean cleanFirst, qboolean writeable)
{
	return (TGenericParser2)Q_syscall(G_GP_PARSE_FILE, fileName, cleanFirst, writeable);
}

void trap_GP_Clean(TGenericParser2 GP2)
{
	Q_syscall(G_GP_CLEAN, GP2);
}

void trap_GP_Delete(TGenericParser2 *GP2)
{
	Q_syscall(G_GP_DELETE, GP2);
}

TGPGroup trap_GP_GetBaseParseGroup(TGenericParser2 GP2)
{
	return (TGPGroup)Q_syscall(G_GP_GET_BASE_PARSE_GROUP, GP2);
}


// CGPGroup (void *) routines
qboolean trap_GPG_GetName(TGPGroup GPG, char *Value)
{
	return (qboolean)Q_syscall(G_GPG_GET_NAME, GPG, Value);
}

TGPGroup trap_GPG_GetNext(TGPGroup GPG)
{
	return (TGPGroup)Q_syscall(G_GPG_GET_NEXT, GPG);
}

TGPGroup trap_GPG_GetInOrderNext(TGPGroup GPG)
{
	return (TGPGroup)Q_syscall(G_GPG_GET_INORDER_NEXT, GPG);
}

TGPGroup trap_GPG_GetInOrderPrevious(TGPGroup GPG)
{
	return (TGPGroup)Q_syscall(G_GPG_GET_INORDER_PREVIOUS, GPG);
}

TGPGroup trap_GPG_GetPairs(TGPGroup GPG)
{
	return (TGPGroup)Q_syscall(G_GPG_GET_PAIRS, GPG);
}

TGPGroup trap_GPG_GetInOrderPairs(TGPGroup GPG)
{
	return (TGPGroup)Q_syscall(G_GPG_GET_INORDER_PAIRS, GPG);
}

TGPGroup trap_GPG_GetSubGroups(TGPGroup GPG)
{
	return (TGPGroup)Q_syscall(G_GPG_GET_SUBGROUPS, GPG);
}

TGPGroup trap_GPG_GetInOrderSubGroups(TGPGroup GPG)
{
	return (TGPGroup)Q_syscall(G_GPG_GET_INORDER_SUBGROUPS, GPG);
}

TGPValue trap_GPG_FindSubGroup(TGPGroup GPG, const char *name)
{
	return (TGPValue)Q_syscall(G_GPG_FIND_SUBGROUP, GPG, name);
}

TGPValue trap_GPG_FindPair(TGPGroup GPG, const char *key)
{
	return (TGPValue)Q_syscall(G_GPG_FIND_PAIR, GPG, key);
}

qboolean trap_GPG_FindPairValue(TGPGroup GPG, const char *key, const char *defaultVal, char *Value)
{
	return (qboolean)Q_syscall(G_GPG_FIND_PAIRVALUE, GPG, key, defaultVal, Value);
}


// CGPValue (void *) routines
qboolean trap_GPV_GetName(TGPValue GPV, char *Value)
{
	return (qboolean)Q_syscall(G_GPV_GET_NAME, GPV, Value);
}

TGPValue trap_GPV_GetNext(TGPValue GPV)
{
	return (TGPValue)Q_syscall(G_GPV_GET_NEXT, GPV);
}

TGPValue trap_GPV_GetInOrderNext(TGPValue GPV)
{
	return (TGPValue)Q_syscall(G_GPV_GET_INORDER_NEXT, GPV);
}

TGPValue trap_GPV_GetInOrderPrevious(TGPValue GPV)
{
	return (TGPValue)Q_syscall(G_GPV_GET_INORDER_PREVIOUS, GPV);
}

qboolean trap_GPV_IsList(TGPValue GPV)
{
	return (qboolean)Q_syscall(G_GPV_IS_LIST, GPV);
}

qboolean trap_GPV_GetTopValue(TGPValue GPV, char *Value)
{
	return (qboolean)Q_syscall(G_GPV_GET_TOP_VALUE, GPV, Value);
}

TGPValue trap_GPV_GetList(TGPValue GPV)
{
	return (TGPValue)Q_syscall(G_GPV_GET_LIST, GPV);
}

int	trap_CM_RegisterTerrain(const char *config)
{
	return Q_syscall(G_CM_REGISTER_TERRAIN, config);
}

void trap_GetModelFormalName ( const char* model, const char* skin, char* name, int size )
{
	Q_syscall( G_GET_MODEL_FORMALNAME, model, skin, name, size );
}

void trap_GetWorldBounds ( vec3_t mins, vec3_t maxs )
{
	Q_syscall( G_GET_WORLD_BOUNDS, mins, maxs );
}

void *trap_VM_LocalAlloc ( int size )
{
	return (void *)Q_syscall( G_VM_LOCALALLOC, size );
}

void *trap_VM_LocalAllocUnaligned ( int size )
{
	return (void *)Q_syscall( G_VM_LOCALALLOCUNALIGNED, size );
}

void *trap_VM_LocalTempAlloc( int size )
{
	return (void *)Q_syscall( G_VM_LOCALTEMPALLOC, size );
}

void trap_VM_LocalTempFree( int size )
{
	Q_syscall( G_VM_LOCALTEMPFREE, size );
}

const char *trap_VM_LocalStringAlloc ( const char *source )
{
	return (const char *)Q_syscall( G_VM_LOCALSTRINGALLOC, source );
}

void trap_GT_Init ( const char* gametype, qboolean restart )
{
	Q_syscall( G_GT_INIT, gametype, restart );
}

void trap_GT_RunFrame ( int time )
{
	Q_syscall( G_GT_RUNFRAME, time );
}

void trap_GT_Start ( int time )
{
	Q_syscall( G_GT_START, time );
}

int trap_GT_SendEvent ( int event, int time, int arg0, int arg1, int arg2, int arg3, int arg4 )
{
	return Q_syscall( G_GT_SENDEVENT, event, time, arg0, arg1, arg2, arg3, arg4 );
}

