#pragma once

#include "Model.h"
#include <iostream>


using std::fstream;

class CSOff : public CModel
{
	public:
		CSOff();
		~CSOff();
		bool load(string path);
};