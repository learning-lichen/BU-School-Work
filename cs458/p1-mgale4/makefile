all: telnet-serv telnet-cli

# Client
telnet-cli: client_driver.o telnet_client.o
	g++ -Wall client_driver.o telnet_client.o -o telnet-cli -lsocket -lnsl

client_driver.o: client_driver.cpp
	g++ -Wall -c client_driver.cpp

telnet_client.o: telnet_client.cpp
	g++ -Wall -c telnet_client.cpp

# Server
telnet-serv: server_driver.o telnet_server.o
	g++ -Wall server_driver.o telnet_server.o -o telnet-serv -lsocket -lnsl

server_driver.o: server_driver.cpp
	g++ -Wall -c server_driver.cpp 

telnet_server.o: telnet_server.cpp
	g++ -Wall -c telnet_server.cpp

clean:
	rm -f *~ *.o telnet-cli telnet-serv
