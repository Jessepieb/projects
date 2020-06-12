#include <iostream>
#include <valarray>
#include <cmath>
#include <ctime>
#include <fstream>
#include <vector>
#include "../../../../Users/Jesse/source/repos/SortTimer/Sorter.cpp"
using namespace std;


//void bubblesort(std::vector<int> arr, int length){
//    bool swapped;
//    for (int i = 0; i < length -1; i++){
//        swapped = false;
//        for (int j = 0; j < length - i -1; j++){
//            if (arr[j] > arr[j+1]){
//                swap(&arr[j],&arr[j+1]);
//                swapped = true;
//            }
//        }
//        if (swapped == false){
//            break;}
//    }
//
//}


void meassure(int size){
    ofstream testfile;
    testfile.open("test.txt", ofstream::trunc);
    double starttime, endtime, duration;
    Sorter sorter =  Sorter(size);
    sorter.Fillarray();
    sorter.PrintArray();

        starttime = clock();
        //sorter.BubbleSort();
        endtime = clock();
        duration = ((endtime - starttime)/(CLOCKS_PER_SEC));
        if (testfile.is_open()){
            testfile << " "<< size << " " << duration << endl;
        }
        sorter.~Sorter();
    testfile.close();
}
int main() {

    meassure(50);
    return 0;
}