#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <chrono>
#include <assert.h>
#include <time.h>
#include <omp.h>

#define VECTOR_SIZE 10000

uint16_t* vector;

void createVector() {
    vector = new uint16_t[VECTOR_SIZE];

    for (uint32_t i = 0; i < VECTOR_SIZE; i++) {
        vector[i] = (uint16_t)(rand() % 11);
    }
}

uint32_t vectorLength() {
    uint32_t length = 0;

    for (uint32_t i = 0; i < VECTOR_SIZE; i++) {
        length += vector[i];
    }

    return length;
}

uint32_t vectorLengthParallel() {
    uint32_t length = 0;

#pragma omp parallel for shared(vector) reduction(+ : length)
    for (int32_t i = 0; i < VECTOR_SIZE; i++) {
        length += vector[i];
    }

    return length;
}

int main() {
    srand(time(NULL));

    createVector();

    auto start = std::chrono::high_resolution_clock::now();
    uint32_t length = vectorLength();
    auto end = std::chrono::high_resolution_clock::now();

    printf("Vector length calculated sequentially: %u in time: %llu microseconds\r\n", length,
        std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());

    start = std::chrono::high_resolution_clock::now();
    length = vectorLengthParallel();
    end = std::chrono::high_resolution_clock::now();

    printf("Vector length calculated in parallel: %u in time: %llu microseconds\r\n", length,
        std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());

    delete[] vector;

    return 0;
}
