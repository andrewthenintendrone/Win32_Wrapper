#pragma once
#include "Window.h"
#include <stdio.h>
#include <time.h>
#include <vector>
#include <string>

namespace winWrap
{
    class myWindow : public Window
    {
    public:
        myWindow() { m_image = nullptr; };
        ~myWindow() {};

        void create(LPCTSTR className, LPCTSTR windowTitle, DWORD dwStyle, int xPosition, int yPosition, int width, int height, HWND parent);
    protected:

        virtual void onCreate();
        virtual void onPaint(HDC hdc);
        virtual void onLeftMouseButtonDown(int xPos, int yPos);
        virtual void onLeftClickButton(HWND buttonID);
        virtual void onResize();
        virtual void onPressEnter();
        virtual void onClose();
    private:
        HWND m_textBox1;
        HWND m_button1;
        HWND m_loadBar1;
        RECT m_clientRect;
        int m_width;
        int m_height;
        HBRUSH m_backgroundBrush;

        unsigned int m_pick;

        std::vector<std::wstring> pics =
        {
            L"abra",
            L"aerodactyl",
            L"alakazam",
            L"arbok",
            L"arcanine",
            L"articuno",
            L"beedrill",
            L"bellsprout",
            L"blastoise",
            L"bulbasaur",
            L"butterfree",
            L"caterpie",
            L"chansey",
            L"charizard",
            L"charmander",
            L"charmeleon",
            L"clefable",
            L"clefairy",
            L"cloyster",
            L"cubone",
            L"dewgong",
            L"diglett",
            L"ditto",
            L"dodrio",
            L"doduo",
            L"dragonair",
            L"dragonite",
            L"dratini",
            L"drowzee",
            L"dugtrio",
            L"eevee",
            L"ekans",
            L"electabuzz",
            L"electrode",
            L"exeggcute",
            L"exeggutor",
            L"farfetchd",
            L"fearow",
            L"flareon",
            L"gastly",
            L"gengar",
            L"geodude",
            L"gloom",
            L"golbat",
            L"goldeen",
            L"golduck",
            L"golem",
            L"graveler",
            L"grimer",
            L"growlithe",
            L"gyarados",
            L"haunter",
            L"hitmonchan",
            L"hitmonlee",
            L"horsea",
            L"hypno",
            L"ivysaur",
            L"jigglypuff",
            L"jolteon",
            L"jynx",
            L"kabuto",
            L"kabutops",
            L"kadabra",
            L"kakuna",
            L"kangaskhan",
            L"kingler",
            L"koffing",
            L"krabby",
            L"lapras",
            L"lickitung",
            L"machamp",
            L"machoke",
            L"machop",
            L"magikarp",
            L"magmar",
            L"magnemite",
            L"magneton",
            L"mankey",
            L"marowak",
            L"meowth",
            L"metapod",
            L"mew",
            L"mewtwo",
            L"missingno",
            L"moltres",
            L"mrmime",
            L"muk",
            L"nidoking",
            L"nidoqueen",
            L"nidoranf",
            L"nidoranm",
            L"nidorina",
            L"nidorino",
            L"ninetales",
            L"oddish",
            L"omanyte",
            L"omastar",
            L"onix",
            L"paras",
            L"parasect",
            L"persian",
            L"pidgeot",
            L"pidgeotto",
            L"pidgey",
            L"pikachu",
            L"pinsir",
            L"poliwag",
            L"poliwhirl",
            L"poliwrath",
            L"ponyta",
            L"porygon",
            L"primeape",
            L"psyduck",
            L"raichu",
            L"rapidash",
            L"raticate",
            L"rattata",
            L"rhydon",
            L"rhyhorn",
            L"sandshrew",
            L"sandslash",
            L"scyther",
            L"seadra",
            L"seaking",
            L"seel",
            L"shellder",
            L"slowbro",
            L"slowpoke",
            L"snorlax",
            L"spearow",
            L"squirtle",
            L"starmie",
            L"staryu",
            L"substitute",
            L"tangela",
            L"tauros",
            L"tentacool",
            L"tentacruel",
            L"vaporeon",
            L"venomoth",
            L"venonat",
            L"venusaur",
            L"victreebel",
            L"vileplume",
            L"voltorb",
            L"vulpix",
            L"wartortle",
            L"weedle",
            L"weepinbell",
            L"weezing",
            L"wigglytuff",
            L"zapdos",
            L"zubat"
            };

        Gdiplus::Image* m_image;
    };
}
