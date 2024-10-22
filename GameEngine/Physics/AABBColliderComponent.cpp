#include "AABBColliderComponent.h"
#include "CircleColliderComponent.h"
#include "Engine/TransformComponent.h"
#include "Math/Vector2.h"
#include "Engine/Entity.h"
#include <raylib.h>


/// <summary>
/// Checks for collision with a Circle Collider
/// </summary>
/// <param name="other">The other collider this one would be detecting</param>
/// <returns></returns>
GamePhysics::Collision* GamePhysics::AABBColliderComponent::checkCollisionCircle(CircleColliderComponent* other)
{
    //this is for getting a direction to another collider
    GameMath::Vector2 otherPosition = other->getOwner()->getTransform()->getGlobalPosition();
    GameMath::Vector2 position = getOwner()->getTransform()->getGlobalPosition();
    GameMath::Vector2 direction = otherPosition - position;
    float distance = direction.getMagnitude();
    float otherRadius = other->getRadius();

    //If there is no collision then don't do anything and return a null pointer.
    if (distance > otherRadius + m_radius)
        return nullptr;

    //if a collision is detected
    if (position.x < otherPosition.x + getRadius() && position.x + m_width > otherPosition.x &&
        position.y < otherPosition.y + other->getRadius() && position.y + m_height > otherPosition.y)
    {
        //Get Circle collision data and return that collision
        GamePhysics::Collision* collisionData = new Collision();
        collisionData->collider = other;
        collisionData->normal = direction.getNormalized();
        collisionData->contactPoint = position + direction.getNormalized() * getRadius();
        collisionData->penetrationDistance = (otherRadius + m_radius) - distance;

        return collisionData;
    }
}


/// <summary>
/// Checks for collision between itself and an AABB collider
/// </summary>
/// <param name="other">the other collider that this one would be checking for collision against</param>
/// <returns></returns>
    GamePhysics::Collision* GamePhysics::AABBColliderComponent::checkCollisionAABB(AABBColliderComponent* other)
{
    //this is for getting direction to the other collider
    GameMath::Vector2 otherPosition = other->getOwner()->getTransform()->getGlobalPosition();
    GameMath::Vector2 position = getOwner()->getTransform()->getGlobalPosition();
    GameMath::Vector2 direction = otherPosition - position;

    //if a collision is detected
    if (position.x < otherPosition.x + other->getWidth() && position.x + m_width > otherPosition.x &&
        position.y < otherPosition.y + other->getHeight() && position.y + m_height > otherPosition.y)
    {
        //get AABB collistion data and return that collision
        GamePhysics::Collision* collisionData = new Collision();
        collisionData->collider = other;
        collisionData->normal = direction.getNormalized();
        collisionData->contactPoint = position + direction.getNormalized() * getRadius();
        collisionData->penetrationDistance = (other->getRadius() + getRadius());

        return collisionData;
    }
    else
        return nullptr;
}


/// <summary>
/// draws an AABB collider in the Window
/// </summary>
void GamePhysics::AABBColliderComponent::draw()
{
    //get position to draw to
    GameMath::Vector2 position = getOwner()->getTransform()->getGlobalPosition();

    RAYLIB_H::DrawRectangleLines(position.x - m_width / 2, position.y - m_height / 2, getWidth(), getHeight(), GetColor(getColor()));
}
