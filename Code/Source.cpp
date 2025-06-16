#include <SFML/Graphics.hpp>
#include "Maze.h"
#include <SFML/Audio.hpp>
using namespace sf;


/// WITH  WORKING INVENTORY CODE '''''''''''''''''''''''''''''''''''

void displayMaze(RenderWindow& window, const string& maze, int dim, Maze& MAZE)
{
    RectangleShape wall(Vector2f(40, 40));
    wall.setFillColor(Color::Blue);
    CircleShape Items(10);
    Items.setFillColor(Color::Yellow);
    Items.setOrigin(10, 10);

   


    for (int i = 0; i < dim; ++i)
    {
        for (int j = 0; j < dim; ++j)
        {
            if (maze[i * dim + j] == '1')
            {
                wall.setPosition(j * 40, i * 40);
                window.draw(wall);
            }

            else if (maze[i * dim + j] == 'K') //spawn pokeball
            {
                //Items.setPosition((j + 0.5) * 40, (i + 0.5) * 40);
             //   window.draw(Items);

                    // MAZE.treasures.values->sprite.setPosition((MAZE.treasures.values[i].y_pos + 0.5) * 40, (MAZE.treasures.values[i].x_pos + 0.5) * 40);
                    //  window.draw(MAZE.treasures.values[i].sprite);

                MAZE.pokeball->sprite.setPosition((j + 0.5) * 40, (i + 0.5) * 40);

                window.draw(MAZE.pokeball->sprite);

            }
            else if (maze[i * dim + j] == 'k') //spawn keys
            {
                MAZE.key->sprite.setPosition((j + 0.5) * 40, (i + 0.5) * 40);

                window.draw(MAZE.key->sprite);
            }

            else if (maze[i * dim + j] == 'S') // spawn swords
            {
                MAZE.sword->sprite.setPosition((j + 0.5) * 40, (i + 0.5) * 40);
                window.draw(MAZE.sword->sprite);
            }
            else if (maze[i * dim + j] == 'D') // spawn swords
            {
                MAZE.dragonball->sprite.setPosition((j + 0.5) * 40, (i + 0.5) * 40);
                window.draw(MAZE.dragonball->sprite);
            }
            else if (maze[i * dim + j] == 'F') // spawn finish
            {
                MAZE.exit->sprite.setPosition((j + 0.5) * 40, (i + 0.5) * 40);
                window.draw(MAZE.exit->sprite);
            }
            else if (maze[i * dim + j] == 'E') // spawn enemy
            {
                MAZE.enemy->sprite.setPosition((j + 0.5) * 40, (i + 0.5) * 40);
                window.draw(MAZE.enemy->sprite);
            }
        }
    }
}

