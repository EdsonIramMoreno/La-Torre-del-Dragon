#include "Player.h"

Player::Player(ID3D11Device* d3dDevice, ID3D11DeviceContext* _ID3D11DeviceContext) {
	this->playerModelF = ModeloRR::Builder().setD3DDevice(d3dDevice)->
		setDD3DContext(_ID3D11DeviceContext)->
		setModelPath("Assets/Caballo/caballo.obj")->
		setcolorTexturePath(L"Assets/Caballo/caballobayoText.jpg")->
		setspecularTexturePath(L"Assets/Caballo/caballobayoSpecular.jpg")->
		setPosX(0)->setPosZ(0)->Build();
	this->playerModelT = ModeloRR::Builder().setD3DDevice(d3dDevice)->
		setDD3DContext(_ID3D11DeviceContext)->
		setModelPath("Assets/Caballo3erPersona/Caballo3eraPersona.obj")->
		setcolorTexturePath(L"Assets/Caballo3erPersona/caballobayoText.jpg")->
		setspecularTexturePath(L"Assets/Caballo3erPersona/caballobayoSpecular.jpg")->
		setPosX(0)->setPosZ(0)->Build();
	this->firstPerson = true;
	this->rotation = 0;
}

bool Player::isFirstPerson(){
	return this->firstPerson;
}

void Player::setFirstPerson() {
	if (firstPerson) {
		this->firstPerson = false;
		return;
	}
	else {
		this->firstPerson = true;
		return;
	}
}

void Player::setPositions(D3DXVECTOR3 camara) {
	this->playerModelF->setPosX(camara.x);
	this->playerModelF->setPosZ(camara.z);
	this->playerModelT->setPosX(camara.x);
	this->playerModelT->setPosZ(camara.z);
}

void Player::setRotation(float rotation) {
	this->rotation = rotation;
}

float Player::getRotation() {
	return this->rotation;
}