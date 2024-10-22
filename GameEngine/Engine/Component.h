#pragma once

namespace GamePhysics
{
	class Collision;
	class ColliderComponent;
}

namespace GameEngine
{
	class Entity;
	class Component
	{
	public:
		Component() : m_enabled(true), m_owner(nullptr) {}

		virtual void start() {}
		virtual void update(double deltaTime) {}
		virtual void fixedUpdate(float fixedDeltaTime) {}
		virtual void draw() {}
		virtual void end() {}
		virtual void onEnable() {}
		virtual void onDisable() {}
		virtual void onCollisionEnter(GamePhysics::Collision* other) {}

		bool getEnabled() { return m_enabled; }
		void setEnabled(bool enabled);

		Entity* getOwner();
		void setOwner(Entity* entity);

	private:
		bool m_enabled;
		Entity* m_owner;
	};
}