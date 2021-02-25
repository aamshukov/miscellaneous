//......................................................................................
// This is a part of UI Soft Library.  1989-2006 UI Soft Inc.               .
//......................................................................................
// THIS CODE MAY BE USED, COPIED, STORED, OR DISTRIBUTED ONLY IN ACCORDANCE WITH       .
// A WRITTEN LICENSE AGREEMENT AND WITH THE INCLUSION OF THIS COPYRIGHT NOTICE.        .
//......................................................................................

#region prolog
// file       : 
// description: SymbolTable
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
    /// summary description for Symbol
    /// </summary>
    public class Symbol
    {
        #region constants
        #endregion // constants

        #region data members
        private ail.net.parser.Token    TokenAttr;          // token associated with node
        private ail.net.parser.Type     TypeAttr;           // type of symbol
        private string                  GeneratedNameAttr;  // if not null it means symbol name artificially generated
        #endregion // data members

        #region ctor/dtor/finalizer
        public Symbol()
        {
        }
        #endregion ctor/dtor/finalizer

        #region properties
        public ail.net.parser.Token Token
        {
            get
            {
                return TokenAttr;
            }

            set
            {
                TokenAttr = value;
            }            
        }

        public ail.net.parser.Type Type
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

        public string GeneratedName
        {
            get
            {
                return GeneratedNameAttr;
            }

            set
            {
                GeneratedNameAttr = value;
            }
        }
        #endregion // properties

        #region methods
        #endregion // methods
    }

    /// <summary>
    /// summary description for SymbolTable
    /// </summary>
    public class SymbolTable
    {
        #region constants
        #endregion // constants

        #region data members
        private Hashtable                   SymbolsAttr = new Hashtable(1024);  // symbols
        private ail.net.parser.SymbolTable  ParentAttr;                         // link-up
        #endregion // data members

        #region ctor/dtor/finalizer
        public SymbolTable()
        {
        }
        #endregion ctor/dtor/finalizer

        #region properties
        public Hashtable Symbols
        {
            get
            {
                return SymbolsAttr;
            }
        }

        public ail.net.parser.SymbolTable Parent
        {
            get
            {
                return ParentAttr;
            }

            set
            {
                ParentAttr = value;
            }
        }
        #endregion // properties

        #region methods
        #endregion // methods
    }
}

#region epilog
#endregion
