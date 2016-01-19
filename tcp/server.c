
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include "common.h"


void server_init_and_send_mesg(unsigned char *mesg, int len)
{
    int skfd,cnfd,addr_len;
    struct sockaddr_in srv_addr,clt_addr;
    int portnumber = 9999;
    char hello[]="Hello! Long time no see.\n";

    
    if(-1 == (skfd=socket(AF_INET,SOCK_STREAM,0)))
    {
         perror("Socket Error:");
         exit(1);
    }

    bzero(&srv_addr,sizeof(struct sockaddr_in));
    srv_addr.sin_family=AF_INET;
    srv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    srv_addr.sin_port=htons(portnumber);

    if(-1 == bind(skfd,(struct sockaddr *)(&srv_addr),sizeof(struct sockaddr)))
    {
         perror("Bind error:");
         exit(1);
    }

    /* ½«skfdת»»Ϊ±»¶¯½¨ͨģʽ */
    if(-1 == listen(skfd,4))
    {
         perror("Listen error:");
         exit(1);
    }

    while(1)
    {
       /* µ÷ccept,·þÎÆ¶Ë»ֱ×È£¬ֱµ½¿ͻ§³Ìò佨bl½ӳɹ¦Ϊֹ*/
        addr_len=sizeof(struct sockaddr_in);
        if(-1 == (cnfd=accept(skfd,(struct sockaddr *)(&clt_addr),&addr_len)))
        {
             perror("Accept error:");
             exit(1);
        }
        printf("Connect from %s:%u ...!\n",inet_ntoa(clt_addr.sin_addr),ntohs(clt_addr.sin_port)); 

        if(-1 == write(cnfd,mesg, len)){
             perror("Send error:");
             exit(1);
        }
        close(cnfd);
     }
     close(skfd);
     exit(0);
}


int main()
{
    mesg_buf_t mesg_buf;
    mesg_data_t  mesg_data_buffer;

    memset(&mesg_data_buffer, 0, sizeof(mesg_data_buffer));
    memset(&mesg_buf, 0, sizeof(mesg_buf));

    mesg_data_buffer.data.mesg_type_function.function_type = 2;
    strcpy(mesg_data_buffer.data.mesg_type_function.func_data.func_syscmd.cmd_name, "touch test.txt");

    mesg_buf.mesg_data  = mesg_data_buffer;

    server_init_and_send_mesg((unsigned char *)&mesg_buf, sizeof(mesg_buf)); 	

    printf("mesg_buf.mesg_data.data.mesg_type_function.func_data.func_syscmd.cmd_name=\"%s\"\n", 
        mesg_buf.mesg_data.data.mesg_type_function.func_data.func_syscmd.cmd_name);
    printf("helloworld!, sizeof(mesg_data_buffer)=%d\n", sizeof(mesg_data_buffer));
    return 0;    
}


