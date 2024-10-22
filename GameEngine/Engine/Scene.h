#pragma once
#include "List.h"

namespace GamePhysics
{
	class Collision;
	class ColliderComponent;
}

namespace GameEngine
{
	class Entity;

	class Scene
	{
	public:
		Scene();

		void start();
		void update(double deltaTime);
		void fixedUpdate(float fixedDeltaTime);
		void draw();
		void end();

		virtual void onStart() {}
		virtual void onUpdate(double deltaTime) {}
		virtual void onFixedUpdate(float fixedDeltaTime) {}
		virtual void onDraw() {}
		virtual void onEnd() {}

		void addEntity(Entity* entity);
		void removeEntity(Entity* entity);

		void addActiveCollider(GamePhysics::ColliderComponent* collider) { m_activeColliders.add(collider); }
		void removeActiveCollider(GamePhysics::ColliderComponent* collider) { m_activeColliders.remove(collider); }

	private:
		List<GamePhysics::ColliderComponent*> m_activeColliders;
		List<Entity*> m_entities;
	};
}