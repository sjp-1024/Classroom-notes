

#include <iostream>
#include <algorithm>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
using namespace std;

time_t t;
struct tm *tim;
void sleep_wake(int) {
    time(&t);
    tim = localtime(&t);
    cout << "Signal time : " << tim->tm_hour << " : " << tim->tm_min << " : " << tim->tm_sec << endl;
}

int main() {
    int sleep_time;
    cout << "请输入睡眠时间(s)：" ;
    cin >> sleep_time;
    signal(SIGALRM, sleep_wake);
    time(&t);
    tim = localtime(&t);
    cout << "Start time : " << tim->tm_hour << " : " << tim->tm_min << " : " << tim->tm_sec << endl;
    cout << "Sleep start" << endl ;
    alarm(sleep_time);
    pause();
    cout << "Sleep over" << endl;
    time(&t);
    tim = localtime(&t);
    cout << "End time : " << tim->tm_hour << " : " << tim->tm_min << " : " << tim->tm_sec << endl;
    return 0;
}



