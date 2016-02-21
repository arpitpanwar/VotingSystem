#include "defs.h"
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/ioctl.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<algorithm>
#include<string>
#include<list>
#include<map>
#include<iterator>
#include<vector>
#include<sstream>
#include<cctype>

using namespace std;

int getSockHandle();
string zeroize();
string addvoter(int voterid);
string votefor(char *name,int voterid);
string listcandidates();
int votecount(char *name);
string& trim_right_in_place(string& str);
map<int, bool> voterlist;

list<string> candidateList;

map<string, int> votecounts;

int main(){

	int sock_fd = getSockHandle();
	int new_socket,c;
	struct sockaddr_in client;
	
	while( (new_socket = accept(sock_fd, (struct sockaddr *)&client, (socklen_t*)&c)) )
    	{	string message;
		message.resize(2048);
		int len=0;
		int bytes_received = read(new_socket,&message[0],2048);
		vector<string> tokens;
		
		if(bytes_received<0){
			perror("Some error");
			continue;
		}
		istringstream iss(message);
		do{
			
			string token;
			iss >> token;
			trim_right_in_place(token);
			transform(token.begin(), token.end(), token.begin(), ::toupper);
			tokens.push_back(token);
			
		}while(iss);
		
		
		string action = tokens[0];
		string out;
		if(action.compare(ADDVOTER)==0){
			int value;
			istringstream(tokens[1])>>value;
			out = addvoter(value);
		}else{
			if(action.compare(ZEROIZE)==0){
				out = zeroize();
			}else{
				if(action.compare(VOTEFOR)==0){
					int value;
					char *name = &tokens[1][0];
					istringstream(tokens[2])>>value;
					out = votefor(name,value);
				}else{
					if(action.compare(CANDIDATES)==0){
						out = listcandidates();
					}else{
						if(action.compare(COUNT)==0){
							char *name = &tokens[1][0];
							out = to_string(votecount(name));
						}
					}
					
				}
			}
		}


		
		write(new_socket,out.c_str(),out.length());         
    	}
	
	return 0;
}

string& trim_right_in_place(string& str) {
    size_t i = str.size();
    while(i > 0 && (isspace(str[i - 1])||(int)str[i-1]==0 )) { --i; };
    return str.erase(i, str.size());
}

int getSockHandle(){
	
	int sock_fd;
	struct sockaddr_in servaddr;
	sock_fd = socket(AF_INET,SOCK_STREAM,0);
	if(sock_fd<0){
		cout<<"Error Creating Socket";
		exit(-1);
	}
	
	
  	servaddr.sin_family = AF_INET;
  	servaddr.sin_addr.s_addr = htonl( INADDR_ANY );
  	servaddr.sin_port = htons(8811 );
	
	if( bind( sock_fd, (struct sockaddr *) &servaddr, sizeof(servaddr) ) < 0 )
    	{
     		perror( "bind on listenfd");
      		exit( 2 );
    	}
  
  	if( listen( sock_fd, 3 ) < 0 )
    	{
      		perror( "listen on listenfd" );
      		exit( 3 );
    	}
	
	return sock_fd;
}

string zeroize(){
	voterlist.clear();
	votecounts.clear();
	return "TRUE";
}

string addvoter(int voterid){
	
	map<int,bool>::iterator it = voterlist.find(voterid);
	if(it == voterlist.end()){
		voterlist[voterid]=false;
		return "OK";
	}else{
		return "EXISTS";
	}
}

string votefor(char *name,int voterid){

	string candidate = name;
	
	
        map<int,bool>::iterator it = voterlist.find(voterid);
        if(it == voterlist.end()){
                
                return "NOTAVOTER";
        }else{
		if(it->second == true){
                	return "ALREADYVOTED";
		}
        }
	
	map<string,int>::iterator iVoteCount = votecounts.find(candidate);
        if(iVoteCount == votecounts.end()){
                votecounts[name]=1;
		voterlist[voterid]=true;
                return "NEW";
        }else{
                int count = votecounts[candidate];
		count++;
		votecounts[candidate]=count;
		voterlist[voterid]=true;
		return "EXISTS";
        }		
	

}

string listcandidates(){
	
	string candidates="";
	
	for(map<string,int>::iterator it = votecounts.begin();it!=votecounts.end();++it){
		
		candidates+=it->first;
		candidates+="\n";		

	}
	if(candidates.length()==0){
		candidates = "EMPTY";	
	}	

	return candidates;

}

int votecount(char* name){
	
	string candidate = name;
	map<string,int>::iterator iVoteCount = votecounts.find(candidate);
        if(iVoteCount == votecounts.end()){
		return -1;
        }else
	{
                return votecounts[candidate];
        }

}
