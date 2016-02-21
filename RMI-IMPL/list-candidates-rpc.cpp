#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<string>
#include<sys/socket.h>
#include<arpa/inet.h>
#include "defs.h"
#include "votesys.h"
#include<sstream>

using namespace std;

int main(int argc, char*argv[]){
        if(argc!=2){
                cout<<"Incorrect number of argument"<<endl;
                exit(-1);
        }

		char* server = argv[1];
		CLIENT *clnt;
		
		try{
                clnt = clnt_create(server, VOTECLIENT_PROG,VOTECLIENT_VERS, "tcp");
                if (clnt == (CLIENT *)NULL) {
                        clnt_pcreateerror(server);
                        exit(1);
				}
        }
        catch(exception& e){
                cout<<e.what()<<endl;
        }

        string reply;
        reply.resize(2048);
        reply = *listcandidates_1((void*)NULL,clnt);
		
		 if(reply.empty()){
			clnt_perror(clnt, server);
			exit(1);
		}
				
        cout<<reply<<endl;

}
