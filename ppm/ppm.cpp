#include <iostream>
#include <fstream>
#include <string>
#include "ppm.h"
using namespace std;
namespace image {

	float* ReadPPM(const char* filename, int* w, int* h) {
		ifstream infile(filename, ios::binary);
		//infile.open

		if (infile.fail()) {
			cerr << "Error opening file" << endl;
			return nullptr;

		}//adinamia diavasmatos arxeiou

		string type;
		int size;

		infile >> type;//tipos ppm
		infile >> *w >> *h >> size;//diavasma diastasewn


		int width = *w;
		int height = *h;

		if (!(type == "P6")) {

			cout << "The type of image is not P6!";
			infile.close();

		}
		if (width < 0 || height < 0) {

			cout << "Not acceptable dimensions";
			infile.close();

		}
		if (size < 0 || size > 255) {
			cout << "Max value is less than 0 or grater than 255";
			infile.close();
		}

		int imageSize = 3 * width * height;
		char* buf = new char[imageSize + 1];//pinakas me ta alpharitmitika olou tou arxeiou
		infile.read(buf, imageSize);
		unsigned char* buffer = (unsigned char*)buf;//metatroph twn char se unsigned
		float* foo = new float[imageSize];//o pinakas me ta float/255

		for (int i = 0; i < imageSize; i++) {
			*(foo + i) = float(buffer[i + 1]) / 255; //i+1 logw tou space h tab pou akolouthei tis plirofories kefalidas
			//if (i < 50) cout << *(foo + i) << "\n";
		}

		delete[] buf;
		infile.close();
		return foo;

	}

	bool WritePPM(const float* data, int w, int h, const char* filename) {

		if (data == nullptr) {                   // Sfalma se periptwsi pou o pinakas einai adeios
			cerr << "Error the file is empty" << endl;
			return false;
		}
		ofstream ppmFile;
		ppmFile.open(filename, ios::binary);

		if (!ppmFile.is_open()) {                  //Sfalma sto anoigma tou arxeiou
			cerr << "Error writing the file!" << endl;
			return false;
		}

		ppmFile << "P6\n" << w << " " << h << "\n255\n";     //H kefalida tou arxeiou

		for (int i = 0; i < w * h * 3; i++) {                                                          // Metatrepoume tis float times se char kai
																								 //  epeita tis grafoume sto arxeio.
			ppmFile << unsigned char(data[i] * 255);

		}

		ppmFile.close();
		return true;
	}

}