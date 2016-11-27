#include "Background.h"
Background::Background()
{

}
void Background::InitCoordinates()
{
	_CoorTile = new D3DXVECTOR3 *[w_sizex];
	for (int i = 0; i < w_sizex; ++i)
		_CoorTile[i] = new D3DXVECTOR3[w_sizey];
	// Lấy tọa độ mỗi tile
	for (int x = 0; x < w_sizex; x++)
	{
		for (int y = 0; y <w_sizey; y++)
		{

			_CoorTile[x][y].x = y*tile_sizex;
			_CoorTile[x][y].y = x*tile_sizey;
			_CoorTile[x][y].z = 0;

		}
	}
}

Background::~Background()
{
}

void Background::Init(LPDIRECT3DTEXTURE9 _texture,char* _pathname){
	FILE *file;
	file = fopen(_pathname, "r");
	if (!fscanf(file, "%d", &total));
	if (!fscanf(file, "%d" "%d", &tile_sizex, &tile_sizey));
	if (!fscanf(file, "%d" "%d", &widthtile, &heighttile));
	if (!fscanf(file, "%d" "%d", &w_sizey, &w_sizex));
	map = new int*[w_sizex];
	for (int i = 0; i < w_sizex; i++)
		map[i] = new int[w_sizey];
	for (int i = 0; i < w_sizex; i++)
	{
		for (int j = 0; j <w_sizey; j++)
		{

			if (!fscanf(file, "%d", &map[i][j]))
				break;
		}
	}
	fclose(file);
	m_texture = _texture;
	
	InitCoordinates();
}
void Background::Draw(LPD3DXSPRITE _spriteHandler, D3DXVECTOR2 pos_c, int _lobeginx, int _loendx, int _lobeginy, int _loendy)
{
	CCamera *a = new CCamera();
	D3DXMATRIX Scale;
	D3DXMatrixIdentity(&Scale); 
	D3DXMatrixTransformation2D(&Scale, &D3DXVECTOR2(0, 0), 0.0f, &D3DXVECTOR2(1.0f, -1.0f), NULL, 0.f, NULL);
	D3DXMatrixMultiply(&Scale, &Scale, &a->Get_ViewPort());
	_spriteHandler->SetTransform(&Scale);
	RECT rect;
	int x_tile = 0;
	int y_tile = 0;
	int minRange = pos_c.x / tile_sizex + _lobeginx;
	int maxRange = minRange + SCREEN_WIDTH / tile_sizex + 2;
	int _dy = _loendy - _lobeginy;
	int maxRangeHer = _loendy;
	int minRangeHer = maxRangeHer - _dy+1;
		int c = 0, d = 0;
		for (int x = minRangeHer; x < maxRangeHer; x++)
		{
			for (int y = minRange; y < maxRange; y++)
			{
          		x_tile = (map[x][y] % (tile_sizex));
				y_tile = (map[x][y] / (tile_sizey));
				rect = { x_tile * tile_sizex, y_tile * tile_sizey, (x_tile + 1) * tile_sizex, (y_tile + 1) * tile_sizey };
				_spriteHandler->Draw(m_texture, &rect, NULL, &_CoorTile[c][d], D3DCOLOR_XRGB(255, 255, 255));
				if (d <= (SCREEN_WIDTH / tile_sizex)){
					d++;
				}
				else{
					d = 0;
				}
			}
			if (c < SCREEN_HEIGHT / tile_sizex){
				c++;
			}
			else{
				c = 0;
			}
	}
}

