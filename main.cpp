// Client side C/C++ program to demonstrate Socket
// programming
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include <iostream>

#define PORT 10002

using namespace rapidjson;

char* server_ip = "44.224.209.130" ;
char* wallet = u8"49FrBm432j9fg33N8PrwSiSig7aTrxZ1wY4eELssmkmeESaYzk2fPkvfN7Kj4NHMfH11NuhUAcKc5DkP7jZQTvVGUnD243g";
char* workername = u8"cpp";
char* rigid = u8"kor";
char* agent = u8"cccpminer";

//function templetes
int nethandle(int sockl);
//end

int main(int argc, char const* argv[])
{
	int status, valread, clientsock;
	
	
  	

	clientsock = socket(AF_INET, SOCK_STREAM, 0);

  	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
  	serv_addr.sin_addr.s_addr = inet_addr(server_ip);


	//init ends here
	//conns
	int suks = connect(clientsock,(sockaddr*) &serv_addr ,sizeof(serv_addr));

  	if (suks < 0){
    	printf("error in connecting");
  	}
	
	nethandle(clientsock);

	return 0;
}


int nethandle(int sockl){

//basic json 
	
	rapidjson::Document loginjson;
	loginjson.SetObject();
	
	loginjson.AddMember("method", "login", loginjson.GetAllocator());
	
	
	loginjson.AddMember("id", 1, loginjson.GetAllocator());
	Value jsonparams(kObjectType);
	
	jsonparams.AddMember("login", Value(wallet, loginjson.GetAllocator()), loginjson.GetAllocator());
	jsonparams.AddMember("pass", Value(workername, loginjson.GetAllocator()), loginjson.GetAllocator());
	jsonparams.AddMember("rigid", Value(rigid, loginjson.GetAllocator()), loginjson.GetAllocator());
	jsonparams.AddMember("agent", Value(agent, loginjson.GetAllocator()), loginjson.GetAllocator());

	loginjson.AddMember("params", jsonparams, loginjson.GetAllocator());

	StringBuffer zbuffer;
  	Writer<StringBuffer>writer(zbuffer);
  	loginjson.Accept(writer);
	std::string ulog = zbuffer.GetString();


	char* login = (char*)ulog.c_str();
	strcat(login ,"\n");
	printf("login\n");
	
	//basic json ends
	//response handler
  	rapidjson::Document respjson;
	
	assert(respjson.IsObject());
  	char recvbuffer[3000] = { 0 };
	
	send(sockl, login, strlen(login), 0);

	//response json handler

	while(1==1){
	  recv(sockl, &recvbuffer,3000 ,0); 
	  printf("%s\n", recvbuffer);
	  respjson.Parse(recvbuffer);
	  printf("method ",respjson["method"].GetString());
	  printf("json rpc  ",respjson["jsonrpc"].GetString());



      memset(recvbuffer, 0, sizeof(recvbuffer));
    }
	// closing the connected socket
	close(sockl);





	return 0;

}