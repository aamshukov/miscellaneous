////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AIL_H__
#   include <ail.hpp>
#endif

#ifndef __COLOR_INC__
#   include <Color.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class Color
// ----- -----
const uint ConstSymbolic = 0x80000000;

const Color Color::None(0xFF000000);
const Color Color::Transparent(0xFE000000);

const Color Color::Black                    (  0,   0,   0);
const Color Color::Gray                     (128, 128, 128);
const Color Color::MediumGray               (160, 160, 164);
const Color Color::LtGray                   (192, 192, 192);
const Color Color::LtRed                    (255,   0,   0);
const Color Color::LtGreen                  (  0, 255,   0);
const Color Color::LtYellow                 (255, 255,   0);
const Color Color::LtBlue                   (  0,   0, 255);
const Color Color::LtMagenta                (255,   0, 255);
const Color Color::LtCyan                   (  0, 255, 255);
const Color Color::DarkBlue                 (  0,   0, 128);
const Color Color::DarkGreen                (  0, 128,   0);
const Color Color::Brown                    (128,   0,   0);
const Color Color::BlueGreen                (  0, 128, 128);
const Color Color::DarkPurple               (128,   0, 128);
const Color Color::Olive                    (128, 128,   0);
const Color Color::PaleGreen                (192, 220, 192);
const Color Color::LightBlue                (166, 202, 240);
const Color Color::OffWhite                 (255, 251, 240);
const Color Color::White                    (255, 255, 255);

const Color Color::ToolTip                  (255, 255, 225);

const Color Color::SysScrollbar             (ConstSymbolic | COLOR_SCROLLBAR);
const Color Color::SysDesktop               (ConstSymbolic | COLOR_BACKGROUND);
const Color Color::SysActiveCaption         (ConstSymbolic | COLOR_ACTIVECAPTION);
const Color Color::SysInactiveCaption       (ConstSymbolic | COLOR_INACTIVECAPTION);
const Color Color::SysMenu                  (ConstSymbolic | COLOR_MENU);
const Color Color::SysWindow                (ConstSymbolic | COLOR_WINDOW);
const Color Color::SysWindowFrame           (ConstSymbolic | COLOR_WINDOWFRAME);
const Color Color::SysMenuText              (ConstSymbolic | COLOR_MENUTEXT);
const Color Color::SysWindowText            (ConstSymbolic | COLOR_WINDOWTEXT);
const Color Color::SysCaptionText           (ConstSymbolic | COLOR_CAPTIONTEXT);
const Color Color::SysActiveBorder          (ConstSymbolic | COLOR_ACTIVEBORDER);
const Color Color::SysInactiveBorder        (ConstSymbolic | COLOR_INACTIVEBORDER);
const Color Color::SysAppWorkspace          (ConstSymbolic | COLOR_APPWORKSPACE);
const Color Color::SysHighlight             (ConstSymbolic | COLOR_HIGHLIGHT);
const Color Color::SysHighlightText         (ConstSymbolic | COLOR_HIGHLIGHTTEXT);
const Color Color::Sys3dFace                (ConstSymbolic | COLOR_BTNFACE);
const Color Color::Sys3dShadow              (ConstSymbolic | COLOR_BTNSHADOW);
const Color Color::SysGrayText              (ConstSymbolic | COLOR_GRAYTEXT);
const Color Color::SysBtnText               (ConstSymbolic | COLOR_BTNTEXT);
const Color Color::SysInactiveCaptionText   (ConstSymbolic | COLOR_INACTIVECAPTIONTEXT);
const Color Color::Sys3dHighlight           (ConstSymbolic | COLOR_BTNHIGHLIGHT);
const Color Color::Sys3dDkShadow            (ConstSymbolic | COLOR_3DDKSHADOW);
const Color Color::Sys3dLight               (ConstSymbolic | COLOR_3DLIGHT);
const Color Color::SysInfoText              (ConstSymbolic | COLOR_INFOTEXT);
const Color Color::SysInfoBk                (ConstSymbolic | COLOR_INFOBK);

const tchar   Color::CharBlack[TEXT_SIZE_SMALL]        = _t("Black");
const tchar   Color::CharGray[TEXT_SIZE_SMALL]         = _t("Gray");
const tchar   Color::CharMediumGray[TEXT_SIZE_SMALL]   = _t("Medium Gray");
const tchar   Color::CharLtGray[TEXT_SIZE_SMALL]       = _t("Bright Gray");
const tchar   Color::CharLtRed[TEXT_SIZE_SMALL]        = _t("Bright Red");
const tchar   Color::CharLtGreen[TEXT_SIZE_SMALL]      = _t("Bright Green");
const tchar   Color::CharLtYellow[TEXT_SIZE_SMALL]     = _t("Yellow");
const tchar   Color::CharLtBlue[TEXT_SIZE_SMALL]       = _t("Bright Blue");
const tchar   Color::CharLtMagenta[TEXT_SIZE_SMALL]    = _t("Magenta");
const tchar   Color::CharLtCyan[TEXT_SIZE_SMALL]       = _t("Cyan");
const tchar   Color::CharDarkBlue[TEXT_SIZE_SMALL]     = _t("Dark Blue");
const tchar   Color::CharDarkGreen[TEXT_SIZE_SMALL]    = _t("Dark Green");
const tchar   Color::CharBrown[TEXT_SIZE_SMALL]        = _t("Brown");
const tchar   Color::CharBlueGreen[TEXT_SIZE_SMALL]    = _t("Blue Green");
const tchar   Color::CharDarkPurple[TEXT_SIZE_SMALL]   = _t("Dark Purple");
const tchar   Color::CharOlive[TEXT_SIZE_SMALL]        = _t("Olive");
const tchar   Color::CharPaleGreen[TEXT_SIZE_SMALL]    = _t("Pale Green");
const tchar   Color::CharLightBlue[TEXT_SIZE_SMALL]    = _t("Light Blue");
const tchar   Color::CharOffWhite[TEXT_SIZE_SMALL]     = _t("Off White");
const tchar   Color::CharWhite[TEXT_SIZE_SMALL]        = _t("White");
const tchar   Color::CharTransparent[TEXT_SIZE_SMALL]  = _t("Transparent");
//
Color::Color()
{
    Value = 0;
}

Color::Color(const Color& _other)
{
    if(this != &_other)
    {
        Value = _other.Value;
    }
}

Color::Color(COLORREF _value)
{
    Value = _value;
}

Color::Color(uint _value)
{
    Value = COLORREF(_value);
}

Color::Color(byte _r, byte _g, byte _b)
{
    Value = RGB(_r, _g, _b);
}

Color::Color(byte _r, byte _g, byte _b, byte _f)
{
    Value = (uint(_f)<<24)|RGB(_r, _g, _b);
}

Color::Color(const PALETTEENTRY& _pe)
{
    Value = RGB(_pe.peRed, _pe.peGreen, _pe.peBlue);
}

Color::Color(const RGBQUAD& _q)
{
    Value = RGB(_q.rgbRed, _q.rgbGreen, _q.rgbBlue);
}

Color::Color(const RGBTRIPLE& _t)
{
    Value = RGB(_t.rgbtRed, _t.rgbtGreen, _t.rgbtBlue);
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__
