#region copyright
//......................................................................................
// This is a part of UI Soft Library. Copyright © 1989-2006 UI Soft Inc.               .
//......................................................................................
// THIS CODE MAY BE USED, COPIED, STORED, OR DISTRIBUTED ONLY IN ACCORDANCE WITH       .
// A WRITTEN LICENSE AGREEMENT AND WITH THE INCLUSION OF THIS COPYRIGHT NOTICE.        .
//......................................................................................
#endregion

#region prolog
// file       : 
// description: Token
// package    : ail.net.parser
//
#endregion

#region import
using System;
#endregion

namespace ail.net.parser
{
    /// <summary>
    /// summary description for Token
    /// </summary>
    public class Token : ICloneable
    {
        #region constants
        public enum EType : int
        {
            // the following six (6) entries, MUST be the first entries in the enum
            eUnknown = 0,
            eEpsilon,
            eEndOfStream,
            eWhiteSpace,
            eEndMarker,
            eError,

            // the following one (1) entry, MUST be the last entry in the enum
            eSize
        };

        protected static string [] Names = new string []
        {
            "eUnknown",
            "eEpsilon",
            "eEndOfStream",
            "eWhiteSpace",
            "eEndMarker",
            "eError"
        };

        public const int kUndefinedEscapeTokenType = -1;
        #endregion // constants

        #region data members
        int     TypeAttr;       // type of lexeme, explicitly casted to int
        int     OffsetAttr;     // offset in context (absolute address)
        int     LengthAttr;     // length of lexeme
        int     PositionAttr;   // position in line (relative address)
        int     LineNumberAttr; // line number (relative address)
        int     PriorityAttr;   // priority to resolve lexical conflicts in DFA construction
        //?? int     HashCode;       // hash code
        #endregion // data members

        #region ctor/dtor/finalizer
        public Token()
        {
        }

        public Token(int xi_type, int xi_priority)
        {
            TypeAttr     = xi_type;
            PriorityAttr = xi_priority;
        }
        #endregion ctor/dtor/finalizer

        #region properties
        public int Type
        {
            get
            {
                return TypeAttr;
            }

            set
            {
                TypeAttr = value;
            }
        }

        public int Offset
        {
            get
            {
                return OffsetAttr;
            }
            
            set
            {
                OffsetAttr = value;
            }
        }
        
        public int Length
        {
            get
            {
                return LengthAttr;
            }
            
            set
            {
                LengthAttr = value;
            }
        }

        public int Position
        {
            get
            {
                return PositionAttr;
            }
            
            set
            {
                PositionAttr = value;
            }
        }
        
        public int LineNumber
        {
            get
            {
                return LineNumberAttr;
            }
            
            set
            {
                LineNumberAttr = value;
            }
        }

        public int Priority
        {
            get
            {
                return PriorityAttr;
            }
            
            set
            {
                PriorityAttr = value;
            }
        }
        #endregion // properties

        #region methods
        public virtual object Clone()
        {
            Token result = new Token();

            result.TypeAttr       = TypeAttr;
            result.OffsetAttr     = OffsetAttr;
            result.LengthAttr     = LengthAttr;
            result.PositionAttr   = PositionAttr;
            result.LineNumberAttr = LineNumberAttr;
            result.PriorityAttr   = PriorityAttr;

            return result;
        }

        public virtual string GetClassName()
        {
            const string name = "ail.net.parser.Token";
            return name;
        }

        public virtual string GetTokenName(int xi_token_type)
        {
            return Names[xi_token_type];
        }

        public virtual int GetTokenSize()
        {
            return (int)ail.net.parser.Token.EType.eSize;;
        }
        #endregion // methods
    }
}

#region epilog
#endregion
