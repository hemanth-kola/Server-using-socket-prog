#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
int main(){
// open a file to store
FILE *html_data;
html_data = fopen("index.html","r");
char buffer[128];
char response_data[1024] = {'\0'}; // Initialise to '\0' so that there's no garbage values since we will
 // append to end of this string


while(fgets(buffer,sizeof(buffer),html_data)) // For a multi-line HTML file
{
strcat(response_data,buffer);
}
char http_header[2048] = "HTTP/1.1 200 OK \r\n\n";
char http_request1[2048] = "";
strcat(http_header,response_data);
// create a socket
int server_socket;
server_socket = socket(AF_INET,SOCK_STREAM,0);
//define the address
struct sockaddr_in server_address;
server_address.sin_family = AF_INET;
server_address.sin_port = htons(8080);
server_address.sin_addr.s_addr = INADDR_ANY;
bind(server_socket,(struct sockaddr *)&server_address, sizeof(server_address));
listen(server_socket,5);
int client_socket;
while(1){
printf("\nWaiting for new connection\\n\n");
client_socket = accept(server_socket,NULL,NULL);
send(client_socket,http_header,sizeof(http_header),0);
close(client_socket);

 }
return 0;
}