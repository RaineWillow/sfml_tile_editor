#ifndef Widget_Base_hpp
#define Widget_Base_hpp
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

struct WidgetData {
	int mx;
	int my;
	bool mMoved = false;

	int active = -1;
	int lastActive = -1;
	int hover = -1;
	int lastHover = -1;
	bool clicked = false;
	void setActive(int id) {
		lastActive = active;
		active = id;
	}
	void setHover(int id) {
		lastHover = hover;
		hover = id;
	}

	bool textMode = false;
	bool textEntered = false;
	bool backSpace = false;
	bool genUp = false;
	char lastText;

	int mDelta = 0;
};

class WidgetBase {
public:
	virtual bool update(WidgetData * data, sf::RenderTexture * texture)=0;
	virtual void render(sf::RenderTexture * renderOut)=0;

	int scrollOffsetX = 0;
	int scrollOffsetY = 0;

	int menuOffsetX = 0;
	int menuOffsetY = 0;

	int _x;
	int _y;

	sf::View * useView = nullptr;
};

#endif
