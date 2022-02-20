#include "mysocket.h"
bool MySocket::InitSocket() {
	// ��ʼ��socket dll
	WSADATA wsaData;
	WORD socketVersion = MAKEWORD(2, 2);
	if (::WSAStartup(socketVersion, &wsaData) != 0)
	{
		printf("Init socket dll error\n");
		return false;
	}
	return true;
}

void MySocket::TcpListen(std::string addr,uint16_t port)
{
	serverPort = port;
	serverAddr = addr;
	// ����socket�׽���
	server = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SOCKET_ERROR == server)
	{
		printf("Init Socket Error!\n");
		return;
	}
	// ��socket��һ�����ص�ַ
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(serverPort);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	if (::bind(server, (LPSOCKADDR)&sin, sizeof(sockaddr_in)) == SOCKET_ERROR)
	{
		printf("Bind Error!\n");
		return;
	}

	// ����socket�������״̬
	if (::listen(server, 10) == SOCKET_ERROR)
	{
		printf("Listen Error!\n");
		return;
	}
	printf("Listening To Client...\n");

	// ѭ������client�˵���������
	sockaddr_in ClientAddr;
	int nAddrLen = sizeof(sockaddr_in);

	while (INVALID_SOCKET == (client = ::accept(server, (sockaddr*)&ClientAddr, &nAddrLen)))
	{
	}

	while (true == ProcessMsg(client))
	{
	}

	// �ر�ͬ�ͻ��˵�����
	::closesocket(client);
	::closesocket(server);
}

bool MySocket::ProcessMsg(SOCKET s)
{
	int nRecv = ::recv(s, recvbuf, MAX_PACK_SIZE + 1, 0);
	if (nRecv > 1) {
		printf("\nReceive Data :\n");
		for (int i = 0; i < nRecv; i++)
		{
			printf("%c", recvbuf[i]);
		}
		return true;
	}
	return false;
}

bool MySocket::CloseSocket()
{
	// �ͷ�winsock��
	::WSACleanup();

	return true;
}

// ���û���������ݴ��͵�client��
bool MySocket::SendDataToClient()
{
	char Data[256];
	printf("Input the Data: \n");

	fgets(Data, 64, stdin);

	for (int i = 0; i < 64; i++)
	{
		Data[i] = Data[i] - 48;
	}
	if (SOCKET_ERROR == ::send(client, (char*)(&Data), 256, 0))
	{
		printf("Send Data Error!\n");
		exit(-1);
	}

	return true;
}
// ��server�����ӽ��д���
bool MySocket::ConectToServer(std::string addr,uint16_t port)
{
	serverAddr = addr;
	serverPort = port;
	// ��ʼ��socket�׽���
	if (SOCKET_ERROR == (client = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)))
	{
		printf("Init Socket Error!\n");
		exit(-1);
	}
	sockaddr_in servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(serverPort);
	servAddr.sin_addr.S_un.S_addr = ::inet_addr(serverAddr.c_str());
	if (INVALID_SOCKET == (::connect(client, (sockaddr*)&servAddr, sizeof(sockaddr_in))))
	{
		printf("Connect to Server Error!\n");
		exit(-1);
	}
	// �������ݴ��䵽server��
	//while (true == SendDataToServer((char*)"a world"))
	//{
	//}

	// ����server�˴���������Ϣ,ֱ�������ļ��ɹ�Ϊֹ
	while (true == ProcessMsg(server))
	{
	}
	 
	return true;
}

// ���û���������ݴ��͵�server��
bool MySocket::SendDataToServer(char *message)
{
	if (SOCKET_ERROR == ::send(client, message, strlen(message), 0))
	{
		printf("Send Data Error!\n");
		exit(-1);
	}
	return true;
}