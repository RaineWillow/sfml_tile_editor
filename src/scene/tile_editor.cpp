#include "tile_editor.hpp"

TileEditor::TileEditor(ResourceManager * resMan) {
	_resManager = resMan;
	_data = new WidgetData;

	_guiManager = new GuiManager(800, 600, _data);
	_controller = new Controller;
	_controller->mbAdd(sf::Mouse::Left);

	_tileMenu = new GMenu<TileEditor, void>(_guiManager->getNext(), 600, 0, 200, 400, 30);
	_guiManager->registerWidget(_tileMenu);

	GButton<TileEditor, void> * newButton = new GButton<TileEditor, void>(_guiManager->getNext(), 600, 450, 200, 30);
	newButton->addTitle("Click to add Button!", _resManager->getFont(1), sf::Color(200, 200, 255));
	newButton->registerEvent("onClick", *this, &TileEditor::onBClick);
	newButton->registerEvent("onHover", *this, &TileEditor::onBHover);
	newButton->registerEvent("onLeft", *this, &TileEditor::onBLeave);

	_guiManager->registerWidget(newButton);

}

TileEditor::~TileEditor() {
	delete _data;
	delete _guiManager;
	delete _controller;
}

void TileEditor::update(sf::RenderWindow & _window, sf::Event & event, bool happened) {
	char newChar = *"";
	if (happened) {
		switch (event.type) {
			case sf::Event::KeyPressed:
				_controller->keyDown(event.key.code);
				break;
			case sf::Event::KeyReleased:
				_controller->keyUp(event.key.code);
				break;
			case sf::Event::MouseButtonPressed:
				_controller->mbDown(event.mouseButton.button);
				break;
			case sf::Event::MouseButtonReleased:
				_controller->mbUp(event.mouseButton.button);
				break;
			case sf::Event::MouseMoved:
				_controller->mouseMotion(event.mouseMove.x, event.mouseMove.y);
				break;
			case sf::Event::TextEntered:
				if (event.text.unicode < 128) {
					newChar = static_cast<char>(event.text.unicode);
				}
				break;
			case sf::Event::MouseWheelScrolled:
				_controller->mouseScrolled(event.mouseWheelScroll.delta);
				break;
		}
	}

	_data->mx = _controller->getMx();
	_data->my = _controller->getMy();

	_data->clicked = _controller->getMbClicked(sf::Mouse::Left);
	_data->mMoved = _controller->mMoved();
	_data->mDelta = _controller->mouseDelta();

	_guiManager->recText(newChar);
	_guiManager->update();

	if (_window.pollEvent(event)) {
		this->update(_window, event, true);
	}
}

void TileEditor::render(sf::RenderWindow * _window) {
	_window->clear(sf::Color::Black);
	_window->draw(_guiManager->getRenderable());
}

void TileEditor::onBClick(Widget<TileEditor, void> * instance) {
	GButton<TileEditor, void> * testButton = new GButton<TileEditor, void>(_guiManager->getNext(), 0, _tileMenu->getCenteredY(40), 100, 40);
	testButton->addTitle("New Test", _resManager->getFont(1), sf::Color(200, 200, 255));
	testButton->registerEvent("onHover", *this, &TileEditor::onBHover);
	testButton->registerEvent("onLeft", *this, &TileEditor::onBLeave);
	_tileMenu->registerWidget(testButton);
}

void TileEditor::onBHover(Widget<TileEditor, void> * instance) {
	GButton<TileEditor, void> * castContext = dynamic_cast<GButton<TileEditor, void>*>(instance);
	castContext->wBox.setFillColor(sf::Color(255, 255, 255, 255));
	castContext->title.setFillColor(sf::Color(50, 50, 50));
}

void TileEditor::onBLeave(Widget<TileEditor, void> * instance) {
	GButton<TileEditor, void> * castContext = dynamic_cast<GButton<TileEditor, void>*>(instance);
	castContext->wBox.setFillColor(sf::Color(40, 75, 145, 255));
	castContext->title.setFillColor(sf::Color(200, 200, 255));
}
