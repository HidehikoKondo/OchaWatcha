//
//  Step3Layer.cpp
//  ocha
//
//  Created by OhsakaTakashi on 2016/05/21.
//
//

#include "Step3Layer.hpp"


USING_NS_CC;


#pragma mark -
Step3Layer::Step3Layer()
{
}
Step3Layer::~Step3Layer()
{
}


#pragma mark -
bool Step3Layer::init()
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
void Step3Layer::onEnter()
{
    Layer::onEnter();
}

void Step3Layer::onExit()
{
    Layer::onExit();
}
