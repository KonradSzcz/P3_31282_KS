#include <iostream>
#include <thread>
#include <vector>
#include <numeric>
#include <random>

void sum(std::vector<int>::iterator begin, std::vector<int>::iterator end, int& result)
{
	result = std::accumulate(begin, end, 0);
}

int main()
{
	const int numElements = 100; 
	const int numThreads = 10; 
	const int chunkSize = numElements / numThreads; 
	std::vector<int> data(numElements);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 100);
	for (auto& elem : data)
	{
		elem = dis(gen);
	}

	std::vector<int> results(numThreads);
	std::vector<std::thread> threads;

	for (int i = 0; i < numThreads; ++i)
	{
		auto begin = data.begin() + i * chunkSize;
		auto end = (i == numThreads - 1) ? data.end() : begin + chunkSize;

		threads.push_back(std::thread(sum, begin, end, std::ref(results[i])));
	}

	for (int i = 0; i < numThreads; ++i)
	{
		threads[i].join();
		std::cout << "Sum of thread " << i << ": " << results[i] << std::endl;
	}

	int totalSum = std::accumulate(results.begin(), results.end(), 0);

	std::cout << "Total sum: " << totalSum << std::endl;

	return 0;
}