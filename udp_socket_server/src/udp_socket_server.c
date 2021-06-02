#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <fcntl.h>

#define MAXLINE  1024
#define SERVER_MODE 0
#define CLIENT_MODE 1
#define PORT     8080

static char data_buf[MAXLINE];

static const char *server_address = "192.168.18.1",
			      *port = "8080";



struct sockaddr_in client;
struct sockaddr_in server;


int start_server(const char *file_name) {

    memset(&server, 0, sizeof(struct sockaddr_in));
    memset(&client, 0, sizeof(struct sockaddr_in));

	unsigned int len = sizeof(client);
	int socket_fd = 0;
    int sent_file_fd = 0,
		data_num = 0;

    memset(data_buf, 0, sizeof(MAXLINE));

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(server_address);
	server.sin_port = htons(strtoul(port,NULL,10));

	if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("The socket creation failed\n\r.");
		exit(EXIT_FAILURE);
	}

	if (bind(socket_fd, (const struct sockaddr *)&server,
			sizeof(server)) < 0 ) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	data_num = recvfrom(socket_fd, (char *)data_buf, MAXLINE,
					MSG_WAITALL, ( struct sockaddr *) &client, &len);

	printf("%s\n\r",data_buf);

	if (0 == strcmp(data_buf, "exit")) {
		close(socket_fd);
		exit(EXIT_SUCCESS);
	}

	if(0 == strcmp(data_buf, "ready")) {

		sent_file_fd = open(file_name, O_RDONLY);
		data_num = read(sent_file_fd, data_buf, MAXLINE);
		close(sent_file_fd);

		sendto(socket_fd, data_buf, data_num, 0, (struct sockaddr *)&client, sizeof(struct sockaddr_in));
	}


	return 0;
}

int main(int argc, char **argv) {

    char *file_name = NULL; //todo:path

    int32_t arg = 0;

   /* while(-1 != (arg = getopt(argc, argv, "h:d:"))) {
        switch(arg) {
            case 'h':
                printf("\n-n a directory path of sent/received files;\n");
                printf("-m choice between a server (0) or a client(1) mode;\n");
                //todo: info

                exit(EXIT_SUCCESS);
            break;
            case 'd':
            	file_name = optarg;
            break;
            default:
            	printf("exit\n");
            	exit(EXIT_FAILURE);
            break;

        }
    }*/

    start_server("./../sent.txt");

    return 0;
}
