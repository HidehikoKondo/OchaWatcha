//
//  InputLayer.cpp
//  ocha
//
//  Created by OhsakaTakashi on 2016/05/21.
//
//

#include "InputLayer.hpp"


USING_NS_CC;


#pragma mark -
InputLayer::InputLayer()
{
}
InputLayer::~InputLayer()
{
}


#pragma mark -
bool InputLayer::init()
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
void InputLayer::onEnter()
{
    Layer::onEnter();
}

void InputLayer::onExit()
{
    Layer::onExit();
}
