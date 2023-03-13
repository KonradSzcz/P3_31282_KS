#include <chrono>
#include <cstdio>
#include <windows.h>
#include <fstream>

int main() {
	auto start = std::chrono::steady_clock::now();
	//długie operacje
	
	std::fstream fs;
	fs.open ("test.txt", std::fstream::in | std::fstream::out);
	fs.close();
	Sleep(2000);
	auto end = std::chrono::steady_clock::now();

	printf("Czas trwania: %llu\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

	return 0;
}