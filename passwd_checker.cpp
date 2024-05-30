#include <iostream>
#include <string>
#include <cctype>
#include <exception>

using namespace std;

//Password strength colour codes
const std::string RESET     = "\033[0m";
const std::string GREEN     = "\033[32m"; //Strong Password
const std::string YELLOW    = "\033[33m"; //Moderate Password
const std::string ORANGE    = "\033[38;5;214m"; //Weak Password
const std::string RED       = "\033[31m"; //Very Weak Password

//Handle specific password-related exceptions
class PasswordException : public std::exception{
    private:
        string message;
    public:
        PasswordException(const string &msg) : message(msg) {}
        const char* what() const noexcept override{
            return message.c_str();
        }
};

bool hasMinimumLength(const string &password, int length){
    return password.length() >= length;
}

bool hasUppercaseLetter(const string &password){
    for(char ch : password){
        if(isupper(ch)){
            return true;
        }
    }
    return false;
}

bool hasLowercaseLetter(const string &password){
    for(char ch : password){
        if(isdigit(ch)){
            return true;
        }
    }
    return false;
}

bool hasDigit(const string &password){
    for(char ch : password){
        if (isdigit(ch)){
            return true;
        }
    }
    return false;
}

bool hasSpecialCharacter(const string &password){
    for(char ch : password){
        if(ispunct(ch)){
            return true;
        }
    }
    return false;
}

string evaluatePasswordStrength(const string &password){
    const int minLength = 8; //Minimum password length set to 8 characters

    //check if password empty
    if(password.empty()){
        throw PasswordException("Password cannot be empty.");
    }
    
    //Perform checks
    bool lengthCheck        = hasMinimumLength(password, minLength);
    bool uppercaseCheck     = hasUppercaseLetter(password);
    bool lowercaseCheck     = hasLowercaseLetter(password);
    bool digitCheck         = hasDigit(password);
    bool specialCharCheck   = hasSpecialCharacter(password);

    //Calculate password strength metric
    int strengthPoints = 0;
    if(lengthCheck)      strengthPoints++;
    if(uppercaseCheck)   strengthPoints++;
    if(lowercaseCheck)   strengthPoints++;
    if(digitCheck)       strengthPoints++;
    if(specialCharCheck) strengthPoints++;

    switch( strengthPoints){
        
        case 5:  return "Very Strong";
        case 4:  return "Strong";
        case 3:  return "Moderate";
        case 2:  return "Weak";
        default: return "Very Weak";
    }
}

int main(){
    string password;
    int option;
    
    cout << "--------------------------------" << endl;
    cout << "   Password Strenght Checker    " << endl;
    cout << "--------------------------------" << endl << endl;

    do {
        
        cout << "________________" << endl << endl;
        cout << "0. Exit" << endl;
        cout << "1. Input password to test strength" << endl << endl;

        cout << "Select an option: ";
        cin >> option;

        if(option==0){

            cout << "Program terminination in progress." << endl;
            cout << "Program shutdown complete." << endl;

        }else if(option==1){

            cout << "Enter your password to test its strengh: ";
            cin >> password;

            try{

                string strength = evaluatePasswordStrength(password);

                if (strength == "Very Strong" || strength == "Strong") {
                    cout << GREEN  << "Password strength: " << strength << RESET << endl;
                } else if (strength == "Moderate") {
                    cout << YELLOW << "Password strength: " << strength << RESET << endl;
                } else if (strength == "Weak") {
                    cout << ORANGE << "Password strength: " << strength << RESET << endl;
                } else if (strength == "Very Weak") {
                    cout << RED    << "Password strength: " << strength << " (Do not use password!)" << RESET << endl;
                }
            }
            catch (const PasswordException &ex){
                cerr << "Error: " << ex.what() << endl;
            }
            catch (const exception &ex){
                cerr << "An unexpected error occurred: " << ex.what() << endl;
            }

        }else{
            cout << endl << "No valid option selected.\nPlease try again" << endl;
        }
        
    } while(option != 0);

    return 0;
}
