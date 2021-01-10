#pragma once
#include "Common.h"

namespace maze
{
	class Wall
	{
	private:
		int m_X, m_Y;
		int m_Dir;
	public:
		Wall(int x, int y, int dir)
			:m_X(x), m_Y(y), m_Dir(dir)
		{ }

		int GetX() { return m_X; }
		int GetY() { return m_Y; }
		int GetDir() { return m_Dir; }
	};

	class Maze
	{
	private:
		int start_x = -17, start_y = 7;
		std::vector<Wall> m_WallsVec;

		std::unordered_set<std::pair<int32_t, int32_t>, pair_hash> m_Enclosure;
		std::unordered_map<std::pair<int32_t, int32_t>, int32_t, pair_hash> m_WallsMap;
		std::unordered_set<std::pair<int32_t, int32_t>, pair_hash> GetEnclosure() { return m_Enclosure; }
		std::vector<std::pair<int32_t,int32_t>> m_DoorGenerator;
	public:
		
		Maze();
		~Maze();

		std::unordered_map<std::pair<int32_t, int32_t>, int32_t, pair_hash>& GetWallCoordMapRef() { return m_WallsMap; }
		
	private:
		void findWall();
		void InitHeartMaze();
		void FindEnclosure();
		void CreateCoordsOfMaze();
		void CreateRandomWallInMaze();

	};

}