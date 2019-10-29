#include "chunk.h"

Chunk::Chunk(int nx, int nz) : m_blocks(CHUNK_SIZE_X, CHUNK_SIZE_Y, CHUNK_SIZE_Z)
{
	m_positionChunk.x = nx;
	m_positionChunk.z = nz;
	for (int x = 0; x < CHUNK_SIZE_X; ++x) 
	{ 
		for (int z = 0; z < CHUNK_SIZE_Z; ++z) 
		{ 
			for (int y = 0; y < 1; ++y)
			{
				SetBloc(x, y, z, BTYPE_DIRT); 
			} 
		} 
	}
	Size.x = CHUNK_SIZE_X;
	Size.y = CHUNK_SIZE_Y;
	Size.z = CHUNK_SIZE_Z;
	DrawPlayGround();
	m_isDirty = true;
}
void Chunk::Render() const
{
	m_chunkMesh.Render();
}
bool Chunk::IsDirty() const
{
	return m_isDirty;
}
void Chunk::Update(Array2d<BlockInfo>* blockInfo) { 
	// Update mesh 
	if(m_isDirty) 
	{ 
		int maxVertexCount = (CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z) * (6 * 4); 
		ChunkMesh::VertexData* vd = new ChunkMesh::VertexData[maxVertexCount]; 
		int count = 0;
		for (int x = 0; x < CHUNK_SIZE_X; ++x) 
		{
			for (int z = 0; z < CHUNK_SIZE_Z; ++z) 
			{
				for (int y = 0; y < CHUNK_SIZE_Y; ++y) 
				{
					if (count > USHRT_MAX) 
						break;
					BlockType bt = GetBloc(x, y, z);
					if (bt != BTYPE_AIR) 
					{
						int faceMask = IsVisible(x, y, z);
						if (faceMask)
						{
							BlockInfo bi = blockInfo->Get(bt % 4, bt / 4);
							AddBlockToMesh(vd, count, bt, x + m_positionChunk.x, y, z + m_positionChunk.z, bi.m_texCoordX, bi.m_texCoordY, bi.m_largeur, faceMask);
						}
					}
				}
			}
		}
		if (count > USHRT_MAX) 
		{ 
			count = USHRT_MAX; 
			std::cout << "[Chunk::Update] Chunk data truncaned , too much vertices to have a 16bit index" << std::endl; 
		}
		m_chunkMesh.SetMeshData(vd, count); delete[] vd;
	}
	m_isDirty = false;
}

