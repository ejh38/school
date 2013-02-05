/*****************************
 *	Zach Sadler - zps6
 *	Project 5
 *	Tu/Th 11AM section
 *****************************/

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MYPORT 50074

// function prototypes
void *handle_requests(void *p);								// the worker thread function
void send_stuff(char *to_send, int connfd);		// used to communicate to client
void write_to_stats(char *to_write);						// writes to stats.txt

// the mutex for mutual exclusion!
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main() {
	int sfd;										// the socket_id
	int connfd;									// the client id
	struct sockaddr_in addr;		// from hello world

	int thread_id;							// for threading!
	pthread_t thread;						// yeaaah pthreads!

	// pretty much straight from the hello world program
	if ((sfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Socket failed!\n");
		exit(EXIT_FAILURE);
	}

	// same here
	memset(&addr.sin_zero, 0, sizeof(addr.sin_zero));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(MYPORT);
	addr.sin_addr.s_addr = INADDR_ANY;

	// and here
	if (bind(sfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("Bind failed!\n");
		exit(EXIT_FAILURE);
	}

	// again, straight from hello world
	if (listen(sfd, 10) < 0) {
		perror("listen failed!\n");
		exit(EXIT_FAILURE);
	}

	// continue forever!
	while (1) {

		// if we succesfully get a connection
		if ((connfd = accept(sfd, NULL, NULL)) < 0) {
			perror("Accept failed!\n");
			exit(EXIT_FAILURE);
		}

		// then spawn a worker thread!
		thread_id = pthread_create(&thread, NULL, handle_requests, (void *)&connfd);
	}

	close(sfd);
	return 0;
}

// the void *p is connfd
void *handle_requests(void *p) {
	// to be malloc'ed later
	char *filename;
	char *temp_buffer;
	char *big_send_buffer;

	// fixed size buffers
	char http_checker[8];			// to see if the last 8 bytes are 'HTTP/1.1'
	char rcv_buffer[1024];		// if the user sends more than 1024, I'd be surprised
	char send_buffer[1024];		// sort of a temporary buffer to store what we'll send

	int file_size = 0;
	int amt = 0;
	int connfd = *(int *)p;
	
	// for time&date
	time_t time_is;
	struct tm *time_struct;

	if (recv(connfd, rcv_buffer, 1024, 0) > 0) {					// wait for a message
		
		// this if statement keeps us for looking in the string when it's not long
		// enough to contain what we want, and so stops us from segfaulting
		if (strlen(rcv_buffer) <= 15) {

			temp_buffer = malloc(75);		// make some space
			strcat(temp_buffer, "\nYour query must be at least 16 characters.\n");
			strcat(temp_buffer, "Closing connection.\n");
			send_stuff(temp_buffer, connfd);		// send the message
			free(temp_buffer);					// give the space back
		

			close(connfd);					// close the connection

			// mutually exclusively write to stats.txt about their bad request
			pthread_mutex_lock(&mutex);
			write_to_stats(rcv_buffer);
			pthread_mutex_unlock(&mutex);

			return NULL;
		}


		if (!strncmp("GET", rcv_buffer, 3)) {								// if begins with 'GET'
			
			filename = malloc(strlen(rcv_buffer) - 14);				// make enough space
			strncpy(filename, rcv_buffer + 4, strlen(rcv_buffer) - 15);	// copy filename
			strncpy(http_checker, rcv_buffer + 4 + strlen(filename) + 1, 8);	// copy HTTP

			if (!strncmp(http_checker, "HTTP/1.1", 8)) {			// check for HTTP/1.1
		
				FILE *f = fopen(filename, "rt");		// try to open the filename they gave

				if (f == NULL) {					// if file not found, tell them
					strcat(send_buffer, "\nHTTP/1.1 404 Not Found\n\n");
					send_stuff(send_buffer, connfd);

					close(connfd);					// close the connection

					pthread_mutex_lock(&mutex);
					write_to_stats(rcv_buffer);
					pthread_mutex_unlock(&mutex);
					return NULL;						// and quit
				}
				// if we're here then it's a valid file
				
				fseek(f, 0, SEEK_END);		// go to the end
				file_size = ftell(f);			// and see how far we've gone, the file_size
				fseek(f, 0, SEEK_SET);		// then go back to the beginning

				time_is = time(NULL);							// get the current time
				time_struct = gmtime(&time_is);		// then convernt to GMC

				temp_buffer = malloc(50);			// make some room

				// this is pretty cool - printf for time/date basically
  			strftime (temp_buffer, 50, "Date: %a, %d %b %Y %X %Z\n", time_struct );

  			// start filling up the send_buffer with stuff to send
				strcat(send_buffer, "\nHTTP/1.1 200 OK\n");
				strcat(send_buffer, temp_buffer);					// copy in the time/date
				strcat(send_buffer, "Content-Length: ");
				sprintf(temp_buffer, "%d\n", file_size);	// convert file_size to string
				strcat(send_buffer, temp_buffer);					// copy in the file size
				strcat(send_buffer, "Connection: close\n");
				strcat(send_buffer, "Content-Type: text/html\n\n");

				free(temp_buffer);		// free the temp_buffer
				temp_buffer = malloc(file_size);		// make it big enough for the file

				fread(temp_buffer, 1, file_size, f);		// read in all the bytes!
				fclose(f);						// and now we're done with the file, so close it

				// make enough room for what we have, plus the file
				big_send_buffer = malloc(file_size + strlen(send_buffer));
				strcat(big_send_buffer, send_buffer);			// put in the old stuff
				strcat(big_send_buffer, temp_buffer);			// and the file

				send_stuff(big_send_buffer, connfd);			// then send it along!
			}
			else {
				// if here, then they didn't end with 'HTTP/1.1'
				strcat(send_buffer, "\nPlease follow the proper format:\n");
				strcat(send_buffer, "GET /FILENAME.html HTTP/1.1\n");
				strcat(send_buffer, "Closing connection.\n\n");

				send_stuff(send_buffer, connfd);
			}	
		}
		else {
			// if here, then they didn't start with 'GET'
			strcat(send_buffer, "\nPlease follow the proper format:\n");
			strcat(send_buffer, "GET /FILENAME.html HTTP/1.1\n");
			strcat(send_buffer, "Closing connection.\n\n");

			send_stuff(send_buffer, connfd);
		}
	}

	close(connfd);		// close the connection to the client
	
	pthread_mutex_lock(&mutex);
	write_to_stats(rcv_buffer);
	pthread_mutex_unlock(&mutex);

}

// send what's in to_send, to the client connfd
void send_stuff(char *to_send, int connfd) {
	int amt = 0;

	// this while loop will make sure the whole thing sends
	while (amt < strlen(to_send)) {
		int ret = send(connfd, to_send + amt, strlen(to_send) - amt, 0);
		if (ret < 0) {
			perror("Send failed!\n");
			exit(EXIT_FAILURE);
		}
		amt += ret;
	}
}

// write the to_write buffer to the end of stats.txt
void write_to_stats(char *to_write) {
	FILE *f = fopen("stats.txt", "a+");

	if (f == NULL) {		// if file not found, tell them
		printf("Error opening stats.txt\n");

		return;					// and quit
	}

	fseek(f, 0, SEEK_END);											// go to the end
	fwrite(to_write, 1, strlen(to_write), f);		// and write the file
	fclose(f);		// and close the file

}
