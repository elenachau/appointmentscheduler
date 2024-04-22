#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <iostream>
using namespace std;

class Appointment{
    int hours, minutes, day, month, year;
    bool isAM;

    public:
        Appointment();
        Appointment(int, int, int, int, int, bool);
        Appointment(const Appointment&);

        int getHours();
        int getMinutes();
        bool getIsAM();
        int getDay();
        int getMonth();
        int getYear();

        void setHours(int);
        void setMinutes(int);
        void setIsAM(bool);
        void setDay(int);
        void setMonth(int);
        void setYear(int);
        
        friend ostream& operator<<(ostream &out, const Appointment &a);
        bool operator==(const Appointment& a);
};

#endif