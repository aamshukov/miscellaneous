//......................................................................................
// This is a part of UI Soft Library.  1989-2006 UI Soft Inc.               .
//......................................................................................
// THIS CODE MAY BE USED, COPIED, STORED, OR DISTRIBUTED ONLY IN ACCORDANCE WITH       .
// A WRITTEN LICENSE AGREEMENT AND WITH THE INCLUSION OF THIS COPYRIGHT NOTICE.        .
//......................................................................................

#region prolog
// file       : 
// description: FsaPairKey
// package    : ail.net.parser
//
#endregion

#region import
using System;
#endregion

namespace ail.net.parser
{
    /// <summary>
    /// summary description for FsaPairKey
    /// </summary>
    public struct FsaPairKey
    {
        #region data members
        public ail.net.parser.FsaState PState;
        public ail.net.parser.FsaState QState;
        #endregion // data members

        #region ctor/dtor/finalizer
        public FsaPairKey(ail.net.parser.FsaState xi_p_state, ail.net.parser.FsaState xi_q_state)
        {
            PState = xi_p_state;
            QState = xi_q_state;
        }
        #endregion // ctor/dtor/finalizer

        #region operators
        public static bool operator == (FsaPairKey xi_lhs, FsaPairKey xi_rhs)
        {
            bool result = (object)xi_lhs != (object)null &&
                          (object)xi_rhs != (object)null &&
                          (object)xi_lhs.PState == (object)xi_rhs.PState &&
                          (object)xi_lhs.QState == (object)xi_rhs.QState;
            return result;
        }

        public static bool operator != (FsaPairKey xi_lhs, FsaPairKey xi_rhs)
        {
            bool result = !(xi_lhs == xi_rhs);
            return result;
        }
        #endregion // operators

        #region methods
        public override bool Equals(object xi_rhs)
        {
            ail.net.framework.Assert.ExpectedType(xi_rhs, "xi_rhs", typeof(FsaPairKey));

            bool result = this == ((FsaPairKey)xi_rhs);
            return result;
        }

        public override int GetHashCode()
        {
            int result = ail.net.framework.Functor.DualIntHash(PState.Id, QState.Id);
            return result;
        }
        #endregion // methods
    }
}

#region epilog
#endregion
