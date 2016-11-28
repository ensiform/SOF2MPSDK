code

equ trap_Print								  -1	; GT_PRINT 
equ trap_Error								  -2	; GT_ERROR 
equ trap_Milliseconds						  -3	; GT_MILLISECONDS 
equ trap_Cvar_Register						  -4	; GT_CVAR_REGISTER 
equ trap_Cvar_Update						  -5	; GT_CVAR_UPDATE 
equ trap_Cvar_Set							  -6	; GT_CVAR_SET 
equ trap_Cvar_VariableIntegerValue			  -7	; GT_CVAR_VARIABLE_INTEGER_VALUE 
equ trap_Cvar_VariableStringBuffer			  -8	; GT_CVAR_VARIABLE_STRING_BUFFER 
equ trap_Cmd_Restart						-129	; GT_RESTART 
equ trap_Cmd_TextMessage					-117	; GT_TEXTMESSAGE 
equ trap_Cmd_RadioMessage					-123	; GT_RADIOMESSAGE 
equ trap_Cmd_RegisterSound					-120	; GT_REGISTERSOUND 
equ trap_Cmd_StartGlobalSound				-121	; GT_STARTGLOBALSOUND 
equ trap_Cmd_StartSound						-138	; GT_STARTSOUND 
equ trap_Cmd_RegisterEffect					-130	; GT_REGISTEREFFECT 
equ trap_Cmd_PlayEffect						-131	; GT_PLAYEFFECT 
equ trap_Cmd_RegisterIcon					-132	; GT_REGISTERICON 
equ trap_Cmd_SetHUDIcon						-141	; GT_SETHUDICON 
equ trap_Cmd_AddTeamScore					-127	; GT_ADDTEAMSCORE 
equ trap_Cmd_AddClientScore					-128	; GT_ADDCLIENTSCORE 
equ trap_Cmd_RegisterItem					-122	; GT_REGISTERITEM 
equ trap_Cmd_RegisterTrigger				-124	; GT_REGISTERTRIGGER 
equ trap_Cmd_ResetItem						-118	; GT_RESETITEM 
equ trap_Cmd_GetClientName					-119	; GT_GETCLIENTNAME 
equ trap_Cmd_GetClientItems					-125	; GT_GETCLIENTITEMS 
equ trap_Cmd_DoesClientHaveItem				-126	; GT_DOESCLIENTHAVEITEM 
equ trap_Cmd_GetClientOrigin				-134	; GT_GETCLIENTORIGIN 
equ trap_Cmd_GiveClientItem					-135	; GT_GIVECLIENTITEM 
equ trap_Cmd_GetClientList					-140	; GT_GETCLIENTLIST 
equ trap_Cmd_TakeClientItem					-136	; GT_TAKECLIENTITEM 
equ trap_Cmd_SpawnItem						-137	; GT_SPAWNITEM 
equ trap_Cmd_UseTargets						-133	; GT_USETARGETS 
equ trap_Cmd_GetTriggerTarget				-139	; GT_GETTRIGGERTARGET 


; hardcoded functions
equ memset									-101	; GT_MEMSET 
equ memcpy									-102	; GT_MEMCPY 
equ strncpy									-103	; GT_STRNCPY 
equ sin										-104	; GT_SIN 
equ cos										-105	; GT_COS 
equ atan2									-106	; GT_ATAN2 
equ sqrt									-107	; GT_SQRT 
equ matrixmultiply							-116	; GT_MATRIXMULTIPLY 
equ anglevectors							-108	; GT_ANGLEVECTORS 
equ perpendicularvector						-109	; GT_PERPENDICULARVECTOR 
equ floor									-110	; GT_FLOOR 
equ ceil									-111	; GT_CEIL 
equ acos									-114	; GT_ACOS 
equ asin									-115	; GT_ASIN 
