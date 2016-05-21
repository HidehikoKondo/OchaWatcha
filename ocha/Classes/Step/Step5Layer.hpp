//
//  Step5Layer.hpp
//  ocha
//
//  Created by OhsakaTakashi on 2016/05/21.
//
//

#ifndef Step5Layer_hpp
#define Step5Layer_hpp

#include "cocos2d.h"


class Step5Layer : public cocos2d::Layer
{
protected:
    Step5Layer();
    virtual ~Step5Layer();

public:
    CREATE_FUNC(Step5Layer);

protected:
    virtual bool init() override;

protected:
    virtual void onEnter() override;
    virtual void onExit() override;
};
#endif
