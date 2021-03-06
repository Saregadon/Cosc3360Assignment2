// Assignment 2
/*
    Christian Schuering
    Cosc 3360
    Explanation - The program reads in a prediction from a server file
    to a client file what horoscope reads in for any specific zodiac
    sign.
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h> //usesd for bzero();
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

struct sockadder_in
{
    short sin_family; //must be AF_UNIX
    u_short sin_port;
    struct in_addr sin_addr;
    char sin_zero[8]; //not used, must be 0
};

void error(const char* msg)
{
    perror(msg);
    exit(1);
}

int main()
{
    int sockfd, newsockfd, portno, n;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr; //sockaddr_in contains internet address
    socklen_t clilen;

    string inp;
    int pos = 0;
    map<string, string> horoscmsg;
    map<string, string>::iterator it;

    string signs[12] = {"Aries", "Taurus", "Gemini", "Cancer", "Leo", "Virgo", "Libra", "Scorpio", "Sagittarius", "Capricorn", "Aquarius", "Pisces"};

    ifstream ifs("predictions20.txt");

    //if(argc < 2)
    //{
    //    fprintf(stderr,"ERROR, no port provided");
    //    exit(1);
    //}

    while(getline(ifs, inp))
    {
        horoscmsg.insert(make_pair(signs[pos],inp));
        pos++;
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0); //Must use UNIX on unix machine //AF_INET for internet machines
    if (sockfd < 0) 
        error("ERROR opening socket"); //passes the port number which the server accepts connections as an argument aka sockfd

    bzero((char*) &serv_addr, sizeof(serv_addr));
    //portno = atoi(argv[1]);
    cout << "Enter server port number: ";
    cin >> portno;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
        error("ERROR on binding"); //error field

    listen (sockfd,5); //listens on the socket for connections listen(filedescriptor, sizeof(backlogqueue));

    clilen = sizeof(cli_addr);

    while(true)
    {
        newsockfd = accept(sockfd, (struct sockaddr*) &cli_addr, &clilen); // change from clilen to add (socklen_t*)
        if (newsockfd < 0)
            error("ERROR on accept");

        //magic
        bzero(buffer, 256);
        n = read(newsockfd, buffer, 255);
        if (n < 0) error("ERROR reading from socket");
        //printf("Here is the message: %s", buffer);

        buffer[strlen(buffer) - 1] = '\0'; //used for the keypress enter "\0"

        string horoscope(buffer);
        string message;

        //horoscmsg.lower_bound(horoscope)->first //signs[]
        //horoscmsg.lower_bound(horoscope)->second //horoscope

        if(horoscope == horoscmsg.lower_bound(horoscope)->first) //Aries
        {
            cout << "Daily horoscope for " << buffer << ":" << endl;
            message = horoscmsg.lower_bound(horoscope)->second;
            cout << horoscmsg.lower_bound(horoscope)->second << endl;
            strcpy(buffer, message.c_str());
            n = write(newsockfd, buffer,strlen(buffer));
            if (n < 0) error("ERROR writing to socket");
        }
        else if(horoscope == horoscmsg.lower_bound(horoscope)->first) //Taurus
        {
            cout << "Daily horoscope for " << buffer << ":" << endl;
            message = horoscmsg.lower_bound(horoscope)->second;
            cout << horoscmsg.lower_bound(horoscope)->second << endl;
            strcpy(buffer, message.c_str());
            n = write(newsockfd, buffer,strlen(buffer));
            if (n < 0) error("ERROR writing to socket");
        }
        else if(horoscope == horoscmsg.lower_bound(horoscope)->first) //Gemini
        {
            cout << "Daily horoscope for " << buffer << ":" << endl;
            message = horoscmsg.lower_bound(horoscope)->second;
            cout << horoscmsg.lower_bound(horoscope)->second << endl;
            strcpy(buffer, message.c_str());
            n = write(newsockfd, buffer,strlen(buffer));
            if (n < 0) error("ERROR writing to socket");
        }
        else if(horoscope == horoscmsg.lower_bound(horoscope)->first) //Cancer
        {
            cout << "Daily horoscope for " << buffer << ":" << endl;
            message = horoscmsg.lower_bound(horoscope)->second;
            cout << horoscmsg.lower_bound(horoscope)->second << endl;
            strcpy(buffer, message.c_str());
            n = write(newsockfd, buffer,strlen(buffer));
            if (n < 0) error("ERROR writing to socket");
        }
        else if(horoscope == horoscmsg.lower_bound(horoscope)->first) //Leo
        {
            cout << "Daily horoscope for " << buffer << ":" << endl;
            message = horoscmsg.lower_bound(horoscope)->second;
            cout << horoscmsg.lower_bound(horoscope)->second << endl;
            strcpy(buffer, message.c_str());
            n = write(newsockfd, buffer,strlen(buffer));
            if (n < 0) error("ERROR writing to socket");
        }
        else if(horoscope == horoscmsg.lower_bound(horoscope)->first) //Virgo
        {
            cout << "Daily horoscope for " << buffer << ":" << endl;
            message = horoscmsg.lower_bound(horoscope)->second;
            cout << horoscmsg.lower_bound(horoscope)->second << endl;
            strcpy(buffer, message.c_str());
            n = write(newsockfd, buffer,strlen(buffer));
            if (n < 0) error("ERROR writing to socket");
        }
        else if(horoscope == horoscmsg.lower_bound(horoscope)->first) //Libra
        {
            cout << "Daily horoscope for " << buffer << ":" << endl;
            message = horoscmsg.lower_bound(horoscope)->second;
            cout << horoscmsg.lower_bound(horoscope)->second << endl;
            strcpy(buffer, message.c_str());
            n = write(newsockfd, buffer,strlen(buffer));
            if (n < 0) error("ERROR writing to socket");
        }
        else if(horoscope == horoscmsg.lower_bound(horoscope)->first) //Scorpio
        {
            cout << "Daily horoscope for " << buffer << ":" << endl;
            message = horoscmsg.lower_bound(horoscope)->second;
            cout << horoscmsg.lower_bound(horoscope)->second << endl;
            strcpy(buffer, message.c_str());
            n = write(newsockfd, buffer,strlen(buffer));
            if (n < 0) error("ERROR writing to socket");
        }
        else if(horoscope == horoscmsg.lower_bound(horoscope)->first) //Sagittarius
        {
            cout << "Daily horoscope for " << buffer << ":" << endl;
            message = horoscmsg.lower_bound(horoscope)->second;
            cout << horoscmsg.lower_bound(horoscope)->second << endl;
            strcpy(buffer, message.c_str());
            n = write(newsockfd, buffer,strlen(buffer));
            if (n < 0) error("ERROR writing to socket");
        }
        else if(horoscope == horoscmsg.lower_bound(horoscope)->first) //Capricorn
        {
            cout << "Daily horoscope for " << buffer << ":" << endl;
            message = horoscmsg.lower_bound(horoscope)->second;
            cout << horoscmsg.lower_bound(horoscope)->second << endl;
            strcpy(buffer, message.c_str());
            n = write(newsockfd, buffer,strlen(buffer));
            if (n < 0) error("ERROR writing to socket");
        }
        else if(horoscope == horoscmsg.lower_bound(horoscope)->first) //Aquarius
        {
            cout << "Daily horoscope for " << buffer << ":" << endl;
            message = horoscmsg.lower_bound(horoscope)->second;
            cout << horoscmsg.lower_bound(horoscope)->second << endl;
            strcpy(buffer, message.c_str());
            n = write(newsockfd, buffer,strlen(buffer));
            if (n < 0) error("ERROR writing to socket");
        }
        else if(horoscope == horoscmsg.lower_bound(horoscope)->first) //Pisces
        {
            cout << "Daily horoscope for " << buffer << ":" << endl;
            message = horoscmsg.lower_bound(horoscope)->second;
            cout << horoscmsg.lower_bound(horoscope)->second << endl;
            strcpy(buffer, message.c_str());
            n = write(newsockfd, buffer,strlen(buffer));
            if (n < 0) error("ERROR writing to socket");
        }
        else if(horoscope == "Terminate")
        {
            cout << "Server will terminate. Goodbye!" << endl;
            close(newsockfd);
            break;
        }
        else
        {
            cout << "Daily horoscope for " << buffer << ":" << endl;
            n = write(newsockfd, "You did not enter a Zodiac sign.", 33);
            cout << "You did not enter a Zodiac sign." << endl;
            if(n < 0) error("ERROR writing to socket");
        }
    }

    close(newsockfd);
    close(sockfd);

    return 0;
}