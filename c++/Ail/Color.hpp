////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __COLOR_H__
#define __COLOR_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Color
// ----- -----
class __DECLSPEC__ Color
{
    private:
     COLORREF       Value;
    public:
                    Color();
                    Color(const Color&);
                    Color(COLORREF);
                    Color(uint);
                    Color(byte, byte, byte);
                    Color(byte, byte, byte, byte);
                    Color(const PALETTEENTRY&);
                    Color(const RGBQUAD&);
                    Color(const RGBTRIPLE&);

     const Color&   operator = (const Color&);

                    operator COLORREF ()            const;

     bool           operator == (const Color&)      const;
     bool           operator != (const Color&)      const;
     bool           operator == (COLORREF)          const;
     bool           operator != (COLORREF)          const;

     COLORREF       GetValue()                      const;
     void           SetValue(const COLORREF&);

     ushort         GetIndex()                      const;
     Color          GetRgb()                        const;
     Color          GetPalIndex()                   const;
     Color          GetPalRelative()                const;

     byte           GetRed()                        const;
     byte           GetGreen()                      const;
     byte           GetBlue()                       const;
     byte           GetFlags()                      const;
     bool           IsSysColor()                    const;
     bool           IsSpecialColor()                const;

     // colors ! ...
     static const Color None;
     static const Color Transparent;

     static const Color Black;
     static const Color Gray;
     static const Color MediumGray;
     static const Color LtGray;
     static const Color LtRed;
     static const Color LtGreen;
     static const Color LtYellow;
     static const Color LtBlue;
     static const Color LtMagenta;
     static const Color LtCyan;
     static const Color DarkBlue;
     static const Color DarkGreen;
     static const Color Brown;
     static const Color BlueGreen;
     static const Color DarkPurple;
     static const Color Olive;
     static const Color PaleGreen;
     static const Color LightBlue;
     static const Color OffWhite;
     static const Color White;

     static const Color ToolTip;

     static const Color SysScrollbar;
     static const Color SysDesktop;
     static const Color SysActiveCaption;
     static const Color SysInactiveCaption;
     static const Color SysMenu;
     static const Color SysWindow;
     static const Color SysWindowFrame;
     static const Color SysMenuText;
     static const Color SysWindowText;
     static const Color SysCaptionText;
     static const Color SysActiveBorder;
     static const Color SysInactiveBorder;
     static const Color SysAppWorkspace;
     static const Color SysHighlight;
     static const Color SysHighlightText;
     static const Color Sys3dFace;
     static const Color Sys3dShadow;
     static const Color SysGrayText;
     static const Color SysBtnText;
     static const Color SysInactiveCaptionText;
     static const Color Sys3dHighlight;
     static const Color Sys3dDkShadow;
     static const Color Sys3dLight;
     static const Color SysInfoText;
     static const Color SysInfoBk;

     // colors' names ! ...
     static const tchar CharBlack[TEXT_SIZE_SMALL];
     static const tchar CharGray[TEXT_SIZE_SMALL];
     static const tchar CharMediumGray[TEXT_SIZE_SMALL];
     static const tchar CharLtGray[TEXT_SIZE_SMALL];
     static const tchar CharLtRed[TEXT_SIZE_SMALL];
     static const tchar CharLtGreen[TEXT_SIZE_SMALL];
     static const tchar CharLtYellow[TEXT_SIZE_SMALL];
     static const tchar CharLtBlue[TEXT_SIZE_SMALL];
     static const tchar CharLtMagenta[TEXT_SIZE_SMALL];
     static const tchar CharLtCyan[TEXT_SIZE_SMALL];
     static const tchar CharDarkBlue[TEXT_SIZE_SMALL];
     static const tchar CharDarkGreen[TEXT_SIZE_SMALL];
     static const tchar CharBrown[TEXT_SIZE_SMALL];
     static const tchar CharBlueGreen[TEXT_SIZE_SMALL];
     static const tchar CharDarkPurple[TEXT_SIZE_SMALL];
     static const tchar CharOlive[TEXT_SIZE_SMALL];
     static const tchar CharPaleGreen[TEXT_SIZE_SMALL];
     static const tchar CharLightBlue[TEXT_SIZE_SMALL];
     static const tchar CharOffWhite[TEXT_SIZE_SMALL];
     static const tchar CharWhite[TEXT_SIZE_SMALL];
     static const tchar CharTransparent[TEXT_SIZE_SMALL];
};
////////////////////////////////////////////////////////////////////////////////////////
// Colors
// ------
// Shades of Black
const COLORREF  ConstColorBlack               = 0x00000000;  // RGB(  0,   0,   0)

