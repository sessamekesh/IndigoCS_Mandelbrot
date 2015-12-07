#include <fstream>
#include <iostream>>
using namespace std;

int findMandelbrot(double cr, double ci, int max_iterations)
{
	int i = 0;
	double zr = 0.0, zi = 0.0;
	while (i < max_iterations && zr * zr + zi * zi < 4.0)
	{
		double temp = zr * zr - zi * zi + cr;
		zi = 2.0 * zr * zi + ci;
		zr = temp;
		i++;
	}

	return i;
}

double mapToReal(int x, int imageWidth, double minR, double maxR)
{
	double range = maxR - minR;
	return x * (range / imageWidth) + minR;
}

double mapToImaginary(int y, int imageHeight, double minI, double maxI)
{
	double range = maxI - minI;
	return y * (range / imageHeight) + minI;
}

int main()
{
	// Get the required input values from file...
	ifstream fin("input.txt");
	int imageWidth, imageHeight, maxN;
	double minR, maxR, minI, maxI;

	if (!fin)
	{
		cout << "Could not open file!" << endl;
		return 1;
	}

	fin >> imageWidth >> imageHeight >> maxN;
	fin >> minR >> maxR >> minI >> maxI;
	fin.close(); // Not necessary, good practice :D

	// Open the output file, write the PPM header...
	ofstream fout("output_image.ppm");
	fout << "P3" << endl; // "Magic Number" - PPM file
	fout << imageWidth << " " << imageHeight << endl; // Dimensions
	fout << "255" << endl; // Maximum value of a pixel R,G,B value...

	// For every pixel...
	for (int y = 0; y < imageHeight; y++) // Rows...
	{
		for (int x = 0; x < imageWidth; x++) // Pixels in row (columns)...
		{
			// ... Find the real and imaginary values for c, corresponding to that
			//     x, y pixel in the image.
			double cr = mapToReal(x, imageWidth, minR, maxR);
			double ci = mapToImaginary(y, imageHeight, minI, maxI);

			// ... Find the number of iterations in the Mandelbrot formula
			//     using said c.
			int n = findMandelbrot(cr, ci, maxN);

			// ... Map the resulting number to an RGP value
			int r = (n % 256);
			int g = (n % 256);
			int b = (n % 256);

			// ... Output it to an image
			fout << r << " " << g << " " << b << " ";
		}
		fout << endl;
	}
	fout.close();

	cout << "Finished!" << endl;
	return 0;
}