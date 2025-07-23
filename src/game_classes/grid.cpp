#include "grid.hpp"

#include "cell.hpp"
#include "../managers/cell_manager.hpp"
#include "being.hpp"
#include "../tools/get_random_number.hpp"
#include "../tools/get_points.hpp"
#include "../tools/collision.hpp"

const unsigned int CELLSIZE = 5;
const int CELLOFFSETX = 0;
const int CELLOFFSETY = 0;

Grid::Grid() {}

Grid::Grid(unsigned int gridLength, unsigned int gridHeight, std::vector<std::shared_ptr<Being>>* beings) { create(gridLength, gridHeight, beings); }

void Grid::create(unsigned int gridLength, unsigned int gridHeight, std::vector<std::shared_ptr<Being>>* beings)
{
    theGrid.resize(gridHeight);

    for (int i = 0; i < theGrid.size(); i++)
    {
        theGrid[i].resize(gridLength);
    }

    this->beings = beings;
}

Cell* Grid::at(sf::Vector2u position) {
    if (position.y < theGrid.size() && position.x < theGrid[position.y].size())
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

unsigned int Grid::getSizeOfRow(unsigned int rowIndex)
{ 
    if (rowIndex < theGrid.size()) {
        return theGrid[rowIndex].size();
    }
    else
    {
        return 0;
    }
}

int Grid::getCellSize() { return CELLSIZE; }

sf::Vector2f Grid::getCellOffset() { return {CELLOFFSETX, CELLOFFSETY}; }

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

void Grid::makeCellsFromBeing(Being* being, std::string cellType, CellManager* cellManager)
{
    sf::FloatRect bBox = getRectBoundingBox(CELLSIZE, getCellOffset(), being->getPosition(), being->getSize(), being->getRotation(), true);

    int startX = static_cast<int>(std::floor(bBox.position.x));
    int startY = static_cast<int>(std::floor(bBox.position.y));
    int endX = static_cast<int>(std::floor(bBox.position.x + bBox.size.x));
    int endY = static_cast<int>(std::floor(bBox.position.y + bBox.size.y));

    for (int y = startY; y < endY; y++)
    {
        for (int x = startX; x < endX; x++)
        {
            if (pointRectCollide(gridToWorldCoords(CELLSIZE, getCellOffset(), {static_cast<unsigned int>(x), static_cast<unsigned int>(y)}, true), being->getPosition(), being->getSize(), being->getRotation()))
            {
                createCell(cellManager, cellType, {static_cast<unsigned int>(x), static_cast<unsigned int>(y)});
            }
        }
    }
}        

bool Grid::canMoveTo(sf::Vector2u from, sf::Vector2u to)
{
    if (to.y > getSize() - 1 || to.x > getSizeOfRow(to.y) - 1) return false;

    sf::Vector2i distance;

    distance.x = abs(from.x - to.x);
    distance.y = abs(from.y - to.y);

    sf::Vector2i direction;

    (distance.x > 0) ? direction.x = 1 : (distance.x < 0) ? direction.x = -1 : direction.x = 0;
    (distance.y > 0) ? direction.y = 1 : (distance.y < 0) ? direction.y = -1 : direction.y = 0;

    if (checkCellsInLine(from, distance, direction, this, beings, CELLSIZE, getCellOffset())) return false;

    return true;
}

bool Grid::canMoveDistance(sf::Vector2u from, sf::Vector2i distance)
{
    if (from.y + distance.y < 0 || from.x + distance.x < 0) return false;
    if (from.y + distance.y > getSize() - 1 || from.x + distance.x > getSizeOfRow(from.y + distance.y) - 1) return false;

    sf::Vector2i direction;

    (distance.x > 0) ? direction.x = 1 : (distance.x < 0) ? direction.x = -1 : direction.x = 0;
    (distance.y > 0) ? direction.y = 1 : (distance.y < 0) ? direction.y = -1 : direction.y = 0;

    if (checkCellsInLine(from, distance, direction, this, beings, CELLSIZE, getCellOffset())) return false;

    return true;
}

void Grid::createCell(CellManager* cellManager, std::string type, sf::Vector2u position)
{
    // make sure all other necessary checks have been done before calling this function
    if (theGrid[position.y][position.x] == nullptr)
    {
        theGrid[position.y][position.x] = std::make_shared<Cell>(cellManager, this, type, position);
    }
}

void Grid::removeCell(sf::Vector2u gridPos)
{
    theGrid[gridPos.y][gridPos.x].reset();
}

void Grid::moveCell(sf::Vector2u gridPos, sf::Vector2i distance)
{
    // make sure all other necessary checks have been done before calling this function
    theGrid[gridPos.y][gridPos.x]->changePos(distance);
    theGrid[gridPos.y + distance.y][gridPos.x + distance.x] = std::move(theGrid[gridPos.y][gridPos.x]);
}

void Grid::swap(sf::Vector2u gridPos1, sf::Vector2u gridPos2)
{
    theGrid[gridPos1.y][gridPos1.x]->setPos(gridPos2);
    theGrid[gridPos2.y][gridPos2.x]->setPos(gridPos1);
    std::swap(*(theGrid[gridPos1.y][gridPos1.x]), *(theGrid[gridPos2.y][gridPos2.x]));
}

void Grid::updateCells(sf::Vector2u creatorPos)
{
    // // these lines just print the grid for fun
    // std::cout << "//////////////////////////STARTING//////////////////////////\n";

    // for (int y = 0; y < theGrid.size(); y++)
    // {
    //     for (int x = 0; x < theGrid[y].size(); x++)
    //     {
    //         if (x == creatorPos.x && y == creatorPos.y)
    //         {
    //             std::cout << "\e[32mcc\e[39m";
    //         }
    //         else if (theGrid[y][x] != nullptr)
    //         {
    //             if (theGrid[y][x]->getType() == "sand")
    //             {
    //                 std::cout << "\e[33m##\e[39m";
    //             }
    //             else if (theGrid[y][x]->getType() == "water")
    //             {
    //                 std::cout << "\e[34m~~\e[39m";
    //             }
    //             else if (theGrid[y][x]->getType() == "fire")
    //             {
    //                 std::cout << "\e[31m!!\e[39m";
    //             }
    //             else if (theGrid[y][x]->getType() == "wood")
    //             {
    //                 std::cout << "\e[33mHH\e[39m";
    //             }
    //             else if (theGrid[y][x]->getType() == "smoke")
    //             {
    //                 std::cout << "\e[90m**\e[39m";
    //             }
    //         }
    //         else
    //         {
    //             std::cout << "..";
    //         }
    //     }

    //     std::cout << '\n';
    // }

    // std::cout << "////////////////////////////DONE////////////////////////////\n";

    // updating the grid itself
    if (theGrid.size() > 0)
    {
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
    
                // iterates through regular cells
                if (theGrid[y][x] != nullptr)
                {
                    if (!theGrid[y][x]->hasBehavior("rise"))
                    {
                        theGrid[y][x]->update();
                    }
                }
    
                int oppY = (theGrid.size() - 1) - y;
    
                // iterates through rising cells (like smoke)
                if (theGrid[oppY][x] != nullptr)
                {
                    if (theGrid[oppY][x]->hasBehavior("rise"))
                    {
                        theGrid[oppY][x]->update();
                    }
                }
            }
        }
    }
}