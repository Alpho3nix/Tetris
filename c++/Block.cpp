#include "Block.h"
#include <iostream>

Block::Block(sf::Texture& blockTextures, int x, int y, Color color)
	:fSprite(blockTextures, sf::IntRect(color * GcellSize, 0, GcellSize, GcellSize))
{
	setPosition(x * GcellSize, y * GcellSize);
}

sf::Vector2i Block::getBlockLocalPos() const
{
	return sf::Vector2i(getPosition().x / GcellSize, getPosition().y / GcellSize);
}

sf::Vector2i Block::getBlockGlobalPos() const
{
	return convertToBlockCoords(getPosition());
}

void Block::setBlockLocalPos(int x, int y)
{
	setPosition(x * GcellSize, y * GcellSize);
}

void Block::setBlockLocalPos(sf::Vector2i pos)
{
	setPosition(pos.x * GcellSize, pos.y * GcellSize);
}

void Block::setBlockGlobalPos(int x, int y)
{
	setPosition(blockToRealPos(x, y));
}

void Block::setBlockGlobalPos(sf::Vector2i pos)
{
	setPosition(blockToRealPos(pos.x, pos.y));
}

void Block::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(fSprite, states);

}
