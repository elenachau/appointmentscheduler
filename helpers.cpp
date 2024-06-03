#include "helpers.h"

void readClientFile(DynamicArray<Client>& clients){
    ifstream fin("client.txt");
    //Elena, Chau, exc, 293023920320320392, {10;27;2023;3;15;0}{12;22;2023;10;00;1}
    
    while(!fin.eof()){
        string first, last, username, password, appointments, stylist;
        Appointment a;
        DynamicArray<Appointment> appts;
        getline(fin, first, ',');
        getline(fin, last, ',');
        getline(fin, username, ',');
        getline(fin, password, ',');

        getline(fin, stylist, ',');
        getline(fin, appointments);

        if(appointments[1] != '}'){
            parseAppointments(appointments, a, appts);
        }
        Client client(stoi(stylist), password, username, first, last, appts);
        clients.addElementToEndOfArr(client);
    }
}

void readStylistFile(DynamicArray<Stylist>& stylists){
    ifstream fin("stylist.txt");
    // 1 Some,Dude,sduder999,4022020802287451274,{10;27;2023;3;15;0}{12;22;2023;10;00;1},{10;27;2023;12;00;0}

    while(!fin.eof()){
        string first, last, username, password, appointments, stylist, employeeNumber;
        Appointment a;
        DynamicArray<Appointment> appts, availability;
        getline(fin, employeeNumber, ',');
        getline(fin, first, ',');
        getline(fin, last, ',');
        getline(fin, username, ',');
        getline(fin, password, ',');
        getline(fin, appointments, ',');

        if(appointments[1] != '}'){
            parseAppointments(appointments, a, appts);
        }
        getline(fin, appointments);

        if(appointments[1] != '}'){
            parseAppointments(appointments, a, availability);
        }
        Stylist s(availability, stoi(employeeNumber), password, username, first, last, appts);
        stylists.addElementToEndOfArr(s);
    }
}

void parseAppointments(string appointments, Appointment& a, DynamicArray<Appointment>& appts){
    int currentEntry = 0;
    string temp = "";
    for(int i = 1; i < appointments.length() / sizeof('c'); i++){
        if(appointments[i] != '}' && appointments[i] != ';' && appointments[i] != '{'){
            temp += appointments[i];
        }
        else if(appointments[i] == ';'){
            currentEntry++;
            switch(currentEntry){
                case 1:
                    a.setMonth(stoi(temp));
                    break;
                case 2:
                    a.setDay(stoi(temp));
                    break;
                case 3:
                    a.setYear(stoi(temp));
                    break;
                case 4:
                    a.setHours(stoi(temp));
                    break;
                case 5:
                    a.setMinutes(stoi(temp));
                    break;
                case 6:
                    a.setIsAM(stoi(temp));
                    currentEntry = 0;
                    break;
                }
                if(currentEntry == 0){
                    appts.addElementToEndOfArr(a);
                }
                temp = "";
        }
    }
}

void addAccount(DynamicArray<Client>& clients, DynamicArray<Stylist>& stylists){
    string temp;
    DynamicArray<Appointment> appts, avail;
    Person generic = constructPerson();

    do{
        cout << "Is this a client (c) or stylist (s) account (c or s)?";
        getline(cin, temp);
    } while(temp != "C" and temp != "c" and temp != "S" and temp != "s");

    if(temp == "C" || temp == "c"){
        Client newClient = constructClient(stylists, generic);
        clients.addElementToEndOfArr(newClient);
    }
    else{
        Stylist newStylist = constructStylist(stylists, generic);
        stylists.addElementToEndOfArr(constructStylist(stylists, newStylist));
    }
}

