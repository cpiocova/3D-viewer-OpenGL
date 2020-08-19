#include "Model.h"



CModel::CModel()
{
	mTranslation[0] = mTranslation[1] = mTranslation[2] = 0.0f;
	mScale[0] = mScale[1] = mScale[2] = 1.0f;
	mRotate = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	modo = PUNTOS;
	mMColor[0] = mMColor[1] = mMColor[2] = 0.0f;
	mMColor[3] = mMColor2[0] = mMColor2[1] = mMColor2[2] = mMColor2[3] = 1.0f;
	mMColor3[0] = mMColor3[1] = mMColor3[2] = mMColor3[3] = 1.0f;
	mBColor[0] = mBColor[1] = mBColor[2] = 1.0f;
	mNFColor[0] = mNFColor[1] = mNFColor[2] = 1.0f; 
	mNVColor[0] = mNVColor[1] = mNVColor[2] = 1.0f;
	shininess = 20.0f;
}

CModel::~CModel()
{
}

void CModel::display(deploymentModes typeDeployment)
{
	
	//glColor4f(mMColor[0], mMColor[1], mMColor[2], mMColor[3]);

	if (modo == PUNTOS)
	{
		glDisable(GL_LIGHTING);
		//glColor4f(mMColor[0], mMColor[1], mMColor[2], mMColor[3]);
		glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
	}
	else if (modo == LINEAS)
	{
		//glColor4f(mMColor[0], mMColor[1], mMColor[2], mMColor[3]);
		glDisable(GL_LIGHTING);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else if (modo == TRIANGULOS)
	{
		//glEnable(GL_LIGHTING);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		
	}


//------------------------------------------------------------------//

	if (typeDeployment == IMMEDIATE)
	{
		dImmediate();
	}

	if (typeDeployment == DISPLAYL)
	{
		dDisplayList();
	}

	if (typeDeployment == VERTEXP)
	{
		dVertexPointer();
	}

	if (typeDeployment == VBO)
	{
		dVBO();
	}

	


}

void CModel::dImmediate()
{
	//cout << mVertices[0][0];
	if (tipo == "SOFF")
	{
		for (int i = 0; i < mNumOfVertices; i += 3)
		{
			//glColor3f(mMColor[0], mMColor[1], mMColor[2]);
			glBegin(GL_TRIANGLES);
			glVertex3f(mVertices[i].x, mVertices[i].y, mVertices[i].z);
			glVertex3f(mVertices[i + 1].x, mVertices[i + 1].y, mVertices[i + 1].z);
			glVertex3f(mVertices[i + 2].x, mVertices[i + 2].y, mVertices[i + 2].z);
			glEnd();
		}
	}
	else if (tipo == "OBJ" || tipo == "OFF")
	{
		
		glBegin(GL_TRIANGLES);
		
		for (int i = 0; i < mNumOfCaras; i++)
		{
			if (!(modo == TRIANGULOS))
			{
				glColor4f(mMColor[0], mMColor[1], mMColor[2], mMColor[3]);
			}
			if (modo == TRIANGULOS)
			{
				glColor4f(mMColor[0], mMColor[1], mMColor[2], mMColor[3]);
				glEnable(GL_COLOR_MATERIAL);
				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mMColor);
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mMColor2);
				glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mMColor3);
				glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
				//glNormal3f(mNormalesC[i].x, mNormalesC[i].y, mNormalesC[i].z);
				if (shading == FLAT)
				{
					glShadeModel(GL_FLAT);
					glNormal3f(mNormalesC[i].x, mNormalesC[i].y, mNormalesC[i].z);
				}
				else
				{
					glShadeModel(GL_SMOOTH);
					glNormal3f(mNormalesV[mCaras[i][0]].x, mNormalesV[mCaras[i][0]].y, mNormalesV[mCaras[i][0]].z);
				}
			}
			glVertex3f(mVertices[mCaras[i][0]].x, mVertices[mCaras[i][0]].y, mVertices[mCaras[i][0]].z);
			if (modo == TRIANGULOS && shading == GOURAUD)
			{
				glNormal3f(mNormalesV[mCaras[i][1]].x, mNormalesV[mCaras[i][1]].y, mNormalesV[mCaras[i][1]].z);
			}
			glVertex3f(mVertices[mCaras[i][1]].x, mVertices[mCaras[i][1]].y, mVertices[mCaras[i][1]].z);
			if (modo == TRIANGULOS && shading == GOURAUD)
			{
				glNormal3f(mNormalesV[mCaras[i][2]].x, mNormalesV[mCaras[i][2]].y, mNormalesV[mCaras[i][2]].z);
			}
			glVertex3f(mVertices[mCaras[i][2]].x, mVertices[mCaras[i][2]].y, mVertices[mCaras[i][2]].z);
		}

		glEnd();
		glDisable(GL_COLOR_MATERIAL);
	}

}

