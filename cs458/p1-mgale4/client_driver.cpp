#include "telnet_client.h"

using namespace std;

int main(int argc, char* argv[]) {
  if (argc == 1) {

    cerr << "Client: No server address provided. Using 127.0.0.1." << endl;
    TelnetClient telnet_client;
    telnet_client.start_client();

  } else if (argc == 2) {
    
    cerr << "Client: Connecting to: " << argv[1] << endl;
    TelnetClient telnet_client(argv[1], 66887);
    telnet_client.start_client();

  } else {

    cerr << "Invalid Parameters" << endl;
    cerr << "Usage: telnet-cli <server address>" << endl;
    exit(1);

  }

  return 0;
}
