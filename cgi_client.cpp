#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

static const char* request = "/home/jiezai_cbd/projects/vscode_linux/ProcessPoolCGIServer/test\r\n";
int main( int argc, char* argv[] )
{
    
    if( argc <= 2 )
    {
        
        printf( "usage: %s ip_address port_number\n", basename( argv[0] ) );
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi( argv[2] );
    
    

    
    struct sockaddr_in server_address;
    bzero( &server_address, sizeof( server_address ) );
    server_address.sin_family = AF_INET;
    inet_pton( AF_INET, ip, &server_address.sin_addr );
    server_address.sin_port = htons( port );

    int sockfd = socket(PF_INET,SOCK_STREAM,0);
    if(connect(sockfd,(struct sockaddr*)&server_address,sizeof(server_address))<0)
    {
        printf("connection failed\n");
        close(sockfd);
        return 1;

    }  
    
    send(sockfd,request,strlen(request),0);

    char buffer[BUFFER_SIZE];

    memset(buffer,'\0',1024);
    int bytes_read = recv(sockfd,buffer,1024,0);
    printf("read in %d bytes from socket %d with content :%s\n",bytes_read,sockfd,buffer);

/*
    processpool<cgi_conn>* pool = processpool<cgi_conn>::create(listenfd);
    if(pool)
    {
        pool->run();
        delete pool;

    }
    */
    /*如前所述，main函数创建了文件描述符listenfd，那么就由它亲自关闭之*/
   
    return 0;
}