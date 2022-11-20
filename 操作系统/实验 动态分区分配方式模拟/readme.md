# 动态分区分配方式的模拟

## 一、实验目的
了解动态分区分配方式中使用的数据结构和分配算法，并进一步加深对动态分区存储管理方式及其实现过程的理解。
## 二、实验要求
(1) 用C语言实现采用首次适应算法的动态分区分配过程alloc()和回收过程free()。空闲分区通过空闲分区链来管理;在进行内存分配时，系统优先使用空闲区低端的空间。
(2) 假设初始状态下，可用的内存空间为640KB，并有下列的请求序列:

- 作业1申请130KB

- 作业2释放60KB

- 作业3申请100KB

- 作业2释放60KB

- 作业4申请200KB

- 作业3释放100KB

- 作业1释放130KB

- 作业5申请140KB

- 作业6申请60KB

- 作业7申请50KB

- 作业6释放60KB。

  

请采用首次适应算法进行内存块的分配和回收,要求每次分配和回收后显示出空闲内存分区链的情况。

## 三、实验内容

### 1、数据结构

定义**请求序列**结构体，num代表作业号，state代表该作业申请还是释放空间，len代表该做也申请或释放空间的大小。

```cpp
//定义请求序列结构体
struct Allocquery {
    int num;
    char state;  //a表示申请(apply)，f表示释放（free）
    int len;    //长度
    Allocquery(int n = 0, char s = 'f', int l = 0):num(n), state(s), len(l){}
} alocq[MaxNum];  
```

定义**内存分配队列**结构体，flag为0时表示该内存块空闲，为其他数值则表示相应作业。如为1则表示存储的是作业1。firstadd表示该内存块的首地址，len表示该内存块的大小。

```cpp
//定义内存分配队列
struct Freequery {
    int flag;   //0表示空闲，其他数值表示相应作业
    int firstadd;   //起始地址
    int len;        //占有长度
    Freequery(int f = 0, int fi = 0, int l = 0) : flag(f), firstadd(fi), len(l) {}
} freeq[MaxNum];
```

### 2、初始化

从文件中读取，in.txt内容为题意要求的作业请求队列，1 a 130表示作业1申请130KB的空间

> 1 a 130
>
> 2 f 60
>
> 3 a 100
>
> 2 f 60
>
> 4 a 200
>
> 3 f 100
>
> 1 f 130
>
> 5 a 140
>
> 6 a 60
>
> 7 a 50
>
> 6 f 60

定义常量

```cpp
const string InputFileName = "in.txt";
const string OutputFileName = "out.txt";
const int MaxNum = 11;
```



首先初始化作业请求序列，利用c++文件流，初始化每个作业请求。

```cpp
//初始化作业请求序列
void initAlocq() {
    ifstream infp(InputFileName, ios::in);
    int index = 0;
    while(!infp.eof() && index < MaxNum) {
        int num;
        stringstream ss;
        infp >> alocq[index].num >> alocq[index].state >> alocq[index].len;
        ++index;
    }
    infp.close();
}
```



然后初始化内存空间，注意Freequery的构造函数中默认参数中len一开始都为0，也就是说len为0则这个内存块不存在，可以作为循环结束的依据，所以一开始将freeq[0]的长度置为整个内存空间的长度。

```cpp
void initFreeq() {
    freeq[0].flag = 0, freeq[0].firstadd = 0, freeq[0].len = 640;
}
```

### 3、主程序

对每次作业请求执行操作，并显示执行结果在文件out.txt中。其中Freetotal表示内存空余块的数量，一开始当然为1，first_alg为首次适应算法，参数为请求块、当前空块个数、内存分配队列 。                          

```cpp
void Run() {
    ofstream outfp(OutputFileName, ios::out);
    int Freetotal = 1;
    //对每次作业请求执行操作，显示执行结果
    for(int i = 0; i < MaxNum; ++i ) {
        first_alg(alocq[i], Freetotal, freeq);
        outfp << "序列" << i+1 <<  ":作业" << alocq[i].num;
        if(alocq[i].state == 'a') outfp << "申请" << alocq[i].len << "K\n";
        else outfp << "释放" << alocq[i].len << "K\n";
        outfp << "Now total free blocks:" << Freetotal << endl;
        outfp << "IDNum\taddress\t\tlength"<< endl;
        for(int j = 0 ; freeq[j].len != 0; ++j) {
            outfp << "  " << freeq[j].flag << "\t\t   "
                << freeq[j].firstadd << "\t\t  "
                << freeq[j].len << endl;
        }
        outfp << "--------------------------------------------------\n" << endl;

    }
    outfp.close();
}
int main() {
    initAlocq();
    initFreeq();
    Run();
    return 0;
}
```



**首次适应算法**，参数为请求块、当前空块个数、内存分配队列

