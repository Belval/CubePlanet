#ifndef PLAYER_H__
#define PLAYER_H__

#include "define.h"
#include "vector3.h"
#include "world.h"

class Player {
public:
	Player(World* world, float posX = VIEW_DISTANCE, float posY = 100.f, float posZ = VIEW_DISTANCE, float rotX = 0, float rotY = 0);
	~Player();

	void TurnLeftRight(float value);
	void TurnTopBottom(float value);

	Vector3f SimulateMove(bool front, bool back, bool left, bool right, bool run, bool jump, bool crouch, float elapsedTime);

	void ApplyRotation() const;
	void ApplyTranslation() const;
	Vector3f Position() const;
	void SetPosition(Vector3f v);
private:
	World* m_World;
	Vector3f m_positionPersonnage;
	Vector3f m_accelerationPersonnage;
	Vector3f m_vitessePersonnage;
	float rotX = 0.f, rotY = 0.f, angle = 0.0f;
	float vitesseY = 0.f;
};

#endif //PLAYER_H__