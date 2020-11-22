#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
 int socket_desc, new_socket,c;
 struct sockaddr_in server, client;
 char message[2000]= "Im server!", buffer[2000]= {0};
 int port= 8000;

 //Create socket
 socket_desc = socket(AF_INET,SOCK_STREAM,0);
 if(socket_desc == -1)
 {
  printf("Could not create socket");
 }
 
 puts("Successfully create socket.");

 //Prepare the sockaddr_in structure
 server.sin_family = AF_INET;
 server.sin_addr.s_addr = INADDR_ANY;//Ip address client server VM
 server.sin_port = htons(port);

 
 //Bind
 if(bind(socket_desc,(struct sockaddr *)&server,sizeof(server)) < 0)
 {
  perror("bind failed\n");
 }
 else
 {
  printf("Bind success dengan port %d\n",port);
 }

 if(listen(socket_desc,3)<0)
 {
  puts ("Listen failed");
 }

 puts("Listen success");

 //Accept and incoming connection
 puts("waiting for connection.......");
 c= sizeof(struct sockaddr_in);
 
 while(new_socket = accept(socket_desc,(struct sockaddr *)&client,(socklen_t*)&c))
 {
  printf("accepting........\n");
  printf("Ayat dia:");

  send(new_socket,message,2000,0);

  recv(new_socket,buffer,2000,0);
  printf("message from client: %s\n",buffer);
 }
 if(new_socket<0)
 {
   puts("accept success");
 }
 close(socket_desc);
 return 0;
}
