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
		/* Load Winsock 2.0 DLL */
		if (WSAStartup(MAKEWORD(2, 0), &m_wsaData) != 0)
		{
			fprintf(stderr, "WSAStartup() failed");
			return -1;
		}

		/* create a socket for sending to the multicast address */
		if ((m_sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
		{
			fprintf(stderr, "socket() failed");
			return -1;
		}

		/* set the TTL (time to live/hop count) for the send */
		if ((setsockopt(m_sock, IPPROTO_IP, IP_MULTICAST_TTL,
						(void *)&mc_ttl, sizeof(mc_ttl))) < 0)
		{
			fprintf(stderr, "socket() failed");
			return -1;
		}

		/* construct a multicast address structure */
		memset(&m_sockAddr, 0, sizeof(m_sockAddr));
		m_sockAddr.sin_family = AF_INET;
		m_sockAddr.sin_addr.s_addr = inet_addr(m_addrStr);
		m_sockAddr.sin_port = htons(m_port);
	}

	void close()
	{
		closesocket(m_sock);
		WSACleanup(); /* Cleanup Winsock */
	}

	int sendData(const char *buf, int len)
	{
				return sendto(m_sock, buf, len, 0,
						(struct sockaddr *)&m_sockAddr,
						sizeof(m_sockAddr))) != len);
	}

  private:
	WSADATA m_wsaData;
	SOCKET m_sock;
	char *m_addrStr;
	unsigned short m_port;
	struct sockaddr_in m_sockAddr; /* Information about the server */
}
