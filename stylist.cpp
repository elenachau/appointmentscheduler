#include "stylist.h"

Stylist::Stylist(){
    employeeNumber = -5;
}

Stylist::Stylist(DynamicArray<Appointment> available, int n, string p, string u, string f, string l, DynamicArray<Appointment> b):Person(p, u, f, l, b){
    availability = available;
    employeeNumber = n;
}

Stylist::Stylist(const Stylist& rhs) : Person(rhs){
    availability = rhs.availability;
    employeeNumber = rhs.employeeNumber;
}

DynamicArray<Appointment> Stylist::getAvailability(){
    return availability;
}

void Stylist::addAvailability(Appointment a){
    availability.addElementToEndOfArr(a);
}

int Stylist::getEmployeeNumber(){
    return employeeNumber;
}

void Stylist::setEmployeeNumber(int e){
    employeeNumber = e;
}

void Stylist::removeAvailability(int i){
    availability.removeElementAtIndex(i);
}
