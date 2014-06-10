//#

#pragma once

#ifndef _GLOBAL_H_
#define _GLOBAL_H_




//
#include	<sys/types.h>	/* basic system data types */
#include	<sys/socket.h>	/* basic socket definitions */
#if TIME_WITH_SYS_TIME
#include	<sys/time.h>	/* timeval{} for select() */
#include	<time.h>		/* timespec{} for pselect() */
#else
#if HAVE_SYS_TIME_H
#include	<sys/time.h>	/* includes <time.h> unsafely */
#else
#include	<time.h>		/* old system? */
#endif
#endif
#include	<netinet/in.h>	/* sockaddr_in{} and other Internet defns */
#include	<arpa/inet.h>	/* inet(3) functions */
#include	<errno.h>
#include	<fcntl.h>		/* for nonblocking */
#include	<netdb.h>
#include	<signal.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<sys/stat.h>	/* for S_xxx file mode constants */
#include	<sys/uio.h>		/* for iovec{} and readv/writev */
#include	<unistd.h>
#include	<sys/wait.h>
#include	<sys/un.h>		/* for Unix domain sockets */
#include <sys/time.h>

#include <string>
#include <cstdio>
using namespace std;


#define	MAXLINE		4096	/* max text line length */
#define	BUFFSIZE	8192	/* buffer size for reads and writes */
#define	MAXN		16384		/* max # bytes to request from server */
#define	LISTENQ		1024	/* 2nd argument to listen() */
#define SERVER_PORT	4000



//socket msg
#define HEAD_SIZE		4
#define MODE_NUM		127

#define MS_MSG_RES_RECV_OK		1

#define MS_MSG_REQ_SENDFILE	100

//error no
#define ERROR_NO_ERROR	0



#define ERROR_EXIT(szMsg) \
	printf("error:%s\n",szMsg);\
	exit(-1)

#ifdef DEBUG
#define DEBUG_PRINT printf
#else
#define DEBUG_PRINT(str,args...) \
	
#endif




// static int	read_cnt;
// static char	*read_ptr;
// static char	read_buf[MAXLINE];
// 




// 
// static
// ssize_t						/* Read "n" bytes from a descriptor. */
// readn(int fd, void *vptr, size_t n)
// {
// 	size_t	nleft;
// 	ssize_t	nread;
// 	char	*ptr;
// 
// 	ptr = (char *)vptr;
// 	nleft = n;
// 	while (nleft > 0) {
// 		if ( (nread = read(fd, ptr, nleft)) < 0) {
// 			if (errno == EINTR)
// 				nread = 0;		/* and call read() again */
// 			else
// 				return(-1);
// 		} else if (nread == 0)
// 			break;				/* EOF */
// 
// 		nleft -= nread;
// 		ptr   += nread;
// 	}
// 	return(n - nleft);		/* return >= 0 */
// }
// /* end readn */
// 
// 
// static ssize_t
// my_read(int fd, char *ptr)
// {
// 
// 	if (read_cnt <= 0) {
// again:
// 		if ( (read_cnt = read(fd, read_buf, sizeof(read_buf))) < 0) {
// 			if (errno == EINTR)
// 				goto again;
// 			return(-1);
// 		} else if (read_cnt == 0)
// 			return(0);
// 		read_ptr = read_buf;
// 	}
// 
// 	read_cnt--;
// 	*ptr = *read_ptr++;
// 	return(1);
// }
// 
// static
// ssize_t
// readline(int fd, void *vptr, size_t maxlen)
// {
// 	ssize_t	n, rc;
// 	char	c, *ptr;
// 
// 	ptr = (char *)vptr;
// 	for (n = 1; n < maxlen; n++) {
// 		if ( (rc = my_read(fd, &c)) == 1) {
// 			*ptr++ = c;
// 			if (c == '\n')
// 				break;	/* newline is stored, like fgets() */
// 		} else if (rc == 0) {
// 			*ptr = 0;
// 			return(n - 1);	/* EOF, n - 1 bytes were read */
// 		} else
// 			return(-1);		/* error, errno set by read() */
// 	}
// 
// 	*ptr = 0;	/* null terminate like fgets() */
// 	return(n);
// }
// 
// 
// 
// static
// ssize_t						/* Write "n" bytes to a descriptor. */
// writen(int fd, const void *vptr, size_t n)
// {
// 	size_t		nleft;
// 	ssize_t		nwritten;
// 	const char	*ptr;
// 
// 	ptr = (const char *)vptr;
// 	nleft = n;
// 	while (nleft > 0) {
// 		if ( (nwritten = write(fd, ptr, nleft)) <= 0) {
// 			if (nwritten < 0 && errno == EINTR)
// 				nwritten = 0;		/* and call write() again */
// 			else
// 				return(-1);			/* error */
// 		}
// 
// 		nleft -= nwritten;
// 		ptr   += nwritten;
// 	}
// 	return(n);
// }
// 


static
void
sig_chld(int signo)
{
	pid_t	pid;
	int		stat;

	while ( (pid = waitpid(-1, &stat, WNOHANG)) > 0) {
		/* printf("child %d terminated\n", pid); */
	}
	return;
}


#endif
