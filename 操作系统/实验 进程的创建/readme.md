<h2 align='center' > 编程实验3:创建进程</h2>

# 一、实验目的

熟悉操作系统程序接口的使用。

# 二、实验内容

编写一段程序，使用系统调用fork( )创建两个子进程。当此程序运行时，在系统中有一个父进程和两个子进程活动。让每一个进程在屏幕上显示一个字符：父进程显示'a'，子进程分别显示字符'b'和字符'c'。

# 三、实验代码

*unistd.h* 是Linux/Unix系统中内置头文件，包含了许多系统服务的函数原型，例如read函数、write函数和getpid函数等。其作用相当于windows操作系统的"windows.h"，是操作系统为用户提供的统一API接口，方便调用系统提供的一些服务。

**fork函数在当前进程调用后，会产生一个子进程并返回子进程的pid，在子进程中，fork返回的值是0，因此，可以写得测试代码如下**

```c++
#include <iostream>
#include <unistd.h>
using namespace std;
int main() {
    pid_t pid = 5;
    int flag = 1;
    pid = fork();
    if(pid < 0)
        cout << "Error in fork!" << endl;
    else if (pid == 0) cout << "I am Child1!Pid is " << pid << ". content:b" << endl;
    else {
        cout << "I am Parent!Pid is " << pid << ". content:a" << endl;
        pid_t pid2 = fork();
        if (pid2 == 0) cout << "I am Child2!Pid is " << pid2 << ". content:c" << endl;
    }
    cout << "over." << endl;
    return 0;
}
```

# 四、运行结果截图

第一次运行

![第一次运行](第一次运行.png)

第二次运行

![第二次运行](第二次运行.png)

可以看出三个进程执行互不干预，结果具有不可再现性~

加了一行IO阻塞后，打开任务管理器查看进程号，发现确实有三个进程

![img](fork.png)
