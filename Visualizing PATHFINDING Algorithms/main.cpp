#include "Grid.h"
#include "Menu.h"

                            
//------------------ Global variables ( default values )------------------ 
sf::VideoMode screen(1250,850);
	//grid variables
int gridX = 48 , gridY = 28;
float sqr = 25 , sqrOuterLineThick = 2.5;


// ------------------functions------------------
bool mouseInWindow(sf::Vector2i & ms_lc,sf::RenderWindow & window) {
	return 	    ms_lc.x >= window.getPosition().x  &&  ms_lc.x <= window.getPosition().x + window.getSize().x
		    && 
				ms_lc.y >= window.getPosition().y  &&  ms_lc.y <= window.getPosition().y + window.getSize().y;
}

void menu(sf::RenderWindow& window) {
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
		
		}

	}
}

// ------------------ main ------------------
int main()
{
	sf::RenderWindow window(screen,"visualizing PATHFinding Algos");
	window.setFramerateLimit(30);

	//Create the grid 
	Grid grid(gridX,gridY,sqr,sqrOuterLineThick);

	//mouse location variables
	sf::Vector2i ms_lc;
	//change the state using keybaord
	bool red = 1, dir = 0 , deletefunc = 0, dfs=false;
	while (window.isOpen())
	{
		//------------------events handrling ------------------
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
				window.close();
			if (event.key.code == sf::Keyboard::Num1) {
				red = true, dir = false, deletefunc = false;
				std::cout << "select Red walls  \n";
			}
			if (event.key.code == sf::Keyboard::Num2) {
				red = false, dir = true , deletefunc =false;
				std::cout << "select start or end  \n";
			}
			if (event.key.code == sf::Keyboard::Num3) {
				red = false, dir = false, deletefunc = true;
				std::cout << "delete cell  \n";
			}
		}

		// ------------------UPDATE------------------
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			ms_lc = sf::Mouse::getPosition();
			 if (mouseInWindow(ms_lc, window)) {
						
				 if (dir)
				 {
					 sf::Vector2i windowpos = window.getPosition();
					 grid.StartOrEnd(ms_lc, windowpos);
				 }
				 else if(red)
				 {
					 sf::Vector2i windowpos = window.getPosition();
					 grid.buildRedSqr(ms_lc, windowpos);
				 }
				 else if (deletefunc)
				 {
					 sf::Vector2i windowpos = window.getPosition();
					 grid.delet(ms_lc, windowpos);
				 }
			 }
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) 
		{
			std::cout << "START DFS\n";
			grid.DFS(window);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) 
		{
			std::cout << "START BFS\n";
			grid.BFS(window);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)) 
		{
			std::cout << "reset grid\n";
			grid.resetGrid();
		}
		//------------------ DISPLAY------------------
		window.clear(sf::Color::White);		
		grid.drawGrid(window);
		window.display();
	}

}