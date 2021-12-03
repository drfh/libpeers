//
//  message.h
//  libpeers
//
//  Created by David Harris on 9/17/18.
//  Copyright (c) 2018 MegaApps. All rights reserved.
//

#ifndef libpeers_message_h
#define libpeers_message_h

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <string.h>
#include <util/bencode.h>

struct message_s
{
	long		status;
	char*		buff;
	size_t		len;
	int			resends;	/* nano seconds	*/
	be_node_t	*root;

	long		retain;
};

typedef	struct message_s	message_t;

/**
 * Allocate and initialize a sock_t* pointer.
 * @return			Returnes a pointer to memory allocated with the size of the message_s
 *					initializes ->status = 0;
 *					initializes ->buff = NULL;
 *					initializes ->len = 0;
 *
 * @see message_init
 */
message_t* message_init(void);


/**
 * Frees the allocated message record member variables and frees the message_t* pointer.
 * @param	m	The message record
 * @see message_free
 */
void message_free(message_t *m);


void message_retain(message_t *m);
void message_autorelease(message_t *m);
void message_release(message_t *m);

/**
 * Allocate and initialize a message_t* pointer.
 * @return			Returnes a pointer to memory allocated with the size of the message_s
 *					initializes ->status = 0;
 *					initializes ->buff = NULL;
 *					initializes ->len = 0;
 *
 * @see message_parse_packet
 */
message_t* message_parse_packet(char* buff,size_t buff_size);


/**
 * Create a buffer pointer of the flattened message
 * @param	m		The message record
 * @param	t		Topic of message
 * @param	buff	Buffer to store the encoded message
 * @param	buff_len	Size of the buffer in memory
 *
 * @see message_create_packet
 */
void message_create_packet(message_t *m,char* topic,char* buff,size_t *buff_len);

#ifdef __cplusplus
}
#endif

#endif
