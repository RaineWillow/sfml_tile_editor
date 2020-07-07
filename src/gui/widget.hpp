#ifndef Widget_hpp
#define Widget_hpp
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include <map>
#include <iterator>
#include <algorithm>
#include "../utils/functor.hpp"
#include "widget_base.hpp"

template <typename ClassType, typename Result>
class Widget : public WidgetBase
{
	typedef Result (ClassType::*FunctionType)(Widget*);
public:
	virtual ~Widget() {
		for (auto const& x : _eventList) {
			delete x.second;
		}
	}

	virtual bool update(WidgetData * data, sf::RenderTexture * texture)=0;
	virtual void render(sf::RenderTexture * renderOut)=0;

	void registerEvent(std::string qKey, ClassType& object, FunctionType method) {
		if (_eventList.find(qKey) == _eventList.end()) {
			Functor<ClassType, Result, Widget> * newEvent;
			newEvent = new Functor<ClassType, Result, Widget>(object, method);
			_eventList.insert({ qKey, newEvent });
		} else {
			std::cout << "Event is already added to the list\n";
		}
	}

	void callEvent(std::string qKey) {
		if (_eventList.find(qKey) == _eventList.end()) {
			std::cout << "Event does not exist!\n";
		} else {
			_eventList[qKey]->invoke(this);
		}
	}


private:
	std::map<std::string,Functor<ClassType, Result, Widget>*> _eventList;
};

#endif
