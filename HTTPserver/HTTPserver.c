#include <stdio.h>
#include  <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

int main(){
	FILE *fp;//html data
	fp = fopen("default.html","r");//opening file "index.html" in read mode
	//fp holds the address of index.html
	char response_data[1024];
	fgets(response_data,1024,fp);//reading 1024 bytes from fp index.html and storing in response_data

	char http_header[2048]="HTTP/1.1 200 OK\r\n\n";
	strcat(http_header, response_data);

	//create a socket
	int server_socket;
	server_socket=socket(AF_INET,SOCK_STREAM,0);

	//setting up address for server socket;
	struct sockaddr_in server_addr;
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(8080);
	server_addr.sin_addr.s_addr=INADDR_ANY;

	bind(server_socket,(struct sockaddr*)&server_addr, sizeof(server_addr));

	listen(server_socket,5);

	int client_socket;
	while(1){
		client_socket=accept(server_socket,NULL,NULL);
		send(client_socket, http_header, sizeof(http_header),0);
		close(client_socket);
	}
	
	return 0;
}