void CModel::dDisplayList()
{
	int displayList = glGenLists(1);
	

	glNewList(displayList, GL_COMPILE);
	
	if (tipo == "SOFF")
	{
		for (int i = 0; i < mNumOfVertices; i += 3)
		{
			glColor3f(mMColor[0], mMColor[1], mMColor[2]);
			glBegin(GL_TRIANGLES);
			glVertex3f(mVertices[i].x, mVertices[i].y, mVertices[i].z);
			glVertex3f(mVertices[i + 1].x, mVertices[i + 1].y, mVertices[i + 1].z);
			glVertex3f(mVertices[i + 2].x, mVertices[i + 2].y, mVertices[i + 2].z);
			glEnd();
		}
	}
	else if (tipo == "OBJ" || tipo == "OFF")
	{
		//glColor4f(mMColor[0], mMColor[1], mMColor[2], mMColor[3]);
		glBegin(GL_TRIANGLES);

		for (int i = 0; i < mNumOfCaras; i++)
		{
			if (!(modo == TRIANGULOS))
			{
				glColor4f(mMColor[0], mMColor[1], mMColor[2], mMColor[3]);
			}
			if (modo == TRIANGULOS)
			{
				glColor4f(mMColor[0], mMColor[1], mMColor[2], mMColor[3]);
				glEnable(GL_COLOR_MATERIAL);
				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mMColor);
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mMColor2);
				glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mMColor3);
				glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
				//glNormal3f(mNormalesC[i].x, mNormalesC[i].y, mNormalesC[i].z);
				if (shading == FLAT)
				{
					glShadeModel(GL_FLAT);
					glNormal3f(mNormalesC[i].x, mNormalesC[i].y, mNormalesC[i].z);
				}
				else
				{
					glShadeModel(GL_SMOOTH);
					glNormal3f(mNormalesV[mCaras[i][0]].x, mNormalesV[mCaras[i][0]].y, mNormalesV[mCaras[i][0]].z);
				}
			}
			glVertex3f(mVertices[mCaras[i][0]].x, mVertices[mCaras[i][0]].y, mVertices[mCaras[i][0]].z);
			if (modo == TRIANGULOS && shading == GOURAUD)
			{
				glNormal3f(mNormalesV[mCaras[i][1]].x, mNormalesV[mCaras[i][1]].y, mNormalesV[mCaras[i][1]].z);
			}
			glVertex3f(mVertices[mCaras[i][1]].x, mVertices[mCaras[i][1]].y, mVertices[mCaras[i][1]].z);
			if (modo == TRIANGULOS && shading == GOURAUD)
			{
				glNormal3f(mNormalesV[mCaras[i][2]].x, mNormalesV[mCaras[i][2]].y, mNormalesV[mCaras[i][2]].z);
			}
			glVertex3f(mVertices[mCaras[i][2]].x, mVertices[mCaras[i][2]].y, mVertices[mCaras[i][2]].z);
		}

		glEnd();
		glDisable(GL_COLOR_MATERIAL);
	}

	glEndList();
	glCallList(displayList);
	glDeleteLists(displayList,1);

}

