//
//  node.h
//  libpeers
//
//  Created by David Harris on 11/16/11.
//  Copyright (c) 2011 MegaApps. All rights reserved.
//

#ifndef libpeers_node_h
#define libpeers_node_h

#include "socks.h"

#include <stdio.h>
#include <stdint.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "util/uuid4.h"

struct node_s
{
	uuid_t				node_id;
	struct sockaddr_un		sock;

};

typedef	struct node_s	node_t;

#endif
