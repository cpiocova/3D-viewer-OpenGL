#pragma once

#include "Model.h"
#include <iostream>
#include <sstream>



class CObj : public CModel
{
public:
	CObj();
	~CObj();
	bool load(string path);
};