// Shades of Blue
const COLORREF  ConstColorAliceBlue           = 0x00F0F8FF;  // RGB(240, 248, 255)
const COLORREF  ConstColorBlueViolet          = 0x008A2BE2;  // RGB(138,  43, 226)
const COLORREF  ConstColorCadetBlue           = 0x005F9EA0;  // RGB(95,  158, 160)
const COLORREF  ConstColorCadetBlue1          = 0x0098F5FF;  // RGB(152, 245, 255)
const COLORREF  ConstColorCadetBlue2          = 0x008EE5EE;  // RGB(142, 229, 238)
const COLORREF  ConstColorCadetBlue3          = 0x007AC5CD;  // RGB(122, 197, 205)
const COLORREF  ConstColorCadetBlue4          = 0x0053868B;  // RGB( 83, 134, 139)
const COLORREF  ConstColorCornflowerBlue      = 0x006495ED;  // RGB(100, 149, 237)
const COLORREF  ConstColorDarkSlateBlue       = 0x00483D8B;  // RGB( 72,  61, 139)
const COLORREF  ConstColorDarkTurquoise       = 0x0000CED1;  // RGB(  0, 206, 209)
const COLORREF  ConstColorDeepSkyBlue         = 0x0000BFFF;  // RGB(  0, 191, 255)
const COLORREF  ConstColorDeepSkyBlue1        = 0x0000BFFF;  // RGB(  0, 191, 255)
const COLORREF  ConstColorDeepSkyBlue2        = 0x0000B2EE;  // RGB(  0, 178, 238)
const COLORREF  ConstColorDeepSkyBlue3        = 0x00009ACD;  // RGB(  0, 154, 205)
const COLORREF  ConstColorDeepSkyBlue4        = 0x0000688B;  // RGB(  0, 104, 139)
const COLORREF  ConstColorDodgerBlue          = 0x001E90FF;  // RGB( 30, 144, 255)
const COLORREF  ConstColorDodgerBlue1         = 0x001E90FF;  // RGB( 30, 144, 255)
const COLORREF  ConstColorDodgerBlue2         = 0x001C86EE;  // RGB( 28, 134, 238)
const COLORREF  ConstColorDodgerBlue3         = 0x001874CD;  // RGB( 24, 116, 205)
const COLORREF  ConstColorDodgerBlue4         = 0x00104E8B;  // RGB( 16,  78, 139)
const COLORREF  ConstColorLightBlue           = 0x00ADD8E6;  // RGB(173, 216, 230)
const COLORREF  ConstColorLightBlue1          = 0x00BFEFFF;  // RGB(191, 239, 255)
const COLORREF  ConstColorLightBlue2          = 0x00B2DFEE;  // RGB(178, 223, 238)
const COLORREF  ConstColorLightBlue3          = 0x009AC0CD;  // RGB(154, 192, 205)
const COLORREF  ConstColorLightBlue4          = 0x0068838B;  // RGB(104, 131, 139)
const COLORREF  ConstColorLightCyan           = 0x00E0FFFF;  // RGB(224, 255, 255)
const COLORREF  ConstColorLightCyan1          = 0x00E0FFFF;  // RGB(224, 255, 255)
const COLORREF  ConstColorLightCyan2          = 0x00D1EEEE;  // RGB(209, 238, 238)
const COLORREF  ConstColorLightCyan3          = 0x00B4CDCD;  // RGB(180, 205, 205)
const COLORREF  ConstColorLightCyan4          = 0x007A8B8B;  // RGB(122, 139, 139)
const COLORREF  ConstColorLightSkyBlue        = 0x0087CEFA;  // RGB(135, 206, 250)
const COLORREF  ConstColorLightSkyBlue1       = 0x00B0E2FF;  // RGB(176, 226, 255)
const COLORREF  ConstColorLightSkyBlue2       = 0x00A4D3EE;  // RGB(164, 211, 238)
const COLORREF  ConstColorLightSkyBlue3       = 0x008DB6CD;  // RGB(141, 182, 205)
const COLORREF  ConstColorLightSkyBlue4       = 0x00607B8B;  // RGB( 96, 123, 139)
const COLORREF  ConstColorLightSlateBlue      = 0x008470FF;  // RGB(132, 112, 255)
const COLORREF  ConstColorLightSteelBlue      = 0x00B0C4DE;  // RGB(176, 196, 222)
const COLORREF  ConstColorLightSteelBlue1     = 0x00CAE1FF;  // RGB(202, 225, 255)
const COLORREF  ConstColorLightSteelBlue2     = 0x00BCD2EE;  // RGB(188, 210, 238)
const COLORREF  ConstColorLightSteelBlue3     = 0x00A2B5CD;  // RGB(162, 181, 205)
const COLORREF  ConstColorLightSteelBlue4     = 0x006E7B8B;  // RGB(110, 123, 139)
const COLORREF  ConstColorMediumAquamarine    = 0x0066CDAA;  // RGB(102, 205, 170)
const COLORREF  ConstColorMediumBlue          = 0x000000CD;  // RGB(  0,   0, 205)
const COLORREF  ConstColorMediumSlateBlue     = 0x007B68EE;  // RGB(123, 104, 238)
const COLORREF  ConstColorMediumTurquoise     = 0x0048D1CC;  // RGB( 72, 209, 204)
const COLORREF  ConstColorMidnightBlue        = 0x00191970;  // RGB( 25,  25, 112)
const COLORREF  ConstColorNavyBlue            = 0x00000080;  // RGB(  0,   0, 128)
const COLORREF  ConstColorPaleTurquoise       = 0x00AFEEEE;  // RGB(175, 238, 238)
const COLORREF  ConstColorPaleTurquoise1      = 0x00BBFFFF;  // RGB(187, 255, 255)
const COLORREF  ConstColorPaleTurquoise2      = 0x00AEEEEE;  // RGB(174, 238, 238)
const COLORREF  ConstColorPaleTurquoise3      = 0x0096CDCD;  // RGB(150, 205, 205)
const COLORREF  ConstColorPaleTurquoise4      = 0x00668B8B;  // RGB(102, 139, 139)
const COLORREF  ConstColorPowderBlue          = 0x00B0E0E6;  // RGB(176, 224, 230)
const COLORREF  ConstColorRoyalBlue           = 0x004169E1;  // RGB( 65, 105, 225)
const COLORREF  ConstColorRoyalBlue1          = 0x004876FF;  // RGB( 72, 118, 255)
const COLORREF  ConstColorRoyalBlue2          = 0x00436EEE;  // RGB( 67, 110, 238)
const COLORREF  ConstColorRoyalBlue3          = 0x003A5FCD;  // RGB( 58,  95, 205)
const COLORREF  ConstColorRoyalBlue4          = 0x0027408B;  // RGB( 39,  64, 139)
const COLORREF  ConstColorSkyBlue             = 0x0087CEEB;  // RGB(135, 206, 235)
const COLORREF  ConstColorSkyBlue1            = 0x0087CEFF;  // RGB(135, 206, 255)
const COLORREF  ConstColorSkyBlue2            = 0x007EC0EE;  // RGB(126, 192, 238)
const COLORREF  ConstColorSkyBlue3            = 0x006CA6CD;  // RGB(108, 166, 205)
const COLORREF  ConstColorSkyBlue4            = 0x004A708B;  // RGB( 74, 112, 139)
const COLORREF  ConstColorSlateBlue           = 0x006A5ACD;  // RGB(106,  90, 205)
const COLORREF  ConstColorSlateBlue1          = 0x00836FFF;  // RGB(131, 111, 255)
const COLORREF  ConstColorSlateBlue2          = 0x007A67EE;  // RGB(122, 103, 238)
const COLORREF  ConstColorSlateBlue3          = 0x006959CD;  // RGB(105,  89, 205)
const COLORREF  ConstColorSlateBlue4          = 0x00473C8B;  // RGB( 71,  60, 139)
const COLORREF  ConstColorSteelBlue           = 0x004682B4;  // RGB( 70, 130, 180)
const COLORREF  ConstColorSteelBlue1          = 0x0063B8FF;  // RGB( 99, 184, 255)
const COLORREF  ConstColorSteelBlue2          = 0x005CACEE;  // RGB( 92, 172, 238)
const COLORREF  ConstColorSteelBlue3          = 0x004F94CD;  // RGB( 79, 148, 205)
const COLORREF  ConstColorSteelBlue4          = 0x0036648B;  // RGB( 54, 100, 139)
const COLORREF  ConstColorAquamarine          = 0x007FFFD4;  // RGB(127, 255, 212)
const COLORREF  ConstColorAquamarine1         = 0x007FFFD4;  // RGB(127, 255, 212)
const COLORREF  ConstColorAquamarine2         = 0x0076EEC6;  // RGB(118, 238, 198)
const COLORREF  ConstColorAquamarine3         = 0x0066CDAA;  // RGB(102, 205, 170)
const COLORREF  ConstColorAquamarine4         = 0x00458B74;  // RGB( 69, 139, 116)
const COLORREF  ConstColorAzure               = 0x00F0FFFF;  // RGB(240, 255, 255)
const COLORREF  ConstColorAzure1              = 0x00F0FFFF;  // RGB(240, 255, 255)
const COLORREF  ConstColorAzure2              = 0x00E0EEEE;  // RGB(224, 238, 238)
const COLORREF  ConstColorAzure3              = 0x00C1CDCD;  // RGB(193, 205, 205)
const COLORREF  ConstColorAzure4              = 0x00838B8B;  // RGB(131, 139, 139)
const COLORREF  ConstColorBlue                = 0x000000FF;  // RGB(  0,   0, 255)
const COLORREF  ConstColorBlue1               = 0x000000FF;  // RGB(  0,   0, 255)
const COLORREF  ConstColorBlue2               = 0x000000EE;  // RGB(  0,   0, 238)
const COLORREF  ConstColorBlue3               = 0x000000CD;  // RGB(  0,   0, 205)
const COLORREF  ConstColorBlue4               = 0x0000008B;  // RGB(  0,   0, 139)
const COLORREF  ConstColorCyan                = 0x0000FFFF;  // RGB(  0, 255, 255)
const COLORREF  ConstColorCyan1               = 0x0000FFFF;  // RGB(  0, 255, 255)
const COLORREF  ConstColorCyan2               = 0x0000EEEE;  // RGB(  0, 238, 238)
const COLORREF  ConstColorCyan3               = 0x0000CDCD;  // RGB(  0, 205, 205)
const COLORREF  ConstColorCyan4               = 0x00008B8B;  // RGB(  0, 139, 139)
const COLORREF  ConstColorNavy                = 0x00000080;  // RGB(  0,   0, 128)
const COLORREF  ConstColorTurquoise           = 0x0040E0D0;  // RGB( 64, 224, 208)
const COLORREF  ConstColorTurquoise1          = 0x0000F5FF;  // RGB(  0, 245, 255)
const COLORREF  ConstColorTurquoise2          = 0x0000E5EE;  // RGB(  0, 229, 238)
const COLORREF  ConstColorTurquoise3          = 0x0000C5CD;  // RGB(  0, 197, 205)
const COLORREF  ConstColorTurquoise4          = 0x0000868B;  // RGB(  0, 134, 139)

