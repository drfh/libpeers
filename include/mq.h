//
//  mq.h
//  libpeers
//
//  Created by David Harris on 9/17/18.
//  Copyright (c) 2018 MegaApps. All rights reserved.
//

#ifndef libpeers_mq_h
#define libpeers_mq_h

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <string.h>

#include "util/arraylist.h"
#include "node.h"
#include "message.h"


struct mq_m_s
{
	message_t	*m;
	ArrayList	*peers;
};

typedef	struct mq_m_s	mq_m_t;


struct mq_s
{
	long		status;
	int			resend_timeout;

	ArrayList	*out;
	ArrayList	*in;
};

typedef	struct mq_s	mq_t;

/**
 * Allocate and initialize a messagequeue_t* pointer.
 * @return			Returnes a pointer to memory allocated with the size of the message_s
 *					initializes ->status = 0;
 *					initializes ->buff = NULL;
 *					initializes ->len = 0;
 *
 * @see mq_init
 */
mq_t* mq_init(void);


/**
 * Frees the messagequeue_t* pointer.
 * @param	m	The message record
 * @see mq_free
 */
void mq_free(mq_t *mq);


void mq_publish(mq_t *mq,message_t *m,node_t *p);


void mq_add_in(mq_t *mq,message_t m);


void mq_add_out(mq_t *mq,message_t m);




#ifdef __cplusplus
}
#endif

#endif
