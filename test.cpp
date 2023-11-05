#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

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

void ParallelQuickSort(std::vector<int>& arr, int start, int end, int depth){
    
    if(start >= end){
        return;
    }

    int pivot = Partition (arr, start, end);

    if(depth-- > 0){
        // Создание новых потоков для сортировки двух половин массива
        std::thread t1(ParallelQuickSort, std::ref(arr), start, pivot - 1, depth);
        std::thread t2(ParallelQuickSort, std::ref(arr), pivot + 1, end, depth);

        // Ожидание завершения потоков
        t1.join();
        t2.join();
    } else {
        // Сортировка последовательно в глубину рекурсии
        ParallelQuickSort(arr, start, pivot - 1, depth);
        ParallelQuickSort(arr, pivot + 1, end, depth);
    }
}

int main(int argc, char **argv) {
        srand(1337);
        std::vector<int> arr (1000000);
        for(int i = 0; i < arr.size(); i++){
            arr[i] = rand() % 1000;
        }

        std::vector<int> arr2 (1000000);
        std::vector<int> arr4 (1000000);
        std::vector<int> arr6 (1000000);
        std::vector<int> arr8 (1000000);
        std::vector<int> arr10 (1000000);

        std::copy(arr.begin(), arr.end(), arr2.begin());
        std::copy(arr.begin(), arr.end(), arr4.begin());
        std::copy(arr.begin(), arr.end(), arr6.begin());
        std::copy(arr.begin(), arr.end(), arr8.begin());
        std::copy(arr.begin(), arr.end(), arr10.begin());
        int n = arr.size();
    
    int nth = 1;
    if(argc==2) nth=atoi(argv[1]);
        auto start = std::chrono::steady_clock::now();
    // Запуск параллельной быстрой сортировки
        ParallelQuickSort(arr, 0, n - 1, nth);
        auto end = std::chrono::steady_clock::now();

        std::chrono::duration<double> es = end - start;

        std::cout << nth << ':' << es.count() << std::endl;
    
    
    
    return 0;
}
