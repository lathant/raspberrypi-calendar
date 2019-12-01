default: console.cpp control.cpp terminate.cpp
	g++ console.cpp -o console.o
	g++ -pthread event.cpp event_factory.cpp event_manager.cpp timetable.cpp timetable_factory.cpp timetable_manager.cpp authenticator.cpp user.cpp user_factory.cpp user_manager.cpp control.cpp -o control.o
	g++ terminate.cpp -o terminate.o

console: console.cpp
	g++ console.cpp -o console.o

control: control.cpp
	g++ -pthread event.cpp event_factory.cpp event_manager.cpp timetable.cpp timetable_factory.cpp timetable_manager.cpp authenticator.cpp user.cpp user_factory.cpp user_manager.cpp control.cpp -o control.o

terminate: terminate.cpp
	g++ terminate.cpp -o terminate.o

clean: *.o
	rm *.o
