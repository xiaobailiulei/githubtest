/*************************************************************************
#	 FileName	: server.c
#	 Author		: fengjunhui 
#	 Email		: 18883765905@163.com 
#	 Created	: 2018年12月29日 星期六 13时44分59秒
 ************************************************************************/

#include<stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#include "common.h"


/************************************************
 *函数名：do_login
 *参   数：套接字、消息结构体
 *返回值：是否登陆成功
 *功   能：登陆
 *************************************************/
int do_login(int sockfd)
{	
	int n;
	MSG msg;

	while(1){
		printf("*************************************************************\n");
		printf("********  1：管理员模式    2：普通用户模式    3：退出********\n");
		printf("*************************************************************\n");
		printf("请输入您的选择（数字）>>");
		scanf("%d",&n);
		getchar();

		switch(n)
		{
			case 1:
				msg.msgtype  = ADMIN_LOGIN;
				msg.usertype = ADMIN;
				break;
			case 2:
				msg.msgtype =  USER_LOGIN;
				msg.usertype = USER;
				break;
			case 3:
				msg.msgtype = QUIT;
				if(send(sockfd, &msg, sizeof(MSG), 0)<0)
				{
					perror("do_login send");
					return -1;
				}
				recv(sockfd,&msg,sizeof(MSG),0);
				printf("%s\n",msg.recvmsg);
				close(sockfd);
				exit(0);
			default:
				printf("您的输入有误，请重新输入\n"); 
		}

		admin_or_user_login(sockfd,&msg);
	}

}



/**************************************
 *函数名：do_query
 *参   数：消息结构体
 *功   能：登陆
 ****************************************/
void do_admin_query(int sockfd,MSG *msg)
{
	printf("------------%s-----------%d.\n",__func__,__LINE__);
	char sql[1000] = {0};
	msg->msgtype = ADMIN_QUERY;
	memset(sql,0,sizeof(sql));
	send(sockfd, msg, sizeof(MSG), 0);
	while(1){
		recv(sockfd,sql,sizeof(sql),0);
		if(strcmp(sql,"123")==0)
		{
			break;
		}else{
			printf("%-7s\n",sql);
			
		}
		memset(sql,0,sizeof(sql));
		}
}


/**************************************
 *函数名：admin_modification
 *参   数：消息结构体
 *功   能：管理员修改
 ****************************************/
void do_admin_modification(int sockfd,MSG *msg)//管理员修改
{
	printf("------------%s-----------%d.\n",__func__,__LINE__);
	char sql[1000] = {0};
	int i;
	msg->msgtype = ADMIN_MODIFY;
	printf("要修改的员工的编号\n");
	scanf("%d",&msg->info.no);
	/*send(sockfd,msg,sizeof(MSG),0);
	while(1){
		memset(sql,0,sizeof(sql));
		recv(sockfd,sql,sizeof(sql),0);
		if(strcmp(sql,"123")==0)
		{
			break;
		}else{
			printf("%-7s\n",sql);
			
		}
		
	}*/
	printf("请输入要修改的内容\n");
	//msg->recvmsg = 
	printf("员工编号");
	scanf("%d",&msg->info.no);
	printf("员工姓名");
	scanf("%s",msg->info.name);
	printf("员工密码");
	scanf("%s",msg->info.passwd);
	printf("员工年龄");
	scanf("%d",&msg->info.age);
	printf("员工电话");
	scanf("%s",msg->info.phone);
	printf("员工地址");
	scanf("%s",msg->info.addr);
	printf("员工职位");
	scanf("%s",msg->info.work);
	printf("员工工作年限");
	scanf("%d",&msg->info.level);
	printf("员工工资");
	scanf("%lf",&msg->info.salary);
	printf("员工入职年月");
	scanf("%s",msg->info.date);
	send(sockfd,msg,sizeof(MSG),0);

}


/**************************************
 *函数名：admin_adduser
 *参   数：消息结构体
 *功   能：管理员创建用户
 ****************************************/
