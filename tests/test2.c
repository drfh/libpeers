//
//  test2.c
//  libpeers
//
//  Created by David Harris on 08/03/2018.
//  Copyright (c) 2018 MegaApps. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>

#include <errno.h>


#include <libpeers.h>


/** Defines **/
#define kDEFAULT_PORT		8321
#define	kNUM_PEER_TEST		10

/** Prototypes **/
void parse_args(int argc,char const *argv[]);
void handle_message(p2p_ctx* ctx,message_t *m,node_t* n);

struct global{
	bool	done;
	short	port;
	int		verbose;
};
struct	global		g;

void init_globals(void)
{
	g.done=false;
	g.port=8321;
	g.verbose=1;
}

int main(int argc,char const **argv)
{
	printf("Test 2 - v0.1\n");
	printf("libPeers\n");
	printf("-----------------\n");

	p2p_ctx		*ctx;
	int			i,j=kNUM_PEER_TEST;
	char		address[24];

	init_globals();

	printf("Parse args...\n");
	parse_args(argc,(const char **)argv);

	/*	Init a p2pctx instance	*/
	ctx=p2p_init("0.0.0.0",g.port);

	/* Register new handler for messages	*/
	p2p_reg_message_handle(ctx,handle_message);

	char	*string;

	string=p2p_get_stat(ctx,"IP Address");
	printf("IP Address: %s\n",string);
	free(string);

	string=p2p_get_stat(ctx,"Port Number");
	printf("Port: %s\n",string);
	free(string);

	/* Manualy add peers to try to cennect to	*/
	for(i=0;i<j;i++)
	{
		sprintf(address,"localhost:%d",kDEFAULT_PORT+i);
		p2p_add_peers(ctx,address);
	}

	/*	Start the server thread	*/
	p2p_start(ctx);

	char	command_str[256];
//	char	*args=NULL;
	do
	{
		printf("Command: ");
		fscanf(stdin,"%s",command_str);
		if(strcmp(command_str,"quit")==0||strcmp(command_str,"q")==0)
		{
			g.done=true;
		}
		else if(strcmp(command_str,"s")==0)
		{
			char	add[64];
			char	message[256];

			fscanf(stdin,"%s%s",add,message);
			printf("sending(%s): %s\n",add,message);
		}
		if(sched_yield())
			fprintf(stderr,"sched_yield returned non -1: errno=%d\n",errno);
	}while(g.done==false);

	printf("Cleanup...\n");
	p2p_free(ctx);
	printf("Exiting...\n");
	return 0;
}


void parse_args(int argc,char const *argv[])
{
	int c;
//	int digit_optind = 0;

//	int this_option_optind = optind ? optind : 1;
	int option_index = 0;
	static struct option long_options[] = {
		{"deamon", no_argument, 0, 'd'},
		{"name", required_argument, 0, 0},
		{"port", required_argument, 0, 'p'},
		{"verbose", no_argument, 0, 'v'},
		{0, 0, 0, 0}
	};

	while((c=getopt_long(argc,(char**)argv,"vdp:",long_options,&option_index))!=-1)
	{
	//	printf("optarg: %s\n",optarg);
	//	printf("argv[optind]: %s\n",argv[optind]);
	//	printf("optind: %d\n",optind);
	//	printf("------\n");
		switch(c)
		{
			case 0:
			//	printf("option %s @ %d\n",long_options[option_index].name,option_index);
				if(strcmp(long_options[option_index].name,"name")==0)
				{
					printf("name set to: %s\n",optarg);
				}
			//	printf("\n");
				break;
			case 'd':
				printf("deamon mode set to true\n");
				break;
			case 'p':
				g.port=atoi(optarg);
				if(g.port==0)
					printf("-p %s returned 0 so the default port will be used.\n",optarg);
				break;
			case '?':
				break;
			default:
				printf("?? getopt returned character code 0%o ??\n", c);
		}
	}
/*	if(argc>=2)
	{
		fprintf(stderr,"%s\n","error - Argument number not correct");
	}
*/
}

void handle_message(p2p_ctx* ctx,message_t *m,node_t* n)
{
	if(ctx!=NULL)
		printf("%s:(msg) %s\n",__FUNCTION__,m);
	else
		printf("%s: ctx == NULL\n",__FUNCTION__);
}
