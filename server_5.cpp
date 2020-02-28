
#include <iostream>
#include "common_n.h"
#include <poll.h>
using namespace std;
#define MAX_N 200
#define PORT 8888
struct pollfd pfd[MAX_N + 5];
int max_fd ;

void do_accept(int listen_sock) {
    int new_fd;
    new_fd = accept(listen_sock, NULL, NULL);
    if (new_fd < 0) {
        perror("accept");
        return ;
    }
    for (int i = 1; i < MAX_N; i++) {
        if (pfd[i].fd != -1) continue;
        pfd[i].fd = new_fd;
        pfd[i].events = POLLIN;
        max_fd += 1;
        cout << "Has man join in" << endl;
        break;
    }
}


int main() {
    int listen_sock = socket_create(PORT);
    pfd[0].fd = listen_sock;
    pfd[0].events = POLLIN;
    max_fd = 1;
    for (int i = 1; i < MAX_N; i++) {
        pfd[i].fd = -1;
    }
    int reval;
    while (1) {
        reval = poll(pfd, max_fd, 5 * 1000);
        if (reval < 0) {
            perror("poll");
            break;
        } else if (reval == 0) {
            cout << "time out" << endl;
            continue;
        }
        if (pfd[0].revents == POLLIN) {
            do_accept(listen_sock);
        } else { // 接收客户端信息
            int client_fd;
            for (int i = 1; i < max_fd; i++) {
                if(pfd[i].revents != POLLIN) continue;
                client_fd = pfd[i].fd;
                struct sockaddr_in addr;
                socklen_t len = sizeof(addr);
                getpeername(client_fd, (struct sockaddr *)&addr, &len);
                char buff[1024] = {0};
                int k = recv(client_fd, buff, 1024, 0);
                if (k <= 0) {
                    cout << inet_ntoa(addr.sin_addr) << "  has logout" << endl;
                    max_fd -= 1;
                    int j;
                    for (j = i; j < max_fd; j++) {
                        pfd[j] = pfd[j + 1];
                    }
                    pfd[j].fd = -1;
                    close(client_fd);
                    i--;
                    continue;
                }
                cout << inet_ntoa(addr.sin_addr) << "--->" << buff << endl;
                k = send(client_fd, buff , strlen(buff), 0);
                if (k < 0) perror("send");
                else cout << "send : " << buff << endl;
            }
        
        } 
    }
    return 0;
}



