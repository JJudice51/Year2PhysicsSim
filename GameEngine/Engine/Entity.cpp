#include "Entity.h"
#include "TransformComponent.h"

GameEngine::Entity::Entity()
{
	TransformComponent* transform = new TransformComponent();
	addComponent(transform);
	m_transform = transform;
}

void GameEngine::Entity::start()
{
	m_started = true;

	for (Component* component : m_components)
	{
		if (component->getEnabled())
			component->start();
	}

	onStart();
}

void GameEngine::Entity::update(double deltaTime)
{
	for (Component* component : m_components)
	{
		if (component->getEnabled())
			component->update(deltaTime);
	}

	onUpdate(deltaTime);
}

void GameEngine::Entity::fixedUpdate(float fixedDeltaTime)
{
	for (Component* component : m_components)
	{
		if (component->getEnabled())
			component->fixedUpdate(fixedDeltaTime);
	}

	onFixedUpdate(fixedDeltaTime);
}

void GameEngine::Entity::draw()
{
	for (Component* component : m_components)
	{
		if (component->getEnabled())
			component->draw();
	}
}

void GameEngine::Entity::end()
{
	for (Component* component : m_components)
	{
		component->end();
	}
	m_started = false;
	onEnd();
}

void GameEngine::Entity::addComponent(Component* component)
{
	component->setOwner(this);
	m_components.add(component);
}

void GameEngine::Entity::onCollisionEnter(GamePhysics::Collision* collision)
{
	for (Component* component : m_components)
		component->onCollisionEnter(collision);
}

void GameEngine::Entity::setEnabled(bool enabled)
{
	if (!m_enabled && enabled)
		onEnable();
	else if (m_enabled && !enabled)
		onDisable();

	m_enabled = enabled;
}
