//
//  test1.c
//  libpeers
//
//  Created by David Harris on 08/03/2018.
//  Copyright (c) 2018 MegaApps. All rights reserved.
//

#include <stdio.h>
#include <libpeers.h>

int main(int argc,char const *argv[])
{
	printf("Test 1 - v0.1\n");
	printf("libPeers\n");
	printf("-----------------\n");

	p2p_ctx		*ctx;

	ctx=p2p_init("0.0.0.0",12300);

	p2p_add_peers(ctx,"localhost:12301");

	printf("Cleanup...\n");
	p2p_free(ctx);
	printf("Exiting...\n");
	return 0;
}
