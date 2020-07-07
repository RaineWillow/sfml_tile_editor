#ifndef G_Menu_hpp
#define G_Menu_hpp
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "widget_base.hpp"
#include "widget.hpp"
#include <string>
#include <vector>

template <typename ClassType, typename Result>
class GMenu : public Widget<ClassType, Result>
{
	typedef Result (ClassType::*FunctionType)(Widget<ClassType,Result>*);
public:
	GMenu(int id, int x, int y, double w, double h, double widgetHeight) {
		_id = id;
		this->_x = x;
		this->_y = y;
		_w = w;
		_h = h;

		_widgetHeight = widgetHeight;

		wBox.setPosition(sf::Vector2f(this->_x, this->_y));
		wBox.setSize(sf::Vector2f(_w, _h));
		wBox.setFillColor(sf::Color(10, 20, 30, 250));

		scrollBarBack.setPosition(sf::Vector2f((this->_x + _w) - (_w/20), this->_y));
		scrollBarBack.setSize(sf::Vector2f(_w/20, _h));
		scrollBarBack.setFillColor(sf::Color(30, 30, 30));

		scrollBar.setPosition(sf::Vector2f((this->_x + _w) - (_w/20), this->_y));
		scrollBar.setSize(sf::Vector2f(_w/20, _h));
		scrollBar.setFillColor(sf::Color(100, 110, 190));

		_widgetView.reset(sf::FloatRect(this->_x, this->_y, _w, _h));

		_widgetView.setCenter(_w/2, _h/2);

	}

	~GMenu() {
		for (int i = 0; i < (int)_widgets.size(); i++) {
			delete _widgets[i];
		}
	}

	void useSprite(sf::Sprite setSprite) {
		widgetSprite = setSprite;
		this->widgetSprite.setPosition(this->_x, this->_y);
		this->widgetSprite.setScale(_w / this->widgetSprite.getTextureRect().width, _h / this->widgetSprite.getTextureRect().height);
		this->widgetSprite.setColor(sf::Color(255, 255, 255, 200));
		_useSprite = true;
	}

	void addTitle(std::string myTitle, sf::Font * font, sf::Color color) {
		_drawTitle = true;
		title.setFont(*font);
		title.setString(myTitle);
		title.setCharacterSize(_h/2);
		title.setFillColor(color);
	}

	void setScrollable() {
		_scrollable = true;
	}

	bool update(WidgetData * data, sf::RenderTexture * texture)
	{
		sf::Vector2i loc(this->_x - this->scrollOffsetX, this->_y - this->scrollOffsetY);

		sf::Vector2f wLoc = texture->mapPixelToCoords(loc);

		double scrollHeight = _lastHeight - _h;
		if (_scrollable) {
			double calc = (double)_h/(double)_lastHeight;
			scrollBar.setSize(sf::Vector2f(_w/20, _h * calc));
			scrollBar.setPosition(sf::Vector2f((this->_x + _w) - (_w/20), this->_y + (_scrollerOffset * calc)));
		}

		if (scrollHeight < 0) {
			_scrollable = false;
		} else if (scrollHeight > 0) {
			_scrollable = true;
		}

		if (((((data->mx >= wLoc.x) && (data->mx <= wLoc.x+_w)) && ((data->my >= wLoc.y) && (data->my <= wLoc.y+_h))))) {
			data->setHover(_id);

			if (data->clicked) {
				data->setActive(_id);
				this->callEvent("onClick");
				_active = true;

			}

			if (data->mDelta != 0 && _scrollable) {
				_scrollerOffset += (data->mDelta*-1) * (scrollHeight/8.0);
				if (_scrollerOffset < 0) {
					_scrollerOffset = 0;
				}
				if (_scrollerOffset > scrollHeight) {
					_scrollerOffset = scrollHeight;
				}
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

		for (int i = 0; i < (int)_widgets.size(); i++) {
			if (_widgets[i]->update(data, texture)) {
				_active = true;
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
		sf::Sprite texSprite;
		texSprite.setTexture(renderOut->getTexture());
		_widgetView.setViewport(sf::FloatRect((double)this->_x / (double)texSprite.getTextureRect().width, (double)this->_y / (double)texSprite.getTextureRect().height, _w / texSprite.getTextureRect().width, _h / texSprite.getTextureRect().height));
		if (_useShape) {
			renderOut->draw(wBox);
		}

		if (_useSprite) {
			renderOut->draw(widgetSprite);
		}

		if (_drawTitle) {
			title.setOrigin(title.getLocalBounds().width/2, title.getLocalBounds().height/2);
			title.setPosition(this->_x+4, this->_y+_h/2);
			renderOut->draw(title);
		}

		if (_scrollable) {
			renderOut->draw(scrollBarBack);
			renderOut->draw(scrollBar);
		}

		_widgetView.setCenter(_w/2, (_h/2) + _scrollerOffset);
		renderOut->setView(_widgetView);

		for (int i = 0; i < (int)_widgets.size(); i++) {
			_widgets[i]->scrollOffsetY = _scrollerOffset;
			_widgets[i]->menuOffsetX = this->_x;
			_widgets[i]->menuOffsetY = this->_y;
			_widgets[i]->render(renderOut);
		}
	}

	int getCenteredY(double height) {
		int returnVal = _lastHeight + _widgetHeight;
		_lastHeight += height + _widgetHeight;
		return returnVal;
	}

	int getCenteredX(double width) {
		return this->_x;
	}

	void registerWidget(WidgetBase * widget) {
		widget->useView = &_widgetView;
		_widgets.push_back(widget);
	}

	int getNext() {
		return (int)_widgets.size();
	}

	sf::Sprite widgetSprite;
	sf::RectangleShape wBox;
	sf::RectangleShape scrollBarBack;
	sf::RectangleShape scrollBar;
	sf::Text title;
private:
	int _id;
	bool _wasActive = false;
	bool _wasHover = false;

	double _w;
	double _h;

	int _scrollerOffset = 0;

	double _lastHeight;
	double _widgetHeight;

	bool _useSprite = false;

	bool _useShape = true;

	bool _drawTitle = false;

	bool _scrollable = false;

	std::vector<WidgetBase*> _widgets;

	sf::View _widgetView;

	bool _active;
};
#endif
