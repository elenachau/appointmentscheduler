#include "appointment.h"

Appointment::Appointment(){
    day = month = year = hours = minutes = 0;
    isAM = true;
}

Appointment::Appointment(int d, int mon, int y, int h, int min, bool a){
    day = d;
    month = mon;
    year = y;
    hours = h;
    minutes = min;
    isAM = a;
}

Appointment::Appointment(const Appointment& rhs){
    day = rhs.day;
    month = rhs.month;
    year = rhs.year;
    hours = rhs.hours;
    minutes = rhs.minutes;
    isAM = rhs.isAM;
}


int Appointment::getHours(){
    return hours;
}

int Appointment::getMinutes(){
    return minutes;
}

bool Appointment::getIsAM(){
    return isAM;
}

int Appointment::getDay(){
    return day;
}

int Appointment::getMonth(){
    return month;
}

int Appointment::getYear(){
    return year;
}


void Appointment::setHours(int h){
    hours = h;
}

void Appointment::setMinutes(int m){
    minutes = m;
}

void Appointment::setIsAM(bool a){
    isAM = a;
}

void Appointment::setDay(int d){
    day = d;
}

void Appointment::setMonth(int m){
    month = m;
}

void Appointment::setYear(int y){
    year = y;
}

bool Appointment::operator==(const Appointment& rhs){ //equality operator overload
    if(day == rhs.day && month == rhs.month && year == rhs.year && hours == rhs.hours && minutes == rhs.minutes && isAM == rhs.isAM){
        return true;
    }
    return false;
}
