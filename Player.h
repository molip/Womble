#pragma once

#include <memory>

namespace Jig
{
	class ObjMesh;
	class MeshAnimation;
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
	std::unique_ptr<Jig::MeshAnimation> m_anim;
	float m_val;
};

