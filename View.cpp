#include "stdafx.h"
#include "View.h"
#include "Player.h"

#include "Jig/Material.h"

#include <SFML/OpenGL.hpp>

#include <iostream>
#include <set>

#define GL_RESCALE_NORMAL 0x803A

using namespace Jig;

View::View() : m_pPlayer(new Player), m_bWireframe(false), m_bHitTest(true), 
m_vAngle(0), m_hAngle(0), m_zoom(1)
{
}

View::~View()
{
}

void View::Update(float tDelta)
{
	m_pPlayer->Update(tDelta);

	float vRotationDelta = tDelta * 200;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		m_vAngle += vRotationDelta;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		m_vAngle -= vRotationDelta;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		m_hAngle += vRotationDelta;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		m_hAngle -= vRotationDelta;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown))
		m_zoom *= 1 + tDelta;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp))
		m_zoom /= 1 + tDelta;
}

void View::Draw(sf::RenderWindow& win) const
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_CULL_FACE);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_RESCALE_NORMAL);

	float amb[] = { 0.2f, 0.2f, 0.2f, 0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	float light0[] = { -10, 10, 30, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light0);

	glScalef(m_zoom, m_zoom, m_zoom);

	glRotatef(m_vAngle, 1, 0, 0);
	glRotatef(m_hAngle, 0, 1, 0);

	if (m_bWireframe)
		glPolygonMode(GL_FRONT, GL_LINE);

	DrawView();
	DrawSprites();

	glPolygonMode(GL_FRONT, GL_FILL);
}

void View::OnKeyPressed(sf::Keyboard::Key key)
{
	auto RotateCCW = [](Vec3& vec) { vec = Vec3(vec.z, 0, -vec.x); };
	auto RotateCW = [](Vec3& vec) { vec = Vec3(-vec.z, 0, vec.x); };

	if (key == sf::Keyboard::Tab)
		m_bWireframe = !m_bWireframe;
	else if (key == sf::Keyboard::H)
		m_bHitTest = !m_bHitTest;
}

void View::DrawView() const
{
	Material().Apply();
}

void View::DrawSprites() const
{
	glDisable(GL_TEXTURE_2D);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
				
	m_pPlayer->Draw();

	glPopMatrix();
}