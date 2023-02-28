#include <cstdio>
#include <thread>
#include <windows.h>
#include <iostream>
#include <vector>

void action(int id) {
	printf("Uruchamiam watek %d\n", id);
	Sleep(5 * 1000); //5 sekund
	printf("Koncze watek %d\n", id);
}

int main() {


	int thread_count;
	std::cout << "Podaj ilosc ";
	std::cin >> thread_count;
	//alokacja tablicy, która będzie przechowywać wskaźniki na wątki
	//std::thread** threads = new std::thread*[thread_count];
	std::vector<std::thread*> threads;


	//otwieranie wątków
	for (int i = 0; i < thread_count; i++) {
		std::thread* thread = new std::thread(std::thread(action, i)); //wykorzystuje i jako id danego wątku
		threads.push_back(thread);
	}

	//watki pracują, ale trzeba je zsynchronizować
	for (auto t : threads) {
		t->join();
	}
	threads.clear();

	printf("Koniec programu \r\n");

	return 0;
}