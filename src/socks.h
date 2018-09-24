//
//  socks.h
//  libpeers
//
//  Created by David Harris on 11/16/11.
//  Copyright (c) 2011 MegaApps. All rights reserved.
//

#ifndef libpeers_socks_h
#define libpeers_socks_h

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>

struct sock_s
{
	struct sockaddr_in	addr;
	uint32_t			port;
	int					sock;

	int					status;
};

typedef	struct sock_s	sock_t;

/**
 * Allocate and initialize a sock_t* pointer.
 * @param domain	(default: AF_INET)
 * @param type		(default: SOCK_DGRAM)
 * @param protocol	(default: 0)
 * @return			A new arraylist, or NULL if it was not possible
 *
 * @see sock_init
 */
sock_t*	sock_init(int domain,int type,int protocol);

sock_t*	sock_init_udp(void);


/**
 * Disconnect the socket from it's remote connection and frees the memory.
 *
 * @param s		sock_t* of a sock that was created by sock_init
 *				.
 * @see sock_free
 */
void sock_free(sock_t *s);


/**
 * Sets the socket record to the address and port.
 *
 * @param s			Non-NULL sock_t*
 * @param port		port of the socket
 * @param addr		IP address of the socket to open.
 *					Can have a :port_number at the end if the string.
 * @see sock_setaddress
 */
void sock_setaddress_var(sock_t *s,int port,uint32_t addr);


/**
 * Sets the socket record to the address and port.
 * Note: calls sock_setaddress_var(sock_t,uint16_t,char*)
 *
 * @param s			Non-NULL sock_t*
 * @param address	String address of the remote host to connect to.
 *					Can accept ip, and dns host names.
 *					Can have a :port_number at the end if the string.
 * @see sock_setaddress
 */
void sock_setaddress(sock_t *s,char* address);
void sock_setopt(sock_t *s,int level,int opt_name,void* optval,socklen_t option_len);

void sock_connect(sock_t *s);
void sock_disconnect(sock_t *s);

void sock_bind(sock_t *s);

sock_t* sock_accept(sock_t *s);


void sock_send(sock_t *s,char* buff,long size_t);

void sock_receive_packet(sock_t *s,char* buff,size_t *size);
void sock_receive(sock_t *s,char* buff,size_t *size);

char* sock_getaddress(sock_t *s);


#ifdef __cplusplus
}
#endif

#endif
