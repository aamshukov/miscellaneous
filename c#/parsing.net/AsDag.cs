//......................................................................................
// This is a part of UI Soft Library. Copyright © 1989-2006 UI Soft Inc.               .
//......................................................................................
// THIS CODE MAY BE USED, COPIED, STORED, OR DISTRIBUTED ONLY IN ACCORDANCE WITH       .
// A WRITTEN LICENSE AGREEMENT AND WITH THE INCLUSION OF THIS COPYRIGHT NOTICE.        .
//......................................................................................

#region prolog
// file       : 
// description: AsDagNode (abstract syntax direct acyclg graph node)
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
    /// summary description for AsDagNode
    /// </summary>
    public class AsDagNode
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
        private int                     TypeAttr;                           // type of node
        private ail.net.parser.Token    TokenAttr;                          // token associated with node
        private ArrayList               PredecessorsAttr = new ArrayList(); // predecessor(s)
        private ArrayList               SuccessorsAttr   = new ArrayList(); // successor(s)
        #endregion // data members

        #region ctor/dtor/finalizer
        public AsDagNode()
        {
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

        public ArrayList Predecessors
        {
            get
            {
                return PredecessorsAttr;
            }

            set
            {
                PredecessorsAttr = value;
            }
        }

        public ArrayList Successors
        {
            get
            {
                return SuccessorsAttr;
            }
            
            set
            {
                SuccessorsAttr = value;
            }
        }
        #endregion // properties

        #region methods
        #endregion // methods
    }
}

#region epilog
#endregion
