#include	"unp.h"
#include<time.h>
#include<stdio.h>

void
str_cli(FILE *fp, int sockfd)
{
	int			maxfdp1, stdineof;
	fd_set		rset;
	char		buf[MAXLINE];
	int		n;

	stdineof = 0;
	FD_ZERO(&rset);
	int start = time(NULL);
	for ( ; ; ) {
		if (stdineof == 0)
			FD_SET(fileno(fp), &rset);
		FD_SET(sockfd, &rset);
		maxfdp1 = max(fileno(fp), sockfd) + 1;
		Select(maxfdp1, &rset, NULL, NULL, NULL);
		
		if (FD_ISSET(sockfd, &rset)) {	/* socket is readable */
			if ( (n = Read(sockfd, buf, MAXLINE)) == 0) {
				if (stdineof == 1)
				{
					int end = time(NULL);
			//		printf("lead time : %d sec \n", end-start);
					return;		// normal termination 
				}
				else
				{
					err_quit("str_cli: server terminated prematurely");
				}
			}
			Write(fileno(stdout), buf, n);
		}

		if (FD_ISSET(fileno(fp), &rset)) {  /* input is readable */
			if ( (n = Read(fileno(fp), buf, MAXLINE)) == 0) {
				stdineof = 1;
				Shutdown(sockfd, SHUT_WR);	/* send FIN */
				FD_CLR(fileno(fp), &rset);
				continue;
			}
			// SIGPID start
			//Shutdown(sockfd, SHUT_WR);
			//Signal(SIGPIPE, SIG_IGN);
			// SIGPID end
			
			sleep(100000000);	
			Writen(sockfd, buf, n);	//for 파일 출력
			//sleep(3);
			//sleep(100000000);	//for Dos
		}
	}
}
