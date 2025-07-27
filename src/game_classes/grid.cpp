#include "grid.hpp"

#include "cell.hpp"
#include "../managers/cell_manager.hpp"
#include "being.hpp"
#include "../tools/get_random_number.hpp"
#include "../tools/get_points.hpp"
#include "../tools/collision.hpp"

Grid::Grid() {}

Grid::Grid(unsigned int gridLength, unsigned int gridHeight, std::vector<std::shared_ptr<Being>>* beings, CellManager* cellManager)
{
    create(gridLength, gridHeight, beings, cellManager);
}

void Grid::create(unsigned int gridLength, unsigned int gridHeight, std::vector<std::shared_ptr<Being>>* beings, CellManager* cellManager)
{
    theGrid.resize(gridHeight);

    for (int i = 0; i < theGrid.size(); i++)
    {
        theGrid[i].resize(gridLength);
    }

    this->gridLength = gridLength;

    this->gridHeight = gridHeight;

    this->beings = beings;

    this->cellManager = cellManager;

    gridVertices = GridVertices(gridLength, gridHeight, cellManager);
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

unsigned int Grid::getLength() { return gridLength; }

unsigned int Grid::getHeight() { return gridHeight; }

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

void Grid::makeCellsFromBeing(Being* being, std::string cellType)
{
    sf::FloatRect bBox = getRectBoundingBox(cellManager, being->getPosition(), being->getSize(), being->getRotation(), true);

    int startX = static_cast<int>(std::floor(bBox.position.x));
    int startY = static_cast<int>(std::floor(bBox.position.y));
    int endX = static_cast<int>(std::floor(bBox.position.x + bBox.size.x));
    int endY = static_cast<int>(std::floor(bBox.position.y + bBox.size.y));

    for (int y = startY; y < endY; y++)
    {
        for (int x = startX; x < endX; x++)
        {
            if (pointRectCollide(gridToWorldCoords(cellManager, sf::Vector2i(x, y), true), being->getPosition(), being->getSize(), being->getRotation()))
            {
                createCell(cellType, {static_cast<unsigned int>(x), static_cast<unsigned int>(y)});
            }
        }
    }
}        

bool Grid::canMoveTo(sf::Vector2u from, sf::Vector2u to)
{
    if (to.y > gridHeight - 1 || to.x > gridLength - 1) return false;

    sf::Vector2i distance;

    distance.x = abs(static_cast<int>(from.x - to.x));
    distance.y = abs(static_cast<int>(from.y - to.y));

    if (checkCellsInLine(cellManager, from, distance)) return false;

    return true;
}

bool Grid::canMoveDistance(sf::Vector2u from, sf::Vector2i distance)
{
    if (from.y + distance.y < 0 || from.x + distance.x < 0) return false;
    if (from.y + distance.y > gridHeight - 1 || from.x + distance.x > gridLength - 1) return false;

    if (checkCellsInLine(cellManager, from, distance)) return false;

    return true;
}

void Grid::createCell(std::string type, sf::Vector2u position)
{
    // make sure this position does not collide with a being
    for (int i = 0; i < beings->size(); i++)
    {
        if (pointBeingCollide(gridToWorldCoords(cellManager, position, true), (*beings)[i].get(), cellManager->beingRectInflationSize))
        {
            return;
        }   
    }   

    // make sure all other necessary checks have been done before calling this function
    if (theGrid[position.y][position.x] == nullptr)
    {
        theGrid[position.y][position.x] = std::make_shared<Cell>(cellManager, this, beings, type, position);
        gridVertices.updateSquare(static_cast<unsigned int>(position.x), static_cast<unsigned int>(position.y));
    }
}

void Grid::removeCell(sf::Vector2u gridPos)
{
    theGrid[gridPos.y][gridPos.x].reset();
    gridVertices.updateSquare(gridPos.x, gridPos.y);
}

void Grid::moveCell(sf::Vector2u gridPos, sf::Vector2i distance)
{
    if (gridPos != sf::Vector2u(0, 0))
    {
        gridVertices.addMovingCell(gridPos.x, gridPos.y, sf::Vector2u({gridPos.x + distance.x, gridPos.y + distance.y}), theGrid[gridPos.y][gridPos.x].get());

        // make sure all other necessary checks have been done before calling this function
        theGrid[gridPos.y][gridPos.x]->changePos(distance);
        theGrid[gridPos.y + distance.y][gridPos.x + distance.x] = std::move(theGrid[gridPos.y][gridPos.x]);

    }
}

void Grid::swap(sf::Vector2u gridPos1, sf::Vector2u gridPos2)
{
    if (gridPos1 != gridPos2)
    {
        gridVertices.addMovingCell(gridPos1.x, gridPos1.y, gridPos2, theGrid[gridPos1.y][gridPos1.x].get());
        gridVertices.addMovingCell(gridPos2.x, gridPos2.y, gridPos1, theGrid[gridPos2.y][gridPos2.x].get());

        std::swap(theGrid[gridPos1.y][gridPos1.x], theGrid[gridPos2.y][gridPos2.x]);
        theGrid[gridPos1.y][gridPos1.x]->setPos(gridPos1);
        theGrid[gridPos2.y][gridPos2.x]->setPos(gridPos2);
    }
}

void Grid::tick(sf::Vector2u creatorPos)
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
    bool gridHasChanged = false;

    if (theGrid.size() > 0 && theGrid[0].size() > 0)
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
    
                    // iterates through falling cells
                    if (theGrid[y][x] != nullptr)
                    {
                        if (theGrid[y][x]->getWeight() >= 0.f)
                        {
                            if (tickCell({static_cast<unsigned int>(x), static_cast<unsigned int>(y)}))
                            {
                                gridHasChanged = true;
                            }
                        }
                    }
                    
                    int oppY = (gridHeight - 1) - y;

                    // iterates through rising cells
                    if (theGrid[oppY][x] != nullptr)
                    {
                        if (theGrid[oppY][x]->getWeight() < 0.f)
                        {
                            if (tickCell({static_cast<unsigned int>(x), static_cast<unsigned int>(oppY)}))
                            {
                                gridHasChanged = true;
                            }
                        }
                    }
            }
        }
    }

    if (gridHasChanged)
    {
        gridVertices.updateStatic();
    }
}

bool Grid::tickCell(sf::Vector2u position)
{
    if (position.y < gridHeight && position.x < gridLength)
    {
        if (theGrid[position.y][position.x] != nullptr)
        {
            std::pair<Cell*, bool> tickReturns = theGrid[position.y][position.x]->tick();

            if (tickReturns.second)
            {
                return true;
            }
        }
    }

    return false;
}

void Grid::update()
{
    gridVertices.updateMoving();
}

void Grid::draw(sf::RenderWindow& window)
{
    gridVertices.draw(window);
}