Client constructClient(DynamicArray<Stylist>& existingStylists, Person& generic){
    Client client;
    string temp;

    client.setFirst(generic.getFirst());
    client.setLast(generic.getLast());
    client.setPassword(generic.getPassword());
    client.setUsername(generic.getUsername());
    DynamicArray<Appointment> appts;

    do{
        cout << "Do you have a stylist preference (y/n)?";
        getline(cin, temp);
        std::cout << typeid(temp).name() << std::endl;
        cout << "please" << endl;
    }while(temp != "y" and temp != "Y" and temp != "n" and temp != "N");

    if(temp == "y" || temp == "Y"){
        for(int i = 0; i < existingStylists.getCurrentNumElementsStored(); i++){
            cout << i + 1 << ". " << existingStylists.getElementAtIndex(i).getFirst() << existingStylists.getElementAtIndex(i).getLast() << endl;
            cout << existingStylists.getCurrentNumElementsStored() + 1 << ". Actually, I don't have a preference." << endl;
        }

        int val;
        do{
            cout << "Select a stylist: ";
            getline(cin, temp);
            val = stoi(temp);
        }while(val < 1 || val > existingStylists.getCurrentNumElementsStored() + 1);
        if(val - 1 != existingStylists.getCurrentNumElementsStored()){
            client.setStylist(existingStylists.getElementAtIndex(val - 1).getEmployeeNumber());
        }
    }
    return client;
}

Stylist constructStylist(DynamicArray<Stylist>& existingStylists, Person& generic){
    DynamicArray<Appointment> appts;
    DynamicArray<Appointment> available;

    int max = existingStylists.getElementAtIndex(0).getEmployeeNumber();
    for(int i = 1; i < existingStylists.getCurrentNumElementsStored(); i++){
        if(existingStylists.getElementAtIndex(i).getEmployeeNumber() > max){
            max = existingStylists.getElementAtIndex(i).getEmployeeNumber();
        }
    }

    Stylist stylist(generic.getBookedAppointments(), max + 1, generic.getPassword(), generic.getUsername(), generic.getFirst(), generic.getLast(), available);

    return stylist;
}

Person constructPerson(){
    string firstAndLast, username, password;
    
    cout << "Let's Get Started!" << endl;
    cout << "First and Last Name: ";
    getline(cin, firstAndLast);
    DynamicArray<Appointment> appts;

    string first, last;
    string temp = "";
    bool spaceFound = false;
    for(int i = 0; i < firstAndLast.size(); i++){
        if((firstAndLast[i] != ' ' && firstAndLast[i] != '\0' && firstAndLast[i] != '\n') or (spaceFound)) {
            temp += firstAndLast[i];
        }
        if(firstAndLast[i] == ' ' && !spaceFound){
            first = temp;
            temp = "";
            spaceFound = true;
        }
        if(i == firstAndLast.size() - 1){
            last = temp;
        }
    }

    cout << "Username: ";
    getline(cin, username);
    bool noMatch = true;
    do{
        cout << "Password: ";
        getline(cin, password);
        string test;
        cout << "Re-enter Password: ";
        getline(cin, test);
        if(password == test){
            noMatch = false;
        }
        else{
            cout << "Passwords do not match; try again." << endl;
        }
    } while(noMatch);
    Person person(password, username, first, last, appts);
    return person;
}

void displayMainMenu(){
    cout << "Welcome to Harried, your hair appointment scheduler." << endl;
    cout << "1. Create an account" << endl;
    cout << "2. Log into client portal" << endl;
    cout << "3. Log into stylist portal" << endl;
    cout << "4. Exit" << endl;
    cout << "What would you like to do today?";
}

void displayLoginMenu(Person p){
    cout << "Welcome" << p.getFirst() << " " << p.getLast() << ". Let's get started." << endl;
    cout << "1. Add a client appointment" << endl;
    cout << "2. Cancel an appointment" << endl;
    cout << "3. View appointments" << endl;
}

bool validatedClientOperations(int userChoice, Client& person, Stylist& stylist){
    bool exit;
    switch(userChoice){
        case 1:
            if(stylist.getFirst() != "NONE"){
                exit = addAppointment(person, stylist);
            }
            else{
                cout << "Your preferred stylist is fully booked, please try again at a later date." << endl;
            }
            break;
        case 2:
            cancelAppointment(person, stylist);
            break;
        case 3:
            if(person.getBookedAppointments().getCurrentNumElementsStored() > 0){
                cout << person.getBookedAppointments();
            }
            else{
                cout << "No appointments currently booked." << endl;
            }
        }
        return exit;
}

