#include<stdio.h>// for standard input and output
#include<stdlib.h>
#include<netdb.h>
#include<sys/types.h>
#include<arpa/inet.h>//for inet_addr

int main()
{
	int i;
	char host[80];
	struct hostent *he;
	struct in_addr addr;
	
	printf("Enterthe host-name:\n");
	gets(host);
	he = gethostbyname(host);
	if(he== NULL){
		printf("The address cannot be resolved at this time.\n");
		exit(1);
	}
	//printing the Ip and host name:
	printf("Official name is %s\n",he->h_name);
	printf("IP address %s\n",inet_ntoa(*(struct in_addr*)he->h_addr));
	return 0;
}