#pragma once

#include <string>
#include <sstream>

struct Colors
{
    std::string Zombie;
    std::string Blood;
    std::string blackRed;
    std::string zombieBG;
    std::string LightRed;
    std::string Red;
    std::string Green;
    std::string Yellow;
    std::string Orange;
    std::string Blue;
    std::string Magenta;
    std::string BGCyan;
    std::string Cyan;
    std::string White;
    std::string Grey;
    std::string GreyBG;
    std::string Clean;
    std::string BGgreen;
    std::string BGred;
    std::string BGblue;
    std::string BGmagenta;
    std::string BGyellow;
    std::string BGorange;
    std::string BGwhite;
    std::string BGgrey;
    std::string BGclean;
    std::string bright;
    std::string dim;
    std::string gold;
    std::string BGgold;
    std::string black;
    std::string BGblack;
};

std::string rgbToString(int r, int g, int b, int bg_r, int bg_g, int bg_b)
{
    std::stringstream ss;
    ss << "\033[38;2;" << r << ";" << g << ";" << b << ";48;2;" << bg_r << ";" << bg_g << ";" << bg_b << "m";
    return ss.str();
}

std::string rgbToStringNoBG(int r, int g, int b)
{
    std::stringstream ss;
    ss << "\033[38;2;" << r << ";" << g << ";" << b << "m";
    return ss.str();
}

const Colors colors = {    
    .Zombie = rgbToStringNoBG(58,114,29),
    .Blood = rgbToString(136, 8, 8, 0, 0, 0),
    .blackRed= rgbToString(0,0,0, 255, 0, 0),
    .zombieBG = rgbToString(0,0,0, 58,114,29),
    .LightRed = rgbToString(255, 0, 0, 255, 0, 0),
    .Red = rgbToString(255, 0, 0, 0, 0, 0),  
    .Green = rgbToString(0, 255, 0, 0, 0, 0),
    .Yellow = rgbToString(255, 255, 0, 0, 0, 0),
    .Orange = rgbToString(255, 165, 0, 0, 0, 0),
    .Blue = rgbToString(0, 0, 255, 0, 0, 255),
    .Magenta = rgbToString(255, 0, 255, 255, 0, 255),
    .BGCyan = rgbToString(0, 255, 255, 0, 255, 255),
    .Cyan = rgbToString(0, 255, 255, 0, 255, 255),
    .White = rgbToString(255, 255, 255, 0, 0, 0),
    .Grey = rgbToString(128, 128, 128, 0,0,0),
    .GreyBG = rgbToString(0,0,0,128, 128, 128),
    .Clean = "\033[0m",
    .BGgreen = rgbToString(0, 255, 0, 0, 255, 0),
    .BGred = rgbToString(255, 0, 0, 255, 0, 0),
    .BGblue = rgbToString(0, 0, 255, 0, 0, 255),
    .BGmagenta = rgbToString(255, 0, 255, 255, 0, 255),
    .BGyellow = rgbToString(255, 255, 0, 255, 255, 0),
    .BGorange = rgbToString(0, 0, 0, 255, 165, 0),
    .BGwhite = rgbToString(255, 255, 255, 255, 255, 255),
    .BGgrey = rgbToString(128, 128, 128, 128, 128, 128),
    .BGclean = "\033[0m",
    .bright = "\033[1m",
    .dim = "\033[2m",
    .gold = rgbToString(255, 215, 0, 0, 0, 0),
    .BGgold = rgbToString(255, 215, 0, 255, 215, 0),
    .black = rgbToString(0, 0, 0, 0, 0, 0),
    .BGblack = rgbToString(0, 0, 0, 0, 0, 0),   
};

struct ColorRanges
{
    int minArea;
    int maxArea;
    std::string colorCode;
};

const ColorRanges colorRanges[] = {
    {0, 10, colors.White},
    {10, 20, colors.Yellow},
    {20, 30, colors.Green},
    {20, 30, colors.Red},
    {30, 40, colors.Green},
    {40, 50, colors.Cyan},
    {50, 60, colors.Blue},
    {60, 70, colors.Magenta},
    {80, 90, colors.BGwhite},
    {90, 100, colors.BGyellow},
    {100, 110, colors.BGred},
    {110, 120, colors.BGgreen},
    {120, 130, colors.BGCyan},
    {130, 140, colors.BGblue},
    {140, 150, colors.BGmagenta},
    {150, 160, colors.BGgrey},
    {160, 170, colors.BGwhite},
    {170, 180, colors.BGyellow},
    {180, 190, colors.BGred},
    {190, 200, colors.BGgreen},
    {200, 210, colors.BGCyan},
    {210, 220, colors.BGblue},
    {220, 230, colors.gold},
    {220, 230, colors.BGgold},
};
