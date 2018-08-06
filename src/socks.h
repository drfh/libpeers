//
//  socks.h
//  libpeers
//
//  Created by David Harris on 11/16/11.
//  Copyright (c) 2011 MegaApps. All rights reserved.
//

#ifndef libpeers_socks_h
#define libpeers_socks_h

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


sock_t*	sock_init(void);
void sock_free(sock_t *s);

void sock_setaddress(char* address);

void sock_connect(sock_t *s);
void sock_disconnect(sock_t *s);

void sock_send(sock_t *s,char* buff,long len);

void sock_receive(sock_t *s,char* buff,long *size);



#endif
