//#
#include "global.h"
#include "CMySocket.h"
#include "CSerialize.h"

int
main(int argc, char **argv)
{
	using namespace MySocket;

	int	 fd;//
	int nchildren;//
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

	nchildren = 1;//

	for (int i = 0; i < nchildren; i++) 
	{
		if ( (pid = fork()) == 0) 
		{	//child 
			//
			printf("child\n");

			//open a srcFile
			FILE *fileSrc;//
			if ((fileSrc = fopen(strSrcFile.c_str(),"rb")) == NULL)
			{//open file error
				printf("open src file %s fail!\n",strSrcFile.c_str());
				exit(-1);
			}

			struct stat buf;
			off_t fileSize;
			if (stat(strSrcFile.c_str(),&buf) < 0)
			{
				//stat error
			}

			//file info
			if (S_ISREG(buf.st_mode))
			{
				//regular file
				fileSize = buf.st_size;
			}
			else if (S_ISDIR(buf.st_mode))
			{
				//directory

			}
			else 
			{
				//other file
			}
			
			//tcp connect
			fd = TcpConnect(strIPaddr,atoi(strPort.c_str()));

			CSerialize objSeri;
			objSeri.serialize(MS_MSG_REQ_SENDFILE);
			objSeri.serialize(strDstFile.c_str());
			objSeri.serialize(fileSize);
//
			char *pcStr = objSeri.getBuffer();
			TcpSend(fd,pcStr,strlen(pcStr));
			//printf("send data[%s]\n",pcStr);

			sleep(2);
			TcpSend(fd,pcStr,strlen(pcStr));
			sleep(2);
			char m_pszMsg[MAX_LINE_BUF];
			int nRecv = TcpRecv(fd,m_pszMsg,MAX_LINE_BUF);
			CUNSerialize objUNSeri(m_pszMsg);
			int nRecCmd;
			objUNSeri.unserialize(nRecCmd);
			printf("recv from server [%d]\n",nRecCmd);


			printf("clock is set...\nbegin read file...\n");
			struct timeval time_begin,time_end;
			struct timezone time_zone;

			gettimeofday(&time_begin,&time_zone);
			
			long nCount = 0;
			int nReadSize = 0;
			rewind(fileSrc);
			while (!feof(fileSrc))
			{
				//printf("read file\n");
				if ((nReadSize = fread(request,sizeof(char),MAXLINE,fileSrc)) == 0)
				{//

				}
				else
				{//
					
					/**/
					objSeri.resetBuffer();
					objSeri.serialize(request);
					pcStr = objSeri.getBuffer();
					TcpSend(fd,pcStr,strlen(pcStr));

					nCount += nReadSize;


					TcpRecv(fd,m_pszMsg,MAX_LINE_BUF);
					objUNSeri.setStr(m_pszMsg);
					objUNSeri.unserialize(nRecCmd);
					//printf("recv from server [%d]\n",nRecCmd);
					
				}
			}
			//

			gettimeofday(&time_end,&time_zone);

			printf("read file time use:%lf s\n",(time_end.tv_sec*1000000 + time_end.tv_usec-
				time_begin.tv_sec * 1000000 -  time_begin.tv_usec)*1.0f/1000000);
			printf("send %ld bytes\n",nCount);

			fclose(fileSrc);
	
			//if ( (n = readn(fd, reply, nbytes)) != nbytes)
			//	printf("server returned %d bytes\n", n);

			//
			//close(fd);		// TIME_WAIT on client, not server 
			TcpClose(fd);
			
			printf("child %d done\n", i);
			//
			//
			exit(0);
		}
	}

	while (wait(NULL) > 0)	// now parent waits for all children 
		;
	if (errno != ECHILD)
		printf("wait error");


	exit(0);
}
