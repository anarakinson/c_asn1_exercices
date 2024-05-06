
#include <arpa/inet.h>
#include <conversions.h>
#include <net/if.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/sctp.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


#define PORT 9999
#define ADDRESS "127.0.0.1"

// #define PORT 36412
// #define ADDRESS "10.18.10.221"


void tx_send(uint8_t **buffer, ssize_t *len){

    // socket settings
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr(ADDRESS);

    // file descripttor
    int socket_fd = 0;
    int ret = 0;

    // create socket
    socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_SCTP);
    if (socket_fd < 0) {
        printf("ERROR: socket  failed\n");
        exit(EXIT_FAILURE);
    }

    // connect 
    ret = connect(socket_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (ret < 0) {
        printf("ERROR: connectiion failed\n");
        exit(EXIT_FAILURE);
    }

    // sending messsage
    ret = sctp_sendmsg(socket_fd, *buffer, *len, NULL, 0, 0, 0, 0, 0, 0);
    if (ret < 0) {
        printf("ERROR: sending message failed\n");
        exit(EXIT_FAILURE);
    }

    printf("SUCCESS: packet sent\n");

    return;

}

