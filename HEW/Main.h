// main.h
#ifndef _MAIN_H_
#define _MAIN_H_
#ifdef _DEBUG
#pragma comment(lib, "hew_console_x64_md.lib")
#else
#pragma comment(lib, "hew_console_x64_mt.lib")
#endif
#include <iostream>
#include "hew_console.h"
#endif	// _MAIN_H_
