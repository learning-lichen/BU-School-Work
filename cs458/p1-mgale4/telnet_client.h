#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <strings.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define DEFAULT_PORT 66887;

class TelnetClient {
 public:
  TelnetClient();
  TelnetClient(char* server_address_in);
  TelnetClient(char* server_address_in, int port_number);
  ~TelnetClient();

  void start_client();
  
 private:
  int port;
  int socket_fd;
  struct sockaddr_in server_address;

  void initialize_client(char* server_address_in);
  void get_commands();
};
