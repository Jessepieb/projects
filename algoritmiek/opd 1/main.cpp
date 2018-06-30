#include <iostream>
#include <valarray>
#include <cmath>
#include <ctime>
#include <fstream>
#include <unistd.h>
using namespace std;

void swap(int *i, int *j){

    int temp = *i;
    *i = *j;
    *j = temp;
}

void bubblesort(int arr[], int length){
    bool swapped;
    for (int i = 0; i < length -1; i++){
        swapped = false;
        for (int j = 0; j < length - i -1; j++){
            if (arr[j] > arr[j+1]){
                swap(&arr[j],&arr[j+1]);
                swapped = true;
            }
        }
        if (swapped == false){
            break;}
    }

}

void printArray(int arr[], int size){
    for (int k = 0; k < size; k++){
        cout<<arr[k]<<" ";
    }
}

int* fillarray(int arr[], int size){
    for (int i = 0; i < size; i++){
        int ranNum = rand()%101;
        arr[i] = ranNum;
    }
        return arr;
}

void meassure(int cycles){
    ofstream testfile;
    testfile.open("test.dat", ofstream::trunc);
    //testfile<<"##  "<<"     "<<"size  "<< "time"<<endl;
    double starttime, endtime, duration;

    for (int i = 1; i < cycles + 1; i++){
        int arr[64*i];
        int size = sizeof(arr)/sizeof(arr[0]);
        fillarray(arr, size);
        starttime = clock();
        bubblesort(arr, size);
        endtime = clock();
        duration = ((endtime - starttime)/(CLOCKS_PER_SEC))*1000;
        cout<< "Loop" << i << endl;
        //printArray(arr, size);
        if (testfile.is_open()){
            testfile << " "<< size<< " " << duration << endl;
        }
    }
    testfile.close();
}
int main() {
    /*int arr[10] = {4,2,3,7,1,9,1,8,3,4};
    int n = sizeof(arr)/sizeof(arr[0]);
    bubblesort(arr, n);
    printArray(arr, n);*/
    meassure(100);
    return 0;
}