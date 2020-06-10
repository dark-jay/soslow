#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <memory>
#include <stdexcept>
#include <string>
#include <time.h>
#include <sstream>
#include <stdio.h>

//#include <thread>
//#include <chrono>
//#include <array>
//#include <cstdio>

#define ARRAYSIZE(a) \
  ((sizeof(a) / sizeof(*(a))) / \
  static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))
#define clrscr() \
  system("cls")
#define newline() cout << endl

using namespace std;
BOOL IsRunAsAdministrator();
void ElevateNow();

class Security_Check {
private:
    string pass;
    string mypass;
    bool authorize;
    bool security_pass;

    void decrypt(string message, int key){
        for (int i=0; i<message.size(); ++i) {
            message[i] = message[i] ^ key;
        }
        mypass = message;
    }

    // author of this funtion: http://www.cplusplus.com/user/SpaceWorm/
    static BOOL IsRunAsAdministrator()
    {
        BOOL fIsRunAsAdmin = FALSE;
        DWORD dwError = ERROR_SUCCESS;
        PSID pAdministratorsGroup = NULL;

        SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
        if (!AllocateAndInitializeSid(
            &NtAuthority,
            2,
            SECURITY_BUILTIN_DOMAIN_RID,
            DOMAIN_ALIAS_RID_ADMINS,
            0, 0, 0, 0, 0, 0,
            &pAdministratorsGroup))
        {
            dwError = GetLastError();
            goto Cleanup;
        }

        if (!CheckTokenMembership(NULL, pAdministratorsGroup, &fIsRunAsAdmin))
        {
            dwError = GetLastError();
            goto Cleanup;
        }

    Cleanup:

        if (pAdministratorsGroup)
        {
            FreeSid(pAdministratorsGroup);
            pAdministratorsGroup = NULL;
        }

        if (ERROR_SUCCESS != dwError)
        {
            throw dwError;
        }

        return fIsRunAsAdmin;
    }

    // author of this funtion: http://www.cplusplus.com/user/SpaceWorm/
    static void ElevateNow()
    {
        BOOL bAlreadyRunningAsAdministrator = FALSE;
        try
        {
            bAlreadyRunningAsAdministrator = IsRunAsAdministrator();
        }
        catch(...)
        {
        //_asm nop
        }
        if(!bAlreadyRunningAsAdministrator)
        {
            char szPath[MAX_PATH];
            if (GetModuleFileName(NULL, szPath, ARRAYSIZE(szPath)))
            {
                SHELLEXECUTEINFO sei = { sizeof(sei) };

                sei.lpVerb = "runas";
                sei.lpFile = szPath;
                sei.hwnd = NULL;
                sei.nShow = SW_NORMAL;

                if (!ShellExecuteEx(&sei))
                {
                    DWORD dwError = GetLastError();
                    if (dwError == ERROR_CANCELLED)
                    //Annoys you to Elevate it LOL
                    CreateThread(0,0,(LPTHREAD_START_ROUTINE)ElevateNow,0,0,0);
                }
            }

        }
        else {
            ///Code
        }
    }
public:
    string typed_password;
    int key;

    Security_Check() {
        pass = "dowg}maab";
        mypass = "";
        authorize = false;
        security_pass = false;
    }

    bool is_authenticated() {
        decrypt(typed_password, key);
        if (mypass == pass)
            return true;
        else
            return false;
    }

    void get_password() {
        cout << "Enter the password: ";
        int n=0;
        typed_password = "";
        string asteric = "";
        int it = 0; // it for asteric;
        while (n != 13) {
            n = getch();
            if (n != 13) { // enter
                if (n != 8) { // backspace
                    typed_password += char(n);
                    asteric.push_back('*');
                    cout << asteric.at(it);
                    it++;
                } else {
                    if (it > 0) {
                        asteric.erase(asteric.end() - 1);
                        typed_password.erase(typed_password.end() - 1);
                        cout << "\b" << " " << "\b";
                        it--;
                    }
                }
            }
        }
        cout << "\nEnter the key: ";
        cin >> key;
    }

    void authorization() {
        if (IsRunAsAdministrator()) {
            cout << "\n# Administrative access has been granted.\n" << endl;
            authorize = true;
        }
        else {
            cout << "\n# You need to grant Administrative previledges to function the program as expected." << endl;
            char cc;
            cout << "Do you want to give Administrative Right(y/n): ";
            cin >> cc;
            if (cc == 'y') {
                int flag = 0;
                try {
                    ElevateNow();
                    flag = 1;
                }
                catch(...) {}
                if (flag == 1)
                    exit(1);
            }
            else {
                cout << "Program terminating";
                exit(1);
            }
        }
    }

