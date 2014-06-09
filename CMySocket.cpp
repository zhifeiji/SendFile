//
#include "CMySocket.h"

int MySocket::TcpConnect(string strIP,unsigned int nPort)
{
	int sockfd;
	struct sockaddr_in dst_addr;
	sockfd = socket(AF_INET,SOCK_STREAM,0);

	dst_addr.sin_family = AF_INET;
	dst_addr.sin_port = htons(nPort);
	dst_addr.sin_addr.s_addr = inet_addr(strIP.c_str());

	if (connect(sockfd,(struct sockaddr *)&dst_addr,sizeof(dst_addr)) == -1)
	{
		//connect error
		ERROR_EXIT("connect fail!");
	}
	DEBUG_PRINT("connect success\n");
	return sockfd;
}

int MySocket::TcpListen(unsigned int nPort)
{

	int listenfd;
	socklen_t len;
	struct sockaddr_in servaddr;
	listenfd = socket(AF_INET,SOCK_STREAM,0);

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(nPort);

	if (bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr)) == -1)
	{
		//bind error
		ERROR_EXIT("bind fail!");
	}
	if (listen(listenfd,LISTENQ) == -1)
	{
		//listen error
		ERROR_EXIT("listen fail!");
	}
	DEBUG_PRINT("listen success\n");
	return listenfd;
}

int MySocket::TcpAccept(int listenfd)
{
	struct sockaddr_in cliaddr;
	socklen_t clilen;

	int accfd;

	//cliaddr保存对端的连接信息
	if ((accfd = accept(listenfd,(struct sockaddr *)&cliaddr,&clilen)) == -1)
	{
		//accept error
	}

	return accfd;	
}


int MySocket::TcpSend(int sockfd, char *ptr, int size)
{
	if (write(sockfd, ptr, size) != size)
	{
		//write error
		printf("write error[%s]\n",ptr);
		//exit(-1);
	}

	return ERROR_NO_ERROR;
}

int MySocket::TcpRecv(int sockfd)
{
	ssize_t n;
	char buf[MAXLINE];
	while ((n = read(sockfd,buf,MAXLINE)) > 0)
	{
		printf("recv:[%d][%s]\n",n,buf);
	}
	
	
	return ERROR_NO_ERROR;
}

int MySocket::TcpClose(int sockfd)
{
	return close(sockfd);
}