#include<stdio.h>// for standard input and output
#include<stdlib.h>
#include<string.h>// for manipulation of char array
#include<unistd.h> // for write, exit , close.
#include<sys/socket.h>// for making the socket
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>//for inet_addr

#define SIZE 1024
#define PORT 8080

int main(){
	int sockfd, newsockfd, ret;
	struct sockaddr_in serverAddr;

	int newSocket;
	struct sockaddr_in newAddr;

	socklen_t addr_size;
	char buffer[1024];
	pid_t childpid;

	//Creating the Tcp protocol socket:
	sockfd = socket(AF_INET,SOCK_STREAM ,0);
	if(sockfd < 0){
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Server Socket is created.\n");

	memset(&serverAddr , '\0' , sizeof(serverAddr));
	//Set port and ip:
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	//Binding the socket
	ret = bind(sockfd,(struct sockaddr*)&serverAddr,sizeof(serverAddr));

	if(ret < 0){
		printf("[-]Error in binding.\n");
		exit(1);
	}

	printf("[+]Bind to port %d\n",8080);
	//Listening to port
	if(listen(sockfd,10) == 0){
		printf("[+]Listening ......\n");
	}else{
		printf("[-]Error in binding.\n");
	}

	while(1){
		newSocket = accept(sockfd,(struct sockaddr*)&newAddr,&addr_size);
		if(newSocket < 0){
			exit(1);
		}

		printf("Connection accepted from %s:%d\n",inet_ntoa(newAddr.sin_addr),ntohs(newAddr.sin_port));

		if((childpid = fork()) == 0){
			close(sockfd);

			while(1){
				recv(newSocket,buffer,1024,0);
				if(strcmp(buffer,":exit") == 0){
					printf("Disconnected from %s:%d\n",inet_ntoa(newAddr.sin_addr),ntohs(newAddr.sin_port));
					break;
				}else{
					printf("Client: %s\n",buffer);
					send(newSocket,buffer,strlen(buffer),0);
					//Bzero used to erase the given memory area with zero bytes
  					//takes two arguments, the starting address of the memory region and 
  					//the number of bytes that need to be zeroed out. 
					bzero(buffer , sizeof(buffer));
					int rv = recv(newsockfd,buffer,1024,0);

					buffer[rv] = '\0';
					printf("%s",buffer);
				}
			}
		}
	}
	close(newSocket);
	return 0;
}