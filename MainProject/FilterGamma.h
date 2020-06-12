#pragma once
#include "image.h"
#include <math.h> 
#include "Filter.h"
#ifndef _FILTER_G
#define _FILTER_G

namespace image {

	class FilterGamma : public Filter
	{
	protected:
		float gamma;

	public:

		FilterGamma(float g) {
			gamma = g;
		}

		void setG(float g) {
			gamma = g;
		}

		float getG() {
			return gamma;
		}

		~FilterGamma() {}

		Image operator << (const Image& image) {
			
			Color value;
			image::Image newImage(image);

			for (int i = 0; i < image.getWidth(); i++) {

				for (int j = 0; j < image.getHeight(); j++) {

					Color value = image.getPixel(i, j);
					value.r = pow(value.r, gamma);
					value.g = pow(value.g, gamma);
					value.b = pow(value.b, gamma);
					newImage.setPixel(i, j, value);

				}
			}

			return newImage;

		}







	};


}
#endif
