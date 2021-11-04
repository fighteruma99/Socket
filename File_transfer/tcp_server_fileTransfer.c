#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>

#define SIZE 1024

  void write_file(int sockfd){
  int n;
  FILE*fp;
  char*filename="recv.txt";
  char buffer[SIZE];

  //Opening the file
  fp =fopen(filename,"w");
  while(1){
  n =recv(sockfd,buffer,SIZE,0);
  if(n<=0){
   break;
   return;
  }
  fprintf(fp,"%s",buffer);
  //Bzero used to erase the given memory area with zero bytes
  //takes two arguments, the starting address of the memory region and 
  //the number of bytes that need to be zeroed out. 
  bzero(buffer,SIZE);
  }
  return;
 }


  int main(){
  //setting ip and port address
  char*ip ="127.0.0.1";
  int port =8080;
  int e;
  //Creating socket 
  int sockfd,new_sock;
  struct sockaddr_in server_addr, new_addr;
  socklen_t addr_size;
  char buffer[SIZE];
  //Selecting the TCP protocol for socket protocol.
  sockfd=socket(AF_INET,SOCK_STREAM,0);
  if(sockfd<0){
  perror("[-]Error in socket");
  exit(1);
  }
  printf("[+]Server created successfully.\n");
  // assign IP, PORT
  server_addr.sin_family =AF_INET;
  server_addr.sin_port =port;
  server_addr.sin_addr.s_addr=inet_addr(ip);
  e =bind(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
  if(e<0){
  perror("[-]Error in bind");
  exit(1);
  }
  printf("[+]Binding successfull.\n");
  if(listen(sockfd,10)==0){
    printf("[+]Listening...\n");
    }
 else{
   perror("[-]Error in Listening");
   exit(1);
 }
    addr_size =sizeof(new_addr);
    new_sock=accept(sockfd,(struct sockaddr*)&new_addr,&addr_size);
    //Writing a new file.
    write_file(new_sock);
    printf("[+]Data written in the file successfully.\n ");
    return 0;
}

