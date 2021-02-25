//......................................................................................
// This is a part of UI Soft Library.  1989-2006 UI Soft Inc.               .
//......................................................................................
// THIS CODE MAY BE USED, COPIED, STORED, OR DISTRIBUTED ONLY IN ACCORDANCE WITH       .
// A WRITTEN LICENSE AGREEMENT AND WITH THE INCLUSION OF THIS COPYRIGHT NOTICE.        .
//......................................................................................

#region prolog
// file       : 
// description: FsaStateSet
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
    /// summary description for FsaStateSet
    /// </summary>
    public class FsaStateSet : IComparable
    {
        #region data members
        int                 IdAttr;
        private Hashtable   StatesAttr      = new Hashtable();
        private Hashtable   TransitionsAttr = new Hashtable();
        private bool        MarkedAttr;
        #endregion // data members

        #region ctor/dtor/finalizer
        public FsaStateSet()
        {
        }

        public FsaStateSet(int xi_id)
        {
            Id = xi_id;
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

        public Hashtable States
        {
            get
            {
                return StatesAttr;
            }

            set
            {
                StatesAttr = value;
            }
        }

        public Hashtable Transitions
        {
            get
            {
                return TransitionsAttr;
            }

            set
            {
                TransitionsAttr = value;
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
		public static bool operator == (FsaStateSet xi_lhs, FsaStateSet xi_rhs)
		{
            bool result = (object)xi_lhs != (object)null && (object)xi_rhs != (object)null && xi_lhs.States.Count == xi_rhs.States.Count;

			if(result)
			{
                IEnumerator lhs_it = xi_lhs.States.GetEnumerator();
                IEnumerator rhs_it = xi_rhs.States.GetEnumerator();

				while(lhs_it.MoveNext() && rhs_it.MoveNext())
				{
				    ail.net.parser.FsaState lhs_state = (ail.net.parser.FsaState)((DictionaryEntry)lhs_it.Current).Value;
                    ail.net.parser.FsaState rhs_state = (ail.net.parser.FsaState)((DictionaryEntry)rhs_it.Current).Value;

                    if(lhs_state.Id != rhs_state.Id)
                    {
                        result = false;
                        break;
                    }
                }
			}

			return result;
		}

		public static bool operator != (FsaStateSet xi_lhs, FsaStateSet xi_rhs)
		{
			bool result = !(xi_lhs == xi_rhs);
			return result;
		}
		#endregion // operators

		#region methods
		public int CompareTo(object xi_rhs)
		{
			ail.net.framework.Assert.NonNullReference(xi_rhs, "xi_rhs");
			ail.net.framework.Assert.ExpectedType(xi_rhs, "xi_rhs", typeof(FsaStateSet));

			int result = 0;

			if(Id < ((FsaStateSet)xi_rhs).Id)
			{
				result = -1;
			}
			else if(Id > ((FsaStateSet)xi_rhs).Id)
			{
				result = 1;
			}

			return result;
		}
		
		public override bool Equals(object xi_rhs)
		{
			ail.net.framework.Assert.ExpectedType(xi_rhs, "xi_rhs", typeof(FsaStateSet));

			bool result = this == ((FsaStateSet)xi_rhs);
			return result;
		}

		public override int GetHashCode()
		{
			int result = Id;
			return result;
		}

		public void Print()
        {
            Console.WriteLine("eclosure: {0} states{1}", States.Count, '\n');

            foreach(ail.net.parser.FsaState state in States.Values)
            {
                string text = string.Format("\tstate: [{0}]", state.Id);

                if(state.Label.Length > 0)
                {
                    text += string.Format(" \"{0}\"", state.Label);
                }

                Console.WriteLine(text);
            }
        }
        #endregion // methods
    }
}

#region epilog
#endregion
