#include <iostream>
#include <string>
using namespace std;
char ch[26];
int main() {
    for(int i = 0; i < 26; ++i) {
        ch[i] = 'a' + i;
    }

    cout << "test data1: kind=10,length=100,frquence all 10." << endl;
    for(int i = 0; i < 10; ++i ) 
        for(int j = 0; j < 10; ++j) 
            cout << ch[i];
    return 0;
}