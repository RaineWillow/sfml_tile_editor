#ifndef Tile_Editor_hpp
#define Tile_Editor_hpp
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "../core/resource_manager.hpp"
#include "../utils/controller.hpp"
#include "../gui/gui_manager.hpp"
#include "../gui/widget_base.hpp"
#include "../gui/widget.hpp"
#include "../gui/g_button.hpp"
#include "../gui/g_textbox.hpp"
#include "../gui/g_menu.hpp"
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include "scene.hpp"

class TileEditor : public Scene {
public:
	TileEditor(ResourceManager * resMan);
	~TileEditor();

	void update(sf::RenderWindow & _window, sf::Event & event, bool happened);
	void render(sf::RenderWindow * _window);

	void onBClick(Widget<TileEditor, void> * instance);
	void onBHover(Widget<TileEditor, void> * instance);
	void onBLeave(Widget<TileEditor, void> * instance);
private:
	ResourceManager * _resManager;
	GuiManager * _guiManager;
	Controller * _controller;
	WidgetData * _data;
	GMenu<TileEditor, void> * _tileMenu;
};

#endif
