//
//  messagequeue.c
//  libpeers
//
//  Created by David Harris on 9/17/18.
//  Copyright (c) 2018 MegaApps. All rights reserved.
//

#include "messagequeue.h"

#include <stdio.h>
#include <assert.h>
#include "bencode.h"

/* Internal Private functions*/

/* END Internal Private functions*/



messagequeue_t* message_queue_init(void)
{
	messagequeue_t		*mq=NULL;

	mq=malloc(sizeof(messagequeue_t));
	assert(mq!=NULL);
	mq->status=0;
	mq->resend_timeout=1000;
	mq->in=arraylist_new(64);
	mq->out=arraylist_new(64);
	return mq;
}


void message_queue_free(messagequeue_t *mq)
{
	if(mq!=NULL)
	{
		arraylist_free(mq->in);
		arraylist_free(mq->out);
		free(mq);
	}
	else
		assert(mq==NULL);
}
