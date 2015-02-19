#pragma once

#include "Jig/Vector.h"
#include "Jig/Types.h"

#include "SFML/Graphics.hpp"

#include <memory>

class Sprite;
class Player;
class Mesh;

class View
{
public:
	View();
	~View();

	void Update(float tDelta);

	void Draw(sf::RenderWindow& win) const;

	void OnKeyPressed(sf::Keyboard::Key key);

private:
	void DrawView() const;
	void DrawSprites() const;

	bool m_bWireframe, m_bHitTest;

	std::unique_ptr<Player> m_pPlayer;

	int m_rotationTarget;
	float m_vAngle, m_hAngle, m_zoom;
};

