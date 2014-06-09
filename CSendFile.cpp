//#
#include "global.h"
#include "CMySocket.h"

int
main(int argc, char **argv)
{
	using namespace MySocket;

	int	 fd;//连接server的socket描述符
	int nchildren;//表示子进程数量
	pid_t	pid;
	char	request[MAXLINE], reply[MAXN];

	if (argc != 5)
	{
		printf("usage: client <IPaddr> <port> <srcFile> <dstFile>\n");
		exit(-1);
	}

	string strIPaddr  = argv[1];
	string strPort	  = argv[2];
	string strSrcFile = argv[3];
	string strDstFile = argv[4];

	nchildren = 1;//子进程数量

	//snprintf(request, sizeof(request), "src:%s, dst:%s\n", strSrcFile.c_str(),strDstFile.c_str()); /* newline at end */

	for (int i = 0; i < nchildren; i++) 
	{
		if ( (pid = fork()) == 0) 
		{	/* child */
			//连接server
			fd = TcpConnect(strIPaddr,atoi(strPort.c_str()));

			FILE *fileSrc;//源文件描述符
			if ((fileSrc = fopen(strSrcFile.c_str(),"rb")) == NULL)
			{//open file error
				printf("open src file %s fail!\n",strSrcFile.c_str());
				exit(-1);
			}
			
			int nReadSize;
			while (!feof(fileSrc))
			{
				printf("read file\n");
				if ((nReadSize = fread(request,sizeof(char),MAXLINE,fileSrc)) == 0)
				{//没有读到数据

				}
				else
				{//发送已经读取的数据
					//将数据发送
					if (write(fd, request, strlen(request)) != strlen(request))
					{
						printf("write error[%s]\n",request);
					}
				}
			}
			//关闭打开的文件
			fclose(fileSrc);
	
			//if ( (n = readn(fd, reply, nbytes)) != nbytes)
			//	printf("server returned %d bytes\n", n);

			//主动关闭连接
			//close(fd);		/* TIME_WAIT on client, not server */
			TcpClose(fd);
			
			printf("child %d done\n", i);
			//退出子进程
			exit(0);
		}
	}

	while (wait(NULL) > 0)	/* now parent waits for all children */
		;
	if (errno != ECHILD)
		printf("wait error");

	exit(0);
}
