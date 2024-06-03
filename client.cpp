#include "client.h"

Client::Client():Person(){
    stylist = 1;
}

Client::Client(int r, string p, string u, string f, string l, DynamicArray<Appointment> b): Person(p, u, f, l, b){
    stylist = r;
}

Client::Client(const Client& rhs): Person(rhs){
    stylist = rhs.stylist;
}

int Client::getStylist(){
    return stylist;
}

void Client::setStylist(int r){
    stylist = r;
}
