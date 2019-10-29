#include "stalker.h"

Stalker::Stalker() 
{

}
Stalker::~Stalker()
{

}
bool Stalker::PlayerIsInRange(Vector3f vPosPlayer)
{
	if (CalculateDistance(vPosPlayer, Position) < 10)
	{
		CalculateTranslation(vPosPlayer);
		return true;
	}
	else
		return false;
}
void Stalker::SetMeshData(VertexData* vd, int vertexCount)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexVboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData) * vertexCount, vd, GL_STATIC_DRAW);
}
void Stalker::Render() const
{
	VertexData v;
	//SetMeshData(v, 24);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Render the front quad
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(1, 0); glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(1, 1); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(0, 1); glVertex3f(-0.5f, -0.5f, 0.5f);

	// Render the back quad
	glTexCoord2f(0, 0); glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(1, 0); glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(1, 1); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(0, 1); glVertex3f(0.5f, -0.5f, -0.5f);

	// Render the right quad
	glTexCoord2f(0, 0); glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(1, 0); glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(1, 1); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(0, 1); glVertex3f(0.5f, -0.5f, 0.5f);

	// Render the left quad
	glTexCoord2f(0, 0); glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(1, 0); glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(1, 1); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(0, 1); glVertex3f(-0.5f, -0.5f, -0.5f);

	// Render the top quad
	glTexCoord2f(0, 0); glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(1, 0); glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(1, 1); glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0, 1); glVertex3f(-0.5f, 0.5f, 0.5f);

	// Render the bottom quad
	glTexCoord2f(1, 0); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1, 1); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(0, 1); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(0, 0); glVertex3f(-0.5f, -0.5f, 0.5f);
	glEnd();
}
void SetVertexData() 
{

}
float Stalker::CalculateDistance(Vector3f v1, Vector3f v2)
{
	return sqrt(pow((v2.x - v1.x), 2) + pow((v2.y - v1.y), 2) + pow((v2.z - v1.z), 2));
}
void Stalker::CalculateTranslation(Vector3f v1)
{
	Position.x += cos(acos((v1.x - Position.x) / CalculateDistance(v1, Position))) * fVitesse;
	Position.y += sin(asin((v1.y - Position.y) / CalculateDistance(v1, Position))) * fVitesse;
}
void Stalker::ApplyRotation() const
{

}
void Stalker::ApplyTranslation() const
{
	glTranslatef(-Position.x, -Position.y, -Position.z);
}
void Stalker::SetPosition(Vector3f vPos) 
{
	Position.x = vPos.x;
	Position.y = vPos.y;
	Position.z = vPos.z;
}