int main()
{




    Maze MAZE(21);
    MAZE.generateMaze();
    string Mstring = MAZE.mazeToString();
    std::cout << "Generated Maze:" << std::endl;
    for (int i = 0; i < MAZE.dimentions; ++i)
    {
        for (int j = 0; j < MAZE.dimentions; ++j)
        {
            std::cout << Mstring[i * MAZE.dimentions + j] << " ";
        }
        std::cout << std::endl;
    }


    srand(time(0));
    //Maze maze(20);
    //maze.generateMaze();
    //cout << "Raw Maze:\n" << maze.getRawMaze() << endl;
    //cout << "Symbolic Maze:\n" << maze.getSymbolicMaze() << endl;

    

    RenderWindow window(VideoMode(MAZE.dimentions * 40 + 200, MAZE.dimentions * 40), "MAZE");
    window.setVerticalSyncEnabled(true);
    CircleShape Player(10); // 40/4
    Player.setFillColor(Color::Green);
    Player.setOrigin(10, 10);

    Texture menuTexture;
    menuTexture.loadFromFile("menuScreen.jpg");
    Texture GameCompletedTexture;
    GameCompletedTexture.loadFromFile("GameComplete.jpg");

    Sprite menuSprite(menuTexture);
    Sprite gameEndSprite(GameCompletedTexture);
    Texture gameOverTexture;
    gameOverTexture.loadFromFile("GameOver.jpg");
    Sprite gameOverSprite(gameOverTexture);
    menuSprite.setScale(0.88, 0.73);
    window.draw(menuSprite);
    window.display();

    bool gameStarted = false;

    // RenderWindow inventoryWindow(VideoMode(200, 600), "Inventory Window");

    bool flag = false;
    Font font;
    if (!font.loadFromFile("Sugar Quota.ttf")) {
        cout << "font NOT loaded" << endl;
    }
    Text inventoryText;
    inventoryText.setFont(font);
    inventoryText.setCharacterSize(20);
    inventoryText.setFillColor(Color::White);
   // inventoryText.setPosition(MAZE.dimentions*40 + 20, 0); // Adjust position as needed
    string inventoryString = "Inventory: ";
   // inventoryString += "\n";
    
    inventoryText.setString(inventoryString);
    inventoryText.setPosition(MAZE.dimentions * 40 + 20, 20);

    int score = 5;
    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(MAZE.dimentions * 40 + 20, 0);
    scoreText.setString("Score: 5");

    Music music;
    music.openFromFile("Ice-Path.ogg");
    music.play();
    music.setVolume(100);


    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Space) {
                    gameStarted = true;
                }
            }
        }

        if (gameStarted)
        {
            while (window.isOpen())
            {
                Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == Event::Closed)
                    {
                        window.close();
                    }

                    if (event.type == Event::KeyPressed)
                    {
                        if (event.key.code == sf::Keyboard::Up)
                            MAZE.movePlayer(-1, 0);
                        else if (event.key.code == sf::Keyboard::Down)
                            MAZE.movePlayer(1, 0);
                        else if (event.key.code == sf::Keyboard::Left)
                            MAZE.movePlayer(0, -1);
                        else if (event.key.code == sf::Keyboard::Right)
                            MAZE.movePlayer(0, 1);
                        else if (event.key.code == sf::Keyboard::I)
                        {
                            // cout << "WOOOOOOO";
                           // MAZE.player->inventory.inOrder(MAZE.player->inventory.root);
                        }
                    }


                }




                if (MAZE.TreasureCheck())
                {
                    Treasure treasureValue = MAZE.treasurePick2();
                    Mstring = MAZE.mazeToString();
                    MAZE.treasures.removeAt(MAZE.treasurePick());
                    inventoryString = "Inventory:\n";
                    MAZE.Player->inventory.inOrder(MAZE.Player->inventory.root, inventoryString);
                    // inventoryString += "\n";
                   //  inventoryText.setPosition(MAZE.dimentions * 40 + 20, -20 - z);
                    inventoryText.setString(inventoryString);
                    //  inventoryText.setPosition(MAZE.dimentions * 40 + 20, -20 + z);
                    //  window.draw(inventoryText);
                    score += treasureValue.value;
                    MAZE.Player->health = score;
                    string scoreString = "Score: " + to_string(score);
                    scoreText.setString(scoreString);
                    cout << "PLAYER HEALTH: " << MAZE.Player->health << endl;


                }

                if (MAZE.GameEnd())
                {
                    // end game
                    window.clear();
                    window.draw(gameEndSprite);
                    window.display();
                    break;
                }

                if (MAZE.PlayerDied())
                {
                    // YOU LOSE SCREEN
                    window.clear();
                    window.draw(gameOverSprite);
                    window.display();
                    break;
                }


                window.clear();

                if (!MAZE.KeyCheck())
                {
                    string path = MAZE.ShortestPath();
                    // Display the shortest path
                    for (int i = 0; i < MAZE.dimentions * MAZE.dimentions; ++i)
                    {
                        int x = i / MAZE.dimentions;
                        int y = i % MAZE.dimentions;
                        if (path[i] == 'X')
                        {
                            sf::CircleShape cir(5);
                            cir.setFillColor(sf::Color::Yellow);
                            cir.setPosition((y + 0.5) * 40 - 5, (x + 0.5) * 40 - 5);
                            window.draw(cir);
                        }
                    }
                }

                displayMaze(window, Mstring, MAZE.dimentions, MAZE);
                Player.setPosition((MAZE.Player->y_pos + 0.5) * 40, (MAZE.Player->x_pos + 0.5) * 40);
                window.draw(Player);
                window.draw(scoreText);
                window.draw(inventoryText);
                window.display();


            }
        }

    }

   

    


    return 0;

}