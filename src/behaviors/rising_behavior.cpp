#include "rising_behavior.hpp"

RisingBehavior::RisingBehavior() : Behavior("rise", -1) {}

RisingBehavior::RisingBehavior(int riseSpeed) : Behavior("rise", riseSpeed) {}

bool RisingBehavior::update(Grid* grid, sf::Vector2u gridPos)
{
    if (gridPos.y > 0)
    {
        int myRiseSpeed = grid->at(gridPos)->getOptionalSetting("rise");

        if (myRiseSpeed > 0)
        {
            int validSpacesUp = 0;

            for (int i = 1; i <= myRiseSpeed; i++)
            {
                if (i > gridPos.y) 
                {
                    break;
                }

                if (grid->at({gridPos.x, gridPos.y - i}) == nullptr)
                {
                    validSpacesUp++;
                }
                else
                {
                    break;
                }
            }

            if (validSpacesUp > 0)
            {
                grid->moveCell(gridPos, {0, -validSpacesUp});

                return true;
            }
        }
    }
    
    return false;
}