// Shades of Brown
const COLORREF  ConstColorRosyBrown           = 0x00BC8F8F;  // RGB(188, 143, 143)
const COLORREF  ConstColorRosyBrown1          = 0x00FFC1C1;  // RGB(255, 193, 193)
const COLORREF  ConstColorRosyBrown2          = 0x00EEB4B4;  // RGB(238, 180, 180)
const COLORREF  ConstColorRosyBrown3          = 0x00CD9B9B;  // RGB(205, 155, 155)
const COLORREF  ConstColorRosyBrown4          = 0x008B6969;  // RGB(139, 105, 105)
const COLORREF  ConstColorSaddleBrown         = 0x008B4513;  // RGB(139,  69,  19)
const COLORREF  ConstColorSandyBrown          = 0x00F4A460;  // RGB(244, 164,  96)
const COLORREF  ConstColorBeige               = 0x00F5F5DC;  // RGB(245, 245, 220)
const COLORREF  ConstColorBrown               = 0x00A52A2A;  // RGB(165,  42,  42)
const COLORREF  ConstColorBrown1              = 0x00FF4040;  // RGB(255,  64,  64)
const COLORREF  ConstColorBrown2              = 0x00EE3B3B;  // RGB(238,  59,  59)
const COLORREF  ConstColorBrown3              = 0x00CD3333;  // RGB(205,  51,  51)
const COLORREF  ConstColorBrown4              = 0x008B2323;  // RGB(139,  35,  35)
const COLORREF  ConstColorBurlywood           = 0x00DEB887;  // RGB(222, 184, 135)
const COLORREF  ConstColorBurlywood1          = 0x00FFD39B;  // RGB(255, 211, 155)
const COLORREF  ConstColorBurlywood2          = 0x00EEC591;  // RGB(238, 197, 145)
const COLORREF  ConstColorBurlywood3          = 0x00CDAA7D;  // RGB(205, 170, 125)
const COLORREF  ConstColorBurlywood4          = 0x008B7355;  // RGB(139, 115,  85)
const COLORREF  ConstColorChocolate           = 0x00D2691E;  // RGB(210, 105,  30)
const COLORREF  ConstColorChocolate1          = 0x00FF7F24;  // RGB(255, 127,  36)
const COLORREF  ConstColorChocolate2          = 0x00EE7621;  // RGB(238, 118,  33)
const COLORREF  ConstColorChocolate3          = 0x00CD661D;  // RGB(205, 102,  29)
const COLORREF  ConstColorChocolate4          = 0x008B4513;  // RGB(139,  69,  19)
const COLORREF  ConstColorPeru                = 0x00CD853F;  // RGB(205, 133,  63)
const COLORREF  ConstColorTan                 = 0x00D2B48C;  // RGB(210, 180, 140)
const COLORREF  ConstColorTan1                = 0x00FFA54F;  // RGB(255, 165,  79)
const COLORREF  ConstColorTan2                = 0x00EE9A49;  // RGB(238, 154,  73)
const COLORREF  ConstColorTan3                = 0x00CD853F;  // RGB(205, 133,  63)
const COLORREF  ConstColorTan4                = 0x008B5A2B;  // RGB(139,  90,  43)

