#include "grid_vertices.hpp"

#include <algorithm>

#include "cell.hpp"
#include "../managers/cell_manager.hpp"
#include "grid.hpp"
#include "../tools/get_points.hpp"

GridVertices::GridVertices() {}

GridVertices::GridVertices(int gridLength, int gridHeight, CellManager* cellManager)
{
    this->gridLength = gridLength;
    this->gridHeight = gridHeight;

    this->cellManager = cellManager;

    // for easy access
    this->grid = cellManager->grid;

    init();
}

void GridVertices::init()
{
    vertices.setPrimitiveType(sf::PrimitiveType::Triangles);

    vertices.resize(gridLength * gridHeight * 6);

    for (unsigned int y = 0; y < gridHeight; y++)
    {
        for (unsigned int x = 0; x < gridLength; x++)
        {
            int index = (x + y * gridLength) * 6;
        
            vertices[index].position     = {x * cellManager->cellSize, y * cellManager->cellSize};
            vertices[index + 1].position = {x * cellManager->cellSize + cellManager->cellSize, y * cellManager->cellSize};
            vertices[index + 2].position = {x * cellManager->cellSize, y * cellManager->cellSize + cellManager->cellSize};
            vertices[index + 3].position = {x * cellManager->cellSize, y * cellManager->cellSize + cellManager->cellSize};
            vertices[index + 4].position = {x * cellManager->cellSize + cellManager->cellSize, y * cellManager->cellSize};
            vertices[index + 5].position = {x * cellManager->cellSize + cellManager->cellSize, y * cellManager->cellSize + cellManager->cellSize};
        
            updateSquare(x, y);
        }
    }
}

void GridVertices::updateSquare(unsigned int x, unsigned int y)
{
    if (x < gridLength && y < gridHeight)
    {
        int index = (x + y * gridLength) * 6;

        // This cell is not blank
        if (grid->at({x, y}) != nullptr)
        {
            bool isAMovingCell = false;

            if (movingCells.size() > 0)
            {
                for (int i = 0; i < movingCells.size(); i++)
                {
                    // If the current target position of the moving cell is this cell
                    if (std::get<1>(movingCells[i])[0] == sf::Vector2u(x, y))
                    {
                        isAMovingCell = true;

                        break;
                    }
                }
            }

            // cell is not blank and is not connected to a moving cell
            if (!isAMovingCell)
            {
                for (int i = 0; i < 6; i++)
                {
                    vertices[index + i].color = grid->at({x, y})->getColor();
                }

                return;
            }
        }
        
        // either this cell is blank, or it is connected to a moving cell
        for (int i = 0; i < 6; i++)
        {
            vertices[index + i].color = sf::Color::Transparent;
        }
    }
}

void GridVertices::updateStatic()
{
    for (unsigned int y = 0; y < gridHeight; y++)
    {
        for (unsigned int x = 0; x < gridLength; x++)
        {
            updateSquare(x, y);
        }
    }
    
    std::cout << "updated vertices\n";
}

void GridVertices::updateMoving()
{
    if (movingCells.size() > 0)
    {
        std::vector<int> movingCellsToErase;

        for (int i = 0; i < movingCells.size(); i++)
        {
            std::array<sf::Vertex, 6>* vertices = &std::get<0>(movingCells[i]);
            std::vector<sf::Vector2u>* targetPositions = &std::get<1>(movingCells[i]);
            Cell* cell = std::get<2>(movingCells[i]);

            // targetPos - position of top left vertex (currentPos)
            float xDiff = gridToWorldCoords(cellManager, (*targetPositions)[0], false).x - (*vertices)[0].position.x;
            float yDiff = gridToWorldCoords(cellManager, (*targetPositions)[0], false).y - (*vertices)[0].position.y;

            if (getDistance(sf::Vector2f(xDiff, yDiff)) < 0.01f * cellManager->cellSize)
            {
                if (targetPositions->size() > 1)
                {
                    targetPositions->erase(targetPositions->begin());
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
                    (*vertices)[j].position.x += xDiff / 2.f;
                    (*vertices)[j].position.y += yDiff / 2.f;
                }
            }
        }

        if (movingCellsToErase.size() > 0)
        {
            std::sort(movingCellsToErase.begin(), movingCellsToErase.end());

            for (int i = 0; i < movingCellsToErase.size(); i++)
            {
                movingCellsToErase[i] -= i;

                std::array<sf::Vertex, 6>* vertices = &std::get<0>(movingCells[movingCellsToErase[i]]);
                std::vector<sf::Vector2u>* targetPositions = &std::get<1>(movingCells[movingCellsToErase[i]]);
                Cell* cell = std::get<2>(movingCells[movingCellsToErase[i]]);

                sf::Vector2u posToUpdate = (*targetPositions)[0];

                movingCells.erase(movingCells.begin() + movingCellsToErase[i]);

                updateSquare(posToUpdate.x, posToUpdate.y);
            }
        }
    }
}

