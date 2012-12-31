#include "telnet_server.h"

using namespace std;

TelnetServer::TelnetServer() {
  port = 13000;
  
  initialize_server();
}

TelnetServer::TelnetServer(int port_number) {
  port = port_number;
  
  initialize_server();
}

TelnetServer::~TelnetServer() {
}

void TelnetServer::start_server() {
  for ( ; ; ) {
    // Wait for client connections to accept them.
    cerr << "Server: Waiting for connections." << endl;
    client_length = sizeof(client_address);
    connection_fd = accept(listen_fd, (struct sockaddr*)&client_address, (socklen_t*)&client_length);
    cerr << "Server: Client connected." << endl;
    
    handle_commands();

    // Close the connection
    close(connection_fd);
    cerr << "Server: Connection closed." << endl;
  }
}

void TelnetServer::initialize_server() {
  // Create a TCP socket.
  listen_fd = socket(AF_INET, SOCK_STREAM, 0);
  cerr << "Server: Socket created." << endl;

  // Initialize server's address and well-known port.
  bzero(&server_address, sizeof(server_address));
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = htonl(INADDR_ANY);
  server_address.sin_port = htons(port);

  // Bind server's address and port to the socket.
  bind(listen_fd, (struct sockaddr*) &server_address, sizeof(server_address));
  cerr << "Server: Address and port bound to socket." << endl;
  
  // Convert socket to a listening socket with a maximum of 100 pending clients.
  listen(listen_fd, 100);
  cerr << "Server: Socket is now a listening socket." << endl;
}

void TelnetServer::handle_commands() {
  int input_length;
  char recieved_line[100];
  char message_recieved_flag = 0xFF;

  do {
    input_length = read(connection_fd, recieved_line, 100);
    recieved_line[input_length] = '\0';
    input_length = atoi(recieved_line);
 
    if (input_length > 0) {
      char command[input_length + 1];

      write(connection_fd, &message_recieved_flag, 1); 
      input_length = read(connection_fd, command, input_length);
      command[input_length] = '\0';
      cout << "Server: Command \"" << command << "\" recieved." << endl;
      
      execute_command(command);
    }
  } while (input_length > 0);
  
  close(connection_fd);
}

void TelnetServer::execute_command(char* command_and_args) {
  char response_length[100];
  char response_recieved_flag = 0x00;
  char* command;
  char* arguments;
  
  arguments = strchr(command_and_args, ' ');

  if (arguments == NULL) {
    command = command_and_args;
  } else {
    arguments[0] = '\0';
    command = command_and_args;
    arguments = &(arguments[1]);
  }

  if (strcmp(command, (char*)"cd") == 0) {
    
    char* new_working_directory;
    
    chdir(arguments);
    new_working_directory = getcwd(NULL, 0);
    free(new_working_directory);
    new_working_directory = NULL;
    
    // Write a 0 to the socket, indicating no output for the client.
    sprintf(response_length, "%d", 0);
    write(connection_fd, (const void*) response_length, strlen(response_length));

  } else if (strcmp(command, (char*)"pwd") == 0) {
    
    char* current_working_directory;
    current_working_directory = getcwd(NULL, 0);

    // Write the current working directory to the socket as a response.
    sprintf(response_length, "%ud", (unsigned int)strlen(current_working_directory));
    write(connection_fd, (const void*)response_length, strlen(response_length));
    read(connection_fd, &response_recieved_flag, 1);
    write(connection_fd, (const void*)current_working_directory, strlen(current_working_directory));

    free(current_working_directory);
    current_working_directory = NULL;
  } else {
    // Create a pipe to allow exec to communicate with the server.
    int pipe_fd[2];
    pipe(pipe_fd);

    // Fork to preform the exec command.
    if (fork() == 0) {
      close(pipe_fd[0]);
      dup2(pipe_fd[1], 1);
      close(pipe_fd[1]);

      if (strcmp(command, (char*)"ls") == 0) {
	system("ls");
	exit(0);
      } else if (strcmp(command, (char*)"mkdir") == 0) {
	command_and_args[strlen(command)] = ' ';
	system(command_and_args);
	exit(0);
      } else {
	cout << command << " not found.";
	exit(0);
      }
    } else {
      int n;
      char buffer[1024];
      char* response_wire_format;
      stringstream ss(stringstream::in | stringstream::out);

      close(pipe_fd[1]);
      
      while ((n = read(pipe_fd[0], buffer, sizeof(buffer))) != 0) {
	buffer[n] = '\0';
	ss << buffer;
      }

      close(pipe_fd[0]);

      if (ss.str().empty()) {
	// Write a 0 to the socket, indicating no output for the client.
	sprintf(response_length, "%d", 0);
	write(connection_fd, (const void*) response_length, strlen(response_length));
      } else {	
	// Write the output to the client.
	response_wire_format = (char*)ss.str().c_str();
	sprintf(response_length, "%ud", (unsigned int)ss.str().length());
	write(connection_fd, (const void*)response_length, strlen(response_length));
	read(connection_fd, &response_recieved_flag, 1);
	write(connection_fd, (const void*)response_wire_format, strlen(response_wire_format));
      }
    }
  }
}
