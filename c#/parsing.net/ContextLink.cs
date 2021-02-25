//......................................................................................
// This is a part of UI Soft Library.  1989-2006 UI Soft Inc.               .
//......................................................................................
// THIS CODE MAY BE USED, COPIED, STORED, OR DISTRIBUTED ONLY IN ACCORDANCE WITH       .
// A WRITTEN LICENSE AGREEMENT AND WITH THE INCLUSION OF THIS COPYRIGHT NOTICE.        .
//......................................................................................

#region prolog
// file       : 
// description: ContextLink
// package    : ail.net.parser
//
#endregion

#region import
using System;
#endregion

namespace ail.net.parser
{
    /// <summary>
    /// summary description for ContextLink
    /// </summary>
    public class ContextLink
    {
        #region data members
        private int OffsetAttr;     // offset in context (absolute address)
        private int LengthAttr;     // length of lexeme
        private int PositionAttr;   // position in line (relative address)
        private int LineNumberAttr; // line number (relative address)
        #endregion // data members

        #region ctor/dtor/finalizer
        public ContextLink()
        {
        }
        #endregion ctor/dtor/finalizer

        #region properties
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
        #endregion // properties
    }
}

#region epilog
#endregion
