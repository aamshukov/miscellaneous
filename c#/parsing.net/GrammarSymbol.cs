#region copyright
//......................................................................................
// This is a part of UI Soft Library.  1989-2006 UI Soft Inc.               .
//......................................................................................
// THIS CODE MAY BE USED, COPIED, STORED, OR DISTRIBUTED ONLY IN ACCORDANCE WITH       .
// A WRITTEN LICENSE AGREEMENT AND WITH THE INCLUSION OF THIS COPYRIGHT NOTICE.        .
//......................................................................................
#endregion

#region prolog
// file       :  
// description: GrammarSymbol 
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
    /// summary description for GrammarSymbol
    /// </summary>
    public class GrammarSymbol
    {
        #region constants
        public static string kEpsilon     = "~e~";
        public static string kEndOfStream = "~$~";

        public enum EType
        {
            eNonTerminal = 1,
            eTerminal
        };

        public enum EAssociativity
        {
            eLeftAssoc = 1,
            eRightAssoc
        };
        #endregion // constants

        #region data types
        public struct SymbolComparer : IComparer
        {
            public int Compare(object xi_s1, object xi_s2)
            {
                ail.net.parser.GrammarSymbol s1 = (ail.net.parser.GrammarSymbol)xi_s1;
                ail.net.parser.GrammarSymbol s2 = (ail.net.parser.GrammarSymbol)xi_s2;

                int result = 0;

                if(s1.IdAttr < s2.IdAttr)
                {
                    result = -1;
                }
                else if(s1.IdAttr > s2.IdAttr)
                {
                    result = 1;
                }

                return result;
            }
        }

        public struct SymbolNameComparer : IComparer
        {
            public int Compare(object xi_s1, object xi_s2)
            {
                ail.net.parser.GrammarSymbol s1 = (ail.net.parser.GrammarSymbol)xi_s1;
                ail.net.parser.GrammarSymbol s2 = (ail.net.parser.GrammarSymbol)xi_s2;

                int result = s1.NameAttr == s2.NameAttr ? 1 : 0;

                if((int)s1.NameAttr[0] < (int)s2.NameAttr[0])
                {
                    result = -1;
                }
                else if((int)s1.NameAttr[0] > (int)s2.NameAttr[0])
                {
                    result = 1;
                }

                return result;
            }
        }
        #endregion // data types

        #region data members
        private int             IdAttr;                 // enumerable type, will be cast to specific enum values
        private EType           TypeAttr;               // terminal or non-terminal
        private int             CountAttr;              // reference counting for grammar symbols pool
        private string          NameAttr;               // name (label) of the symbol
        private bool            NullableAttr;           // if A ->* e
        private bool            TerminalDerivableAttr;  // if A ->* w (can generate any terminal strings)
        private bool            AccessableAttr;         // reachable, if [S ->* a(lpha) X b(eta)], any sumbol X is accessable
        private int             PrecedenceAttr;         // precedence level of terminal (shift/reduce parsers)
        private EAssociativity  AssociativityAttr;      // associativity of terminals (shift/reduce parsers)
        private ArrayList       FirstSetAttr;           // 'first set' is the set of terminals that can start a string
                                                        // that is derivable from this non-terminal
        private ArrayList       EFFirstSetAttr;         // 'epsilon-free first set'
        private ArrayList       FollowSetAttr;          // 'follow set' is a set of terminals which may follow A
                                                        // (be immediately after A) in a valid derivation
        private string          SemanticsAttr;          // semantic action (source code)
        private int             StateAttr;              // state
        private bool            ErroneousAttr;          // if a non-terminal can be part of a A -> 'error' rule
        #endregion // data members

        #region ctor/dtor/finalizer
        public GrammarSymbol()
        {
        }

       ~GrammarSymbol()
        {
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

        public EType Type
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

        public int Count
        {
            get
            {
                return CountAttr;
            }

            set
            {
                CountAttr = value;
            }
        }

        public string Name
        {
            get
            {
                return NameAttr;
            }

            set
            {
                NameAttr = value;
            }
        }

        public bool Nullable
        {
            get
            {
                return NullableAttr;
            }

            set
            {
                NullableAttr = value;
            }
        }

        public bool TerminalDerivable
        {
            get
            {
                return TerminalDerivableAttr;
            }

            set
            {
                TerminalDerivableAttr = value;
            }
        }

        public bool Accessable
        {
            get
            {
                return AccessableAttr;
            }

            set
            {
                AccessableAttr = value;
            }
        }

        public int Precedence
        {
            get
            {
                return PrecedenceAttr;
            }

            set
            {
                PrecedenceAttr = value;
            }
        }

        public EAssociativity Associativity
        {
            get
            {
                return AssociativityAttr;
            }

            set
            {
                AssociativityAttr = value;
            }
        }

        public ArrayList FirstSet
        {
            get
            {
                if(FirstSetAttr == (object)null)
                {
                    FirstSetAttr = new ArrayList();
                }
                return FirstSetAttr;
            }
        }

        public ArrayList EFFirstSet
        {
            get
            {
                if(EFFirstSetAttr == (object)null)
                {
                    EFFirstSetAttr = new ArrayList();
                }
                return EFFirstSetAttr;
            }
        }

        public ArrayList FollowSet
        {
            get
            {
                if(FollowSetAttr == (object)null)
                {
                    FollowSetAttr = new ArrayList();
                }
                return FollowSetAttr;
            }
        }

        public string Semantics
        {
            get
            {
                return SemanticsAttr;
            }

            set
            {
                SemanticsAttr = value;
            }
        }

        public int State
        {
            get
            {
                return StateAttr;
            }

            set
            {
                StateAttr = value;
            }
        }

        public bool Erroneous
        {
            get
            {
                return ErroneousAttr;
            }

            set
            {
                ErroneousAttr = value;
            }
        }
        #endregion // properties

        #region methods
        public bool IsNonTerminal()
        {
            return TypeAttr == ail.net.parser.GrammarSymbol.EType.eNonTerminal;
        }

        public bool IsTerminal()
        {
            return TypeAttr == ail.net.parser.GrammarSymbol.EType.eTerminal;
        }

        public int AddRef()
        {
            return ++CountAttr;
        }

        public int Release()
        {
            return Math.Max(0, --CountAttr);
        }
        #endregion // methods
    }
}

#region epilog
#endregion
