#include "Filter.h"
#include "array2d.h"
#ifndef _FILTER_B
#define _FILTER_B
#include "image.h"
#include <math.h> 
#include "Vec3.h"



namespace image {

	class FilterBlur : public Filter, public math::Array2D<float> {

	protected:
		int N;

	public:
		FilterBlur() {
		}

		FilterBlur(int N) {
			this->N = N;
			int doubleN = N * N;
			float t = 1.0 / doubleN;

			for (int i = 0; i < doubleN; i++) {
				this->buffer.push_back(t);

			}

		}

		~FilterBlur() {}

		Image operator << (const Image& image) {

			Color value;
			Image newImage(image);
			int w = image.getWidth();
			int h = image.getHeight();
			int X;
			int Y;
			for (int i = 0; i < w; i++) {
				for (int j = 0; j < h; j++) {
					Color newPixel;

					for (int m = -N / 2; m <= N / 2; m++) {
						for (int n = -N / 2; n <= N / 2; n++) {

							X = i + m;
							if (0 > X) {
								X = 0;
							}
							else if (X > (w - 1)) {
								X = w - 1;
							}
							Y = j + n;
							if (0 > Y) {
								Y = 0;
							}
							else if (Y > (h - 1)) {
								Y = h - 1;
							}
							Color value;


							value = image.getPixel(X, Y);
							value = value * (this->buffer[n + (N / 2) * N + m + N / 2]);
							newPixel = newPixel + value;
						}
					}
					Color blur = newPixel;
					newImage.setPixel(i, j, blur);
				}
			}
			return newImage;
		}




	};
}
#endif 