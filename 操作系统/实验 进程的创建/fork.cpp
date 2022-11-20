#include <iostream>
#include <unistd.h>
using namespace std;
int main() {
    pid_t pid = 5;
    int flag = 1;
    
    pid = fork();
    if(pid < 0)
        cout << "Error in fork!" << endl;
    else if (pid == 0) cout << "I am Child1!Pid is " << pid << ". Content:b." << "The true pid is " << getpid() << endl;
    else {
        cout << "I am Parent!Pid is " << pid << ". Content:a." << "The true pid is " << getpid() << endl;
        pid_t pid2 = fork();
        if (pid2 == 0) cout << "I am Child2!Pid is " << pid2 << ". Content:c." << "The true pid is " << getpid() << endl;
    }
    cout << "over." << endl;
    getchar();
    return 0;
}