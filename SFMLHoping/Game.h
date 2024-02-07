#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <ctime>
#include "status/State.h"
class Game
{
private:
	//attributes
	sf::RenderWindow* window;
	sf::Event sfEvent;

	float dt; // delta time attribute
	sf::Clock dtClolck; 
	
	std::stack<State*> states;

	//initialization function
	void initWindow();
	void initState();

public:
	//constructor / deconstructor
	Game();
	virtual ~Game();

	// public functions
	void upDatedt();
	void updateSFMLEvents();
	void update();
	void render();
	void run();
};



#endif // !Game_H
