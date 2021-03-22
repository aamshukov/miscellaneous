////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __AIL_H__
#   include <ail.hpp>
#endif

#ifndef __PAGEMETRIC_INC__
#   include <PageMetric.inc>
#endif

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PageMetric
// ----- ----------
PageMetric::PageMetric()
{
    LogicMode    = false;
    ZoomMode     = true;
    PaperSize    = DMPAPER_LETTER;
    Orientation  = DMORIENT_PORTRAIT;
    Gutter       = 0;
    Header       = 0;
    Footer       = 0;
    LeftMargin   = 0;
    RightMargin  = 0;
    TopMargin    = 0;
    BottomMargin = 0;
    PageOffset   = 0;
    PageSize     = 0;
    ZoomFactor   = 1.0;
}

PageMetric::PageMetric(const PageMetric& _other)
{
    operator = (_other);
}

const PageMetric& PageMetric::operator = (const PageMetric& _other)
{
    if(this != &_other)
    {
        LogicMode    = _other.LogicMode;
        ZoomMode     = _other.ZoomMode;
        PaperSize    = _other.PaperSize;
        Orientation  = _other.Orientation;
        Gutter       = _other.Gutter;
        Header       = _other.Header;
        Footer       = _other.Footer;
        LeftMargin   = _other.LeftMargin;
        RightMargin  = _other.RightMargin;
        TopMargin    = _other.TopMargin;
        BottomMargin = _other.BottomMargin;
        PageOffset   = _other.PageOffset;
        PageSize     = _other.PageSize;
        ZoomFactor   = _other.ZoomFactor;
    }
    return *this;
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__