    bool is_authorized() {
        if (authorize)
            return true;
        else
            return false;
    }

    void set_security_pass(bool is_true) {
        security_pass = is_true;
    }

    bool get_security_pass() {
        return security_pass;
    }

};

std::string exec(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}

void welcome_msg() {
    cout << "      				     SOSLOW\n                                  \"\"\"\"\"\"\"\"\"\"\"\"\n                             By: jaynath1214@gmail.com\n\n";
    string o_cc782f5a5d36d844dc21215b04df6674="\x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20""-\171d\x64""y\055\x0A\x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x3A""m\155m\x6D""m\155:\x0A"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20""h\163s\x6D""m\163s\x68""\x0A\040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040`\x2D""/\157s\x73""s\072`\x20"" \144h\x6F"":\072o\x68""d\040 \x20"":\163s\x6F""o\057-\x60""\x0A\040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x60""/\171m\x6D""m\155m\x6D""m\155h\x2D"" \056/\x73""d\144s\x2F"".\040-\x68""m\155m\x6D""m\155m\x6D""y\057`\x0A"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \057d\x6D""m\155m\x6D""m\144s\x2F""-\072.\x2D""m\155m\x6D""m\155m\x6D""-\056:\x2D""/\163d\x6D""m\155m\x6D""m\144/\x0A"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20""o\155m\x6D""m\155m\x6D"":\056+\x79""m\155d\x3A""-\144m\x6D""m\155d\x2D"":\144m\x6D""y\053-\x3A""m\155m\x6D""m\155m\x6F""\x0A\040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \055-\x2D""-\055-\x2D""-\040o\x6D""m\155m\x6D""m\055.\x3A"":\072:\x2E""-\155m\x6D""m\155m\x6F"" \055-\x2D""-\055-\x2D""-\012 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x2F""m\155m\x6D""m\053`\x79""m\155m\x6D""y\140o\x6D""m\155m\x6D""/\012 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x60""o\157o\x6F""/\056h\x6D""m\155m\x6D""m\150.\x2F""o\157o\x6F""`\012 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"":\163s\x73""/\140h\x6D""m\155m\x6D""m\150`\x2B""s\163s\x3A""\x0A\040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x60""d\155m\x6D""s\140y\x64""d\144d\x73""`\157m\x6D""m\144`\x0A"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x2E""d\155m\x6D""-\056:\x3A"":\072.\x2D""m\155m\x64"".\012 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040.\x68""d\055:\x64""m\155m\x6D""d\072-\x64""h\056`\x0A"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040-\x64""o\140.\x2F""m\155m\x6D""m\155m\x6D""/\056`\x6F""d\055\x0A\x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20""`\144m\x6D""h\055:\x68""m\155m\x6D""m\155h\x3A""-\150m\x6D""d\140\x0A\x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20""+\155m\x6D""m\155s\x20"":\171m\x6D""y\072 \x73""m\155m\x6D""m\053\x0A\x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20""o\155m\x6D""m\150-\x20"" \040.\x2E"" \040 \x2E""h\155m\x6D""m\157\x0A\x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20""-\155m\x6D""o\140 \x20"" \040 \x20"" \040 \x20""`\157m\x6D""m\055\x0A\x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \040 \x20"" \053h\x3A"" \040 \x20"" \040 \x20"" \040 \x20"" \040:\x68""+\012";
    cout << o_cc782f5a5d36d844dc21215b04df6674;
}

void writeCharInSameCursor(int ch, int cursor_space) {
    while (cursor_space--)
        cout << "\b" << " " << "\b";
    cout << ch;
}

// parse seconds
// i/p foramt: Wed Jun 10 10:58:31 2020
int get_curr_sec() {
    time_t givemetime = time(NULL);
    string str = ctime(&givemetime);
    int first_digit = str[17] - '0';
    int second_digit = str[18] - '0';
    unsigned int curr_sec = first_digit*10 + second_digit;
    return curr_sec;
}

void delay_sec(int sec, bool display_sec) {
    int sec_temp = sec;
    unsigned int curr_sec = get_curr_sec();
    unsigned int prev_sec = 70;
    unsigned int sec_count = 0;

    if(display_sec)
        writeCharInSameCursor(0, 2);
    while (sec_temp != -1) {
        curr_sec = get_curr_sec();
        if (curr_sec != prev_sec) {
            sec_temp--;
            if(display_sec)
                writeCharInSameCursor(sec_count, 2);
            sec_count++;
            if (sec_temp == -1)
                sec_count--;
        }
        prev_sec = curr_sec;
    }
    if(display_sec)
        writeCharInSameCursor(sec_count, 2);
}

void showConsoleCursor(bool show_cursor) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    GetConsoleCursorInfo(consoleHandle, &info);
    info.bVisible = show_cursor;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void showLoadingDots(int times) {
    showConsoleCursor(false);
    while (times--) {
        cout << ".";
        delay_sec(1, false);
        cout << ".";
        delay_sec(1, false);
        cout << ".";
        delay_sec(1, false);
        cout << "\b" << " " << "\b";
        cout << "\b" << " " << "\b";
        cout << "\b" << " " << "\b";

        delay_sec(1, false);
    }
    showConsoleCursor(true);
}

int getRam(string sysinfo) {
    std::string result;

    std::istringstream iss(sysinfo);

    for (std::string line; std::getline(iss, line); )
    {
        result += line;
        size_t found = result.find("Total Physical Memory");
        if (found != string::npos) {
            //cout << result;
            break;
        }
        result = "";
    }
    newline();
    int ramInMb = 0;
    for (int i=0; i<result.size(); i++) {
        if (result.at(i) >= 48 && result.at(i) <= 57) {
            ramInMb = ramInMb*10 + (result.at(i) - 48);
        }
    }
    return ramInMb;
}

int main()
{
    welcome_msg();

    Security_Check s;
    s.get_password();
    if (s.is_authenticated()) {
        cout << "access granted";
        clrscr();
        s.authorization();
        s.set_security_pass(s.is_authorized());
    } else {
        cout << "permission denied";
    }

    if (s.get_security_pass()) {
        int ch;
        cout << "Press 1 to make changes in ram usage\n";
        cout << "Press 2 to make changes in cpu voltage\n";
        cout << "Press 3 to make changes in cpu core\n: ";
        cin >> ch;
        if (ch == 1) {
            clrscr();
            int ch2;
            cout << "Loading system info ...\n";
            string sysinfo;
            char c[20] = "systeminfo";
            sysinfo = exec(c);
            int totMem = getRam(sysinfo);
            cout << "Your current ram is: " << totMem << " MB" << endl;
            cout << "Press 1 to remove memory" << endl
                 << "Press 2 to reset memory" << endl << ": ";
            cin >> ch2;
            if (ch2 == 1) {
                int memToBeRemoved;
                cout << "Memory size to be removed must be multiple of 2." << endl
                     << "Enter the memory to be removed: ";
                cin >> memToBeRemoved;
                if (memToBeRemoved%2 == 0) {
                    if (memToBeRemoved < totMem) {
                        try {
                            char yn;
                            cout << "Are sure(y/n): ";
                            cin >> yn;
                            if (yn == 'y') {
                                string temp = "bcdedit /set {current} removememory " + memToBeRemoved;
                                char cmd[50];
                                for (int i=0; i<temp.size(); i++) {
                                    cmd[i] = temp[i];
                                }
                                system(cmd);
                                cout << "Successfully reduced the memory. Please restart the PC." << endl;
                            }
                            else {
                                cout << "Process aborted by the user." << endl;
                            }
                        } catch (...) {
                            cout << "Something went wrong!" << endl;
                        }
                    }
                    else {
                        cout << "Removed memory cannot be bigger that total memory!." << endl;
                    }
                }
                else {
                    cout << "Invalid input.";
                }
            }
            else if (ch2 == 1) {
                cout << "This will reset your memory to total memory." << endl;
                try {
                    char yn;
                    cout << "Are sure(y/n): ";
                    cin >> yn;
                    if (yn == 'y') {
                        char cmd[50] = "bcdedit /deletevalue removememory";
                        system(cmd);
                        cout << "The memory has reset. Please restart the PC." << endl;
                    }
                    else {
                        cout << "Process aborted by the user." << endl;
                    }
                } catch (...) {
                    cout << "Something went wrong!" << endl;
                }
            }
        }
        else if (ch == 2) {
            cout << endl << "Not yet implemented.";
        }
        else if (ch == 3) {
            cout << endl << "Not yet implemented.";
        }
    }

    getch();
    return 0;
}
