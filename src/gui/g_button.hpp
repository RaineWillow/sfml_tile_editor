#ifndef G_Button_hpp
#define G_Button_hpp
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "widget_base.hpp"
#include "widget.hpp"
#include <string>

template <typename ClassType, typename Result>
class GButton : public Widget<ClassType, Result>
{
	typedef Result (ClassType::*FunctionType)(Widget<ClassType,Result>*);
public:
	GButton(int id, int x, int y, double w, double h)
	{
		_id = id;
		this->_x = x;
		this->_y = y;
		_w = w;
		_h = h;
		wBox.setPosition(sf::Vector2f(this->_x, this->_y));
		wBox.setSize(sf::Vector2f(_w, _h));
		wBox.setFillColor(sf::Color(40, 75, 145, 250));
	}

	void useSprite(sf::Sprite setSprite) {
		widgetSprite = setSprite;
		this->widgetSprite.setPosition(this->_x, this->_y);
		this->widgetSprite.setScale(_w / this->widgetSprite.getTextureRect().width, _h / this->widgetSprite.getTextureRect().height);
		this->widgetSprite.setColor(sf::Color(255, 255, 255, 200));
		_useSprite = true;
	}

	bool update(WidgetData * data, sf::RenderTexture * texture)
	{
		sf::Vector2i loc(this->_x - this->scrollOffsetX + this->menuOffsetX, this->_y - this->scrollOffsetY + this->menuOffsetY);

		sf::Vector2f wLoc = texture->mapPixelToCoords(loc);

		if (((((data->mx >= wLoc.x) && (data->mx <= wLoc.x+_w)) && ((data->my >= wLoc.y) && (data->my <= wLoc.y+_h))))) {
			data->setHover(_id);

			if (data->clicked) {
				data->setActive(_id);
				this->callEvent("onClick");
				_active = true;
			}

			if ((!_wasHover) && (data->mMoved)) {
				_wasHover = true;
				this->callEvent("onHover");
			}

		} else {
			if (data->clicked) {
				_active = false;
			}

			if ((_wasHover) && (data->mMoved)) {
				this->callEvent("onLeft");
				_wasHover = false;
			}
		}

		if ((data->active == _id) && (!_wasActive)) {
			_wasActive = true;
		} else if ((data->active != _id) && (_wasActive)) {
			_wasActive = false;
		}

		return _active;
	}

	void render(sf::RenderTexture * renderOut) {
		if (_useShape) {
			renderOut->draw(wBox);
		}

		if (_useSprite) {
			renderOut->draw(widgetSprite);
		}

		if (_drawText) {
			title.setOrigin(title.getLocalBounds().width/2, title.getLocalBounds().height/2);
			title.setPosition(this->_x+_w/2, this->_y+_h/2);
			renderOut->draw(title);
		}

	}

	void addTitle(std::string myTitle, sf::Font * font, sf::Color color) {
		_drawText = true;
		title.setFont(*font);
		title.setString(myTitle);
		title.setCharacterSize(_h/2);
		title.setFillColor(color);
	}

	int getId() {
		return _id;
	}

	sf::Sprite widgetSprite;
	sf::RectangleShape wBox;
	sf::Text title;

private:
	int _id;
	bool _wasActive = false;
	bool _wasHover = false;

	double _w;
	double _h;

	bool _useSprite = false;

	bool _useShape = true;

	bool _drawText = false;

	bool _active = false;

};


#endif
