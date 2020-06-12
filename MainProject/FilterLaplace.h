#ifndef _FILTER_LAP
#define _FILTER_LAP
#include "FilterBlur.h"

namespace image {

	class FilterLaplace : public FilterBlur {

	public:
		FilterLaplace() {
			this->buffer.push_back(0);
			this->buffer.push_back(1);
			this->buffer.push_back(0);
			this->buffer.push_back(1);
			this->buffer.push_back(-4);
			this->buffer.push_back(1);
			this->buffer.push_back(0);
			this->buffer.push_back(1);
			this->buffer.push_back(0);
		}

		Image operator << (const Image & image) {

			Image newImage(image);
			int w = image.getWidth();
			int h = image.getHeight();
			int px;
			int py;
			for (int i = 0; i < w; i++) {
				for (int j = 0; j < h; j++) {
					Color laplace;
					for (int m = -1; m <= 1; m++) {
						for (int n = -1; n <= 1; n++) {
							px = i + m;
							if (px < 0) {
								px = 0;
							}
							else if (px > (w - 1)) {
								px = w - 1;
							}
							py = j + n;
							if (py < 0) {
								py = 0;
							}
							else if (py > (h - 1)) {
								py = h - 1;
							}
							Color temp;
							temp = image.getPixel(px, py);
							temp = temp * (this->buffer[(n + 1) * 3 + (m + 1)]);
							laplace = laplace + temp;

						}
					}
					laplace = laplace.clampToUpperBound(1);
					laplace = laplace.clampToLowerBound(0);
					newImage.setPixel(i, j, laplace);
				}
			}

			return newImage;
		}
	};

}
#endif
