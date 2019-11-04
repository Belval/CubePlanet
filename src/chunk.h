#ifndef CHUNK_H__
#define CHUNK_H__
#include <iostream>
#include "array3d.h"
#include "array2d.h"
#include "chunkmesh.h"
#include "blockinfo.h"
#include "vector3.h"
#include "perlin.h"

class Chunk
{
public:
    Chunk(Perlin* perlin, int x = 0, int z = 0);
    ~Chunk();

	void Update(Array2d<BlockInfo>* m_listBloc);
	void Render() const;
	bool IsDirty() const;
	void AddBlockToMesh(ChunkMesh::VertexData* vd, int& count, BlockType bt, int x, int y, int z, float u, float v, float w, unsigned int BlockDisplayed);

    void RemoveBloc(int x, int y, int z);
    void SetBloc(int x, int y, int z, BlockType type);
	BlockType GetBloc(int x, int y, int z);
	//BLOCK_TYPE GetBloc_s(int x, int y, int z);
	Vector3f GetSize() const;
	uint8 IsVisible(int x, int y, int z);
	void DrawPlayGround();
	void DrawStairs(int x, int y, int z, BlockType type, bool vertical = false);
	void DrawWall(int x, int y, int z, BlockType type, bool vertical = false);
	void DrawArch(int x, int y, int z, BlockType type, bool vertical = false);
	void DrawRoundStairs(int x, int y, int z, BlockType type);
	void DrawTower(int x, int y, int z, BlockType type);
private:
	Array3d<BlockType> m_blocks;
	ChunkMesh m_chunkMesh;
	Vector3f Size;
	bool m_isDirty;
	Vector3f m_positionChunk;
};

#endif // CHUNK_H__
