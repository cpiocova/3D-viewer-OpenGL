#include "UserInterface.h"
#include "Model.h"

extern int gWidth, gHeight;
extern enumModo modoActual;
extern typeShading shadeactual;
extern typeProjection projectionActual;
extern deploymentModes deploymentActual;
extern int picked;

// Global static pointer used to ensure a single instance of the class.
CUserInterface * CUserInterface::mInterface = NULL;

/**
* Creates an instance of the class
*
* @return the instance of this class
*/
CUserInterface * CUserInterface::Instance() 
{
	if (!mInterface)   // Only allow one instance of class to be generated.
		 mInterface = new CUserInterface();
 
   return mInterface;
}

CUserInterface::CUserInterface()
{
	mUserInterface = TwNewBar("Model");

	TwDefine("Model refresh = '0.0001f'");
	TwDefine("Model resizable = true");
	TwDefine("Model fontresizable = false");
	TwDefine("Model movable = true");
	TwDefine("Model position = '20 20'");
	TwDefine("Model size = '350 750'");

	TwEnumVal enumModo[] = {
		{ PUNTOS , "Points" },
		{ LINEAS , "Wire-frame" },
		{TRIANGULOS , "Triangles" }
	};
	TwType twEnumModo = TwDefineEnum("Modo", enumModo, 3);

	TwEnumVal enumShade[] = {
	{ FLAT , "Flat Shading" },
	{ GOURAUD, "Gouraud Shading" }
	};
	TwType twEnumShading = TwDefineEnum("Shading", enumShade, 2);

	TwEnumVal enumProjection[] = {
		{ PERSPECTIVE , "Perspective" },
		{ ORTHOGONAL, "Orthogonal" }
	};
	TwType twEnumProjection = TwDefineEnum("Projection", enumProjection, 2);

	TwEnumVal enumDeployment[] = {
		{ IMMEDIATE , "Immediate" },
		{ DISPLAYL, "Display list" },
		{ VERTEXP, "Vertex pointer" },
		{ VBO, "VBO" }
	};
	TwType twEnumDeployment = TwDefineEnum("Deployment", enumDeployment, 4);


	mModelTranslation[0] = 0.0f;
	mModelTranslation[1] = 0.0f;
	mModelTranslation[2] = 0.0f;
	mModelScale[0] = 1.0f;
	mModelScale[1] = 1.0f;
	mModelScale[2] = 1.0f;
	mModelScale[3] = 1.0f;
	mBoundingColor[0] = mBoundingColor[1] = mBoundingColor[2] = 1.0f;
	mNFaceColor[0] = mNFaceColor[1] = mNFaceColor[2] = 1.0f;
	mNVertexColor[0] = mNVertexColor[1] = mNVertexColor[2] = 1.0f;
	mModelColor[0] = mModelColor[1] = mModelColor[2] = 0.0f;
	mModelColor[3] = mModelColor2[0] = mModelColor2[1] = mModelColor2[2] = mModelColor2[3] = mModelColor3[0] = mModelColor3[1] = mModelColor3[2] = mModelColor3[3] = 1.0f;
	mLightColor[0] = mLightColor[1] = mLightColor[2] = mLightColor[3] = mLightColor2[0] = mLightColor2[1] = mLightColor2[2] = mLightColor2[3]= mLightColor3[0] = mLightColor3[1] = mLightColor3[2] = mLightColor3[3] = 1.0f;
	mLight1Translation[0] = 2.0f;
	mLight1Translation[1] = -0.5f;
	mLight1Translation[2] = 2.0f;
	mLight2Translation[0] = -2.0f;
	mLight2Translation[1] = 2.0f;
	mLight2Translation[2] = -2.0f;
	mMshininess = 20.0f;
	backFace = false;
	zBuffer = false;
	TwAddButton(mUserInterface, "LoadFile", loadFile, NULL, " label='Load File' ");
	TwAddSeparator(mUserInterface, "", NULL);
	TwAddVarRW(mUserInterface, "Picked Figure", TW_TYPE_INT32, &picked, " min=-1 label='Picked' ");
	TwAddSeparator(mUserInterface, "", NULL);
	TwAddVarRW(mUserInterface, "Deployment", twEnumDeployment, &deploymentActual, "group = 'Screen Options'");
	TwAddVarRW(mUserInterface, "Projection", twEnumProjection, &projectionActual, "group = 'Screen Options'");
	TwAddVarRW(mUserInterface, "BackFace", TW_TYPE_BOOLCPP, &backFace, "label='BackFace Culling' group = 'Screen Options'");
	TwAddVarRW(mUserInterface, "zBuffer", TW_TYPE_BOOLCPP, &zBuffer, "label='Z-Buffer' group = 'Screen Options'");
	TwAddSeparator(mUserInterface, "", NULL);
	TwAddVarRW(mUserInterface, "Mode", twEnumModo, &modoActual, NULL);
	TwAddVarRW(mUserInterface, "Shading", twEnumShading, &shadeactual, NULL);
	TwAddVarRW(mUserInterface, "ModelColor1", TW_TYPE_COLOR4F, &mModelColor, "label = 'Ambient Color' group='Model Colors'");
	TwAddVarRW(mUserInterface, "ModelColor2", TW_TYPE_COLOR4F, &mModelColor2, "label = 'Diffuse Color' group='Model Colors'");
	TwAddVarRW(mUserInterface, "ModelColor3", TW_TYPE_COLOR4F, &mModelColor3, "label = 'Specular Color' group='Model Colors'");
	TwAddVarRW(mUserInterface, "ModelShininess", TW_TYPE_FLOAT, &mMshininess, " min=0 max=100 step=0.5 label='Model Shininess' group='Model Colors'");
	TwAddSeparator(mUserInterface, "", NULL);
	TwAddButton(mUserInterface, "BoundingBox", changebbox, NULL, " label='On / Off' group='Bounding Box' ");
	TwAddVarRW(mUserInterface, "BoundingColor", TW_TYPE_COLOR3F, &mBoundingColor[0], "label = 'BoundingBox Color' group='Bounding Box' visible = false");
	TwAddSeparator(mUserInterface, "", NULL);
	TwAddButton(mUserInterface, "NormalFace", changenormalsF, NULL, " group='Normal Vector' label='Normal Faces' ");
	TwAddVarRW(mUserInterface, "NFaceColor", TW_TYPE_COLOR3F, &mNFaceColor[0], " group='Normal Vector' label = 'Normal Faces Color' visible = false");
	TwAddButton(mUserInterface, "NormalVetex", changenormalsV, NULL, " group='Normal Vector' label='Normal Vertex' ");
	TwAddVarRW(mUserInterface, "NVertexColor", TW_TYPE_COLOR3F, &mNVertexColor[0], " group='Normal Vector' label = 'Normal Vertex Color' visible = false");
	TwAddSeparator(mUserInterface, "", NULL);
	TwAddVarRW(mUserInterface, "traslateX", TW_TYPE_FLOAT, &mModelTranslation[0], "label='Translate X' group='Translation' step=0.01 ");
	TwAddVarRW(mUserInterface, "traslateY", TW_TYPE_FLOAT, &mModelTranslation[1], "label='Translate Y' group='Translation' step=0.01 ");
	TwAddVarRW(mUserInterface, "traslateZ", TW_TYPE_FLOAT, &mModelTranslation[2], "label='Translate Z' group='Translation' step=0.01 ");
	TwAddSeparator(mUserInterface, "", NULL);
	TwAddVarRW(mUserInterface, "scaleX", TW_TYPE_FLOAT, &mModelScale[0], "label='Scale X' group='Scale' min = 0.01 step=0.01 ");
	TwAddVarRW(mUserInterface, "scaleY", TW_TYPE_FLOAT, &mModelScale[1], "label='Scale Y' group='Scale' min = 0.01 step=0.01 ");
	TwAddVarRW(mUserInterface, "scaleZ", TW_TYPE_FLOAT, &mModelScale[2], "label='Scale Z' group='Scale' min = 0.01 step=0.01 ");
	TwAddVarRW(mUserInterface, "scaleAll", TW_TYPE_FLOAT, &mModelScale[3], "label='Scale' group='Scale' min = 0.01 step=0.01 ");
	TwAddSeparator(mUserInterface, "", NULL);
	TwAddVarRW(mUserInterface, "rotate", TW_TYPE_QUAT4F, &mModelRotate," label='Rotate' opened='true' ");
	TwAddSeparator(mUserInterface, "", NULL);
	TwAddButton(mUserInterface, "LightsOn", changelights, NULL, " label='On / Off' group='Lights' ");
	TwAddVarRW(mUserInterface, "LightsColor1", TW_TYPE_COLOR4F, &mLightColor, "label = 'Ambient Color' group='Lights' visible = false");
	TwAddVarRW(mUserInterface, "LightsColor2", TW_TYPE_COLOR4F, &mLightColor2, "label = 'Difuse Color' group='Lights' visible = false");
	TwAddVarRW(mUserInterface, "LightsColor3", TW_TYPE_COLOR4F, &mLightColor3, "label = 'Specular Color' group='Lights' visible = false");
	TwAddVarRW(mUserInterface, "traslateL1X", TW_TYPE_FLOAT, &mLight1Translation[0], "label='TranslateL1 X' group='Lights' visible = false step=0.01 ");
	TwAddVarRW(mUserInterface, "traslateL1Y", TW_TYPE_FLOAT, &mLight1Translation[1], "label='TranslateL1 Y' group='Lights' visible = false step=0.01 ");
	TwAddVarRW(mUserInterface, "traslateL1Z", TW_TYPE_FLOAT, &mLight1Translation[2], "label='TranslateL1 Z' group='Lights' visible = false step=0.01 ");
	TwAddVarRW(mUserInterface, "traslateL2X", TW_TYPE_FLOAT, &mLight2Translation[0], "label='TranslateL2 X' group='Lights' visible = false step=0.01 ");
	TwAddVarRW(mUserInterface, "traslateL2Y", TW_TYPE_FLOAT, &mLight2Translation[1], "label='TranslateL2 Y' group='Lights' visible = false step=0.01 ");
	TwAddVarRW(mUserInterface, "traslateL2Z", TW_TYPE_FLOAT, &mLight2Translation[2], "label='TranslateL2 Z' group='Lights' visible = false step=0.01 ");
}


