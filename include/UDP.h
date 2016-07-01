#pragma once

#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>

#pragma comment(lib, "Ws2_32.lib")

class UDP
{
private:
	SOCKET sock;
	struct sockaddr_in broadcast;
	int iResult;

public:
	UDP(unsigned short nPort);
	~UDP() {};

	int setAsBroadcast(bool bSet);
	int setAsNonblocking(bool bSet);

	int sendtoBroadcast(char *msg, int iSizeOf);
};