// Shades of Gray
const COLORREF  ConstColorLtGray              = 0x00C0C0C0;  // RGB(192, 192, 192) 
const COLORREF  ConstColorGray                = 0x00808080;  // RGB(128, 128, 128)
const COLORREF  ConstColorGray00              = 0x00BEBEBE;  // RGB(190, 190, 190)
const COLORREF  ConstColorGray0               = 0x00000000;  // RGB(  0,   0,   0)
const COLORREF  ConstColorGray1               = 0x00030303;  // RGB(  3,   3,   3)
const COLORREF  ConstColorGray2               = 0x00050505;  // RGB(  5,   5,   5)
const COLORREF  ConstColorGray3               = 0x00080808;  // RGB(  8,   8,   8)
const COLORREF  ConstColorGray4               = 0x000A0A0A;  // RGB( 10,  10,  10)
const COLORREF  ConstColorGray5               = 0x000D0D0D;  // RGB( 13,  13,  13)
const COLORREF  ConstColorGray6               = 0x000F0F0F;  // RGB( 15,  15,  15)
const COLORREF  ConstColorGray7               = 0x00121212;  // RGB( 18,  18,  18)
const COLORREF  ConstColorGray8               = 0x00141414;  // RGB( 20,  20,  20)
const COLORREF  ConstColorGray9               = 0x00171717;  // RGB( 23,  23,  23)
const COLORREF  ConstColorGray10              = 0x001A1A1A;  // RGB( 26,  26,  26)
const COLORREF  ConstColorGray11              = 0x001C1C1C;  // RGB( 28,  28,  28)
const COLORREF  ConstColorGray12              = 0x001F1F1F;  // RGB( 31,  31,  31)
const COLORREF  ConstColorGray13              = 0x00212121;  // RGB( 33,  33,  33)
const COLORREF  ConstColorGray14              = 0x00242424;  // RGB( 36,  36,  36)
const COLORREF  ConstColorGray15              = 0x00262626;  // RGB( 38,  38,  38)
const COLORREF  ConstColorGray16              = 0x00292929;  // RGB( 41,  41,  41)
const COLORREF  ConstColorGray17              = 0x002B2B2B;  // RGB( 43,  43,  43)
const COLORREF  ConstColorGray18              = 0x002E2E2E;  // RGB( 46,  46,  46)
const COLORREF  ConstColorGray19              = 0x00303030;  // RGB( 48,  48,  48)
const COLORREF  ConstColorGray20              = 0x00333333;  // RGB( 51,  51,  51)
const COLORREF  ConstColorGray21              = 0x00363636;  // RGB( 54,  54,  54)
const COLORREF  ConstColorGray22              = 0x00383838;  // RGB( 56,  56,  56)
const COLORREF  ConstColorGray23              = 0x003B3B3B;  // RGB( 59,  59,  59)
const COLORREF  ConstColorGray24              = 0x003D3D3D;  // RGB( 61,  61,  61)
const COLORREF  ConstColorGray25              = 0x00404040;  // RGB( 64,  64,  64)
const COLORREF  ConstColorGray26              = 0x00424242;  // RGB( 66,  66,  66)
const COLORREF  ConstColorGray27              = 0x00454545;  // RGB( 69,  69,  69)
const COLORREF  ConstColorGray28              = 0x00474747;  // RGB( 71,  71,  71)
const COLORREF  ConstColorGray29              = 0x004A4A4A;  // RGB( 74,  74,  74)
const COLORREF  ConstColorGray30              = 0x004D4D4D;  // RGB( 77,  77,  77)
const COLORREF  ConstColorGray31              = 0x004F4F4F;  // RGB( 79,  79,  79)
const COLORREF  ConstColorGray32              = 0x00525252;  // RGB( 82,  82,  82)
const COLORREF  ConstColorGray33              = 0x00545454;  // RGB( 84,  84,  84)
const COLORREF  ConstColorGray34              = 0x00575757;  // RGB( 87,  87,  87)
const COLORREF  ConstColorGray35              = 0x00595959;  // RGB( 89,  89,  89)
const COLORREF  ConstColorGray36              = 0x005C5C5C;  // RGB( 92,  92,  92)
const COLORREF  ConstColorGray37              = 0x005E5E5E;  // RGB( 94,  94,  94)
const COLORREF  ConstColorGray38              = 0x00616161;  // RGB( 97,  97,  97)
const COLORREF  ConstColorGray39              = 0x00636363;  // RGB( 99,  99,  99)
const COLORREF  ConstColorGray40              = 0x00666666;  // RGB(102, 102, 102)
const COLORREF  ConstColorGray41              = 0x00696969;  // RGB(105, 105, 105)
const COLORREF  ConstColorGray42              = 0x006B6B6B;  // RGB(107, 107, 107)
const COLORREF  ConstColorGray43              = 0x006E6E6E;  // RGB(110, 110, 110)
const COLORREF  ConstColorGray44              = 0x00707070;  // RGB(112, 112, 112)
const COLORREF  ConstColorGray45              = 0x00737373;  // RGB(115, 115, 115)
const COLORREF  ConstColorGray46              = 0x00757575;  // RGB(117, 117, 117)
const COLORREF  ConstColorGray47              = 0x00787878;  // RGB(120, 120, 120)
const COLORREF  ConstColorGray48              = 0x007A7A7A;  // RGB(122, 122, 122)
const COLORREF  ConstColorGray49              = 0x007D7D7D;  // RGB(125, 125, 125)
const COLORREF  ConstColorGray50              = 0x007F7F7F;  // RGB(127, 127, 127)
const COLORREF  ConstColorGray51              = 0x00828282;  // RGB(130, 130, 130)
const COLORREF  ConstColorGray52              = 0x00858585;  // RGB(133, 133, 133)
const COLORREF  ConstColorGray53              = 0x00878787;  // RGB(135, 135, 135)
const COLORREF  ConstColorGray54              = 0x008A8A8A;  // RGB(138, 138, 138)
const COLORREF  ConstColorGray55              = 0x008C8C8C;  // RGB(140, 140, 140)
const COLORREF  ConstColorGray56              = 0x008F8F8F;  // RGB(143, 143, 143)
const COLORREF  ConstColorGray57              = 0x00919191;  // RGB(145, 145, 145)
const COLORREF  ConstColorGray58              = 0x00949494;  // RGB(148, 148, 148)
const COLORREF  ConstColorGray59              = 0x00969696;  // RGB(150, 150, 150)
const COLORREF  ConstColorGray60              = 0x00999999;  // RGB(153, 153, 153)
const COLORREF  ConstColorGray61              = 0x009C9C9C;  // RGB(156, 156, 156)
const COLORREF  ConstColorGray62              = 0x009E9E9E;  // RGB(158, 158, 158)
const COLORREF  ConstColorGray63              = 0x00A1A1A1;  // RGB(161, 161, 161)
const COLORREF  ConstColorGray64              = 0x00A3A3A3;  // RGB(163, 163, 163)
const COLORREF  ConstColorGray65              = 0x00A6A6A6;  // RGB(166, 166, 166)
const COLORREF  ConstColorGray66              = 0x00A8A8A8;  // RGB(168, 168, 168)
const COLORREF  ConstColorGray67              = 0x00ABABAB;  // RGB(171, 171, 171)
const COLORREF  ConstColorGray68              = 0x00ADADAD;  // RGB(173, 173, 173)
const COLORREF  ConstColorGray69              = 0x00B0B0B0;  // RGB(176, 176, 176)
const COLORREF  ConstColorGray70              = 0x00B3B3B3;  // RGB(179, 179, 179)
const COLORREF  ConstColorGray71              = 0x00B5B5B5;  // RGB(181, 181, 181)
const COLORREF  ConstColorGray72              = 0x00B8B8B8;  // RGB(184, 184, 184)
const COLORREF  ConstColorGray73              = 0x00BABABA;  // RGB(186, 186, 186)
const COLORREF  ConstColorGray74              = 0x00BDBDBD;  // RGB(189, 189, 189)
const COLORREF  ConstColorGray75              = 0x00BFBFBF;  // RGB(191, 191, 191)
const COLORREF  ConstColorGray76              = 0x00C2C2C2;  // RGB(194, 194, 194)
const COLORREF  ConstColorGray77              = 0x00C4C4C4;  // RGB(196, 196, 196)
const COLORREF  ConstColorGray78              = 0x00C7C7C7;  // RGB(199, 199, 199)
const COLORREF  ConstColorGray79              = 0x00C9C9C9;  // RGB(201, 201, 201)
const COLORREF  ConstColorGray80              = 0x00CCCCCC;  // RGB(204, 204, 204)
const COLORREF  ConstColorGray81              = 0x00CFCFCF;  // RGB(207, 207, 207)
const COLORREF  ConstColorGray82              = 0x00D1D1D1;  // RGB(209, 209, 209)
const COLORREF  ConstColorGray83              = 0x00D4D4D4;  // RGB(212, 212, 212)
const COLORREF  ConstColorGray84              = 0x00D6D6D6;  // RGB(214, 214, 214)
const COLORREF  ConstColorGray85              = 0x00D9D9D9;  // RGB(217, 217, 217)
const COLORREF  ConstColorGray86              = 0x00DBDBDB;  // RGB(219, 219, 219)
const COLORREF  ConstColorGray87              = 0x00DEDEDE;  // RGB(222, 222, 222)
const COLORREF  ConstColorGray88              = 0x00E0E0E0;  // RGB(224, 224, 224)
const COLORREF  ConstColorGray89              = 0x00E3E3E3;  // RGB(227, 227, 227)
const COLORREF  ConstColorGray90              = 0x00E5E5E5;  // RGB(229, 229, 229)
const COLORREF  ConstColorGray91              = 0x00E8E8E8;  // RGB(232, 232, 232)
const COLORREF  ConstColorGray92              = 0x00EBEBEB;  // RGB(235, 235, 235)
const COLORREF  ConstColorGray93              = 0x00EDEDED;  // RGB(237, 237, 237)
const COLORREF  ConstColorGray94              = 0x00F0F0F0;  // RGB(240, 240, 240)
const COLORREF  ConstColorGray95              = 0x00F2F2F2;  // RGB(242, 242, 242)
const COLORREF  ConstColorGray96              = 0x00F5F5F5;  // RGB(245, 245, 245)
const COLORREF  ConstColorGray97              = 0x00F7F7F7;  // RGB(247, 247, 247)
const COLORREF  ConstColorGray98              = 0x00FAFAFA;  // RGB(250, 250, 250)
const COLORREF  ConstColorGray99              = 0x00FCFCFC;  // RGB(252, 252, 252)
const COLORREF  ConstColorGrey100             = 0x00FFFFFF;  // RGB(255, 255, 255)
const COLORREF  ConstColorDarkSlateGray       = 0x002F4F4F;  // RGB( 47,  79,  79)
const COLORREF  ConstColorDarkSlateGray1      = 0x0097FFFF;  // RGB(151, 255, 255)
const COLORREF  ConstColorDarkSlateGray2      = 0x008DEEEE;  // RGB(141, 238, 238)
const COLORREF  ConstColorDarkSlateGray3      = 0x0079CDCD;  // RGB(121, 205, 205)
const COLORREF  ConstColorDarkSlateGray4      = 0x00528B8B;  // RGB( 82, 139, 139)
const COLORREF  ConstColorDarkSlateGrey       = 0x002F4F4F;  // RGB( 47,  79,  79)
const COLORREF  ConstColorDimGray             = 0x00696969;  // RGB(105, 105, 105)
const COLORREF  ConstColorDimGrey             = 0x00696969;  // RGB(105, 105, 105)
const COLORREF  ConstColorLightGray           = 0x00D3D3D3;  // RGB(211, 211, 211)
const COLORREF  ConstColorLightGrey           = 0x00D3D3D3;  // RGB(211, 211, 211)
const COLORREF  ConstColorLightSlateGray      = 0x00778899;  // RGB(119, 136, 153)
const COLORREF  ConstColorLightSlateGrey      = 0x00778899;  // RGB(119, 136, 153)
const COLORREF  ConstColorSlateGray           = 0x00708090;  // RGB(112, 128, 144)
const COLORREF  ConstColorSlateGray1          = 0x00C6E2FF;  // RGB(198, 226, 255)
const COLORREF  ConstColorSlateGray2          = 0x00B9D3EE;  // RGB(185, 211, 238)
const COLORREF  ConstColorSlateGray3          = 0x009FB6CD;  // RGB(159, 182, 205)
const COLORREF  ConstColorSlateGray4          = 0x006C7B8B;  // RGB(108, 123, 139)
const COLORREF  ConstColorSlateGrey           = 0x00708090;  // RGB(112, 128, 144)

