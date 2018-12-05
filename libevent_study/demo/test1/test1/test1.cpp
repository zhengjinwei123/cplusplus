//// test1.cpp : 定义控制台应用程序的入口点。
////
//
//#include "stdafx.h"
//#include <string.h>
//#include <errno.h>
//#include <stdio.h>
//#include "event2/bufferevent.h"
//#include "event2/buffer.h"
//#include "event2/listener.h"
//#include "event2/util.h"
//#include "event2/event.h"
//#include "event2/event-config.h"
//#include <WinSock2.h>
//#include <iostream>
//#define IP_ADDRESS ("127.0.0.1")
//#define PORT (9951)
//int m_isrun = 0;
//int tcp_connect_server(const char* server_ip, int port);
//void cmd_msg_cb(int fd, char* msg);
//void socket_read_cb(int fd, short events, void *arg);
//DWORD WINAPI Fun1Proc(LPVOID lpParameter)
//{
//	char t_cin[1024];
//	int sockfd = (int)lpParameter;
//	while (1) {
//		memset(t_cin, 0, 1024);
//
//		std::cin >> t_cin;
//
//		if (strcmp(t_cin, "exit") == 0) {
//			break;
//		}
//		cmd_msg_cb(sockfd, t_cin);
//	}
//	exit(1);
//	return 0;
//}
//int main(int argc, char** argv)
//{
//	//加载套接字库  
//	WSADATA wsaData;
//	int iRet = 0;
//	iRet = WSAStartup(MAKEWORD(2, 2), &wsaData);
//	if (iRet != 0)
//	{
//		return -1;
//	}
//
//	if (2 != LOBYTE(wsaData.wVersion) || 2 != HIBYTE(wsaData.wVersion))
//	{
//		WSACleanup();
//		return -1;
//	}
//	//两个参数依次是服务器端的IP地址、端口号  
//	int sockfd = tcp_connect_server(IP_ADDRESS, PORT);
//	if (sockfd == -1)
//	{
//		perror("tcp_connect error ");
//		return -1;
//	}
//	printf("connect to server successful\n");
//	struct event_base* base = event_base_new();
//	struct event *ev_sockfd = event_new(base, sockfd, EV_READ | EV_PERSIST, socket_read_cb, NULL);
//	event_add(ev_sockfd, NULL);
//	//创建线程发送数据
//	HANDLE hThread1 = CreateThread(NULL, 0, Fun1Proc, (void*)sockfd, 0, NULL);
//	CloseHandle(hThread1);
//	event_base_dispatch(base);
//	WSACleanup();
//	printf("finished \n");
//	return 0;
//}
//void cmd_msg_cb(int fd, char* msg)
//{
//	//把终端的消息发送给服务器端  
//	int ret = send(fd, (const char*)msg, strlen((char*)msg), 0);
//	if (ret <= 0)
//	{
//		perror("read fail ");
//		return;
//	}
//	printf("send:%s\n", (char*)msg);
//}
//void socket_read_cb(int fd, short events, void *arg)
//{
//	char msg[1024];
//	//为了简单起见，不考虑读一半数据的情况  
//	int len = recv(fd, msg, sizeof(msg) - 1, 0);
//	if (len <= 0)
//	{
//		perror("read fail ");
//		exit(1);
//	}
//	msg[len] = '\0';
//	printf("recv %s from server\n", msg);
//}
//int tcp_connect_server(const char* server_ip, int port)
//{
//	int sockfd, status, save_errno;
//	SOCKADDR_IN  server_addr;
//
//	memset(&server_addr, 0, sizeof(server_addr));
//
//	server_addr.sin_family = AF_INET;
//	server_addr.sin_addr.s_addr = inet_addr(server_ip);
//	server_addr.sin_port = htons(port);
//
//	sockfd = ::socket(PF_INET, SOCK_STREAM, 0);
//	if (sockfd == -1)
//		return sockfd;
//
//
//	status = ::connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
//
//	if (status == -1)
//	{
//		save_errno = errno;   //清理  
//		closesocket(sockfd);
//		errno = save_errno; //the close may be error  
//		return -1;
//	}
//
//	evutil_make_socket_nonblocking(sockfd);
//
//	return sockfd;
//}
//
//



