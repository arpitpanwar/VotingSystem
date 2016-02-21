#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<string>
#include<sys/socket.h>
#include<arpa/inet.h>
#include "defs.h"
#include<sstream>
#include "votesys.h"

using namespace std;

int main(int argc, char*argv[]){
        if(argc!=2){
                cout<<"Incorrect number of argument"<<endl;
                exit(-1);
        }
		char* server = argv[1];
        string message,id;
		CLIENT *clnt;
		
		clnt = clnt_create(server, VOTECLIENT_PROG,VOTECLIENT_VERS, "tcp");
		if (clnt == (CLIENT *)NULL) {
			clnt_pcreateerror(server);
			exit(1);
		}
		
		string reply;
        reply.resize(2048);
		reply = *zeroize_1((void*)NULL,clnt);
		if(reply.empty()){
			clnt_perror(clnt, server);
			exit(1);
		}
        
        cout<<reply<<endl;

}
