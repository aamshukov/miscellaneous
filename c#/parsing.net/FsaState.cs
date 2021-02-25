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
// description: FsaState 
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
    /// summary description for FsaState
    /// </summary>
    public class FsaState : ICloneable, IComparable, IDisposable
    {
        #region constants
        [FlagsAttribute]
        protected enum EFlags : ushort
        {
            eEscapedToken = 0x0001
        };
        #endregion // constants

        #region data members
        private int                  IdAttr;                             // unique id of state
        private string               LabelAttr       = "";               // name of state
        private Hashtable            TransitionsAttr = new Hashtable();  // outcomming transitions
        private ail.net.parser.Token TokenAttr;                          // final state token, optional not initialized
        private ail.net.parser.Fsa   PapaAttr;                           // fsa it belongs too
        private bool                 MarkedAttr;
        #endregion // data members

        #region ctor/dtor/finalizer
        public FsaState(ail.net.parser.Fsa xi_papa)
        {
            PapaAttr = xi_papa;
        }

        public FsaState(int xi_id, ail.net.parser.Fsa xi_papa)
        {
            IdAttr   = xi_id;
            PapaAttr = xi_papa;
        }

        public FsaState(int xi_id, string xi_label, ail.net.parser.Fsa xi_papa)
        {
            IdAttr    = xi_id;
            LabelAttr = xi_label;
            PapaAttr  = xi_papa;
        }

       ~FsaState()
        {
            Dispose(false);
        }
        #endregion ctor/dtor/finalizer

        #region properties
        public int Id
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

        public string Label
        {
            get
            {
                if(LabelAttr.Length == 0)
                {
                    LabelAttr = "q"+IdAttr.ToString();
                }
                return LabelAttr;
            }
            
            set
            {
                LabelAttr = value;
            }
        }
        
        public Hashtable Transitions
        {
            get
            {
                return TransitionsAttr;
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
                TokenAttr = value;;
            }
        }

        public ail.net.parser.Fsa Papa
        {
            get
            {
                return PapaAttr;
            }

            set
            {
                PapaAttr = value;
            }
        }

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
        #endregion // properties

        #region operators
        public static bool operator == (FsaState xi_lhs, FsaState xi_rhs)
        {
            bool result = (object)xi_lhs != (object)null && (object)xi_rhs != (object)null && xi_lhs.Id == xi_rhs.Id;
            return result;
        }

        public static bool operator != (FsaState xi_lhs, FsaState xi_rhs)
        {
            bool result = !(xi_lhs == xi_rhs);
            return result;
        }
        #endregion // operators

        #region methods
	    public object Clone()
	    {
		    FsaState result = new FsaState(Papa);

		    result.Id              = Id;
            result.Label           = Label;
            result.TransitionsAttr = Transitions;
            result.Token           = Token;
            result.Papa            = Papa;

		    return result;
		}

        public int CompareTo(object xi_rhs)
        {
            ail.net.framework.Assert.NonNullReference(xi_rhs, "xi_rhs");
            ail.net.framework.Assert.ExpectedType(xi_rhs, "xi_rhs", typeof(FsaState));

            int result = 0;

            if(Id < ((FsaState)xi_rhs).Id)
            {
                result = -1;
            }
            else if(Id > ((FsaState)xi_rhs).Id)
            {
                result = 1;
            }

            return result;
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this); 
        }

        protected virtual void Dispose(bool xi_disposing)
        {
            if(xi_disposing)
            {
                // free managed objects
            }

            // free unmanaged objects, including base class
            // set large fields to null (de-reference)
        }

        public override bool Equals(object xi_rhs)
        {
            ail.net.framework.Assert.ExpectedType(xi_rhs, "xi_rhs", typeof(FsaState));

            bool result = this == ((FsaState)xi_rhs);
            return result;
        }

        public override int GetHashCode()
        {
            int result = Id;
            return result;
        }

        public bool HasEpsilonTransition()
        {
            bool result = false;

            foreach(ail.net.parser.FsaTransition it in Transitions)
            {
                if(it.Predicate.Text == ail.net.parser.FsaTransition.kEpsilonPredicate)
                {
                    result = true;
                    break;
                }
            }

            return result;
        }

        public ail.net.parser.FsaTransition GetTransitionByPredicate(ail.net.parser.FsaTransitionPredicate xi_predicate)
        {
            ail.net.framework.Assert.NonNullReference(xi_predicate, "xi_predicate");
            
            ail.net.parser.FsaTransition result = null;

            foreach(ail.net.parser.FsaTransition transition in Transitions.Values)
            {
                if(transition.Predicate.Text == xi_predicate.Text)
                {
                    result = transition;
                    break;
                }
            }

            return result;
        }
        #endregion // methods
    }
}

#region epilog
#endregion
