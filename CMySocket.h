//

#ifndef _CMYSOCKET_H_
#define _CMYSOCKET_H_

#include "global.h"

namespace MySocket
{

/************************************************************************/
/*                                                                      */
/************************************************************************/

	int TcpConnect(string strIP,unsigned int nPort);
	int TcpListen(unsigned int nPort = SERVER_PORT);
	int TcpAccept(int listenfd);
	int TcpSend(int sockfd, char *ptr, int size);
	int TcpRecv(int sockfd);
	int TcpClose(int sockfd);
}




#endif


