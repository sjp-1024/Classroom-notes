
#include <iostream>
#include <algorithm>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
using namespace std;

int socket_connect_nonblock(char *ip, int port, long timeout) {
    int sockfd;
    struct timeval tm;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        return -1;
    }
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);
    unsigned long ul = 1; 
    //printf("Connect to %s : %d\n", ip, port);
    ioctl (sockfd, FIONBIO, &ul);
    fd_set wfds;
    FD_ZERO(&wfds);
    FD_SET(sockfd, &wfds);
    tm.tv_sec = 0;
    tm.tv_usec = timeout;
    int error = -1;
    int len = sizeof(int);
    int ret = -1 ;
    if(connect(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        if (select(sockfd + 1, NULL, &wfds, NULL, &tm) > 0) {
            if(getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, (socklen_t *) &len) < 0) {
                perror("getsockopt");
                ret = -1;
            }
            if (error == 0) {
                ret = 0;
            } else {
                ret = -1;
            }
        }
    }
    close(sockfd);
    return ret;
}

int main() {
    int port = 22;
    int ret;
    char ip[20] = {0};
    for (int i = 1; i <= 254; i++) {
        sprintf(ip, "192.168.2.%d", i);
        if ((ret = socket_connect_nonblock(ip, port, 100000)) == 0) {
            printf("已开启：%s\n", ip);
        }
    }
    return 0;
}

