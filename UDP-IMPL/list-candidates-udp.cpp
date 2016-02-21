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
	int addr_len = sizeof(struct sockaddr);
        stringstream(argv[2])>>port;
        sockfd = socket(AF_INET,SOCK_DGRAM,0);
        if(sockfd == -1){
                cout<<"Unable to create socket"<<endl;
                exit(1);
        }

        server.sin_addr.s_addr = inet_addr(argv[1]);
        server.sin_family = AF_INET;
        server.sin_port = htons(port);
	/*
        if(connect(sockfd,(struct sockaddr *)&server,sizeof(server))<0){
                cout<<"Unable to connect to the server"<<endl;
                exit(1);
        }
	*/
        message = CANDIDATES;

        if(sendto(sockfd,message.c_str(),message.length(),0,(struct sockaddr *)&server,sizeof(struct sockaddr))<0){
                cout<<"Unable to send data"<<endl;
                exit(1);
        }

        string reply;
        reply.resize(2048);
        int bytes_received = recvfrom(sockfd,&reply[0],2048,0,(struct sockaddr *)&server,(socklen_t*)&addr_len);
        if(bytes_received<0){
                perror("Unable to read from socket");
                exit(1);
        }
        cout<<reply<<endl;

}
