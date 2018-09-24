//
//  message.c
//  libpeers
//
//  Created by David Harris on 9/17/18.
//  Copyright (c) 2018 MegaApps. All rights reserved.
//

#include "message.h"

#include <stdio.h>
#include <assert.h>
#include "bencode.h"

/* Internal Private functions*/
message_t* _message_parse_packet_v1(char* buff,size_t buff_size);

/* END Internal Private functions*/



message_t* message_init(void)
{
	message_t		*m=NULL;

	m=malloc(sizeof(message_t));
	assert(m!=NULL);
	m->buff=NULL;
	m->len=0;
	m->status=0;
	m->root=be_alloc(DICT);

	return m;
}


void message_free(message_t *m)
{
	if(m!=NULL)
	{
		free(m->buff);
		be_free(m->root);
		free(m);
	}
	else
		assert(m==NULL);
}


message_t* message_parse_packet(char* buff,size_t buff_size)
{
	message_t		*m=NULL;

	if(buff!=NULL&&buff_size>0)
	{
		if(buff[0]==1)
			m=_message_parse_packet_v1(buff,buff_size);
//		m->buff=buff;
		m->len=buff_size;


		m->status=1;
	}
	else
	{
		assert(buff!=NULL);
	}
	return	 m;
}

message_t* _message_parse_packet_v1(char* buff,size_t buff_size)
{
	message_t		*m=NULL;
	long			offset=1;

	m=message_init();
	if(m!=NULL)
	{
		/* Parse the  */
		char	*C_UUID=malloc(16);

		memcpy(C_UUID,buff+offset,16);
	}
	return m;
}


void message_create_packet(message_t *m,char* buff,size_t *buff_len)
{
//	char*		b=NULL;

	if(m!=NULL)
	{
		be_dict_add_num(m->root,"version",1);
		be_dump(m->root);
	}
}
