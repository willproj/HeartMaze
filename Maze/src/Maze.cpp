#include "Maze.h"

namespace maze
{
	Maze::Maze()
	{
		InitHeartMaze();
	}

	Maze::~Maze()
	{
	}

	void Maze::findWall()
	{
		if (m_Enclosure.find({ start_x + 1,start_y }) == m_Enclosure.end() && m_WallsMap[{start_x + 1, start_y}] == WALL)
		{
			m_WallsVec.push_back(Wall(start_x + 1, start_y, RIGHT));
		}
		if (m_Enclosure.find({ start_x,start_y + 1 }) == m_Enclosure.end() && m_WallsMap[{start_x, start_y + 1}] == WALL)
		{
			m_WallsVec.push_back(Wall(start_x, start_y + 1, UP));
		}
		if (m_Enclosure.find({ start_x - 1,start_y }) == m_Enclosure.end() && m_WallsMap[{start_x - 1, start_y}] == WALL)
		{
			m_WallsVec.push_back(Wall(start_x - 1, start_y, LEFT));
		}
		if (m_Enclosure.find({ start_x ,start_y-1 }) == m_Enclosure.end() && m_WallsMap[{start_x , start_y-1}] == WALL)
		{
			m_WallsVec.push_back(Wall(start_x , start_y-1, DOWN));
		}
	}

	void Maze::InitHeartMaze()
	{
		CreateCoordsOfMaze();
		FindEnclosure();
		CreateRandomWallInMaze();
	}

	void Maze::CreateCoordsOfMaze()
	{
		float leftVal = 0, rightVal = 0;

		for (int32_t i = -MAZE_AREAX; i < MAZE_AREAX; i++)
		{
			for (int32_t j = -MAZE_AREAY; j < MAZE_AREAY; j++)
			{
				leftVal = calculateLeft(i, j);
				rightVal = calculateRight(i, j);

				if (leftVal <= rightVal)
				{
					m_WallsMap.insert({ {i,j },WALL });
				}
				else
				{
					m_WallsMap.insert({ {i,j },NOT_WALL});
				}
			}
		}

	}

	void Maze::CreateRandomWallInMaze()
	{
		findWall();
		srand((unsigned)time(NULL));
		m_WallsMap[{start_x, start_y}] = NOT_WALL;
		m_WallsMap[{start_x - 1, start_y}] = NOT_WALL;

		while (m_WallsVec.size()) {
			int wallSize = m_WallsVec.size();
			int randnum = rand() % wallSize;
			Wall selectedWall = m_WallsVec[randnum];
			start_x = selectedWall.GetX();
			start_y = selectedWall.GetY();
			switch (selectedWall.GetDir())
			{
			case RIGHT:
			{
				start_x++;
				break;
			}
			case UP:
			{
				start_y++;
				break;
			}
			case DOWN:
			{
				start_y--;
				break;
			}
			case LEFT:
			{
				start_x--;
				break;
			}
			}
			if (m_WallsMap[{start_x, start_y}] == WALL && m_Enclosure.find({ start_x,start_y }) == m_Enclosure.end())
			{
				m_WallsMap[{selectedWall.GetX(), selectedWall.GetY()}] = m_WallsMap[{start_x, start_y}] = NOT_WALL;
				findWall();
			}
			m_WallsVec.erase(m_WallsVec.begin() + randnum);
		}

		//generate a door
		for (auto p : m_DoorGenerator)
		{
			if (m_WallsMap[{p.first - 1, p.second}] == NOT_WALL)
			{
				m_WallsMap[{p.first, p.second}] = NOT_WALL;
				break;
			}
		}

	}


	void Maze::FindEnclosure()
	{
		for (auto it=m_WallsMap.begin();it!=m_WallsMap.end();it++)
		{
			if (it->second==NOT_WALL)
			{
				auto leftWall = m_WallsMap.find({ it->first.first - 1,it->first.second });
				if (leftWall != m_WallsMap.end())
				{
					if (leftWall->second == WALL)
					{
						if (m_Enclosure.find({ it->first.first - 1,it->first.second}) == m_Enclosure.end())
						{
							m_Enclosure.insert({ it->first.first - 1, it->first.second});
						}
					}
				}

				auto upWall = m_WallsMap.find({ it->first.first ,it->first.second+ 1 });
				if (upWall != m_WallsMap.end())
				{
					if (upWall->second == WALL)
					{
						if (m_Enclosure.find({ it->first.first ,it->first.second + 1 }) == m_Enclosure.end())
						{
							m_Enclosure.insert({ it->first.first , it->first.second + 1 });
						}
					}
				}

				auto rightWall = m_WallsMap.find({ it->first.first + 1,it->first.second });
				if (rightWall != m_WallsMap.end())
				{
					if (rightWall->second == WALL)
					{
						if (m_Enclosure.find({ it->first.first + 1,it->first.second }) == m_Enclosure.end())
						{
							m_Enclosure.insert({ it->first.first + 1, it->first.second});
						}
					}
				}

				auto downWall = m_WallsMap.find({ it->first.first ,it->first.second - 1 });
				if (downWall != m_WallsMap.end())
				{
					if (downWall->second == WALL)
					{
						if (m_Enclosure.find({ it->first.first  ,it->first.second - 1 }) == m_Enclosure.end())
						{
							m_Enclosure.insert({ it->first.first , it->first.second - 1 });
						}
					}
				}
			}
		}

		//area of door which may generated
		for (auto it = m_Enclosure.begin(); it != m_Enclosure.end(); it++)
		{
			if (it->first >= 14 && it->first <= 18 && it->second >= -3 && it->second <= 13)
			{
				m_DoorGenerator.push_back({ it->first, it->second });
			}
		}

	}

}