void do_admin_adduser(int sockfd,MSG *msg)//管理员添加用户
{		
	printf("------------%s-----------%d.\n",__func__,__LINE__);
	msg->msgtype = ADMIN_ADDUSER;
	printf("请输入权限\n");
	scanf("%d",&msg->info.usertype);
	printf("%d",msg->info.usertype);
	printf("请输入员工信息\n");
	printf("员工编号");
	scanf("%d",&msg->info.no);
	printf("员工姓名");
	scanf("%s",msg->info.name);
	printf("员工密码");
	scanf("%s",msg->info.passwd);
	printf("员工年龄");
	scanf("%d",&msg->info.age);
	printf("员工电话");
	scanf("%s",msg->info.phone);
	printf("员工地址");
	scanf("%s",msg->info.addr);
	printf("员工职位");
	scanf("%s",msg->info.work);
	printf("员工工作年限");
	scanf("%d",&msg->info.level);
	printf("员工工资");
	scanf("%lf",&msg->info.salary);
	printf("员工入职年月");
	scanf("%s",msg->info.date);
	send(sockfd, msg, sizeof(MSG), 0);
	
}


/**************************************
 *函数名：admin_deluser
 *参   数：消息结构体
 *功   能：管理员删除用户
 ****************************************/
void do_admin_deluser(int sockfd,MSG *msg)//管理员删除用户
{
	printf("------------%s-----------%d.\n",__func__,__LINE__);
	int a;
	msg->msgtype = ADMIN_DELUSER;
	printf("请输入员工编号删除\n");
	scanf("%d",&msg->info.no);
	send(sockfd,msg,sizeof(MSG),0);
	

}



/**************************************
 *函数名：do_history
 *参   数：消息结构体
 *功   能：查看历史记录
 ****************************************/
void do_admin_history (int sockfd,MSG *msg)
{
	printf("------------%s-----------%d.\n",__func__,__LINE__);
	msg->msgtype = ADMIN_HISTORY;
	char sql[1000] = {0};
	//msg->msgtype = ADMIN_QUERY;
	memset(sql,0,sizeof(sql));
	send(sockfd, msg, sizeof(MSG), 0);
	while(1){
		recv(sockfd,sql,sizeof(sql),0);
		if(strcmp(sql,"123")==0)
		{
			break;
		}else{
			printf("%-7s\n",sql);
			send(sockfd,msg,sizeof(MSG),0);
			
		}
		memset(sql,0,sizeof(sql));
		}
	

}


/**************************************
 *函数名：admin_menu
 *参   数：套接字、消息结构体
 *功   能：管理员菜单
 ****************************************/
void admin_menu(int sockfd,MSG *msg)
{
	int n;

	while(1)
	{
		printf("*************************************************************\n");
		printf("* 1：查询  2：修改 3：添加用户  4：删除用户  5：查询历史记录*\n");
		printf("* 6：退出													*\n");
		printf("*************************************************************\n");
		printf("请输入您的选择（数字）>>");
		scanf("%d",&n);
		getchar();

		switch(n)
		{
			case 1:
				do_admin_query(sockfd,msg);
				break;
			case 2:
				do_admin_modification(sockfd,msg);
				break;
			case 3:
				do_admin_adduser(sockfd,msg);
				break;
			case 4:
				do_admin_deluser(sockfd,msg);
				break;
			case 5:
				do_admin_history(sockfd,msg);
				break;
			case 6:
				msg->msgtype = QUIT;
				send(sockfd, msg, sizeof(MSG), 0);
				recv(sockfd,msg,sizeof(MSG),0);
				printf("%s\n",msg->recvmsg);
				close(sockfd);
				exit(0);
			default:
				printf("您输入有误，请重新输入！\n");
		}
	}
}


/**************************************
 *函数名：do_query
 *参   数：消息结构体
 *功   能：登陆
 ****************************************/
void do_user_query(int sockfd,MSG *msg)
{
	printf("------------%s-----------%d.\n",__func__,__LINE__);
	char sql[1000] = {0};
	int i;
	msg->msgtype = USER_QUERY;
	strcpy(msg->recvmsg,"123");
	send(sockfd,msg,sizeof(MSG),0);
	for(i=0;i<2;i++)
	{
		recv(sockfd,sql,sizeof(sql),0);
		send(sockfd,msg,sizeof(MSG),0);
		printf("%s\n",sql);
		memset(sql,0,sizeof(sql));
	}

}


/**************************************
 *函数名：do_modification
 *参   数：消息结构体
 *功   能：修改
 ****************************************/
