//
//  Step4Layer.cpp
//  ocha
//
//  Created by OhsakaTakashi on 2016/05/21.
//
//

#include "Step4Layer.hpp"

#include "PrivateConfig.h"


USING_NS_CC;


#pragma mark -
Step4Layer::Step4Layer()
{
}
Step4Layer::~Step4Layer()
{
}


#pragma mark -
bool Step4Layer::init()
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
void Step4Layer::onEnter()
{
    Layer::onEnter();
}

void Step4Layer::onExit()
{
    Layer::onExit();
}
