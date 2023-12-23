#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <utf8.h>


using namespace std;

int minerport = 10002;

int main() {
  // Create a socket
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    cerr << "Error creating socket" << endl;
    return 1;
  }

  // Connect to the server
  sockaddr_in servaddr;
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(minerport); // Port 8080
  servaddr.sin_addr.s_addr = inet_addr("44.224.209.130"); // localhost

  int loc = connect(sockfd, (sockaddr*)&servaddr, sizeof(servaddr));
  if ( loc < 0) {
    cerr << "Error connecting to server" << endl;
    return 1;
  }
 // init done

  // Send data to the server
  std::string str = "{ \"method\" : \"login\" , \"params\" : { \"login\" : \"49FrBm432j9fg33N8PrwSiSig7aTrxZ1wY4eELssmkmeESaYzk2fPkvfN7Kj4NHMfH11NuhUAcKc5DkP7jZQTvVGUnD243g\" , \"pass\" : \"nor1\" , \"rigid\" : \"\" , \"agent\" : \"stratum-miner-py/0.1\" } , \"id\" : 1 }" ;
  std::string lstr = utf8::encode(str);
  

  // Receive data from the server
  char recvbuf[3000];
  cout << buf << endl;
  while (1==1){
    send(sockfd, lstr.c_str(), lstr.length(),0);
    read(sockfd, recvbuf, sizeof(recvbuf));
    cout << recvbuf << endl;
  }
  // Close the socket
  close(sockfd);

  return 0;
}