#include <fstream>
#include <iostream>
#include <cstring>
using namespace std;


main(){
ofstream dosya;
dosya.open("veriler.txt",ios::app);
char buffer[256];
buffer[0]={'1'};
bzero(buffer,256);
buffer[1]={'2'};
dosya<<buffer<<endl;
dosya.close();
}