void do_user_modification(int sockfd,MSG *msg)
{
	int n;
	printf("------------%s-----------%d.\n",__func__,__LINE__);
	msg->msgtype = USER_MODIFY;
	while(1){
	printf("**********修改内容*****************\n");
	printf("**1.密码***2.电话***3.地址***4.退出*\n");
	printf("***********************************\n");
	printf("请输入选项");
	scanf("%d",&n);
	switch (n)
	{		case 1:
					printf("请输入新密码\n");
					scanf("%s",msg->info.passwd);
					strcpy(msg->recvmsg,msg->info.passwd);
					strcpy(msg->amend,"passwd");
					send(sockfd,msg,sizeof(MSG),0);
					continue;
			case 2:
					printf("请输入新电话\n");
					scanf("%s",msg->info.phone);
					strcpy(msg->recvmsg,msg->info.phone);
					strcpy(msg->amend,"phone");
					send(sockfd,msg,sizeof(MSG),0);
					continue;
			case 3:
					printf("请输入新地址\n");
					scanf("%s",msg->info.addr);
					strcpy(msg->recvmsg,msg->info.addr);
					strcpy(msg->amend,"addr");
					send(sockfd,msg,sizeof(MSG),0);
					continue;
			case 4:
					//user_menu(sockfd,msg);
					return ;
			default:
				printf("您输入有误，请输入数字\n");
				break;
	
	}
	}

}


/**************************************
 *函数名：user_menu
 *参   数：消息结构体
 *功   能：管理员菜单
 ****************************************/
void user_menu(int sockfd,MSG *msg)
{
	printf("------------%s-----------%d.\n",__func__,__LINE__);
	int n;
	while(1)
	{
		printf("*************************************************************\n");
		printf("*************  1：查询  	2：修改		3：退出	 *************\n");
		printf("*************************************************************\n");
		printf("请输入您的选择（数字）>>");
		scanf("%d",&n);
		getchar();

		switch(n)
		{
			case 1:
				do_user_query(sockfd,msg);
				break;
			case 2:
				do_user_modification(sockfd,msg);
				break;
			case 3:
				msg->msgtype = QUIT;
				send(sockfd, msg, sizeof(MSG), 0);
				close(sockfd);
				exit(0);
			default:
				printf("您输入有误，请输入数字\n");
				break;
		}
	}
}




int admin_or_user_login(int sockfd,MSG *msg)
{
	printf("------------%s-----------%d.\n",__func__,__LINE__);
	//输入用户名和密码
	memset(msg->username, 0, NAMELEN);
	printf("请输入用户名：");
	scanf("%s",msg->username);
	getchar();

	memset(msg->passwd, 0, DATALEN);
	printf("请输入密码（6位）");
	scanf("%s",msg->passwd);
	getchar();

	//发送登陆请求
	send(sockfd, msg, sizeof(MSG), 0);
	//接受服务器响应
	recv(sockfd, msg, sizeof(MSG), 0);
	printf("msg->recvmsg :%s\n",msg->recvmsg);

	//判断是否登陆成功
	if(strncmp(msg->recvmsg, "OK", 2) == 0)
	{
		if(msg->usertype == ADMIN)
		{
			printf("亲爱的管理员，欢迎您登陆员工管理系统！\n");
			strcpy(msg->cunchu,msg->username);
			admin_menu(sockfd,msg);	
		}
		else if(msg->usertype == USER)
		{
			printf("亲爱的用户，欢迎您登陆员工管理系统！\n");
			strcpy(msg->cunchu,msg->username);
			user_menu(sockfd,msg);
		}
	}
	else
	{
		printf("登陆失败！%s\n", msg->recvmsg);
		return -1;
	}

	return 0;
}


int main(int argc, const char *argv[])
{
	//socket->填充->绑定->监听->等待连接->数据交互->关闭 
	int sockfd;
	int acceptfd;
	ssize_t recvbytes,sendbytes;
	struct sockaddr_in serveraddr;
	struct sockaddr_in clientaddr;
	socklen_t addrlen = sizeof(serveraddr);
	socklen_t cli_len = sizeof(clientaddr);

	//创建网络通信的套接字
	sockfd = socket(AF_INET,SOCK_STREAM, 0);
	if(sockfd == -1){
		perror("socket failed.\n");
		exit(-1);
	}
	printf("sockfd :%d.\n",sockfd); 

	//填充网络结构体
	memset(&serveraddr,0,sizeof(serveraddr));
	memset(&clientaddr,0,sizeof(clientaddr));
	serveraddr.sin_family = AF_INET;
//	serveraddr.sin_port   = htons(atoi(argv[2]));
//	serveraddr.sin_addr.s_addr = inet_addr(argv[1]);
	serveraddr.sin_port   = htons(5001);
	serveraddr.sin_addr.s_addr = inet_addr("192.168.1.161");

	if(connect(sockfd,(const struct sockaddr *)&serveraddr,addrlen) == -1){
		perror("connect failed.\n");
		exit(-1);
	}

	do_login(sockfd);

	close(sockfd);

	return 0;
}



