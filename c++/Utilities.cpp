#include "Utilities.h"
#include "Tetris.h"
#include <iostream>

bool collide(Tetris& block, const std::vector<Block*>& allBlocks)
{
	for (Block* b : block.fBlocks)
	{
		if (b) {
			if (b->getBlockLocalPos().y + block.getBlockPos().y >= GgameBorders.top + GgameBorders.height)
			{
				return true;
			}
			for (Block* c : allBlocks)
			{
				if (c) {
					if (b->getBlockLocalPos() + block.getBlockPos() == c->getBlockGlobalPos())
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

Borders hasReachBorders(Tetris& block)
{
	for (Block* b : block.fBlocks)
	{
		if (b) {
			int pos_x = b->getBlockLocalPos().x + block.getBlockPos().x;
			if (pos_x >= GgameBorders.left + GgameBorders.width - 1)
				return Borders::Right;
			if (pos_x <= GgameBorders.left)
				return Borders::Left;
		}
	}

	return Borders::None;
}
