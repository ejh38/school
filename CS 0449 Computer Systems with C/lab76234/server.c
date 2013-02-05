#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MYPORT 50073

int main() {
	int sfd, connfd, amt = 0;
	struct sockaddr_in addr;
	char buf[1024];
	char rcv_buffer[1024];

	if ((sfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Socket failed!\n");
		exit(EXIT_FAILURE);
	}

	memset(addr.sin_zero, 0, sizeof(addr.sin_zero));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(MYPORT);
	addr.sin_addr.s_addr = INADDR_ANY;

	if (bind(sfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("Bind failed!\n");
		exit(EXIT_FAILURE);
	}

	if (listen(sfd, 10) < 0) {
		perror("listen failed!\n");
		exit(EXIT_FAILURE);
	}

	if ((connfd = accept(sfd, NULL, NULL)) < 0) {
		perror("Accept failed!\n");
		exit(EXIT_FAILURE);
	}


	// infinite loop waiting for requests

	while (1) {
		if (recv(connfd, rcv_buffer, 1024, 0) > 0) {
			strncpy(buf, rcv_buffer, strlen(rcv_buffer)-1);
			printf("Here's what I got\n%s", buf);
			if (strncmp(buf, "Hello", 5) == 0 || strncmp(buf, "hello", 5) == 0
				|| strncmp(buf, "Hi", 2) == 0 || strncmp(buf, "hi", 2) == 0) {
				sprintf(buf, "%s to you too.\n", buf);
				send(connfd, buf, strlen(buf), 0);
			}
			else {
				strcpy(buf, "Awww.. say hi\n");
				send(connfd, buf, strlen(buf), 0);
			}

			memset(buf, 0, 1024);
		}
		else {
			printf("Nothing on my end\n");
		}

	}


	strcpy(buf, "Hello there!\n");




	// then start sending it
	while (amt < strlen(buf)) {
		int ret = send(connfd, buf + amt, strlen(buf) - amt, 0);
		if (ret < 0) {
			perror("Send failed!\n");
			exit(EXIT_FAILURE);
		}
		amt += ret;
	}

	close(connfd);
	close(sfd);

	return 0;
}

// the void *p is the buffer
void handle_requests(void *p) {
	printf("I'm in a worker thread\n");



}
