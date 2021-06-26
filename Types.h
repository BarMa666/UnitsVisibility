#pragma once

#include <utility>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <tchar.h>
#include <list>
#include <map>

#include "Vector2.h"

#ifndef OUT
#define OUT
#endif

#if defined(_UNICODE) || defined(UNICODE)
#define tcout std::wcout
#define tstring std::wstring
#define tifstream std::wifstream
#define tofstream std::wofstream
#define tstringstream std::wstringstream
#define tostring std::to_wstring
#else
#define tcout std::cout
#define tstring std::string
#define tifstream std::ifstream
#define tofstream std::ofstream
#define tstringstream std::stringstream
#define tostring std::to_string
#endif


using PositionT = Vector2;
using DirectionT = Vector2;

using VisibleCountT = unsigned;
using NameT = tstring;