#ifndef ResourceManager_hpp
#define ResourceManager_hpp
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "SFML/Graphics.hpp"
#include "../utils/split.hpp"

struct RImg {
	sf::Texture tex;
	sf::Sprite spr;
};

class ResourceManager {
public:
	ResourceManager(std::string path);
	~ResourceManager();

	void loadTexture(int id, std::string path);

	sf::Font * getFont(int id);
	sf::Sprite getSprite(int id);

private:
	std::map<int, RImg*> _imgLists;
	std::map<int, sf::Font> _fontLists;
	std::string _path;
};
#endif
