//Added comments for better understanding
#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "block.hpp"

class Wall : public Block
{
public:
	virtual void SetUp() override;
};