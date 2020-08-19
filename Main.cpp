#include "Main.h"
#include "Model.h"
#include "SOff.h"
#include "Off.h"
#include "Obj.h"


using std::vector;

GLFWwindow *gWindow;
int gWidth, gHeight;
CUserInterface * userInterface;
vector <CModel *> models;
int picked = -1;
enumModo modoActual = PUNTOS;
typeShading shadeactual = FLAT;
typeProjection projectionActual = PERSPECTIVE;
deploymentModes deploymentActual = IMMEDIATE;
typeProjection pProject;
int totalmodels = 0;
bool shownormalsF = false, shownormalsV = false, showbbox = false, showlights = false, backFace, zBuffer;
vector <CModel *> lights;
GLfloat lightambient[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat lightdiffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat lightspecular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat lightposition1[] = { 2.0, -2.0, 2.0, 0.0 };
GLfloat lightposition2[] = { -2.0, 2.0, -2.0, 0.0 };

void initLights()
{
	CObj * light1 = new CObj();
	if (!light1->load("../files/cubo.obj")) {
		cout << "hOLA";
		return;
	}
		
	float traslationaux[3];
	glm::vec3 traslation0;
	traslationaux[0] = lightposition1[0];
	traslationaux[1] = lightposition1[1];
	traslationaux[2] = lightposition1[2];
	traslation0.x = lightposition1[0];
	traslation0.y = lightposition1[1];
	traslation0.z = lightposition1[2];
	lights.push_back(light1);
	userInterface->setModelTranslation(traslationaux);
	lights[0]->setTranslation(traslation0);
	lights[0]->setModo(TRIANGULOS);
	lights[0]->setShading(FLAT);
	lights[0]->setMColor(lightambient[0], lightambient[1], lightambient[2], lightambient[3]);
	lights[0]->calculateNormals();
	CObj * light2 = new CObj();
	if (!light2->load("../files/cubo.obj"))
		return;
	traslationaux[0] = lightposition2[0];
	traslationaux[1] = lightposition2[1];
	traslationaux[2] = lightposition2[2];
	traslation0.x = lightposition2[0];
	traslation0.y = lightposition2[1];
	traslation0.z = lightposition2[2];
	lights.push_back(light2);
	userInterface->setModelTranslation(traslationaux);
	lights[1]->setTranslation(traslation0);
	lights[1]->setModo(TRIANGULOS);
	lights[1]->setShading(FLAT);
	lights[1]->setMColor(lightambient[0], lightambient[1], lightambient[2], lightambient[3]);
	lights[1]->calculateNormals();

}



string openfilename()
{
	OPENFILENAME ofn;
	char fileName[MAX_PATH] = "";
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFilter = "All Files\0*.OBJ;*.SOFF;*.OFF";
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "";
	string fileNameStr;
	if (GetOpenFileName(&ofn))
		fileNameStr = fileName;
	return fileNameStr;
}

void TW_CALL changebbox(void * p)
{
	showbbox = !showbbox;
	userInterface->boundingColorVisible(showbbox);

}

void TW_CALL changelights(void * p)
{
	showlights = !showlights;
	userInterface->lightsOptionsVisible(showlights);

}

void TW_CALL changenormalsF(void * p)
{
	shownormalsF = !shownormalsF;
	userInterface->nfaceColorVisible(shownormalsF);
}

void TW_CALL changenormalsV(void * p)
{
	shownormalsV = !shownormalsV;
	userInterface->nvertexColorVisible(shownormalsV);
}

void TW_CALL loadFile(void * p)
{
	string name = openfilename();

	if (name.substr(name.find_last_of(".") + 1) == "soff")
	{
		CSOff * soff = new CSOff();
		if (!soff->load(name))
			return;
		picked++;
		glm::vec3 traslation0;
		glm::vec4 scale0;
		float *traslationaux = new float[3];
		float *scaleaux = new float[4];
		traslationaux[0] = traslationaux[1] = traslationaux[2] = 0.0f;
		traslation0[0] = traslation0[1] = traslation0[2] = 0.0f;
		scaleaux[0] = scaleaux[1] = scaleaux[2] = scaleaux[3] = 1.0f;
		scale0.x = scale0.y = scale0.z = scale0.w = 1.0f;
		models.push_back(soff);
		userInterface->setModelTranslation(traslationaux);
		models[picked]->setTranslation(traslation0);
		userInterface->setModelScale(scaleaux);
		models[picked]->setScale(scale0);
		models[picked]->setModo(modoActual);
		models[picked]->setShading(shadeactual);
	}
	else if (name.substr(name.find_last_of(".") + 1) == "obj")
	{
		CObj * obj = new CObj();
		if (!obj->load(name))
			return;
		picked++;
		glm::vec3 traslation0;
		glm::vec4 scale0;
		glm::quat rotate0;

		float *traslationaux = new float[3];
		float *scaleaux = new float[4];
		float *rotateaux = new float[4];


		traslationaux[0] = traslationaux[1] = traslationaux[2] = 0.0f;
		traslation0[0] = traslation0[1] = traslation0[2] = 0.0f;

		scaleaux[0] = scaleaux[1] = scaleaux[2] = scaleaux[3] = 1.0f;
		scale0.x = scale0.y = scale0.z = scale0.w = 1.0f;
		
		rotateaux[0] = rotateaux[1] = rotateaux[2] = rotateaux[3] = 0.0f;
		rotate0.x = rotate0.y = rotate0.z = rotate0.w = 0.0f;
	
		models.push_back(obj);

		userInterface->setModelTranslation(traslationaux);
		userInterface->setModelScale(scaleaux);
		userInterface->setModelRotate(rotate0);

		models[picked]->setTranslation(traslation0);
		models[picked]->setScale(scale0);
		models[picked]->setRotate(rotate0);

		models[picked]->setModo(modoActual);
		models[picked]->setShading(shadeactual);
		models[picked]->calculateNormals();

		





	}
	else if (name.substr(name.find_last_of(".") + 1) == "off")
	{
		COff * off = new COff();
		if (!off->load(name))
			return;	
		picked++;
		glm::vec3 traslation0;
		glm::vec4 scale0;
		glm::quat rotate0;
			   		 	  
		float *traslationaux = new float[3];
		float *scaleaux = new float[4];
		float *rotateaux = new float[4];

		traslationaux[0] = traslationaux[1] = traslationaux[2] = 0.0f;
		traslation0[0] = traslation0[1] = traslation0[2] = 0.0f;
		scaleaux[0] = scaleaux[1] = scaleaux[2] = scaleaux[3] = 1.0f;
		scale0.x = scale0.y = scale0.z = scale0.w = 1.0f;
		rotateaux[0] = rotateaux[1] = rotateaux[2] = rotateaux[3] = 0.0f;
		rotate0.x = rotate0.y = rotate0.z = rotate0.w = 0.0f;
		models.push_back(off);
		userInterface->setModelTranslation(traslationaux);
		models[picked]->setTranslation(traslation0);
		userInterface->setModelScale(scaleaux);
		models[picked]->setScale(scale0);
		models[picked]->setModo(modoActual);
		models[picked]->setShading(shadeactual);
		models[picked]->calculateNormals();
	}
	totalmodels++;
	
}

void updateUserInterface()
{
	float * lightscolor1 = userInterface->getmLightColor();
	float * lightscolor2 = userInterface->getmLightColor2();
	float * lightscolor3 = userInterface->getmLightColor3();

	lightambient[0] = lightscolor1[0];
	lightambient[1] = lightscolor1[1];
	lightambient[2] = lightscolor1[2];
	lightambient[3] = lightscolor1[3];
	lightspecular[0] = lightscolor3[0];
	lightspecular[1] = lightscolor3[1];
	lightspecular[2] = lightscolor3[2];
	lightspecular[3] = lightscolor3[3];
	lightdiffuse[0] = lightscolor2[0];
	lightdiffuse[1] = lightscolor2[1];
	lightdiffuse[2] = lightscolor2[2];
	lightdiffuse[3] = lightscolor2[3];

	
	lights[0]->setMColor(lightambient[0], lightambient[1], lightambient[2], lightambient[3]);
	lights[1]->setMColor(lightambient[0], lightambient[1], lightambient[2], lightambient[3]);
	lights[0]->setMColor2(lightdiffuse[0], lightdiffuse[1], lightdiffuse[2], lightdiffuse[3]);
	lights[1]->setMColor2(lightdiffuse[0], lightdiffuse[1], lightdiffuse[2], lightdiffuse[3]);
	lights[0]->setMColor3(lightspecular[0], lightspecular[1], lightspecular[2], lightspecular[3]);
	lights[1]->setMColor3(lightspecular[0], lightspecular[1], lightspecular[2], lightspecular[3]);

	lights[0]->setTranslation(userInterface->getLight1Translation());
	lights[1]->setTranslation(userInterface->getLight2Translation());
	glm::vec3 lightpos1 = userInterface->getLight1Translation();
	glm::vec3 lightpos2 = userInterface->getLight2Translation();
	lightposition1[0] = lightpos1.x;
	lightposition1[1] = lightpos1.y;
	lightposition1[2] = lightpos1.z;
	lightposition2[0] = lightpos2.x;
	lightposition2[1] = lightpos2.y;
	lightposition2[2] = lightpos2.z;

	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightdiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightspecular);
	glLightfv(GL_LIGHT1, GL_AMBIENT, lightambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightdiffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightspecular);
	glLightfv(GL_LIGHT0, GL_POSITION, lightposition1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightposition2);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	if (picked > -1 && picked < models.size())
	{

		float * mBColor = userInterface->getmBColor();
		float * mMColor = userInterface->getmMColor();
		float * mMColor2 = userInterface->getmMColor2();
		float * mMColor3 = userInterface->getmMColor3();
		float * mNFColor = userInterface->getmNFColor();
		float * mNVColor = userInterface->getmNVColor();

		models[picked]->setBColor(mBColor[0], mBColor[1], mBColor[2]);
		models[picked]->setMColor(mMColor[0], mMColor[1], mMColor[2], mMColor[3]);
		models[picked]->setMColor2(mMColor2[0], mMColor2[1], mMColor2[2], mMColor2[3]);
		models[picked]->setMColor3(mMColor3[0], mMColor3[1], mMColor3[2], mMColor3[3]);
		models[picked]->setNFColor(mNFColor[0], mNFColor[1], mNFColor[2]);
		models[picked]->setNVColor(mNVColor[0], mNVColor[1], mNVColor[2]);

		float shininess = userInterface->getshininess();
		models[picked]->setshininess(shininess);
		models[picked]->setTranslation(userInterface->getModelTranslation());
		models[picked]->setScale(userInterface->getModelScale());
		glm::vec4 rotation = userInterface->getModelRotate();
		models[picked]->setRotate(glm::quat(rotation.w, rotation.x, rotation.y, rotation.z));
		models[picked]->setModo(modoActual);
		models[picked]->setShading(shadeactual);
	}
	else
	{
		picked = -1;
	}
}

