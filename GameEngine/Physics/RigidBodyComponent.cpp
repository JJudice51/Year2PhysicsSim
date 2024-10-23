#include "RigidBodyComponent.h"
#include "Engine/TransformComponent.h"
#include "Engine/Entity.h"
#include "Physics/ColliderComponent.h"

void GamePhysics::RigidBodyComponent::applyForce(GameMath::Vector2 force)
{
	m_velocity = m_velocity + force / getMass();
}

void GamePhysics::RigidBodyComponent::applyForceToEntity(RigidBodyComponent* rigidBody, GameMath::Vector2 force)
{
	applyForce(force * -1);
	rigidBody->applyForce(force);
}

void GamePhysics::RigidBodyComponent::fixedUpdate(float fixedDeltaTime)
{
	GameMath::Vector2 position = getOwner()->getTransform()->getLocalPosition();
	getOwner()->getTransform()->setLocalPosition(position + m_velocity * fixedDeltaTime);

	GameMath::Vector2 gravity = { 0, getGravity() };
	applyForce(gravity * getMass());
}

void GamePhysics::RigidBodyComponent::resolveCollision(GamePhysics::Collision* collisionData)
{
	RigidBodyComponent* otherRigi = collisionData->collider->getRigidBody();
	
	GameMath::Vector2 otherNorm = GameMath::Vector2({ -1 * collisionData->normal.x,-1 * collisionData->normal.y });

	float force;

	GameMath::Vector2 impulse;
	
	GameMath::Vector2 collisionForce = (otherNorm * collisionData->penetrationDistance);

	if (otherRigi)
	{
		if(otherRigi->getMass() == getMass() && 1 == getDotProduct(collisionData->normal, collisionData->normal))
		{
			force = getMass() * getDotProduct(getVelocity() - otherRigi->getVelocity(), collisionData->normal);
		}
		else
		{
			force = (2 * getDotProduct(getVelocity() - otherRigi->getVelocity(), collisionData->normal)
				/ (getDotProduct(collisionData->normal, collisionData->normal) * ((1 / getMass()) + (1 / otherRigi->getMass()))));
		}

			impulse = (collisionData->normal * -force) + (collisionForce / 2);

			applyForceToEntity(otherRigi, impulse);

	}

	else
	{

		force = 2 * getDotProduct(getVelocity(), collisionData->normal) * getMass();
		
		impulse = (collisionData->normal * -force) + collisionForce;

		applyForce(impulse);
	}

	
}
