// Client side C/C++ program to demonstrate Socket
// programming
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"

#define PORT 10002

using namespace rapidjson;

char* server_ip = "44.224.209.130" ;
char* wallet ="49FrBm432j9fg33N8PrwSiSig7aTrxZ1wY4eELssmkmeESaYzk2fPkvfN7Kj4NHMfH11NuhUAcKc5DkP7jZQTvVGUnD243g";
char* workername ="cpp";
char* rigid ="kor";
char* agent ="cccpminer";

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
	printf("domsmk");
	rapidjson::Document loginjson;
	printf("domsm");
	loginjson.AddMember("method", "login", loginjson.GetAllocator());
	loginjson.AddMember("id", 1, loginjson.GetAllocator());
	printf("domsm1");
	Value jsonparams(kObjectType);
	printf("domsm2");
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
