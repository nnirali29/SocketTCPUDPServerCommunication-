#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8888

void *TCPserver(void *message);
void *UDPserver(void *message);

int main(int c, char *argv[])
{
  char message[100];
  printf("\n Enter sentence: ");
  fgets(message, 100, stdin);
  pthread_t tcpth,udpth;
  pthread_create(&tcpth,NULL,&TCPserver,message);
  pthread_create(&udpth,NULL,&UDPserver,message);
  sleep(5);
  return 0;

}

void *TCPserver(void *message)
{

    int sock;
    struct sockaddr_in server;
    char server_reply[2000];
    char *sentence = message;
    
     
    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        printf("Socket couldn't created");
    }
    puts("Socket created");
     
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
 
    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connection failed ");
        return 1;
    }
     
    puts("Connected\n");
       send(sock, sentence, strlen(sentence), 0); 
        //Receive a reply from the server
        if( recv(sock , server_reply , 2000 , 0) < 0)
        {
            puts("recv failed");
        }
        puts("Capitalized sentence from Server :");
        puts(server_reply);
    close(sock);
    return 0;
  }


  void *UDPserver(void *message)
  {
  int clientSocket, portNum, nBytes; 
  struct sockaddr_in serverAddr;
  socklen_t addr_size;

  /*Create UDP socket*/
  clientSocket = socket(PF_INET, SOCK_DGRAM, 0);

  /*Configure settings in address struct*/
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(PORT);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  /*Initialize size variable to be used later on*/
  addr_size = sizeof serverAddr;

    char *sentence = message;
    nBytes = strlen(sentence) + 1;
    
    /*Send message to server*/
    sendto(clientSocket,sentence,nBytes,0,(struct sockaddr *)&serverAddr,addr_size);

    /*Receive message from server*/
    nBytes = recvfrom(clientSocket,sentence,1024,0,NULL, NULL);

    printf("reversed sentence received from server: %s\n",sentence);
    return 0;
  }

  