bool addAppointment(Client& person, Stylist& preferred){
    string userChoice;
    cout << "Available appointments for this stylist: " << endl;
    cout << preferred.getAvailability();
    cout << preferred.getAvailability().getCurrentNumElementsStored() + 1 << ". Return to logged in user options" << endl;
    cout << preferred.getAvailability().getCurrentNumElementsStored() + 2 << ". Exit" << endl;
    DynamicArray<int> choices;
    
    do{
        cout << "Which appointment(s) would you like to book?";
        getline(cin, userChoice);
        if(stoi(userChoice) > 0 && stoi(userChoice) <= preferred.getAvailability().getCurrentNumElementsStored()){
            bool found = false;
            for(int i = 0; i < choices.getCurrentNumElementsStored(); i++){
                if(stoi(userChoice) == choices.getElementAtIndex(i)){
                    found = true;
                }
            }
            if(!found){
                choices.addElementToEndOfArr(stoi(userChoice) - 1);
            }
        }
    }while(stoi(userChoice) != preferred.getAvailability().getCurrentNumElementsStored()+1 && stoi(userChoice) != preferred.getAvailability().getCurrentNumElementsStored() + 2);
    if(stoi(userChoice) == preferred.getAvailability().getCurrentNumElementsStored()+2){
        return true;
    }
    for(int i = 0; i < choices.getCurrentNumElementsStored(); i++){
        person.addBooking(preferred.getAvailability().getElementAtIndex(choices.getElementAtIndex(i)));
        preferred.addBooking(preferred.getAvailability().getElementAtIndex(choices.getElementAtIndex(i)));
        preferred.removeAvailability(choices.getElementAtIndex(i));
    }

    return false;
}

void addAppointment(Stylist& stylist){
    string dateString, timeString, temp = "";
    int day, month, year, hour, minute, val = 0;
    bool am = false;
    cout << "Let's create an available appointment for your clients!" << endl;
    cout << "Please enter the date you're available in the format (MM/DD/YYYY): ";
    getline(cin, dateString, '/');
    month = stoi(dateString);
    getline(cin, dateString, '/');
    day = stoi(dateString);
    getline(cin, dateString);
    year = stoi(dateString);

    cout << "Please enter the time you're available in the format (HH:MM): ";
    getline(cin, timeString, ':');
    hour = stoi(timeString);
    getline(cin, timeString);
    minute = stoi(timeString);
    cout << "1. AM" << endl;
    cout << "2. PM" << endl;
    do{
        cout << "Is this an AM or PM appointment?";
        getline(cin, temp);
    }while(stoi(temp) != 1 && stoi(temp) != 2);

    if(stoi(temp) == 1){
        am = true;
    }
    Appointment a(day, month, year, hour, minute, am);
    stylist.addAvailability(a);
}

void addAppointment(Stylist& stylist, DynamicArray<Client>& customers, DynamicArray<Stylist>& stylists){
    string entry;
    Client client;
    if(stylist.getAvailability().getCurrentNumElementsStored() > 0){
        do{
            cout << "Is this a new client? (y/n)";
            getline(cin, entry);
        }while(entry != "y" && entry != "Y" && entry != "N" && entry != "n");

        if(entry == "y" || entry == "Y"){
            Person p = constructPerson();
            client = constructClient(stylists, p);
            customers.addElementToEndOfArr(client);
            entry = to_string(customers.getCurrentNumElementsStored());
        }
        else{
            for(int i = 0; i < customers.getCurrentNumElementsStored(); i++){
                cout << i + 1 << ". " << customers.getElementAtIndex(i).getFirst() << " " << customers.getElementAtIndex(i).getLast() << endl;
            }
            do{
                cout << "Which customer would you like to add an appointment to?";
                getline(cin, entry);
            } while(stoi(entry) < 1 && stoi(entry) > customers.getCurrentNumElementsStored());
            client = customers.getElementAtIndex(stoi(entry) - 1);
        }
        addAppointment(client, stylist);
        customers.replaceElementAtIndex(stoi(entry) - 1, client);
        for(int i = 0; i < stylists.getCurrentNumElementsStored(); i++){
            if(stylist.getEmployeeNumber() == stylists.getElementAtIndex(i).getEmployeeNumber()){
                stylists.replaceElementAtIndex(i, stylist);
            }
        }
    }
    else{
        cout << "No availability for stylist." << endl;
    }
}

