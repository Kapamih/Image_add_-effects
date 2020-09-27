#ifndef _IMAGE
#define _IMAGE
#include "vec3.h"
#include  "imageio.h"
#include "array2d.h"
#include "../ppm/ppm.h"
#include <algorithm>



namespace image {


	typedef float fl;
	typedef math::Vec3<fl> Color;

	class Image :virtual public ImageIO, public math::Array2D<Color> {

	public:

		Image(unsigned int width = 0, unsigned int height = 0, const Color* data_ptr = 0)
			: math::Array2D<Color>(width, height, data_ptr) {}

		Image(const Image& src)
			: math::Array2D<Color>(src) {
		}

		~Image() {

		}

		Color getPixel(unsigned int x, unsigned int y) const {

			return const_cast<Image*> (this)->operator()(x, y);
		}

		void setPixel(unsigned int x, unsigned int y, Color& value) {

			(*this)(x, y) = value;

		}

		bool load(const std::string& filename, const std::string& format) {

			std::string p = "ppm";
			std::string s = format;
			transform(s.begin(), s.end(), s.begin(), ::tolower);
			int i = p.compare(format);

			if (i == 0) {
				fl red, green, blue;

				float* floatData;
				const char* ch = filename.c_str();
				int readWidth;
				int readHeight;

				floatData = ReadPPM(ch, &readWidth, &readHeight);

				width = readWidth;
				height = readHeight;

				unsigned int size = width * height * 3;
				Color* imageColors = new Color[size];

				for (int i = 0; i < size; i = i + 3) {

					red = floatData[i];
					green = floatData[i + 1];
					blue = floatData[i + 2];

					imageColors[i / 3] = Color(red, green, blue);

				}

				Image* img = new Image(this->getWidth(), this->getHeight(), imageColors);
				*this = *img;
				delete[] imageColors;

			}

			else {

				std::cout << "Wrong format type!!!" << std::endl;
				return false;
			}
			return true;
		}




		bool save(const std::string& filename, const std::string& format) {
			std::string p = "ppm";
			std::string s = format;
			transform(s.begin(), s.end(), s.begin(), ::tolower);
			int i = p.compare(format);
			int j;

			if (i == 0) {
				float* buf = new float[width * height * 3];
				for (int i = 0; i < width * height; i++) {
					j = (i + 1) * 3;
					buf[j - 3] = buffer[i].x;
					buf[j - 2] = buffer[i].y;
					buf[j - 1] = buffer[i].z;

				}

				const char* ch = filename.c_str();
				return WritePPM(buf, width, height, ch);
			}
			else {
				std::cout << "Wrong format type!!!" << std::endl;
				return false;
			}

		}

	};
}
#endif