// Shades of Green
const COLORREF  ConstColorDarkGreen           = 0x00006400;  // RGB(  0, 100,   0)
const COLORREF  ConstColorDarkKhaki           = 0x00BDB76B;  // RGB(189, 183, 107)
const COLORREF  ConstColorDarkOliveGreen      = 0x00556B2F;  // RGB( 85, 107,  47)
const COLORREF  ConstColorDarkOliveGreen1     = 0x00CAFF70;  // RGB(202, 255, 112)
const COLORREF  ConstColorDarkOliveGreen2     = 0x00BCEE68;  // RGB(188, 238, 104)
const COLORREF  ConstColorDarkOliveGreen3     = 0x00A2CD5A;  // RGB(162, 205,  90)
const COLORREF  ConstColorDarkOliveGreen4     = 0x006E8B3D;  // RGB(110, 139,  61)
const COLORREF  ConstColorDarkSeaGreen        = 0x008FBC8F;  // RGB(143, 188, 143)
const COLORREF  ConstColorDarkSeaGreen1       = 0x00C1FFC1;  // RGB(193, 255, 193)
const COLORREF  ConstColorDarkSeaGreen2       = 0x00B4EEB4;  // RGB(180, 238, 180)
const COLORREF  ConstColorDarkSeaGreen3       = 0x009BCD9B;  // RGB(155, 205, 155)
const COLORREF  ConstColorDarkSeaGreen4       = 0x00698B69;  // RGB(105, 139, 105)
const COLORREF  ConstColorForestGreen         = 0x00228B22;  // RGB( 34, 139,  34)
const COLORREF  ConstColorGreenYellow         = 0x00ADFF2F;  // RGB(173, 255,  47)
const COLORREF  ConstColorLawnGreen           = 0x007CFC00;  // RGB(124, 252,   0)
const COLORREF  ConstColorLightSeaGreen       = 0x0020B2AA;  // RGB( 32, 178, 170)
const COLORREF  ConstColorLimeGreen           = 0x0032CD32;  // RGB( 50, 205,  50)
const COLORREF  ConstColorMediumSeaGreen      = 0x003CB371;  // RGB( 60, 179, 113)
const COLORREF  ConstColorMediumSpringGreen   = 0x0000FA9A;  // RGB(  0, 250, 154)
const COLORREF  ConstColorMintCream           = 0x00F5FFFA;  // RGB(245, 255, 250)
const COLORREF  ConstColorOliveDrab           = 0x006B8E23;  // RGB(107, 142,  35)
const COLORREF  ConstColorOliveDrab1          = 0x00C0FF3E;  // RGB(192, 255,  62)
const COLORREF  ConstColorOliveDrab2          = 0x00B3EE3A;  // RGB(179, 238,  58)
const COLORREF  ConstColorOliveDrab3          = 0x009ACD32;  // RGB(154, 205,  50)
const COLORREF  ConstColorOliveDrab4          = 0x00698B22;  // RGB(105, 139,  34)
const COLORREF  ConstColorPaleGreen           = 0x0098FB98;  // RGB(152, 251, 152)
const COLORREF  ConstColorPaleGreen1          = 0x009AFF9A;  // RGB(154, 255, 154)
const COLORREF  ConstColorPaleGreen2          = 0x0090EE90;  // RGB(144, 238, 144)
const COLORREF  ConstColorPaleGreen3          = 0x007CCD7C;  // RGB(124, 205, 124)
const COLORREF  ConstColorPaleGreen4          = 0x00548B54;  // RGB( 84, 139,  84)
const COLORREF  ConstColorSeaGreen            = 0x002E8B57;  // RGB( 46, 139,  87)
const COLORREF  ConstColorSeaGreen1           = 0x0054FF9F;  // RGB( 84, 255, 159)
const COLORREF  ConstColorSeaGreen2           = 0x004EEE94;  // RGB( 78, 238, 148)
const COLORREF  ConstColorSeaGreen3           = 0x0043CD80;  // RGB( 67, 205, 128)
const COLORREF  ConstColorSeaGreen4           = 0x002E8B57;  // RGB( 46, 139,  87)
const COLORREF  ConstColorSpringGreen         = 0x0000FF7F;  // RGB(  0, 255, 127)
const COLORREF  ConstColorSpringGreen1        = 0x0000FF7F;  // RGB(  0, 255, 127)
const COLORREF  ConstColorSpringGreen2        = 0x0000EE76;  // RGB(  0, 238, 118)
const COLORREF  ConstColorSpringGreen3        = 0x0000CD66;  // RGB(  0, 205, 102)
const COLORREF  ConstColorSpringGreen4        = 0x00008B45;  // RGB(  0, 139,  69)
const COLORREF  ConstColorYellowGreen         = 0x009ACD32;  // RGB(154, 205,  50)
const COLORREF  ConstColorChartreuse          = 0x007FFF00;  // RGB(127, 255,   0)
const COLORREF  ConstColorChartreuse1         = 0x007FFF00;  // RGB(127, 255,   0)
const COLORREF  ConstColorChartreuse2         = 0x0076EE00;  // RGB(118, 238,   0)
const COLORREF  ConstColorChartreuse3         = 0x0066CD00;  // RGB(102, 205,   0)
const COLORREF  ConstColorChartreuse4         = 0x00458B00;  // RGB( 69, 139,   0)
const COLORREF  ConstColorGreen               = 0x0000FF00;  // RGB(  0, 255,   0)
const COLORREF  ConstColorGreen1              = 0x0000FF00;  // RGB(  0, 255,   0)
const COLORREF  ConstColorGreen2              = 0x0000EE00;  // RGB(  0, 238,   0)
const COLORREF  ConstColorGreen3              = 0x0000CD00;  // RGB(  0, 205,   0)
const COLORREF  ConstColorGreen4              = 0x00008B00;  // RGB(  0, 139,   0)
const COLORREF  ConstColorKhaki               = 0x00F0E68C;  // RGB(240, 230, 140)
const COLORREF  ConstColorKhaki1              = 0x00FFF68F;  // RGB(255, 246, 143)
const COLORREF  ConstColorKhaki2              = 0x00EEE685;  // RGB(238, 230, 133)
const COLORREF  ConstColorKhaki3              = 0x00CDC673;  // RGB(205, 198, 115)
const COLORREF  ConstColorKhaki4              = 0x008B864E;  // RGB(139, 134,  78)

