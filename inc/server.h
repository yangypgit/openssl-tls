#ifndef __SERVER_H__
#define __SERVER_H__

#include <string>
#include <unordered_map>
#include <memory>

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <arpa/inet.h>

#include "client.h"

using client_map = std::unordered_map<size_t, std::shared_ptr<client>>;

struct client_info
{
    size_t fd;
    struct sockaddr_in addr;
};

class server
{
public:
    server();
    server(std::string ip, int port);
    ~server();

    bool initial();
    void destroy();

    client_info accept();

    bool add_client(size_t port, std::shared_ptr<client> cli);
    bool remove_client(size_t port);

    size_t get_socket_fd() const { return fd_; }
private:
    int create_fd();
    int create_nonblocking_fd();
    int create_epoll_fd();

    int bind();
    int listen(int num = SOMAXCONN);

private:
    std::string ip_;
    int         port_;
    size_t      fd_;

    client_map * client_map_;
};

#endif // __SERVER_H__