CUserInterface::~CUserInterface()
{
}

void CUserInterface::reshape()
{
	TwWindowSize(gWidth, gHeight);
}

void CUserInterface::show()
{
	TwDefine("Figure visible = true");
}

void CUserInterface::hide()
{
	TwDefine("Figure visible = false");
}

void CUserInterface::setmBColor(float *color)
{
	mBoundingColor[0] = color[0];
	mBoundingColor[1] = color[1];
	mBoundingColor[2] = color[2];
}

void CUserInterface::setmMColor(float *color)
{
	mModelColor[0] = color[0];
	mModelColor[1] = color[1];
	mModelColor[2] = color[2];
	mModelColor[3] = color[3];
}

void CUserInterface::setmMColor2(float *color)
{
	mModelColor2[0] = color[0];
	mModelColor2[1] = color[1];
	mModelColor2[2] = color[2];
	mModelColor2[3] = color[3];
}

void CUserInterface::setmMColor3(float *color)
{
	mModelColor3[0] = color[0];
	mModelColor3[1] = color[1];
	mModelColor3[2] = color[2];
	mModelColor3[3] = color[3];
}

void CUserInterface::setmNFColor(float *color)
{
	mNFaceColor[0] = color[0];
	mNFaceColor[1] = color[1];
	mNFaceColor[2] = color[2];
}

