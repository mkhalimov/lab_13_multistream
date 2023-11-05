#include <iostream>
#include <vector>
#include <chrono>


// Функция разделения массива на подмассивы
int Partition(std::vector<int>& arr, int start, int end)
{
    int pivot = arr[end];

    int pIndex = start;

    for (int i = start; i < end; i++)
    {
        if (arr[i] <= pivot)
        {
            std::swap(arr[i], arr[pIndex]);
            pIndex++;
        }
    }

    std::swap(arr[pIndex], arr[end]);
    return pIndex;
}

void QuickSort(std::vector<int>& arr, int start, int end){
    
    if(start >= end){
        return;
    }

    int pivot = Partition (arr, start, end);

    QuickSort(arr, start, pivot - 1);
    QuickSort(arr, pivot + 1, end);
}

int main() {
    for(int k = 10; k <= 1000000; k += 10000)
    {
        std::vector<int> arr (k);
        for(int i = 0; i < arr.size(); i++){
            arr[i] = rand() % 1000;
        }
        int n = arr.size();
        
    /* std::cout << "Исходный массив: ";
        for (int num : arr) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
        */
        
        auto start = std::chrono::steady_clock::now();
        // Запуск быстрой сортировки
        QuickSort(arr, 0, n - 1);
        auto end = std::chrono::steady_clock::now();

        /*std::cout << "Отсортированный массив: ";
        for (int num : arr) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
        */

        std::chrono::duration<double> es = end - start;

        std::cout << es.count() << std::endl;
    }
    return 0;
}