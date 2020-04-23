#ifndef GAME1_H
#define GAME1_H

#include "../Engine/Core/CoreEngine.h"

class Game1 : public GameInterface
{
public:
	Game1();
	virtual ~Game1();

	virtual bool OnCreate();
	virtual void Update(const float deltaTime_);
	virtual void Render();

private:
	Scene* currentScene;
	int currentSceneNum;
	void BuildScene();

};


#endif // !GAME1_H