void CModel::dVertexPointer()
{

	int numPoints = mCaras.size() * 3;
	GLint *faceArray = new GLint[numPoints];
	GLfloat *vertexArray = new GLfloat[mNumOfVertices * 3];
	GLfloat *vertexNormals = new GLfloat[mNumOfVertices * 3];
	GLfloat *facesNormals = new GLfloat[mNumOfCaras * 3];

	for (int i = 0; i < mNumOfCaras; i++)
	{
		faceArray[(i * 3)] = mCaras[i][0];
		faceArray[(i * 3) + 1] = mCaras[i][1];
		faceArray[(i * 3) + 2] = mCaras[i][2];
	}

	for (int j = 0; j < mNumOfVertices; j++)
	{
		vertexArray[(j * 3)] = mVertices[j].x;
		vertexArray[(j * 3) + 1] = mVertices[j].y;
		vertexArray[(j * 3) + 2] = mVertices[j].z;
	}

	for (int j = 0; j < mNumOfVertices; j++)
	{
		vertexNormals[(j * 3)] = mNormalesV[j].x;
		vertexNormals[(j * 3) + 1] = mNormalesV[j].y;
		vertexNormals[(j * 3) + 2] = mNormalesV[j].z;
	}

	for (int i = 0; i < mNumOfCaras; i++)
	{
		facesNormals[(i * 3)] = mNormalesC[i].x;
		facesNormals[(i * 3) + 1] = mNormalesC[i].y;
		facesNormals[(i * 3) + 2] = mNormalesC[i].z;
	}

	//GLfloat colours[] = { mMColor[0], mMColor[1], mMColor[2], mMColor2[0], mMColor2[1], mMColor2[2], mMColor3[0], mMColor3[1], mMColor3[2] };
		
	

	//glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	
	glColor4f(mMColor[0], mMColor[1], mMColor[2], mMColor[3]);
	if (modo == TRIANGULOS)
	{
		glEnable(GL_COLOR_MATERIAL);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mMColor);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mMColor2);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mMColor3);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
		if (shading == FLAT)
		{
			
			glShadeModel(GL_FLAT);
			glNormalPointer(GL_FLOAT, 0, facesNormals);
		}
		else
		{
			glShadeModel(GL_SMOOTH);
			glNormalPointer(GL_FLOAT, 0,vertexNormals);
		}
	}
	glVertexPointer(3, GL_FLOAT, 0, vertexArray);

	
	//glColorPointer(3, GL_FLOAT, 0, colours);

	glDrawElements(GL_TRIANGLES, numPoints, GL_UNSIGNED_INT, faceArray);

	
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_COLOR_ARRAY);
	glDisable(GL_COLOR_MATERIAL);
}

void CModel::dVBO()
{
	int numPoints = mCaras.size() * 3;
	GLint *faceArray = new GLint[numPoints];
	GLfloat *vertexArray = new GLfloat[mNumOfVertices * 3];
	GLfloat *vertexNormals = new GLfloat[mNumOfVertices * 3];
	GLfloat *facesNormals = new GLfloat[mNumOfCaras * 3];

	for (int i = 0; i < mNumOfCaras; i++)
	{
		faceArray[(i * 3)] = mCaras[i][0];
		faceArray[(i * 3) + 1] = mCaras[i][1];
		faceArray[(i * 3) + 2] = mCaras[i][2];
	}

	for (int j = 0; j < mNumOfVertices; j++)
	{
		vertexArray[(j * 3)] = mVertices[j].x;
		vertexArray[(j * 3) + 1] = mVertices[j].y;
		vertexArray[(j * 3) + 2] = mVertices[j].z;
	}

	for (int j = 0; j < mNumOfVertices; j++)
	{
		vertexNormals[(j * 3)] = mNormalesV[j].x;
		vertexNormals[(j * 3) + 1] = mNormalesV[j].y;
		vertexNormals[(j * 3) + 2] = mNormalesV[j].z;
	}

	for (int i = 0; i < mNumOfCaras; i++)
	{
		facesNormals[(i * 3)] = mNormalesC[i].x;
		facesNormals[(i * 3) + 1] = mNormalesC[i].y;
		facesNormals[(i * 3) + 2] = mNormalesC[i].z;
	}

	GLuint vbo, vindex, vnormals;
	
	//glGenBuffers(1, &vbo); 
	//glGenBuffers(1, &vindex);
}

