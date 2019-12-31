#pragma once
#include "Utilities.h"

class Block : public sf::Drawable, public sf::Transformable
{
public:
	enum Color
	{
		Yellow, Orange, Red, Pink, Purple, Cyan, Blue, LightGreen, DarkGreen, ColorCount
	};

	Block(sf::Texture& blockTextures, int x, int y, Color color = Red);

	sf::Vector2i getBlockLocalPos() const;
	sf::Vector2i getBlockGlobalPos() const;
	void setBlockLocalPos(int x, int y);
	void setBlockLocalPos(sf::Vector2i pos);
	void setBlockGlobalPos(int x, int y);
	void setBlockGlobalPos(sf::Vector2i pos);

private:

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::Sprite fSprite;
};