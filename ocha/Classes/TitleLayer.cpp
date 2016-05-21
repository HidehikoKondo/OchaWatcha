//
//  TitleLayer.cpp
//  ocha
//
//  Created by OhsakaTakashi on 2016/05/21.
//
//

#include "TitleLayer.hpp"

#include "PrivateConfig.h"


USING_NS_CC;


#pragma mark -
TitleLayer::TitleLayer()
{
}
TitleLayer::~TitleLayer()
{
}


#pragma mark -
bool TitleLayer::init()
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
void TitleLayer::onEnter()
{
    Layer::onEnter();
}

void TitleLayer::onExit()
{
    Layer::onExit();
}
