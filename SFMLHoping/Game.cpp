#include"Game.h"
//initialization function
void Game::initWindow()
{
    /* Creating a game object using options menu in game.ini file  */
    
    //defult settings
    sf::VideoMode window_dimensions(800,600);
    std::string title = "RPG Game";
    unsigned fps = 120;
    bool vertical_sync_enabled = false;

    //load from the file
    std::ifstream window_config("./config/config.ini");
    if (window_config.is_open()) 
    {
        std::getline(window_config,title);
        window_config >> window_dimensions.width >> window_dimensions.height;
        window_config >> fps;
        window_config >> vertical_sync_enabled;
    }
    window_config.close();

    //set the settings
    this->window = new sf::RenderWindow(window_dimensions,title);
    this->window->setFramerateLimit(fps);
    this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initState()
{
    //this->states.push();
}

//constructor / deconstructor
Game::Game()
{
    this->initWindow();
}

Game::~Game()
{
	delete this->window;
}

// public functions

void Game::upDatedt()
{
    this->dt = this->dtClolck.restart().asSeconds();
    system("cls");
    std::cout << this->dt << std::endl;
}

void Game::updateSFMLEvents()
{
    sf::Event event;
    while (this->window->pollEvent(this->sfEvent))
    {
        if (this->sfEvent.type == sf::Event::Closed)
            this->window->close();
    }
}

void Game::update()
{
    this->updateSFMLEvents();
    if (!this->states.empty())
        this->states.top()->update();

}

void Game::render()
{
    this->window->clear();

    //Render items 
    if (!this->states.empty())
        this->states.top()->render();

    this->window->display();
}

void Game::run()
{
    while (this->window->isOpen())
    {
        this->upDatedt();
        this->update();
        this->render(); 
    }

}
