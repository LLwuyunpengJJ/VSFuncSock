#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
int main() {
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

	//初始化id端口号
	struct sockaddr_in serv_addr = { 0 };
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr - inet_addr("120.0.0.1");
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
	while ((accp = accept(sever, (struct sockaddr*)&clnt_addr, &clnt_addr_len)) < 0);

	printf("sever connect!!\r\n");

	int cnt = 0;
	while (1) {

		char str[200] = "";
		sprintf(str, "你好阿现在运行到第%d行\r\n", cnt++);
		write(accp, str, sizeof(str));
		printf("写入%d个\r\n", cnt);
		sleep(2);
	}
	close(accp);
	close(sever);
	return 0;
}