bool validatedStylistOperations(int userChoice, Stylist& stylist, DynamicArray<Client>& clients, DynamicArray<Stylist>& stylists){
    string entry;
    bool exit;

    switch(userChoice){
        case 1:
            addAppointment(stylist, clients, stylists);
            break;
        case 2:
            cout << "1. Cancel booked appointment" << endl;
            cout << "2. Cancel available appointment" << endl;
            cout << "3. I've changed my mind" << endl;

            do{
                cout << "What would you like to cancel?";
                getline(cin, entry);
            }while(stoi(entry) < 1 || stoi(entry) > 3);

            if(stoi(entry) == 1){
                cancelAppointment(stylist, clients);
            }
            else if (stoi(entry) == 2){
                cancelAppointment(stylist);
            }
            else{
                return false;
            }
            break;
        case 3:
            if(stylist.getBookedAppointments().getCurrentNumElementsStored() > 0){
                cout << stylist.getBookedAppointments();
            }
            else{
                cout << "No appointments currently booked." << endl;
            }
            break;
        case 4:
            addAppointment(stylist);
            break;
        }

        for(int i = 0; i < stylists.getCurrentNumElementsStored(); i++){
            if(stylists.getElementAtIndex(i).getEmployeeNumber() == stylist.getEmployeeNumber()){
                stylists.replaceElementAtIndex(i, stylist);
            }
        }
        
        return exit;
}

void cancelAppointment(Client& c, Stylist& person){
    cout << c.getBookedAppointments();
    string userChoice;

    if(c.getBookedAppointments().getCurrentNumElementsStored() > 0){
        do{
            cout << "Select an appointment for removal: ";
            getline(cin, userChoice);
        }while(stoi(userChoice) < 1 && stoi(userChoice) > c.getBookedAppointments().getCurrentNumElementsStored());
        int indexOfCancellation = stoi(userChoice) - 1;
        Appointment selected = c.getBookedAppointments().getElementAtIndex(indexOfCancellation);
        for(int j = 0; j < person.getBookedAppointments().getCurrentNumElementsStored(); j++){
            if(person.getBookedAppointments().getElementAtIndex(j) == c.getBookedAppointments().getElementAtIndex(indexOfCancellation)){
                person.addAvailability(selected);
                person.removeBooking(j);
                c.removeBooking(indexOfCancellation);
            }
        }
    }
    else{
        cout << endl << "No appointments to cancel." << endl << endl;
    }
}

void cancelAppointment(Stylist& s, DynamicArray<Client>& people){
    cout << s.getBookedAppointments();
    string userChoice;
    do{
        cout << "Select an appointment for removal: ";
        getline(cin, userChoice);
    }while(stoi(userChoice) < 1 && stoi(userChoice) > s.getBookedAppointments().getCurrentNumElementsStored());
    int indexofCancellation = stoi(userChoice) - 1;
    Appointment selected = s.getBookedAppointments().getElementAtIndex(indexofCancellation);
    for(int i = 0; i < people.getCurrentNumElementsStored(); i++){
        Client c = people.getElementAtIndex(i);
        for(int j = 0; j < people.getElementAtIndex(i).getBookedAppointments().getCurrentNumElementsStored(); j++){
            if(people.getElementAtIndex(i).getBookedAppointments().getElementAtIndex(j) == selected){
                s.addAvailability(selected);
                people.getElementAtIndex(i).removeBooking(j);
                s.removeBooking(indexofCancellation);
            }
        }
    }
}

void cancelAppointment(Stylist& s){
    cout << s.getAvailability();
    string userChoice;
    do{
        cout << "Select an appointment for removal: ";
        getline(cin, userChoice);
    } while(stoi(userChoice) < 1 && stoi(userChoice) > s.getAvailability().getCurrentNumElementsStored());
    int indexOfCancellation = stoi(userChoice) - 1;
    s.removeAvailability(indexOfCancellation);
}

