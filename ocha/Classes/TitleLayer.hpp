//
//  TitleLayer.hpp
//  ocha
//
//  Created by OhsakaTakashi on 2016/05/21.
//
//

#ifndef TitleLayer_hpp
#define TitleLayer_hpp

#include "cocos2d.h"


class TitleLayer : public cocos2d::Layer
{
protected:
    TitleLayer();
    virtual ~TitleLayer();

public:
    CREATE_FUNC(TitleLayer);

protected:
    virtual bool init() override;

protected:
    virtual void onEnter() override;
    virtual void onExit() override;
};
#endif
