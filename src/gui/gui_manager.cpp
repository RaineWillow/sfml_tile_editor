#include "gui_manager.hpp"

GuiManager::GuiManager(int w, int h, WidgetData * data) {
	_data = data;
	_guiTexture.create(w, h);

	_currTime = std::chrono::high_resolution_clock::now();
	std::chrono::milliseconds defDur(200);
	textDelay = defDur;
}

GuiManager::~GuiManager() {
	for (int i = 0; i < (int)_widgets.size(); i++) {
		delete _widgets[i];
	}
}

void GuiManager::registerWidget(WidgetBase * widget) {
	_widgets.push_back(widget);
}

int GuiManager::getNext() {
	return ++_lastId;
}

void GuiManager::recText(char myChar) {
	if (_data->textMode) {
		if (myChar != *"") {
			_data->lastText = myChar;
		} else {
			return;
		}

		auto newTime = std::chrono::high_resolution_clock::now();

		if ((!_data->textEntered)) {
			if (_lastChar != _data->lastText || _data->genUp) {
				_currTime = newTime;
				_data->textEntered = true;
			} else {
				auto elapsedTime(newTime-_currTime);
				if (std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(elapsedTime).count() > std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(textDelay).count())
				{
					_currTime = newTime;
					_data->textEntered = true;
				}
			}
		}
		_lastChar = _data->lastText;
	}
}

void GuiManager::update() {
	bool anyActive = false;
	for (int i = 0; i < (int)_widgets.size(); i++) {
		if (_widgets[i]->update(_data, &_guiTexture)) {
			anyActive = true;
		}
	}
	if (_data->textEntered) {
		_data->textEntered = false;
	}
	if ((_data->clicked) && (!anyActive)) {
		std::cout << "set false!\n";
		_data->setActive(-1);
		_data->textMode = false;
	}
}

sf::Sprite GuiManager::getRenderable() {
	_guiTexture.clear(sf::Color(0, 0, 0, 0));
	for (int i = 0; i < (int)_widgets.size(); i++) {
		_widgets[i]->render(&_guiTexture);
		_guiTexture.setView(_guiTexture.getDefaultView());
	}
	_guiTexture.display();
	sf::Sprite spr;
	spr.setTexture(_guiTexture.getTexture());

	return spr;
}
