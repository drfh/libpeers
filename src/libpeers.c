//
//  libpeers.c
//  libpeers
//
//  Created by David Harris on 11/16/11.
//  Copyright (c) 2011 MegaApps. All rights reserved.
//

#include "global.h"
#include "libpeers.h"

#include <stdio.h>
#include <stdlib.h>


void p2p_init(p2p_ctx **ctx)
{
	ctx=malloc(sizeof(p2p_ctx));

}

void p2p_free(p2p_ctx *ctx)
{
	if(ctx!=NULL)
	{
		if(ctx->nodes!=NULL)
		{
			free(ctx->nodes);
		}
		free(ctx);
	}
}
