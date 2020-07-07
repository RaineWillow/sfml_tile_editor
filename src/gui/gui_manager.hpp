#ifndef Gui_Manager_hpp
#define Gui_Manager_hpp
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "widget_base.hpp"
#include <iostream>
#include <chrono>
#include <vector>

class GuiManager {
public:
	GuiManager(int w, int h, WidgetData * data);
	~GuiManager();

	void registerWidget(WidgetBase * widget);
	int getNext();

	void recText(char myChar);

	void update();
	sf::Sprite getRenderable();

	std::chrono::milliseconds textDelay;

private:
	WidgetData * _data;
	std::vector<WidgetBase*> _widgets;
	sf::RenderTexture _guiTexture;
	std::chrono::time_point<std::chrono::high_resolution_clock> _currTime;
	int _lastId = 0;
	char _lastChar;
};


#endif
