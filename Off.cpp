#include "Off.h"

COff::COff()
{
}

COff::~COff()
{
}

bool COff::load(string path)
{
	fstream file;
	string token, token2, token3, v1, v2, v3;
	vector<int> caras(3);
	float vx, vy, vz;
	file.open(path, std::ios::in);

	file >> token; 

	if (token != "OFF")
	{
		file.close();
		return false;
	}
	else
	{
		tipo = token;
		file >> token;
		file >> token2;
		file >> token3;

		mNumOfVertices = atoi(token.c_str());
		mNumOfCaras = atoi(token2.c_str());

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

		for (int i = 0; i < mNumOfVertices-1; i++)
		{
			file >> v1;
			file >> v2;
			file >> v3;

			/*glm::vec3 normalized = glm::normalize(glm::vec3((atof(v1.c_str())), (atof(v2.c_str())), (atof(v3.c_str()))));
			mVertices.push_back(normalized);*/
			vx = atof(v1.c_str());
			vy = atof(v2.c_str());
			vz = atof(v3.c_str());

			mVertices.push_back(glm::vec3(vx,vy,vz));

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

		for (int i = 0; i < mNumOfCaras; i++)
		{
			file >> token3;
			int numofveccara = atoi(token3.c_str());
			int j = 3;
			file >> v1;
			file >> v2;
			file >> v3;	
			caras[0] = atoi(v1.c_str());
			caras[1] = atoi(v2.c_str());
			caras[2] = atoi(v3.c_str());
			mCaras.push_back(caras);
			if (numofveccara > 3)
			{
				while (j < numofveccara)
				{
					caras[1] = caras[2];
					file >> v1;
					caras[2] = atoi(v1.c_str());
					mCaras.push_back(caras);
					j++;
				}
			}
			file.ignore(10000, '\n');
		}
		mNumOfCaras = mCaras.size();
		file.close();
		return true;
	}
}