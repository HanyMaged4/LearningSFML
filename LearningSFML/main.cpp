#include <SFML/Graphics.hpp>
#include<iostream>
#include<random>

float speed = 15;
float enimyspeed = 12;
sf::Vector2f shootSize(10.f, 10.f);

void shootGo(std::vector<sf::RectangleShape>& shoots, sf::RenderWindow& window);
void enimyGo(std::vector<sf::RectangleShape>& enimy, sf::RenderWindow& window);

int main(){
    sf::RenderWindow window(sf::VideoMode(840, 600), "Learning SFML");
    window.setFramerateLimit(30);
    //loading fonts
    sf::Font font;
    font.loadFromFile("./assets/fonts/MouldyCheeseRegular-WyMWG.ttf");
    //creating the score
    sf::Text score("0", font);
    score.setPosition(8, 3);
    int scorenum =  1553117738;
    //create shapes 
    sf::RectangleShape player(sf::Vector2f(40, 40));
    float mouse_y_pos = window.getSize().y - player.getSize().y - 100;
    player.setPosition(player.getSize().x +15, mouse_y_pos);

    bool isShoot = false;
    std::vector<sf::RectangleShape>shoots;
    std::vector<sf::RectangleShape> enimies;

    sf::Clock clock;
    bool loose = false;
    while (window.isOpen()) 
    {
        sf::Time elapsed = clock.getElapsedTime();
        float elapsedSeconds = elapsed.asSeconds();

        if ((int)elapsedSeconds % 1 == 0 && enimies .size()<=2) {
            sf::RectangleShape tmpenimy(sf::Vector2f(40, 40));
            float randomNum = std::rand() % window.getSize().x - 40;
            tmpenimy.setPosition(randomNum, window.getSize().y / 6);
            tmpenimy.setFillColor(sf::Color::Red);
            enimies.push_back(tmpenimy);
        }
        sf::Event eve;
        while (window.pollEvent(eve))
        {
            if (eve.type == sf::Event::Closed)
                window.close();
            if (eve.type == sf::Event::KeyPressed && eve.key.code == sf::Keyboard::Escape)
               window.close();
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                isShoot =true;
        }
        //update
        sf::Vector2i windowPos = window.getPosition() , mousePos = sf::Mouse::getPosition();
        sf::Vector2f playerSize = player.getSize();
        sf::Vector2u windowSize = window.getSize();

        // check if the mouse in the program window
        if (mousePos.x - playerSize.x > windowPos.x && mousePos.y > windowPos.y + playerSize.y
            && mousePos.x < windowPos.x + windowSize.x && mousePos.y < windowPos.y + windowSize.y )
        {
            float mouse_x_pos = mousePos.x - windowPos.x - playerSize.x;
            player.setPosition(mouse_x_pos, mouse_y_pos);
            if (isShoot) {
                isShoot = false;
                sf::RectangleShape tmp(shootSize);
                tmp.setPosition(mouse_x_pos + (playerSize.x/2), mouse_y_pos);
                shoots.push_back(tmp);
            }
        }

        //check if there is a shoot that damage an enimy
        for (int i = 0; i < enimies.size(); i++) 
            for (int j = 0; j < shoots.size(); j++) 
                if (enimies[i].getGlobalBounds().intersects(shoots[j].getGlobalBounds()))
                {
                    enimies.erase(enimies.begin() + i);
                    shoots.erase(shoots.begin() + j);
                    scorenum++;
                    break;
                }
        // check game over
        for (int i = 0; i < enimies.size(); i++)
                if (enimies[i].getGlobalBounds().intersects(player.getGlobalBounds()))
                {
                    loose = true;
                    break;
                }
        window.clear();
        if (loose)
        {
            score.setString("Game Over\n");
            score.setCharacterSize(34);
            score.setPosition( (window.getSize().x - score.getGlobalBounds().width)/2,( window.getSize().y - score.getGlobalBounds().height) /2);
            enimies.clear();
            shoots.clear();
            player.setPosition(-1000, -1000);
        }

        else 
            score.setString("Score: " + std::to_string(scorenum));
        
        enimyGo(enimies, window);
        shootGo(shoots, window);
        window.draw(player);
        window.draw(score);
        window.display();
    }
    return 0;   
}

void shootGo(std::vector<sf::RectangleShape>& shoots, sf::RenderWindow& window) {
    for (int i = 0; i < shoots.size(); i++)
    {
        if (shoots[i].getPosition().y > 0)
        {
            shoots[i].move(0, -speed);
            window.draw(shoots[i]);
        }
        else
            shoots.erase(shoots.begin() + i);
    }
}
void enimyGo(std::vector<sf::RectangleShape>& enimy, sf::RenderWindow& window) {
    for (int i = 0; i < enimy.size(); i++)
    {
        if (enimy[i].getPosition().y < window.getSize().y)
        {
            enimy[i].move(0 , enimyspeed);
            window.draw(enimy[i]);
        }
        else
            enimy.erase(enimy.begin() + i);
    }
} 