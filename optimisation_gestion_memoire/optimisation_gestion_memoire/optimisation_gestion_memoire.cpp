#include <iostream>
#include <vector>
#include <windows.h>
#include <psapi.h>  // Pour GetProcessMemoryInfo

// Fonction pour obtenir la memoire utilisee (en Ko)
size_t getMemoryUsage() {
    PROCESS_MEMORY_COUNTERS memCounter;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &memCounter, sizeof(memCounter))) {
        return memCounter.WorkingSetSize / 1024;  // Convertir en Ko
    }
    return 0;
}

int main() {
    size_t memory_before, memory_after;

    // Allocation manuelle de memoire
    memory_before = getMemoryUsage();
    std::cout << "Allocation manuelle de memoire demarree" << std::endl;

    int* arr = new int[10000000];
    for (int i = 0; i < 10000000; i++) {
        arr[i] = i;
    }

    Sleep(1000);  // Pause pour stabiliser la mesure memoire
    memory_after = getMemoryUsage();
    std::cout << "Memoire utilisee avec allocation manuelle: "
        << (memory_after - memory_before) << " Ko" << std::endl;

    delete[] arr;  // Liberation de memoire

    // Allocation avec std::vector
    memory_before = getMemoryUsage();
    std::cout << "Allocation de memoire avec std::vector demarree" << std::endl;

    std::vector<int> vec(10000000);
    for (int i = 0; i < 10000000; i++) {
        vec[i] = i;
    }

    Sleep(1000);  // Pause pour stabiliser la mesure memoire
    memory_after = getMemoryUsage();
    std::cout << "Memoire utilisee avec std::vector: "
        << (memory_after - memory_before) << " Ko" << std::endl;

    return 0;
}
