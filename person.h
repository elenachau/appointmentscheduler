#ifndef PERSON_H
#define PERSON_H

#include "appointment.h"
#include "dynamicArray.h"

class Person{
    protected: //attributes accessible within subclasses
        string first, last, username, password;
        DynamicArray<Appointment> bookedAppointments;

    public:
        Person();
        Person(string, string, string, string, DynamicArray<Appointment>);
        Person(const Person&);

        string getFirst();
        string getLast();
        string getUsername();
        string getPassword();
        DynamicArray<Appointment> getBookedAppointments();

        void setFirst(string);
        void setLast(string);
        void setUsername(string);
        void setPassword(string);
        void addBooking(Appointment);
        void removeBooking(int i);

        Person& operator=(const Person&);
};

#endif