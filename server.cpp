/*
    Live Server on port 8888
*/
#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

int s , new_socket;
struct sockaddr_in server , client;
int c;
char *message;

void createserversocket(){
    bzero((char *) &server, sizeof(server));
    if(!(s = socket(AF_INET , SOCK_STREAM , 0 )))
    {
        printf("Could not create socket");
        exit (EXIT_FAILURE); 
    }
    printf("Socket created.\n");

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );
    if( bind(s ,(struct sockaddr *)&server , sizeof(server))<0)
    {
        printf("Bind failed with error code");
        exit (EXIT_FAILURE);   
    }
    puts("Bind done");

}
void waitconnection(){
    listen(s , 3);

    //Accept and incoming connection
    puts("Waiting for incoming connections...");

    c = sizeof(struct sockaddr_in);
    //accept baglantý gelene kadar o satýrda bekletir.
    if( (new_socket = accept(s , (struct sockaddr *)&client, (socklen_t *)&c)))
    {
        puts("Connection accepted");
    }
    if (!new_socket)
    {
        printf("accept failed with error code");
        waitconnection();
    }
}
//Gelen veriyi dosyaya yaz.
void receivedata(){
   /* int n;
    char buffer[256];
    ofstream dosya;
    dosya.open("veriler.txt",ios::app);
    while(true){
        bzero(buffer,256);
        n = read(new_socket,buffer,255);
        if (n < 0) {printf("ERROR reading from socket"); waitconnection();}
        if (n > 0){//printf("Here is the message: %s\n",buffer);
            cout<<buffer<<endl;
            dosya<<buffer<<endl;
        }  
    }
    dosya.close();*/

    char data[256];
    ofstream dosya;
    dosya.open("veriler.txt",ios::app);
    while(true){
        bzero(data,256);
        if(recv(new_socket , data ,256 , 0))
        {
            cout<<data<<endl;
            dosya<<data<<endl;
            send(new_socket , "a" , strlen("a") , 0);
        }
        else {printf("ERROR reading from socket\n"); waitconnection();}
    }
    dosya.close();
}

int main(int argc , char *argv[])
{

    //Create a socket
    createserversocket();
    //Listen to incoming connections
    waitconnection();
    receivedata();
    close(new_socket);
    close(s);

    return 0;
}
