#include "controller.hpp"

void Controller::keyAdd(sf::Keyboard::Key qKey) {
	if (_keyList.find(qKey) == _keyList.end()) {
		ButtonData data = {false, false};
		_keyList.insert({ qKey, data });
	} else {
		std::cout << "key is already watched!\n";
	}
}

void Controller::keyDown(sf::Keyboard::Key qKey) {
	if (_keyList.find(qKey) == _keyList.end()) {
		std::cout << "key input not in list of watched keys, add the key to the watched keys list\n";
	} else {
		_keyList[qKey].down = true;
	}
	_generic.down = true;
}

void Controller::keyUp(sf::Keyboard::Key qKey) {
	if (_keyList.find(qKey) == _keyList.end()) {
		std::cout << "key input not in list of watched keys, add the key to the watched keys list\n";
	} else {
		if (_keyList[qKey].down) {
			_keyList[qKey].clicked = true;
		}
		_keyList[qKey].down = false;
	}

	if (_generic.down) {
		_generic.clicked = true;
	}
	_generic.down = false;
}

bool Controller::getKey(sf::Keyboard::Key qKey) {
	if (_keyList.find(qKey) == _keyList.end()) {
		std::cout << "key input not in list of watched keys, add the key to the watched keys list\n";
	} else {
		return _keyList[qKey].down;
	}
	return false;
}

bool Controller::getKeyClicked(sf::Keyboard::Key qKey) {
	if (_keyList.find(qKey) == _keyList.end()) {
		std::cout << "key input not in list of watched keys, add the key to the watched keys list\n";
	} else {
		if (_keyList[qKey].clicked) {
			_keyList[qKey].clicked = false;
			return true;
		} else {
			return false;
		}
	}
	return false;
}

bool Controller::getGen() {
	return _generic.down;
}

bool Controller::getGenClicked() {
	if (_generic.clicked) {
		_generic.clicked = false;
		return true;
	} else {
		return false;
	}
	return false;
}


void Controller::mbAdd(sf::Mouse::Button mb) {
	if (_mbList.find(mb) == _mbList.end()) {
		ButtonData data = {false, false};
		_mbList.insert({ mb, data });
	} else {
		std::cout << "mouse button is already watched!\n";
	}
}

void Controller::mbDown(sf::Mouse::Button mb) {
	if (_mbList.find(mb) == _mbList.end()) {
		std::cout << "mouse button is not in list of watched buttons, add the button 1.\n";
	} else {
		_mbList[mb].down = true;
	}
}

void Controller::mbUp(sf::Mouse::Button mb) {
	if (_mbList.find(mb) == _mbList.end()) {
		std::cout << "mouse button is not in list of watched buttons, add the button 2.\n";
	} else {
		if (_mbList[mb].down == true) {
			_mbList[mb].clicked = true;
		}
		_mbList[mb].down = false;

	}
}

bool Controller::getMb(sf::Mouse::Button mb) {
	if (_mbList.find(mb) == _mbList.end()) {
		std::cout << "mouse button is not in list of watched buttons, add the button 3.\n";
	} else {
		return _mbList[mb].down;
	}
	return false;
}

bool Controller::getMbClicked(sf::Mouse::Button mb) {
	if (_mbList.find(mb) == _mbList.end()) {
		std::cout << "mouse button is not in list of watched buttons, add the button 4.\n";
	} else {
		if (_mbList[mb].clicked) {
			_mbList[mb].clicked = false;
			return true;
		} else {
			return false;
		}
	}
	return false;
}

void Controller::mouseMotion(int mx, int my){
	if ((mx != _mx) || my != _my) {
		_mMoved = true;
	}
	_mx = mx;
	_my = my;
}

void Controller::mouseScrolled(int delta) {
	_mouseDelta = delta;
}

int Controller::mouseDelta()
{
	if (_mouseDelta != 0) {
		int retVal = _mouseDelta;
		_mouseDelta = 0;
		return retVal;
	}
	return 0;
}

bool Controller::mMoved() {
	if (_mMoved) {
		_mMoved = false;
		return true;
	} else {
		return false;
	}
}

int Controller::getMx() {
	return _mx;
}

int Controller::getMy() {
	return _my;
}
