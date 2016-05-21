//
//  Step4Layer.hpp
//  ocha
//
//  Created by OhsakaTakashi on 2016/05/21.
//
//

#ifndef Step4Layer_hpp
#define Step4Layer_hpp

#include "cocos2d.h"


class Step4Layer : public cocos2d::Layer
{
protected:
    Step4Layer();
    virtual ~Step4Layer();

public:
    CREATE_FUNC(Step4Layer);

protected:
    virtual bool init() override;

protected:
    virtual void onEnter() override;
    virtual void onExit() override;
};
#endif
