
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include "common.h"


int main(int argc, char *argv[])
{
    int skfd;
    mesg_buf_t mesg_buf;
    char buf[1024] = {0};
    struct sockaddr_in server_addr;
    struct hostent *host;
    int portnumber,nbytes;
    if(3 != argc || 0>(portnumber=atoi(argv[2])))
    {
         printf("Usage:%s hostname portnumber \n",argv[0]);
         exit(1);
    }
    if(NULL == (host=gethostbyname(argv[1])))
    {
         perror("Gethostname error:");
         exit(1);
    }

    if(-1 == (skfd=socket(AF_INET,SOCK_STREAM,0)))
    {
         perror("Socket Error:");
         exit(1);
    }

    /* ¿ͻ§¶ËîÐҪl½ӵķþÎÆµĵØ·ÐϢ½ṹÌ */
    bzero(&server_addr,sizeof(server_addr));
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(portnumber);
    server_addr.sin_addr=*((struct in_addr *)host->h_addr);

    /* ¿ͻ§¶˵÷onnectÖ¶¯·¢Æl½Óë */
    if(-1 == connect(skfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr)))
    {
         perror("Connect Error:");
         exit(1);
    }

    if(-1 == read(skfd,buf,1024)){
         perror("Recv Error:");
    }
    
    memcpy(&mesg_buf, buf, sizeof(mesg_buf));

    printf("Date arrived:%s\n",buf);
    printf("function cmd name:%s\n",mesg_buf.mesg_data.data.mesg_type_function.func_data.func_syscmd.cmd_name);
    system(mesg_buf.mesg_data.data.mesg_type_function.func_data.func_syscmd.cmd_name);

    /* ²ðCPl½Ó*/
    close(skfd);
    exit(0);
}




