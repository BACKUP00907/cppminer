// Client side C/C++ program to demonstrate Socket
// programming
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 10002

int main(int argc, char const* argv[])
{
	int status, valread, client_fd;
	struct sockaddr_in serv_addr;
	char* login = "{ \"method\" : \"login\" , \"params\" : { \"login\" : \"49FrBm432j9fg33N8PrwSiSig7aTrxZ1wY4eELssmkmeESaYzk2fPkvfN7Kj4NHMfH11NuhUAcKc5DkP7jZQTvVGUnD243g\" , \"pass\" : \"nor1\" , \"rigid\" : \"\" , \"agent\" : \"stratum-miner-py/0.1\" } , \"id\" : 1 }";
	char buffer[3000] = { 0 };
  cout << login << endl;
	if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary
	// form
	if (inet_pton(AF_INET, "44.224.209.130", &serv_addr.sin_addr)
		<= 0) {
		printf(
			"\nInvalid address/ Address not supported \n");
		return -1;
	}

	if ((status
		= connect(client_fd, (struct sockaddr*)&serv_addr,
				sizeof(serv_addr)))
		< 0) {
		printf("\nConnection Failed \n");
		return -1;
	}
  printf("login\n");
	send(client_fd, login, strlen(login), 0);
	while(1==1){
	  valread = read(client_fd, buffer,3000 ); // subtract 1 for the null terminator at the end
	  printf("%s\n", buffer);
    memset(buffer, 0, sizeof(buffer));
  }
	// closing the connected socket
	close(client_fd);
	return 0;
}
