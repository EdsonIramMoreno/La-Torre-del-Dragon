#include"GameManager.h"
#include <iostream>
#include "Player.h"
#include "loadModel.h"
#include <d3d11.h>
#include <d3dx11.h>
#include <DxErr.h>
#include <D3Dcompiler.h>
#include <d3dx10math.h>
#include <conio.h>
#include <vector>
#include <iostream>

GameManager* GameManager::instance = 0;

GameManager::GameManager() {

}

GameManager* GameManager::getInstance() {
	if (instance == NULL)
		instance = new GameManager();
	return instance;
}

void GameManager::getCamaraGM(Camara* camaraGM) {
	this->camaraGM = camaraGM;
}

void GameManager::getTerrenoGM(TerrenoRR* terrenoGM) {
	this->terrenoGM = terrenoGM;
}

void GameManager::loadModels(ID3D11Device* d3dDevice, ID3D11DeviceContext* _ID3D11DeviceContext) {
	Models[Torre] = ModeloRR::Builder().setD3DDevice(d3dDevice)->
		setDD3DContext(_ID3D11DeviceContext)->
		setModelPath("Assets/Torre/Torre.obj")->
		setcolorTexturePath(L"Assets/Torre/Kickelhahn_C.png")->
		setspecularTexturePath(L"Assets/Torre/SpecularMap.png")->
		setPosX(0)->setPosZ(0)->setTypeOfCollision(1)->setXWith(10)->setZHeight(10)->Build();
	Models[Puente] = ModeloRR::Builder().setD3DDevice(d3dDevice)->
		setDD3DContext(_ID3D11DeviceContext)->
		setModelPath("Assets/Puente/Puente.obj")->
		setcolorTexturePath(L"Assets/Puente/Most_texture_None_color.png")->
		setspecularTexturePath(L"Assets/Puente/SpecularMap.png")->
		setPosX(100)->setPosZ(100)->setTypeOfCollision(1)->setXWith(10)->setZHeight(10)->Build();
	Models[Lampara] = ModeloRR::Builder().setD3DDevice(d3dDevice)->
		setDD3DContext(_ID3D11DeviceContext)->
		setModelPath("Assets/Lampara/Lampara.obj")->
		setcolorTexturePath(L"Assets/Lampara/DiffuseColor.png")->
		setspecularTexturePath(L"Assets/Lampara/Lamp_Post_Spec.png")->
		setPosX(-92)->setPosZ(-16)->setTypeOfCollision(1)->setXWith(10)->setZHeight(10)->Build();
	Models[Fogata] = ModeloRR::Builder().setD3DDevice(d3dDevice)->
		setDD3DContext(_ID3D11DeviceContext)->
		setModelPath("Assets/Fogata/Fogata.obj")->
		setcolorTexturePath(L"Assets/Fogata/campfire_base.png")->
		setspecularTexturePath(L"Assets/Fogata/SpecularMap.png")->
		setPosX(133)->setPosZ(-133)->setTypeOfCollision(1)->setXWith(10)->setZHeight(10)->Build();
	Models[Bote] = ModeloRR::Builder().setD3DDevice(d3dDevice)->
		setDD3DContext(_ID3D11DeviceContext)->
		setModelPath("Assets/Bote/bote.obj")->
		setcolorTexturePath(L"Assets/Bote/boatColor.png")->
		setspecularTexturePath(L"Assets/Bote/SpecularMap.png")->
		setPosX(-24)->setPosZ(-89)->setTypeOfCollision(1)->setXWith(10)->setZHeight(10)->Build();
	Models[Barriles] = ModeloRR::Builder().setD3DDevice(d3dDevice)->
		 setDD3DContext(_ID3D11DeviceContext)->
		 setModelPath("Assets/Barriles/Barriles.obj")->
		 setcolorTexturePath(L"Assets/Barriles/wooden_barrel_albedo_25.png")->
		 setspecularTexturePath(L"Assets/Barriles/wooden_barrel_specular_25.png")->
		 setPosX(28)->setPosZ(-130)->setTypeOfCollision(1)->setXWith(10)->setZHeight(10)->Build();
}

void GameManager::drawModels() {
	Models[Torre]->Draw(camaraGM->vista, camaraGM->proyeccion, terrenoGM->Superficie(30, 0), camaraGM->posCam, 10.0f, 0, 'X', 0.06);
	Models[Puente]->Draw(camaraGM->vista, camaraGM->proyeccion, terrenoGM->Superficie(0, 0), camaraGM->posCam, 10.0f, 0, 'X', 5);
	Models[Lampara]->Draw(camaraGM->vista, camaraGM->proyeccion, terrenoGM->Superficie(-10, 0), camaraGM->posCam, 10.0f, 0, 'X', 1.5);
	Models[Fogata]->Draw(camaraGM->vista, camaraGM->proyeccion, terrenoGM->Superficie(-20, 0), camaraGM->posCam, 10.0f, 0, 'X', 0.5);
	Models[Bote]->Draw(camaraGM->vista, camaraGM->proyeccion, terrenoGM->Superficie(0, 0), camaraGM->posCam, 10.0f, 0, 'X', 0.5);
	Models[Barriles]->Draw(camaraGM->vista, camaraGM->proyeccion, terrenoGM->Superficie(0, 0), camaraGM->posCam, 10.0f, 0, 'X', 0.5);
}

