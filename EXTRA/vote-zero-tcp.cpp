#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<string>
#include<sys/socket.h>
#include<arpa/inet.h>
#include "defs.h"
#include<sstream>

using namespace std;

int main(int argc, char*argv[]){
        if(argc!=3){
                cout<<"Incorrect number of argument"<<endl;
                exit(-1);
        }

        int sockfd,port;
        struct sockaddr_in server;
        string message,id;

        stringstream(argv[2])>>port;
        sockfd = socket(AF_INET,SOCK_STREAM,0);
        if(sockfd == -1){
                cout<<"Unable to create socket"<<endl;
                exit(1);
        }

        server.sin_addr.s_addr = inet_addr(argv[1]);
        server.sin_family = AF_INET;
        server.sin_port = htons(port);

        if(connect(sockfd,(struct sockaddr *)&server,sizeof(server))<0){
                cout<<"Unable to connect to the server"<<endl;
                exit(1);
        }

        message = ZEROIZE;
        
        if(send(sockfd,message.c_str(),message.length(),0)<0){
                cout<<"Unable to send data"<<endl;
                exit(1);
        }

        string reply;
        reply.resize(2048);
        int bytes_received = read(sockfd,&reply[0],2048);
        if(bytes_received<0){
                cout<<"Unable to read from socket";
                exit(1);
        }
        cout<<reply<<endl;

}
