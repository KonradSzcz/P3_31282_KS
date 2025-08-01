#include <cstdio>
#include <thread>
#include <windows.h>

int action(int sleep_time) {
	std::thread::id this_id = std::this_thread::get_id();
	printf("Uruchamiam watek %d\n", this_id);
	Sleep(10 * sleep_time); //10 sekund
	printf("Koncze watek %d\n", this_id);
	return 0;
}

int main() {
	//tworzenie wątku
	std::thread t1(action,400); //konstruktor klasy t1 przyjmuje minimum wskaźnik na funckje do wykonania
	std::thread t2(action,1000); //funckja ta może coś zwracać, ale może zwaracać też void
	std::thread t3(action,600); //dalsze parametry zostaną przekazane do podanej funckji

	t1.join();  //synchronizacja
	t2.join();  //wątek główny ma tu poczekać na te 3 wątki
	t3.join();  //inaczej program by się zakończył wcześniej bo wątki trwają minimum 10 sekund

	printf("Koniec programu \r\n");

	return 0;
}