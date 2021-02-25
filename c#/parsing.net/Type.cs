//......................................................................................
// This is a part of UI Soft Library.  1989-2006 UI Soft Inc.               .
//......................................................................................
// THIS CODE MAY BE USED, COPIED, STORED, OR DISTRIBUTED ONLY IN ACCORDANCE WITH       .
// A WRITTEN LICENSE AGREEMENT AND WITH THE INCLUSION OF THIS COPYRIGHT NOTICE.        .
//......................................................................................

#region prolog
// file       : 
// description: Type
// package    : ail.net.parser
//
#endregion

#region import
using System;
using System.Collections;
#endregion

namespace ail.net.parser
{
    /// <summary>
    /// summary description for Type
    /// </summary>
    public class Type
    {
        #region constants
        public enum EType
        {
            // the following one (1) entry, MUST be the first entry in the enum
            eUnknown,
            eNumber,
            eText,

            // the following one (1) entry, MUST be the last entry in the enum
            eSize
        }
        #endregion // constants

        #region data members
        private ail.net.parser.Type.EType   IdAttr;                         // type id
        private int                         AlignAttr;                      // alignment
        private int                         SizeAttr;                       // size of type
        private ArrayList                   TypesAttr = new ArrayList();    // to build nested types
        #endregion // data members

        #region ctor/dtor/finalizer
        public Type()
        {
            Id = ail.net.parser.Type.EType.eUnknown;
        }
        #endregion ctor/dtor/finalizer

        #region properties
        public ail.net.parser.Type.EType Id
        {
            get
            {
                return IdAttr;
            }
            
            set
            {
                IdAttr = value;
            }
        }
        
        public int Align
        {
            get
            {
                return AlignAttr;
            }

            set
            {
                AlignAttr = value;
            }
        }

        public int Size
        {
            get
            {
                return SizeAttr;
            }

            set
            {
                SizeAttr = value;
            }
        }

        public ArrayList Types
        {
            get
            {
                return TypesAttr;
            }
        }
        #endregion // properties

        #region methods
        #endregion // methods
    }
}

#region epilog
#endregion
