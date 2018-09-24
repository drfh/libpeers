//
//  message.h
//  libpeers
//
//  Created by David Harris on 9/17/18.
//  Copyright (c) 2018 MegaApps. All rights reserved.
//

#ifndef libpeers_messagequeue_h
#define libpeers_messagequeue_h

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <string.h>

#include "util/arraylist.h"
//#include "message.h"


struct messagequeue_s
{
	long		status;
	int			resend_timeout;

	ArrayList	*out;
	ArrayList	*in;
};

typedef	struct messagequeue_s	messagequeue_t;

/**
 * Allocate and initialize a messagequeue_t* pointer.
 * @return			Returnes a pointer to memory allocated with the size of the message_s
 *					initializes ->status = 0;
 *					initializes ->buff = NULL;
 *					initializes ->len = 0;
 *
 * @see messagequeue_init
 */
messagequeue_t* message_queue_init(void);


/**
 * Frees the messagequeue_t* pointer.
 * @param	m	The message record
 * @see messagequeue_free
 */
void message_queue_free(messagequeue_t *m);



#ifdef __cplusplus
}
#endif

#endif
