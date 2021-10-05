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

void GameManager::unloadModels() {
	
}

void GameManager::drawModels() {
	Models[Torre]->Draw(camaraGM->vista, camaraGM->proyeccion, terrenoGM->Superficie(30,0), camaraGM->posCam, 10.0f, 0, 'X', 0.06);
	Models[Puente]->Draw(camaraGM->vista, camaraGM->proyeccion, terrenoGM->Superficie(0, 0), camaraGM->posCam, 10.0f, 0, 'X', 5);
	Models[Lampara]->Draw(camaraGM->vista, camaraGM->proyeccion, terrenoGM->Superficie(-10, 0), camaraGM->posCam, 10.0f, 0, 'X', 1.5);
	Models[Fogata]->Draw(camaraGM->vista, camaraGM->proyeccion, terrenoGM->Superficie(-20, 0), camaraGM->posCam, 10.0f, 0, 'X', 0.5);
	Models[Bote]->Draw(camaraGM->vista, camaraGM->proyeccion, terrenoGM->Superficie(0, 0), camaraGM->posCam, 10.0f, 0, 'X', 0.5);
	Models[Barriles]->Draw(camaraGM->vista, camaraGM->proyeccion, terrenoGM->Superficie(0, 0), camaraGM->posCam, 10.0f, 0, 'X', 0.5);
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