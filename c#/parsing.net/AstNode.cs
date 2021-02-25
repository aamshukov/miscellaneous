//......................................................................................
// This is a part of UI Soft Library.  1989-2006 UI Soft Inc.               .
//......................................................................................
// THIS CODE MAY BE USED, COPIED, STORED, OR DISTRIBUTED ONLY IN ACCORDANCE WITH       .
// A WRITTEN LICENSE AGREEMENT AND WITH THE INCLUSION OF THIS COPYRIGHT NOTICE.        .
//......................................................................................

#region prolog
// file       : 
// description: AstNode (abstract syntax tree node)
// package    : ail.net.parser
//
#endregion

#region import
using System;
#endregion

namespace ail.net.parser
{
    /// <summary>
    /// summary description for AstNode
    /// </summary>
    public class AstNode
    {
        #region constants
        enum EType
        {
            // the following one (1) entry, MUST be the first entry in the enum
            eUnknown,

            // the following one (1) entry, MUST be the last entry in the enum
            eSize
        }
        #endregion // constants

        #region data members
        private int                     TypeAttr;       // type of node
        private ail.net.parser.Token    TokenAttr;      // token associated with node
        private ail.net.parser.AstNode  ParentAttr;     // papa
        private ail.net.parser.AstNode  BrotherAttr;    // right sibling
        private ail.net.parser.AstNode  ChildAttr;      // first child
        private ail.net.parser.AstNode  LastChildAttr;  // last child
        #endregion // data members

        #region ctor/dtor/finalizer
        public AstNode(int xi_type)
        {
            TypeAttr    = xi_type;
            TokenAttr   = null;
            ParentAttr  = null;
            BrotherAttr = null;
            ChildAttr   = null;
            LastChild   = null;
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

        public ail.net.parser.AstNode Parent
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

        public ail.net.parser.AstNode Brother
        {
            get
            {
                return BrotherAttr;
            }

            set
            {
                BrotherAttr = value;
            }
        }

        public ail.net.parser.AstNode Child
        {
            get
            {
                return ChildAttr;
            }

            set
            {
                ChildAttr = value;
            }
        }

        public ail.net.parser.AstNode LastChild
        {
            get
            {
                return LastChildAttr;
            }

            set
            {
                LastChildAttr = value;
            }
        }
        #endregion // properties

        #region methods
        public void AddNode(ail.net.parser.AstNode xi_new_node)
        {
            // add new node to the level as child
            ail.net.framework.Assert.NonNullReference(xi_new_node, "xi_new_node");

            if(LastChild != (object)null)
            {
                LastChild.Brother = xi_new_node;
            }
            else
            {
                Child = xi_new_node;
            }

            LastChild = xi_new_node;
            xi_new_node.Parent = this;
        }
        #endregion // methods
    }
}

#region epilog
#endregion