void Chunk::AddBlockToMesh(ChunkMesh::VertexData* vd, int& count, BlockType bt, int x, int y, int z, float u, float v, float w, unsigned int BlocDisplayed) 
{	
	if (BlocDisplayed & 1)
	{
		// Front 
		vd[count++] = ChunkMesh::VertexData(x - .5f, y - .5f, z + .5f, .8f, .8f, .8f, u, v);
		vd[count++] = ChunkMesh::VertexData(x + .5f, y - .5f, z + .5f, .8f, .8f, .8f, (u + w), v);
		vd[count++] = ChunkMesh::VertexData(x + .5f, y + .5f, z + .5f, .8f, .8f, .8f, (u + w), (v + w));
		vd[count++] = ChunkMesh::VertexData(x - .5f, y + .5f, z + .5f, .8f, .8f, .8f, u, (v + w));
	}
	if (BlocDisplayed & 2)
	{
		//Right															 	1.  4
		vd[count++] = ChunkMesh::VertexData(x + .5f, y - .5f, z + .5f, .9f, .9f, .9f, u, v);
		vd[count++] = ChunkMesh::VertexData(x + .5f, y - .5f, z - .5f, .9f, .9f, .9f, (u + w), v);
		vd[count++] = ChunkMesh::VertexData(x + .5f, y + .5f, z - .5f, .9f, .9f, .9f, (u + w), (v + w));
		vd[count++] = ChunkMesh::VertexData(x + .5f, y + .5f, z + .5f, .9f, .9f, .9f, u, (v + w));
	}
	if (BlocDisplayed & 4)
	{
		//Back															 	1.  4
		vd[count++] = ChunkMesh::VertexData(x + .5f, y - .5f, z - .5f, .9f, .9f, .9f, u, v);
		vd[count++] = ChunkMesh::VertexData(x - .5f, y - .5f, z - .5f, .9f, .9f, .9f, (u + w), v);
		vd[count++] = ChunkMesh::VertexData(x - .5f, y + .5f, z - .5f, .9f, .9f, .9f, (u + w), (v + w));
		vd[count++] = ChunkMesh::VertexData(x + .5f, y + .5f, z - .5f, .9f, .9f, .9f, u, (v + w));
	}
	if (BlocDisplayed & 8)
	{
		//Left															 	1.  4
		vd[count++] = ChunkMesh::VertexData(x - .5f, y - .5f, z - .5f, 1.f, 1.f, 1.f, u, v);
		vd[count++] = ChunkMesh::VertexData(x - .5f, y - .5f, z + .5f, 1.f, 1.f, 1.f, (u + w), v);
		vd[count++] = ChunkMesh::VertexData(x - .5f, y + .5f, z + .5f, 1.f, 1.f, 1.f, (u + w), (v + w));
		vd[count++] = ChunkMesh::VertexData(x - .5f, y + .5f, z - .5f, 1.f, 1.f, 1.f, u, (v + w));
	}
	if (BlocDisplayed & 16)
	{
		//Top															 	1.  4
		vd[count++] = ChunkMesh::VertexData(x - .5f, y + .5f, z + .5f, 1.f, 1.f, 1.f, u, v);
		vd[count++] = ChunkMesh::VertexData(x + .5f, y + .5f, z + .5f, 1.f, 1.f, 1.f, (u + w), v);
		vd[count++] = ChunkMesh::VertexData(x + .5f, y + .5f, z - .5f, 1.f, 1.f, 1.f, (u + w), (v + w));
		vd[count++] = ChunkMesh::VertexData(x - .5f, y + .5f, z - .5f, 1.f, 1.f, 1.f, u, (v + w));
	}
	if (BlocDisplayed & 32)
	{
		//Bottom														 	1.  4
		vd[count++] = ChunkMesh::VertexData(x - .5f, y - .5f, z - .5f, 1.f, 1.f, 1.f, u, v);
		vd[count++] = ChunkMesh::VertexData(x + .5f, y - .5f, z - .5f, 1.f, 1.f, 1.f, (u + w), v);
		vd[count++] = ChunkMesh::VertexData(x + .5f, y - .5f, z + .5f, 1.f, 1.f, 1.f, (u + w), (v + w));
		vd[count++] = ChunkMesh::VertexData(x - .5f, y - .5f, z + .5f, 1.f, 1.f, 1.f, u, (v + w));
	}
}

Chunk::~Chunk() { }

void Chunk::RemoveBloc(int x, int y, int z)
{
    m_blocks.Set(x, y, z, BTYPE_AIR);
}

void Chunk::SetBloc(int x, int y, int z, BlockType type)
{
    m_blocks.Set(x, y, z, type);
}

BlockType Chunk::GetBloc(int x, int y, int z)
{
    return m_blocks.Get(x, y, z);
}

//BLOCK_TYPE Chunk::GetBloc_s(int x, int y, int z)
//{
//	if (x >= Size.x || y >= Size.y || z >= Size.z)
//		return BTYPE_DIRT;
//
//	return m_blocks->Get(x, y, z);
//}

Vector3f Chunk::GetSize() const
{
	return Size;
}

