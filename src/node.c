//
//  node.c
//  libpeers
//
//  Created by David Harris on 11/16/11.
//  Copyright (c) 2011 MegaApps. All rights reserved.
//

#include "global.h"
#include "node.h"

#include <stdio.h>
#include <stdlib.h>

node_t* node_init(void)
{
	node_t	*n;

	n=malloc(sizeof(node_t));
	n->status=0;
//	n->s=sock_init();

	return n;
}

node_t* node_init_address(char* address)
{
	return NULL;
}

node_t* node_init_sockaddr(node_t *n,struct sockaddr *addr)
{
	return NULL;
}
