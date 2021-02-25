//......................................................................................
// This is a part of UI Soft Library.  1989-2006 UI Soft Inc.               .
//......................................................................................
// THIS CODE MAY BE USED, COPIED, STORED, OR DISTRIBUTED ONLY IN ACCORDANCE WITH       .
// A WRITTEN LICENSE AGREEMENT AND WITH THE INCLUSION OF THIS COPYRIGHT NOTICE.        .
//......................................................................................

#region prolog
// file       : 
// description: GrammarPool
// package    : ail.net.parser
//
#endregion

#region import
using System;
using System.Collections;
using System.Text;
#endregion

namespace ail.net.parser
{
    /// <summary>
    /// summary description for GrammarPool
    /// </summary>
    public class GrammarPool : IDisposable
    {
        #region data members
        private int                 NonTerminalCountAttr;
        private int                 TerminalCountAttr;
        private Hashtable           PoolAttr     = new Hashtable();
        private static GrammarPool  InstanceAttr = null;
        #endregion // data members

        #region ctor/dtor/finalizer
        public GrammarPool()
        {
        }

       ~GrammarPool()
        {
            Dispose(false);
        }
        #endregion ctor/dtor/finalizer

        #region properties
        public int TerminalCount
        {
            get
            {
                return TerminalCountAttr;
            }

            set
            {
                TerminalCountAttr = value;
            }
        }

        public int NonTerminalCount
        {
            get
            {
                return NonTerminalCountAttr;
            }

            set
            {
                NonTerminalCountAttr = value;
            }
        }
        
        public Hashtable Pool
        {
            get
            {
                return PoolAttr;
            }

            set
            {
                PoolAttr = value;
            }
        }

        public static GrammarPool Instance
        {
            get
            {
                if(InstanceAttr == (object)null)
                {
                    lock(typeof(GrammarPool))
                    {
                        if(InstanceAttr == (object)null)
                        {
                            InstanceAttr = new GrammarPool();
                        }
                    }
                }

                return InstanceAttr;
            }
        }
        #endregion // properties

        #region indexers
        public ail.net.parser.GrammarSymbol this [int xi_symbol_id]
        {
            get
            {
                ail.net.parser.GrammarSymbol result = (ail.net.parser.GrammarSymbol)PoolAttr[xi_symbol_id];
                ail.net.framework.Assert.NonNullReference(result, "result");
                return result;
            }
        }
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
                PoolAttr = null;
            }

            // free unmanaged objects, including base class
            // set large fields to null (de-reference)
        }

        public bool HasSymbol(int xi_symbol_id)
        {
            return PoolAttr.Contains(xi_symbol_id);
        }

        public ail.net.parser.GrammarSymbol AddSymbol(int xi_symbol_id, ail.net.parser.GrammarSymbol.EType xi_type, string xi_name)
        {
            ail.net.parser.GrammarSymbol result = (ail.net.parser.GrammarSymbol)PoolAttr[xi_symbol_id];

            if(result == (object)null)
            {
                result = new ail.net.parser.GrammarSymbol();

                result.Id   = xi_symbol_id;
                result.Type = xi_type;
                result.Name = xi_name;

                PoolAttr[xi_symbol_id] = result;

                if(result.IsNonTerminal())
                {
                    NonTerminalCountAttr++;
                }
                else if(result.IsTerminal())
                {
                    TerminalCountAttr++;
                }
            }

            ail.net.framework.Assert.NonNullReference(result, "result");

            result.AddRef();

            return result;
        }

        public void RemoveSymbol(int xi_symbol_id)
        {
            ail.net.parser.GrammarSymbol symbol = (ail.net.parser.GrammarSymbol)PoolAttr[xi_symbol_id];

            if(symbol != (object)null && symbol.Release() == 0)
            {
                if(symbol.IsNonTerminal())
                {
                    NonTerminalCountAttr--;
                }
                else if(symbol.IsTerminal())
                {
                    TerminalCountAttr--;
                }

                PoolAttr.Remove(symbol.Id);
            }
        }

        protected struct SymbolComparer : IComparer
        {
            public int Compare(object xi_i1, object xi_i2)
            {
                ail.net.parser.GrammarSymbol i1 = (ail.net.parser.GrammarSymbol)xi_i1;
                ail.net.parser.GrammarSymbol i2 = (ail.net.parser.GrammarSymbol)xi_i2;

                int result = 0;

                if(i1.Id < i2.Id)
                {
                    result = -1;
                }
                else if(i1.Id > i2.Id)
                {
                    result = 1;
                }

                return result;
            }
        }

        public string DecoratePool()
        {
            StringBuilder result = new StringBuilder();

            ArrayList symbols = new ArrayList(PoolAttr.Values);
            
            symbols.Sort(new ail.net.parser.GrammarPool.SymbolComparer());

            foreach(ail.net.parser.GrammarSymbol symbol in symbols)
            {
                result.Append(symbol.Name);

                if(symbol.Name == ail.net.parser.GrammarSymbol.kEpsilon)
                {
                    result.Append(@" : ");
                }
                else
                {
                    result.Append(@"   : ");
                }

                result.Append(symbol.Id);

                if(symbol.IsNonTerminal())
                {
                    result.Append(@", non-terminal");
                }
                else if(symbol.IsTerminal())
                {
                    result.Append(@", terminal");
                }
                else
                {
                    result.Append(@", <unknown>");
                }

                if(symbol.Nullable)
                {
                    result.Append(@", nullable");
                }

                result.Append(Environment.NewLine);
            }

            return result.ToString();
        }
        #endregion // methods
    }
}

#region epilog
#endregion