void writeToStylistFile(DynamicArray<Stylist>& stylists){
    // 1,Some,Dude,sduder999,HairBall42,{10;27;2023;3;15;0}{12;22;2023;10;00;1},{10;27;2023;12;00;0}
    ofstream fout("stylist.txt");
    for(int i = 0; i < stylists.getCurrentNumElementsStored(); i++){
        fout << stylists.getElementAtIndex(i).getEmployeeNumber() << ",";
        fout << stylists.getElementAtIndex(i).getFirst() << ",";
        fout << stylists.getElementAtIndex(i).getLast() << ",";
        fout << stylists.getElementAtIndex(i).getUsername() << ",";
        fout << stylists.getElementAtIndex(i).getPassword() << ",";

        if(stylists.getElementAtIndex(i).getBookedAppointments().getCurrentNumElementsStored() > 0){
            for(int j = 0; j < stylists.getElementAtIndex(i).getBookedAppointments().getCurrentNumElementsStored(); j++){
                fout << "{" << stylists.getElementAtIndex(i).getBookedAppointments().getElementAtIndex(j).getMonth() << ";";
                fout << stylists.getElementAtIndex(i).getBookedAppointments().getElementAtIndex(j).getDay() << ";";
                fout << stylists.getElementAtIndex(i).getBookedAppointments().getElementAtIndex(j).getYear() << ";";
                fout << stylists.getElementAtIndex(i).getBookedAppointments().getElementAtIndex(j).getHours() << ";";
                if(stylists.getElementAtIndex(i).getBookedAppointments().getElementAtIndex(j).getMinutes() != 0){
                    fout << stylists.getElementAtIndex(i).getBookedAppointments().getElementAtIndex(j).getMinutes() << ";";
                }
                else{
                    fout << "00;";
                }
                fout << stylists.getElementAtIndex(i).getBookedAppointments().getElementAtIndex(j).getIsAM() << ";}";
            }
        }
        else{
            fout << "{}";
        }
        fout << ",";
        if(stylists.getElementAtIndex(i).getAvailability().getCurrentNumElementsStored() > 0){
            for(int k = 0; k < stylists.getElementAtIndex(i).getAvailability().getCurrentNumElementsStored(); k++){
                fout << "{" << stylists.getElementAtIndex(i).getAvailability().getElementAtIndex(k).getMonth() << ";";
                fout << stylists.getElementAtIndex(i).getAvailability().getElementAtIndex(k).getDay() << ";";
                fout << stylists.getElementAtIndex(i).getAvailability().getElementAtIndex(k).getYear() << ";";
                fout << stylists.getElementAtIndex(i).getAvailability().getElementAtIndex(k).getHours() << ";";
                if(stylists.getElementAtIndex(i).getAvailability().getElementAtIndex(k).getMinutes() != 0){
                    fout << stylists.getElementAtIndex(i).getAvailability().getElementAtIndex(k).getMinutes() << ";";
                }
                else{
                    fout << "00;";
                }
                fout << stylists.getElementAtIndex(i).getAvailability().getElementAtIndex(k).getIsAM() << ";}";
            }
        }
        else{
            fout << "{}";
        }
        if(i != stylists.getCurrentNumElementsStored() - 1){
            fout << endl;
        }
    }
    fout.close();
}

