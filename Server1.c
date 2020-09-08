#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8888

int main(int argc, char const *argv[])
{
    int server_fd, new_socket, p;
    struct sockaddr_in address;
    int opt = 1,ch,length,i;
    int addrlen = sizeof(address);
    char sentence[1024];
	  
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
	printf("Socket Created Successfully !! \n");
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
      
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
	
    if (listen(server_fd, 3) < 0)
    {
        perror("listen failed..");
        exit(EXIT_FAILURE);
    }
	
	printf("Server is waiting for client to connect..\n");
	
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&addrlen))<0)
    {
        perror("accept error..");
        exit(EXIT_FAILURE);
    }
	
	printf("Connection establised !! \n");
    p = read(new_socket, sentence, 1024, 0);
	printf("Sentence from Client : %s ", sentence);
	
	ch=fork();
	
	if(ch==0)
	{
		printf("Child created successfully..\nThis Child will convert sentence into Upper Case.\n");
		
		length=strlen(sentence);
		
		for(i=0;i<length;i++) {
		  sentence[i] = toupper(sentence[i]);
        }
	
		send(new_socket , sentence , strlen(sentence) , 0 );
		exit (0);
	}
	    
    return 0;
}