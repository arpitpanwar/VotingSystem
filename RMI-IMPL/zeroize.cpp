#include<string>
#include<iostream>
#include<rpc/rpc.h>
#include "defs.h"
#include "votesys.h"

using namespace std;

string* zeroize_1_svc()

{
	static string result;
	try{
	voterlist.clear();
	votecounts.clear();
	result = "TRUE";
	}
	catch(exception& e)
	{
		cout<<e.what()<<endl;
		result = "FALSE";
	}
	return &result;
}