void GameManager::loadBillboards(ID3D11Device* d3dDevice, ID3D11DeviceContext* _ID3D11DeviceContext) {
	billCargaFuego();
	frameFire = 0;
	fire = BillboardRR::Builder().setD3DDevice(d3dDevice)->
		setDD3DContext(_ID3D11DeviceContext)->
		setBillboard(L"Assets/Billboards/fuego-anim.png")->
		setNormalMap(L"Assets/Billboards/fuego-anim-normal.png")->
		setEscala(5)->setPosX(-11)->setPosZ(-78)->Build();
}

void GameManager::drawBillboards(){
	fire->Draw(camaraGM->vista, camaraGM->proyeccion, camaraGM->posCam, 
		fire->getPosX(), fire->getPosZ(), fire->getEscala(), 
		terrenoGM->Superficie(fire->getPosX(), fire->getPosZ()) + 5, uv1, uv2, uv3, uv4, frameFire);
}

void GameManager::setFrames() {
	frameFire++;
	if (frameFire == 32)
		frameFire = 0;
}

void GameManager::unloadModels() {
	
}

float GameManager::camaraOffsetY(bool isFirstPerson) {
	if (isFirstPerson)
		return 20;
	else
		return 25;
}

void GameManager::GetDesktopResolution(int& horizontal, int& vertical){
	RECT desktop;
	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);
	// The top left corner will have coordinates (0,0)
	// and the bottom right corner will have coordinates
	// (horizontal, vertical)
	horizontal = desktop.right;
	vertical = desktop.bottom;

	//used as constructor
	angleSkyDome = 0;
}

bool GameManager::detectCollision(ModeloRR* player) {
	bool collided = false;
	for (ModeloRR* modelo : Models){
		if (player->getTypeOfCollision() == 1) {
			if (modelo->getTypeOfCollision() == 0)
				collided = modelo->collision.squareCollision.collisionSS(player->collision);
			else if (modelo->getTypeOfCollision() == 1)
				collided = modelo->collision.circleCollision.collisionCS(player->collision);
		}
		if (collided)
			break;
	}
	return collided;
}

void GameManager::setAngleSkydome() {
	angleSkyDome += 0.0005;
	if (angleSkyDome >= 360) 
		angleSkyDome = 0.0f;
}

float GameManager::getAngleSkydome() {
	return this->angleSkyDome;
}

void GameManager::billCargaFuego() {
	uv1[0].u = .125;
	uv2[0].u = .125;
	uv3[0].u = 0;
	uv4[0].u = 0;

	uv1[0].v = .25;
	uv2[0].v = 0;
	uv3[0].v = 0;
	uv4[0].v = .25;


	for (int j = 0; j < 8; j++) {
		uv1[j].u = uv1[0].u + (j * .125);
		uv2[j].u = uv2[0].u + (j * .125);
		uv3[j].u = uv3[0].u + (j * .125);
		uv4[j].u = uv4[0].u + (j * .125);

		uv1[j].v = .25;
		uv2[j].v = 0;
		uv3[j].v = 0;
		uv4[j].v = .25;
	}
	for (int j = 0; j < 8; j++) {
		uv1[j + 8].u = uv1[0].u + (j * .125);
		uv2[j + 8].u = uv2[0].u + (j * .125);
		uv3[j + 8].u = uv3[0].u + (j * .125);
		uv4[j + 8].u = uv4[0].u + (j * .125);

		uv1[j + 8].v = .5;
		uv2[j + 8].v = .25;
		uv3[j + 8].v = .25;
		uv4[j + 8].v = .5;
	}

	for (int j = 0; j < 8; j++) {
		uv1[j + 16].u = uv1[0].u + (j * .125);
		uv2[j + 16].u = uv2[0].u + (j * .125);
		uv3[j + 16].u = uv3[0].u + (j * .125);
		uv4[j + 16].u = uv4[0].u + (j * .125);

		uv1[j + 16].v = .75;
		uv2[j + 16].v = .5;
		uv3[j + 16].v = .5;
		uv4[j + 16].v = .75;
	}

	for (int j = 0; j < 8; j++) {
		uv1[j + 24].u = uv1[0].u + (j * .125);
		uv2[j + 24].u = uv2[0].u + (j * .125);
		uv3[j + 24].u = uv3[0].u + (j * .125);
		uv4[j + 24].u = uv4[0].u + (j * .125);

		uv1[j + 24].v = 1;
		uv2[j + 24].v = .75;
		uv3[j + 24].v = .75;
		uv4[j + 24].v = 1;
	}
}