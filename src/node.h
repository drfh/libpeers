//
//  socks.h
//  libpeers
//
//  Created by David Harris on 11/16/11.
//  Copyright (c) 2011 MegaApps. All rights reserved.
//

#ifndef libpeers_socks_h
#define libpeers_socks_h

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "uuid4.h"

struct node_t
{
	uuid_t				node_id;
	struct sockaddr_un		sock;

};



#endif
