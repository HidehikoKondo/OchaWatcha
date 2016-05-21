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
    std::string name = ImageFileName.at(ImageType::chasen);
    switch(heroType){
        case ImageType::chasen: name = ImageFileName.at(ImageType::chasen);; break;
        case ImageType::maccha: name = ImageFileName.at(ImageType::maccha);; break;
        case ImageType::yunomi1: name = ImageFileName.at(ImageType::yunomi1);; break;
        case ImageType::yunomi2: name = ImageFileName.at(ImageType::yunomi2);; break;
        default: name = ImageFileName.at(ImageType::chasen);
    }
    return name;
}

