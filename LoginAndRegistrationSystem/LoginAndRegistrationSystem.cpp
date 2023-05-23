#include <iostream>
#include <fstream>
#include <string>

class UserInfo {
public:
    std::string UserName, UserPassword, E_String;
    UserInfo();
    void encrpyt(std::string MainString);
};
void LoginScreen();
void RegisterScreen();

int main()
{
    char SelectedText;
    while (true)
    {
        std::cout << "\x1B[32m" << "For login press 1 \nFor register press 2\nFor quit press any other button " << "\033[0m";
        std::cin >> SelectedText;
        switch (SelectedText)
        {
        //LOGIN
        case '1':
            
            LoginScreen();
            break;
        //REGISTER
        case '2':
            RegisterScreen();
            break;
        //EXIT
        default:
            std::cout << "exiting from program";
            return 0;
        }
    }
}

void LoginScreen()
{
    UserInfo User;

    User.encrpyt(User.UserName);
    std::cout << "\nEncrypted string: " << User.E_String << std::endl;

    std::string FileString = User.E_String;
    FileString = "Users/" + FileString + ".txt";

    std::ifstream myfile;
    myfile.open(FileString);
    std::string TextLine;
    getline(myfile, TextLine);
    User.encrpyt(User.UserPassword);
    if (!myfile) {
        std::cout<<"This user not exist. Returning the Main Menu" << std::endl;
    }
    else
    {
        std::cout << (TextLine == User.E_String ? "\x1B[33mThis user exist\033[0m" : "\x1B[31mThe password is incorrect\033[0m.") << std::endl;
    }
    myfile.close();
}
void RegisterScreen()
{
    UserInfo User;
    User.encrpyt(User.UserName);

    std::cout << "\nEncrypted string: " << User.E_String << std::endl;

    std::string FileString = User.E_String;
    FileString = "Users/" + FileString + ".txt";

    std::ifstream myfile(FileString);
    if (!myfile) {
        myfile.close();
        std::ofstream WritedFile(FileString);
        User.encrpyt(User.UserPassword);
        WritedFile << User.E_String;
        WritedFile.close();
        std::cout << "CREATED" << std::endl;
    }
    else
    {
        myfile.close();
        std::cout << "\x1B[31mThis user exist\033[0m" << std::endl;
    }
}

UserInfo::UserInfo()
{
    system("CLS");
    std::cout << "Username :";
    std::cin >> UserName; 
    std::cout << "Password :";
    std::cin >> UserPassword;
}

void UserInfo::encrpyt(std::string MainString)
{
    E_String = MainString;
    for (int i = 0; (i < MainString.size() && MainString[i] != '\0'); i++) { E_String[i] = MainString[i] + 2; }
}

