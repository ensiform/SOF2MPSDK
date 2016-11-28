// Copyright (C) 2001-2002 Raven Software.
//
// gt_local.h -- local definitions for gametype module

#include "../../game/q_shared.h"
#include "../gt_public.h"
#include "../gt_syscalls.h"

typedef struct gametypeLocals_s
{
	int			time;

	int			bombBeepTime;

	int			bombPlantTime;
	vec3_t		bombPlantOrigin;
	char		bombPlantTarget[MAX_QPATH];
	
	qboolean	firstFrame;

	int			bombExplodeEffect;
	int			bombBeepSound;
	int			bombTakenSound;
	int			bombExplodedSound;
	int			bombPlantedSound;

	int			iconBombPlanted[7];

	int			bombGiveClient;
	int			bombPlantClient;

	qboolean	roundOver;

} gametypeLocals_t;

extern	gametypeLocals_t	gametype;

