#pragma once
//#include<iostream>
#include <stack>
#include <string>
#include <cstdlib>
#include <ctime>
#include "List.h"
#include "Player.h"
#include "Items.h"
#include <queue>
//using namespace std;

class Maze
{
public:

	int** maze;
	int dimentions;
	player *Player = new player("bob", 5);
	//Treasure* key = new Treasure("key", 5);

	

	PokeballSprite *pokeball = new PokeballSprite("pokeball.png");
	SwordSprite* sword = new SwordSprite("sword.png");
	KeySprite* key = new KeySprite("key.png");
	DragonBallSprite* dragonball = new DragonBallSprite();
	EnemySprite* enemy = new EnemySprite();
	Exit* exit = new Exit();
	
	//Treasure* keys[5];
	List<Treasure> treasures;
	Maze(int dim)
	{
		dimentions = dim;
		maze = new int* [dim];
		for (int i = 0; i < dim; ++i)
		{
			maze[i] = new int[dim];
		}

		for (int i = 0; i < dim; ++i)
		{
			for (int j = 0; j < dim; ++j)
			{
				maze[i][j] = 1;
			}
		}

	}

	void generateMaze()
	{
		srand(time(NULL));

		struct Cell
		{
			int x;
			int y;
			bool visited;
			Cell(int xx=1, int yy=1)
			{
				x = xx;
				y = yy;
				visited = false;
			}
		};

		List<Cell> frontier;
		
		frontier.insert(Cell(1, 1));

		while (!frontier.isEmpty())
		{
			int index = rand() % frontier.size();
			Cell current = frontier.values[index];
			frontier.removeAt(index);
			maze[current.x][current.y] = 0; // Mark the current cell as path

			// Randomly choose a neighboring cell that has all walls intact
		
			List<Cell> neighbors;
			if (current.x - 2 > 0 && maze[current.x - 2][current.y] == 1)
				neighbors.insert(Cell(current.x - 2, current.y));
			if (current.x + 2 < dimentions && maze[current.x + 2][current.y] == 1)
				neighbors.insert(Cell(current.x + 2, current.y));
			if (current.y - 2 > 0 && maze[current.x][current.y - 2] == 1)
				neighbors.insert(Cell(current.x, current.y - 2));
			if (current.y + 2 < dimentions && maze[current.x][current.y + 2] == 1)
				neighbors.insert(Cell(current.x, current.y + 2));
			//cout << neighbors.size() << " ";

			if (!neighbors.isEmpty())
			{
				int numConnections = rand() % neighbors.size() + 1;
				for (int i = 0; i < numConnections; ++i)
				{
					int nextIndex = rand() % neighbors.size();
					Cell next = neighbors.values[nextIndex];
					maze[next.x][next.y] = 0; // Mark the neighboring cell as path
					frontier.insert(Cell(next.x, next.y));

					// Mark the cell in between current and next as path
					maze[current.x + (next.x - current.x) / 2][current.y + (next.y - current.y) / 2] = 0;

					// Erase the chosen neighbor from the list
					
					neighbors.removeAt(nextIndex);
				}
			}
		}
		
		do
		{
			//Player->x_pos = rand() % dimentions;
			//Player->y_pos = rand() % dimentions;
			Player->x_pos = 1;
			Player->y_pos = 1;


		} while (maze[Player->x_pos][Player->y_pos] != 0);

		SpawnTreasure(3, "pokeball", 2, 3);
		SpawnTreasure(3, "sword", 3, 10);
		SpawnTreasure(3, "key", 4, 1);
		SpawnTreasure(1, "DragonBall", 5, 20);
		SpawnTreasure(5, "enemy", 6, -5);

		treasures.insert(Treasure("Exit", 0, dimentions - 2, dimentions - 2)); 
		
		maze[dimentions - 2][dimentions - 2] = -1; // for finish 
		
		
	}

	string mazeToString()
	{
		std::string mazeString = "";
		for (int i = 0; i < dimentions; ++i)
		{
			for (int j = 0; j < dimentions; ++j)
			{
				if (i == Player->x_pos && j == Player->y_pos)
				{
					mazeString += "P";
				}
				else if(maze[i][j] == 2) //check pokeball
				{
					//mazeString += std::to_string(maze[i][j]);
					mazeString += "K"; // capital K
				}
				else if (maze[i][j] == 3) //check sword
				{
					mazeString += "S";
				}
				else if (maze[i][j] == 4)// check key
				{
					mazeString += "k"; //small k
				}
				else if (maze[i][j] == 5)// check dragonball
				{
					mazeString += "D";
				}
				else if (maze[i][j] == 6) // check enemy
				{
					mazeString += "E";
				}
				else if (maze[i][j] == -1)
				{
					mazeString += "F"; // check Finish
				}
				else
				{
					mazeString += to_string(maze[i][j]);
				}

			}
		}
		return mazeString;
	}

