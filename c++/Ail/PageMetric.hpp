////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PAGEMETRIC_H__
#define __PAGEMETRIC_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PageMetric
// ----- ----------
class __DECLSPEC__ PageMetric
{
    private:
     bool               LogicMode;  // logical/device coordinate
     bool               ZoomMode;
     ushort             PaperSize;
     ushort             Orientation;
     ushort             Gutter;
     ushort             Header;
     ushort             Footer;
     ushort             LeftMargin;
     ushort             RightMargin;
     ushort             TopMargin;
     ushort             BottomMargin;
     double             ZoomFactor;

     Size               PageOffset;
     Size               PageSize;
    public:
                        PageMetric();
                        PageMetric(const PageMetric&);

     const PageMetric&  operator = (const PageMetric&);

     bool               IsLogicMode()                           const;
     void               SetLogicMode(bool = true);

     bool               IsZoomMode()                            const;
     void               SetZoomMode(bool = true);

     ushort             GetPaperSize()                          const;
     void               SetPaperSize(ushort = DMPAPER_LETTER);

     ushort             GetOrientation()                        const;
     void               SetOrientation(ushort = DMORIENT_PORTRAIT);

     ushort             GetGutter()                             const;
     void               SetGutter(ushort);

     ushort             GetHeader()                             const;
     void               SetHeader(ushort);

     ushort             GetFooter()                             const;
     void               SetFooter(ushort);

     ushort             GetLeftMargin()                         const;
     void               SetLeftMargin(ushort);

     ushort             GetRightMargin()                        const;
     void               SetRightMargin(ushort);

     ushort             GetTopMargin()                          const;
     void               SetTopMargin(ushort);

     ushort             GetBottomMargin()                       const;
     void               SetBottomMargin(ushort);

     Size               GetPageOffset()                         const;
     void               SetPageOffset(const Size&);

     Size               GetPageSize()                           const;
     void               SetPageSize(const Size&);

     Rect               GetRealPageSize()                       const;
     Point              GetOrigPoint()                          const;

     double             GetZoomFactor()                         const;
     void               SetZoomFactor(double);

     void               GetPageSizeInPx(Size&, HDC = null)      const;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PAGEMETRIC_H__
