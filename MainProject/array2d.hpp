#ifndef _ARRAY2D_HPP
#define _ARRAY2D_HPP

#include <iostream>
#include <vector>

#include "array2d.h"

namespace math
{

	template <typename T>
	const unsigned int Array2D<T>::getWidth() const {

		return width;

	}

	template <typename T>
	const unsigned int Array2D<T>::getHeight() const {

		return height;

	}

	template <typename T>
	T* Array2D<T>::getRawDataPtr() {

		return buffer.data();

	}

	template <typename T>
	void Array2D<T>::setData(const T* const& data_ptr) {

		if (width == 0 || height == 0)return;
		T t;
		buffer.clear();
		for (int i = 0; i < width * height; i++) buffer.push_back(t);
		std::memcpy(buffer.data(), data_ptr, sizeof(T) * width * height);

	}


	template <typename T>
	T& Array2D<T>:: operator()  (unsigned int x, unsigned int y) {

		if (x<0 || y<0 || x>width || y>height) {
			T value = T();
			return value;
		}

		return buffer[y * width + x];
	}

	template <typename T>
	Array2D<T>::Array2D(unsigned int width, unsigned int height, const T * data_ptr) {//???????????

		this->width = width;
		this->height = height;
		this->setData(data_ptr);
	}

	template <typename T>
	Array2D<T>::Array2D(const Array2D<T> & src) {
		width = src.width;
		height = src.height;
		this->setData(src.buffer.data());
	}

	template <typename T>
	Array2D<T>::~Array2D() {
		 buffer.erase(buffer.begin(), buffer.begin()+width*height);
	}


	template <typename T>
	Array2D<T>& Array2D<T>::operator = (const Array2D<T> & right) {

		width = right.width;
		height = right.height;
		this->setData(right.buffer.data());
		return *this;

	}


}

#endif