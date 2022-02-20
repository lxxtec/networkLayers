#ifndef __MYSOCKET_H
#define __MYSOCKET_H
#include <iostream>
#include <WinSock2.h>
#include <stdio.h>
#include <assert.h>
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1

#pragma comment(lib, "WS2_32")
#define MAX_PACK_SIZE  1024 // ���ݰ�����󳤶�,��λ��sizeof(char)
class MySocket
{
private:
	uint16_t serverPort = 8888;
	std::string serverAddr = "192.168.0.105";
	SOCKET client;
	SOCKET server;
	char recvbuf[MAX_PACK_SIZE + 1];
	char sendbuf[MAX_PACK_SIZE + 1];
public:
	MySocket() {
		InitSocket();
	}
	// ��ʼ��
	bool InitSocket();
	// ����
	void TcpListen(std::string addr,uint16_t port);
	// ���ӷ�����
	bool ConectToServer(std::string addr, uint16_t port);
	// ��Ϣ����
	bool ProcessMsg(SOCKET s);
	bool CloseSocket();
	// ���û���������ݴ��͵�client��
	bool SendDataToClient();

	// ���û���������ݴ��͵�server��
	bool SendDataToServer(char* message);
	~MySocket() {
		CloseSocket();
	}
};


#endif // !__MYSOCKET_H


