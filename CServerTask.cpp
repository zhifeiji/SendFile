//
#include "CServerTask.h"


CServerTask::CServerTask(int socketfd)
{
	m_socketfd = socketfd;
	m_pszMsg = (char *)malloc(MAX_SERIALIZE_BUF * sizeof(char));
}
CServerTask::~CServerTask()
{
	free(m_pszMsg);
}
int CServerTask::RecvMsg()
{
	//char recBuf[MAX_LINE_BUF];

	int nRecv = TcpRecv(m_socketfd,m_pszMsg,MAX_LINE_BUF);
	if (nRecv > 0)
	{
		SendOK();
		m_objUNSeri.setStr(m_pszMsg);
	}
	
	return nRecv;
}
void CServerTask::SendMsg()
{
	char *pcStr = m_objSeri.getBuffer();
	TcpSend(m_socketfd,pcStr,strlen(pcStr));
}
void CServerTask::SendOK()
{
	m_objSeri.resetBuffer();
	m_objSeri.serialize((int)MS_MSG_RES_RECV_OK);
	SendMsg();
}

void CServerTask::Run()
{
	printf("begin CServerTask::Run()\n");

	int nRecv;
	char recBuf[MAX_LINE_BUF];

	while (1)
	{
		if((nRecv = RecvMsg()) < 0)
		{
			continue;
			//recv error
		}
		else if (nRecv == 0) {
			// eof
			break;
		} else {
			int nCmd;
			m_objUNSeri.unserialize(nCmd);

			switch (nCmd) {
				case MS_MSG_REQ_SENDFILE:
					HdReqSendFile();
					break;
				default:
					break;
			}
		}
		//printf("recv over!\n");
	}
	printf("end CServerTask::Run()\n");

}

void CServerTask::HdReqSendFile()
{
	DEBUG_PRINT("start HdReqSendFile\n");

	char szFileName[MAX_FILE_NAME_LENGH];
	long fileSize;
	m_objUNSeri.unserialize(szFileName);
	m_objUNSeri.unserialize(fileSize);
	printf("filename[%s],filesize[%ld]\n",szFileName,fileSize);

	int fileFD;
	if (access(szFileName,F_OK) == -1)
	{
		//file does not exists
		fileFD = open(szFileName,O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
	}
	else
	{
		fileFD = open(szFileName,O_WRONLY|O_APPEND);
	}

	struct timeval time_begin,time_end;
	struct timezone time_zone;

	gettimeofday(&time_begin,&time_zone);

	long nCount = 0;
	int nRecv;
	while (1)
	{
		if ((nRecv = RecvMsg()) < 0)
		{
			printf("recv error\n");
			continue;
		}
		else if (nRecv == 0)
		{
			printf("file over\n");
			break;
		}
		else
		{
			//char *pStr = m_objUNSeri.;
			char szMsg[MAX_LINE_BUF];
			m_objUNSeri.unserialize(szMsg);
			write(fileFD,szMsg,strlen(szMsg));

			nCount += strlen(szMsg);
			//SendOK();
		}
	}
	gettimeofday(&time_end,&time_zone);

	float fUseTime = (time_end.tv_sec*1000000 + time_end.tv_usec-
		time_begin.tv_sec * 1000000 -  time_begin.tv_usec)*1.0f/1000000;

	printf("time use:%lf s\n",fUseTime);
	float fSpeed = fileSize*1.0f/(1024*1024)/fUseTime;

	printf("write %ld bytes\n",nCount);

	printf("speed:%lf M/s\n");

	printf("file %s recv over\n",szFileName);

	close(fileFD);

	DEBUG_PRINT("end HdReqSendFile\n");

}
