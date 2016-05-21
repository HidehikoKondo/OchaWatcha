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
    chasen,
    maccha,
    yunomi1,
    yunomi2,
    retry,
    
};

//キャラクター画像ファイル名
const std::map<ImageType, std::string> ImageFileName
{
    {ImageType::chasen, "chasen.png"},
    {ImageType::maccha, "maccha.png"},
    {ImageType::yunomi1, "yunomi1.png"},
    {ImageType::yunomi2, "yunomi2.png"},
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
