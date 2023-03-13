#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <thread>

#define SIZE 40

void add(int id, int* a, int* b, int* c, int start, int end) {
    for (int i = start; i < end; i++) {
        c[i] = a[i] + b[i];
    }
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

    auto start = std::chrono::high_resolution_clock::now(); //rozpoczęcie pomiaru czasu

    const int THREAD_COUNT = SIZE / 10;
    std::thread** threads = new std::thread * [THREAD_COUNT];

    for (int i = 0; i < THREAD_COUNT; i++) {
        int start = i * 10;
        int end = start + 10;
        threads[i] = new std::thread(add, i, a, b, c, start, end);
    }

    for (int i = 0; i < THREAD_COUNT; i++) {
        threads[i]->join();
    }
    auto end = std::chrono::high_resolution_clock::now(); //zakończenie pomiaru czasu

    //wypisanie na ekranie C
    for (int i = 0; i < SIZE; i++) {
        printf("%u ", c[i]);
    }

    printf("\n");
    printf("Czas trwania: %llu\n", std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());

    for (int i = 0; i < THREAD_COUNT; i++) {
        delete threads[i];
    }
    delete[] threads;

    return 0;
}