#include "pch.h"
#include <fstream> // file manipulation
#include <complex> // complex numbers
#include <iostream>
#include <thread>
#include <vector>
#include <string>

using namespace std;
int value(int x, int y, int width, int height) {
	complex<float> point((float)x / width - 1.5, (float)y / height - 0.5);
	// divide by the image dimensions to get value smaller than 1
	// then apply translation

	complex<float> z(0, 0);
	unsigned int nb_iter = 0;
	unsigned int max_iter = 96;
	while (abs(z) < 2 && nb_iter <= max_iter) {
		z = z * z + point;
		nb_iter++;
	}
	if (nb_iter < max_iter -1) {
		return (255*nb_iter)/max_iter -1;
	}
	else
	{
		return 255;
	}
}

void mandelbrot(ofstream *my_Img,int width, int height) {
	thread t1;
	thread t2;
	thread t3;
	thread t4;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++)
		{
			int val = value(j, i, width, height);
			*my_Img << val << ' ' << val << ' ' << val << "\n";
		}
	}
}

int main()
{
	float width = 1600;
	float height = 1600;
    cout << "Starting...";
	ofstream my_Img("mandelbrot.ppm");
	if (my_Img.is_open()) {
		my_Img << "P3\n" << width << " " << height << " 255\n";
		mandelbrot(&my_Img, width, height);
		
		my_Img.close();
	}
	else cout << "couldn't open the file";
	return 0;
}