// Shades of Orange
const COLORREF  ConstColorDarkOrange          = 0x00FF8C00;  // RGB(255, 140,   0)
const COLORREF  ConstColorDarkOrange1         = 0x00FF7F00;  // RGB(255, 127,   0)
const COLORREF  ConstColorDarkOrange2         = 0x00EE7600;  // RGB(238, 118,   0)
const COLORREF  ConstColorDarkOrange3         = 0x00CD6600;  // RGB(205, 102,   0)
const COLORREF  ConstColorDarkOrange4         = 0x008B4500;  // RGB(139,  69,   0)
const COLORREF  ConstColorDarkSalmon          = 0x00E9967A;  // RGB(233, 150, 122)
const COLORREF  ConstColorLightCoral          = 0x00F08080;  // RGB(240, 128, 128)
const COLORREF  ConstColorLightSalmon         = 0x00FFA07A;  // RGB(255, 160, 122)
const COLORREF  ConstColorLightSalmon1        = 0x00FFA07A;  // RGB(255, 160, 122)
const COLORREF  ConstColorLightSalmon2        = 0x00EE9572;  // RGB(238, 149, 114)
const COLORREF  ConstColorLightSalmon3        = 0x00CD8162;  // RGB(205, 129,  98)
const COLORREF  ConstColorLightSalmon4        = 0x008B5742;  // RGB(139,  87,  66)
const COLORREF  ConstColorPeachPuff           = 0x00FFDAB9;  // RGB(255, 218, 185)
const COLORREF  ConstColorPeachPuff1          = 0x00FFDAB9;  // RGB(255, 218, 185)
const COLORREF  ConstColorPeachPuff2          = 0x00EECBAD;  // RGB(238, 203, 173)
const COLORREF  ConstColorPeachPuff3          = 0x00CDAF95;  // RGB(205, 175, 149)
const COLORREF  ConstColorPeachPuff4          = 0x008B7765;  // RGB(139, 119, 101)
const COLORREF  ConstColorBisque              = 0x00FFE4C4;  // RGB(255, 228, 196)
const COLORREF  ConstColorBisque1             = 0x00FFE4C4;  // RGB(255, 228, 196)
const COLORREF  ConstColorBisque2             = 0x00EED5B7;  // RGB(238, 213, 183)
const COLORREF  ConstColorBisque3             = 0x00CDB79E;  // RGB(205, 183, 158)
const COLORREF  ConstColorBisque4             = 0x008B7D6B;  // RGB(139, 125, 107)
const COLORREF  ConstColorCoral               = 0x00FF7F50;  // RGB(255, 127,  80)
const COLORREF  ConstColorCoral1              = 0x00FF7256;  // RGB(255, 114,  86)
const COLORREF  ConstColorCoral2              = 0x00EE6A50;  // RGB(238, 106,  80)
const COLORREF  ConstColorCoral3              = 0x00CD5B45;  // RGB(205,  91,  69)
const COLORREF  ConstColorCoral4              = 0x008B3E2F;  // RGB(139,  62,  47)
const COLORREF  ConstColorHoneydew            = 0x00F0FFF0;  // RGB(240, 255, 240)
const COLORREF  ConstColorHoneydew1           = 0x00F0FFF0;  // RGB(240, 255, 240)
const COLORREF  ConstColorHoneydew2           = 0x00E0EEE0;  // RGB(224, 238, 224)
const COLORREF  ConstColorHoneydew3           = 0x00C1CDC1;  // RGB(193, 205, 193)
const COLORREF  ConstColorHoneydew4           = 0x00838B83;  // RGB(131, 139, 131)
const COLORREF  ConstColorOrange              = 0x00FFA500;  // RGB(255, 165,   0)
const COLORREF  ConstColorOrange1             = 0x00FFA500;  // RGB(255, 165,   0)
const COLORREF  ConstColorOrange2             = 0x00EE9A00;  // RGB(238, 154,   0)
const COLORREF  ConstColorOrange3             = 0x00CD8500;  // RGB(205, 133,   0)
const COLORREF  ConstColorOrange4             = 0x008B5A00;  // RGB(139,  90,   0)
const COLORREF  ConstColorSalmon              = 0x00FA8072;  // RGB(250, 128, 114)
const COLORREF  ConstColorSalmon1             = 0x00FF8C69;  // RGB(255, 140, 105)
const COLORREF  ConstColorSalmon2             = 0x00EE8262;  // RGB(238, 130,  98)
const COLORREF  ConstColorSalmon3             = 0x00CD7054;  // RGB(205, 112,  84)
const COLORREF  ConstColorSalmon4             = 0x008B4C39;  // RGB(139,  76,  57)
const COLORREF  ConstColorSienna              = 0x00A0522D;  // RGB(160,  82,  45)
const COLORREF  ConstColorSienna1             = 0x00FF8247;  // RGB(255, 130,  71)
const COLORREF  ConstColorSienna2             = 0x00EE7942;  // RGB(238, 121,  66)
const COLORREF  ConstColorSienna3             = 0x00CD6839;  // RGB(205, 104,  57)
const COLORREF  ConstColorSienna4             = 0x008B4726;  // RGB(139,  71,  38)

// Shades of Red
const COLORREF  ConstColorDeepPink            = 0x00FF1493;  // RGB(255,  20, 147)
const COLORREF  ConstColorDeepPink1           = 0x00FF1493;  // RGB(255,  20, 147)
const COLORREF  ConstColorDeepPink2           = 0x00EE1289;  // RGB(238,  18, 137)
const COLORREF  ConstColorDeepPink3           = 0x00CD1076;  // RGB(205,  16, 118)
const COLORREF  ConstColorDeepPink4           = 0x008B0A50;  // RGB(139,  10,  80)
const COLORREF  ConstColorHotPink             = 0x00FF69B4;  // RGB(255, 105, 180)
const COLORREF  ConstColorHotPink1            = 0x00FF6EB4;  // RGB(255, 110, 180)
const COLORREF  ConstColorHotPink2            = 0x00EE6AA7;  // RGB(238, 106, 167)
const COLORREF  ConstColorHotPink3            = 0x00CD6090;  // RGB(205,  96, 144)
const COLORREF  ConstColorHotPink4            = 0x008B3A62;  // RGB(139,  58,  98)
const COLORREF  ConstColorIndianRed           = 0x00CD5C5C;  // RGB(205,  92,  92)
const COLORREF  ConstColorIndianRed1          = 0x00FF6A6A;  // RGB(255, 106, 106)
const COLORREF  ConstColorIndianRed2          = 0x00EE6363;  // RGB(238,  99,  99)
const COLORREF  ConstColorIndianRed3          = 0x00CD5555;  // RGB(205,  85,  85)
const COLORREF  ConstColorIndianRed4          = 0x008B3A3A;  // RGB(139,  58,  58)
const COLORREF  ConstColorLightPink           = 0x00FFB6C1;  // RGB(255, 182, 193)
const COLORREF  ConstColorLightPink1          = 0x00FFAEB9;  // RGB(255, 174, 185)
const COLORREF  ConstColorLightPink2          = 0x00EEA2AD;  // RGB(238, 162, 173)
const COLORREF  ConstColorLightPink3          = 0x00CD8C95;  // RGB(205, 140, 149)
const COLORREF  ConstColorLightPink4          = 0x008B5F65;  // RGB(139,  95, 101)
const COLORREF  ConstColorMediumVioletRed     = 0x00C71585;  // RGB(199,  21, 133)
const COLORREF  ConstColorMistyRose           = 0x00FFE4E1;  // RGB(255, 228, 225)
const COLORREF  ConstColorMistyRose1          = 0x00FFE4E1;  // RGB(255, 228, 225)
const COLORREF  ConstColorMistyRose2          = 0x00EED5D2;  // RGB(238, 213, 210)
const COLORREF  ConstColorMistyRose3          = 0x00CDB7B5;  // RGB(205, 183, 181)
const COLORREF  ConstColorMistyRose4          = 0x008B7D7B;  // RGB(139, 125, 123)
const COLORREF  ConstColorOrangeRed           = 0x00FF4500;  // RGB(255,  69,   0)
const COLORREF  ConstColorOrangeRed1          = 0x00FF4500;  // RGB(255,  69,   0)
const COLORREF  ConstColorOrangeRed2          = 0x00EE4000;  // RGB(238,  64,   0)
const COLORREF  ConstColorOrangeRed3          = 0x00CD3700;  // RGB(205,  55,   0)
const COLORREF  ConstColorOrangeRed4          = 0x008B2500;  // RGB(139,  37,   0)
const COLORREF  ConstColorPaleVioletRed       = 0x00DB7093;  // RGB(219, 112, 147)
const COLORREF  ConstColorPaleVioletRed1      = 0x00FF82AB;  // RGB(255, 130, 171)
const COLORREF  ConstColorPaleVioletRed2      = 0x00EE799F;  // RGB(238, 121, 159)
const COLORREF  ConstColorPaleVioletRed3      = 0x00CD6889;  // RGB(205, 104, 137)
const COLORREF  ConstColorPaleVioletRed4      = 0x008B475D;  // RGB(139,  71,  93)
const COLORREF  ConstColorVioletRed           = 0x00D02090;  // RGB(208,  32, 144)
const COLORREF  ConstColorVioletRed1          = 0x00FF3E96;  // RGB(255,  62, 150)
const COLORREF  ConstColorVioletRed2          = 0x00EE3A8C;  // RGB(238,  58, 140)
const COLORREF  ConstColorVioletRed3          = 0x00CD3278;  // RGB(205,  50, 120)
const COLORREF  ConstColorVioletRed4          = 0x008B2252;  // RGB(139,  34,  82)
const COLORREF  ConstColorFirebrick           = 0x00B22222;  // RGB(178,  34,  34)
const COLORREF  ConstColorFirebrick1          = 0x00FF3030;  // RGB(255,  48,  48)
const COLORREF  ConstColorFirebrick2          = 0x00EE2C2C;  // RGB(238,  44,  44)
const COLORREF  ConstColorFirebrick3          = 0x00CD2626;  // RGB(205,  38,  38)
const COLORREF  ConstColorFirebrick4          = 0x008B1A1A;  // RGB(139,  26,  26)
const COLORREF  ConstColorPink                = 0x00FFC0CB;  // RGB(255, 192, 203)
const COLORREF  ConstColorPink1               = 0x00FFB5C5;  // RGB(255, 181, 197)
const COLORREF  ConstColorPink2               = 0x00EEA9B8;  // RGB(238, 169, 184)
const COLORREF  ConstColorPink3               = 0x00CD919E;  // RGB(205, 145, 158)
const COLORREF  ConstColorPink4               = 0x008B636C;  // RGB(139,  99, 108)
const COLORREF  ConstColorRed                 = 0x00FF0000;  // RGB(255,   0,   0)
const COLORREF  ConstColorRed1                = 0x00FF0000;  // RGB(255,   0,   0)
const COLORREF  ConstColorRed2                = 0x00EE0000;  // RGB(238,   0,   0)
const COLORREF  ConstColorRed3                = 0x00CD0000;  // RGB(205,   0,   0)
const COLORREF  ConstColorRed4                = 0x008B0000;  // RGB(139,   0,   0)
const COLORREF  ConstColorTomato              = 0x00FF6347;  // RGB(255,  99,  71)
const COLORREF  ConstColorTomato1             = 0x00FF6347;  // RGB(255,  99,  71)
const COLORREF  ConstColorTomato2             = 0x00EE5C42;  // RGB(238,  92,  66)
const COLORREF  ConstColorTomato3             = 0x00CD4F39;  // RGB(205,  79,  57)
const COLORREF  ConstColorTomato4             = 0x008B3626;  // RGB(139,  54,  38)

