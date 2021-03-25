#include <stdio.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h> //usesd for bzero();
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

struct hostent
{
    char *h_name; //official name of host
    char **h_aliases; //alias list
    int h_addtrype; //host address type
    int h_length; //length of the address
    char **h_addr_list; //list of addressses from name server
    #define h_addr , h_addr_list[0] //address for backwards compatibility
};

void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    struct hostent *gethostbyname(char *name);

    char buffer[256];
    if (argc < 3)
    {
        fprintf(stderr, "usage %s hostname port", argv[0]);
        exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sockfd < 0)
        error((char*)"ERROR opening socket");

    server = gethostbyname(argv[1]);
    if(server == NULL)
    {
        fprintf(stderr, "ERROR, no such host");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_UNIX;
    bcopy((char *)server->h_addr_list, //h_addr_list instead of h_addr
          (char*)&serv_addr.sin_addr.s_addr, 
          server->h_length);
    serv_addr.sin_port = htons(portno);

    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) //add (struct sockaddr *) to &serv_addr
        error((char*)"ERROR connecting");

    printf("Please enter the message: ");
    bzero(buffer, 256);
    fgets(buffer, 255, stdin);
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0)
        error((char*)"ERROR writing to socket");
    bzero(buffer,256);
    n = read(sockfd, buffer, 255);
    if (n < 0)
        error((char*)"ERROR reading from socket");
    printf("%s", buffer);

    return 0;
}