#include "server.h"

#include <cstring>

#define CHK_RET(ret) if (ret < 0) { return false; }

server::server()
{
}

server::server(std::string ip, int port) 
    : ip_(ip), port_(port)/*, client_map_(nullptr)*/
{
}

server::~server()
{
}

bool server::initial()
{
    int ret = -1;
    fd_ = create_fd();
    CHK_RET(fd_);

    ret = bind();
    CHK_RET(ret);

    ret = listen();
    CHK_RET(ret);

    return true;
}

void server::destroy()
{
    close(fd_);
}

bool server::add_client(size_t port, std::shared_ptr<client> cli)
{
    // lock
    client_map_->insert(std::make_pair(port, cli));

    return true;
}

bool server::remove_client(size_t port)
{

    return true;
}

int server::create_fd()
{
    int fd = ::socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        // error log
    }

    return fd;
}

int server::create_nonblocking_fd()
{
    int fd = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, 0);
    if (fd < 0)
    {
        // error log
    }

    return fd;
}

int server::create_epoll_fd()
{
    int fd = ::epoll_create(EPOLL_CLOEXEC);
    if (fd < 0)
    {
        // error log
    }

    return fd;
}

int server::bind()
{
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip_.data());
    addr.sin_port = htons(port_);

    socklen_t len = sizeof(addr);

    int ret = ::bind(fd_, (struct sockaddr*)&addr, len);
    if (ret < 0)
    {
        // error log
    }

    return ret;
}

int server::listen(int num)
{
    int ret = ::listen(fd_, num);
    if (ret < 0)
    {
        // error log
    }

    return ret;
}

client_info server::accept()
{
    struct client_info info;
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));

    socklen_t len = sizeof(addr);

    int conn_fd = ::accept(fd_, (struct sockaddr*)&addr, &len);
    if (conn_fd < 0)
    {
        // error log
    }

    info.fd = conn_fd;
    info.addr = addr;

    return info;
}

