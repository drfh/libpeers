//
//  libpeers.h
//  libpeers
//
//  Created by David Harris on 11/16/18.
//  Copyright (c) 2011 MegaApps. All rights reserved.
//

#ifndef libpeers_libpeers_h
#define libpeers_libpeers_h

#include "global.h"

#include "node.h"

#include <stdint.h>

struct p2p_s
{
    node_t		*nodes;
	uint32_t	port;

};
typedef	struct p2p_s	p2p_ctx;

#endif
