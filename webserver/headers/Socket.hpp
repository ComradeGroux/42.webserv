#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <poll.h>
//#include <sys/event.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/select.h>
#include <algorithm>
#include <list>
#include "Client.hpp"


class Socket{


	public:
	Socket();
	~Socket();
	void setup(int port);
	//void handleConnection(int clientsocket);
	//void prepareConnection(int clientsocket);
	void handleConnection(std::list<Client> *clientlist);
	void initsets(std::list<Client> *clientlist, Client *clientarray[]);
	void rmfdfromset(int fd, fd_set *set);
	void addfdtoset(int fd, fd_set *set);
	void closeconnection(std::list<Client> *clientlist, int i);
	void checktimeout(Client *clientarray[]);
	void readrequest(Client *clientarray[], int fd);
	int findclient(std::list<Client> *clientlist, int fd);
	void setMaxSock(Client *clientarray[]);
	void acceptConnection2(int listeningsocket, Client *clientarray[]);
	void sendresponse(Client *clientarray[], int fd);
	
	sockaddr_in _server;
	fd_set _read, _write, _except, _main;
	timeval _timeout;
	int _listening_socket, _r, _w, _e;
	char _svc[NI_MAXSERV];
	char _buffer[4096];
	int _max_sock;

	private:


};











#endif