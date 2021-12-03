//
//  mq.c
//  libpeers
//
//  Created by David Harris on 9/17/18.
//  Copyright (c) 2018 MegaApps. All rights reserved.
//

#include "mq.h"

#include <stdio.h>
#include <assert.h>
#include "util/bencode.h"

/* Internal Private functions*/

/* END Internal Private functions*/



mq_t* mq_init(void)
{
	mq_t		*mq=NULL;

	mq=malloc(sizeof(mq_t));
	assert(mq!=NULL);
	mq->status=0;
	mq->resend_timeout=1000;
	mq->in=arraylist_new(64);
	mq->out=arraylist_new(64);
	return mq;
}


void mq_free(mq_t *mq)
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

void mq_publish(mq_t *mq,message_t *m,node_t *p)
{
	;
}
