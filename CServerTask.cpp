//
#include "CServerTask.h"
#include "CMySocket.h"

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

	while (1)
	{
		TcpRecv(m_socketfd);
		//printf("recv over!\n");
	}
	



}