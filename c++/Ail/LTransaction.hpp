////////////////////////////////////////////////////////////////////////////////////////
//......................................................................................
//  This is a part of AI Library [Arthur's Interfaces Library].                        .
//  1989-2001 Arthur Amshukov                                              .
//......................................................................................
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND         .
//  DO NOT REMOVE MY NAME AND THIS NOTICE FROM THE SOURCE                              .
//......................................................................................
////////////////////////////////////////////////////////////////////////////////////////
#ifndef __L_TRANSACTION_H__
#define __L_TRANSACTION_H__

#pragma once

__BEGIN_NAMESPACE__
__BEGIN_RRT_NAMESPACE__
////////////////////////////////////////////////////////////////////////////////////////
// class LTransaction - logic transaction
// ----- ------------ - ----- -----------
class __DECLSPEC__ LTransaction
{
    public:

    enum EState
    {
        Unknown = 0,
        Pended,
        Aborted,
        Completed
    };

    private:
     volatile EState    State;
    private:
                        LTransaction(const LTransaction&);
     LTransaction       operator = (const LTransaction&);
    public:
     // ctor/dtor
                        LTransaction();
                       ~LTransaction();

     // access
     bool               IsPended()      const;
     bool               IsAborted()     const;
     bool               IsCompleted()   const;
};
////////////////////////////////////////////////////////////////////////////////////////
__END_RRT_NAMESPACE__
__END_NAMESPACE__

#endif // __L_TRANSACTION_H__
