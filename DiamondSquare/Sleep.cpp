#include "stdafx.h"
#include <cassert>
#include "sleep.h"

#ifdef _WIN32
#include <Windows.h>
void sleep(double seconds) {
	assert(seconds >= 0.0);
	int milliseconds = (int)(seconds * 1000.0);
	if (milliseconds > 0) {
		Sleep(milliseconds);
	}
	else {
		Sleep(0);
	}
}
#else
	//linux/unix
#include <unistd.h>
void sleep(double seconds) {
	assert(seconds > 0.0);
	int microseconds = (int)(seconds*10000000.0);
	if (microseconds > 0) {
		Sleep(microseconds);
	}
	else{
		Sleep(0);
}
#endif