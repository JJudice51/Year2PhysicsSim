#include "ColliderComponent.h"
#include "Engine/Engine.h"
#include "Engine/Scene.h"
#include "Engine/Entity.h"
#include "Physics/RigidBodyComponent.h"

void GamePhysics::ColliderComponent::start()
{
	GameEngine::Engine::getCurrentScene()->addActiveCollider(this);
	// Get owner's rigidbody
	
	m_rigidBody = getOwner()->getComponent<GamePhysics::RigidBodyComponent>();
}

GamePhysics::Collision* GamePhysics::ColliderComponent::checkCollision(ColliderComponent* other)
{
	switch (other->getColliderType())
	{
	case CIRCLE:
		return checkCollisionCircle((CircleColliderComponent*)other);
	case AABB:
		return checkCollisionAABB((AABBColliderComponent*)other);
	}

	return nullptr;
}

void GamePhysics::ColliderComponent::onCollisionEnter(GamePhysics::Collision* other)
{
	m_color = 0xFF0000FF;
}

void GamePhysics::ColliderComponent::update(double deltaTime)
{
	m_color = 0x00FF00FF;
}
