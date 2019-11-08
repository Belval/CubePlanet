#include "chunk.h"

Chunk::Chunk(Perlin perlin, int nx, int nz) : m_blocks(CHUNK_SIZE_X, CHUNK_SIZE_Y, CHUNK_SIZE_Z)
{
	m_positionChunk.x = nx;
	m_positionChunk.z = nz;
	for (int x = 0; x < CHUNK_SIZE_X; ++x) 
	{ 
		for (int z = 0; z < CHUNK_SIZE_Z; ++z) 
		{ 
			int height = CHUNK_SIZE_Y * (perlin.Get((float)(nz + z) / 2000.f, (float)(nx + x) / 2000.f) + 1) / 2;
			for (int y = 0; y < height; ++y)
			{
				SetBloc(x, y, z, height - y < 5 ? height - y == 1 ? BTYPE_GRASS : BTYPE_DIRT : BTYPE_STONE);
				if (height - y == 1)
				{
					if (rand() % 50 == 1) {
						DrawTree(x, height, z);
					}
				}
			} 
		} 
	}
	Size.x = CHUNK_SIZE_X;
	Size.y = CHUNK_SIZE_Y;
	Size.z = CHUNK_SIZE_Z;
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
	m_isDirty = true;
}

void Chunk::SetBloc(int x, int y, int z, BlockType type)
{
    m_blocks.Set(x, y, z, type);
	m_isDirty = true;
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
void Chunk::DrawTree(int x, int y, int z)
{
	size_t treeHeight = rand() % 5 + 3;
	size_t foliageHeight = treeHeight - rand() % treeHeight - 2;
	foliageHeight = foliageHeight < 1 ? 1 : foliageHeight;
	for (size_t i = 0; i < treeHeight; i++) 
	{
		m_blocks.Set(x, y + i, z, BTYPE_WOOD);
		if (i > foliageHeight) {
			for (int j = x - 2; j < x + 3; j++) {
				for (int k = z - 2; k < z + 3; k++) {
					if (j != 0 && k != 0)
						m_blocks.Set(j, y + i, k, BTYPE_LEAF); 
				}
			}
		}
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
