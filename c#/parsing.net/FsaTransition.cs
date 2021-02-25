//......................................................................................
// This is a part of UI Soft Library. Copyright © 1989-2006 UI Soft Inc.               .
//......................................................................................
// THIS CODE MAY BE USED, COPIED, STORED, OR DISTRIBUTED ONLY IN ACCORDANCE WITH       .
// A WRITTEN LICENSE AGREEMENT AND WITH THE INCLUSION OF THIS COPYRIGHT NOTICE.        .
//......................................................................................

#region prolog
// file       :  
// description: FsaTransition 
// package    : ail.net.parser
//
#endregion

#region import
using System;
#endregion

namespace ail.net.parser
{
    /// <summary>
    /// summary description for FsaTransition
    /// </summary>
    public class FsaTransition : ICloneable, IComparable, IDisposable
    {
        #region constants
        public const int        kMaxRankValue     = 8;
        public static string    kEpsilonPredicate = "~e~";
        #endregion // constants

        #region data members
        private int                                     IdAttr;                                                      // unique id
        private int                                     StartAttr;                                                   // start state id
        private int                                     EndAttr;                                                     // end state id
        private ail.net.parser.FsaTransitionPredicate   PredicateAttr = new ail.net.parser.FsaTransitionPredicate(); // predicate
        #endregion // data members

        #region ctor/dtor/finalizer
        public FsaTransition()
        {
        }

        public FsaTransition(int xi_id)
        {
            IdAttr = xi_id;
        }

        public FsaTransition(int xi_id, int xi_start, int xi_end, string xi_predicate)
        {
            IdAttr             = xi_id;
            StartAttr          = xi_start;
            EndAttr            = xi_end;
            PredicateAttr.Text = xi_predicate;
        }

        public FsaTransition(int xi_id, int xi_start, int xi_end, string xi_predicate, string xi_context)
        {
            IdAttr                = xi_id;
            StartAttr             = xi_start;
            EndAttr               = xi_end;
            PredicateAttr.Text    = xi_predicate;
            PredicateAttr.Context = xi_context;
        }

        public FsaTransition(int xi_id, int xi_start, int xi_end, string xi_predicate, int xi_rank)
        {
            IdAttr             = xi_id;
            StartAttr          = xi_start;
            EndAttr            = xi_end;
            PredicateAttr.Text = xi_predicate;
            PredicateAttr.Rank = xi_rank;

            ail.net.framework.Assert.Condition(PredicateAttr.Rank <= ail.net.parser.FsaTransition.kMaxRankValue, "xi_rank");
        }

        public FsaTransition(int xi_id, int xi_start, int xi_end, string xi_predicate, string xi_context, int xi_rank)
        {
            IdAttr                = xi_id;
            StartAttr             = xi_start;
            EndAttr               = xi_end;
            PredicateAttr.Text    = xi_predicate;
            PredicateAttr.Context = xi_context;
            PredicateAttr.Rank    = xi_rank;

            ail.net.framework.Assert.Condition(PredicateAttr.Rank <= ail.net.parser.FsaTransition.kMaxRankValue, "xi_rank");
        }

        public FsaTransition(int xi_id, int xi_start, int xi_end, string xi_predicate, char xi_switch_char, string xi_context, int xi_rank)
        {
            IdAttr                   = xi_id;
            StartAttr                = xi_start;
            EndAttr                  = xi_end;
            PredicateAttr.Text       = xi_predicate;
            PredicateAttr.SwitchChar = xi_switch_char;
            PredicateAttr.Context    = xi_context;
            PredicateAttr.Rank       = xi_rank;

            ail.net.framework.Assert.Condition(PredicateAttr.Rank <= ail.net.parser.FsaTransition.kMaxRankValue, "xi_rank");
        }

        ~FsaTransition()
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
        
        public int Start
        {
            get
            {
                return StartAttr;
            }

            set
            {
                StartAttr = value;
            }
        }
        
        public int End
        {
            get
            {
                return EndAttr;
            }

            set
            {
                EndAttr = value;
            }
        }
        
        public ail.net.parser.FsaTransitionPredicate Predicate
        {
            get
            {
                return PredicateAttr;
            }

            set
            {
                PredicateAttr = value;
            }
        }
        #endregion // properties

        #region operators
        public static bool operator == (FsaTransition xi_lhs, FsaTransition xi_rhs)
        {
            bool result = (object)xi_lhs != (object)null && (object)xi_rhs != (object)null && xi_lhs.Id == xi_rhs.Id;
            return result;
        }

        public static bool operator != (FsaTransition xi_lhs, FsaTransition xi_rhs)
        {
            bool result = !(xi_lhs == xi_rhs);
            return result;
        }
        #endregion // operators

        #region methods
	    public object Clone()
	    {
		    FsaTransition result = new FsaTransition();

		    result.Id        = Id;
		    result.Start     = Start;
		    result.End       = End;
		    result.Predicate = (ail.net.parser.FsaTransitionPredicate)Predicate.Clone();

		    return result;
		}

        public int CompareTo(object xi_rhs)
        {
            ail.net.framework.Assert.NonNullReference(xi_rhs, "xi_rhs");
            ail.net.framework.Assert.ExpectedType(xi_rhs, "xi_rhs", typeof(FsaTransition));

            int result = 0;

            if(Id < ((FsaTransition)xi_rhs).Id)
            {
                result = -1;
            }
            else if(Id > ((FsaTransition)xi_rhs).Id)
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
            ail.net.framework.Assert.ExpectedType(xi_rhs, "xi_rhs", typeof(FsaTransition));

            bool result = this == ((FsaTransition)xi_rhs);
            return result;
        }

        public override int GetHashCode()
        {
            int result = Id;
            return result;
        }

        public bool IsEpsilon()
        {
            bool result = Predicate.Text == ail.net.parser.FsaTransition.kEpsilonPredicate;
            return result;
        }
        #endregion // methods
    }
}

#region epilog
#endregion
