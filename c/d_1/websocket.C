#include <sys/socket.h>

void main()

{
	int s = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in add= {

		AF_INET,
		0x901f,
		0
	};

	bind(s, &addr, sizeof(addr));

	listen(s, 10);

	int client_fd = accept(s, 0, 0);


}
