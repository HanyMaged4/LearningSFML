#include <SFML/Graphics.hpp>
#include <iostream>
#include<queue>
const short dx[] = { -1, 0, 0, 1 };
const short dy[] = { 0, -1, 1, 0 };
const float speed = 0.03f; // using in (draw - BFS - DFS) 

class Grid
{
private:
	bool start;
	bool end;
	int gridX;
	int  gridY;
	float sqr;
	float sqrOuterLineThick;
	
	//start and end indexes
	std::pair<int, int> S, E;
	std::vector<std::vector<sf::RectangleShape>>grid;
	std::vector<std::vector<char>>gridState;
	/*
	* grid state
	* No State => ''
	* Red =>R
	* Start=> S
	* end =>E
	*/
public:
	Grid(int x, int y, float sqrlen, float sqrouter) {
		this->gridX = x;
		this->gridY = y;
		this->sqr = sqrlen;
		start = end = false;

		this->sqrOuterLineThick = sqrouter;
		//Create the grid 
		for (int i = 0; i < gridX; i++)
		{
			std::vector<sf::RectangleShape>tmp;
			for (int j = 0; j < gridY; j++)
			{
				sf::RectangleShape rec(sf::Vector2f(sqr - sqrOuterLineThick, sqr - sqrOuterLineThick));
				rec.setOutlineColor(sf::Color::Black);
				rec.setOutlineThickness(sqrOuterLineThick);
				rec.setPosition((i + 1) * sqr, (j + 1) * sqr);
				tmp.push_back(rec);
			}
			this->grid.push_back(tmp);
		}
		//create the grid state
		gridState = std::vector<std::vector<char>>(gridX, std::vector<char>(gridY, ' '));
	}
	void resetGrid() {
		gridState = std::vector<std::vector<char>>(gridX, std::vector<char>(gridY, ' '));
		for (int i = 0; i < gridX; i++)
			for (int j = 0; j < gridY; j++)			
				if(grid[i][j].getFillColor() != (sf::Color::White))
					grid[i][j].setFillColor(sf::Color::White);
		S = E = { -1,-1 };
		end = false;
		start = false;

	}
	 
	//------------------draw functions------------------
	void drawGrid(sf::RenderWindow& window)
	{
		for (int i = 0; i < gridX; i++)
			for (int j = 0; j < gridY; j++)
				window.draw(grid[i][j]);
	}
	
	void addRedLine(sf::Vector2i ms_ps, sf::Vector2i ms_ps2, sf::Vector2i& window)
	{
		int gx = static_cast<int>(std::ceil((ms_ps.x - window.x - grid[0][0].getPosition().x) / 25.0) - 1);
		int gy = static_cast<int>(std::ceil((ms_ps.y - window.y - grid[0][0].getPosition().y) / 25.0) - 2);
		if (gy >= 0 && gy < this->gridY && gx >= 0 && gx < this->gridX)
		{ 
			if (gridState[gx][gy] != ' ') {
				std::cout << "Grid state at position (" << gy << ", " << gx << "): " << gridState[gx][gy] << std::endl;
			}
			else {
				grid[gx][gy].setFillColor(sf::Color::Red);
				gridState[gx][gy] = 'R';
			}
		}
		else
			std::cout << "Invalid grid position (" << gy << ", " << gx << ")" << std::endl;
	}
	void StartOrEnd(sf::Vector2i ms_ps, sf::Vector2i& window)
	{
		int gx = static_cast<int>(std::ceil((ms_ps.x - window.x - grid[0][0].getPosition().x) / 25.0) - 1);
		int gy = static_cast<int>(std::ceil((ms_ps.y - window.y - grid[0][0].getPosition().y) / 25.0) - 2);
		if (gy >= 0 && gy < this->gridY && gx >= 0 && gx < this->gridX)
		{
			if (!start && gridState[gx][gy] != 'E') {
				grid[gx][gy].setFillColor(sf::Color::Green);
				gridState[gx][gy] = 'S';
				S.first = gx, S.second = gy;
				start = true;
			}
			else if(!end && gridState[gx][gy] !='S') {
				grid[gx][gy].setFillColor(sf::Color::Cyan);
				gridState[gx][gy] = 'E';
				E.first = gx, E.second = gy;
				end = true;
			}
			else {
				std::cout << "you have start and end delet one of them first to use this function \n";
			}
		}
		else
			std::cout << "Invalid grid position (" << gy << ", " << gx << ")" << std::endl;
	}
	void delet(sf::Vector2i ms_ps, sf::Vector2i& window) 
	{
		int gx = static_cast<int>(std::ceil((ms_ps.x - window.x - grid[0][0].getPosition().x) / 25.0) - 1);
		int gy = static_cast<int>(std::ceil((ms_ps.y - window.y - grid[0][0].getPosition().y) / 25.0) - 2);
		if (gy >= 0 && gy < this->gridY && gx >= 0 && gx < this->gridX)
		{
			if (gridState[gx][gy] == ' ')
				std::cout << "empty cell \n";
			else if (gridState[gx][gy] == 'R'){ 
				grid[gx][gy].setFillColor(sf::Color::White);
				gridState[gx][gy] = ' ';
			}
			else {
				grid[gx][gy].setFillColor(sf::Color::White);
				if (gridState[gx][gy] == 'S') {
					S = { -1,-1 };
					start = false;
				}
				else {
					E = { -1,-1 };
					end = false;
				}
				gridState[gx][gy] = ' ';
			}
		}
		else
			std::cout << "Invalid grid position (" << gy << ", " << gx << ")" << std::endl;
	}
	