void CModel::BoundingBox()
{
	
	glDisable(GL_LIGHTING);
	glColor3f(mBColor[0], mBColor[1], mBColor[2]);
	glLineWidth(2);
	glBegin(GL_LINES);
		glVertex3f(xMin,yMin, zMax);
		glVertex3f(xMax, yMin, zMax);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(xMax, yMin, zMax);
		glVertex3f(xMax, yMax, zMax);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(xMax, yMax, zMax);
		glVertex3f(xMin, yMax, zMax);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(xMin, yMax, zMax);
		glVertex3f(xMin, yMin, zMax);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(xMin, yMax, zMax);
		glVertex3f(xMin, yMax, zMin);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(xMin, yMax, zMin);
		glVertex3f(xMax, yMax, zMin);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(xMax, yMax, zMin);
		glVertex3f(xMax, yMax, zMax);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(xMax, yMax, zMin);
		glVertex3f(xMax, yMin, zMin);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(xMax, yMin, zMin);
		glVertex3f(xMax, yMin, zMax);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(xMax, yMin, zMin);
		glVertex3f(xMin, yMin, zMin);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(xMin, yMin, zMin);
		glVertex3f(xMin, yMax, zMin);
	glEnd();

	glBegin(GL_LINES);
		glVertex3f(xMin, yMin, zMin);
		glVertex3f(xMin, yMin, zMax);
	glEnd();
	glLineWidth(1);
}

typeShading CModel::getShading()
{
	return shading;
}

void CModel::setBColor(float r, float g, float b)
{
	mBColor[0] = r;
	mBColor[1] = g;
	mBColor[2] = b;
}
void CModel::setMColor(float r, float g, float b, float a)
{
	mMColor[0] = r;
	mMColor[1] = g;
	mMColor[2] = b;
	mMColor[3] = a;
}

void CModel::setMColor2(float r, float g, float b, float a)
{
	mMColor2[0] = r;
	mMColor2[1] = g;
	mMColor2[2] = b;
	mMColor2[3] = a;
}

void CModel::setMColor3(float r, float g, float b, float a)
{
	mMColor3[0] = r;
	mMColor3[1] = g;
	mMColor3[2] = b;
	mMColor3[3] = a;
}

void CModel::setNFColor(float r, float g, float b)
{
	mNFColor[0] = r;
	mNFColor[1] = g;
	mNFColor[2] = b;
}

void CModel::setNVColor(float r, float g, float b)
{
	mNVColor[0] = r;
	mNVColor[1] = g;
	mNVColor[2] = b;
}

void CModel::setshininess(float shini)
{
	shininess = shini;
}


float* CModel::getBColor()
{
	return mBColor;
}

float* CModel::getMColor()
{
	return mMColor;
}

float* CModel::getMColor2()
{
	return mMColor2;
}

float* CModel::getMColor3()
{
	return mMColor3;
}

float* CModel::getNFColor()
{
	return mNFColor;
}

float* CModel::getNVColor()
{
	return mNVColor;
}

float CModel::getshininess()
{
	return shininess;
}


void CModel::setTranslation(glm::vec3 translation)
{
	if (&translation != NULL) 
		mTranslation = translation;
	
}

glm::vec3 CModel::getTranslation()
{
	return mTranslation;
}

void CModel::setScale(glm::vec4 scale)
{
	if (&scale != NULL)
		mScale = scale;

}

glm::vec3 CModel::boundingVertex(bool d)
{
	if (d)
	{
		return glm::vec3(xMin, yMin, zMin);
	}
	else
	{
		return glm::vec3(xMax, yMax, zMax);
	}
}

glm::quat CModel::getRotate()
{
	return mRotate;
}

void CModel::setRotate(glm::quat quaternion)
{
	mRotate = quaternion;
}

void CModel::setModo(enumModo modo)
{
	this->modo = modo;
}

enumModo CModel::getModo()
{
	return modo;
}

void CModel::setShading(typeShading shading)
{
	this->shading = shading;
}

glm::vec4 CModel::getScale()
{
	return mScale;
} 

