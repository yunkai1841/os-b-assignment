#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "error.h"

void send_msg(int sockfd, char* msg) {
    int n;
    char buffer[256];

    // データを送信する
    n = send(sockfd, msg, strlen(msg), 0);
    if (n < 0) {
        exit_with_msg("ERROR writing to socket");
    }
    printf("send %d bytes\n", n);

    // 確認メッセージを受信する
    memset(buffer, 0, 256);
    n = recv(sockfd, buffer, 255, 0);
    if (n < 0) {
        exit_with_msg("ERROR reading from socket");
    }
    printf("Message from server: %s\n", buffer);
}

char* receive_msg(int sockfd) {
    int n;
    char buffer[256];

    // データを受信する
    memset(buffer, 0, 256);
    n = recv(sockfd, buffer, 255, 0);
    if (n < 0) {
        exit_with_msg("ERROR reading from socket");
    }
    printf("Message from server: %s\n", buffer);

    // 確認メッセージを送信する
    n = send(sockfd, "OK", 2, 0);
    if (n < 0) {
        exit_with_msg("ERROR writing to socket");
    }
    return buffer;
}