void GridVertices::draw(sf::RenderWindow& window)
{
    if (cellManager->cellOffset != sf::Vector2f({0, 0}))
    {
        sf::Transform newTransform;

        newTransform.translate(cellManager->cellOffset);

        states.transform = newTransform;
    }

    window.draw(&vertices[0], vertices.getVertexCount(), vertices.getPrimitiveType());

    // TODO: try to avoid a draw call for each moving cell
    for (int i = 0; i < movingCells.size(); i++)
    {
        window.draw(&std::get<0>(movingCells[i])[0], 6, sf::PrimitiveType::Triangles, states);
    }
}

void GridVertices::addMovingCell(unsigned int x, unsigned int y, sf::Vector2u targetPos, Cell* cell)
{
    if (!cell->canSmooth()) return;

    sf::Vector2f screenCurrentPos = {x * cellManager->cellSize, y * cellManager->cellSize};
    sf::Vector2f screenTargetPos = {targetPos.x * cellManager->cellSize, targetPos.y * cellManager->cellSize};

    // If this cell is already being represented by another moving cell

    if (movingCells.size() > 0)
    {
        for (int i = 0; i < movingCells.size(); i++)
        {
            // if the last target pos of the moving cell is equal to the start of this one
            if (std::get<1>(movingCells[i]).back() == sf::Vector2u(x, y))
            {
                std::array<sf::Vertex, 6>* vertices = &std::get<0>(movingCells[i]);
                std::vector<sf::Vector2u>* targetPositions = &std::get<1>(movingCells[i]);
                Cell* cell = std::get<2>(movingCells[i]);

                for (int j = 0; j < 6; j++)
                {
                    (*vertices)[j].color = cell->getColor();
                }

                sf::Vector2u targetBeforeLast;

                if (targetPositions->size() > 1)
                {
                    // if the moving cell is going many places, it will be here eventually \/
                    targetBeforeLast = (*targetPositions)[targetPositions->size() - 2];
                }
                else
                {
                    // if the moving cell has only one target, we use it to check for a straight line
                    targetBeforeLast = worldToGridCoords(cellManager, (*vertices)[0].position);
                }

                // on a vertical or horizontal line, can combine target positions
                if (targetBeforeLast.x == x || targetBeforeLast.y == y)
                {
                    targetPositions->back() = targetPos;

                    return;
                }

                // not a vertical or horizontal line, adding new target position
                targetPositions->emplace_back(targetPos);

                return;
            }
        }
    }


    // This cell is not currently being represented by a moving cell

    std::array<sf::Vertex, 6> newVertices;
    
    for (int i = 0; i < 6; i++)
    {
        newVertices[i].color = cell->getColor();
    }

    newVertices[0].position = {screenCurrentPos.x, screenCurrentPos.y};
    newVertices[1].position = {screenCurrentPos.x + cellManager->cellSize, screenCurrentPos.y};
    newVertices[2].position = {screenCurrentPos.x, screenCurrentPos.y + cellManager->cellSize};
    newVertices[3].position = {screenCurrentPos.x, screenCurrentPos.y + cellManager->cellSize};
    newVertices[4].position = {screenCurrentPos.x + cellManager->cellSize, screenCurrentPos.y};
    newVertices[5].position = {screenCurrentPos.x + cellManager->cellSize, screenCurrentPos.y + cellManager->cellSize};

    std::vector<sf::Vector2u> targetPositions = {targetPos};

    movingCells.emplace_back(newVertices, targetPositions, cell);
}