void display(deploymentModes typeDeployment)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (showlights)
	{
		glEnable(GL_LIGHTING);
		//cout << "desplegando la luz \n";
		for (unsigned int i = 0; i < lights.size(); i++)
		{
			
			//
			glm::vec3 maxbboxL = lights[i]->boundingVertex(false);
			glm::vec3 minbboxL = lights[i]->boundingVertex(true);
			glm::vec3 translationL = lights[i]->getTranslation();
			//glColor3f(1.0f, 1.0f, 1.0f);
			float maxscaleL = max(max(abs(maxbboxL.x - minbboxL.x), abs(maxbboxL.y - minbboxL.y)), abs(maxbboxL.z - minbboxL.z));
			glPushMatrix();
				glTranslatef(translationL.x, translationL.y, translationL.z);
				glScalef(0.5f, 0.5f, 0.5f);
				glScalef(1.0f / maxscaleL, 1.0f / maxscaleL, 1.0f / maxscaleL);
				glTranslatef(-((maxbboxL.x + minbboxL.x) / 2), -((maxbboxL.y + minbboxL.y) / 2), -((maxbboxL.z + minbboxL.z) / 2));
				lights[i]->display(IMMEDIATE);
			glPopMatrix();

		}
		glDisable(GL_LIGHTING);
	}
	for (unsigned int i = 0; i < models.size(); i++)
	{
		if (showlights)
		{
			glEnable(GL_LIGHTING);
		}
		else
		{
			glDisable(GL_LIGHTING);
		}

		if (backFace)
		{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		}
		else
		{
		glDisable(GL_CULL_FACE);
		}

		/*if (zBuffer)
		{
		glEnable(GL_DEPTH_TEST);
		}
		else
		{
		glDisable(GL_DEPTH_TEST);
		}*/

		glm::vec3 maxbbox = models[i]->boundingVertex(false);
		glm::vec3 minbbox = models[i]->boundingVertex(true);
		glm::vec3 translation = models[i]->getTranslation();
		glm::vec4 scale = models[i]->getScale();
		glm::mat4 rotation = glm::mat4_cast(models[i]->getRotate());
		//models[i]->setModo(modoActual);
		float maxscale = max(max(abs(maxbbox.x - minbbox.x), abs(maxbbox.y - minbbox.y)), abs(maxbbox.z - minbbox.z));
		float matrot[4 * 4] = { rotation[0][0], rotation[0][1], rotation[0][2], rotation[0][3],
								rotation[1][0], rotation[1][1], rotation[1][2], rotation[1][3],
								rotation[2][0], rotation[2][1], rotation[2][2], rotation[2][3],
								rotation[3][0], rotation[3][1], rotation[3][2], rotation[3][3] };
		glPushMatrix();

			glTranslatef(translation.x, translation.y, translation.z);
			glScalef(scale.w, scale.w, scale.w);
			glScalef(scale.x, scale.y, scale.z);
			glMultMatrixf(matrot);

			glScalef(1.0f / maxscale, 1.0f / maxscale, 1.0f / maxscale);
			glTranslatef(-((maxbbox.x + minbbox.x) / 2), -((maxbbox.y + minbbox.y) / 2), -((maxbbox.z + minbbox.z) / 2));

			

			models[i]->display(typeDeployment);

			if (picked == i && showbbox)
			{
				models[i]->BoundingBox();
			}
			if (picked == i && shownormalsF)
			{
				models[i]->displayNormalsFace();
			}
			if (picked == i && shownormalsV)
			{
				models[i]->displayNormalsVertex();
			}

		glPopMatrix();
	}
		
}

