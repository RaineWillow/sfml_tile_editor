#ifndef Window_hpp
#define Window_hpp
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "../scene/scene.hpp"
#include "../scene/tile_editor.hpp"
#include "resource_manager.hpp"
#include <string>
#include <iostream>
#include <map>
#include <iterator>
#include <algorithm>

class Window {
public:
	Window(int w, int h, std::string title);
	~Window();
	void run();
private:
	sf::RenderWindow * _window;
	ResourceManager * _resManager;
	bool _isRunning = true;
	bool _doingScenes;
	std::map<int, Scene *> _scenes;
};

#endif
