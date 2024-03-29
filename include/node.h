//
//  node.h
//  libpeers
//
//  Created by David Harris on 11/16/11.
//  Copyright (c) 2011 MegaApps. All rights reserved.
//

#ifndef libpeers_node_h
#define libpeers_node_h

#ifdef __cplusplus
extern "C" {
#endif

#include "socks.h"

#include <stdio.h>
#include <stdint.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "util/uuid4.h"

struct node_s
{
	uuid_t		node_id;
	sock_t		*s;

	long		status;
};

typedef	struct node_s	node_t;


node_t* node_init_(char* address);


#ifdef __cplusplus
}
#endif

#endif
