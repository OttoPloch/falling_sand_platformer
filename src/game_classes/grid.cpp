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

    this->beings = beings;

    this->cellManager = cellManager;

    verticesInit();
}

void Grid::verticesInit()
{
    vertexArray.setPrimitiveType(sf::PrimitiveType::Triangles);
    vertexArray.resize(getSizeOfRow(0) * getSize() * 6);

    movingCells.resize(0);

    for (int y = 0; y < getSize(); y++)
    {
        for (int x = 0; x < getSizeOfRow(y); x++)
        {
            int index = (x + y * getSizeOfRow(y)) * 6;

            vertexArray[index].position     = {x * cellManager->cellSize, y * cellManager->cellSize};
            vertexArray[index + 1].position = {x * cellManager->cellSize + cellManager->cellSize, y * cellManager->cellSize};
            vertexArray[index + 2].position = {x * cellManager->cellSize, y * cellManager->cellSize + cellManager->cellSize};
            vertexArray[index + 3].position = {x * cellManager->cellSize, y * cellManager->cellSize + cellManager->cellSize};
            vertexArray[index + 4].position = {x * cellManager->cellSize + cellManager->cellSize, y * cellManager->cellSize};
            vertexArray[index + 5].position = {x * cellManager->cellSize + cellManager->cellSize, y * cellManager->cellSize + cellManager->cellSize};

            updateSpecificVertices({static_cast<unsigned int>(x), static_cast<unsigned int>(y)});
        }
    }
}

void Grid::updateVertices()
{
    for (int y = 0; y < getSize(); y++)
    {
        for (int x = 0; x < getSizeOfRow(y); x++)
        {
            updateSpecificVertices({static_cast<unsigned int>(x), static_cast<unsigned int>(y)});
        }
    }
}

void Grid::updateSpecificVertices(sf::Vector2u position)
{
    int index = (position.x + position.y * getSizeOfRow(position.y)) * 6;

    // If a cell is here
    if (at({static_cast<unsigned int>(position.x), static_cast<unsigned int>(position.y)}) != nullptr)
    {
        // Make sure that cell is not being visually interpolated
        bool isAMovingCell = false;
        
        if (movingCells.size() > 0)
        {
            for (int i = 0; i < movingCells.size(); i++)
            {
                if (movingCells[i].second[0] == position)
                {
                    isAMovingCell = true;
                    
                    break;
                }
            }
        }

        if (!isAMovingCell)
        {
            for (int i = 0; i < 6; i++)
            {
                vertexArray[index + i].color = at({static_cast<unsigned int>(position.x), static_cast<unsigned int>(position.y)})->getColor();
            }

            return;
        }
    }

    // this will get called if either this cell is nullptr OR this cell is being interpolated to AND a cell is being interpolated FROM it.
    // the second case occurs when, for example, two sand are falling from the same spot and one is one tick behind the other (it is above).
    // in the next tick, since the cell is being interpolated to (it is the target position of a moving cell), it does not get updated to that
    // cell's color yet, HOWEVER since the cell that is ahead just left that spot, the checks above don't consider whether another cell has just
    // moved there, and assumes it is nullptr and will get made transparent because of that. But, we must also consider this case where it isn't.
    // Just wanted to explain the logic of that, also this could be an else statement to "if (!isAMovingCell)" above, but it can be combined with
    // the first case here using a return statement.
    for (int i = 0; i < 6; i++)
    {
        vertexArray[index + i].color = sf::Color::Transparent;
    }

}