void reshape(GLFWwindow *window, int width, int height)
{
	gWidth = width;
	gHeight = height;

	glViewport(0, 0, gWidth, gHeight);

	userInterface->reshape();

}

void keyInput(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (TwEventKeyGLFW(key, action))
		return;

	if (action == GLFW_PRESS)
	{
		switch (key)
		{
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(window, GL_TRUE);
				break;
		}
	}
}

void mouseButton(GLFWwindow* window, int button, int action, int mods)
{
	if (TwEventMouseButtonGLFW(button, action))
		return;
}

void cursorPos(GLFWwindow* window, double x, double y)
{
	if (TwEventMousePosGLFW(int(x), int(y)))
		return;
}

void charInput(GLFWwindow* window, unsigned int scanChar)
{
	if (TwEventCharGLFW(scanChar, GLFW_PRESS))
		return;
}

void destroy()
{
	for (unsigned int i = 0; i < models.size(); i++)
		delete models[i];

	delete userInterface;

	TwTerminate();
	glfwDestroyWindow(gWindow);
	glfwTerminate();
}

bool initGlfw()
{
	if (!glfwInit())
		return false;

	gWindow = glfwCreateWindow(gWidth, gHeight, "3d loader", NULL, NULL);

	if (!gWindow)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(gWindow);

	const GLFWvidmode * vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowPos(gWindow, (vidMode->width - gWidth) >> 1, (vidMode->height - gHeight) >> 1);

	glfwSetWindowSizeCallback(gWindow, reshape);
	glfwSetKeyCallback(gWindow, keyInput);
	glfwSetMouseButtonCallback(gWindow, mouseButton);
	glfwSetCursorPosCallback(gWindow, cursorPos);
	glfwSetCharCallback(gWindow, charInput);

	return true;
}

