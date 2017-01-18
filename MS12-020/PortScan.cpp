#include <WinSock2.h>
#include <stdlib.h>
#include <stdio.h>

void portscan(char *targetIP, int port)
{
	int retval;
	//socket() ���� ����
	SOCKET test_sock;
	test_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (test_sock == INVALID_SOCKET)
		return;

	//���� �ּ� ����ü ����
	SOCKADDR_IN target;
	target.sin_family = AF_INET;
	target.sin_addr.s_addr = inet_addr(targetIP);
	target.sin_port = htons(port);

	//�˻�
	printf("IP[%s] port[%d] : ", targetIP, port);
	retval = connect(test_sock, (SOCKADDR *)&target, sizeof(target));
	if (retval == SOCKET_ERROR)
		printf("closed\n");
	else
		printf("open\n");

	printf("%d", retval);
	//closesocket()
	closesocket(test_sock);
}