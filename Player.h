#pragma once

#include <memory>

namespace Jig
{
	class ObjMesh;
}

class Player
{
public:
	Player();
	~Player();

	void Update(float tDelta);
	void Draw() const;

private:
	std::unique_ptr<Jig::ObjMesh> m_mesh;
	float m_val;
};

