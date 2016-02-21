#include "votesys.h"
#include "defs.h"
#include<string>
#include<iostream>
#include<rpc/rpc.h>

using namespace std;

char **
zeroize_1_svc(void *argp, struct svc_req *rqstp)
{
	static char * result;
	try{
	voterlist.clear();
	votecounts.clear();
	
	result = "True";
	}
	catch(exception& e){
		cout<<e.what()<<endl;
		result = "False";
	}
	return &result;
}

char **
addvoter_1_svc(int *argp, struct svc_req *rqstp)
{
	static char * result;
	int voterid = *argp;
	map<int,bool>::iterator it = voterlist.find(voterid);
	if(it == voterlist.end()){
		voterlist[voterid]=false;
		result = "OK";
	}else{
		result = "EXISTS";
	}

	return &result;
}

char **
votefor_1_svc(voteparameters *argp, struct svc_req *rqstp)
{
	static char * result;

	string candidate = argp->name;
	int voterid = argp->voterid;	
	
        map<int,bool>::iterator it = voterlist.find(voterid);
        if(it == voterlist.end()){
                
                result = "NOTAVOTER";
		return &result;	
        }else{
		if(it->second == true){
                	result = "ALREADYVOTED";
			return &result;
		}
        }
	
	map<string,int>::iterator iVoteCount = votecounts.find(candidate);
        if(iVoteCount == votecounts.end()){
                votecounts[candidate]=1;
		voterlist[voterid]=true;
                result = "NEW";
        }else{
                int count = votecounts[candidate];
		count++;
		votecounts[candidate]=count;
		voterlist[voterid]=true;
		result = "EXISTS";
        }		
	
	return &result;
}

char **
listcandidates_1_svc(void *argp, struct svc_req *rqstp)
{
	static char * result;

	string candidates="";
	
	for(map<string,int>::iterator it = votecounts.begin();it!=votecounts.end();++it){
		
		candidates+=it->first;
		candidates+="\n";		

	}
	
	if(candidates.length()==0){
		candidates = "EMPTY";
	}
		
	result = &candidates[0];

	return &result;
}

int *
votecount_1_svc(char **argp, struct svc_req *rqstp)
{
	static int  result;

	string candidate = *argp;
	map<string,int>::iterator iVoteCount = votecounts.find(candidate);
        if(iVoteCount == votecounts.end()){
		result = -1;
        }else
	{
                result = votecounts[candidate];
        }


	return &result;
}
