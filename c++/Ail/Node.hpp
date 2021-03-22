////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __NODE_H__
#define __NODE_H__

#pragma once

__BEGIN_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// Prototypes
// ----------
//
//  template <typename _T, typename _Key> struct KeyExtractor
//  {
//      const _Key& operator() (const _T&) const = 0;
//  };
//
//  template <typename _Key> struct Comparator
//  {
//      int operator() (const _Key&, const _Key&) const = 0;
//  };
////////////////////////////////////////////////////////////////////////////////////////
// class NodeBase
// ----- --------
template <typename _T, typename _Key> class NodeBase
{
    public:
    
    enum EFlag
    {
        StandardAlloc = 0x00000001,
        InUse         = 0x00000002
    };

    private:
                     NodeBase(const NodeBase&);
     const NodeBase& operator = (const NodeBase&);
    protected:
     uint            Flags;
    protected:
     virtual bool    operator < (const _Key&);
     virtual bool    operator == (const _Key&);
    public:
     // ctor/dtor
     explicit        NodeBase(uint = NodeBase::StandardAlloc);
     virtual        ~NodeBase() = 0;

     // access
     uint            GetFlags()  const;
     void            ModifyFlags(uint, uint);
};
////////////////////////////////////////////////////////////////////////////////////////
// class Node
// ----- ----
template <typename _T> class Node
{
    private:
    _T              Data;
    private:
                    Node(const Node&);
     const Node&    operator = (const Node&);
    public:
     // ctor/dtor
     explicit       Node(const _T&);
     virtual       ~Node();

     // access
     const _T&      GetData()  const;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_NAMESPACE__

#endif // __NODE_H__
