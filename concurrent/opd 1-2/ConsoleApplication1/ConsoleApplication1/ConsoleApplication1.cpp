// mandelbrot.cpp
// compile with: g++ -std=c++11 mandelbrot.cpp -o mandelbrot
// view output with: eog mandelbrot.ppm
#include "pch.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <complex> // if you make use of complex number facilities in C++
#include<chrono>
#include <vector>
using namespace std;
template <class T> struct RGB { T r, g, b; };

template <class T>
class Matrix {
public:
    Matrix(const size_t rows, const size_t cols) : _rows(rows), _cols(cols) {
        _matrix = new T * [rows];
        for (size_t i = 0; i < rows; ++i) {
            _matrix[i] = new T[cols];
        }
    }
    Matrix(const Matrix& m) : _rows(m._rows), _cols(m._cols) {
        _matrix = new T * [m._rows];
        for (size_t i = 0; i < m._rows; ++i) {
            _matrix[i] = new T[m._cols];
            for (size_t j = 0; j < m._cols; ++j) {
                _matrix[i][j] = m._matrix[i][j];
            }
        }
    }
    ~Matrix() {
        for (size_t i = 0; i < _rows; ++i) {
            delete[] _matrix[i];
        }
        delete[] _matrix;
    }
    T* operator[] (const size_t nIndex)
    {
        return _matrix[nIndex];
    }
    size_t width() const { return _cols; }
    size_t height() const { return _rows; }
protected:
    size_t _rows, _cols;
    T** _matrix;
};

// Portable PixMap image
class PPMImage : public Matrix<RGB<unsigned char> >
{
public:
    PPMImage(const size_t height, const size_t width) : Matrix(height, width) { }

    int value(int x, int y, int width, int height) {
        complex<float> point((float)x / width - 1.5, (float)y / height - 0.5);
        complex<float> z(0, 0);
        unsigned int nb_iter = 0;
        unsigned int max_iter = 96;
        while (abs(z) < 2 && nb_iter <= max_iter) {
            z = z * z + point;
            nb_iter++;
        }
        if (nb_iter < max_iter - 1) {
            return (255 * nb_iter) / max_iter - 1;
        }
        else
        {
            return 255;
        }
    }

    void save(const std::string& filename)
    {
        std::ofstream out(filename, std::ios_base::binary);
        out << "P6" << std::endl << _cols << " " << _rows << std::endl << 255 << std::endl;
        for (size_t y = 0; y < _rows; y++)
            for (size_t x = 0; x < _cols; x++)
                out << _matrix[y][x].r << _matrix[y][x].g << _matrix[y][x].b;
    }
};

//void thread_task(PPMImage *img, int start, int size, int width, int height) {
//    for (int y = start; y < (start+size); y++) {
//        for (int x = 0; x < width; x++) {
//            *img[y][x].r = *img[y][x].g = img[y][x].b = img.value(x, y, width, height);
//        }
//    }
//}

void thread_task(PPMImage* img, int start, int size, int width, int height) {
    for (int y = start; y < (start + size); y++) {
        for (int x = 0; x < width; x++) {
            img[y][x].r = img[y][x].g = img[y][x].b = img.value(x, y, width, height);
        }
    }
}

int main()
{
    const unsigned width = 1600;
    const unsigned height = 1600;

    PPMImage image(height, width);
    vector<thread> workers;
    auto start = chrono::steady_clock::now();

    //image.thread_task(0, 1600, 1600, 1600);
    auto t1 = thread(thread_task,&image,0, 1600, 1600, 1600);
    t1.join();
    //for (int y = 0; y < height; y++) {
    //    for (int x = 0; x < width; x++) {
    //        image[y][x].r = image[y][x].g = image[y][x].b = image.value(x,y,width,height);
    //    }
    //}

    //for (int y = 0; y < height; y++) {
    //    for (int x = 0; x < width; x++) {
    //        image[y][x].r = image[y][x].g = image[y][x].b = image.value(x,y,width,height);
    //    }
    //}

    image.save("mandelbrot.ppm");
    auto end = chrono::steady_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << "elapsed time: " << elapsed.count() << "s\n";
    return 0;
}