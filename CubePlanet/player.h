#ifndef PLAYER_H__
#define PLAYER_H__
#include "vector3.h"
#include "chunk.h"

class Player {
public:
	Player(float posX = VIEW_DISTANCE, float posY = 2.7f, float posZ = VIEW_DISTANCE, float rotX = 0, float rotY = 0);
	~Player();

	void TurnLeftRight(float value);
	void TurnTopBottom(float value);

	Vector3f SimulateMove(bool front, bool back, bool left, bool right, bool run, bool jump, bool crouch, float elapsedTime);

	void ApplyRotation() const;
	void ApplyTranslation() const;
	Vector3f Position() const;
	void SetPosition(Vector3f v);
	//Chunk* CurrentChunk() const;
	//void SetCurrentChunk(Chunk* chunk);
	//Vector3f CurrentChunkPos() const;
	//void SetCurrentChunkPos(int x, int z);
	//bool Collision(Vector3f v);
	//bool CollisionUnder();
	//bool CollisionTop();
	//bool CollisionY(Vector3f v);
	//void CalculateY(float fTime);
	//BLOCK_TYPE BlocFront();
	//BLOCK_TYPE BlocBack();
	//BLOCK_TYPE BlocLeft();
	//BLOCK_TYPE BlocRight();
	//BLOCK_TYPE BlocTop();
private:
	// Positions cartésiennes du personnage ainsi que l'orientation
	/*Vector3<float>*/
	//Array2d<Chunk*>* m_Map;
	//Chunk* m_currentChunk;
	//Vector3f m_currentChunkPos;
	Vector3f m_positionPersonnage;
	float rotX = 0.f, rotY = 0.f, angle = 0.0f;
	float vitesseY = 0.f;
};

#endif //PLAYER_H__