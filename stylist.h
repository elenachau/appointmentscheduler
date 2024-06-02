#ifndef STYLIST_H
#define STYLIST_H
#include "person.h"

class Stylist: public Person{
    DynamicArray<Appointment> availability;
    int employeeNumber;

    public:
        Stylist();
        Stylist(DynamicArray<Appointment>, int, string, string, string, string, DynamicArray<Appointment>);
        Stylist(const Stylist&);

        DynamicArray<Appointment> getAvailability();
        void addAvailability(Appointment);
        int getEmployeeNumber();
        void setEmployeeNumber(int);
        void removeAvailability(int);
};

#endif