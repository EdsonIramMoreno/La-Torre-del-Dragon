#ifndef _Player
#define _Player
#include "ModeloRR.h"
#include "loadModel.h"
#include <d3d11.h>
#include <d3dx11.h>
#include <DxErr.h>
#include <D3Dcompiler.h>
#include <d3dx10math.h>
#include <conio.h>
#include <vector>
#include <iostream>

class Player{
	bool firstPerson;
	float rotation;
public:
	ModeloRR* playerModelF;
	ModeloRR* playerModelT;
	Player(ID3D11Device* _ID3D11Device, ID3D11DeviceContext* _ID3D11DeviceContext);
	bool isFirstPerson();
	void setFirstPerson();
	void setPositions(D3DXVECTOR3);
	void setRotation(float);
	float getRotation();
};

#endif