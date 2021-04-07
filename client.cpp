#include <stdio.h>
#include <netdb.h> //used for struct hostent 
#include <unistd.h>
#include <string.h> //usesd for bzero();
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

/*struct hostent
{
    char *h_name; //official name of host
    char **h_aliases; //alias list
    int h_addtrype; //host address type
    int h_length; //length of the address
    char **h_addr_list; //list of addressses from name server
    #define h_addr, h_addr_list[0] //address for backwards compatibility
};*/

void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main()
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[256];
    string name;

    cout << "Please enter the server host name: ";
    cin >> name;
    const char* hostname = name.c_str();
    cout << "Please enter the port number: ";
    cin >> portno;

    if(portno < 1024 || portno > 65535)
    {
        cout << "ERROR: Please enter a port number above 1024." << endl;
    }

    //portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error((char*)"ERROR opening socket");

    server = gethostbyname(hostname);
    if(server == NULL)
    {
        fprintf(stderr, "ERROR, no such host");
        exit(0);
    }
    cin.ignore();
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_UNIX;
    bcopy((char *)server->h_addr,
          (char*)&serv_addr.sin_addr.s_addr, 
          server->h_length);
    serv_addr.sin_port = htons(portno);

    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) //add (struct sockaddr *) to &serv_addr
        error((char*)"ERROR connecting");

    printf("Please enter a Zodiac sign: ");
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

    //server enhancements

    /*while(true)
    {
        newsockfd = accept(sockfd, (struct sockaddr*) &cli_addr, (socklen_t*) &clilen); // change from clilen to add (socklen_t*)
    }

    if(newsockfd < 0)
        error((char*)"ERROR on accept");
    int pid = fork();
    if (pid < 0)
        error((char*)"ERROR on accept");
    if (pid == 0)
    {
        close(sockfd);
        dostuff(newsockfd);
        exit(0);
    }
    else
        close(newsockfd);
    */ //this is only for a "real world" server as this runs indefinitely
    close(sockfd);

    return 0;
}