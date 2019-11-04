#include "world.h"

World::World(int x, int z) : m_Map(x, z)
{
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < z; j++)
		{
			m_Map.Set(i, j, new Chunk(m_perlin, i * CHUNK_SIZE_X, j * CHUNK_SIZE_Z));
		}
	}
}
World::~World() 
{

}

Chunk* World::ChunkAt(int x, int y, int z) const 
{
	int cx = (int)x / CHUNK_SIZE_X;
	int cz = (int)z / CHUNK_SIZE_Z;

	return m_Map.Get(cx, cz);
}
Chunk* World::ChunkAt(const Vector3f& pos) const 
{
	return ChunkAt(pos.x, pos.y, pos.z);
}
BlockType World::BlockAt(int x, int y, int z, BlockType bType) const
{
	Chunk* c = ChunkAt(x, y, z);

	if (!c)
		return BTYPE_AIR;

	int bx = (int)x % CHUNK_SIZE_X;
	int by = (int)y % CHUNK_SIZE_Y;
	int bz = (int)z % CHUNK_SIZE_Z;

	return c->GetBloc(bx, by, bz);
}