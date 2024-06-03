#ifndef CLIENT_H
#define CLIENT_H
#include "person.h"

class Client : public Person{
    int stylist;

    public:
        Client();
        Client(int, string, string, string, string, DynamicArray<Appointment>);
        Client(const Client&);

        int getStylist();
        void setStylist(int);
};

#endif