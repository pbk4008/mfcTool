#include "stdafx.h"
#include "Terrain.h"


Terrain::Terrain()
{
}


Terrain::~Terrain()
{
	ReleaseTerrain();
}

void Terrain::AddTileData(TILE * pTile)
{
	mVecTile.emplace_back(pTile);
}

HRESULT Terrain::ReadyTerrain()
{
	mVecTile.reserve(TILEX * TILEY);
	TILE* pTile = nullptr;

	for (int i = 0; i < TILEY; i++) {
		for (int j = 0; j < TILEX; j++) {
			pTile = new TILE;
			float fY = (TILECY >> 1) * i;
			float fX = (TILECX >> 1) * j;
			pTile->vPos = { fX, fY, 0.f };
			pTile->vSize = { 1.f , 1.f , 1.f };
			mVecTile.emplace_back(pTile);
		}
	}
	return S_OK;
}

void Terrain::RenderTerrain()
{
	
	int size = mVecTile.size();
	float fY = (TILECY >> 1);
	float fX = (TILECX >> 1);

	for (int i = 0; i < size; i++) 
	{
		TILE* temp = mVecTile[i];
		
		D3DXVECTOR2 vLine[4] = {
			{ temp->vPos.x - fX, temp->vPos.y - fY },
			{ temp->vPos.x + fX, temp->vPos.y - fY },
			{ temp->vPos.x + fX, temp->vPos.y + fY },
			{ temp->vPos.x - fX, temp->vPos.y + fY } 
		};

		CGraphicDevice::getInstance()->getLine()->Draw(vLine, 4, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void Terrain::ReleaseTerrain()
{
	for_each(mVecTile.begin(), mVecTile.end(), Safe_Delete<TILE*>);
	mVecTile.clear();
	mVecTile.swap(vector<TILE*>());
}

Terrain * Terrain::Create()
{
	Terrain* pInstance = new Terrain;
	if (FAILED(pInstance->ReadyTerrain()))
		Safe_Delete(pInstance);

	return pInstance;
}
