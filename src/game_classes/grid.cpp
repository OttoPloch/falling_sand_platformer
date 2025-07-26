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

            if (at({static_cast<unsigned int>(x), static_cast<unsigned int>(y)}) != nullptr)
            {
                vertexArray[index].color     = at({static_cast<unsigned int>(x), static_cast<unsigned int>(y)})->getColor();
                vertexArray[index + 1].color = at({static_cast<unsigned int>(x), static_cast<unsigned int>(y)})->getColor();
                vertexArray[index + 2].color = at({static_cast<unsigned int>(x), static_cast<unsigned int>(y)})->getColor();
                vertexArray[index + 3].color = at({static_cast<unsigned int>(x), static_cast<unsigned int>(y)})->getColor();
                vertexArray[index + 4].color = at({static_cast<unsigned int>(x), static_cast<unsigned int>(y)})->getColor();
                vertexArray[index + 5].color = at({static_cast<unsigned int>(x), static_cast<unsigned int>(y)})->getColor();
            }
            else
            {
                vertexArray[index].color     = sf::Color::Transparent;
                vertexArray[index + 1].color = sf::Color::Transparent;
                vertexArray[index + 2].color = sf::Color::Transparent;
                vertexArray[index + 3].color = sf::Color::Transparent;
                vertexArray[index + 4].color = sf::Color::Transparent;
                vertexArray[index + 5].color = sf::Color::Transparent;
            }
        }
    }
}

void Grid::updateVertices()
{
    for (int y = 0; y < getSize(); y++)
    {
        for (int x = 0; x < getSizeOfRow(y); x++)
        {
            int index = (x + y * getSizeOfRow(y)) * 6;

            if (at({static_cast<unsigned int>(x), static_cast<unsigned int>(y)}) != nullptr)
            {
                vertexArray[index].color     = at({static_cast<unsigned int>(x), static_cast<unsigned int>(y)})->getColor();
                vertexArray[index + 1].color = at({static_cast<unsigned int>(x), static_cast<unsigned int>(y)})->getColor();
                vertexArray[index + 2].color = at({static_cast<unsigned int>(x), static_cast<unsigned int>(y)})->getColor();
                vertexArray[index + 3].color = at({static_cast<unsigned int>(x), static_cast<unsigned int>(y)})->getColor();
                vertexArray[index + 4].color = at({static_cast<unsigned int>(x), static_cast<unsigned int>(y)})->getColor();
                vertexArray[index + 5].color = at({static_cast<unsigned int>(x), static_cast<unsigned int>(y)})->getColor();
            }
            else
            {
                vertexArray[index].color     = sf::Color::Transparent;
                vertexArray[index + 1].color = sf::Color::Transparent;
                vertexArray[index + 2].color = sf::Color::Transparent;
                vertexArray[index + 3].color = sf::Color::Transparent;
                vertexArray[index + 4].color = sf::Color::Transparent;
                vertexArray[index + 5].color = sf::Color::Transparent;
            }
        }
    }
}

void Grid::updateSpecificVertices(sf::Vector2u position)
{
    int index = (position.x + position.y * getSizeOfRow(position.y)) * 6;

    if (at({static_cast<unsigned int>(position.x), static_cast<unsigned int>(position.y)}) != nullptr)
    {
        vertexArray[index].color     = at({static_cast<unsigned int>(position.x), static_cast<unsigned int>(position.y)})->getColor();
        vertexArray[index + 1].color = at({static_cast<unsigned int>(position.x), static_cast<unsigned int>(position.y)})->getColor();
        vertexArray[index + 2].color = at({static_cast<unsigned int>(position.x), static_cast<unsigned int>(position.y)})->getColor();
        vertexArray[index + 3].color = at({static_cast<unsigned int>(position.x), static_cast<unsigned int>(position.y)})->getColor();
        vertexArray[index + 4].color = at({static_cast<unsigned int>(position.x), static_cast<unsigned int>(position.y)})->getColor();
        vertexArray[index + 5].color = at({static_cast<unsigned int>(position.x), static_cast<unsigned int>(position.y)})->getColor();
    }
    else
    {
        vertexArray[index].color     = sf::Color::Transparent;
        vertexArray[index + 1].color = sf::Color::Transparent;
        vertexArray[index + 2].color = sf::Color::Transparent;
        vertexArray[index + 3].color = sf::Color::Transparent;
        vertexArray[index + 4].color = sf::Color::Transparent;
        vertexArray[index + 5].color = sf::Color::Transparent;
    }
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
    
                // iterates through regular cells
                if (theGrid[y][x] != nullptr)
                {
                    if (theGrid[y][x]->getWeight() > -1)
                    {
                        if (theGrid[y][x]->tick()) gridHasChanged = true;
                    }
                }
    
                int oppY = (theGrid.size() - 1) - y;
    
                // iterates through rising cells (like smoke)
                if (theGrid[oppY][x] != nullptr)
                {
                    if (theGrid[oppY][x]->getWeight() < 0)
                    {
                        if (theGrid[oppY][x]->tick()) gridHasChanged = true;
                    }
                }
            }
        }
    }

    if (gridHasChanged) updateVertices();
}

void Grid::draw(sf::RenderWindow& window)
{
    if (cellManager->cellOffset != sf::Vector2f({0, 0})) states.transform.translate(cellManager->cellOffset);

    window.draw(&vertexArray[0], vertexArray.getVertexCount(), sf::PrimitiveType::Triangles, states);
}