// Shades of Violet
const COLORREF  ConstColorDarkOrchid          = 0x009932CC;  // RGB(153,  50, 204)
const COLORREF  ConstColorDarkOrchid1         = 0x00BF3EFF;  // RGB(191,  62, 255)
const COLORREF  ConstColorDarkOrchid2         = 0x00B23AEE;  // RGB(178,  58, 238)
const COLORREF  ConstColorDarkOrchid3         = 0x009A32CD;  // RGB(154,  50, 205)
const COLORREF  ConstColorDarkOrchid4         = 0x0068228B;  // RGB(104,  34, 139)
const COLORREF  ConstColorDarkViolet          = 0x009400D3;  // RGB(148,   0, 211)
const COLORREF  ConstColorLavenderBlush       = 0x00FFF0F5;  // RGB(255, 240, 245)
const COLORREF  ConstColorLavenderBlush1      = 0x00FFF0F5;  // RGB(255, 240, 245)
const COLORREF  ConstColorLavenderBlush2      = 0x00EEE0E5;  // RGB(238, 224, 229)
const COLORREF  ConstColorLavenderBlush3      = 0x00CDC1C5;  // RGB(205, 193, 197)
const COLORREF  ConstColorLavenderBlush4      = 0x008B8386;  // RGB(139, 131, 134)
const COLORREF  ConstColorMediumOrchid        = 0x00BA55D3;  // RGB(186,  85, 211)
const COLORREF  ConstColorMediumOrchid1       = 0x00E066FF;  // RGB(224, 102, 255)
const COLORREF  ConstColorMediumOrchid2       = 0x00D15FEE;  // RGB(209,  95, 238)
const COLORREF  ConstColorMediumOrchid3       = 0x00B452CD;  // RGB(180,  82, 205)
const COLORREF  ConstColorMediumOrchid4       = 0x007A378B;  // RGB(122,  55, 139)
const COLORREF  ConstColorMediumPurple        = 0x009370DB;  // RGB(147, 112, 219)
const COLORREF  ConstColorMediumPurple1       = 0x00AB82FF;  // RGB(171, 130, 255)
const COLORREF  ConstColorMediumPurple2       = 0x009F79EE;  // RGB(159, 121, 238)
const COLORREF  ConstColorMediumPurple3       = 0x008968CD;  // RGB(137, 104, 205)
const COLORREF  ConstColorMediumPurple4       = 0x005D478B;  // RGB( 93,  71, 139)
const COLORREF  ConstColorLavender            = 0x00E6E6FA;  // RGB(230, 230, 250)
const COLORREF  ConstColorMagenta             = 0x00FF00FF;  // RGB(255,   0, 255)
const COLORREF  ConstColorMagenta1            = 0x00FF00FF;  // RGB(255,   0, 255)
const COLORREF  ConstColorMagenta2            = 0x00EE00EE;  // RGB(238,   0, 238)
const COLORREF  ConstColorMagenta3            = 0x00CD00CD;  // RGB(205,   0, 205)
const COLORREF  ConstColorMagenta4            = 0x008B008B;  // RGB(139,   0, 139)
const COLORREF  ConstColorMaroon              = 0x00B03060;  // RGB(176,  48,  96)
const COLORREF  ConstColorMaroon1             = 0x00FF34B3;  // RGB(255,  52, 179)
const COLORREF  ConstColorMaroon2             = 0x00EE30A7;  // RGB(238,  48, 167)
const COLORREF  ConstColorMaroon3             = 0x00CD2990;  // RGB(205,  41, 144)
const COLORREF  ConstColorMaroon4             = 0x008B1C62;  // RGB(139,  28,  98)
const COLORREF  ConstColorOrchid              = 0x00DA70D6;  // RGB(218, 112, 214)
const COLORREF  ConstColorOrchid1             = 0x00FF83FA;  // RGB(255, 131, 250)
const COLORREF  ConstColorOrchid2             = 0x00EE7AE9;  // RGB(238, 122, 233)
const COLORREF  ConstColorOrchid3             = 0x00CD69C9;  // RGB(205, 105, 201)
const COLORREF  ConstColorOrchid4             = 0x008B4789;  // RGB(139,  71, 137)
const COLORREF  ConstColorPlum                = 0x00DDA0DD;  // RGB(221, 160, 221)
const COLORREF  ConstColorPlum1               = 0x00FFBBFF;  // RGB(255, 187, 255)
const COLORREF  ConstColorPlum2               = 0x00EEAEEE;  // RGB(238, 174, 238)
const COLORREF  ConstColorPlum3               = 0x00CD96CD;  // RGB(205, 150, 205)
const COLORREF  ConstColorPlum4               = 0x008B668B;  // RGB(139, 102, 139)
const COLORREF  ConstColorPurple              = 0x00A020F0;  // RGB(160,  32, 240)
const COLORREF  ConstColorPurple1             = 0x009B30FF;  // RGB(155,  48, 255)
const COLORREF  ConstColorPurple2             = 0x00912CEE;  // RGB(145,  44, 238)
const COLORREF  ConstColorPurple3             = 0x007D26CD;  // RGB(125,  38, 205)
const COLORREF  ConstColorPurple4             = 0x00551A8B;  // RGB( 85,  26, 139)
const COLORREF  ConstColorThistle             = 0x00D8BFD8;  // RGB(216, 191, 216)
const COLORREF  ConstColorThistle1            = 0x00FFE1FF;  // RGB(255, 225, 255)
const COLORREF  ConstColorThistle2            = 0x00EED2EE;  // RGB(238, 210, 238)
const COLORREF  ConstColorThistle3            = 0x00CDB5CD;  // RGB(205, 181, 205)
const COLORREF  ConstColorThistle4            = 0x008B7B8B;  // RGB(139, 123, 139)
const COLORREF  ConstColorViolet              = 0x00EE82EE;  // RGB(238, 130, 238)

