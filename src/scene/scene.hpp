#ifndef Scene_hpp
#define Scene_hpp
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <vector>
#include <string>

struct SceneData {
	int id = 0;
	std::vector<std::string> args;
};

class Scene {
public:

	virtual void update(sf::RenderWindow & _window, sf::Event & event, bool happened)=0;
	virtual void render(sf::RenderWindow * _window)=0;

	SceneData run(sf::RenderWindow & _window) {
		_isActive = true;
		bool newEvent;
		while (_isActive) {
			sf::Event event;
			newEvent = _window.pollEvent(event);
			switch (event.type) {
				case sf::Event::Closed:
					_window.close();
					this->_isActive = false;
					this->_myDat.id = -1;
					break;
			}
			this->update(_window, event, newEvent);
			this->render(&_window);
			_window.display();
		}
	return _myDat;
	}

	bool _isActive = true;
	SceneData _myDat;
};

#endif
