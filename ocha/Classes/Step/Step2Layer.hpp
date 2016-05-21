//
//  Step2Layer.hpp
//  ocha
//
//  Created by OhsakaTakashi on 2016/05/21.
//
//

#ifndef Step2Layer_hpp
#define Step2Layer_hpp

#include "cocos2d.h"


class Step2Layer : public cocos2d::Layer
{
protected:
    Step2Layer();
    virtual ~Step2Layer();

public:
    CREATE_FUNC(Step2Layer);

protected:
    virtual bool init() override;

protected:
    virtual void onEnter() override;
    virtual void onExit() override;
};
#endif
