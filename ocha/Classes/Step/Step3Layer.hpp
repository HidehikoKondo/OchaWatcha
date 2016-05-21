//
//  Step3Layer.hpp
//  ocha
//
//  Created by OhsakaTakashi on 2016/05/21.
//
//

#ifndef Step3Layer_hpp
#define Step3Layer_hpp

#include "cocos2d.h"


class Step3Layer : public cocos2d::Layer
{
protected:
    Step3Layer();
    virtual ~Step3Layer();

public:
    CREATE_FUNC(Step3Layer);

protected:
    virtual bool init() override;

protected:
    virtual void onEnter() override;
    virtual void onExit() override;
};
#endif
