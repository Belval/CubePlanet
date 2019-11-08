#include "player.h"

Player::Player(World world, float posX, float posY, float posZ, float rotX, float rotY) : m_World(world), m_positionPersonnage(posX, posY, posZ) {}

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
		if (m_World.BlockAt(m_positionPersonnage.x, m_positionPersonnage.y - 1.7f, m_positionPersonnage.z) != BTYPE_AIR ||
			m_World.BlockAt(m_positionPersonnage.x, m_positionPersonnage.y - 2.0f, m_positionPersonnage.z) != BTYPE_AIR) {
			m_vitessePersonnage.y += 100.f * elapsedTime;
		}
	}
	if (crouch)
	{
		vecteurDeplacement.y -= float(20 * elapsedTime);
	}
	if (m_World.BlockAt(m_positionPersonnage.x, m_positionPersonnage.y - 1.7f, m_positionPersonnage.z) != BTYPE_AIR ||
		m_World.BlockAt(m_positionPersonnage.x, m_positionPersonnage.y - 2.0f, m_positionPersonnage.z) != BTYPE_AIR)
	{
		m_vitessePersonnage.y = m_vitessePersonnage.y > 0 ? m_vitessePersonnage.y : 0;
	}
	else if (m_World.BlockAt(m_positionPersonnage.x, m_positionPersonnage.y + 0.4f, m_positionPersonnage.z) != BTYPE_AIR)
	{
		m_vitessePersonnage.y = m_vitessePersonnage.y < 0 ? m_vitessePersonnage.y : 0;
	}
	else {
		m_vitessePersonnage.y += GRAVITY * 3 * elapsedTime;
	}
	// FIXME: Reducing Y by smallish increments because collision detection is shady
	vecteurDeplacement.y += m_vitessePersonnage.y * elapsedTime - 1.f * elapsedTime;

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
