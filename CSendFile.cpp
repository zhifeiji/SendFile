//#
#include "global.h"
#include "CMySocket.h"
#include "CSerialize.h"

int
main(int argc, char **argv)
{
	using namespace MySocket;

	int	 fd;//����server��socket������
	int nchildren;//��ʾ�ӽ������
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

	nchildren = 1;//�ӽ������

	//snprintf(request, sizeof(request), "src:%s, dst:%s\n", strSrcFile.c_str(),strDstFile.c_str()); /* newline at end */

	for (int i = 0; i < nchildren; i++) 
	{
		if ( (pid = fork()) == 0) 
		{	/* child */
			//����server
			fd = TcpConnect(strIPaddr,atoi(strPort.c_str()));

			CSerialize objSeri;
			objSeri.serialize(MS_MSG_REQ_SENDFILE);
			objSeri.serialize(strDstFile.c_str());

			char *pcStr = objSeri.getBuffer();

			write(fd, pcStr, strlen(pcStr));// != strlen(pcStr)

			FILE *fileSrc;//Դ�ļ�������
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
				{//û�ж������

				}
				else
				{//�����Ѿ���ȡ�����
					//����ݷ���
					if (write(fd, request, strlen(request)) != strlen(request))
					{
						printf("write error[%s]\n",request);
					}
				}
			}
			//�رմ򿪵��ļ�
			fclose(fileSrc);
	
			//if ( (n = readn(fd, reply, nbytes)) != nbytes)
			//	printf("server returned %d bytes\n", n);

			//�����ر�����
			//close(fd);		/* TIME_WAIT on client, not server */
			TcpClose(fd);
			
			printf("child %d done\n", i);
			//�˳��ӽ��
			exit(0);
		}
	}

	while (wait(NULL) > 0)	/* now parent waits for all children */
		;
	if (errno != ECHILD)
		printf("wait error");

	exit(0);
}
