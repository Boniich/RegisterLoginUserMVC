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

    class BaseModel
    {
    protected:
        static list<User*> _userData;
        ~BaseModel() {
            for (auto item : _userData) {
                delete item;
            }
        }
    };

    list<User*> BaseModel::_userData = { new User("Boniich", "123456") };


    class Register : public BaseModel
    {

    public:
        Register() : BaseModel() {};
        bool checkExistingUser(const string usarName) {
            for (auto element : _userData)
            {
                if (element->getUsername() == usarName) {
                    return true;
                }
            }
            return false;
        }
        bool addUser(string usarName, string password) {
            _userData.push_back(new User(usarName, password));
            if (usarName == _userData.back()->getUsername()) {
                if (password == _userData.back()->getPassword()) {
                    return true;
                }
            }

            return false;
        }

    };

    class Login : public BaseModel
    {
  

    public:
        Login() : BaseModel() {}

        bool checkUserData(string username, string password)
        {
            for (auto element : _userData) {
                if (element->getUsername() == username) {
                    if (element->getPassword() == password) {
                        return true;
                    }
                }
            }

            return false;
        }

    };

    class Admin : public BaseModel
    {
    public:
        Admin() : BaseModel() {};

        list<User*> getUserList() {
            return _userData;
        }
    };

}

namespace Controllers
{
    class AdminController {
        View::UI* _ui;
        Models::Admin* _admin;

    public:
        AdminController() {
            _ui = new View::UI;
            _admin = new Models::Admin;
        }
        ~AdminController() {
            delete _ui;
            delete _admin;
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
            _ui->printText("### Login ###");
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
                _ui->printEndl();
            }
            else {
                _ui->printText("Ups! Alguno de los datos es erroneo! Revisalos por favor!");
                _ui->printEndl();
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
            bool exit = false;
            string username = "";
            string password = "";

            _ui->printText("### Registro ###");
            _ui->printEndl();
            _ui->printText("Por favor ingresa un usuario y contraseña para registrarte en el sistema");
            _ui->printEndl();
            do
            {
                _ui->printText("Usuario: ");
                username = _ui->inputUsername();

                bool isUsernameAlreadyRegister = _register->checkExistingUser(username);

                if (isUsernameAlreadyRegister) {
                    _ui->printText("Este nombre de usuario ya esta registrado! Intenta con otro");
                }
                else {
                    exit = true;
                }

            } while (!exit);


            _ui->printText("Contraseña: ");
            _ui->printEndl();

            password = _ui->inputPassword();
            bool isUserRegisteredCorrectly = _register->addUser(username, password);
            if (isUserRegisteredCorrectly) {
                _ui->printText("Usted ha sido registrado correctamente");
                _ui->printEndl();
            }
            else {
                _ui->printText("No hemos podido registrarlo! Intentelo de nuevo");
            }
            
        }

    };


}


int main()
{
    int option = NULL;
    bool exit = false;

    Controllers::AdminController adminController;
    Controllers::LoginController loginController;
    Controllers::RegisterController registerController;


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
            system("cls");
            loginController.doLogin();
            break;
        case 2:
            cin.ignore();
            system("cls");
            registerController.doRegister();
            break;
        case 3:
            system("cls");
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

