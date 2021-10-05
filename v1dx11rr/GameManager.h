#ifndef _GameManager
#define _GameManager
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
#include "Camara.h"
#include"TerrenoRR.h"

using namespace std;

class GameManager{
private:
	static GameManager* instance;
	GameManager();
	Camara* camaraGM;
	TerrenoRR* terrenoGM;
	ModeloRR* model;
	ModeloRR* Torre;
	ModeloRR* Puente;
	ModeloRR* Lampara;

	ModeloRR* Fogata;
	ModeloRR* Bote;
	ModeloRR* Barriles;



public:
	void getCamaraGM(Camara*);

	void getTerrenoGM(TerrenoRR*);

	static GameManager* getInstance();

	void loadModels(ID3D11Device*, ID3D11DeviceContext*);

	void unloadModels();

	void drawModels();

	float camaraOffsetY(bool);

	D3DXVECTOR3 camaraOffset(bool);

};


#endif
