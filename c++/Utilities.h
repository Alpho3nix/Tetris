#pragma once
#include "SFML/Graphics.hpp"

#define WIDTH 400
#define HEIGHT 600

class Tetris;
class Block;

const sf::FloatRect GgameWindowDim(168.f, 2.f, 230.f, 460.f);
const int GcellSize = 23;

static sf::Vector2f blockToRealPos(int blockX, int blockY)
{
	return sf::Vector2f(GgameWindowDim.left + blockX * GcellSize, GgameWindowDim.top + blockY * GcellSize);
}

static sf::Vector2i convertToBlockCoords(sf::Vector2f pos)
{
	return sf::Vector2i(pos.x / GcellSize - int(GgameWindowDim.left / GcellSize), pos.y / GcellSize - int(GgameWindowDim.top / GcellSize));
}

const sf::IntRect GgameBorders(0, 0, GgameWindowDim.width / GcellSize, GgameWindowDim.height / GcellSize);

bool collide(Tetris& block, const std::vector<Block*>& allBlocks);

enum class Borders
{
	None, Left, Right
};
Borders hasReachBorders(Tetris& block);