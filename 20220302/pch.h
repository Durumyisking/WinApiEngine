#pragma once




#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             

#include <windows.h>


#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <Windows.h>
// 라이브러리 참조
#pragma comment(lib, "Msimg32.lib") // 이미지 관리 라이브러리

// 소리
//#include <mmsystem.h>
//#include <dsound.h>
//#include <dinput.h>
//
//#pragma comment(lib, "winmm.lib")
//#pragma comment(lib, "dsound.lib")


#include <assert.h>

#include <vector>
using std::vector;
#include <map>
using std::map;
using std::make_pair;
#include <list>
using std::list;


#include <string>
#include <sstream>
using std::string;
using std::wstring;

#include <math.h>
#include <time.h>

#include <Commdlg.h>

// 함수포인터 관련 라이브러리
#include <functional>


// custom header
#include "define.h"
#include "struct.h"
#include "func.h"