函数声明：

```cpp
void first_alg(Allocquery nowaloc, int &ptotal, Freequery *pfreeq);
```

首先判断是申请空间还是释放空间，若为申请空间，遍历所有内存块。当且仅当该内存块pfreeq[i]没有被分配，且大小大于等于申请的空间量，将该块分配给该作业，并将空块合并，详细的合并方法在注释里都有体现。若为释放空间，那就找到待释放的块将其释放，并将释放后空闲区合并。

```cpp
//首次适应算法
//参数为请求块、当前空块个数、内存具体使用情况
void first_alg(Allocquery nowaloc, int &ptotal, Freequery *pfreeq){
    Freequery temp;
    Freequery temp_f1, temp_f2;
    if(nowaloc.state == 'a') {
        //申请空间
        for(int i = 0; i < MaxNum; ++i) {
            //该内存块空闲 且空间足以分给该作业
            if(pfreeq[i].flag == 0 && pfreeq[i].len >= nowaloc.len) {
                temp.flag = pfreeq[i].flag;
                temp.firstadd = pfreeq[i].firstadd+nowaloc.len; //首地址下移
                temp.len = pfreeq[i].len-nowaloc.len;           //剩余空间长度
                //找到的空块长度正好等于请求块，则立刻分配
                pfreeq[i].flag = nowaloc.num;
                pfreeq[i].len = nowaloc.len;
                if(pfreeq[i+1].len == 0) {
                    //找到的空块正好是全部剩余空间
                    pfreeq[i+1] = temp;
                } else if (pfreeq[i+1].firstadd != temp.firstadd){
                    //前后被占用，空块在中间，且长度大于请求块
                    temp_f1 = temp;
                    temp_f2 = pfreeq[i+1];
                    int j;
                    for(j = i+1; pfreeq[j].len != 0; ++j) {
                        pfreeq[j] = temp_f1;
                        temp_f1 = temp_f2;
                        temp_f2 = pfreeq[j+1];
                    }
                    pfreeq[j] = temp_f1;
                }
                break;
            }
        } 
    } else {
        //释放空间
        for(int i = 0; i < MaxNum; ++i) {
            if(pfreeq[i].flag == nowaloc.num) {
                //找到待回收的块
                if(i > 0 && pfreeq[i-1].flag == 0 && pfreeq[i+1].flag == 0) {
                    //前后都为空块，且回收块的首地址不是0
                    pfreeq[i-1].len = pfreeq[i-1].len + nowaloc.len + pfreeq[i+1].len;
                    for(int j = i; pfreeq[j].len != 0; ++j) {
                            //三块合并后队列变化
                        pfreeq[j] = pfreeq[j+2];
                    }
                } else if(i > 0 && pfreeq[i-1].flag == 0) {
                        //前为空块,后不为空块，且不是首块
                        pfreeq[i-1].len = pfreeq[i-1].len + nowaloc.len;
                        for(int j = i; pfreeq[j].len != 0; ++j) {
                            //两块合并后队列变化
                            pfreeq[j] = pfreeq[j+1];
                        }
                } else if(pfreeq[i+1].flag == 0) {
                    //后为空块
                    pfreeq[i].flag = 0;
                    pfreeq[i].len = nowaloc.len + pfreeq[i+1].len;
                    for(int j = i+1; pfreeq[j].len != 0; ++j) {
                        pfreeq[j] = pfreeq[j+1];
                    }
                } else {
                    //前后都不空
                    pfreeq[i].flag = 0;
                }
            }
        }
    }
    int fnum = 0;   //统计空闲块
    for(int i = 0; pfreeq[i].len != 0; ++i) 
        if(pfreeq[i].flag == 0) ++fnum;
    ptotal = fnum;
}
```

## 四、实验结果

![out](out.png)

## 五、完整代码

