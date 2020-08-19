#include "SOff.h"

CSOff::CSOff()
{
}

CSOff::~CSOff()
{
}

bool CSOff::load(string path)
{
	fstream file;
	string token, v1, v2, v3;
	float vx, vy, vz;
	file.open(path, std::ios::in);

	file >> token;

	if (token != "SOFF")
	{
		file.close();
		return false;
	}
	else
	{
		tipo = token;
		file >> token;
		mNumOfVertices = atoi(token.c_str());

		file >> v1;
		file >> v2;
		file >> v3;

		vx = atof(v1.c_str());
		vy = atof(v2.c_str());
		vz = atof(v3.c_str());

		xMin = xMax = vx;
		yMin = yMax = vy;
		zMin = zMax = vz;

		mVertices.push_back(glm::vec3(vx, vy, vz));

		for (int i = 0; i < mNumOfVertices - 1; i++)
		{
			file >> v1;
			file >> v2;
			file >> v3;


			vx = atof(v1.c_str());
			vy = atof(v2.c_str());
			vz = atof(v3.c_str());

			mVertices.push_back(glm::vec3(vx, vy, vz));

			if (vx <= xMin)
				xMin = vx;

			if (vy <= yMin)
				yMin = vy;

			if (vz <= zMin)
				zMin = vz;

			if (vx >= xMax)
				xMax = vx;

			if (vy >= yMax)
				yMax = vy;

			if (vz >= zMax)
				zMax = vz;
		}
	
		file.close();
		return true;
	}
}