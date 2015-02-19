#pragma once

#include <memory>

namespace Jig
{
	class ObjMesh;
}

class Player
{
public:
	enum class State { Stand, Walk };

	Player();
	~Player();

	void Update(float tDelta);
	void Draw() const;
	void SetState(State s);

private:
	State m_state;
	std::unique_ptr<Jig::ObjMesh> m_mesh;
	float m_val;
};

