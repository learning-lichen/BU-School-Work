#include "telnet_server.h"

int main(int argc, char* argv[]) {
  TelnetServer serv(66887);
  
  serv.start_server();
}
