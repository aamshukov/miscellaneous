//......................................................................................
// This is a part of UI Soft Library. Copyright © 1989-2006 UI Soft Inc.               .
//......................................................................................
// THIS CODE MAY BE USED, COPIED, STORED, OR DISTRIBUTED ONLY IN ACCORDANCE WITH       .
// A WRITTEN LICENSE AGREEMENT AND WITH THE INCLUSION OF THIS COPYRIGHT NOTICE.        .
//......................................................................................

#region prolog
// file       : 
// description: GrammarRule
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
    /// summary description for GrammarRule
    /// </summary>
    public class GrammarRule : IDisposable
    {
        #region constants
        #endregion // constants

        #region data members
        private int         IdAttr;                             // enumerable type, will be cast to specific enum values
        private int         LhsNonTerminalCountAttr;
        private int         LhsTerminalCountAttr;
        private int         RhsNonTerminalCountAttr;
        private int         RhsTerminalCountAttr;
        private ArrayList   LhsAttr         = new ArrayList();
        private ArrayList   RhsAttr         = new ArrayList();
        private ArrayList   PrecedencesAttr = new ArrayList();  // context dependent precedence level of terminals for the rule (shift/reduce parsers)
        private string      NameAttr;
        #endregion // data members

        #region ctor/dtor/finalizer
        public GrammarRule(int xi_id)
        {
            IdAttr = xi_id;
        }

        ~GrammarRule()
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
        
        public int LhsNonTerminalCount
        {
            get
            {
                return LhsNonTerminalCountAttr;
            }

            set
            {
                LhsNonTerminalCountAttr = value;
            }
        }
        
        public int LhsTerminalCount
        {
            get
            {
                return LhsTerminalCountAttr;
            }

            set
            {
                LhsTerminalCountAttr = value;
            }
        }
        
        public int RhsNonTerminalCount
        {
            get
            {
                return RhsNonTerminalCountAttr;
            }

            set
            {
                RhsNonTerminalCountAttr = value;
            }
        }
        
        public int RhsTerminalCount
        {
            get
            {
                return RhsTerminalCountAttr;
            }

            set
            {
                RhsTerminalCountAttr = value;
            }
        }
        
        public ArrayList Lhs
        {
            get
            {
                return LhsAttr;
            }

            set
            {
                LhsAttr = value;
            }
        }
        
        public ArrayList Rhs
        {
            get
            {
                return RhsAttr;
            }

            set
            {
                RhsAttr = value;
            }
        }
        
        public ArrayList Precedences
        {
            get
            {
                return PrecedencesAttr;
            }

            set
            {
                PrecedencesAttr = value;
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
        #endregion // properties

        #region indexers
        #endregion // properties

        #region methods
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
                LhsAttr         = null;
                RhsAttr         = null;
                PrecedencesAttr = null;
            }

            // free unmanaged objects, including base class
            // set large fields to null (de-reference)
        }

        public bool IsEmpty()
        {
            return LhsAttr.Count == 0;
        }

        public bool IsEmptyRule()
        {
            ail.net.framework.Assert.Condition(RhsAttr.Count > 0, "ail.net.parser.GrammarRule.IsEmptyRule: Rhs.Count > 0");
            return RhsAttr.Count == 1 && ((ail.net.parser.GrammarSymbol)RhsAttr[0]).Id == (int)ail.net.parser.Token.EType.eEpsilon;
        }

        public bool IsErroneousRule()
        {
            ail.net.framework.Assert.Condition(RhsAttr.Count > 0, "ail.net.parser.GrammarRule.IsErroneousRule: Rhs.Count > 0");
            return RhsAttr.Count == 1 && ((ail.net.parser.GrammarSymbol)RhsAttr[0]).Id == (int)ail.net.parser.Token.EType.eError;
        }

        bool IsNullable()
        {
            return RhsAttr.Count == 0;
        }

        public ail.net.parser.GrammarSymbol AddLhsSymbol(int xi_symbol_id, ail.net.parser.GrammarSymbol.EType xi_type, string xi_name)
        {
            ail.net.parser.GrammarSymbol result = GrammarPool.Instance.AddSymbol(xi_symbol_id, xi_type, xi_name);

            LhsAttr.Add(result);

            if(result.IsNonTerminal())
            {
                LhsNonTerminalCountAttr++;
            }
            else if(result.IsTerminal())
            {
                LhsTerminalCountAttr++;
            }

            return result;
        }

        public void RemoveLhsSymbol(int xi_symbol_id)
        {
            foreach(ail.net.parser.GrammarSymbol symbol in LhsAttr)
            {
                if(symbol.Id == xi_symbol_id)
                {
                    if(symbol.IsNonTerminal())
                    {
                        LhsNonTerminalCountAttr--;
                    }
                    else if(symbol.IsTerminal())
                    {
                        LhsTerminalCountAttr--;
                    }

                    LhsAttr.Remove(symbol);
                    GrammarPool.Instance.RemoveSymbol(xi_symbol_id);
                }
            }
        }

        public ail.net.parser.GrammarSymbol AddRhsSymbol(int xi_symbol_id, ail.net.parser.GrammarSymbol.EType xi_type, string xi_name)
        {
            ail.net.parser.GrammarSymbol result = GrammarPool.Instance.AddSymbol(xi_symbol_id, xi_type, xi_name);

            RhsAttr.Add(result);

            if(result.IsNonTerminal())
            {
                RhsNonTerminalCountAttr++;
            }
            else if(result.IsTerminal())
            {
                RhsTerminalCountAttr++;
            }

            return result;
        }

        public void RemoveRhsSymbol(int xi_symbol_id)
        {
            foreach(ail.net.parser.GrammarSymbol symbol in RhsAttr)
            {
                if(symbol.Id == xi_symbol_id)
                {
                    if(symbol.IsNonTerminal())
                    {
                        RhsNonTerminalCountAttr--;
                    }
                    else if(symbol.IsTerminal())
                    {
                        RhsTerminalCountAttr--;
                    }

                    RhsAttr.Remove(symbol);
                    GrammarPool.Instance.RemoveSymbol(xi_symbol_id);
                }
            }
        }
        #endregion // methods
    }
}

#region epilog
#endregion
