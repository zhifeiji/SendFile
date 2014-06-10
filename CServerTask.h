//
//
#ifndef _CSERVER_TASK_H_
#define _CSERVER_TASK_H_

#include "global.h"
#include "CMySocket.h"
#include "CSerialize.h"
using namespace MySocket;

#define MAX_FILE_NAME_LENGH	256

class CServerTask
{
private:
	int m_socketfd;
	CUNSerialize m_objUNSeri;
	CSerialize m_objSeri;
	char *m_pszMsg;

public:
	CServerTask(int socketfd);
	virtual ~CServerTask();

public:
	void Run();

private:
	int RecvMsg();
	void SendMsg();
	void SendOK();
	
	void HdReqSendFile();

};



#endif


