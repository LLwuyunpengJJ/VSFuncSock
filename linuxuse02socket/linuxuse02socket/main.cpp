#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
int socket_test(void);
int main() {
	while (1) {
		socket_test();
		sleep(1);
	}
}
int cnt = 1;
int socket_test(void) {
	printf("欢迎使用本服务器！！my\r\n");
	int err;    //返回值
	int accp = 0;
	//创建套接字
	int sever = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sever < 0)
	{
		printf("server : server socket create error\n");
		return -1;
	}

	int on = 1;
	int s = setsockopt(sever, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	if (s < 0) {
		printf("server : setsockopt error\n");
		return -1;
	}

	//初始化id端口号
	struct sockaddr_in serv_addr = { 0 };
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
	serv_addr.sin_port = htons(1234);
	err = bind(sever, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	if (err < 0)
	{
		printf("server : bind error\n");
		return -1;
	}
	//监听
	err = listen(sever, SOMAXCONN);
	if (err < 0)
	{
		printf("server : listen error\n");
		return -1;
	}

	//连接任务//处理数据接受
	struct sockaddr_in clnt_addr = { 0 };
	socklen_t clnt_addr_len = sizeof(clnt_addr);
	accp = accept(sever, (struct sockaddr*)&clnt_addr, &clnt_addr_len);
	if (accp > 0) {
		printf("sever : accept!\n");
	}else {
		printf("sever : accept error\n");
		return -1;
	}
	printf("sever connect!!\r\n");

	/* 发送数据给客户端 */
	char str[200] = { 0 };
	sprintf(str, "这是服务器第%d条数据", cnt);
	write(accp, str, strlen(str));
	printf("写入%d个\r\n", cnt);

	//读取客户端传回的数据
	char buffer[40] = { 0 };
	read(accp, buffer, sizeof(buffer) - 1);
	printf(">>%d<<Message form server: %s\n", cnt, buffer);

	cnt++;
	close(accp);
	close(sever);
	return 0;
}