#include<stdio.h>  
#include<string.h>  
#include<errno.h>
#include <signal.h>
#include "event2/bufferevent.h"
#include "event2/buffer.h"
#include "event2/listener.h"
#include "event2/util.h"
#include "event2/event.h"
#include <event2/event-config.h>
#include <WinSock2.h>

#define IP_ADDRESS ("127.0.0.1")
#define PORT (9951)

void accept_cb(int fd, short events, void* arg);
void socket_read_cb(int fd, short events, void *arg);
int tcp_server_init(int port, int listen_num);

int main(int argc, char** argv)
{
	//加载套接字库  
	WSADATA wsaData;
	int iRet = 0;
	iRet = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iRet != 0)
	{
		//cout << "WSAStartup(MAKEWORD(2, 2), &wsaData) execute failed!" << endl;;
		return -1;
	}
	if (2 != LOBYTE(wsaData.wVersion) || 2 != HIBYTE(wsaData.wVersion))
	{
		WSACleanup();
		//cout << "WSADATA version is not correct!" << endl;
		return -1;
	}
	int listener = tcp_server_init(PORT, 10);
	if (listener == -1)
	{
		perror(" tcp_server_init error ");
		return -1;
	}
	struct event_base* base = event_base_new();
	//添加监听客户端请求连接事件  
	struct event* ev_listen = event_new(base, listener, EV_READ | EV_PERSIST,
		accept_cb, base);
	event_add(ev_listen, NULL);
	event_base_dispatch(base);
	WSACleanup();
	return 0;
}

void accept_cb(int fd, short events, void* arg)
{
	evutil_socket_t sockfd;
	struct sockaddr_in client;
	socklen_t len = sizeof(client);
	sockfd = ::accept(fd, (struct sockaddr*)&client, &len);
	evutil_make_socket_nonblocking(sockfd);
	printf("accept a client %d\n", sockfd);
	struct event_base* base = (event_base*)arg;
	//仅仅是为了动态创建一个event结构体  
	struct event *ev = event_new(NULL, -1, 0, NULL, NULL);
	//将动态创建的结构体作为event的回调参数  
	event_assign(ev, base, sockfd, EV_READ | EV_PERSIST,
		socket_read_cb, (void*)ev);
	event_add(ev, NULL);
}

void socket_read_cb(int fd, short events, void *arg)
{
	char msg[4096];
	struct event *ev = (struct event*)arg;
	int len = recv(fd, msg, sizeof(msg) - 1, 0);
	if (len <= 0)
	{
		printf("some error happen when read\n");
		event_free(ev);
		closesocket(fd);
		return;
	}
	msg[len] = '\0';
	printf("recv the client msg: %s\n", msg);
	char reply_msg[4096] = "I have recvieced the msg: ";
	strcat(reply_msg + strlen(reply_msg), msg);
	int ret = send(fd, reply_msg, strlen(reply_msg), 0);
}

int tcp_server_init(int port, int listen_num)
{
	int errno_save;
	int listener;
	listener = ::socket(AF_INET, SOCK_STREAM, 0);
	if (listener == -1)
		return -1;
	//允许多次绑定同一个地址。要用在socket和bind之间  
	evutil_make_listen_socket_reuseable(listener);
	struct sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = 0;
	sin.sin_port = htons(port);
	if (::bind(listener, (struct sockaddr*)&sin, sizeof(sin)) < 0) {
		errno_save = errno;
		evutil_closesocket(listener);
		errno = errno_save;
		return -1;
	}
	if (::listen(listener, listen_num) < 0) {
		errno_save = errno;
		evutil_closesocket(listener);
		errno = errno_save;
		return -1;
	}
	//跨平台统一接口，将套接字设置为非阻塞状态  
	evutil_make_socket_nonblocking(listener);
	return listener;
}
