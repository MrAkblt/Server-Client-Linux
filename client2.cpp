#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <thread>
#include <vector>
#include <arpa/inet.h>
#include <iostream>
using namespace std;
int s;
struct sockaddr_in server;
char *message;

vector<int> numbers;
 //Winsock Library
void createsocket(){
    if(!(s = socket(AF_INET , SOCK_STREAM , 0 )))
    {
        printf("Could not create socket");
        createsocket();
    }
    printf("Socket created.\n");
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    //server.sin_addr = *(in_addr *) gethostbyname("www.google.com")->h_addr_list[0];
    server.sin_family = AF_INET;
    server.sin_port = htons( 8888 );
}

void connecthost(){
    createsocket();
    if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0)
    {   
        puts("connect error");
        usleep(500*1000);
        connecthost(); 
    }

    puts("Connected");
}

void sendhost(){
    /*usleep(3000*1000);
    int result;
    while(true){
        if(!numbers.empty()){   
            string str=to_string(numbers.front());
            const char *pchar=str.c_str();
            if( result=send(s , pchar , strlen(pchar) , 0))
            {
                //printf("%d\n",result);
                printf("Data Send: %s\n",pchar);
                numbers.erase(numbers.begin()); 
            }
            else {
                
                puts("Send failed");
                connecthost();
            }
        }
        usleep(300*1000);
    }*/
    
    //usleep(3000*1000);
    int result;
    char server_reply[2000];
    try{
    while(true){
        if(!numbers.empty()){   
            string str=to_string(numbers.front());
            const char *pchar=str.c_str();
            if( result=write(s , pchar , strlen(pchar))>=0)
            {   
                if(recv(s , server_reply , 2000 , 0)){
                    //printf("%d\n",result);
                    printf("Data Send: %s\n",pchar);
                    numbers.erase(numbers.begin()); 
                }
                else {
                    puts("Send failed");
                    connecthost();
                }
            }

        }
        usleep(200*1000);
    }
    }catch(exception ex){
        std::cout<<ex.what()<<std::endl;
    }
}
void startcounter(){
    int i=0;
    while(true){
        numbers.push_back(i);
        usleep(1000*1000);
        i++;
    }
}

void replyfromhost(){
    int recv_size;
    char server_reply[2000];
    if(!(recv_size = recv(s , server_reply , 2000 , 0)))
    {
        puts("recv failed");
    }

    puts("Reply received\n");
    //Add a NULL terminating character to make it a proper string before printing
    server_reply[recv_size] = '\0';
    puts(server_reply);
}

main(int argc , char *argv[])
{

    //Create a socket
    createsocket();
    //Connect to remote server
    connecthost();
    //Receive a reply from the server
    //replyfromhost();
    //Send some data
    thread t1(startcounter);
    thread t2(sendhost);
    t1.join();
    t2.join();
    

}

