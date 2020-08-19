#pragma once

#include "../headers/glfw3.h"
#include "UserInterface.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class CModel
{
	protected:
		vector<glm::vec3> mVertices;
		vector<vector<int>> mCaras;
		glm::vec3 mTranslation;
		glm::vec4 mScale;
		glm::quat mRotate;
		int mNumOfVertices;
		int mNumOfCaras;
		float xMin, xMax, yMin, yMax, zMin, zMax;
		float mBColor[3], mMColor[4], mMColor2[4], mMColor3[4], mNFColor[3], mNVColor[3];
		float shininess;
		string tipo;
		enumModo modo;
		typeShading shading;
		vector<glm::vec3> mNormalesC;
		vector<glm::vec3> mNormalesV;
		vector<glm::vec3> mCentroideC;
	public:
		CModel();
		~CModel();
		virtual bool load(string path) = 0;
		virtual void display(deploymentModes typeDeployment);
		void BoundingBox();
		void setTranslation(glm::vec3 translation);
		glm::vec3 getTranslation();
		glm::vec4 getScale();
		void calculateNormals();
		void displayNormalsFace();
		void displayNormalsVertex();
		void setScale(glm::vec4 scale);
		glm::vec3 boundingVertex(bool d);
		glm::quat getRotate();
		void setRotate(glm::quat quaternion);
		void setModo(enumModo modo);
		enumModo getModo();
		void setShading(typeShading shading);
		typeShading getShading();
		void setBColor(float r, float g, float b);
		void setMColor(float r, float g, float b, float a);
		void setMColor2(float r, float g, float b, float a);
		void setMColor3(float r, float g, float b, float a);
		void setNFColor(float r, float g, float b);
		void setNVColor(float r, float g, float b);
		void setshininess(float shini);

		float * getBColor();
		float * getMColor();
		float * getMColor2();
		float * getMColor3();
		float * getNFColor();
		float * getNVColor();
		float getshininess();

		void dImmediate();
		void dDisplayList();
		void dVertexPointer();
		void dVBO();
};