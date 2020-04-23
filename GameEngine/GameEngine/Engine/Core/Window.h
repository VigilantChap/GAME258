#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
#include <string>
#include <iostream>

class Window
{
private:
	void SetPreAttributes();
	void SetPostAttributes();

	int width, height;
	SDL_Window* window;
	SDL_GLContext context;

public:
	Window();
	~Window();

	bool OnCreate(std::string name_, int width_, int height_);
	void OnDestroy();

	inline int GetWidth() { return width; }
	inline int GetHeight() { return height; }
	inline SDL_Window* GetWindow() const { return window; }

};


#endif // !WINDOW_H