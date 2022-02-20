#ifndef __MYSOCKET_H
#define __MYSOCKET_H
#include <iostream>
#include <WinSock2.h>
#include <stdio.h>
#include <assert.h>
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1

#pragma comment(lib, "WS2_32")
#define MAX_PACK_SIZE  1024 // 数据包的最大长度,单位是sizeof(char)
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
	// 初始化
	bool InitSocket();
	// 监听
	void TcpListen(std::string addr,uint16_t port);
	// 连接服务器
	bool ConectToServer(std::string addr, uint16_t port);
	// 消息处理
	bool ProcessMsg(SOCKET s);
	bool CloseSocket();
	// 把用户输入的数据传送到client端
	bool SendDataToClient();

	// 把用户输入的数据传送到server端
	bool SendDataToServer(char* message);
	~MySocket() {
		CloseSocket();
	}
};


#endif // !__MYSOCKET_H


