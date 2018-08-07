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


p2p_ctx* p2p_init(char* ip_bind,uint32_t port)
{
	p2p_ctx		*ctx=malloc(sizeof(p2p_ctx));

	if(ctx!=NULL)
		ctx->nodes=arraylist_new(20);
	return ctx;
}

void p2p_free(p2p_ctx *ctx)
{
	if(ctx!=NULL)
	{
		if(ctx->nodes!=NULL)
		{
			arraylist_free(ctx->nodes);
		}
		free(ctx);
	}
}