bool initUserInterface()
{
	if (!TwInit(TW_OPENGL, NULL))
		return false;

	userInterface = CUserInterface::Instance();

	return true;
}

/*bool initScene()
{
	CSOff* soff = new CSOff();
	string name = openfilename();

	if(!soff->load(name))
		return false;
	
	models.push_back(soff);

	return true;
}*/

int main(void)
{
	gWidth = 1200;
	gHeight = 800;
	picked = -1;
	

	if (!initGlfw() || /*!initScene() || */!initUserInterface())
		return EXIT_FAILURE;

	glLightfv(GL_LIGHT0, GL_AMBIENT, lightambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightdiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightspecular);
	glLightfv(GL_LIGHT1, GL_AMBIENT, lightambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightdiffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightspecular);
	glLightfv(GL_LIGHT0, GL_POSITION, lightposition1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightposition2);
	initLights();
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	reshape(gWindow, gWidth, gHeight);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(3.0f, 3.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	gluLookAt(0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);


	

	while (!glfwWindowShouldClose(gWindow))
	{

		deploymentActual = userInterface->getDeployment();
		pProject = userInterface->getProjection();
		backFace = userInterface->getBackFace();

		if (pProject == PERSPECTIVE)
		{
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(45.0f, (float)gWidth / (float)gHeight, 0.1f, 100.0f);
			glViewport(0, 0, gWidth, gHeight);
			glMatrixMode(GL_MODELVIEW);
		}
		else
		{
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(-(float)gWidth / 400.0f, (float)gWidth / 400.0f, -(float)gHeight / 400.0f, (float)gHeight / 400.0f, 0.1f, 100.0f);
			//glOrtho(-1, 1, -1, 1, 0.1f, 100.0f);
			glViewport(0, 0, gWidth, gHeight);
			glMatrixMode(GL_MODELVIEW);

		}

		/*if (backFace)
		{
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);

		}
		else
		{
			glDisable(GL_CULL_FACE);
		}

		if (zBuffer)
		{
			glEnable(GL_DEPTH_TEST);
		}
		else
		{
			glDisable(GL_DEPTH_TEST);
		}*/



		display(deploymentActual);

		TwDraw();
	
		updateUserInterface();
		
		glfwSwapBuffers(gWindow);

		glfwPollEvents();
	
	}

	destroy();


	return EXIT_SUCCESS;
}