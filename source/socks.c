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
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/errno.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include "socks.h"

/* Internals (Private) */
void sock_send_safe(sock_t *s,char* buff,long len);

/* Internals end */


/*
sock_t*	sock_new(int domain,int type,int protocol)
{
	sock_t		*s=malloc(sizeof(sock_t));

	return ;
}
*/
sock_t*	sock_init(int domain,int type,int protocol)
{
	sock_t		*s=malloc(sizeof(sock_t));

//	printf("socket: %p\n",s);
//	assert(s==NULL);
	if((s->sock=socket(domain,type,protocol))<0)
	{
		printf("\n Socket creation error \n");
		s->status=-1;
		sock_free(s);
	}
	else
	{
		s->status=0;
		s->port=0;
	//	printf("socket: %d\n",s->sock);
	}
	return s;
}

sock_t*	sock_init_udp(void)
{
	return sock_init(AF_INET,SOCK_DGRAM,0);
}

void sock_free(sock_t *s)
{
	sock_disconnect(s);
	free(s);
}

void sock_setaddress_var(sock_t *s,int port,uint32_t addr)
{
//	printf("sock_setaddress_var: %d\n",addr);
	/*	Validate the variables	*/
	if(s!=NULL&&port<=1024)
	{
		fprintf(stderr,"%s: send bad variables. (sock=NULL port=%d address=NULL)\n",__func__,port);
	}
	else
	{
		s->port=port;
		memset(&s->addr,0,sizeof(struct sockaddr_in));
		s->addr.sin_family=AF_INET;
		s->addr.sin_port=htons(port);
		s->addr.sin_addr.s_addr=addr;
	//	memset(&s->addr.sin_addr,&addr,sizeof(struct in_addr));
	}
}

void sock_setaddress(sock_t *s,char* address)
{

	/*	Parse Address	*/

//	short		port=8000;


//	sock_setaddress_var(s,port,"127.0.0.1");
}


void sock_setopt(sock_t *s,int level,int opt_name,void* optval,socklen_t option_len)
{
	if(s==NULL)
	{
		fprintf(stderr,"sock_setopt: sent NULL socket");
		exit(1);
	}
	int		ret;

	ret=setsockopt(s->sock,level,opt_name,(const void *)&optval,option_len);
	if(ret==-1)
	{
		printf("setsockopt: %d\n",errno);
		if(errno==EFAULT)
			printf("found it\n");
	}
}


void sock_connect(sock_t *s)
{
	if (connect(s->sock,(struct sockaddr *)&s->addr,sizeof(s->addr))<0)
	{
		fprintf(stderr,"\nConnection Failed \n");
	}
}

void sock_disconnect(sock_t *s)
{
	if(s->sock>1)
	{
		close(s->sock);
	}
}

void sock_bind(sock_t *s)
{
	if(bind(s->sock,(struct sockaddr *) &s->addr,sizeof(struct sockaddr_in))<0)
	{
		perror("Cannot bind to the socket");
		exit(1);
	}
}


sock_t* sock_accept(sock_t *s)
{
	int				err=0;
	socklen_t		addrlen=sizeof(struct sockaddr_in);
	struct sockaddr_in	fromAddr;
	sock_t*			sock=NULL;
	char		*buff;
	short		buff_size=0;

	buff=malloc(buff_size);
	printf("recvfrom\n");
//	fcntl(s->sock);
	err=recvfrom(s->sock,buff,buff_size,0,(struct sockaddr*)&fromAddr,&addrlen);
	if(err>0)
	{
		buff_size=err;
		printf("packet(%s:%d): %p %d\n",inet_ntoa(fromAddr.sin_addr),ntohs(fromAddr.sin_port),buff,addrlen);
		sock=sock_init_udp();
		sock->addr=fromAddr;
		sock->port=fromAddr.sin_port;

		printf("message: %s\n",buff);
	}
	else if(err<0)
	{
		printf("Timout reached\n");
	}
	else
		printf("%s(%d): Error was 0\n",__func__,__LINE__);
	return sock;
}

void sock_send(sock_t *s,char* buff,long len)
{
	if(s!=NULL)
		if(len>0)
			if(buff!=NULL)
				sock_send_safe(s,buff,len);
			else
				printf("%s(%d) buffer pointer was NULL\n",__func__,__LINE__);
		else
			printf("%s(%d) length %ld is not an option\n",__func__,__LINE__,len);
	else
		printf("%s(%d) sock pointer was NULL\n",__func__,__LINE__);
}

/* Internal */
void sock_send_safe(sock_t *s,char* buff,long len)
{
	ssize_t		count=0;

	count=send(s->sock,(void*)buff,(size_t)len,0);
	if(count==0)
	{
		assert(count==0);
	}

}

void sock_receive_packet(sock_t *s,char* buff,size_t *size)
{
	;
}



void sock_receive(sock_t *s,char* buff,size_t *size)
{
	int				err=0;
	socklen_t		addrlen=sizeof(struct sockaddr_in);
	struct sockaddr_in	fromAddr;
	sock_t*			peer=NULL;
//	char		*buff;
//	short		buff_size=0;

	buff=malloc(*size);
	printf("recvfrom\n");
//	fcntl(s->sock);
	err=recvfrom(s->sock,buff,*size,0,(struct sockaddr*)&fromAddr,&addrlen);

	if(err>0)
	{
		*size=(long)err;
		printf("packet(%s:%d): %p %d\n",inet_ntoa(fromAddr.sin_addr),ntohs(fromAddr.sin_port),buff,(int)*size);
		peer=sock_init_udp();
		peer->addr=fromAddr;
		peer->port=fromAddr.sin_port;

		printf("message: %s\n",buff);
	}
	else if(err<0)
	{
		printf("Timout reached: Resending segment\n");
	}
	else
		printf("%s(%d): Error was 0\n",__func__,__LINE__);
}

char* sock_getaddress(sock_t *s)
{
	char	*str_copy=NULL;
	char	*str=inet_ntoa(s->addr.sin_addr);

	if(str)
	{
		str_copy=malloc(strlen(inet_ntoa(s->addr.sin_addr)));
		strcpy(str_copy,inet_ntoa(s->addr.sin_addr));
	//	s->addr.sin_addr.s_addr;
	}
//	printf("address  %s\n",str_copy);
	return str_copy;
}
