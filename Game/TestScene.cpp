#include "TestScene.h"
#include "Engine/Entity.h"
#include "Graphics/ShapeComponent.h"
#include "Engine/TransformComponent.h"
#include "Physics/CircleColliderComponent.h"
#include "Physics/AABBColliderComponent.h"
#include "Physics/RigidBodyComponent.h"
#include <chrono>
#include <cmath>

void TestScene::onStart()
{
	// Set up circle 1
	m_circle1 = new GameEngine::Entity();
	m_circle1->getTransform()->setLocalScale({ 40, 40 });
	m_circle1->getTransform()->setLocalPosition({ 100, 100 });
	m_circle1->addComponent<GameGraphics::ShapeComponent>()
		->setShapeType(GameGraphics::CIRCLE);
	m_circle1->addComponent(new GamePhysics::CircleColliderComponent(50));
	GamePhysics::RigidBodyComponent* circle1Rigi = m_circle1->addComponent(new GamePhysics::RigidBodyComponent());
	circle1Rigi->setGravity(9.18f);
	circle1Rigi->setMass(5);
	circle1Rigi->setEnabled(true);
	addEntity(m_circle1);

	// Set up circle 2
	m_circle2 = new GameEngine::Entity();
	m_circle2->getTransform()->setLocalScale({ 40, 40 });
	m_circle2->getTransform()->setLocalPosition({ 600, 100 });
	m_circle2->addComponent<GameGraphics::ShapeComponent>()
		->setShapeType(GameGraphics::CIRCLE);
	m_circle2->addComponent(new GamePhysics::CircleColliderComponent(50));
	GamePhysics::RigidBodyComponent* circle2Rigi = m_circle2->addComponent(new GamePhysics::RigidBodyComponent());
	circle2Rigi->setGravity(9.18f);
	circle2Rigi->setMass(3);
	circle2Rigi->setEnabled(true);


	addEntity(m_circle2);

	// Set up floor
	m_floor = new GameEngine::Entity();
	m_floor->getTransform()->setLocalScale({ 1000, 100 });
	m_floor->getTransform()->setLocalPosition({ 400, 750 });
	m_floor->addComponent<GameGraphics::ShapeComponent>()
		->setShapeType(GameGraphics::BOX);
	m_floor->addComponent(new GamePhysics::AABBColliderComponent(1010, 110));
	GamePhysics::RigidBodyComponent* floorRigi = m_floor->addComponent(new GamePhysics::RigidBodyComponent());
	floorRigi->setGravity(0);
	floorRigi->setMass(20);
	floorRigi->setEnabled(true);
	addEntity(m_floor);
}

void TestScene::onUpdate(double deltaTime)
{

}
