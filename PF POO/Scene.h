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
int index = 0;

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
	EDXFramework::Model* cerca;
	EDXFramework::Model* trampa;
	EDXFramework::Model* ficha;
	EDXFramework::Model* pino;
	EDXFramework::Model* maizal;
	EDXFramework::Model* queso;
	EDXFramework::Model* reloj;
	EDXFramework::Model* piedra;
	EDXFramework::Model* telarana;
	EDXFramework::Model* deco;
	EDXFramework::Model* vaca;
	EDXFramework::Model* gato;

	EDXFramework::Model* orilla[2];
	EDXFramework::Model* Arana[7];

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
		cerca = new EDXFramework::Model("Modelos//cerca//cerca.obj", "Modelos//textures//Image_0.bmp", 1);
		trampa = new EDXFramework::Model("Modelos//trampa//trampa.obj", "Modelos//trampa//Image_1.bmp", 1);
		ficha = new EDXFramework::Model("Modelos//ficha//ficha.obj", "Modelos//ficha//Image_2.bmp", 1);
		pino = new EDXFramework::Model("Modelos//pino//pinos.obj", "Modelos//textures//Image_0.bmp", 1);
		maizal= new EDXFramework::Model("Modelos//pino//maiz.obj", "Modelos//textures//Image_0.bmp", 1);
		queso = new EDXFramework::Model("Modelos//queso//queso.obj", "Modelos//queso//Image_3.bmp", 1);
		reloj = new EDXFramework::Model("Modelos//reloj//clock.obj", "Modelos//reloj//Image_4.bmp", 1);
		piedra = new EDXFramework::Model("Modelos//roca//piedras.obj", "Modelos//textures//Image_0.bmp", 1);
		telarana = new EDXFramework::Model("Modelos//telaraña//web.obj", "Modelos//telaraña//webtext.bmp", 1);
		deco = new EDXFramework::Model("Modelos//espanta//espantapajaros.obj", "Modelos//textures//Image_0.bmp", 1);
		vaca = new EDXFramework::Model("Modelos//vaca//vaca.obj", "Modelos//textures//Image_0.bmp", 1);
		gato = new EDXFramework::Model("Modelos//gato//gato.obj", "Modelos//gato//Image_0.bmp", 1);

		/*orilla[0] = new EDXFramework::Model("Modelos//bridge//puertos.obj", "Modelos//textures//Image_0.bmp", 1);
		orilla[1] = new EDXFramework::Model("Modelos//bridge//puertos.obj", "Modelos//textures//Image_0.bmp", 1);*/

		Arana[0] = new EDXFramework::Model("Modelos//arana//attack1.obj", "Modelos//arana//Image_2.bmp", 1);
		Arana[1] = new EDXFramework::Model("Modelos//arana//attack2.obj", "Modelos//arana//Image_2.bmp", 1);
		Arana[2] = new EDXFramework::Model("Modelos//arana//attack3.obj", "Modelos//arana//Image_2.bmp", 1);
		Arana[3] = new EDXFramework::Model("Modelos//arana//attack4.obj", "Modelos//arana//Image_2.bmp", 1);
		Arana[4] = new EDXFramework::Model("Modelos//arana//attack5.obj", "Modelos//arana//Image_2.bmp", 1);
		Arana[5] = new EDXFramework::Model("Modelos//arana//attack6.obj", "Modelos//arana//Image_2.bmp", 1);
		Arana[6] = new EDXFramework::Model("Modelos//arana//attack7.obj", "Modelos//arana//Image_2.bmp", 1);
		Arana[7] = new EDXFramework::Model("Modelos//arana//attack8.obj", "Modelos//arana//Image_2.bmp", 1);



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
			glScalef(1, 6.6f, 1);
			lago->Draw();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0, 35.0f, 50);			
			PC->Draw();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(2.7f, 16, -27);
			glScalef(6, 6, 6);
			trampa->Draw();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(2.7f, 16, -20);
			glScalef(0.01, 0.01, 0.01);
			ficha->Draw();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(15.0f, 22, -60);
			glScalef(3, 3, 3);
			pino->Draw();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-42, 16, -24);
			//glScalef(0.01, 0.01, 0.01);
			maizal->Draw();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-42, 16, -5);
			queso->Draw();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-42, 16, -7);
			glScalef(6, 6, 6);
			reloj->Draw();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-22, 15, 12);
			//glScalef(6, 6, 6);
			piedra->Draw();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-42, 20, -10);
			telarana->Draw();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-52, 19, -26);
			glScalef(2, 2, 2);
			//glRotated(175, 0, 1, 0);
			deco->Draw();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(-33, 19, 13);
			glScalef(5, 5, 5);
			vaca->Draw();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(9, 16, -22);
			glScalef(0.009, 0.009, 0.009);
			gato->Draw();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(2, 15.0f, 6);
			glRotatef(-90, 0, 1, 0);
			cerca->Draw();
		glPopMatrix();

		//glPushMatrix();
		//	glTranslatef(2, 15.0f, 6);
		//orilla[0]->Draw();
		//glPopMatrix();
		//glPushMatrix();
		//	glTranslatef(-10.4f, 6, 26.9f);
		//orilla[1]->Draw();
		//glPopMatrix();

		glPushMatrix();
			if (index < 8) {
				glTranslatef(2, 15, 5);
				Arana[index]->Draw();
				index++;
			if (index == 7)index = 0;
}
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
		delete cerca;
		delete trampa;
		delete ficha;
		delete maizal;
		delete pino;
		delete queso;
		delete reloj;
		delete piedra;
		delete telarana;
		delete deco;
		delete vaca;
		delete gato;
		for (int i = 0; i < 8; i++) {
			delete Arana[i];
		}
	}
};
#endif
