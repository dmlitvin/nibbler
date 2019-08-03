/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl2.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 13:32:57 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/08/03 15:07:30 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Grid and stuff

#include "Grid.hpp"

namespace
{
	static ::Window		*window;
	static ::Grid		*grid;
    static uint8_t      *map;

	int squareSide = 15;
	int stride = 3;
}

extern "C"
void    init(uint8_t gridWidth, uint8_t gridHeight, key initKey)
{
	window = new ::Window("Nibbler [SDL2]", gridWidth * squareSide + stride * gridWidth,
									gridHeight * squareSide + stride * gridHeight, initKey);
	grid = new ::Grid(window, _2DPoint{ 0, 0 }, (int)gridHeight, (int)gridWidth, squareSide, squareSide, stride);

    grid->SetGrid();
    grid->SetMap(map);
}

extern "C"
void	destroy()
{
	delete grid;
	delete window;
}

extern "C"
void	draw()
{
    grid->Draw();
    window->poolEvents();
    window->clear();
}

extern "C"
void	setGrid(uint8_t* gridPtr)
{
    map = gridPtr;
}

extern "C"
key		getLastPressed()
{
	return window->getLastPressed();
}
