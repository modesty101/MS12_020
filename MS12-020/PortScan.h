#include <WinSock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int portscan(char *targetIP, int port)
{
	int retval;
	//socket() ���� ����
	SOCKET test_sock;
	test_sock = socket(AF_INET, SOCK_STREAM, 0);

	if (test_sock == INVALID_SOCKET)
		return -1;

	//���� �ּ� ����ü ����
	SOCKADDR_IN target;
	target.sin_family = AF_INET;
	target.sin_addr.s_addr = inet_addr(targetIP);	// IP ����
	target.sin_port = htons(port);	// ��Ʈ 

	//�˻�
	//printf("IP[%s] port[%d] : ", targetIP, port);
	retval = connect(test_sock, (SOCKADDR *)&target, sizeof(target));	
	
	// ���� ��Ʈ ��ĵ
	fd_set set;
	FD_ZERO(&set);
	timeval tvout = { 0, 1};
	FD_SET(test_sock, &set);
	if (select(test_sock + 1, NULL, &set, NULL, &tvout) <= 0) {
		printf("cannot connect to \"%s : %d\" (err:%d)\n", targetIP, port, WSAGetLastError());
		return 1;
	}
	
	if (retval == SOCKET_ERROR)
		printf("closed..\n");
	else if (retval == 0 || port == 3389) {
		printf("%d PORT Open!!\n",port);
		return port;
	}
	else
		puts("Other PORT Open!");
	
	//closesocket()
	closesocket(test_sock);
	return 0;
}