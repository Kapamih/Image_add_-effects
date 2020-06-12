/*
ERGASIA C++
Akadimaiko etos 2019-2020.

Meli omadas:

Mitrousi Ioanna (3140121)
Michalakakou Konstantina (3150111)

*/

#include <iostream>
#include <vector>
#include "FilterLinear.h"
#include "FilterGamma.h"
#include "FilterBlur.h"
#include "FilterLaplace.h"
#include "../ppm/ppm.h"

using namespace std;
typedef math::Vec3<float> Color;

void main(int argc, char* argv[]) {
	
	float g ;
	float a1;
	float a2;
	float a3;
	float c1;
	float c2;
	float c3;
	int jump;
	int N;

	string imName = argv[argc - 1]; //image name

	//No arguments!
	if (argc == 1) {
		cout << "\nNo arguments where inputed\n" << endl;
		return;
	}

	

	bool flag = false; 
	bool filt = false; 

	for (int ar = 0; ar < argc; ar++) {
		if (string(argv[ar]).find("-f") != std::string::npos) {
			filt = true; // found -f
			break;
		}
	}

	//No filter!!
	if (filt == false) return;

	for (int ar = 0; ar < argc; ar++) {
		if (string(argv[ar]).find("gamma") != std::string::npos) {
			flag = true; //found gamma
			break;
		}
		else if (string(argv[ar]).find("linear") != std::string::npos) {
			flag = true; //found linear 
			break;
		}
		else if (string(argv[ar]).find("blur") != std::string::npos) {
			flag = true;//found blur 
			break;

		}

	}

	//No filter name.
	if (flag == false) {
		cout << "\nNo filters found.\n";
			return;
	}

	//Not an image,or wrgong fomat type.
	if (imName.substr(imName.find(".") + 1, imName.size()) != "ppm") {
		cout << "\nError!No ppm image found.\n" << endl;
		return;
	}

	image::Image im;

	im.load(imName, "ppm");
	image::Image im2(im);

	for (int a = 2; a < argc; a = a + jump) {
		
		if (string(argv[a]) == "gamma") {

			g = stof(argv[a + 1]);
			image::FilterGamma filtG(g);
			im2 = filtG << im2;

			jump = 3;
		}
		
		else if (string(argv[a ]) == "linear") {

			a1 = stof(argv[a + 1]);
			a2 = stof(argv[a + 2]);
			a3 = stof(argv[a + 3]);
			c1 = stof(argv[a + 4]);
			c2 = stof(argv[a + 5]);
			c3 = stof(argv[a + 6]);

			Color aVec(a1,a2,a3);
			Color cVec(c1,c2,c3);

			image::FilterLinear filtL(aVec, cVec);
			im2=filtL << im2;
			jump = 8;

		}

		else if (string(argv[a]) == "blur") {

			N = atoi(argv[a + 1]);
			image::FilterBlur filtB(N);
			im2 = filtB << im2;
			jump = 3;

		}

		else if (string(argv[a]) == "laplace") {

			image::FilterLaplace filtL;
			im2 = filtL << im2;
			jump = 2;

		}
	}
	
	string newImName = imName.substr(0, imName.find(".")) + "f.ppm";
	
	im2.save(newImName, "ppm");

}
