#include "Player.h"
#include "Jig/ObjMesh.h"

Player::Player() : m_val(0)
{
	m_mesh.reset(new Jig::ObjMesh("../Wombat/res/player.obj"));
}

Player::~Player()
{
}

void Player::Update(float tDelta)
{
	m_val += tDelta;
}

void Player::Draw() const
{
	glPushMatrix();
	glTranslatef(0, -0.8f, 0);

	float angle = ::sin(m_val * 20) * 50;

	m_mesh->DrawObject("Body");

	glPushMatrix();
	glTranslatef(0, 0.6f, 0);
	glRotatef(angle, 1, 0, 0);
	glTranslatef(0, -0.6f, 0);
	m_mesh->DrawObject("Left_leg");
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0.6f, 0);
	glRotatef(-angle, 1, 0, 0);
	glTranslatef(0, -0.6f, 0);
	m_mesh->DrawObject("Right_leg");
	glPopMatrix();

	glPopMatrix();
}

