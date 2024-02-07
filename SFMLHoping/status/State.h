#ifndef STATE_H
#define STATE_H

#include<vector>
#include<fstream>
#include<sstream>
#include<stack>
#include <map>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class State
{
private:
	//attributes
	sf::RenderWindow* window;
	std::vector<sf::Texture> textures;

public:

	// constructor / deconstructor
	State();
	virtual ~State();

	//virtual funcs
	virtual void update() = 0;
	virtual void render() = 0;

	virtual void endState() = 0;
	
};

#endif

