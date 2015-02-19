#include "Player.h"
#include "Jig/ObjMesh.h"
#include "Jig/MeshAnimation.h"

Player::Player() : m_val(0)
{
	m_mesh.reset(new Jig::ObjMesh("../Wombat/res/player.obj"));
	m_anim.reset(new Jig::MeshAnimation(*m_mesh));
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

	m_anim->Draw(m_val);

	glPopMatrix();
}

