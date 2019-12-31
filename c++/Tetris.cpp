#include "Tetris.h"
#include <cassert>
#include <iostream>
#include "../BrickPong/UtilityFunc.h"

Tetris::Tetris(sf::Texture& blockTextures, int x, int y, Type type, Block::Color color)
	:fBlocks(), fType(type)
{
	setPosition(blockToRealPos(x, y));
	Block* b1 = nullptr;
	Block* b2 = nullptr;
	Block* b3 = nullptr;
	Block* b4 = nullptr;
	switch (type)
	{
	case Tetris::Type::O_Ricky:
	{
		b1 = new Block(blockTextures, 0, 1, color);
		b2 = new Block(blockTextures, 1, 1, color);
		b3 = new Block(blockTextures, 2, 1, color);
		b4 = new Block(blockTextures, 2, 0, color);


		std::array<sf::Vector2i, 4> rotateUp = { sf::Vector2i(0, 1), sf::Vector2i(1, 1), sf::Vector2i(2, 1), sf::Vector2i(2, 0) };
		std::array<sf::Vector2i, 4> rotateRight = { sf::Vector2i(0, 0), sf::Vector2i(0, 1), sf::Vector2i(0, 2), sf::Vector2i(1, 2) };
		std::array<sf::Vector2i, 4> rotateDown = { sf::Vector2i(0, 0), sf::Vector2i(0, 1), sf::Vector2i(1, 0), sf::Vector2i(2, 0) };
		std::array<sf::Vector2i, 4> rotateLeft = { sf::Vector2i(0, 0), sf::Vector2i(1, 0), sf::Vector2i(1, 1), sf::Vector2i(1, 2) };

		fRotationConfig[Up] = rotateUp;
		fRotationConfig[Right] = rotateRight;
		fRotationConfig[Down] = rotateDown;
		fRotationConfig[Left] = rotateLeft;
	}
		break;
	case Tetris::Type::B_Ricky:
	{
		b1 = new Block(blockTextures, 0, 0, color);
		b2 = new Block(blockTextures, 0, 1, color);
		b3 = new Block(blockTextures, 1, 1, color);
		b4 = new Block(blockTextures, 2, 1, color);


		std::array<sf::Vector2i, 4> rotateUp = { sf::Vector2i(0, 0), sf::Vector2i(0, 1), sf::Vector2i(1, 1), sf::Vector2i(2, 1) };
		std::array<sf::Vector2i, 4> rotateRight = { sf::Vector2i(0, 0), sf::Vector2i(0, 1), sf::Vector2i(0, 2), sf::Vector2i(1, 0) };
		std::array<sf::Vector2i, 4> rotateDown = { sf::Vector2i(0, 0), sf::Vector2i(1, 0), sf::Vector2i(2, 0), sf::Vector2i(2, 1) };
		std::array<sf::Vector2i, 4> rotateLeft = { sf::Vector2i(0, 2), sf::Vector2i(1, 0), sf::Vector2i(1, 1), sf::Vector2i(1, 2) };

		fRotationConfig[Up] = rotateUp;
		fRotationConfig[Right] = rotateRight;
		fRotationConfig[Down] = rotateDown;
		fRotationConfig[Left] = rotateLeft;
	}
		break;
	case Tetris::Type::RhodeIsland:
	{
		b1 = new Block(blockTextures, 0, 1, color);
		b2 = new Block(blockTextures, 1, 1, color);
		b3 = new Block(blockTextures, 1, 0, color);
		b4 = new Block(blockTextures, 2, 0, color);


		std::array<sf::Vector2i, 4> rotateUp = { sf::Vector2i(0, 1), sf::Vector2i(1, 1), sf::Vector2i(1, 0), sf::Vector2i(2, 0) };
		std::array<sf::Vector2i, 4> rotateRight = { sf::Vector2i(0, 0), sf::Vector2i(0, 1), sf::Vector2i(1, 1), sf::Vector2i(1, 2) };
		std::array<sf::Vector2i, 4> rotateDown = { sf::Vector2i(0, 1), sf::Vector2i(1, 1), sf::Vector2i(1, 0), sf::Vector2i(2, 0) };
		std::array<sf::Vector2i, 4> rotateLeft = { sf::Vector2i(0, 0), sf::Vector2i(0, 1), sf::Vector2i(1, 1), sf::Vector2i(1, 2) };

		fRotationConfig[Up] = rotateUp;
		fRotationConfig[Right] = rotateRight;
		fRotationConfig[Down] = rotateDown;
		fRotationConfig[Left] = rotateLeft;
	}
		break;
	case Tetris::Type::Cleveland:
	{
		b1 = new Block(blockTextures, 0, 0, color);
		b2 = new Block(blockTextures, 1, 0, color);
		b3 = new Block(blockTextures, 1, 1, color);
		b4 = new Block(blockTextures, 2, 1, color);


		std::array<sf::Vector2i, 4> rotateUp = { sf::Vector2i(0, 0), sf::Vector2i(1, 0), sf::Vector2i(1, 1), sf::Vector2i(2, 1) };
		std::array<sf::Vector2i, 4> rotateRight = { sf::Vector2i(0, 1), sf::Vector2i(0, 2), sf::Vector2i(1, 0), sf::Vector2i(1, 1) };
		std::array<sf::Vector2i, 4> rotateDown = { sf::Vector2i(0, 0), sf::Vector2i(1, 0), sf::Vector2i(1, 1), sf::Vector2i(2, 1) };
		std::array<sf::Vector2i, 4> rotateLeft = { sf::Vector2i(0, 1), sf::Vector2i(0, 2), sf::Vector2i(1, 0), sf::Vector2i(1, 1) };

		fRotationConfig[Up] = rotateUp;
		fRotationConfig[Right] = rotateRight;
		fRotationConfig[Down] = rotateDown;
		fRotationConfig[Left] = rotateLeft;
	}
		break;
	case Tetris::Type::Teewee:
	{
		b1 = new Block(blockTextures, 0, 1, color);
		b2 = new Block(blockTextures, 1, 1, color);
		b3 = new Block(blockTextures, 1, 0, color);
		b4 = new Block(blockTextures, 2, 1, color);


		std::array<sf::Vector2i, 4> rotateUp = { sf::Vector2i(0, 1), sf::Vector2i(1, 1), sf::Vector2i(1, 0), sf::Vector2i(2, 1) };
		std::array<sf::Vector2i, 4> rotateRight = { sf::Vector2i(0, 0), sf::Vector2i(0, 1), sf::Vector2i(0, 2), sf::Vector2i(1, 1) };
		std::array<sf::Vector2i, 4> rotateDown = { sf::Vector2i(0, 0), sf::Vector2i(1, 0), sf::Vector2i(1, 1), sf::Vector2i(2, 0) };
		std::array<sf::Vector2i, 4> rotateLeft = { sf::Vector2i(0, 1), sf::Vector2i(1, 0), sf::Vector2i(1, 1), sf::Vector2i(1, 2) };

		fRotationConfig[Up] = rotateUp;
		fRotationConfig[Right] = rotateRight;
		fRotationConfig[Down] = rotateDown;
		fRotationConfig[Left] = rotateLeft;
	}
		break;
	case Tetris::Type::Hero:
	{
		b1 = new Block(blockTextures, 0, 0, color);
		b2 = new Block(blockTextures, 1, 0, color);
		b3 = new Block(blockTextures, 2, 0, color);
		b4 = new Block(blockTextures, 3, 0, color);


		std::array<sf::Vector2i, 4> rotateUp = { sf::Vector2i(0, 0), sf::Vector2i(1, 0), sf::Vector2i(2, 0), sf::Vector2i(3, 0) };
		std::array<sf::Vector2i, 4> rotateRight = { sf::Vector2i(0, 0), sf::Vector2i(0, 1), sf::Vector2i(0, 2), sf::Vector2i(0, 3) };
		std::array<sf::Vector2i, 4> rotateDown = { sf::Vector2i(0, 0), sf::Vector2i(1, 0), sf::Vector2i(2, 0), sf::Vector2i(3, 0) };
		std::array<sf::Vector2i, 4> rotateLeft = { sf::Vector2i(0, 0), sf::Vector2i(0, 1), sf::Vector2i(0, 2), sf::Vector2i(0, 3) };

		fRotationConfig[Up] = rotateUp;
		fRotationConfig[Right] = rotateRight;
		fRotationConfig[Down] = rotateDown;
		fRotationConfig[Left] = rotateLeft;
	}
		break;
	case Tetris::Type::SmashBoy:
	{
		b1 = new Block(blockTextures, 0, 0, color);
		b2 = new Block(blockTextures, 0, 1, color);
		b3 = new Block(blockTextures, 1, 0, color);
		b4 = new Block(blockTextures, 1, 1, color);
		

		std::array<sf::Vector2i, 4> rotateUp = { sf::Vector2i(0, 0), sf::Vector2i(0, 1), sf::Vector2i(1, 0), sf::Vector2i(1, 1) };
		std::array<sf::Vector2i, 4> rotateRight = { sf::Vector2i(0, 0), sf::Vector2i(0, 1), sf::Vector2i(1, 0), sf::Vector2i(1, 1) };
		std::array<sf::Vector2i, 4> rotateDown = { sf::Vector2i(0, 0), sf::Vector2i(0, 1), sf::Vector2i(1, 0), sf::Vector2i(1, 1) };
		std::array<sf::Vector2i, 4> rotateLeft = { sf::Vector2i(0, 0), sf::Vector2i(0, 1), sf::Vector2i(1, 0), sf::Vector2i(1, 1) };

		fRotationConfig[Up] = rotateUp;
		fRotationConfig[Right] = rotateRight;
		fRotationConfig[Down] = rotateDown;
		fRotationConfig[Left] = rotateLeft;
	}
		break;
	default:
		assert(false);
		break;
	}


	fBlocks[0] = (b1);
	fBlocks[1] = (b2);
	fBlocks[2] = (b3);
	fBlocks[3] = (b4);

}

