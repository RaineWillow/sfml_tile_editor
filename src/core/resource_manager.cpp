#include "resource_manager.hpp"

ResourceManager::ResourceManager(std::string path)
{
	_path = path;

	std::ifstream input_stream;
	input_stream.open(_path + "res_data.dat");

	if (input_stream.fail()) {
		std::cout << "failed to read\n";
		return;
	}
	std::string fLine;
	std::vector<std::string> lines;
	while (getline(input_stream, fLine)) {
		lines.push_back(fLine);
	}
	input_stream.close();

	int nextInstruct = 0;
	while (true) {
		if (lines[nextInstruct] == "imgs:") {
			for (size_t i = nextInstruct+1; i < lines.size(); i++) {
				if (lines[i] == "-") {
					nextInstruct = i+1;
					break;
				}
				Split myData(lines[i], " ");
				if (myData[0] == "//") {
					std::cout << "Comment: " << myData[1] << "\n";
				} else {
					std::cout << "Loading: " << myData[1] << "\n";
					loadTexture(std::stoi(myData[0]), myData[1]);
				}
			}
		} else if (lines[nextInstruct] == "fonts:")  {
			for (size_t i = nextInstruct+1; i < lines.size(); i++) {
				if (lines[i] == "-") {
					nextInstruct = i+1;
					break;
				}
				Split myData(lines[i], " ");
				if (myData[0] == "//") {
					std::cout << "Comment: " << myData[1] << "\n";
				} else {
					std::cout << "Loading: " << myData[1] << "\n";
					sf::Font font;
					_fontLists.insert({std::stoi(myData[0]), font});
					if (!_fontLists[std::stoi(myData[0])].loadFromFile(_path + myData[1])) {
						std::cout << "Failed to load Font: " << myData[1] << "\n";
					}

				}
			}
		} else if (lines[nextInstruct] == "end") {
			break;
		} else {
			std::cout << "Recieved unexpected input in Resource Manager. Line number " << nextInstruct << ": " << lines[nextInstruct] << "\n";
			break;
		}
	}

}

ResourceManager::~ResourceManager()
{
	for (auto const& x : _imgLists) {
		delete x.second;
	}
}

void ResourceManager::loadTexture(int id, std::string path)
{
	std::string myPath = _path + path;
	RImg * myImg = new RImg;

	if (!myImg->tex.loadFromFile(myPath))
	{
		std::cout << "Error loading:" << myPath << "\n";
		return;
	}

	myImg->spr.setTexture(myImg->tex);

	_imgLists.insert({id, myImg});
	return;
}

sf::Font * ResourceManager::getFont(int id) {
	return &_fontLists[id];
}

sf::Sprite ResourceManager::getSprite(int id)
{
	return _imgLists[id]->spr;
}
