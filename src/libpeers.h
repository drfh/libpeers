//
//  libpeers.h
//  libpeers
//
//  Created by David Harris on 11/16/18.
//  Copyright (c) 2011 MegaApps. All rights reserved.
//

#ifndef libpeers_libpeers_h
#define libpeers_libpeers_h

#ifdef __cplusplus
extern "C" {
#endif

#include "global.h"

#include "util/arraylist.h"
#include "node.h"

#include <stdint.h>

struct p2p_s
{
	ArrayList	*nodes;
	uint32_t	port;

};
typedef	struct p2p_s	p2p_ctx;


/**
 * Allocate and initialize a sock_t* pointer.
 * @param ip_bind	IP address to bind to. (NULL = all interfaces)
 * @param port		Port number to bind to. (0 = 12300)
 * @return			Returnes a pointer to memory allocated with the size of the p2p_s
 *					Also initializes ->nodes with array list
 *
 * @see p2p_init
 */
p2p_ctx* p2p_init(char* ip_bind,uint32_t port);


/**
 * Frees the allcated memort of ctx after disconnecting and releasing the nodes.
 * @param ctx		ctx that needs to be deallocated and freed.
 * @return			Returnes a pointer to memory allocated with the size of the p2p_s
 *					Also initializes ->nodes with array list
 *
 * @see p2p_free
 */
void p2p_free(p2p_ctx *ctx);


#ifdef __cplusplus
}
#endif

#endif
