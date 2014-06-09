//
//
#ifndef _CSERVER_TASK_H_
#define _CSERVER_TASK_H_

#include "global.h"
#include "CMySocket.h"
using namespace MySocket;

class CServerTask
{
private:
	int m_socketfd;

public:
	CServerTask(int socketfd);
	virtual ~CServerTask();

public:
	void Run();

};



#endif


