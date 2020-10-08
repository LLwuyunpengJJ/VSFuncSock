#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
	int err = 0;
	//创建套接字
	int client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (client < 0)
	{
		printf("client : create socket error\n");
		return 1;
	}
	//配置连接IP和端口
	struct sockaddr_in client_addr = { 0 };
	client_addr.sin_family = AF_INET;  //使用IPv4地址
	client_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
	client_addr.sin_port = htons(1234);  //端口

	//连接
	err = connect(client, (struct sockaddr*)&client_addr, sizeof(client_addr));

	if (err == 0)
	{
		printf("client : connect to server\n");
	}
	else
	{
		printf("client : connect error\n");
		return -1;
	}
	printf("connect!\r\n");
	int cnt = 0;

	while (1) {
		//读取服务器传回的数据
		char buffer[40] = { 0 };
		while (read(client, buffer, sizeof(buffer) - 1) <= 0);//阻塞
		printf(">>%d<<Message form server: %s\n", cnt++, buffer);
		usleep(1000000);
	}
	close(client);
	return 0;
}




