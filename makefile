style: main.o helpers.o client.o stylist.o person.o appointment.o
	g++ -o style main.o helpers.o client.o stylist.o person.o appointment.o -g

main.o: main.cpp helpers.h dynamicArray.h templateHelpers.h
	g++ -c main.cpp -g

helpers.o: helpers.h helpers.cpp dynamicArray.h appointment.h templateHelpers.h
	g++ -c helpers.cpp -g

client.o: client.h client.cpp person.h appointment.h
	g++ -c client.cpp -g

stylist.o: stylist.cpp stylist.h person.h appointment.h
	g++ -c stylist.cpp -g

person.o: person.h person.cpp appointment.h
	g++ -c person.cpp -g

appointment.o: appointment.h appointment.cpp
	g++ -c appointment.cpp -g

clean:
	rm *.o style