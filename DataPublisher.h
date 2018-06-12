#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock.h>
#include <time.h>

class DataPublisher
{
  public:
	int init()
	{
		/* Open windows connection */
		if (WSAStartup(0x0101, &w) != 0)
		{
			fprintf(stderr, "Could not open Windows connection.\n");
			exit(0);
		}

		/* Open a datagram socket */
		sd = socket(AF_INET, SOCK_DGRAM, 0);
		if (sd == INVALID_SOCKET)
		{
			fprintf(stderr, "Could not create socket.\n");
			WSACleanup();
			return -1;
		}

		/* Clear out server struct */
		memset((void *)&sockaddr, '\0', sizeof(struct sockaddr_in));

		/* Set family and port */
		sockaddr.sin_family = AF_INET;
		sockadr.sin_port = htons(port_number);
		sockaddr.sin_addr.S_un.S_un_b.s_b1 = (unsigned char)addr[0];
		sockaddr.sin_addr.S_un.S_un_b.s_b2 = (unsigned char)addr[1];
		sockaddr.sin_addr.S_un.S_un_b.s_b3 = (unsigned char)addr[2];
		sockaddr.sin_addr.S_un.S_un_b.s_b4 = (unsigned char)addr[3];
		if (bind(sd, (struct sockaddr *)&server, sizeof(struct sockaddr_in)) == -1)
		{
			fprintf(stderr, "Could not bind name to socket.\n");
			closesocket(sd);
			WSACleanup();
			return -1;
		}

		/* Print out server information */
		printf("Server running on %u.%u.%u.%u\n", (unsigned char)server.sin_addr.S_un.S_un_b.s_b1,
			   (unsigned char)server.sin_addr.S_un.S_un_b.s_b2,
			   (unsigned char)server.sin_addr.S_un.S_un_b.s_b3,
			   (unsigned char)server.sin_addr.S_un.S_un_b.s_b4);
	}

  private:
	WSADATA w;							/* Used to open windows connection */
	unsigned short port_number = 60000; /* Port number to use */
	int addr[4] = {239, 255, 4, 12};
	int client_length;			 /* Length of client struct */
	int bytes_received;			 /* Bytes received from client */
	SOCKET sd;					 /* Socket descriptor of server */
	struct sockaddr_in sockaddr; /* Information about the server */
	char buffer[BUFFER_SIZE];	/* Where to store received data */
	time_t current_time;		 /* Current time */
}
