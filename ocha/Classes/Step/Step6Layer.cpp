//
//  Step6Layer.cpp
//  ocha
//
//  Created by OhsakaTakashi on 2016/05/21.
//
//

#include "Step6Layer.hpp"

#include "PrivateConfig.h"


USING_NS_CC;


#pragma mark -
Step6Layer::Step6Layer()
{
}
Step6Layer::~Step6Layer()
{
}


#pragma mark -
bool Step6Layer::init()
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
void Step6Layer::onEnter()
{
    Layer::onEnter();
}

void Step6Layer::onExit()
{
    Layer::onExit();
}
