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
	unsigned int max_iter = 255;
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
	ofstream first("1.ppm");
	ofstream sec("2.ppm");
	ofstream third("3.ppm");

	first << "P3\n" << width << " " << height << " 255\n";
	sec << "P3\n" << width << " " << height << " 255\n";
	third << "P3\n" << width << " " << height << " 255\n";
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++)
		{
			int val = value(j, i, width, height);
			*my_Img << val << ' ' << val << ' ' << val << "\n";
			if (i < height / 4) {
				first << val << ' ' << val << ' ' << val << "\n";
			}
			else
			{
				first.close();
			}
			if (i < height / 2) {
				sec << val << ' ' << val << ' ' << val << "\n";
			}
			else
			{
				sec.close();
			}
			if (i < height * 0.75) {
				third << val << ' ' << val << ' ' << val << "\n";
			}
			else
			{
				third.close();
			}
		}
	}
}

int main()
{
	float width = 600;
	float height = 600;
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
