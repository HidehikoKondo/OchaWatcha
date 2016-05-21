//
//  InputLayer.hpp
//  ocha
//
//  Created by OhsakaTakashi on 2016/05/21.
//
//

#ifndef InputLayer_hpp
#define InputLayer_hpp

#include "cocos2d.h"


class InputLayer : public cocos2d::Layer
{
protected:
    InputLayer();
    virtual ~InputLayer();

public:
    CREATE_FUNC(InputLayer);

protected:
    virtual bool init() override;

protected:
    virtual void onEnter() override;
    virtual void onExit() override;
};
#endif
