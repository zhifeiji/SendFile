//#
#include "global.h"
#include "CMySocket.h"
#include "CServerTask.h"


int
main(int argc, char **argv)
{
	using namespace MySocket;

	int					listenfd, connfd;
	pid_t				childpid;
	void				sig_chld(int), sig_int(int), web_child(int);
	

	if (argc == 1)
	{
		listenfd = TcpListen();
	}
	else if (argc == 1)
	{
		listenfd = TcpListen(atoi(argv[1]));
	}
	else
	{
		printf("usage: server [port]\n");
		exit(-1);
	}
	signal(SIGCHLD, sig_chld);
	signal(SIGINT, sig_int);

	for ( ; ; ) {
		if ( (connfd = TcpAccept(listenfd)) < 0) {
			if (errno == EINTR)
				continue;		/* back to for() */
			else
				printf("accept error");
		}

		if ( (childpid = fork()) == 0) {	/* child process */
			close(listenfd);	/* close listening socket */
			printf("a connect\n");
			//web_child(connfd);	/* process request */
			CServerTask serTask(connfd);
			serTask.Run();
			exit(0);
		}
		close(connfd);			/* parent closes connected socket */
	}
}
/* end serv01 */

/* include sigint */
void
sig_int(int signo)
{
	//void	pr_cpu_time(void);

	printf("sig_int\n");
	//pr_cpu_time();
	exit(0);
}
/* end sigint */