#include <stdio.h>
#include <unistd.h>
#include <string.h> //usesd for bzero();
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

struct sockadder_in
{
    short sin_family; //must be AF_UNIX
    u_short sin_port;
    struct in_addr sin_addr;
    char sin_zero[8]; //not used, must be 0
};

void error(char* msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno, n;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr; //sockaddr_in contains internet address
    socklen_t clilen;

    if(argc < 2)
    {
        fprintf(stderr,"ERROR, no port provided");
        exit(1);
    }

    sockfd = socket(AF_UNIX, SOCK_STREAM, 0); //Must use UNIX on unix machine //AF_INET for internet machines
    if (sockfd < 0) 
        error((char*)"ERROR opening socket"); //passes the port number which the server accepts connections as an argument aka sockfd

    bzero((char*) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);

    serv_addr.sin_family = AF_UNIX;
    serv_addr.sin_port = htons(portno);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
        error((char*)"ERROR on binding"); //error field

    listen (sockfd,5); //listens on the socket for connections listen(filedescriptor, sizeof(backlogqueue));

    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr*) &cli_addr, &clilen); // change from clilen to add (socklen_t*)
    if (newsockfd < 0)
        error((char*)"ERROR on accept");

    bzero(buffer, 256);
    n = read(newsockfd, buffer, 255);
    if (n < 0) error((char*)"ERROR reading from socket");
    printf("Here is the message: %s", buffer);

    n = write(newsockfd, "I got your message", 18);
    if(n < 0)
        error((char*)"ERROR writing to socket");

    close(newsockfd);
    close(sockfd);

    return 0;
}