void CModel::calculateNormals() 
{
	if (tipo == "SOFF" /*|| tipo == "OBJ"*/)
		return;

	vector<vector<int>> incidences(mNumOfVertices);
	/*glm::vec3 maxbboxh = this->boundingVertex(false);
	glm::vec3 minbboxh = this->boundingVertex(true);
	float maxscaleh = max(max(abs(maxbboxh.x - minbboxh.x), abs(maxbboxh.y - minbboxh.y)), abs(maxbboxh.z - minbboxh.z));
	glm::vec3 auxnc; */
	for (int i = 0; i < mNumOfCaras; i++)
	{
		mCentroideC.push_back(glm::vec3((mVertices[mCaras[i][2]].x + mVertices[mCaras[i][1]].x + mVertices[mCaras[i][0]].x) / 3,
										(mVertices[mCaras[i][2]].y + mVertices[mCaras[i][1]].y + mVertices[mCaras[i][0]].y) / 3,
										(mVertices[mCaras[i][2]].z + mVertices[mCaras[i][1]].z + mVertices[mCaras[i][0]].z) / 3));

		/*auxnc = glm::cross(mVertices[mCaras[i][1]] - mVertices[mCaras[i][0]], mVertices[mCaras[i][2]] - mVertices[mCaras[i][0]]);
		auxnc.x = auxnc.x / maxscaleh;
		auxnc.y = auxnc.y / maxscaleh;
		auxnc.z = auxnc.z / maxscaleh;
		auxnc = glm::normalize(auxnc);
		mNormalesC.push_back(auxnc);*/
		mNormalesC.push_back(glm::normalize(glm::cross(mVertices[mCaras[i][1]]- mVertices[mCaras[i][0]], mVertices[mCaras[i][2]]- mVertices[mCaras[i][0]])));
		//mNormalesC.push_back(glm::cross(mVertices[mCaras[i][2]] - mVertices[mCaras[i][0]], mVertices[mCaras[i][1]] - mVertices[mCaras[i][0]]));
		incidences[mCaras[i][0]].push_back(i);
		incidences[mCaras[i][1]].push_back(i);
		incidences[mCaras[i][2]].push_back(i);
	}
	glm::vec3 auxnorm2;
	glm::vec3 vec0 = glm::vec3(0, 0, 0);
	int cant = 1;
	for (int i = 0; i < incidences.size(); i++)
	{
		auxnorm2.x = vec0.x;
		auxnorm2.y = vec0.y;
		auxnorm2.z = vec0.z;
		for (int j = 0; j < incidences[i].size(); j++)
		{
			auxnorm2.x += mNormalesC[incidences[i][j]].x;
			auxnorm2.y += mNormalesC[incidences[i][j]].y;
			auxnorm2.z += mNormalesC[incidences[i][j]].z;
		}
		if (incidences[i].size() > 0)
		{
			cant = incidences[i].size();
		}
		auxnorm2.x = auxnorm2.x / cant;
		auxnorm2.y = auxnorm2.y / cant;
		auxnorm2.z = auxnorm2.z / cant;
		mNormalesV.push_back(auxnorm2);
		cant = 1;
	}
}

void CModel::displayNormalsFace()
{
	if (tipo == "SOFF" /*|| tipo == "OBJ"*/)
		return;

	glDisable(GL_LIGHTING);
	glColor3f(mNFColor[0], mNFColor[1], mNFColor[2]);
	glPointSize(3.0);
	for (int i = 0; i < mNormalesC.size(); i++)
	{
		glBegin(GL_LINES);
			glVertex3f(mCentroideC[i].x, mCentroideC[i].y, mCentroideC[i].z);
			glVertex3f((mNormalesC[i].x + mCentroideC[i].x) , (mNormalesC[i].y + mCentroideC[i].y) , (mNormalesC[i].z + mCentroideC[i].z));
		glEnd();
		/*glBegin(GL_LINES);
			glVertex3f(mCentroideC[i].x, mCentroideC[i].y, mCentroideC[i].z);
			glVertex3f((-mNormalesC[i].x + mCentroideC[i].x), (-mNormalesC[i].y + mCentroideC[i].y), (-mNormalesC[i].z + mCentroideC[i].z));
		glEnd();*/
	}

	glPointSize(1.0);
}

void CModel::displayNormalsVertex()
{
	if (tipo == "SOFF" /*|| tipo == "OBJ"*/)
		return;

	glDisable(GL_LIGHTING);
	glColor3f(mNVColor[0], mNVColor[1], mNVColor[2]);
	glPointSize(3.0);
	for (int i = 0; i < mNormalesV.size(); i++)
	{
		glBegin(GL_LINES);
			glVertex3f(mVertices[i].x, mVertices[i].y, mVertices[i].z);
			glVertex3f((mNormalesV[i].x + mVertices[i].x), (mNormalesV[i].y + mVertices[i].y), (mNormalesV[i].z + mVertices[i].z));
		glEnd();

		/*glBegin(GL_LINES);
			glVertex3f(mVertices[i].x, mVertices[i].y, mVertices[i].z);
			glVertex3f((-mNormalesV[i].x + mVertices[i].x) , (-mNormalesV[i].y + mVertices[i].y) , (-mNormalesV[i].z + mVertices[i].z) );
		glEnd();*/
	}
	glPointSize(1.0);
}