// Shades of White
const COLORREF  ConstColorAntiqueWhite        = 0x00FAEBD7;  // RGB(250, 235, 215)
const COLORREF  ConstColorAntiqueWhite1       = 0x00FFEFDB;  // RGB(255, 239, 219)
const COLORREF  ConstColorAntiqueWhite2       = 0x00EEDFCC;  // RGB(238, 223, 204)
const COLORREF  ConstColorAntiqueWhite3       = 0x00CDC0B0;  // RGB(205, 192, 176)
const COLORREF  ConstColorAntiqueWhite4       = 0x008B8378;  // RGB(139, 131, 120)
const COLORREF  ConstColorFloralWhite         = 0x00FFFAF0;  // RGB(255, 250, 240)
const COLORREF  ConstColorGhostWhite          = 0x00F8F8FF;  // RGB(248, 248, 255)
const COLORREF  ConstColorNavajoWhite         = 0x00FFDEAD;  // RGB(255, 222, 173)
const COLORREF  ConstColorNavajoWhite1        = 0x00FFDEAD;  // RGB(255, 222, 173)
const COLORREF  ConstColorNavajoWhite2        = 0x00EECFA1;  // RGB(238, 207, 161)
const COLORREF  ConstColorNavajoWhite3        = 0x00CDB38B;  // RGB(205, 179, 139)
const COLORREF  ConstColorNavajoWhite4        = 0x008B795E;  // RGB(139, 121,  94)
const COLORREF  ConstColorOldLace             = 0x00FDF5E6;  // RGB(253, 245, 230)
const COLORREF  ConstColorWhiteSmoke          = 0x00F5F5F5;  // RGB(245, 245, 245)
const COLORREF  ConstColorGainsboro           = 0x00DCDCDC;  // RGB(220, 220, 220)
const COLORREF  ConstColorIvory               = 0x00FFFFF0;  // RGB(255, 255, 240)
const COLORREF  ConstColorIvory1              = 0x00FFFFF0;  // RGB(255, 255, 240)
const COLORREF  ConstColorIvory2              = 0x00EEEEE0;  // RGB(238, 238, 224)
const COLORREF  ConstColorIvory3              = 0x00CDCDC1;  // RGB(205, 205, 193)
const COLORREF  ConstColorIvory4              = 0x008B8B83;  // RGB(139, 139, 131)
const COLORREF  ConstColorLinen               = 0x00FAF0E6;  // RGB(250, 240, 230)
const COLORREF  ConstColorSeashell            = 0x00FFF5EE;  // RGB(255, 245, 238)
const COLORREF  ConstColorSeashell1           = 0x00FFF5EE;  // RGB(255, 245, 238)
const COLORREF  ConstColorSeashell2           = 0x00EEE5DE;  // RGB(238, 229, 222)
const COLORREF  ConstColorSeashell3           = 0x00CDC5BF;  // RGB(205, 197, 191)
const COLORREF  ConstColorSeashell4           = 0x008B8682;  // RGB(139, 134, 130)
const COLORREF  ConstColorSnow                = 0x00FFFAFA;  // RGB(255, 250, 250)
const COLORREF  ConstColorSnow1               = 0x00FFFAFA;  // RGB(255, 250, 250)
const COLORREF  ConstColorSnow2               = 0x00EEE9E9;  // RGB(238, 233, 233)
const COLORREF  ConstColorSnow3               = 0x00CDC9C9;  // RGB(205, 201, 201)
const COLORREF  ConstColorSnow4               = 0x008B8989;  // RGB(139, 137, 137)
const COLORREF  ConstColorWheat               = 0x00F5DEB3;  // RGB(245, 222, 179)
const COLORREF  ConstColorWheat1              = 0x00FFE7BA;  // RGB(255, 231, 186)
const COLORREF  ConstColorWheat2              = 0x00EED8AE;  // RGB(238, 216, 174)
const COLORREF  ConstColorWheat3              = 0x00CDBA96;  // RGB(205, 186, 150)
const COLORREF  ConstColorWheat4              = 0x008B7E66;  // RGB(139, 126, 102)
const COLORREF  ConstColorWhite               = 0x00FFFFFF;  // RGB(255, 255, 255)

// Shades of Yellow
const COLORREF  ConstColorBlanchedAlmond      = 0x00FFEBCD;  // RGB(255, 235, 205)
const COLORREF  ConstColorDarkGoldenrod       = 0x00B8860B;  // RGB(184, 134,  11)
const COLORREF  ConstColorDarkGoldenrod1      = 0x00FFB90F;  // RGB(255, 185,  15)
const COLORREF  ConstColorDarkGoldenrod2      = 0x00EEAD0E;  // RGB(238, 173,  14)
const COLORREF  ConstColorDarkGoldenrod3      = 0x00CD950C;  // RGB(205, 149,  12)
const COLORREF  ConstColorDarkGoldenrod4      = 0x008B6508;  // RGB(139, 101,   8)
const COLORREF  ConstColorLemonChiffon        = 0x00FFFACD;  // RGB(255, 250, 205)
const COLORREF  ConstColorLemonChiffon1       = 0x00FFFACD;  // RGB(255, 250, 205)
const COLORREF  ConstColorLemonChiffon2       = 0x00EEE9BF;  // RGB(238, 233, 191)
const COLORREF  ConstColorLemonChiffon3       = 0x00CDC9A5;  // RGB(205, 201, 165)
const COLORREF  ConstColorLemonChiffon4       = 0x008B8970;  // RGB(139, 137, 112)
const COLORREF  ConstColorLightGoldenrod      = 0x00EEDD82;  // RGB(238, 221, 130)
const COLORREF  ConstColorLightGoldenrod1     = 0x00FFEC8B;  // RGB(255, 236, 139)
const COLORREF  ConstColorLightGoldenrod2     = 0x00EEDC82;  // RGB(238, 220, 130)
const COLORREF  ConstColorLightGoldenrod3     = 0x00CDBE70;  // RGB(205, 190, 112)
const COLORREF  ConstColorLightGoldenrod4     = 0x008B814C;  // RGB(139, 129,  76)
const COLORREF  ConstColorLightGoldenrodYellow= 0x00FAFAD2;  // RGB(250, 250, 210)
const COLORREF  ConstColorLightYellow         = 0x00FFFFE0;  // RGB(255, 255, 224)
const COLORREF  ConstColorLightYellow1        = 0x00FFFFE0;  // RGB(255, 255, 224)
const COLORREF  ConstColorLightYellow2        = 0x00EEEED1;  // RGB(238, 238, 209)
const COLORREF  ConstColorLightYellow3        = 0x00CDCDB4;  // RGB(205, 205, 180)
const COLORREF  ConstColorLightYellow4        = 0x008B8B7A;  // RGB(139, 139, 122)
const COLORREF  ConstColorPaleGoldenrod       = 0x00EEE8AA;  // RGB(238, 232, 170)
const COLORREF  ConstColorPapayaWhip          = 0x00FFEFD5;  // RGB(255, 239, 213)
const COLORREF  ConstColorCornsilk            = 0x00FFF8DC;  // RGB(255, 248, 220)
const COLORREF  ConstColorCornsilk1           = 0x00FFF8DC;  // RGB(255, 248, 220)
const COLORREF  ConstColorCornsilk2           = 0x00EEE8CD;  // RGB(238, 232, 205)
const COLORREF  ConstColorCornsilk3           = 0x00CDC8B1;  // RGB(205, 200, 177)
const COLORREF  ConstColorCornsilk4           = 0x008B8878;  // RGB(139, 136, 120)
const COLORREF  ConstColorGold                = 0x00FFD700;  // RGB(255, 215,   0)
const COLORREF  ConstColorGold1               = 0x00FFD700;  // RGB(255, 215,   0)
const COLORREF  ConstColorGold2               = 0x00EEC900;  // RGB(238, 201,   0)
const COLORREF  ConstColorGold3               = 0x00CDAD00;  // RGB(205, 173,   0)
const COLORREF  ConstColorGold4               = 0x008B7500;  // RGB(139, 117,   0)
const COLORREF  ConstColorGoldenrod           = 0x00DAA520;  // RGB(218, 165,  32)
const COLORREF  ConstColorGoldenrod1          = 0x00FFC125;  // RGB(255, 193,  37)
const COLORREF  ConstColorGoldenrod2          = 0x00EEB422;  // RGB(238, 180,  34)
const COLORREF  ConstColorGoldenrod3          = 0x00CD9B1D;  // RGB(205, 155,  29)
const COLORREF  ConstColorGoldenrod4          = 0x008B6914;  // RGB(139, 105,  20)
const COLORREF  ConstColorMoccasin            = 0x00FFE4B5;  // RGB(255, 228, 181)
const COLORREF  ConstColorYellow              = 0x00FFFF00;  // RGB(255, 255,   0)
const COLORREF  ConstColorYellow1             = 0x00FFFF00;  // RGB(255, 255,   0)
const COLORREF  ConstColorYellow2             = 0x00EEEE00;  // RGB(238, 238,   0)
const COLORREF  ConstColorYellow3             = 0x00CDCD00;  // RGB(205, 205,   0)
const COLORREF  ConstColorYellow4             = 0x008B8B00;  // RGB(139, 139,   0)
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __COLOR_H__
