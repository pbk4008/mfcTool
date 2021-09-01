#pragma once
#ifndef __TERRAIN_H__
#define __TERRAIN_H__

class Terrain final
{
private:
	Terrain();
public:
	~Terrain();

public:
public:
	void AddTileData(TILE* pTile);
	HRESULT ReadyTerrain();
	void RenderTerrain();
	void ReleaseTerrain();

	static Terrain* Create();
private:
	vector<TILE*> mVecTile;
};

#endif // !__TERRAIN_H__