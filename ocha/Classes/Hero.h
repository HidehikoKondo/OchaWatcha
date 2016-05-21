//
//  Hero.cpp
//  ocha
//
//  Created by e-kondo on 2016/05/21.
//
//

#ifndef __OgrePingPong__Hero__
#define __OgrePingPong__Hero__

#include <stdio.h>

////画像種類
//enum HeroType
//{
//    Hero01,
//    Enemy01,
//};


class Hero : public cocos2d::Sprite{
protected:
    std::string getFileName(ImageType heroType);  //画像ファイル名取得
    
public:
//    Hero();  //コンストラクタ
//    ~Hero();  //デストラクタ
    virtual bool init(ImageType heroType);  //初期化
    static Hero* create(ImageType heroType);  //インスタンス生成
    
//    CREATE_FUNC(Hero);
};

#endif /* defined(__OgrePingPong__Hero__) */