```cpp
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;
const string InputFileName = "in.txt";
const string OutputFileName = "out.txt";
const int MaxNum = 11;
//定义请求序列结构体
struct Allocquery {
    int num;
    char state;  //a表示申请(apply)，f表示释放（free）
    int len;    //长度
    Allocquery(int n = 0, char s = 'f', int l = 0):num(n), state(s), len(l){}
} alocq[MaxNum];  
//定义内存分配队列
struct Freequery {
    int flag;   //0表示空闲，其他数值表示相应作业
    int firstadd;   //起始地址
    int len;        //占有长度
    Freequery(int f = 0, int fi = 0, int l = 0) : flag(f), firstadd(fi), len(l) {}
} freeq[MaxNum];

//首次适应算法
//参数为请求块、当前空块个数、内存分配队列
void first_alg(Allocquery nowaloc, int &ptotal, Freequery *pfreeq);

//初始化作业请求序列
void initAlocq() {
    ifstream infp(InputFileName, ios::in);
    int index = 0;
    while(!infp.eof() && index < MaxNum) {
        int num;
        stringstream ss;
        infp >> alocq[index].num >> alocq[index].state >> alocq[index].len;
        //cout << alocq[index].num << ' ' << alocq[index].state << ' ' << alocq[index].len << endl;
        ++index;
    }
    infp.close();
}
//初始化内存空间
void initFreeq() {
    freeq[0].flag = 0, freeq[0].firstadd = 0, freeq[0].len = 640;
}
void Run() {
    ofstream outfp(OutputFileName, ios::out);
    int Freetotal = 1;
    //对每次作业请求执行操作，显示执行结果
    for(int i = 0; i < MaxNum; ++i ) {
        first_alg(alocq[i], Freetotal, freeq);
        outfp << "序列" << i+1 <<  ":作业" << alocq[i].num;
        if(alocq[i].state == 'a') outfp << "申请" << alocq[i].len << "K\n";
        else outfp << "释放" << alocq[i].len << "K\n";
        outfp << "Now total free blocks:" << Freetotal << endl;
        outfp << "IDNum\taddress\t\tlength"<< endl;
        for(int j = 0 ; freeq[j].len != 0; ++j) {
            outfp << "  " << freeq[j].flag << "\t\t   "
                << freeq[j].firstadd << "\t\t  "
                << freeq[j].len << endl;
        }
        outfp << "--------------------------------------------------\n" << endl;

    }
    outfp.close();
}
int main() {
    initAlocq();
    initFreeq();
    Run();
    return 0;
}
//首次适应算法
//参数为请求块、当前空块个数、内存具体使用情况
void first_alg(Allocquery nowaloc, int &ptotal, Freequery *pfreeq){
    Freequery temp;
    Freequery temp_f1, temp_f2;
    if(nowaloc.state == 'a') {
        //申请空间
        for(int i = 0; i < MaxNum; ++i) {
            //该内存块空闲 且空间足以分给该作业
            if(pfreeq[i].flag == 0 && pfreeq[i].len >= nowaloc.len) {
                temp.flag = pfreeq[i].flag;
                temp.firstadd = pfreeq[i].firstadd+nowaloc.len; //首地址下移
                temp.len = pfreeq[i].len-nowaloc.len;           //剩余空间长度
                //找到的空块长度正好等于请求块，则立刻分配
                pfreeq[i].flag = nowaloc.num;
                pfreeq[i].len = nowaloc.len;
                if(pfreeq[i+1].len == 0) {
                    //找到的空块正好是全部剩余空间
                    pfreeq[i+1] = temp;
                } else if (pfreeq[i+1].firstadd != temp.firstadd){
                    //前后被占用，空块在中间，且长度大于请求块
                    temp_f1 = temp;
                    temp_f2 = pfreeq[i+1];
                    int j;
                    for(j = i+1; pfreeq[j].len != 0; ++j) {
                        pfreeq[j] = temp_f1;
                        temp_f1 = temp_f2;
                        temp_f2 = pfreeq[j+1];
                    }
                    pfreeq[j] = temp_f1;
                }
                break;
            }
        } 
    } else {
        //释放空间
        for(int i = 0; i < MaxNum; ++i) {
            if(pfreeq[i].flag == nowaloc.num) {
                //找到待回收的块
                if(i > 0 && pfreeq[i-1].flag == 0 && pfreeq[i+1].flag == 0) {
                    //前后都为空块，且回收块的首地址不是0
                    pfreeq[i-1].len = pfreeq[i-1].len + nowaloc.len + pfreeq[i+1].len;
                    for(int j = i; pfreeq[j].len != 0; ++j) {
                            //三块合并后队列变化
                        pfreeq[j] = pfreeq[j+2];
                    }
                } else if(i > 0 && pfreeq[i-1].flag == 0) {
                        //前为空块,后不为空块，且不是首块
                        pfreeq[i-1].len = pfreeq[i-1].len + nowaloc.len;
                        for(int j = i; pfreeq[j].len != 0; ++j) {
                            //两块合并后队列变化
                            pfreeq[j] = pfreeq[j+1];
                        }
                } else if(pfreeq[i+1].flag == 0) {
                    //后为空块
                    pfreeq[i].flag = 0;
                    pfreeq[i].len = nowaloc.len + pfreeq[i+1].len;
                    for(int j = i+1; pfreeq[j].len != 0; ++j) {
                        pfreeq[j] = pfreeq[j+1];
                    }
                } else {
                    //前后都不空
                    pfreeq[i].flag = 0;
                }
            }
        }
    }
    int fnum = 0;   //统计空闲块
    for(int i = 0; pfreeq[i].len != 0; ++i) 
        if(pfreeq[i].flag == 0) ++fnum;
    ptotal = fnum;
}
```

