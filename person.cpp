#include "person.h"

Person::Person(){
    password = last = username = first = "NONE";
}

Person::Person(string p, string u, string f, string l, DynamicArray<Appointment> b){
    password = p;
    username = u;
    first = f;
    last = l;
    bookedAppointments = b;
}

Person::Person(const Person& rhs){
    password = rhs.password;
    username = rhs.username;
    first = rhs.first;
    last = rhs.last;
    bookedAppointments = rhs.bookedAppointments;
}

string Person::getFirst(){
    return first;
}

string Person::getLast(){
    return last;
}

string Person::getUsername(){
    return username;
}

string Person::getPassword(){
    return password;
}

DynamicArray<Appointment> Person::getBookedAppointments(){
    return bookedAppointments;
}

void Person::setFirst(string f){
    first = f;
}

void Person::setLast(string l){
    last = l;
}

void Person::setUsername(string u){
    username = u;
}

void Person::setPassword(string p){
    password = p;
}

void Person::addBooking(Appointment a){
    bookedAppointments.addElementToEndOfArr(a);
}

void Person::removeBooking(int i){
    bookedAppointments.removeElementAtIndex(i);
}

Person& Person::operator=(const Person& rhs){
    password = rhs.password;
    username = rhs.username;
    first = rhs.first;
    last = rhs.last;
    bookedAppointments = rhs.bookedAppointments;
    return *this;
}
