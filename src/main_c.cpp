#include <iostream>

#include <cstring>

#include "client.h"

void test1()
{
    std::cout << "=====client start main=====" << '\n';

    ssl_tls tls;
    tls.two_way_auth = true;
#if 0
    tls.ca_certf = std::string("../etc/centos7/ca.crt");
    tls.certf    = std::string("../etc/centos7/client.crt");
    tls.private_key  = std::string("../etc/centos7/client.key");
    tls.passwd  = std::string("uway123");
#else
    tls.ca_certf = std::string("../etc/ubuntu18/cacert.pem");
    tls.certf    = std::string("../etc/ubuntu18/client.crt");
    tls.private_key  = std::string("../etc/ubuntu18/client.key");
    tls.passwd  = std::string("yyp123");
#endif
    tls.meth = TLSv1_client_method();

    std::shared_ptr<client> c = std::make_shared<client>("127.0.0.1", 9999, tls);
    // std::shared_ptr<client> c = std::make_shared<client>("127.0.0.1", 9999);
    if (c->initial() == false)
    {
        std::cout << "client initial error!" << '\n';
        return ;
    }

    char buffer[1024] = {0};
    for (int i = 0; i < 10; ++i)
    {
        int ret = c->send_msg("hello world!", strlen("hello world!"));
        if (ret < 0)
        {
            std::cout << "send_msg error!" << '\n';
            break;
        }

        ret = c->recv_msg(buffer, 1024);
        if (ret < 0)
        {
            std::cout << "recv_msg error!" << '\n';
            break;
        }

        buffer[ret] = '\0';
        std::cout << "\033[32mclient fd: " << c->get_socket_fd() << ", recv msg: " << buffer << "\033[0m" << '\n';
    }
    
    std::cout << "=====client end main=====" << '\n';
}

int main()
{
    test1();

    return 0;
}
