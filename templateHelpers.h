#include "dynamicArray.h"

template<typename T>
int validateUser(string u, string p, DynamicArray<T> arr){
    for(int i = 0; i < arr.getCurrentNumElementsStored(); i++){
        if(arr.getElementAtIndex(i).getUsername() == u && arr.getElementAtIndex(i).getPassword() == p){
            return i;
        }
    }
    return -10;
}

template<typename T>
int logIn(DynamicArray<T>& arr){
    int userIndex;
    string continueLoggingIn;
    string username, password;

    do{
        cout << "Username: ";
        getline(cin, username);
        cout << "Password: ";
        getline(cin, password);
        userIndex = validateUser<T>(username, password, arr);
        if(userIndex == -10){
            do{
                cout << "Incorrect username or password. Try again? (y/n)";
                getline(cin, continueLoggingIn);
            }while(continueLoggingIn != "y" && continueLoggingIn != "Y" && continueLoggingIn != "N" && continueLoggingIn != "n");
        }
    }while(userIndex == -10 && (continueLoggingIn == "y" || continueLoggingIn == "Y"));

    return userIndex;
}

template<typename T>
ostream& operator<<(ostream& out, const DynamicArray<T>& arr){
    for(int i = 0; i < arr.getCurrentNumElementsStored(); i++){
        out << i+1 << ". " << arr.getElementAtIndex(i) << endl;
    }
    return out;
}