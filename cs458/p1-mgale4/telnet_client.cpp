#include "telnet_client.h"

using namespace std;

TelnetClient::TelnetClient() {
  port = DEFAULT_PORT;

  initialize_client((char*) "127.0.0.1");
}

TelnetClient::TelnetClient(char* server_address_in) {
  struct hostent* host_entry;
  struct in_addr** address_list;

  port = DEFAULT_PORT;
  if ((host_entry = gethostbyname(server_address_in)) == NULL) {
    cerr << "Server: Error resolving address from hostname." << endl;
    exit(6);
  }

  address_list = (struct in_addr**)host_entry->h_addr_list;
  initialize_client(inet_ntoa(*address_list[0]));
}

TelnetClient::TelnetClient(char* server_address_in, int port_number) {
  struct hostent* host_entry;
  struct in_addr** address_list;

  port = port_number;
  if ((host_entry = gethostbyname(server_address_in)) == NULL) {
    cerr << "Server: Error resolving address from hostname." << endl;
    exit(6);
  }

  address_list = (struct in_addr**)host_entry->h_addr_list;
  initialize_client(inet_ntoa(*address_list[0]));
}

TelnetClient::~TelnetClient() {
}

void TelnetClient::start_client() {
  // Connect to the server
  if (connect(socket_fd, (struct sockaddr*) &server_address, sizeof(server_address)) < 0) {
    cerr << "Client: Could not connect to server." << endl;
    cerr << "Client Error: " << strerror(errno) << endl;
    exit(4);
  } else {
    cerr << "Client: Connected to server." << endl;
  }

  get_commands();

  close(socket_fd);
}

void TelnetClient::initialize_client(char* server_address_in) {
  // Create a TCP socket.
  if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    cerr << "Client: Error creating socket" << endl;
    exit(2);
  }
  
  // Specify the server's IP address and port
  bzero(&server_address, sizeof(server_address));
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(port); // Daytime server port.
  
  if (inet_pton(AF_INET, server_address_in, &server_address.sin_addr) <= 0) {
    cerr << "Client: Inet pton error." << endl;
    exit(3);
  }
}

void TelnetClient::get_commands() {
  bool quit = false;

  // Variables used for sending the command.
  char size_recieved_flag = 0x00;
  char user_input_length[100];
  char* user_input_wire_format;
  string user_input;

  // Variables used for recieving response from server.
  int response_length;
  char response_length_in[100];
  char response_recieved_flag = 0xFF;
  
  while (!quit) {
    // Read in command from user.
    cout << "telnet> ";
    getline(cin, user_input);
    
    if (user_input.compare("exit") == 0) {
      quit = true;
    } else if (user_input.compare("") != 0) {
      // Convert user command to a wire format. This sime protocol sends the length of the command, waits for 
      // the server to acknowledge the size, and then sends the command. 
      user_input_wire_format = (char*) user_input.c_str();
      sprintf(user_input_length, "%d", (unsigned int) user_input.length());
      
      write(socket_fd, (const void*) user_input_length, strlen(user_input_length));
      read(socket_fd, &size_recieved_flag, 1);
      write(socket_fd, (const void*) user_input_wire_format, strlen(user_input_wire_format));

      // Wait for the server to send a response to the command. This response is sent with the same 'protocol'
      // that sends the command to the server.
      response_length = read(socket_fd, response_length_in, 100);
      response_length_in[response_length] = '\0';
      response_length = atoi(response_length_in);

      if (response_length > 0) {
	char response[response_length + 1];

	write(socket_fd, &response_recieved_flag, 1);
	response_length = read(socket_fd, response, response_length);
	response[response_length] = '\0';
	cout << response << endl;
      }
    }
  }
}
