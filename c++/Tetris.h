#pragma once
#include "Block.h"
#include <array>

class Tetris : public sf::Drawable, public sf::Transformable
{
public:
	enum class Type
	{
		O_Ricky, B_Ricky, RhodeIsland, Cleveland, Teewee, Hero, SmashBoy, Count
	};
	enum class State
	{
		Moving, Static
	};
	enum RotateState
	{
		Up, Right, Down, Left, Count
	};

	Tetris(sf::Texture& blockTextures, int x, int y, Type type, Block::Color color = Block::Color::Red);

	sf::Vector2i getBlockPos() const;
	void setBlockPos(int x, int y);
	void setBlockPos(sf::Vector2i pos);
	void moveBlock(int x_amount, int y_amount, std::vector<Block*>& allBlocks);
	void rotateBlock(std::vector<Block*>& allBlocks);

	State getState() const;


	~Tetris();

	std::array<Block*, 4> fBlocks;
	Type fType;
private:

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	State fCurrentState = State::Moving;
	sf::Vector2f fOriginOffset = sf::Vector2f(0.f, 0.f);

	std::array<std::array<sf::Vector2i, 4>, 4> fRotationConfig;
	int fRotateState = Up;
};