uint8 Chunk::IsVisible(int x, int y, int z)
{
	// TODO: Optimize this -Kan
	// 2015-11-16: Thank you past me!
	int i = 0;
	if (x < Size.x && y < Size.y && z + 1 < Size.z && x >= 0 && y >= 0 && z + 1 >= 0){
		if (m_blocks.Get(x, y, z + 1) == BTYPE_AIR)
			i += 1;
	}
	else
		i += 1;
	if (x + 1 < Size.x && y < Size.y && z < Size.z && x + 1 >= 0 && y >= 0 && z >= 0){
		if (m_blocks.Get(x + 1, y, z) == BTYPE_AIR)
			i += 2;
	}
	else
		i += 2;
	if (x < Size.x && y < Size.y && z - 1 < Size.z && x >= 0 && y >= 0 && z - 1 >= 0){
		if (m_blocks.Get(x, y, z - 1) == BTYPE_AIR)							
			i += 4;
	}
	else
		i += 4;
	if (x - 1 < Size.x && y < Size.y && z < Size.z && x - 1 >= 0 && y >= 0 && z >= 0){
		if (m_blocks.Get(x - 1, y, z) == BTYPE_AIR)
			i += 8;
	}
	else
		i += 8;
	if (x < Size.x && y + 1 < Size.y && z < Size.z && x >= 0 && y + 1 >= 0 && z >= 0){
		if (m_blocks.Get(x, y + 1, z) == BTYPE_AIR)
			i += 16;
	}
	else
		i += 16;
	if (x < Size.x && y - 1 < Size.y && z < Size.z && x >= 0 && y - 1 >= 0 && z >= 0){
		if (m_blocks.Get(x, y - 1, z) == BTYPE_AIR)
			i += 32;
	}
	else
		i += 32;
	return i;
}
void Chunk::DrawPlayGround() 
{
	if(rand() % 100 < 25)
		DrawArch(1, 1, 12, BTYPE_LEAF);
	if(rand() % 100 > 90)
		DrawStairs(8, 1, 6, BTYPE_STONE, true);
	if(rand() % 10 < 4)
		DrawWall(12, 1, 5, BTYPE_STONE);
	if(rand() % 4000 < 375)
		DrawWall(4, 1, 2, BTYPE_SANDSTONE, true);
	if (rand() % 200 > 150)
		DrawRoundStairs(0, 0, 0, BTYPE_SANDSTONE);
	if (rand() % 10 > 8)
		DrawTower(7, 1, 7, BTYPE_WOOD);
}
void Chunk::DrawStairs(int x, int y, int z, BlockType type, bool vertical)
{
	size_t v = 0;
	for (size_t u = 0; u < 4; u++)
	{
		if (vertical)
			m_blocks.Set(x, y + v, z + u, type);
		else
			m_blocks.Set(x + u, y + v, z, type);
		v++;
	}
}
void Chunk::DrawWall(int x, int y, int z, BlockType type, bool vertical)
{
	for (size_t u = 0; u < 4; u++)
	{
		for (size_t v = 0; v < 3; v++)
		{
			if (vertical)
				m_blocks.Set(x, y + v, z + u, type);
			else
				m_blocks.Set(x + u, y + v, z, type);
		}
	}
}
void Chunk::DrawArch(int x, int y, int z, BlockType type, bool vertical)
{
	for (size_t u = 0; u < 4; u+=2)
	{
		for (size_t v = 0; v < 4; v++)
		{
			if (vertical)
				m_blocks.Set(x, y + v, z + u, type);
			else
				m_blocks.Set(x + u, y + v, z, type);
		}
	}
	if (vertical)
		m_blocks.Set(x, y + 3, z + 1, type);
	else
		m_blocks.Set(x + 1, y + 3, z, type);
}
void Chunk::DrawRoundStairs(int x, int y, int z, BlockType type)
{
	int nx = 0;
	int nz = 0;
	for (size_t ny = y; ny < CHUNK_SIZE_Y; ny++)
	{
		switch (ny % 9)
		{
		case 0:
			nx = 0;
			nz = 0;
			break;
		case 1:
			nx = 0;
			nz = 1;
			break;
		case 2:
			nx = 0;
			nz = 2;
			break;
		case 3:
			nx = 1;
			nz = 2;
			break;
		case 4:
			nx = 2;
			nz = 2;
			break;
		case 5:
			nx = 2;
			nz = 1;
			break;
		case 6:
			nx = 2;
			nz = 0;
			break;
		case 7:
			nx = 1;
			nz = 2;
			break;
		case 8:
			nx = 0;
			nz = 0;
			break;
		}
		m_blocks.Set(x + nx, y + ny, z + nz, type);
	}
}
void Chunk::DrawTower(int x, int y, int z, BlockType type)
{
	for (size_t i = 0; i < 16; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			for (size_t k = 0; k < 4; k++)
			{
				m_blocks.Set(x + j, y + i, z + k, type);
			}
		}
		for (size_t j = 1; j < 3; j++)
		{
			for (size_t k = 1; k < 3; k++)
			{
				m_blocks.Set(x + j, y + i, z + k, BTYPE_AIR);
			}
		}
		for (size_t i = 0; i < 4; i++)
		{
			switch (i)
			{
			case 0:
				m_blocks.Set(x, y + 16, z, BTYPE_SANDSTONE);
				m_blocks.Set(x, y + 17, z, BTYPE_SANDSTONE);
				break;
			case 1:
				m_blocks.Set(x + 3, y + 16, z, BTYPE_SANDSTONE);
				m_blocks.Set(x + 3, y + 17, z, BTYPE_SANDSTONE);
				break;
			case 2:
				m_blocks.Set(x, y + 16, z + 3, BTYPE_SANDSTONE);
				m_blocks.Set(x, y + 17, z + 3, BTYPE_SANDSTONE);
				break;
			case 3:
				m_blocks.Set(x + 3, y + 16, z + 3, BTYPE_SANDSTONE);
				m_blocks.Set(x + 3, y + 17, z + 3, BTYPE_SANDSTONE);
				break;
			}

		}
		for (size_t i = 0; i < 6; i++)
		{
			for (size_t j = 0; j < 6; j++)
			{
				m_blocks.Set(x - 1 + i, 19, z - 1 + j, BTYPE_UNKNOWN);
			}
		}
	}
}
