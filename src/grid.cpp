#include "grid.hpp"

#include "cell.hpp"
#include "cell_manager.hpp"

Grid::Grid() {}

Grid::Grid(unsigned int gridLength, unsigned int gridHeight) { create(gridLength, gridHeight); }

void Grid::create(unsigned int gridLength, unsigned int gridHeight)
{
    theGrid.resize(gridHeight);

    for (int i = 0; i < theGrid.size(); i++)
    {
        theGrid[i].resize(gridLength);
    }
}

Cell* Grid::at(sf::Vector2u position) {
    if (position.x < theGrid[position.y].size() && position.y < theGrid.size())
    {
        if (theGrid[position.y][position.x] != nullptr)
        {
            return theGrid[position.y][position.x].get();
        }
        else
        {
            return nullptr;
        }
    }

    return nullptr;
}

unsigned int Grid::getSize() { return theGrid.size(); }

unsigned int Grid::getSizeOfRow(unsigned int rowIndex) { return theGrid[rowIndex].size(); }

unsigned int Grid::getCellCount()
{
    int cells = 0;

    for (int y = 0; y < theGrid.size(); y++)
    {
        for (int x = 0; x < theGrid.size(); x++)
        {
            if (theGrid[y][x] != nullptr)
            {
                cells++;
            }
        }
    }

    return cells;
}

void Grid::createCell(CellManager* cellManager, Grid* grid, std::string type, sf::Vector2u position)
{
    // make sure all other necessary checks have been done before calling this function
    if (theGrid[position.y][position.x] == nullptr)
    {
        theGrid[position.y][position.x] = std::make_unique<Cell>(cellManager, grid, type, position);
    }
}

void Grid::moveCell(sf::Vector2u gridPos, sf::Vector2i distance)
{
    // make sure all other necessary checks have been done before calling this function
    if (theGrid[gridPos.y + distance.y][gridPos.x + distance.x] == nullptr)
    {
        theGrid[gridPos.y][gridPos.x]->changePos(distance);
        theGrid[gridPos.y + distance.y][gridPos.x + distance.x] = std::move(theGrid[gridPos.y][gridPos.x]);
    }
}

void Grid::swap(sf::Vector2u gridPos1, sf::Vector2u gridPos2)
{
    theGrid[gridPos1.y][gridPos1.x]->setPos(gridPos2);
    theGrid[gridPos2.y][gridPos2.x]->setPos(gridPos1);
    std::swap(*(theGrid[gridPos1.y][gridPos1.x]), *(theGrid[gridPos2.y][gridPos2.x]));
}

void Grid::updateCells()
{
    // these lines just print the grid
    std::cout << "////////////////////////STARTING////////////////////////\n";

    for (int y = 0; y < theGrid.size(); y++)
    {
        for (int x = 0; x < theGrid[y].size(); x++)
        {
            if (theGrid[y][x] != nullptr)
            {
                if (theGrid[y][x]->getType() == "sand")
                {
                    std::cout << "\e[33m##\e[39m";
                }
                else if (theGrid[y][x]->getType() == "water")
                {
                    std::cout << "\e[34m~~\e[39m";
                }
                else if (theGrid[y][x]->getType() == "fire")
                {
                    std::cout << "\e[31m~~\e[39m";
                }
            }
            else
            {
                std::cout << "..";
            }
        }

        std::cout << '\n';
    }

    std::cout << "//////////////////////////DONE//////////////////////////\n";

    // updating the grid itself
    for (int y = theGrid.size() - 1; y >= 0; y--)
    {
        bool rightToLeft;

        // randomly decides whether to go left or right on this row,
        // this is done to avoid a bias to one side
        (getRandomInt(1) == 0) ? rightToLeft = true : rightToLeft = false;

        for (int i = 0; i < theGrid[y].size(); i++)
        {
            int x;

            // setting the x that the grid will use to iterate based
            // on the rightToLeft boolean variable
            (rightToLeft) ? x = theGrid[y].size() - 1 - i : x = i;

            if (theGrid[y][x] != nullptr)
            {
                theGrid[y][x]->update();
            }
        }
    }
}