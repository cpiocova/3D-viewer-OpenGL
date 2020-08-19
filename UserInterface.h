#pragma once

#include "../headers/AntTweakBar.h"
#include "../headers/glm/glm.hpp"
#include "../headers/glm/gtc/quaternion.hpp"
#include "../headers/glm/gtx/quaternion.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include "Windows.h"

using std::string;

enum enumModo
{
	PUNTOS,
	LINEAS,
	TRIANGULOS
};

enum typeProjection
{
	PERSPECTIVE,
	ORTHOGONAL
};


enum typeShading
{
	FLAT, 
	GOURAUD
};

enum deploymentModes
{
	IMMEDIATE,
	DISPLAYL,
	VERTEXP,
	VBO
};

//Singleton user interface class
void TW_CALL loadFile(void *p);
void TW_CALL changebbox(void *p);
void TW_CALL changelights(void *p);
void TW_CALL changenormalsF(void *p);
void TW_CALL changenormalsV(void *p);

class CUserInterface
{
private:
	static CUserInterface * mInterface; //Holds the instance of the class
	TwBar *mUserInterface;
	string mModo;
	string mShading;
	int mModelTotal;
	glm::vec3 mModelTranslation, mLight1Translation, mLight2Translation;
	glm::vec4 mModelScale;
	glm::vec4 mModelRotate;
	float mBoundingColor[3], mModelColor[4], mNFaceColor[3], mNVertexColor[3], mModelColor2[4], mModelColor3[4];
	float mLightColor[4], mLightColor2[4], mLightColor3[4];
	float mMshininess;
	bool backFace, zBuffer;
	int mPicked;


public:
	///Method to obtain the only instance of the calls
	static CUserInterface * Instance();
	~CUserInterface();
	void reshape();
	void show();
	void hide();

	void setModo(string type);
	void setShading(string type);

	void setModelTranslation(float *modelTranslation);
	glm::vec3 getModelTranslation();

	void setModelScale(float * modelScale);
	glm::vec4 getModelScale();

	void setModelRotate(glm::quat quaternion);

	glm::vec4 getModelRotate();

	void boundingColorVisible(bool v);
	void nfaceColorVisible(bool v);
	void nvertexColorVisible(bool v);
	void lightsOptionsVisible(bool v);

	float * getmBColor();
	float * getmMColor();
	float * getmMColor2();
	float * getmMColor3();
	float * getmNFColor();
	float * getmNVColor();
	float getshininess();

	float * getmLightColor();
	float * getmLightColor2();
	float * getmLightColor3();

	void setmBColor(float *color);
	void setmMColor(float *color);
	void setmMColor2(float *color);
	void setmMColor3(float *color);
	void setmNFColor(float *color);
	void setmNVColor(float *color);
	void setshininess(float shini);

	void setmLightColor(float *color);
	void setmLightColor2(float *color);
	void setmLightColor3(float *color);

	void setLight1Translation(float *lightTranslation);
	glm::vec3 getLight1Translation();
	void setLight2Translation(float *lightTranslation);
	glm::vec3 getLight2Translation();

	typeProjection getProjection();
	deploymentModes getDeployment();

	void setModelTotals(int total);
	int getmPicked();
	bool getBackFace();
	bool getZBuffer();

private:
	///Private constructor
	CUserInterface(); 
};