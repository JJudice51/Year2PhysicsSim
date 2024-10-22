#include "Engine/Engine.h"
#include "TestScene.h"

int main(int argc, char* argv[])
{
	GameEngine::Engine engine = GameEngine::Engine();

	TestScene* scene = new TestScene();

	engine.setCurrentScene(scene);
	engine.run();

	return 0;
}