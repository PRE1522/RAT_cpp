#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <stdexcept>
#include <bits/stdc++.h>

#define maxc 5

using namespace std;

class Socket
{
        int sock;

public:
        Socket(int sd) : sock(sd)
        {
                if (sock < 0)
                        throw std::runtime_error("Socket creation error");
        }
        Socket() : Socket(socket(AF_INET, SOCK_STREAM, 0)) {}
        std::string re()
        {
                char buffer[1024] = {0};
                int n = read(sock, buffer, sizeof(buffer));
                return std::string(buffer, n);
        }
        void se(std::string s)
        {
                send(sock, s.c_str(), s.length(), 0);
        }
        int getSocket()
        {
                return sock;
        }
        //<=========================================================>
        int minx(int x, int y)
        {
                if (x < y)
                        return x;
                else
                        return y;
        }
        bool senddata(void *buf, int buflen)
        {
                unsigned char *pbuf = (unsigned char *)buf;
                while (buflen > 0)
                {
                        int num = send(sock, pbuf, buflen, 0);
                        if (num < 0)
                                return false;

                        pbuf += num;
                        buflen -= num;
                }

                return true;
        }

        bool sendlong(int value)
        {
                value = htonl(value);
                return senddata(&value, sizeof(value));
        }

        

        bool sendfile(FILE *f)
        {
                fseek(f, 0, SEEK_END);
                int filesize = ftell(f);

                rewind(f);
                if (filesize == EOF)
                        return false;
                if (!sendlong(filesize))
                        return false;
                if (filesize > 0)
                {
                        char buffer[1024] = {0};
                        do
                        {
                                size_t num = minx(filesize, sizeof(buffer));
                                num = fread(buffer, 1, num, f);
                                if (num < 1)
                                        return false;
                                if (!senddata(buffer, num))
                                        return false;
                                filesize -= num;
                        } while (filesize > 0);
                }
                return true;
        }
        //<==============================================>
        bool readdata(void *buf, int buflen)
        {
                unsigned char *pbuf = (unsigned char *)buf;
                while (buflen > 0)
                {
                        int num = recv(sock, pbuf, buflen, 0);
                        if (num < 1) return false;

                        pbuf += num;

                        buflen -= num;
                }

                return true;
        }

        bool readlong(int *value)
        {
                if (!readdata(value, sizeof(*value)))
                        return false;
                *value = ntohl(*value);
                return true;
        }

        bool readfile(FILE *f)
        {
                int filesize = 0;
                // cout << "size: " << sizeof(filesize) << std::endl;
                if (!readlong(&filesize))
                        return false;
                // std:: cout << "filesize: " << filesize << std::endl;
                if (filesize > 0)
                {
                        char buffer[1024] = {0};
                        do
                        {
                                int num = minx(filesize, sizeof(buffer));
                                // cout << "num: " << num << std::endl;
                                if (!readdata(buffer, num)) 
                                {
                                        cout << "read error: " << endl;
                                        return false;
                                }
                                int offset = 0;
                                do
                                {
                                        size_t written = fwrite(&buffer[offset], 1, num - offset, f);
                                        if (written < 1)
                                        {
                                                cout << "write error: " <<endl;
                                                return false;
                                        }
                                        offset += written;
                                } while (offset < num);
                                filesize -= num;
                                // cout << "filesize " << filesize << std::endl;
                        } while (filesize > 0);
                }
                return true;
        }
};

class Connection : public Socket
{
public:
        Connection(int socket) : Socket(socket) {}
        Connection(std::string address, unsigned short port) : Socket()
        {
                struct sockaddr_in serv_addr;
                serv_addr.sin_family = AF_INET;
                serv_addr.sin_port = htons(port);

                if (inet_pton(
                        AF_INET,
                        address.c_str(),
                        &serv_addr.sin_addr) <= 0)
                        throw std::runtime_error("Invalid address: Address not supported");

                if (connect(
                        getSocket(),
                        (struct sockaddr *)&serv_addr,
                        sizeof(serv_addr)) < 0)
                        throw std::runtime_error("\nConnection Failed \n");
        }
};

class PortListener
{
        Socket server;
        struct sockaddr_in address;
        int opt = 1;

public:
        PortListener(unsigned short port)
        {
                if (setsockopt(
                        server.getSocket(),
                        SOL_SOCKET,
                        SO_REUSEADDR | SO_REUSEPORT,
                        &opt,
                        sizeof(opt)))
                        throw std::runtime_error("setsockopt");

                address.sin_family = AF_INET;
                address.sin_addr.s_addr = INADDR_ANY;
                address.sin_port = htons(port);

                if (bind(
                        server.getSocket(),
                        (struct sockaddr *)&address,
                        sizeof(address)) < 0)
                        throw std::runtime_error("bind failed");

                if (listen(server.getSocket(), maxc) < 0)
                {
                        throw std::runtime_error("listen");
                }
        }
        Connection waitForConnection()
        {
                int new_socket;
                int addrlen = sizeof(struct sockaddr_in);
                new_socket = accept(
                    server.getSocket(),
                    (struct sockaddr *)&address,
                    (socklen_t *)&addrlen);
                if (new_socket < 0)
                        throw std::runtime_error("accept");
                return Connection(new_socket);
        }
};

class Handler
{

};