void Grid::updateMovingVertices()
{
    if (movingCells.size() > 0)
    {
        std::vector<int> movingCellsToErase(0);

        for (int i = 0; i < movingCells.size(); i++)
        {
            float xDiff = gridToWorldCoords(cellManager, {static_cast<int>(movingCells[i].second[0].x), static_cast<int>(movingCells[i].second[0].y)}, false).x - movingCells[i].first[0].position.x;
            float yDiff = gridToWorldCoords(cellManager, {static_cast<int>(movingCells[i].second[0].x), static_cast<int>(movingCells[i].second[0].y)}, false).y - movingCells[i].first[0].position.y;

            if (abs(xDiff) < .1f && abs(yDiff) < .1f)
            {
                if (movingCells[i].second.size() > 1)
                {
                    movingCells[i].second.erase(movingCells[i].second.begin());
                }
                else
                {
                    movingCellsToErase.emplace_back(i);
                }
            }
            else
            {
                for (int j = 0; j < 6; j++)
                {
                    if (sqrt(pow(xDiff, 2) + pow(yDiff, 2)) > cellManager->cellSize * 10)
                    {
                        movingCells[i].first[j].position.x += xDiff / 3.f;
                        movingCells[i].first[j].position.y += yDiff / 3.f;
                    }
                    else if (sqrt(pow(xDiff, 2) + pow(yDiff, 2)) > cellManager->cellSize * 5)
                    {
                        movingCells[i].first[j].position.x += xDiff / 2.f;
                        movingCells[i].first[j].position.y += yDiff / 2.f;
                    }
                    else if (sqrt(pow(xDiff, 2) + pow(yDiff, 2)) > cellManager->cellSize * 2)
                    {
                        movingCells[i].first[j].position.x += xDiff / 1.2f;
                        movingCells[i].first[j].position.y += yDiff / 1.2f;
                    }
                    else
                    {
                        movingCells[i].first[j].position.x += xDiff / 1.15f;
                        movingCells[i].first[j].position.y += yDiff / 1.15f;
                    }
                }
            }
        }

        if (movingCellsToErase.size() > 0)
        {
            while (movingCellsToErase.size() > 0)
            {
                // maybe there's a better way to do this than a double for loop but this is more fun
                
                // grab the position of the moving cell
                sf::Vector2u posToUpdate = movingCells[movingCellsToErase[0]].second[0];

                // erase the moving cell
                movingCells.erase(movingCells.begin() + movingCellsToErase[0]);

                // erase the identifier that we just used above
                movingCellsToErase.erase(movingCellsToErase.begin());

                // decrement other identifiers to reflect the new 
                for (int j = 0; j < movingCellsToErase.size(); j++)
                {
                    movingCellsToErase[j]--;
                }

                updateSpecificVertices(posToUpdate);
            }
        }
    }
}

void Grid::addMovingVertices(sf::Vector2u currentPos, sf::Vector2u targetPos, sf::Color color)
{  
    sf::Vector2f screenCurrentPos = {currentPos.x * cellManager->cellSize, currentPos.y * cellManager->cellSize};
    sf::Vector2f screenTargetPos = {targetPos.x * cellManager->cellSize, targetPos.y * cellManager->cellSize};
    
    // If this cell is already being tracked by another moving cell
    if (movingCells.size() > 0)
    {
        for (int i = 0; i < movingCells.size(); i++)
        {
            if (movingCells[i].second.back() == currentPos)
            {
                for (int j = 0; j < 6; j++)
                {
                    movingCells[i].first[j].color = color;
                }

                sf::Vector2u targetBeforeLast;

                if (movingCells[i].second.size() > 1)
                {
                    // if the moving cell is going many places, it will be here eventually \/
                    targetBeforeLast = movingCells[i].second[movingCells[i].second.size() - 2];
                }
                else
                {
                    // if the moving cell has only one target, we use it to check for a straight line
                    targetBeforeLast = worldToGridCoords(cellManager, movingCells[i].first[0].position);
                }

                // If the moving cell is going in a vertical or horizontal line towards currentPos
                if (targetBeforeLast.x == currentPos.x || targetBeforeLast.y == currentPos.y)
                {
                    movingCells[i].second.back() = targetPos;

                    return;
                }

                movingCells[i].second.emplace_back(targetPos);

                return;
            }
        }
    }

    // This cell is not currently being represented by a moving cell
    std::array<sf::Vertex, 6> newVertices;

    for (int i = 0; i < 6; i++)
    {
        newVertices[i].color = color;
    }

    newVertices[0].position = {screenCurrentPos.x, screenCurrentPos.y};
    newVertices[1].position = {screenCurrentPos.x + cellManager->cellSize, screenCurrentPos.y};
    newVertices[2].position = {screenCurrentPos.x, screenCurrentPos.y + cellManager->cellSize};
    newVertices[3].position = {screenCurrentPos.x, screenCurrentPos.y + cellManager->cellSize};
    newVertices[4].position = {screenCurrentPos.x + cellManager->cellSize, screenCurrentPos.y};
    newVertices[5].position = {screenCurrentPos.x + cellManager->cellSize, screenCurrentPos.y + cellManager->cellSize};

    std::vector<sf::Vector2u> targetPositions = {targetPos};

    movingCells.emplace_back(newVertices, targetPositions);
}

