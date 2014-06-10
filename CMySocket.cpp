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
	//socklen_t len;
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

	//cliaddr����Զ˵�������Ϣ
	if ((accfd = accept(listenfd,(struct sockaddr *)&cliaddr,&clilen)) == -1)
	{
		//accept error
	}

	return accfd;	
}


int MySocket::TcpSend(int sockfd, char *ptr, int size)
{
	char szDst[MAX_SEND_BUF];
	int nLengh = setHeadLengh(szDst,ptr,size);
	

	if (write(sockfd, szDst, nLengh) != nLengh)
	{
		//write error
		printf("write error[%s]\n",ptr);
		//exit(-1);
	}
	printf("send datta [%s]\n",szDst);

	return ERROR_NO_ERROR;
}

int MySocket::tcpRecv(int sockfd, char *ptr, int size)
{
	ssize_t n,nCount = 0;
	//char buf[MAXLINE];
	//memset(ptr,'\0',size);
	char *pCur = ptr;

	while (size > 0)
	{
		printf("-\n");
		if ((n = read(sockfd,pCur,size)) > 0)
		{
			printf("recv:[%d] byte\n",n);
			size = size -n;
			pCur = pCur + n;
			nCount += n;
			//printf("recv %d byte\n",n);
		}
	}
	return nCount;
}
int MySocket::TcpRecv(int sockfd, char *ptr, int size)
{
	printf("begin TcpRecv\n");
	char szHead[HEAD_SIZE+1];
	memset(szHead,'\0',HEAD_SIZE+1);
	int n = tcpRecv(sockfd,szHead,int(HEAD_SIZE));

	printf("sz head [%s]\n",szHead);

	int nLengh  = 0;
	for (int i = HEAD_SIZE-1;i>=0;--i)
	{
		nLengh = nLengh * MODE_NUM + int(szHead[i] - 1);
	}
	printf("head len %d\n",nLengh);

	n = tcpRecv(sockfd,ptr,nLengh);
	DEBUG_PRINT("recv [%s]\n",ptr);
	return n;
}
int MySocket::TcpClose(int sockfd)
{
	return close(sockfd);
}


int MySocket::setHeadLengh(char *dst,const char *src,const int srcSize)
{
	printf("comput head lengh:");
	int nLengh = srcSize+HEAD_SIZE;
	int nMode;
	for (int n=0;n<HEAD_SIZE;++n)
	{
		nMode = 0;
		if (nLengh != 0)
		{
			nMode = nLengh % MODE_NUM;
			nLengh /= MODE_NUM;
		}
		dst[n] = (char)nMode + 1;
		printf("--->%d\n",dst[n]);
	}
	printf("\n");
	printf("dst len [%d]\n",strlen(dst));
	strncat(dst,src,srcSize);
	printf("after set head [%s]\n",dst);
	//printf("dst[0]")
	for (int i = 0;i<HEAD_SIZE;++i)
	{
		printf("dst[%d] -->%d\n",i,dst[i]);
	}
	

	return nLengh;
}