void writeToClientFile(DynamicArray<Client>& clients){
    ofstream fout("client.txt");
    for(int i = 0; i < clients.getCurrentNumElementsStored(); i++){
        fout << clients.getElementAtIndex(i).getFirst() << ",";
        fout << clients.getElementAtIndex(i).getLast() << ",";
        fout << clients.getElementAtIndex(i).getUsername() << ",";
        fout << clients.getElementAtIndex(i).getPassword() << ",";
        fout << clients.getElementAtIndex(i).getStylist() << ",";
        if (clients.getElementAtIndex(i).getBookedAppointments().getCurrentNumElementsStored() > 0){
            for(int j = 0; j < clients.getElementAtIndex(i).getBookedAppointments().getCurrentNumElementsStored(); j++){
                fout << "{" << clients.getElementAtIndex(i).getBookedAppointments().getElementAtIndex(j).getMonth() << ";";
                fout << clients.getElementAtIndex(i).getBookedAppointments().getElementAtIndex(j).getDay() << ";";
                fout << clients.getElementAtIndex(i).getBookedAppointments().getElementAtIndex(j).getYear() << ";";
                fout << clients.getElementAtIndex(i).getBookedAppointments().getElementAtIndex(j).getHours() << ";";
                if(clients.getElementAtIndex(i).getBookedAppointments().getElementAtIndex(j).getMinutes() != 0){
                    fout << clients.getElementAtIndex(i).getBookedAppointments().getElementAtIndex(j).getMinutes() << ";";
                }
                else{
                    fout << "00";
                }
                fout << clients.getElementAtIndex(i).getBookedAppointments().getElementAtIndex(j).getIsAM() << ";}";
            }
        }
        else{
            fout << "{}";
        }
        if(i != clients.getCurrentNumElementsStored() - 1){
            fout << endl;
        }
    }
    fout.close();
}

void displayStylistLoginMenu(Person p){
    displayLoginMenu(p);
    cout << "4. Add available appointment" << endl;
    cout << "5. Exit" << endl;
}

void displayClientLoginMenu(Person p){
    displayLoginMenu(p);
    cout << "4. Exit" << endl;
}

string promptWhatWouldYouLikeToDo(int upper){
    string userChoice;
    do{
        cout << "What would you like to do?";
        getline(cin, userChoice);
    }while(stoi(userChoice) < 1 || stoi(userChoice) > upper);
    return userChoice;
}

bool loggedInOperationsClient(DynamicArray<Client>& clients, DynamicArray<Stylist>& stylists, Client& c_loggedIn){
    string userChoice;
    bool exit;
    Stylist clientPreferred;
    int loggedInIndex;
    loggedInIndex = logIn(clients);
    if(loggedInIndex == -10){
        exit = true;
        return exit;
    }
    do{
        c_loggedIn = clients.getElementAtIndex(loggedInIndex);
        displayClientLoginMenu(c_loggedIn);
        userChoice = promptWhatWouldYouLikeToDo(4);
        int stylistInd;
        if(stoi(userChoice) < 4){
            for(int i = 0; i < stylists.getCurrentNumElementsStored(); i++){
                if(stylists.getElementAtIndex(i).getEmployeeNumber() == c_loggedIn.getStylist()){
                    clientPreferred = stylists.getElementAtIndex(i);
                    stylistInd = i;
                }
            }
            exit = validatedClientOperations(stoi(userChoice), c_loggedIn, clientPreferred);
        }
        else{
            exit = true;
        }
        clients.replaceElementAtIndex(loggedInIndex, c_loggedIn);
        stylists.replaceElementAtIndex(stylistInd, clientPreferred);
    }while(stoi(userChoice) != 4);
    return exit;
}

bool loggedInOperationsStylist(DynamicArray<Stylist>& stylists, DynamicArray<Client>& clients, Stylist& s_loggedIn){
    int loggedInIndex;
    loggedInIndex = logIn(stylists);
    string userChoice;
    bool exit;
    if(loggedInIndex == -10){
        return 0;
    }
    do{
        s_loggedIn = stylists.getElementAtIndex(loggedInIndex);
        displayStylistLoginMenu(s_loggedIn);
        userChoice = promptWhatWouldYouLikeToDo(5);
        if(stoi(userChoice) < 5){
            exit = validatedStylistOperations(stoi(userChoice), s_loggedIn, clients, stylists);
        }
        else{
            exit = true;
        }
    } while(stoi(userChoice) != 5);
    return exit;
}

ostream& operator<<(ostream &out, const Appointment &a){
    out << a.month << "/" << a.day << "/" << a.year << " at " << a.hours << ":";
    if(a.minutes != 0){
        out << a.minutes << " ";
    }
    else{
        out << "00 ";
    }
    if(a.isAM){
        out << "AM";
    }
    else{
        out << "PM";
    }
    return out;
}

