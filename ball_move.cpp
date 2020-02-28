

#include <iostream>
#include <algorithm>
#include <string.h>
#include <curses.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
using namespace std;
int yd_power = 30;
int ball_x  = 10, ball_y = 10;

void move(int){
    if (yd_power > 0) {
        yd_power -= 1;
        ball_y += (yd_power/10);
    }
}

int main() {
    signal(14, move);
    initscr();
    clear();
    char ball[2] = "O";
    struct itimerval tm;
    tm.it_value.tv_sec = 0;
    tm.it_value.tv_usec = 100000;
    tm.it_interval.tv_sec = 0;
    tm.it_interval.tv_usec = 100000;
    setitimer(ITIMER_REAL, &tm, NULL);
    while (1) {
        move(ball_x, ball_y);
        addstr(ball);
        refresh();
        sleep(10000);
        clear();
    }
    return 0;
}



