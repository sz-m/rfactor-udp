#include "../include/UDP.h"

#include <cstdlib>

UDP::UDP(unsigned short nPort)
{
	WSADATA wsaData;

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		//printf("WSAStartup() error.\n");
		//return iResult;
		exit(1);
	}

	// create socket
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == INVALID_SOCKET)
	{
		WSACleanup();
		exit(2);
	}

	// broadcast
	broadcast.sin_addr.S_un.S_addr = htonl(-1); // 255.255.255.255
	broadcast.sin_port = htons(nPort);
	broadcast.sin_family = AF_INET;

}

int UDP::setAsBroadcast(bool bSet)
{
	bool bOptVal = bSet;
	iResult = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char*)&bOptVal, sizeof(BOOL));
	return iResult;
}

int UDP::setAsNonblocking(bool bSet)
{
	u_long iMode = bSet;
	iResult = ioctlsocket(sock, FIONBIO, &iMode);
	return iResult;
}

int UDP::sendtoBroadcast(char* msg, int iSizeOf)
{
	iResult = sendto(sock, msg, iSizeOf, 0, (struct sockaddr *)&broadcast, sizeof(struct sockaddr_in));
	return iResult;
}


