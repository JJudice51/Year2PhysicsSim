#include "CircleColliderComponent.h"
#include "Engine/TransformComponent.h"
#include "Math/Vector2.h"
#include "Engine/Entity.h"
#include <raylib.h>
#include "AABBColliderComponent.h"
#include <iostream>

GamePhysics::Collision* GamePhysics::CircleColliderComponent::checkCollisionCircle(CircleColliderComponent* other)
{
    GameMath::Vector2 otherPosition = other->getOwner()->getTransform()->getGlobalPosition();
    GameMath::Vector2 position = getOwner()->getTransform()->getGlobalPosition();
    GameMath::Vector2 direction = otherPosition - position;
    float distance = direction.getMagnitude();

    if (distance > other->m_radius + m_radius)
        return nullptr;

    GamePhysics::Collision* collisionData = new Collision();
    collisionData->collider = other;
    collisionData->normal = direction.getNormalized();
    collisionData->contactPoint = position + direction.getNormalized() * getRadius();
    collisionData->penetrationDistance = (other->m_radius + m_radius) - distance;

    return collisionData;
}

GamePhysics::Collision* GamePhysics::CircleColliderComponent::checkCollisionAABB(GamePhysics::AABBColliderComponent* other)
{
    GameMath::Vector2 direction = getOwner()->getTransform()->getGlobalPosition() - other->getOwner()->getTransform()->getGlobalPosition();
    
    if (direction.x < -other->getWidth() / 2)
    {
        direction.x = -other->getWidth() / 2;
    }
    else if(direction.x > other->getWidth() / 2)
    {
        direction.x = other->getWidth() / 2;
    }
    if (direction.y < -other->getHeight() / 2)
    {
        direction.y = -other->getHeight() / 2;
    }
    else if (direction.y > other->getWidth() / 2)
    {
        direction.y = other->getWidth() / 2;
    }

    GameMath::Vector2 edgePoint = direction + other->getOwner()->getTransform()->getGlobalPosition();

    float distance = (getOwner()->getTransform()->getGlobalPosition() - edgePoint).getMagnitude();
    if (distance <= m_radius)
    {
        std::cout << "CollistionDetected" << "\n";
    }

    return nullptr;
}

void GamePhysics::CircleColliderComponent::draw()
{
    GameMath::Vector2 position = getOwner()->getTransform()->getGlobalPosition();

    RAYLIB_H::DrawCircleLines(position.x, position.y, getRadius(), GetColor(getColor()));
}
