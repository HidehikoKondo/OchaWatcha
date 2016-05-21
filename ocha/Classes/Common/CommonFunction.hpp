//
//  CommonFunction.hpp
//  ocha
//
//  Created by OhsakaTakashi on 2016/05/21.
//
//

#ifndef CommonFunction_hpp
#define CommonFunction_hpp

#include "cocos2d.h"


class CommonFunction
{
#pragma mark - テンプレート
public:
    //enum class用 (intへ型変換)
    template <class T>
    static typename std::underlying_type<T>::type enumToInteger(T t)
    {
        return static_cast<typename std::underlying_type<T>::type>(t);
    }

public:
};
#endif
