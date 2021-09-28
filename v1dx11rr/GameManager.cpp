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
}

void GameManager::unloadModels() {
	
}

void GameManager::drawModels() {
	model->Draw(camaraGM->vista, camaraGM->proyeccion, terrenoGM->Superficie(model->getPosX(), model->getPosZ()) + 10, camaraGM->posCam, 10, 0, 'Y', 1);
	
}

float GameManager::camaraOffsetY(bool isFirstPerson) {
	if (isFirstPerson)
		return 15;
	else
		return 20;
}

D3DXVECTOR3 GameManager::camaraOffset(bool isFirstPerson) {
	D3DXVECTOR3 pos;
	if (isFirstPerson) {
		pos.x = camaraGM->posCam.x;
		pos.y = camaraGM->posCam.y;
		pos.z = camaraGM->posCam.z;
	}
	else {
		pos.x = camaraGM->posCam.x - 5;
		pos.y = camaraGM->posCam.y;
		pos.z = camaraGM->posCam.z - 5;
	}
	return pos;
}