	//------------------graph algo------------------
	void BFS(sf::RenderWindow& window) 
	{
		int childnum = 0;
		if (S.first == -1 || S.second == -1 || E.first == -1 || E.second == -1)
		{
			std::cout << "start or end does not exist yet\n";
			return;
		}

		int x = S.first, y = S.second;

		std::queue<std::pair<int, int>> que;
		std::vector<std::vector<std::pair<int, int>>> parent(gridX, std::vector < std::pair<int, int>>(gridY));

		que.push({ x,y });
		while (!que.empty())
		{
			int xx = que.front().first;
			int yy = que.front().second;
			que.pop();
			for (int i = 0; i < 4; i++) 
			{
				int nx = xx + dx[i];
				int ny = yy+ dy[i];
				if (nx >= 0 && nx < this->gridX && ny >= 0 && ny < this->gridY 
					&& (gridState[nx][ny] == ' '|| gridState[nx][ny] == 'E'))
				{
					parent[nx][ny] = { xx,yy };

					if (nx == E.first && ny == E.second) 
					{
						std::cout << "Found it using BFS :> " << std::endl;
						int targetx = E.first, targety = E.second;
						while (parent[targetx][targety] != std::make_pair(S.first, S.second))
						{
							this->grid[targetx][targety].setFillColor(sf::Color::Cyan);
							this->drawGrid(window);
							window.display();
							targetx = parent[targetx][targety].first;
							targety = parent[targetx][targety].second;
						}
						this->grid[S.first][S.second].setFillColor(sf::Color::Cyan);
						this->drawGrid(window);
						window.display();
						return;

					}

					gridState[nx][ny] = 'V';
					this->grid[nx][ny].setFillColor(sf::Color::Magenta);
					this->drawGrid(window);
					window.display();
					que.push({ nx,ny }); 

				}
			}
		}
		std::cout << "NOT Found :<" << std::endl;

	}

	bool helperDFS(int x, int y, sf::RenderWindow & window)
	{
	//	std::cout << x << " " << y << "\n";
	//	if (S.first == -1 || S.second == -1 || E.first == -1 || E.second == -1)
	//	{
	//		std::cout << "Start or end does not exist yet\n";
	//		return false;
	//	}

	//	if ((x < 0 || x >= this->gridX) || (y < 0 || y >= this->gridY) || gridState[x][y] == 'R' || gridState[x][y] == 'V')
	//		return false;

	//	if (x == E.first && y == E.second) 
	//	{
	//		std::cout << "Found it :> " << std::endl;
	//		return true;
	//	}
	//	gridState[x][y] = 'V';
	//	this->drawGrid(window);
	//	window.display();
	//	//drawGrid(window);
	//	sf::sleep(sf::seconds(speed));
	//	this->grid[x][y].setFillColor(sf::Color::Green);
	//	for (int i = 0; i < 4; i++) {
	//		int nx = x + dx[i];
	//		int ny = y + dy[i];
	//		if (nx >= 0 && nx < this->gridX && ny >= 0 && ny < this->gridY && gridState[nx][ny] != 'V' && gridState[nx][ny] != 'R')
	//		{
	//			if (helperDFS(nx, ny, window))
	//				return true;
	//		}
	//	}
	//	return false;
	//}
	//void DFS(sf::RenderWindow& window) {
	//	if (helperDFS(S.first, S.second, window))
	//		std::cout << "we did it :)\n";
	//	else
	//		std::cout << " shit \n";
	}
};

