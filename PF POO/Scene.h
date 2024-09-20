#ifndef __Escena
#define __Escena

#include <gl\GLU.h>
#include <gl\GL.h>
#include "SkyDome.h"
#include "Terrain.h"
#include "Model.h"
#include "Water.h"
#include "Billboard.h"
#include "Fog.h"
#include "Camera.h"

#define BILLSIZE 50

//BIENVENIDO AL ARCHIVO MAS IMPORTANTE DE TU PROYECTO

class Scene : public Camera
{
public:

	HWND hWnd = 0;

	short int skyIndex, lightIndex;
	float skyRotation;

	SkyDome* skyDome = new SkyDome(hWnd, 32, 32, 500, L"Imagenes//sky5.jpg");
	Terrain* terrain;
	Water* lago;
	GLfloat AmbMat[4] = { 255, 255, 220, 1 };

	EDXFramework::Model  *PC;

	Billboard *billBoard[BILLSIZE];
	

	Scene(HWND hWnd)
	{
		this->hWnd = hWnd;
		skyIndex = lightIndex, skyRotation = 0;
		
		GLfloat AmbPos[] = { 0, 400, 400, 1 };

		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glMaterialfv(GL_FRONT, GL_AMBIENT, AmbMat);
		glEnable(GL_NORMALIZE);
		glEnable(GL_LIGHT0);
		glLightfv(GL_LIGHT0, GL_POSITION, AmbPos);

		//lago = Pista, busca en sus constructores para poder crear un lago.
		//lago = new Water;
		lago = new Water(hWnd, L"Imagenes//terreno.bmp", L"Imagenes//water1.bmp", 50, 10);
		terrain = new Terrain(hWnd, L"Imagenes//terreno.bmp", L"Imagenes//test2.jpg", L"Imagenes//test2.jpg", 512, 512);
		PC = new EDXFramework::Model("Modelos//Laptop//laptop1.obj", "Modelos//Laptop//laptop.bmp", 1);

		Billboards(billBoard, hWnd);

		cameraInitialize();
	}

	void Billboards(Billboard *bills[], HWND hWnd)
	{
		//Aqui puedes crear algo util con un FOR quiza.
	}
	

	void render(HDC hDC)
	{
		skyRotation < 360 ? skyRotation +=0.1f : skyRotation = 0;

		glMaterialfv(GL_FRONT, GL_AMBIENT, AmbMat);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0, 0, 0, 0);
		glLoadIdentity();

		GLfloat AmbInt[] = { 0.1, 0.1, 0.1, 1 };
		glLightfv(GL_LIGHT0, GL_AMBIENT, AmbInt);
		py = terrain->Superficie(px, pz) * 4 + 6;

		cameraUpdate();

		//Skydome
		glPushMatrix();
			glTranslatef(0, 8, 0);
			glRotatef(skyRotation, 0, 1, 0);
			skyDome->Draw();
		glPopMatrix();

		//Terreno
		glPushMatrix();
			glScalef(1, 4, 1);
			terrain->Draw();
		glPopMatrix();

		glPushMatrix();
			glScalef(1, 6.8f, 1);
			lago->Draw();
		glPopMatrix();

		//PC
		glPushMatrix();
			glTranslatef(0, 35.0f, 50);			
			PC->Draw();
		glPopMatrix();

		


		glPushMatrix();
		for (int i = 0; i < BILLSIZE; i++)
			//Aqui puede ir algo en especial, en tu carpeta de HEADER_FILES, el primer archivo es la respuesta.
		glPopMatrix();


		SwapBuffers(hDC);
		
	}

	~Scene()
	{
		//NO OLVIDES PONER AQUI TODOS TUS PUNTEROS
		delete skyDome;
		delete lago;
		delete PC;
	}
};
#endif
