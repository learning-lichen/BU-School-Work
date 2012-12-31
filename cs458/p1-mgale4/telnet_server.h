#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>

class TelnetServer {
 public:
  TelnetServer();
  TelnetServer(int port_number);
  ~TelnetServer();

  void start_server();

 private:
  int port, listen_fd, connection_fd;
  int client_length;
  struct sockaddr_in server_address, client_address;

  void initialize_server();
  void handle_commands();
  void execute_command(char* command);
};
