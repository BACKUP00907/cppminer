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

int main(int argc, char const* argv[])
{
	int status, valread, client_fd;
	
	char buffer[3000] = { 0 };
  	

	client_fd = socket(AF_INET, SOCK_STREAM, 0);

  	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
  	serv_addr.sin_addr.s_addr = inet_addr(server_ip);

	//init ends here

	//basic json 
	
	rapidjson::Document loginjson;
	Value y;
	y =StringRef("login");
	loginjson.AddMember("method", y, loginjson.GetAllocator());
	
	std::cout << "rashyet" << std::endl;
	loginjson.AddMember("id", 1, loginjson.GetAllocator());
	std::cout <<"fsdf"<< std::endl ;
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


	//char* login = u8"{ \"method\" : \"login\" , \"params\" : { \"login\" : \"49FrBm432j9fg33N8PrwSiSig7aTrxZ1wY4eELssmkmeESaYzk2fPkvfN7Kj4NHMfH11NuhUAcKc5DkP7jZQTvVGUnD243g\" , \"pass\" : \"nor1\" , \"rigid\" : \"\" , \"agent\" : \"cppminer\" } , \"id\" : 1 }\n";
	char* login = (char*)ulog.c_str();
	printf(login);
	//basic json ends
	//basic comm
  	int suks = connect(client_fd,(sockaddr*) &serv_addr ,sizeof(serv_addr));

  	if (suks < 0){
    	printf("error in connecting");
  	}

  	printf("login\n");
	send(client_fd, login, strlen(login), 0);

	while(1==1){
	  recv(client_fd, &buffer,3000 ,0); 
	  printf("%s\n", buffer);
      memset(buffer, 0, sizeof(buffer));
    }
	// closing the connected socket
	close(client_fd);
	return 0;
}
