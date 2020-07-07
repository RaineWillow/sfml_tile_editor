#include "window.hpp"
Window::Window(int w, int h, std::string title) {
	_window = new sf::RenderWindow(sf::VideoMode(w, h), title);
	_window->setVerticalSyncEnabled(true);
	_window->setFramerateLimit(60);

	_resManager = new ResourceManager("res/");
	Scene * tileEditor = new TileEditor(_resManager);
	_scenes.insert(std::make_pair(1, tileEditor));

	_doingScenes = true;
}

Window::~Window() {
	delete _resManager;
	for (auto const& x : _scenes) {
		delete x.second;
	}
	delete _window;
}

void Window::run() {
	int currScene = 1;
	while (_doingScenes) {
		SceneData nextScene = _scenes[currScene]->run(*_window);
		if (nextScene.id == -1) {
			_window->close();
			_isRunning = false;
			_doingScenes = false;
		} else {
			if (_scenes.find(nextScene.id) == _scenes.end()) {
				std::cout << "Tried to access non-existent scene. " << nextScene.id << "\n";
				_doingScenes = false;
			} else {
				std::cout << "Changing to scene: " << nextScene.id << "\n";
				currScene = nextScene.id;
			}
		}
	}
}
