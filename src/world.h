#ifndef WORLD_H__
#define WORLD_H__

#include "chunk.h"
#include "perlin.h"

class World 
{
public:
	World(int x, int z);
	~World();
	
	Chunk* ChunkAt(int x, int y, int z) const;
	Chunk* ChunkAt(const Vector3f& pos) const;
	BlockType BlockAt(int x, int y, int z, BlockType bType = BTYPE_AIR) const;
	Array2d<Chunk*> m_Map;
	Perlin* m_perlin = new Perlin(16, 2, 1, 95);
};

#endif