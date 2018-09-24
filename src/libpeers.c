//
//  libpeers.c
//  libpeers
//
//  Created by David Harris on 11/16/11.
//  Copyright (c) 2011 MegaApps. All rights reserved.
//

#include "global.h"
#include "libpeers.h"

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <stdbool.h>

#include <netdb.h>

#include <assert.h>
#include <errno.h>

#include <pthread.h>
#include <sched.h>
#include <unistd.h>


/** Private declarations **/
void libpeers_default_handle_message(p2p_ctx* ctx,message_t* m,node_t* n);
void *p2p_main_loop(void* arg1);

/** end **/


p2p_ctx* p2p_init(char* ip_bind,uint32_t port)
{
	p2p_ctx		*ctx=malloc(sizeof(p2p_ctx));

	if(ctx!=NULL)
	{
		pthread_mutex_init(&ctx->mutex,NULL);
		ctx->peers=arraylist_new(20);
		ctx->handler=libpeers_default_handle_message;
		ctx->port=port;
		ctx->s=sock_init(AF_INET,SOCK_DGRAM,0);
		ctx->packet_size=kKB4;

	//	sock_setaddress(ctx->s,ip_bind);
		sock_setaddress_var(ctx->s,ctx->port,htonl(INADDR_ANY));
	//	int		opt=1;
	//	sock_setopt(ctx->s,SOL_SOCKET,SO_REUSEADDR,&opt,1);
	//	sock_setopt(ctx->s,SOL_SOCKET,SO_REUSEPORT,&opt,1);

//		struct timeval timeout={1,0};
//		timeout.tv_sec = 1;
//		timeout.tv_usec = 0;
//		sock_setopt(ctx->s,SOL_SOCKET,SO_RCVTIMEO,&timeout,sizeof(timeout));
		ctx->status=0;
	}
	return ctx;
}

void p2p_free(p2p_ctx *ctx)
{
	if(ctx!=NULL)
	{
		int		thread_status=0;

		pthread_mutex_lock(&ctx->mutex);
		ctx->status=0;
		pthread_mutex_unlock(&ctx->mutex);
		thread_status=pthread_join(ctx->tid,NULL);
		printf("thread joined with status: %d\n",thread_status);
		if(ctx->peers!=NULL)
		{
			arraylist_free(ctx->peers);
		}
		pthread_mutex_destroy(&ctx->mutex);
		free(ctx);
	}
}



void p2p_start(p2p_ctx *ctx)
{
	/* check to see that we can create listen socket */
	if(ctx->s==NULL)
	{
		perror("Cannot create socket");
		exit(1);
	}

	/* Now bind to the socket	*/
	sock_bind(ctx->s);
	if(ctx->s==NULL)
	{
		perror("Cannot bind to the socket");
		exit(1);
	}

//	peer_t	*peer=NULL;

	ctx->status=1;
	pthread_create(&ctx->tid,NULL,p2p_main_loop,ctx);
}

void *p2p_main_loop(void* arg1)
{
	p2p_ctx 	*ctx=(p2p_ctx*)arg1;
//	sock_t		*peer_sock;
	char		*buff=NULL;
	size_t		buff_size=0;
	bool		local_test=true;
	message_t	*m=NULL;

	buff=malloc(kKB(ctx->packet_size));
	while(local_test==true)
	{
		pthread_mutex_lock(&ctx->mutex);
		if(ctx->status!=1)
			local_test=false;

		buff_size=0;
		bzero(buff,ctx->packet_size);

		pthread_mutex_unlock(&ctx->mutex);

	//	peer_sock=sock_accept(ctx->s);

	//	sock_receive(ctx->s,buff,&buff_size);
		sock_receive_packet(ctx->s,buff,&buff_size);
		m=message_parse_packet(buff,buff_size);
		if(m!=NULL)
		{
			printf("message received:(%ld) \n",m->len);
			ctx->handler(ctx,m,NULL);
		/*	if(peer_sock!=NULL)
			{
				printf("peer_sock: %p  \n",peer_sock);
				sock_free(peer_sock);
			}
			else
			{
				printf("sock_accept returned NULL peer.\n");
			}
		*/
		}
	//	if(peer_sock!=NULL)
	//		free(peer_sock);
		if(sched_yield())
			fprintf(stderr,"sched_yield returned non -1: errno=%d\n",errno);
	}
	free(buff);
	return NULL;
}


void p2p_remove_peer(p2p_ctx *ctx,const char* address)
{
	;
}

void p2p_remove_peer_ptr(p2p_ctx *ctx,peer_t *p)
{
	;
}


void p2p_receive_message(sock_t s)
{
	;
}

void p2p_add_peers(p2p_ctx *ctx,const char* address)
{
//	fprintf(stderr,"add_peer: %s\n",address);
	p2p_add_peers_op(ctx,address,kOneTry);
}

void p2p_add_peers_op(p2p_ctx *ctx,const char* address,int option)
{
	peer_t	*peer=NULL;
	int			port=8321;
	char		host[256];
	int			succ_parsing=0;

	if(sscanf(address,"%99[^:]:%i[^\n]",host,&port)==2)
	{
		succ_parsing=1;
	}
	else if(sscanf(address,"%99[^\n]",host)==1)
	{
		succ_parsing=1;
	}
	else
	{
		fprintf(stderr,"%s(%d): failed to get host name\n",__FUNCTION__,__LINE__);
	}

	if(succ_parsing==1)
	{
		struct hostent *server=NULL;

		server=gethostbyname(host);
		assert(ctx!=NULL);
		assert(address!=NULL);

		peer=malloc(sizeof(peer_t));
		bzero((char*)peer,sizeof(peer_t));
		peer->retries=1;
		peer->status=0;

		peer->addr.sin_family = AF_INET;
		peer->addr.sin_addr.s_addr = htonl(INADDR_ANY);

		bcopy((char *)server->h_addr,(char *)&peer->addr.sin_addr.s_addr, server->h_length);
		peer->addr.sin_port=htons(port);

//		if(g.verbose)
//			printf("adding peer: %s   %d\n",host,port);
		arraylist_append(ctx->peers,peer);
	}
	else
		fprintf(stderr,"Failed to parse peer\n");
}

void p2p_reg_message_handle(p2p_ctx *ctx,p2p_message_handle func)
{
	ctx->handler=func;
}

char* p2p_get_stat(p2p_ctx *ctx,char* stat_str)
{
	char		*ret=malloc(128);

	if(strcmp(stat_str,"IP Address")==0)
	{
		sprintf(ret,"127.0.0.1");
	}
	else if(strcmp(stat_str,"PORT")==0)
	{
		sprintf(ret,"%d",ctx->port);
	}
	else if(strcmp(stat_str,"Number Of Peers")==0)
	{
		sprintf(ret,"%d",ctx->peers->length);
	}
	return ret;
}

void libpeers_default_handle_message(p2p_ctx* ctx,message_t* m,node_t* n)
{
	printf("libpeers_default_handle_message: called\n");
	printf("message: %s\n",m->buff);

}