void Grid::snapToRealPos()
{
    movingCells.clear();

    updateVertices();
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
            if (pointRectCollide(gridToWorldCoords(cellManager, {x, y}, true), being->getPosition(), being->getSize(), being->getRotation()))
            {
                createCell(cellType, {static_cast<unsigned int>(x), static_cast<unsigned int>(y)});
            }
        }
    }
}        

bool Grid::canMoveTo(sf::Vector2u from, sf::Vector2u to)
{
    if (to.y > getSize() - 1 || to.x > getSizeOfRow(to.y) - 1) return false;

    sf::Vector2i distance;

    distance.x = abs(static_cast<int>(from.x - to.x));
    distance.y = abs(static_cast<int>(from.y - to.y));

    if (checkCellsInLine(cellManager, from, distance)) return false;

    return true;
}

bool Grid::canMoveDistance(sf::Vector2u from, sf::Vector2i distance)
{
    if (from.y + distance.y < 0 || from.x + distance.x < 0) return false;
    if (from.y + distance.y > getSize() - 1 || from.x + distance.x > getSizeOfRow(from.y + distance.y) - 1) return false;

    if (checkCellsInLine(cellManager, from, distance)) return false;

    return true;
}

void Grid::createCell(std::string type, sf::Vector2u position)
{
    for (int i = 0; i < beings->size(); i++)
    {
        if (pointBeingCollide(gridToWorldCoords(cellManager, {static_cast<int>(position.x), static_cast<int>(position.y)}, true), (*beings)[i].get(), cellManager->beingRectInflationSize))
        {
            return;
        }   
    }   

    // make sure all other necessary checks have been done before calling this function
    if (theGrid[position.y][position.x] == nullptr)
    {
        theGrid[position.y][position.x] = std::make_shared<Cell>(cellManager, this, beings, type, position);
        updateSpecificVertices(position);
    }
}

void Grid::removeCell(sf::Vector2u gridPos)
{
    theGrid[gridPos.y][gridPos.x].reset();
    updateSpecificVertices(gridPos);
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
                        if (theGrid[y][x]->getWeight() > -1)
                        {
                            if (updateACell({static_cast<unsigned int>(x), static_cast<unsigned int>(y)}))
                            {
                                gridHasChanged = true;
                            }
                        }
                    }
                    
                    int oppY = (getSize() - 1) - y;

                    // iterates through rising cells
                    if (theGrid[oppY][x] != nullptr)
                    {
                        if (theGrid[oppY][x]->getWeight() < 0)
                        {
                            if (updateACell({static_cast<unsigned int>(x), static_cast<unsigned int>(oppY)}))
                            {
                                gridHasChanged = true;
                            }
                        }
                    }
            }
        }
    }

    if (gridHasChanged) updateVertices();
}

bool Grid::updateACell(sf::Vector2u position)
{
    if (position.y < getSize() && position.x < getSizeOfRow(position.y))
    {
        if (theGrid[position.y][position.x] != nullptr)
        {
            std::pair<sf::Vector2u, bool> tickReturns = theGrid[position.y][position.x]->tick();
            
            if (tickReturns.first != sf::Vector2u({0, 0}))
            {
                // This will check for duplicate movingCells on its own
                addMovingVertices({static_cast<unsigned int>(position.x), static_cast<unsigned int>(position.y)}, tickReturns.first, theGrid[tickReturns.first.y][tickReturns.first.x]->getColor());
            }

            if (tickReturns.second)
            {
                return true;
            }
        }
    }

    return false;
}

void Grid::draw(sf::RenderWindow& window)
{
    // TODO: Fix this. This will not work
    if (cellManager->cellOffset != sf::Vector2f({0, 0})) states.transform.translate(cellManager->cellOffset);

    window.draw(&vertexArray[0], vertexArray.getVertexCount(), sf::PrimitiveType::Triangles, states);

    if (movingCells.size() > 0)
    {
        updateMovingVertices();

        // TODO: combine into one vertex array
        for (int i = 0; i < movingCells.size(); i++)
        {
            window.draw(&movingCells[i].first[0], 6, sf::PrimitiveType::Triangles, states);
        }
    }
}