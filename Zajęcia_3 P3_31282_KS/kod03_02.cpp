#include <chrono>
#include <cstdio>
#include <windows.h>
#include <fstream>
using namespace std;

void fibonacci(int n)
{
	long long a = 0, b = 1;

	for (int i = 0; i < n; i++)
	{
		b += a; //pod zmienną b przypisujemy wyraz następny czyli a+b
		a = b - a; //pod zmienną a przypisujemy wartość zmiennej b
	}
}
int main() {
	auto start = std::chrono::steady_clock::now();
	//długie operacje
	
	int n = 40;
	fibonacci(n);
	auto end = std::chrono::steady_clock::now();

	printf("Czas trwania: %llu\n", std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());

	return 0;
}