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
	model = ModeloRR::Builder().setD3DDevice(d3dDevice)->
		setDD3DContext(_ID3D11DeviceContext)->
		setModelPath("Assets/Cofre/Cofre.obj")->
		setcolorTexturePath(L"Assets/Cofre/Cofre-color.png")->
		setspecularTexturePath(L"Assets/Cofre/Cofre-spec.png")->
		setPosX(0)->setPosZ(0)->Build();
	Torre = ModeloRR::Builder().setD3DDevice(d3dDevice)->
		setDD3DContext(_ID3D11DeviceContext)->
		setModelPath("Assets/Torre/Torre.obj")->
		setcolorTexturePath(L"Assets/Torre/Kickelhahn_C.png")->
		setspecularTexturePath(L"Assets/Torre/SpecularMap.png")->
		setPosX(0)->setPosZ(0)->Build();
	Puente= ModeloRR::Builder().setD3DDevice(d3dDevice)->
		setDD3DContext(_ID3D11DeviceContext)->
		setModelPath("Assets/Puente/Puente.obj")->
		setcolorTexturePath(L"Assets/Puente/Most_texture_None_color.png")->
		setspecularTexturePath(L"Assets/Puente/SpecularMap.png")->
		setPosX(100)->setPosZ(100)->Build();

	Lampara = ModeloRR::Builder().setD3DDevice(d3dDevice)->
		setDD3DContext(_ID3D11DeviceContext)->
		setModelPath("Assets/Lampara/Lampara.obj")->
		setcolorTexturePath(L"Assets/Lampara/DiffuseColor.png")->
		setspecularTexturePath(L"Assets/Lampara/Lamp_Post_Spec.png")->
		setPosX(-92)->setPosZ(-16)->Build();
	Fogata = ModeloRR::Builder().setD3DDevice(d3dDevice)->
		setDD3DContext(_ID3D11DeviceContext)->
		setModelPath("Assets/Fogata/Fogata.obj")->
		setcolorTexturePath(L"Assets/Fogata/campfire_base.png")->
		setspecularTexturePath(L"Assets/Fogata/SpecularMap.png")->
		setPosX(133)->setPosZ(-133)->Build();
	 Bote = ModeloRR::Builder().setD3DDevice(d3dDevice)->
		setDD3DContext(_ID3D11DeviceContext)->
		setModelPath("Assets/Bote/bote.obj")->
		setcolorTexturePath(L"Assets/Bote/boatColor.png")->
		setspecularTexturePath(L"Assets/Bote/SpecularMap.png")->
		setPosX(-24)->setPosZ(-89)->Build();

	 Barriles = ModeloRR::Builder().setD3DDevice(d3dDevice)->
		 setDD3DContext(_ID3D11DeviceContext)->
		 setModelPath("Assets/Barriles/Barriles.obj")->
		 setcolorTexturePath(L"Assets/Barriles/wooden_barrel_albedo_25.png")->
		 setspecularTexturePath(L"Assets/Barriles/wooden_barrel_specular_25.png")->
		 setPosX(28)->setPosZ(-130)->Build();
}

void GameManager::unloadModels() {
	
}

void GameManager::drawModels() {
	model->Draw(camaraGM->vista, camaraGM->proyeccion, terrenoGM->Superficie(model->getPosX(), model->getPosZ()) + 10, camaraGM->posCam, 10, 0, 'Y', 1);
	Torre->Draw(camaraGM->vista, camaraGM->proyeccion, terrenoGM->Superficie(30,0), camaraGM->posCam, 10.0f, 0, 'X', 0.06);
	Puente->Draw(camaraGM->vista, camaraGM->proyeccion, terrenoGM->Superficie(0, 0), camaraGM->posCam, 10.0f, 0, 'X', 5);
	Lampara->Draw(camaraGM->vista, camaraGM->proyeccion, terrenoGM->Superficie(-10, 0), camaraGM->posCam, 10.0f, 0, 'X', 1.5);
	Fogata->Draw(camaraGM->vista, camaraGM->proyeccion, terrenoGM->Superficie(-20, 0), camaraGM->posCam, 10.0f, 0, 'X', 0.5);
	Bote->Draw(camaraGM->vista, camaraGM->proyeccion, terrenoGM->Superficie(0, 0), camaraGM->posCam, 10.0f, 0, 'X', 0.5);
	Barriles->Draw(camaraGM->vista, camaraGM->proyeccion, terrenoGM->Superficie(0, 0), camaraGM->posCam, 10.0f, 0, 'X', 0.5);

}

float GameManager::camaraOffsetY(bool isFirstPerson) {
	if (isFirstPerson)
		return 15;
	else
		return 20;
}

D3DXVECTOR3 GameManager::camaraOffset(bool isFirstPerson) {
	D3DXVECTOR3 pos = camaraGM->posCam;
	float x = 0, z = 0;
	if (!isFirstPerson) {
		x = (pos.x + (pos.x + 15)) / 2;
		z = (pos.z + (pos.z + 15)) / 2;
		pos.x = x;
		pos.z = z;
		pos.y = 0;
		return pos;
	}
	return camaraGM->posCam;
}