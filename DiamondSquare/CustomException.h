#pragma once
#ifndef __CUSTOMEXCEPTION_H_
#define __CUSTOMEXCEPTION_H_

#include <iostream>
#include <exception>

struct DiamondSquareArraySizeException : public std::exception {
	const char * what() const throw() {
		return "Diamond Square Algorithm requires 2^n + 1 size";
	}
};

#endif // !__CUSTOMEXCEPTION_H_
