#include <iostream>
#include <string>
#include <list>

using namespace std;

namespace View
{
    class UI
    {
    public:
        void printText(const string text) {
            cout << text;
        }
        void printEndl(string end = "") { cout << end << endl; }

        string inputUsername() {
            string userName;
            getline(cin, userName);
            return userName;
        }

        string inputPassword() {
            string password;
            getline(cin, password);
            return password;
        }
    };

}

namespace Models
{
    class User 
    {
        string _username;
        string _password;
    public: 
        User(string username, string password) : _username(username), _password(password) {};
        string getUsername() {
            return _username;
        }
        string getPassword() {
            return _password;
        }
    };

    class UserFactory
    {
        static list<User*> _userData;
    public:
        list<User*> getUserList() { return _userData; };
    };

    list<User*> UserFactory::_userData = { new User("Boniich", "123456") };


    class Register
    {
        UserFactory* _userFactory = nullptr;
    public:
        Register() {
            _userFactory = new UserFactory();
        }
        void addUser(string usarName, string password) {
            _userFactory->getUserList().push_back(new User(usarName, password));
        }

    };

    class Login
    {
        UserFactory* _userFactory = nullptr;

    public:
        Login() {
            _userFactory = new UserFactory();
        }

        bool checkUserData(string username, string password)
        {
            for (auto element : _userFactory->getUserList()) {
                if (element->getUsername() == username) {
                    if (element->getPassword() == password) {
                        return true;
                    }
                }
            }

            return false;
        }

    };

    class Admin
    {
        UserFactory* _userFactory = nullptr;
    public:
        Admin() {
            _userFactory = new UserFactory();
        }

        list<User*> getUserList() {
            return _userFactory->getUserList();
        }
    };

}

namespace Controllers
{
    class AdminController {
        View::UI* _ui;
        Models::Admin* _admin;

    public:
        AdminController(View::UI* view, Models::Admin* admin) {
            _ui = view;
            _admin = admin;
        }
        void showAllUsersData() {
            _ui->printText("Bienvenido Administrador, los usuarios registrados son: ");
            _ui->printEndl();
            for (auto element : _admin->getUserList())
            {
                _ui->printText("Usuario: ");
                _ui->printText(element->getUsername());
                _ui->printEndl();
                _ui->printText("Password: ");
                _ui->printText(element->getPassword());
            }
        }
    };
}


int main()
{
    View::UI ui;
    Models::Admin admin;

    Controllers::AdminController adminController (&ui, &admin);

    adminController.showAllUsersData();


    return 0;

}

