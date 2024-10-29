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
            std::cout << "Ошибка! Пользователь с таким логином уже существует. Попробуйте снова.\n";
            return false;
        }
        else {
            db << "INSERT INTO users (login, password) VALUES (?, ?);"
                << login
                << password;
            std::cout << "Пользователь успешно зарегистрирован!\n";
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
            std::cout << "Авторизация успешна! Добро пожаловать, " << login << "!\n";
            return true;
        }
        else {
            std::cout << "Ошибка! Неверный логин или пароль.\n";
            return false;
        }
    }

private:
    database db{ "database.db" };
};

class CLTMaseng {
public:
    static void run() {
        cout << "1 - регистрация \n" << "2 - авторизация \n" << "3 - выход из профиля\n" << "4 - выход\n";
        while (true) {
            int number;
            cin >> number;


            AccountManager a;
            string login;
            string password;
            
            switch (number) {
            case 1:
                cout << "Регистрация (login, password): ";
                cin >> login >> password;
                a.add(login, password);
                break;
            case 2:
                cout << "Авторизация (login, password): ";
                cin >> login >> password;
                a.login(login, password);
                break;
            case 3:
                cout << "выход из профиля: " << "\n";
                u.end();
                break;
            case 4:
                cout << "выход " << "\n";
                u.end();
                return;
            default:
                cout << "Неверный выбор, попробуйте снова.\n";
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
