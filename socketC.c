#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h> // inet_addr
#include <string.h>//strlen
#include <unistd.h>

int main(int argc,char *argv[])
{
 int socket_desc;
 struct sockaddr_in server;
 char *message, server_reply[2000];

 //Create socket
 socket_desc = socket(AF_INET,SOCK_STREAM,0);
 if(socket_desc == -1)
 {
  printf("Could not create socket\n");
 }
 puts("Created socket\n");

 server.sin_addr.s_addr = inet_addr("192.168.240.8");//IP address serverVM
 server.sin_family = AF_INET;
 server.sin_port = htons(8000);

 //Connet to remote server
 if(connect(socket_desc,(struct sockaddr*)&server,sizeof(server))<0)
 {
  puts("connect error");
  return 1;
 }

 puts("Connected");

 //Send some data
 message = "connect";
 if(send(socket_desc,message,strlen(message),0)<0)
 {
  puts("send data failed");
  return -1;
 }
 puts("Send data Successfully");

 //Receive a reply from server
 if(recv(socket_desc,server_reply,2000,0)<0)
 {
   printf("recv failed");
   return 1;
 }
 else
 {
  puts("Reply received\n");
 }
 printf("Reply from server: %s\n",server_reply);

 close(socket_desc);

 return 0;
}
