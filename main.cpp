#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


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

  if (connect(sockfd, (sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
    cerr << "Error connecting to server" << endl;
    return 1;
  }
 // init done

  // Send data to the server
  char buf [] = "{\"method\": \"login\", \"params\": {\"login\": \"49FrBm432j9fg33N8PrwSiSig7aTrxZ1wY4eELssmkmeESaYzk2fPkvfN7Kj4NHMfH11NuhUAcKc5DkP7jZQTvVGUnD243g\", \"pass\": \"nor1\", \"rigid\": \"kozrov\", \"agent\": \"stratum-miner-py/0.1\"}, \"id\": 1}" ;

  write(sockfd, buf, sizeof(buf));

  // Receive data from the server
  char recvbuf[300];
  int n = read(sockfd, recvbuf, sizeof(recvbuf));
  if (n < 0) {
    cerr << "Error reading from socket" << endl;
    return 1;
  }

  // Print the data received from the server
  cout << recvbuf << endl;

  // Close the socket
  close(sockfd);

  return 0;
}