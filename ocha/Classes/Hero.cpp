//
//  Hero.h
//  ocha
//
//  Created by e-kondo on 2016/05/21.
//
//

#include "Hero.h"

//----------------------------------------------------
//コンストラクタ
//----------------------------------------------------
//Hero::Hero(){
//}

//----------------------------------------------------
//インスタンス生成
//----------------------------------------------------
Hero* Hero::create(ImageType heroType){
    Hero* pRet = new Hero();
    if(pRet && pRet->init(heroType)){
        pRet->autorelease();
        return pRet;
    }else{
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

//----------------------------------------------------
//初期化
//----------------------------------------------------
bool Hero::init(ImageType heroType){
    if(!Sprite::initWithFile(getFileName(heroType))){
        return false;
    }
    
    return true;
}

//----------------------------------------------------
//画像ファイル名取得
//----------------------------------------------------
std::string Hero::getFileName(ImageType heroType){
    std::string name = ImageFileName.at(ImageType::Hero01);
    switch(heroType){
        case ImageType::Hero01: name = ImageFileName.at(ImageType::Hero01);; break;
        case ImageType::Enemy01: name = ImageFileName.at(ImageType::Enemy01);; break;
        default: name = ImageFileName.at(ImageType::Hero01);
    }
    return name;
}

