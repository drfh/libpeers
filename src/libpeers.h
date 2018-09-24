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
#include "message.h"

#include <stdint.h>
#include <pthread.h>


typedef	struct p2p_s	p2p_ctx;

typedef void (*p2p_message_handle)(p2p_ctx* ctx,char* m,node_t* n);

struct p2p_s
{
	long		status;
	ArrayList	*peers;
	uint32_t	port;
	sock_t		*s;

	long		packet_size;

	pthread_mutex_t	mutex;
	pthread_t	tid;

	p2p_message_handle	handler;
};


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
 *
 * @see p2p_free
 */
void p2p_free(p2p_ctx *ctx);


/**
 * Start the pthread for the poll runloop.
 * @param ctx		Context record of the p2p server that is to be operated on.
 *
 * @see p2p_start
 */
void p2p_start(p2p_ctx *ctx);



enum peer_options { kOneTry=0 };
enum peer_options { kOneTry=0,kTryForever };

/**
 * Adds a peer to the list of peers.
 * @param ctx		Context record of the p2p server that is to be operated on.
 * @param address	Address of the peer to add into nodes list.
 *
 *
 * @see p2p_add_peers
 */

void p2p_add_peers(p2p_ctx *ctx,char* address);
void p2p_add_peers_op(p2p_ctx *ctx,char* address,int option);
void p2p_add_peers(p2p_ctx *ctx,const char* address);
void p2p_add_peers_op(p2p_ctx *ctx,const char* address,int option);


void p2p_remove_peer(p2p_ctx *ctx,const char* address);
void p2p_remove_peer_ptr(p2p_ctx *ctx,peer_t *p);


void p2p_reg_message_handle(p2p_ctx *ctx,p2p_message_handle func);


/**
 * Query the p2p context for internal stats.
 * @param ctx		Context record of the p2p server that is to be operated on.
 * @param stat_str	Name of the stat to lookup.
 *
 * @return char* string of the result
 * @see p2p_get_stat
 */

char* p2p_get_stat(p2p_ctx *ctx,char* stat_str);
//void p2p_get_stat(p2p_ctx *ctx,char* stat_str,char* reply);



/**
 * Query the p2p context for internal stats.
 * @param ctx		Context record of the p2p server that is to be operated on.
 * @param return_string	ptr to memort that will store the address that p2p_ctx is bound to.
 *
 * @see p2p_details_get_address
 */
void p2p_details_get_address(p2p_ctx *ctx,char* return_string);

#ifdef __cplusplus
}
#endif

#endif
