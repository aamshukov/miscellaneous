////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1998-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __PAGEMETRIC_INL__
#define __PAGEMETRIC_INL__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class PageMetric
// ----- ----------
__INLINE__ bool PageMetric::IsLogicMode() const
{
    return LogicMode;
}

__INLINE__ void PageMetric::SetLogicMode(bool mode)
{
    LogicMode = mode;
}

__INLINE__ bool PageMetric::IsZoomMode() const
{
    return ZoomMode;
}

__INLINE__ void PageMetric::SetZoomMode(bool mode)
{
    ZoomMode = mode;
}

__INLINE__ ushort PageMetric::GetPaperSize() const
{
    return PaperSize;
}

__INLINE__ void PageMetric::SetPaperSize(ushort size)
{
    PaperSize = size;
}

__INLINE__ ushort PageMetric::GetOrientation() const
{
    return Orientation;
}

__INLINE__ void PageMetric::SetOrientation(ushort o)
{
    Orientation = o;
}

__INLINE__ ushort PageMetric::GetGutter() const
{
    return static_cast<ushort>(Gutter*(ZoomMode ? ZoomFactor : 1.0));
}

__INLINE__ void PageMetric::SetGutter(ushort gutter)
{
    Gutter = gutter;
}

__INLINE__ ushort PageMetric::GetHeader() const
{
    return static_cast<ushort>(Header*(ZoomMode ? ZoomFactor : 1.0));
}

__INLINE__ void PageMetric::SetHeader(ushort header)
{
    Header = header;
}

__INLINE__ ushort PageMetric::GetFooter() const
{
    return static_cast<ushort>(Footer*(ZoomMode ? ZoomFactor : 1.0));
}

__INLINE__ void PageMetric::SetFooter(ushort footer)
{
    Footer = footer;
}

__INLINE__ ushort PageMetric::GetLeftMargin() const
{
    return static_cast<ushort>(LeftMargin*(ZoomMode ? ZoomFactor : 1.0));
}

__INLINE__ void PageMetric::SetLeftMargin(ushort margin)
{
    LeftMargin = margin;
}

__INLINE__ ushort PageMetric::GetRightMargin() const
{
    return static_cast<ushort>(RightMargin*(ZoomMode ? ZoomFactor : 1.0));
}

__INLINE__ void PageMetric::SetRightMargin(ushort margin)
{
    RightMargin = margin;
}

__INLINE__ ushort PageMetric::GetTopMargin() const
{
    return static_cast<ushort>(TopMargin*(ZoomMode ? ZoomFactor : 1.0));
}

__INLINE__ void PageMetric::SetTopMargin(ushort margin)
{
    TopMargin = margin;
}

__INLINE__ ushort PageMetric::GetBottomMargin() const
{
    return static_cast<ushort>(BottomMargin*(ZoomMode ? ZoomFactor : 1.0));
}

__INLINE__ void PageMetric::SetBottomMargin(ushort margin)
{
    BottomMargin = margin;
}

__INLINE__ Size PageMetric::GetPageOffset() const
{
    Size sz(PageOffset);

    sz.cx = int(sz.cx*(ZoomMode ? ZoomFactor : 1.0));
    sz.cy = int(sz.cy*(ZoomMode ? ZoomFactor : 1.0));

    return sz;
}

__INLINE__ void PageMetric::SetPageOffset(const Size& offset)
{
    PageOffset = offset;
}

__INLINE__ Size PageMetric::GetPageSize() const
{
    Size sz(PageSize);

    sz.cx = int(sz.cx*(ZoomMode ? ZoomFactor : 1.0));
    sz.cy = int(sz.cy*(ZoomMode ? ZoomFactor : 1.0));

    return sz;
}

__INLINE__ void PageMetric::SetPageSize(const Size& size)
{
    PageSize = size;
}

__INLINE__ Rect PageMetric::GetRealPageSize() const
{
    Rect r(0, 0, GetPageSize().cx, GetPageSize().cy);

    r.left   += GetPageOffset().cx+GetGutter()+GetLeftMargin();
    r.top    += GetPageOffset().cy+GetTopMargin()+GetHeader();
    r.right  -= GetPageOffset().cx+GetRightMargin();
    r.bottom -= GetPageOffset().cy+GetBottomMargin()+GetFooter();

    return r;
}

__INLINE__ Point PageMetric::GetOrigPoint() const
{
    return GetRealPageSize().TopLeft();
}

__INLINE__ double PageMetric::GetZoomFactor() const
{
    return ZoomFactor;
}

__INLINE__ void PageMetric::SetZoomFactor(double factor)
{
    ZoomFactor = factor;
}

__INLINE__ void PageMetric::GetPageSizeInPx(Size& sz, HDC hdc) const
{
    ail::GetPageSizeInPx(PaperSize, sz, hdc);
}
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __PAGEMETRIC_INL__
