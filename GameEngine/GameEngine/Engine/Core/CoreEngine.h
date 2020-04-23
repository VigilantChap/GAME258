#ifndef COREENGINE_H
#define COREENGINE_H

#include <memory.h>
#include "Window.h"
#include "Timer.h"
#include "Debug.h"
#include "GameInterface.h"
#include "Scene.h"
#include "../Rendering/3D/GameObject.h"
#include "../Rendering/SceneGraph.h."
#include "../Graphics/ShaderHandler.h"
#include "../Graphics/TextureHandler.h"
#include "../Camera//Camera.h"
#include "../Events/EventListener.h"

class CoreEngine
{
public:
	//Disabling ability to duplicate a CoreEngine
	CoreEngine(const CoreEngine&) = delete;
	CoreEngine(CoreEngine&&) = delete;
	CoreEngine& operator =(const CoreEngine&) = delete;
	CoreEngine& operator =(CoreEngine&&) = delete;

	bool OnCreate(std::string name_, int width_, int height_);
	void Run();
	inline bool GetIsRunning() const { return isRunning; }
	inline glm::vec2 GetWindowSize() const { return glm::vec2(window->GetWidth(), window->GetHeight()); }

	//either creates an instance or returns the existing instance of the CoreEngine
	//ensures only one can exist at any given time
	static CoreEngine* GetInstance();
	Camera* GetCamera() const;

	inline void SetCamera(Camera* camera_) { camera = camera_; }
	inline Camera* GetCamera() { return camera; }

	void SetGameInterface(GameInterface* gameInterface_);

	inline int GetSceneNum() { return currentSceneNum; }
	inline void SetSceneNum(int num) { currentSceneNum = num; }

	inline void Exit() { isRunning = false; }

	void NotifyOfMousePressed(glm::vec2 mouse_);
	void NotifyOfMouseRelease(glm::vec2 mouse_, int buttonType_);
	void NotifyOfMouseMove(glm::vec2 mouse_);
	void NotifyOfMouseScroll(int y_);

private:

	CoreEngine();
	~CoreEngine();

	static std::unique_ptr<CoreEngine> engineInstance;
	friend std::default_delete<CoreEngine>;
	
	void OnDestroy();
	void Update(const float deltaTime_);
	void Render();

	bool isRunning;
	Window* window;
	Camera* camera;

	Timer timer;
	unsigned int fps;
	
	GameInterface* gameInterface;

	int currentSceneNum;
	
};

#endif // !COREENGINE_H

