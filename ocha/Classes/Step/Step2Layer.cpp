//
//  Step2Layer.cpp
//  ocha
//
//  Created by OhsakaTakashi on 2016/05/21.
//
//

#include "Step2Layer.hpp"

#include "PrivateConfig.h"


USING_NS_CC;


#pragma mark -
Step2Layer::Step2Layer()
{
}
Step2Layer::~Step2Layer()
{
}


#pragma mark -
bool Step2Layer::init()
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
void Step2Layer::onEnter()
{
    Layer::onEnter();
}

void Step2Layer::onExit()
{
    Layer::onExit();
}
