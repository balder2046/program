#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <event.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#define SERVER_PORT 8000
#ifndef null
#define null 0
#endif

int debug = 0;

struct client
{
    int fd;
    struct bufferevent * buf_ev;
};
int setnonblock(int fd)
{
    int flags = fcntl(fd,F_GETFL);
    flags |= O_NONBLOCK;
    fcntl(fd,F_SETFL,flags);
}
void buf_read_callback(struct bufferevent *incoming,void *arg)
{
    struct evbuffer *evreturn;
    char *req;
    req = evbuffer_readline(incoming->input);
    if (req == null) {
        return;
    }

    struct client *client = (struct client *)arg;
    if (strcmp(req,"bye") == 0) {

    }
    evreturn = evbuffer_new();
    evbuffer_add_printf(evreturn,"You said %s\n",req);
    bufferevent_write_buffer(incoming,evreturn);
    evbuffer_free(evreturn);
    free(req);

}
void buf_write_callback(struct bufferevent * bev, void *arg) {

}
void buf_error_callback(struct bufferevent *bev,short what, void *arg) {
    struct client *client = (struct client *)arg;
    bufferevent_free(client->buf_ev);
    close(client->fd);
    printf("Error ,reason %d",what);
    free(client);
}
void accept_callback(int fd,short ev,void *arg)
{
    int client_fd;
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    struct client *client;
    client_fd = accept(fd,(struct sockaddr *)&client_addr,&client_len);
    if (client_fd < 0)
    {
        printf("Client: accept() failed");
        return;
    }
    setnonblock(client_fd);
    client = (struct client *)calloc(1,sizeof(struct client));
    if (client == null) {
        printf("malloc failed");
        return;
    }
    client->fd = client_fd;
    client->buf_ev = bufferevent_new(client_fd,buf_read_callback,
                                     buf_write_callback,
                                     buf_error_callback,
                                     client);
    bufferevent_enable(client->buf_ev,EV_READ);
    struct evbuffer *evreturn = evbuffer_new();
    evbuffer_add_printf(evreturn,"Hello ,Welcome ! input bye to quit!\n");
    bufferevent_write_buffer(client->buf_ev,evreturn);
    evbuffer_free(evreturn);
}
int main()
{
    int socketlisten;
    struct sockaddr_in addresslisten;
    struct event accept_event;
    int reuse = 1;
    event_init();
    socketlisten = socket(AF_INET,SOCK_STREAM,0);
    if (socketlisten < 0) {
        fprintf(stderr,"Fail to create listen socket!");
        return 1;
    }
    memset(&addresslisten,0,sizeof(addresslisten));
    addresslisten.sin_family = AF_INET;
    addresslisten.sin_addr.s_addr = INADDR_ANY;
    addresslisten.sin_port = htons(SERVER_PORT);
    if (bind(socketlisten,(struct sockaddr *)&addresslisten,sizeof(addresslisten)) < 0) {
        fprintf(stderr,"Failed to bind");
        return 1;
    }
    if (listen(socketlisten,5)< 0) {
        fprintf(stderr,"Failed to listen to socket");
        return 1;
    }
    setsockopt(socketlisten,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse));
    setnonblock(socketlisten);
    event_set(&accept_event,socketlisten,EV_READ|EV_PERSIST,accept_callback,NULL);
    event_add(&accept_event,NULL);
    event_dispatch();
    close(socketlisten);

    printf("hello world!");
    return 0;
}
