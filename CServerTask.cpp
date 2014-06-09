//
#include "CServerTask.h"
#include "CMySocket.h"
#include "CSerialize.h"

using namespace MySocket;


CServerTask::CServerTask(int socketfd)
{
	m_socketfd = socketfd;
}
CServerTask::~CServerTask()
{

}

void CServerTask::Run()
{
	printf("begin CServerTask::Run()\n");

	int nRecv;
	char recBuf[MAX_LINE_BUF];

	while (1)
	{
		if((nRecv = TcpRecv(m_socketfd,recBuf,MAX_LINE_BUF)) < 0)
		{
			continue;
			//recv error
		}
		else if (nRecv == 0) {
			// eof
			break;
		} else {
			CUNSerialize objUseri(recBuf);
			int nCmd;
			char pStrRecv[MAX_LINE_BUF];
			objUseri.unserialize(nCmd);

			switch (nCmd) {
				case MS_MSG_REQ_SENDFILE:
					objUseri.unserialize(pStrRecv);
					printf("cmd [%d],msg[%s]\n",nCmd,pStrRecv);
					break;
				default:
					break;
			}
		}
		//printf("recv over!\n");
	}
	



}
