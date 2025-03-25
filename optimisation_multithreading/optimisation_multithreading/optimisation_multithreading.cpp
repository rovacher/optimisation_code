#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <algorithm>

int main() {
	// Creation du tableau avec des valeurs aleatoires
	std::vector<int> arr(1000000);
	for (int i = 0; i < arr.size(); i++) {
		arr[i] = rand() % 1000000;
	}

	// Tri sans multithreading
	std::cout << "Depart tri sans multithreading" << std::endl;
	auto start = std::chrono::high_resolution_clock::now();
	std::sort(arr.begin(), arr.end());
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Temps d'execution sans multithreading: " << duration.count() << " microsecondes" << std::endl;

	// Creation du tableau avec des valeurs aleatoires à nouveau pour le tri parallèle
	for (int i = 0; i < arr.size(); i++) {
		arr[i] = rand() % 1000000;
	}

	// Tri avec multithreading
	std::cout << "Depart tri avec multithreading" << std::endl;
	auto parallelSort = [](std::vector<int>& arr, int start, int end) {
		std::sort(arr.begin() + start, arr.begin() + end);
		};

	start = std::chrono::high_resolution_clock::now();
	std::thread t1(parallelSort, std::ref(arr), 0, arr.size() / 2);
	std::thread t2(parallelSort, std::ref(arr), arr.size() / 2, arr.size());
	t1.join();
	t2.join();

	// Fusionner les deux sous-listes triees
	std::inplace_merge(arr.begin(), arr.begin() + arr.size() / 2, arr.end());

	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Temps d'execution avec multithreading: " << duration.count() << " microsecondes" << std::endl;

	return 0;
}
