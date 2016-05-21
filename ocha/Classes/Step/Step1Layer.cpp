//
//  Step1Layer.cpp
//  ocha
//
//  Created by OhsakaTakashi on 2016/05/21.
//
//

#include "Step1Layer.hpp"


USING_NS_CC;


#pragma mark -
Step1Layer::Step1Layer()
{
}
Step1Layer::~Step1Layer()
{
}


#pragma mark -
bool Step1Layer::init()
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
void Step1Layer::onEnter()
{
    Layer::onEnter();
}

void Step1Layer::onExit()
{
    Layer::onExit();
}
