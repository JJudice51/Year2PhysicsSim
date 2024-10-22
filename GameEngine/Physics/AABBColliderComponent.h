#pragma once
#include "ColliderComponent.h"

namespace GamePhysics
{
	class AABBColliderComponent : public ColliderComponent
	{
	public:

		AABBColliderComponent(float width, float height) : ColliderComponent() { m_width = width; m_height = height; setColliderType(AABB); }


		GamePhysics::Collision* checkCollisionCircle(CircleColliderComponent* other) override;
		GamePhysics::Collision* checkCollisionAABB(AABBColliderComponent* other) override;

		void draw() override;

		float getWidth() {return m_width;}
		float getHeight() {return m_height;}
		float getRadius() {return m_radius;}

	private:
		//the horizontal measurement or distance measured from side to side.
		float m_width;

		//the measurement of the distance of an object from the base to the top.
		float m_height;

		//the line segment that runs from the center of the rectangle/square to any one of its vertices.
		float m_radius;

	};
}
