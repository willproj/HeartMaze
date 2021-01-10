#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <tuple>
#include <memory>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include <time.h>
#include <functional>


#define WALL 1
#define NOT_WALL -1

#define DOWN 1
#define RIGHT 2
#define LEFT 4
#define UP 8

const int32_t MAZE_AREAX = 22;
const int32_t MAZE_AREAY = 22;

struct pair_hash
{
	template <class T1, class T2>
	std::size_t operator() (const std::pair<T1, T2>& pair) const
	{
		return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
	}
};

//maze math formula
//(x^2/a^2+y^2/a^2-1)^3=x^2/a^2*y^3/a^3 (a is constant)
static float calculateLeft(int x, int y)
{
	float leftVal = x * x * 1.0f / 255.0f + y * y * 1.0f / 255.0f - 1;
	return leftVal * leftVal * leftVal;
}


static float calculateRight(int x, int y)
{
	return x * x * 1.0f * y * y * y / 860625.0f;
}
