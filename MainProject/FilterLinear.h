#pragma once
#include "image.h"
#include <math.h>  
#include "Filter.h"
#ifndef _FILTER_L
#define _FILTER_L

namespace image {

	class FilterLinear :public Filter
	{
	protected:
		Color a, c;
	public:
		FilterLinear(Color aVec = 0, Color cVec = 0) {

			a = aVec;
			c = cVec;

		}

		void setAVec(Color aVec) { a = aVec; }

		void setCVec(Color cVec) { c = cVec; }

		Color getAVec() { return a; }

		Color getCVec() { return c; }

		~FilterLinear() {}

		image::Image operator<<  (const image::Image& image) {
			Color value;
			image::Image newImage(image);

			for (int i = 0; i < image.getWidth(); i++) {
				for (int j = 0; j < image.getHeight(); j++) {

					Color value = image.getPixel(i,j);
					value =image.getPixel(i,j) * a + c ;
					value = value.clampToUpperBound(1);
					value = value.clampToLowerBound(0);
					newImage.setPixel(i,j, value);

				}
			}

			return newImage;

		}

	};


}
#endif