void CUserInterface::setmNVColor(float *color)
{
	mNVertexColor[0] = color[0];
	mNVertexColor[1] = color[1];
	mNVertexColor[2] = color[2];
}

void CUserInterface::setshininess(float shini)
{
	mMshininess = shini;
}

void CUserInterface::setmLightColor(float *color)
{
	mLightColor[0] = color[0];
	mLightColor[1] = color[1];
	mLightColor[2] = color[2];
	mLightColor[3] = color[3];
}

void CUserInterface::setmLightColor2(float *color)
{
	mLightColor2[0] = color[0];
	mLightColor2[1] = color[1];
	mLightColor2[2] = color[2];
	mLightColor2[3] = color[3];
}

void CUserInterface::setmLightColor3(float *color)
{
	mLightColor3[0] = color[0];
	mLightColor3[1] = color[1];
	mLightColor3[2] = color[2];
	mLightColor3[3] = color[3];
}

float* CUserInterface::getmBColor()
{
	return mBoundingColor;
}

float* CUserInterface::getmMColor()
{
	return mModelColor;
}

float* CUserInterface::getmMColor2()
{
	return mModelColor2;
}

float* CUserInterface::getmMColor3()
{
	return mModelColor3;
}

float* CUserInterface::getmNFColor()
{
	return mNFaceColor;
}

float* CUserInterface::getmNVColor()
{
	return mNVertexColor;
}

