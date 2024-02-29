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

    class LoginController
    {
        View::UI* _ui;
        Models::Login* _login;

    public:
        LoginController() {
            _ui = new View::UI;
            _login = new Models::Login();
        }
        ~LoginController() {
            delete _ui;
            delete _login;
        }
        void doLogin() {
            _ui->printText("### Bienvenido ###");
            _ui->printEndl();
            _ui->printText("Por favor, ingresa tu usuario y contraseña para ingresar al sistem: ");
            _ui->printEndl();
            _ui->printText("Ingresa tu usuario: ");
            string userName = _ui->inputUsername();

            cout << endl;

            _ui->printText("Ingresa tu contraseña: ");
            string password = _ui->inputPassword();

            cout << endl;

            bool isUserRegistred = _login->checkUserData(userName, password);

            if (isUserRegistred) {
                _ui->printText("Has ingresado correctamente");
            }
            else {
                _ui->printText("Ups! Alguno de los datos es erroneo! Revisalos por favor!");
            }
        }
    };

    class RegisterController
    {
        View::UI* _ui;
        Models::Register* _register;

     public:
        RegisterController() {
            _ui = new View::UI;
            _register = new Models::Register();
        }
        ~RegisterController() {
            delete _ui;
            delete _register;
        }

        void doRegister() {
            _ui->printText("### Registro ###");
            _ui->printEndl();
            _ui->printText("Por favor ingresa un usuario y contraseña para registrarte en el sistema");
            _ui->printEndl();
            _ui->printText("Usuario: ");
            string username = _ui->inputUsername();
            _ui->printText("Contraseña: ");
            _ui->printEndl();
            string password = _ui->inputPassword();
            _register->addUser(username, password);
            _ui->printText("Usuario registrado con exito!");
        }

    };


}


int main()
{
    View::UI ui;
    Models::Admin admin;
    int option = NULL;
    bool exit = false;

    Controllers::AdminController adminController (&ui, &admin);
    Controllers::LoginController loginController;
    Controllers::RegisterController registerController;


    //loginController.doLogin();

    do
    {
        cout << "### Bienvenido ###" << endl;
        cout << "#### Menu de opciones ####" << endl;
        cout << "1- Login" << endl;
        cout << "2- Register" << endl;
        cout << "3- Admin panel" << endl;
        cout << "0- Salir" << endl;

        cout << "Introduce una opcion: ";
        cin >> option;

        switch (option)
        {
        case 1:
            cin.ignore();
            loginController.doLogin();
            break;
        case 2:
            registerController.doRegister();
            break;
        case 3:
            adminController.showAllUsersData();
            break;
        case 0:
            exit = true;
            break;
        default:
            cout << "Opcion no valida";
            break;
        }

    } while (!exit);

    return 0;

}

