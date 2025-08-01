#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <thread>

#define SIZE 40

void add(int id, int* a, int* b, int* c) {
	c[id] = a[id] + b[id];

}

int main() {
	srand(time(NULL));
	int a[SIZE];
	int b[SIZE];
	int c[SIZE];

	for (int i = 0; i < SIZE; i++) {
		a[i] = rand() % 100 + 1; //1 do 100
		b[i] = rand() % 100 + 1;
	}

	//wypisanie na ekranie A
	for (int i = 0; i < SIZE; i++) {
		printf("%u ", a[i]);
	}
	printf("\n");

	//wypisanie na ekranie B
	for (int i = 0; i < SIZE; i++) {
		printf("%u ", b[i]);
	}
	printf("\n");

	std::thread** threads = new std::thread * [SIZE];
	auto start = std::chrono::steady_clock::now();
	for (int i = 0; i < SIZE; i++) {
		threads[i] = new std::thread(add, i, a, b, c); //wykorzystuje i jako id danego wątku
	}
	auto end = std::chrono::steady_clock::now();
	printf("Czas trwania: %llu\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

	for (int i = 0; i < SIZE; i++) {
		threads[i]->join();
	}

	for (int i = 0; i < SIZE; i++) {
		delete threads[i];
	}
	delete[] threads;

	//wypisanie na ekranie C
	for (int i = 0; i < SIZE; i++) {
		printf("%u ", c[i]);
	}

	return 0;
}