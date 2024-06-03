#ifndef HELPERS_H
#define HELPERS_H
#include "stylist.h"
#include "client.h"
#include <unordered_map>
#include <fstream>
#include <sstream>
#include "templateHelpers.h"

void readClientFile(DynamicArray<Client>&);
void readStylistFile(DynamicArray<Stylist>&);
void parseAppointments(string, Appointment&, DynamicArray<Appointment>&);

Client constructClient(DynamicArray<Stylist>&, Person&);
Stylist constructStylist(DynamicArray<Stylist>&, Person&);
Person constructPerson();
void displayMainMenu();
void displayLoginMenu(Person);

void addAccount(DynamicArray<Client>&, DynamicArray<Stylist>&);
bool validatedClientOperations(int, Client&, Stylist&);
bool addAppointment(Client&, Stylist&);
void addAppointment(Stylist&);
void addAppointment(Stylist&, DynamicArray<Client>&, DynamicArray<Stylist>&);
bool validatedStylistOperations(int, Stylist&, DynamicArray<Client>&, DynamicArray<Stylist>&);
void cancelAppointment(Client&, Stylist&);
void cancelAppointment(Stylist&, DynamicArray<Client>&);
void cancelAppointment(Stylist&);
void writeToStylistFile(DynamicArray<Stylist>&);
void writeToClientFile(DynamicArray<Client>&);
void displayStylistLoginMenu(Person);
void displayClientLoginMenu(Person);
string promptWhatWouldYouLikeToDo(int);
bool loggedInOperationsClient(DynamicArray<Client>&, DynamicArray<Stylist>&, Client&);
bool loggedInOperationsStylist(DynamicArray<Stylist>&, DynamicArray<Client>&, Stylist&);

#endif