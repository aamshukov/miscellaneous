//......................................................................................
// This is a part of UI Soft Library.  1989-2006 UI Soft Inc.               .
//......................................................................................
// THIS CODE MAY BE USED, COPIED, STORED, OR DISTRIBUTED ONLY IN ACCORDANCE WITH       .
// A WRITTEN LICENSE AGREEMENT AND WITH THE INCLUSION OF THIS COPYRIGHT NOTICE.        .
//......................................................................................

#region prolog
// file       : 
// description: FsaPair
// package    : ail.net.parser
//
#endregion

#region import
using System;
#endregion

namespace ail.net.parser
{
    /// <summary>
    /// summary description for FsaPair
    /// pair - (first, second)
    /// </summary>
    public class FsaPair
    {
        #region data members
        private bool                    MarkedAttr;
        private ail.net.parser.FsaState PStateAttr;
        private ail.net.parser.FsaState QStateAttr;
        #endregion // data members

        #region ctor/dtor/finalizer
        public FsaPair(ail.net.parser.FsaState xi_p_state, ail.net.parser.FsaState xi_q_state)
        {
            MarkedAttr = false;
            PStateAttr = xi_p_state;
            QStateAttr = xi_q_state;
        }
        #endregion ctor/dtor/finalizer

        #region properties
        public bool Marked
        {
            get
            {
                return MarkedAttr;
            }

            set
            {
                MarkedAttr = value;
            }
        }
        
        public ail.net.parser.FsaState PState
        {
            get
            {
                return PStateAttr;
            }

            set
            {
                PStateAttr = value;
            }
        }

        public ail.net.parser.FsaState QState
        {
            get
            {
                return QStateAttr;
            }

            set
            {
                QStateAttr = value;
            }
        }
        #endregion // properties
    }
}

#region epilog
#endregion
