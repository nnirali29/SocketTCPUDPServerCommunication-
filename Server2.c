#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#define PORT 8888

int main(){
	
	struct sockaddr_in myaddr;	
	struct sockaddr_in remaddr;	
	socklen_t addrlen = sizeof(remaddr);		
	int udpSocket;			
	
int length,i,ch;
char sentence[1024],reverse[1024];
struct sockaddr_storage serverStorage;
socklen_t addr_size;


udpSocket = socket(PF_INET, SOCK_DGRAM, 0);
printf("Socket Created Successfully !! \n");


	memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	myaddr.sin_port = htons(PORT);

	if (bind(udpSocket, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
		perror("bind failed");
		return 0;
	}
	
	printf("Server is waiting for client..\n");
	
	
addr_size = sizeof serverStorage;

length = recvfrom(udpSocket,sentence,1024,0,(struct sockaddr *)&serverStorage, &addr_size);

ch=fork();

if(ch==0)
{
	printf("Child created successfully..\nThis Child will convert sentence into reverse order.\n");
	int x = strlen(sentence);
	x = x-1;
	for(i=0;i<length-1;i++)
    {

      reverse[i] = sentence[x];

        x = x-1;
    }
	sendto(udpSocket,reverse,length,0,(struct sockaddr *)&serverStorage,addr_size);
	exit (0);

}

return 0;
}