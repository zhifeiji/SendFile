//

#ifndef _CMYSOCKET_H_
#define _CMYSOCKET_H_

#include "global.h"

namespace MySocket
{

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define MAX_DATA_BUF	(4*1024*1024)
#define MAX_LINE_BUF	(4*1024)
#define MAX_SEND_BUF	(4096+5)

	int TcpConnect(string strIP,unsigned int nPort);
	int TcpListen(unsigned int nPort = SERVER_PORT);
	int TcpAccept(int listenfd);
	int TcpSend(int sockfd, char *ptr, int size);
	int tcpRecv(int sockfd, char *ptr, int size);
	int TcpRecv(int sockfd, char *ptr, int size);

	int TcpClose(int sockfd);
	int setHeadLengh(char *dst,const char *src,const int srcSize);
}




#endif


