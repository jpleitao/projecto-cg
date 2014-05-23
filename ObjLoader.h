#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>

#include "ModelArrays.h"


class ObjLoader {

    FILE* file;

	public:
		ObjLoader(const char* name);
		~ObjLoader();
		ModelArrays load();
};

#endif
