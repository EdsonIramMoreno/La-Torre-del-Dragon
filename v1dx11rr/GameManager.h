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
#include "Billboard.h"
#include "Camara.h"
#include"TerrenoRR.h"

using namespace std;

enum Modelos { Torre, Puente, Lampara, Fogata,
				Bote, Barriles
};

class GameManager{
private:
	static GameManager* instance;
	GameManager();
	Camara* camaraGM;
	TerrenoRR* terrenoGM;

	ModeloRR* Models[6];

	BillboardRR* fire;

	int frameFire;

	vector2 uv1[32], uv2[32], uv3[32], uv4[32];

	void billCargaFuego();

public:
	void getCamaraGM(Camara*);

	void getTerrenoGM(TerrenoRR*);

	static GameManager* getInstance();

	void loadModels(ID3D11Device*, ID3D11DeviceContext*);

	void loadBillboards(ID3D11Device*, ID3D11DeviceContext*);

	void unloadModels();

	void drawModels();

	void drawBillboards();

	void setFrames();

	float camaraOffsetY(bool);

	void GetDesktopResolution(int&, int&);

	bool detectCollision(ModeloRR*);
};


#endif
