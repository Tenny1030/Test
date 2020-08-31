#ifndef __SERVER_H__
#define __SERVER_H__

//服务端的sockfd
int s_sockfd;
//已连接的客户端数量
int clients;

pthread_mutex_t	mutex;
pthread_cond_t	cond;
pthread_attr_t	attr;


//初始化服务端
extern int init_socket(int port);
//卸载服务端
extern int uninit_socket(void);

extern void do_service(int sockfd);

extern int lis_acc(int max_lis);

#endif
