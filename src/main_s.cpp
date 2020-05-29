#include <iostream>

#include "server.h"
#include "client.h"

void test1()
{
    std::cout << "=====server start main=====" << '\n';

    std::shared_ptr<server> s = std::make_shared<server>(server("127.0.0.1", 9999));
    s->initial();

    std::cout << "server accept begin!" << '\n';
    client_info cli;
    ssl_tls tls;
    tls.two_way_auth = true;
#if 0
    tls.ca_certf = std::string("../etc/centos7/ca.crt");
    tls.certf    = std::string("../etc/centos7/server.crt");
    tls.private_key  = std::string("../etc/centos7/server.key");
    tls.passwd  = std::string("uway123");
#else
    tls.ca_certf = std::string("../etc/ubuntu18/cacert.pem");
    tls.certf    = std::string("../etc/ubuntu18/server.crt");
    tls.private_key  = std::string("../etc/ubuntu18/server.key");
    tls.passwd  = std::string("yyp123");
#endif
    tls.meth = TLSv1_server_method();
    
    while (true)
    {
        cli = s->accept();
        const char * ip_addr = inet_ntoa(cli.addr.sin_addr);
        uint16_t port = ntohs(cli.addr.sin_port);
        std::cout << "client ip: " << ip_addr << ", port: " << port << ", fd: " << cli.fd << '\n';

        std::shared_ptr<client> c = std::make_shared<client>(ip_addr, port, cli.fd, tls);
        c->start();
    }
    
    s->destroy();

    std::cout << "=====server end main=====" << '\n';
}

int main()
{
    test1();

    return 0;
}
