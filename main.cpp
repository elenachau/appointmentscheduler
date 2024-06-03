#include "helpers.h"

int main(){
    DynamicArray<Client> clients;
    DynamicArray<Stylist> stylists;

    readClientFile(clients);
    readStylistFile(stylists);

    Client c_loggedIn;
    Stylist s_loggedIn, clientPreferred;
    string userChoice, userChoiceOuter;
    bool exit = false;

    do{
        displayMainMenu();
        userChoiceOuter = promptWhatWouldYouLikeToDo(4);
        switch(stoi(userChoiceOuter)){
            case 1:
                addAccount(clients, stylists);
                break;
            case 2:
                exit = loggedInOperationsClient(clients, stylists, c_loggedIn);
                break;
            case 3:
                exit = loggedInOperationsStylist(stylists, clients, s_loggedIn);
                break;
            case 4:
                break;
        }
        writeToStylistFile(stylists);
        writeToClientFile(clients);
    }while(stoi(userChoiceOuter) != 4 && exit == false);

    return 0;
}