sf::Vector2i Tetris::getBlockPos() const
{
	return convertToBlockCoords(sf::Vector2f(getPosition().x - getOrigin().x, getPosition().y - getOrigin().y));
}

void Tetris::setBlockPos(int x, int y)
{
	setPosition(blockToRealPos(x - getOrigin().x, y - getOrigin().y));
}

void Tetris::setBlockPos(sf::Vector2i pos)
{
	setPosition(blockToRealPos(pos.x - getOrigin().x, pos.y - getOrigin().y));
}

void Tetris::moveBlock(int x_amount, int y_amount, std::vector<Block*>& allBlocks)
{
	if (fCurrentState != State::Static)
	{
		assert(allBlocks.size() == GgameBorders.width * GgameBorders.height);
		move(x_amount * GcellSize, y_amount * GcellSize);

		if (collide(*this, allBlocks)) {

			move(-x_amount * GcellSize, -y_amount * GcellSize);
			if (x_amount == 0) {
				fCurrentState = State::Static;
				for (Block* b : fBlocks) {
					b->setBlockGlobalPos(getBlockPos() + b->getBlockLocalPos());
					allBlocks[b->getBlockGlobalPos().x + GgameBorders.width * b->getBlockGlobalPos().y] = b;
				}
			}
		}
	}
}

