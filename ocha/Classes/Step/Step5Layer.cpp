//
//  Step5Layer.cpp
//  ocha
//
//  Created by OhsakaTakashi on 2016/05/21.
//
//

#include "Step5Layer.hpp"


USING_NS_CC;


#pragma mark -
Step5Layer::Step5Layer()
{
}
Step5Layer::~Step5Layer()
{
}


#pragma mark -
bool Step5Layer::init()
{
    auto result = false;

    do
    {
        if (! Layer::init())
        {
            break;
        }

        result = true;
    } while (0);

    return result;
}


#pragma mark -
void Step5Layer::onEnter()
{
    Layer::onEnter();
}

void Step5Layer::onExit()
{
    Layer::onExit();
}
