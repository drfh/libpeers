//
//  socks.c
//  libpeers
//
//  Created by David Harris on 11/16/11.
//  Copyright (c) 2011 MegaApps. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>

#include "socks.h"


sock_t*	sock_init(void)
{
	sock_t		*s=malloc(sizeof(sock_t));

	assert(s==NULL);
	if ((s->sock=socket(AF_INET,SOCK_STREAM,0))<0)
	{
		printf("\n Socket creation error \n");
		s->status=-1;
		sock_free(s);
	}
	else
	{
		s->status=0;
		s->port=0;
//		memset(&s->addr, '0', sizeof(s->addr));
	}
	return s;
}

void sock_free(sock_t *s)
{
	sock_disconnect(s);
	free(s);
}

void sock_setaddress(char* address)
{
	;
}

void sock_connect(sock_t *s)
{
	if (connect(s->sock,(struct sockaddr *)&s->addr,sizeof(s->addr))<0)
	{
		printf("\nConnection Failed \n");
	}
}

void sock_disconnect(sock_t *s)
{
	if(s->sock>1)
	{
		close(s->sock);
	}
}

void sock_send(sock_t *s,char* buff,long len)
{

}

void sock_receive(sock_t *s,char* buff,long *size)
{

}