void Tetris::rotateBlock(std::vector<Block*>& allBlocks)
{
	fRotateState = (fRotateState + 1) % Count;

	for (int i = 0; i < fBlocks.size(); ++i)
	{
		fBlocks[i]->setBlockLocalPos(fRotationConfig[fRotateState][i]);
		int pos_x = fBlocks[i]->getBlockLocalPos().x + getBlockPos().x;
		if (pos_x >= GgameBorders.left + GgameBorders.width || pos_x < GgameBorders.left 
			|| fBlocks[i]->getBlockLocalPos().y + getBlockPos().y >= GgameBorders.top + GgameBorders.height - 1
			|| allBlocks[getBlockPos().x + fBlocks[i]->getBlockLocalPos().x + (getBlockPos().y + fBlocks[i]->getBlockLocalPos().y) * GgameBorders.width])
		{
			fRotateState = abs((fRotateState - 1) % Count);
			for (int i = 0; i < fBlocks.size(); ++i)
			{
				fBlocks[i]->setBlockLocalPos(fRotationConfig[fRotateState][i]);
			}
			break;
		}
	}
}

Tetris::State Tetris::getState() const
{
	return fCurrentState;
}

Tetris::~Tetris()
{
	//for (Block* b : fBlocks)
	//	if (b != nullptr) delete b;
}

void Tetris::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	for (Block* b : fBlocks)
	{
		if(b)
			target.draw(*b, states);
	}
}
