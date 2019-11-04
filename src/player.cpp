#include "player.h"

Player::Player(World* world, float posX, float posY, float posZ, float rotX, float rotY) : m_positionPersonnage(posX, posY, posZ)
{
	m_World = world;
}

Player::~Player() { }

void Player::TurnLeftRight(float value)
{
	rotY += value;
}
void Player::TurnTopBottom(float value)
{
	if ((rotX + value) > 90) // On emp�che le joueur de faire des "frontflips"
		rotX = 90;
	else if ((rotX + value) < -90)  // On emp�che le joueur de faire des "backflip"
		rotX = -90;
	else
		rotX += value;
}

Vector3f Player::SimulateMove(bool front, bool back, bool left, bool right, bool run, bool jump, bool crouch, float elapsedTime)
{
	// Pour �viter les calculs suppl�mentaires on le fait une fois en haut
	float fMultiplicateur = elapsedTime * (run && !crouch ? VITESSE_COURSE : (crouch ? VITESSE_ACCROUPI : VITESSE_MARCHE)); // On prend en compte si le joueur "run"
	Vector3f vecteurDeplacement;
	vecteurDeplacement.Zero();
	if (front)
	{
		float xrotrad, yrotrad;
		yrotrad = (rotY / 180 * 3.141592654f);
		xrotrad = (rotX / 180 * 3.141592654f);
		vecteurDeplacement.x += float(sin(yrotrad)) * fMultiplicateur;
		vecteurDeplacement.z -= float(cos(yrotrad)) * fMultiplicateur;
	}
	if (back)
	{
		float xrotrad, yrotrad;
		yrotrad = (rotY / 180 * 3.141592654f);
		xrotrad = (rotX / 180 * 3.141592654f);
		vecteurDeplacement.x -= float(sin(yrotrad)) * fMultiplicateur;
		vecteurDeplacement.z += float(cos(yrotrad)) * fMultiplicateur;
	}
	if (left)
	{
		float yrotrad;
		yrotrad = (rotY / 180 * 3.141592654f);
		vecteurDeplacement.x -= float(cos(yrotrad)) * fMultiplicateur;
		vecteurDeplacement.z -= float(sin(yrotrad)) * fMultiplicateur;
	}
	if (right)
	{
		float yrotrad;
		yrotrad = (rotY / 180 * 3.141592654f);
		vecteurDeplacement.x += float(cos(yrotrad)) * fMultiplicateur;
		vecteurDeplacement.z += float(sin(yrotrad)) * fMultiplicateur;
	}
	if (jump)
	{
		vecteurDeplacement.y += float(20 * elapsedTime);
	}
	if (crouch)
	{
		vecteurDeplacement.y -= float(20 * elapsedTime);
	}
	return vecteurDeplacement;
}

void Player::ApplyRotation() const
{
	glRotatef(rotX, 1.0, 0.0, 0.0);
	glRotatef(rotY, 0.0, 1.0, 0.0);
}
void Player::ApplyTranslation() const
{
	glTranslatef(-Player::Position().x, -Player::Position().y, -Player::Position().z);
}

Vector3f Player::Position() const
{
	return m_positionPersonnage;
}

void Player::SetPosition(Vector3f v)
{
	m_positionPersonnage = v;
}

//void Player::CalculateY(float fTime)
//{
//	Vector3f v;
//	v.y = roundf(vitesseY * fTime * 10.f) / 10.f;
//	Vector3f nouvellePosition = m_positionPersonnage + v;
//	bool positive = m_positionPersonnage.y <= nouvellePosition.y;
//	int delta = roundf(abs(m_positionPersonnage.y - nouvellePosition.y));
//	std::cout << "delta: " << (delta) << std::endl;
//	//assert(delta == 0);
//	if (delta != 0)
//	{
//		std::cout << "";
//	}
//	int i = delta;
//	do
//	{
//		std::cout << "i: " << i << std::endl;
//		//float posY = nouvellePosition.y - i /*(positive ? delta - i : i)*/;
//		float posY = roundf(nouvellePosition.y - (positive ? i - 1.f : delta - i + 1.f));
//		auto btype = m_currentChunk->GetBloc_s(
//			roundf(nouvellePosition.x - m_currentChunkPos.x * CHUNK_SIZE_X),
//			posY,
//			roundf(nouvellePosition.z - m_currentChunkPos.z * CHUNK_SIZE_Z));
//		if (btype != BTYPE_AIR)
//		{
//			std::cout << "It's a hit?" << posY << std::endl;
//			m_positionPersonnage.y = posY + 1.7f;
//			//m_positionPersonnage.y = nouvellePosition.y + (delta * sign);
//			vitesseY = 0.f;
//			return;
//		}
//		else
//		{
//			std::cout << "";
//		}
//	} while (i--);
//	//if (!Collision(v))
//	//{
//		//std::cout << "Nope" << std::endl;
//		m_positionPersonnage += v;
//		vitesseY += roundf(GRAVITY * fTime * 3.0f * 10.f) / 10.f;
//	//}
//	//else
//	//{
//	//	std::cout << "Yep" << std::endl;
//	//	m_positionPersonnage.y = ceilf(m_positionPersonnage.y) - 0.3f;
//	//}
//	std::cout << vitesseY << std::endl;
//}