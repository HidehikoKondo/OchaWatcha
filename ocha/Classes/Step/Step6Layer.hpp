//
//  Step6Layer.hpp
//  ocha
//
//  Created by OhsakaTakashi on 2016/05/21.
//
//

#ifndef Step6Layer_hpp
#define Step6Layer_hpp

#include "cocos2d.h"


class Step6Layer : public cocos2d::Layer
{
protected:
    Step6Layer();
    virtual ~Step6Layer();

public:
    CREATE_FUNC(Step6Layer);

protected:
    virtual bool init() override;

protected:
    virtual void onEnter() override;
    virtual void onExit() override;
};
#endif
