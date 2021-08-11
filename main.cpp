#include <iostream>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
int mandelbrot(float Px, float Py) {
	float x0 = Px;
	float y0 = Py;
	float x = 0;
	float y = 0;
	int iteration = 0;
	int max_iterations = 256;
	while (x * x + y * y <= 2 * 2 & iteration < max_iterations) {
		float xtemp = x * x - y * y + x0;
		y = 2 * x * y + y0;
		x = xtemp;
		iteration++;
	}
	return iteration;
}

int main()
{
	//ppm
	const int dimx = 8000, dimy = 8000;
	int i,j;
	FILE *fp = fopen("first.ppm", "wb");
	(void) fprintf(fp, "P6\n%d %d\n255\n", dimx, dimy);
	for (j = 0; j < dimx; ++j){
		for (i = 0; i < dimy; ++i){
			static unsigned char color[3];
			/*color[0] = i % 256; //red
			color[1] = j % 256; //green
			color[2] = (i*j) % 256; //blue
			*/
			float Px = (float)j / (float)dimx;
			float Py = (float)i / (float)dimy;
			float xOffset = -.4;
			float yOffset = .6;
			float xScale = .6;
			float yScale = .6;
			Px = Px * xScale + xOffset;
			Py = Py * yScale + yOffset;
			int mandelbrot_steps = mandelbrot(Px, Py);
			color[0] = (unsigned char) mandelbrot_steps;
			color[1] = (unsigned char) mandelbrot_steps;
			color[2] = (unsigned char) mandelbrot_steps;
			(void) fwrite(color,1,3,fp);
			cout << (j*dimx+i) * 100 / (dimx * dimy) << "%" << "\r" << flush;
		}
	}
	(void) fclose(fp);
	return EXIT_SUCCESS;
}