float CUserInterface::getshininess()
{
	return mMshininess;
}

float* CUserInterface::getmLightColor()
{
	return mLightColor;
}

float* CUserInterface::getmLightColor2()
{
	return mLightColor2;
}

float* CUserInterface::getmLightColor3()
{
	return mLightColor3;
}

void CUserInterface::setModelTranslation(float *modelTranslation)
{
	mModelTranslation[0] = modelTranslation[0];
	mModelTranslation[1] = modelTranslation[1];
	mModelTranslation[2] = modelTranslation[2];
}

glm::vec3 CUserInterface::getLight1Translation()
{
	return mLight1Translation;
}

void CUserInterface::setLight1Translation(float *lightTranslation)
{
	mLight1Translation[0] = lightTranslation[0];
	mLight1Translation[1] = lightTranslation[1];
	mLight1Translation[2] = lightTranslation[2];
}

glm::vec3 CUserInterface::getLight2Translation()
{
	return mLight2Translation;
}

void CUserInterface::setLight2Translation(float *lightTranslation)
{
	mLight2Translation[0] = lightTranslation[0];
	mLight2Translation[1] = lightTranslation[1];
	mLight2Translation[2] = lightTranslation[2];
}

glm::vec3 CUserInterface::getModelTranslation()
{
	return mModelTranslation;
}
void CUserInterface::setModelScale(float *modelScale)
{
	mModelScale[0] = modelScale[0];
	mModelScale[1] = modelScale[1];
	mModelScale[2] = modelScale[2];
	mModelScale[3] = modelScale[3];
}

glm::vec4 CUserInterface::getModelScale()
{
	return mModelScale;
}

void CUserInterface::setModelRotate(glm::quat quaternion)
{
	mModelRotate[0] = quaternion.x;
	mModelRotate[1] = quaternion.y;
	mModelRotate[2] = quaternion.z;
	mModelRotate[3] = quaternion.w;
}

glm::vec4 CUserInterface::getModelRotate()
{
	return mModelRotate;
}

void CUserInterface::setModo(string type)
{
	mModo = type;
}

void CUserInterface::setShading(string type)
{
	mShading = type;
}

void CUserInterface::boundingColorVisible(bool v)
{
	if (v) {
		TwDefine("Model/BoundingColor visible = true");
	}
	else {
		TwDefine("Model/BoundingColor visible = false");
	}

}

void CUserInterface::lightsOptionsVisible(bool v)
{
	if (v) {
		TwDefine("Model/LightsColor1 visible = true");
		TwDefine("Model/LightsColor2 visible = true");
		TwDefine("Model/LightsColor3 visible = true");
		TwDefine("Model/traslateL1X visible = true");
		TwDefine("Model/traslateL1Y visible = true");
		TwDefine("Model/traslateL1Z visible = true");
		TwDefine("Model/traslateL2X visible = true"); 
		TwDefine("Model/traslateL2Y visible = true");
		TwDefine("Model/traslateL2Z visible = true");
	}
	else {
		TwDefine("Model/LightsColor1 visible = false");
		TwDefine("Model/LightsColor2 visible = false");
		TwDefine("Model/LightsColor3 visible = false");
		TwDefine("Model/traslateL1X visible = false");
		TwDefine("Model/traslateL1Y visible = false");
		TwDefine("Model/traslateL1Z visible = false");
		TwDefine("Model/traslateL2X visible = false");
		TwDefine("Model/traslateL2Y visible = false");
		TwDefine("Model/traslateL2Z visible = false");
	}

}

void CUserInterface::nfaceColorVisible(bool v)
{
	if (v) {
		TwDefine("Model/NFaceColor visible = true");
	}
	else {
		TwDefine("Model/NFaceColor visible = false");
	}

}

void CUserInterface::nvertexColorVisible(bool v)
{
	if (v) {
		TwDefine("Model/NVertexColor visible = true");
	}
	else {
		TwDefine("Model/NVertexColor visible = false");
	}

}

typeProjection CUserInterface::getProjection()
{
	return projectionActual;
}

bool CUserInterface::getBackFace()
{
	return backFace;
}

bool CUserInterface::getZBuffer()
{
	return zBuffer;
}

deploymentModes CUserInterface::getDeployment()
{
	return deploymentActual;
}

void CUserInterface::setModelTotals(int total)
{
}

int CUserInterface::getmPicked()
{
	return mPicked;
}
