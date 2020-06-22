#include <iostream>
#include <ctime>
#include <fstream>
#include "SortTimer/Sorter.cpp"

const int result = 100;
void meassure(size_t size){
   std::ofstream testfile;
    testfile.open("test.csv", std::ofstream::trunc);
    testfile << "iter,size,duration\n";
    double starttime, endtime, duration;
    int iter = 1;
    for (size_t i = (size/result); i <= size; i+=(size/result))
    {
        Sorter sorter = Sorter(i);
        sorter.Fillarray();
       // sorter.PrintArray();

        starttime = clock();
        sorter.BubbleSort();
        endtime = clock();
        duration = ((endtime - starttime) / (CLOCKS_PER_SEC));
        if (testfile.is_open()) {
            testfile<< iter<< "," << i << "," << duration << std::endl;
        }

        //sorter.PrintArray();
        std::cout << "size: " << i << " duration:" << duration << "\n";
        sorter.~Sorter();
        iter++;
    }
    testfile.close();
}
int main() {

    meassure(5000);
    return 0;
}