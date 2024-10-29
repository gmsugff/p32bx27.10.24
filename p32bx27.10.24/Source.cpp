#include <iostream> 
#include <string> 
#include <sqlite_modern_cpp.h> 
#include<vector> 
using namespace sqlite;
using namespace std;
class AccountManager {
public:
    AccountManager() {
        db << "CREATE TABLE IF NOT EXISTS users ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
            "login TEXT UNIQUE,"
            "password TEXT"
            ");";
    }

    bool access(const string& login, const string& password) {
        int count = 0;

        db << "SELECT COUNT(*) FROM users WHERE login = ?;"
            << login
            >> count;

        if (count > 0) {
            std::cout << "������! ������������ � ����� ������� ��� ����������. ���������� �����.\n";
            return false;
        }
        else {
            db << "INSERT INTO users (login, password) VALUES (?, ?);"
                << login
                << password;
            std::cout << "������������ ������� ���������������!\n";
            return true;
        }
    }

    bool add(const string& login, const string& password) {
        return access(login, password);
    }

    bool login(const string& login, const string& password) {
        int count = 0;

        db << "SELECT COUNT(*) FROM users WHERE login = ? AND password = ?;"
            << login
            << password
            >> count;

        if (count > 0) {
            std::cout << "����������� �������! ����� ����������, " << login << "!\n";
            return true;
        }
        else {
            std::cout << "������! �������� ����� ��� ������.\n";
            return false;
        }
    }

private:
    database db{ "database.db" };
};

class CLTMaseng {
public:
    static void run() {
        cout << "1 - ����������� \n" << "2 - ����������� \n" << "3 - ����� �� �������\n" << "4 - �����\n";
        while (true) {
            int number;
            cin >> number;


            AccountManager a;
            string login;
            string password;
            
            switch (number) {
            case 1:
                cout << "����������� (login, password): ";
                cin >> login >> password;
                a.add(login, password);
                break;
            case 2:
                cout << "����������� (login, password): ";
                cin >> login >> password;
                a.login(login, password);
                break;
            case 3:
                cout << "����� �� �������: " << "\n";
                u.end();
                break;
            case 4:
                cout << "����� " << "\n";
                u.end();
                return;
            default:
                cout << "�������� �����, ���������� �����.\n";
                break;
            }
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    CLTMaseng c;
    c.run();

}
