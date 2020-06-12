#pragma once
#include "image.h"
#include <math.h>  
#ifndef _FILTER
#define _FILTER

namespace image {
	class Filter {

	public:

		Filter() {}

		virtual Image operator << (const Image& image) = 0;

		~Filter() {}


	};


}
#endif
