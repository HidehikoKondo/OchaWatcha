//
//  Common.h
//  ocha
//
//  Created by e-kondo on 2016/05/21.
//
//


#ifndef OgrePingPong_Common_h
#define OgrePingPong_Common_h

//キャラクター画像種類
enum ImageType
{
    Hero01,
    Enemy01,
    Bullet01,
    table,
    retry,
    
};

//キャラクター画像ファイル名
const std::map<ImageType, std::string> ImageFileName
{
    {ImageType::Hero01, "tyasen.png"},
    {ImageType::Enemy01, "enemy.png"},
    {ImageType::Bullet01, "bullet.png"},
    {ImageType::table, "table.png"},
    {ImageType::retry, "retry.png"},
};

//音声種類
enum SoundType
{
    GameMainBGM,
    racketEffect,
    boundEffect,
    
};

//音声ファイル名
const std::map<SoundType, std::string> SoundFileName
{
    {SoundType::GameMainBGM, "gameMain"},
    {SoundType::racketEffect, "racketEffect"},
    {SoundType::boundEffect, "boundEffect"},
};

//Key種類
enum KeyType
{
    Score_Key,
    HighScore_Key,
};

//スコアキー
const std::map<KeyType, std::string> ScoreKeyValue
{
    {KeyType::Score_Key, "scoreKey"},
    {KeyType::HighScore_Key, "highScoreKey"},
};

#endif
