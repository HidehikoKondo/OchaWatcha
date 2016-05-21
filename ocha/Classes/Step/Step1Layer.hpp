//
//  Step1Layer.hpp
//  ocha
//
//  Created by OhsakaTakashi on 2016/05/21.
//
//

#ifndef Step1Layer_hpp
#define Step1Layer_hpp

#include "cocos2d.h"


class Step1Layer : public cocos2d::Layer
{
protected:
    Step1Layer();
    virtual ~Step1Layer();

public:
    CREATE_FUNC(Step1Layer);

protected:
    virtual bool init() override;

protected:
    virtual void onEnter() override;
    virtual void onExit() override;
};
#endif