	string ShortestPath()
	{
		const int INF = numeric_limits<int>::max();
		string path(dimentions * dimentions, ' ');
		int **parentX = new int*[dimentions];
		for (int i = 0; i < dimentions; ++i)
		{
			parentX[i] = new int[dimentions];
		}
		int** parentY = new int* [dimentions];
		for (int i = 0; i < dimentions; ++i)
		{
			parentY[i] = new int[dimentions];
		}
		int** dist = new int* [dimentions];
		for (int i = 0; i < dimentions; ++i)
		{
			dist[i] = new int[dimentions];
		}
		for (int i = 0; i < dimentions; ++i)
		{
			for (int j = 0; j < dimentions; ++j)
			{
				parentX[i][j] = -1;
				parentY[i][j] = -1;
				dist[i][j] = INF;
			}
		}
		dist[Player->x_pos][Player->y_pos] = 0;
		std::priority_queue<std::pair<int, std::pair<int, int>>> pq;
		pq.push(std::make_pair(0, std::make_pair(Player->x_pos, Player->y_pos)));
		
		int dx[] = { -1, 1, 0, 0 };
		int dy[] = { 0, 0, -1, 1 };

		while (!pq.empty())
		{
			int x = pq.top().second.first;
			int y = pq.top().second.second;
			pq.pop();

			for (int i = 0; i < 4; ++i)
			{
				int nx = x + dx[i];
				int ny = y + dy[i];

				if (nx >= 0 && nx < dimentions && ny >= 0 && ny < dimentions && maze[nx][ny] != 1)
				{
					int nd = dist[x][y] + 1;
					if (nd < dist[nx][ny])
					{
						dist[nx][ny] = nd;
						pq.push(std::make_pair(-nd, std::make_pair(nx, ny)));
						parentX[nx][ny] = x;
						parentY[nx][ny] = y;
					}
				}
			}
		}

		int x = dimentions - 2, y = dimentions - 2;
		while (x != -1 && y != -1)
		{
			path[x * dimentions + y] = 'X';
			int px = parentX[x][y];
			int py = parentY[x][y];
			x = px;
			y = py;
		}

		return path;
	}


	int treasurePick()
	{
		for (int i = 0; i < treasures.counter; ++i)
		{
			if (treasures.values[i].x_pos == Player->x_pos && treasures.values[i].y_pos == Player->y_pos)
			{
				cout << "Treasure Collected" << endl;
				//cout << "THIS NOT MAKING SENSE";
				if (treasures.values[i].name != "Exit" && treasures.values[i].value > 0)
				{
					cout << "YEAAAAAAAAAAA";
					Player->inventory.Insert(treasures.values[i]);
				}
				
				
				return i;
			}
		}
		cout << "Treasure Pick NOT WORKING" << endl;
		return -1;
	}

	Treasure treasurePick2()
	{
		for (int i = 0; i < treasures.counter; ++i)
		{
			if (treasures.values[i].x_pos == Player->x_pos && treasures.values[i].y_pos == Player->y_pos)
			{
				cout << "Treasure Collected" << endl;
				//cout << "THIS NOT MAKING SENSE";
				//player->inventory.Insert(treasures.values[i]);


				return treasures.values[i];
			}
		}
		cout << "Treasure Pick NOT WORKING" << endl;
		//return -1;
	}

	bool TreasureCheck()
	{
		for (int i = 0; i < treasures.counter; ++i)
		{
			if (treasures.values[i].x_pos == Player->x_pos && treasures.values[i].y_pos == Player->y_pos)
			{
				return true;
			}
		}
		return false;
	}

	bool GameEnd()
	{
		for (int i = 0; i < treasures.counter; ++i)
		{
			if (Player->x_pos == dimentions - 2 && Player->y_pos == dimentions-2)
			{
				return true;
			}
		}
		return false;
	}

	bool PlayerDied()
	{
		if (Player->health < 0)
		{

			return true;
		}
		return false;
	}

	bool KeyCheck()
	{
		for (int i = 0; i < treasures.counter; ++i)
		{
			
				if (treasures.values[i].value == 1) 
				{
					//cout << "KEYS EXIST";
					return true;
				}
			
		}
		//cout << "NO KEYS EXIsT";
		return false;
	}

	void movePlayer(int dx, int dy)
	{
		//float deltaTime = clock.restart().asSeconds();
		//float moveAmount = Player->speed * deltaTime;

		int newX = Player->x_pos + dx;
		int newY = Player->y_pos + dy;
		if (newX >= 0 && newX < dimentions && newY >= 0 && newY < dimentions && maze[newX][newY] == 0) // collision check
		{
			Player->x_pos = newX;
			Player->y_pos = newY;
		}
		else if (newX >= 0 && newX < dimentions && newY >= 0 && newY < dimentions && (maze[newX][newY] == 2 || maze[newX][newY] == 3 || maze[newX][newY] == 4 || maze[newX][newY] == 5 || maze[newX][newY] == 6)) // collision check
		{
			Player->x_pos = newX;
			Player->y_pos = newY;
			//Treasure temp = treasurePick();
			//treasures.removeAt(treasurePick());
			//cout << temp.name;
			//cout << "Treasure collected" << endl;
			maze[Player->x_pos][Player->y_pos] = 0;
			
		}
		else if (newX == dimentions-2 && newY == dimentions - 2) // check finish
		{
			if (!KeyCheck())
			{
				Player->x_pos = newX;
				Player->y_pos = newY;
			}
		}
		

	}


	void SpawnTreasure(int n, string name, int type, int score) // type: 2(poekball), 3(sword), 4(key)
	{
		for (int i = 0; i < n; ++i)
		{
			int x, y;
			do
			{
				x = rand() % dimentions;
				y = rand() % dimentions;
			} while (maze[x][y] > 0 && (x != 1 && y != 1) && (x!= dimentions -2 && y!= dimentions-2)); //&& (maze[x][y] != 2 && (maze[x][y] != 3  && maze[x][y] != 4 && maze[x])));
			cout << "X: " << x << endl;
			treasures.insert(Treasure(name + to_string(i + 1), score, x, y)); // "pokeball.png"));
			//keys[i] = new Treasure("key" + to_string(i + 1), 5, x, y, "pokeball.png");
			maze[x][y] = type;


		}
	}

};
