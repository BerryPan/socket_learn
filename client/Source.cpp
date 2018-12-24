#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <Ws2tcpip.h>


#pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.dll

int main() {
	//初始化DLL
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//创建套接字
	SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	//向服务器发起请求
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
	sockAddr.sin_family = PF_INET;
	inet_pton(PF_INET, "127.0.0.1", &sockAddr.sin_addr);
	sockAddr.sin_port = htons(1234);
	connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

	//发送数据
	const char *buffer = "Hello world!";
	send(sock, buffer, strlen(buffer)+sizeof(char), NULL);
	char buf[100] = { 0 };
	recv(sock, buf, 100, NULL);
	printf("%s\n", buf);


	//关闭套接字
	closesocket(sock);

	//终止使用 DLL
	WSACleanup();

	system("pause");
	return 0;
}