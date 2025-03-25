#include <iostream>
#include <vector>
#include <chrono> // Pour mesurer le temps d'execution

using namespace std;
using namespace std::chrono;

// Tri a bulle (inefficace)
void bubbleSort(vector<int>& arr) {
	int n = arr.size();
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}

// Partition pour le tri rapide
int partition(vector<int>& arr, int low, int high) {
	int pivot = arr[high];
	int i = low - 1;
	for (int j = low; j < high; j++) {
		if (arr[j] < pivot) {
			i++;
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i + 1], arr[high]);
	return i + 1;
}

// Tri rapide (optimise)
void quickSort(vector<int>& arr, int low, int high) {
	if (low < high) {
		int pi = partition(arr, low, high);
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

int main() {
	// Creation d'un grand tableau pour demontrer l'impact de l'optimisation
	vector<int> arr(10000);
	for (int i = 0; i < arr.size(); i++) {
		arr[i] = rand() % 10000; // Remplissage avec des nombres aleatoires
	}

	// Mesurer le temps d'execution du tri a bulle
	auto start = high_resolution_clock::now();
	vector<int> bubbleArr = arr; // Copie pour tri a bulle
	cout << "Lancement du tri a bulle" << endl ;
	bubbleSort(bubbleArr);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "Temps d'execution du Tri a Bulle: " << duration.count() << " microsecondes" << endl;

	// Mesurer le temps d'execution du tri rapide
	start = high_resolution_clock::now();
	vector<int> quickArr = arr; // Copie pour tri rapide
	cout << "Lancement du tri rapide" << endl;
	quickSort(quickArr, 0, quickArr.size() - 1);
	stop = high_resolution_clock::now();
	duration = duration_cast<microseconds>(stop - start);
	cout << "Temps d'execution du Tri Rapide: " << duration.count() << " microsecondes" << endl;

	return 0;
}
