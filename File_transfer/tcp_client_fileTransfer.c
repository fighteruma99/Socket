#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#define SIZE 1024

  void send_file(FILE *fp,int sockfd){
  int n;
  char data[SIZE]={0};
  
  //Error checking in sending of file
  while(fgets(data,SIZE,fp)!=NULL){
  if(send(sockfd,data,sizeof(data),0)==-1){
  perror("[-]Error in sending file.");
  exit(1);
  }
  //Bzero used to erase the given memory area with zero bytes
  //takes two arguments, the starting address of the memory region and 
  //the number of bytes that need to be zeroed out. 
  bzero(data,SIZE); 
  }
  }

 int main(){
  //setting ip and port address
  char*ip ="127.0.0.1";
  int port = 8080;
  int e;

 //Creating socket 
 int sockfd;
 struct sockaddr_in server_addr;
 FILE *fp;
 char*filename="send.txt";

 //Selecting the TCP protocol for socket protocol.
 sockfd =socket(AF_INET, SOCK_STREAM,0);
 if(sockfd<0){
 perror("[-]Error in socket");
 exit(1);
 }
 printf("[+]Server socket created successfully.\n");
 // assign IP, PORT
 server_addr.sin_family=AF_INET;
 server_addr.sin_port=port;
 server_addr.sin_addr.s_addr=inet_addr(ip);
 e=connect(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
 if(e==-1){
  perror("[-]Error in socket");
  exit(1);
  }
    printf("[+]Connected to Server.\n");
    fp=fopen("sample.txt","r");
    if(fp==NULL){
        perror("[-]Error in reading file.");
        exit(1);
  }
  //Using send_file function for sending file.
   send_file(fp,sockfd);
   printf("[+]File data sent successfully.\n");
          
           printf("[+]Closing the connection.\n");
        close(sockfd);

   return 0;
}
