//......................................................................................
// This is a part of UI Soft Library. Copyright © 1989-2006 UI Soft Inc.               .
//......................................................................................
// THIS CODE MAY BE USED, COPIED, STORED, OR DISTRIBUTED ONLY IN ACCORDANCE WITH       .
// A WRITTEN LICENSE AGREEMENT AND WITH THE INCLUSION OF THIS COPYRIGHT NOTICE.        .
//......................................................................................
#region defines
#define PRINT_STATS
#define FIRST_K1
#endregion // defines

#region prolog
// file       : 
// description: LRParser
// package    : ail.net.parser
//
#endregion

#region import
using System;
using System.Collections;
using System.Text;
using System.IO;
#endregion

namespace ail.net.parser
{
    /// <summary>
    /// summary description for LRParser
    /// </summary>
    public class LRParser : ail.net.parser.Parser
    {
        #region constants
        [FlagsAttribute]
        private enum EFlags : uint
        {
            eAccepted   = 0x00000002,
            eReduce     = 0x00000004,
            eFinalState = 0x00000100,
            eMarked     = 0x80000000
        };

        public enum ELRMode
        {
            eLR0,
            eLR1
        };

        public enum ELRConflict
        {
            eShiftReduce,
            eReduceReduce
        };

        public enum ELRCompareMode
        {
            eWithLookahead,
            eCoreItemOnly
        };

        public enum ELRAction
        {
            eShift,
            eReduce,
            eAccept,
            eError
        };

        protected const uint kAcceptCode   = 0x08000000; // accept entry
        protected const int  kAcceptedCode = 123456789;  // accept entry
        protected const uint kErrorCode    = 0x08100000; // error entry
        #endregion // constants

        #region data types
        public class CoreItem
        {
            public int                        Id;   // unique id
            public ail.net.parser.GrammarRule Rule; // production (rule)
            public int                        Dot;  // dot - position in rhs,
                                                    // if Dot = rhs.count it means it points to the end of the rhs
        };

        public class Item
        {
#if PRINT_STATS
            public int                              Id;         // unique id
#endif
            public ail.net.parser.LRParser.CoreItem CoreItem;   // pointer to static core item
            public ail.net.parser.GrammarSymbol     Lookahead;  // terminal for LR(1) and undefined for LR(0)
        }

#if PRINT_STATS
        protected struct ItemComparer : IComparer
        {
            public int Compare(object xi_i1, object xi_i2)
            {
                ail.net.parser.LRParser.Item i1 = (ail.net.parser.LRParser.Item)xi_i1;
                ail.net.parser.LRParser.Item i2 = (ail.net.parser.LRParser.Item)xi_i2;

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
#endif
        protected struct ItemLaComparer : IComparer // lookahead symbol comparer
        {
            public int Compare(object xi_i1, object xi_i2)
            {
                ail.net.parser.LRParser.Item i1 = (ail.net.parser.LRParser.Item)xi_i1;
                ail.net.parser.LRParser.Item i2 = (ail.net.parser.LRParser.Item)xi_i2;

                ail.net.framework.Assert.NonNullReference(i1.Lookahead, "i1.Lookahead");
                ail.net.framework.Assert.NonNullReference(i2.Lookahead, "i2.Lookahead");

                int result = 0;

                if(i1.Lookahead.Id < i2.Lookahead.Id)
                {
                    result = -1;
                }
                else if(i1.Lookahead.Id > i2.Lookahead.Id)
                {
                    result = 1;
                }

                return result;
            }
        }

        public class State // automaton state with set of items
        {
            public int          Id;                             // unique id
            public Hashtable    Items       = new Hashtable();  // list of items
            public Hashtable    Transitions = new Hashtable();  // outcomming transitions
            public uint         Flags;                          // flags
        };

#if PRINT_STATS
        protected struct StateComparer : IComparer
        {
            public int Compare(object xi_s1, object xi_s2)
            {
                ail.net.parser.LRParser.State s1 = (ail.net.parser.LRParser.State)xi_s1;
                ail.net.parser.LRParser.State s2 = (ail.net.parser.LRParser.State)xi_s2;

                int result = 0;

                if(s1.Id < s2.Id)
                {
                    result = -1;
                }
                else if(s1.Id > s2.Id)
                {
                    result = 1;
                }

                return result;
            }
        }
#endif
        public class Transition
        {
            public ail.net.parser.GrammarSymbol  Symbol; // predicate
            public ail.net.parser.LRParser.State State;  // to state
        };

        protected struct TableKey
        {
            public int Id;    // symbol id, terminal or non-terminal
            public int State; // state number

            public TableKey(int xi_symbol, int xi_state)
            {
                Id = xi_symbol;
                State = xi_state;
            }
            
            public static bool operator == (TableKey xi_lhs, TableKey xi_rhs)
            {
                // no args assertion!!!
                return xi_lhs.Id == xi_rhs.Id && xi_lhs.State == xi_rhs.State;
            }

            public static bool operator != (TableKey xi_lhs, TableKey xi_rhs)
            {
                // no args assertion!!!
                return !(xi_lhs == xi_rhs);
            }

            public override bool Equals(object xi_rhs)
            {
                // no args assertion!!!
                return this == ((TableKey)xi_rhs);
            }

            public override int GetHashCode()
            {
                // no args assertion!!!
                return ail.net.framework.Functor.DualIntHash(Id, State);
            }
        }
        #endregion // data types

        #region data members
        private ail.net.parser.LRParser.State           StartStateAttr;                     // start state
        private ArrayList                               StatesAttr       = new ArrayList(); // states
        private ArrayList                               CanonicalSetAttr = new ArrayList(); // canonical set
        private Hashtable                               ActionTableAttr  = new Hashtable(); // action table
        private Hashtable                               GoToTableAttr    = new Hashtable(); // goto table

        private ArrayList                               CoreItemTableAttr;                  // prebuild core items table

        private Hashtable                               PredictTableAttr;                   // prediction table, [non-terminal][list of core items]
        private bool []                                 PredictedNonTerminalsAttr;          // vector of predicted non-terminals
        private bool []                                 PredictedNonTerminalsZeroizerAttr;  // predefined vector of 'false' values for quick clean up

        private ail.net.parser.Semantics                SemanticsAttr;                      // semantics interface

        private ail.net.parser.LRParser.ELRMode         LRModeAttr;                         // LR mode
        private ail.net.parser.LRParser.ELRCompareMode  LRCompareModeAttr;
        #endregion // data members

        #region ctor/dtor/finalizer
        public LRParser(ail.net.parser.LexAnalyzer xi_lexer, ail.net.parser.Grammar xi_grammar, ArrayList xi_errors)
            : base(xi_lexer, xi_grammar, xi_errors)
        {
            LRModeAttr = ail.net.parser.LRParser.ELRMode.eLR0;
            LRCompareModeAttr = ail.net.parser.LRParser.ELRCompareMode.eWithLookahead;
        }

       ~LRParser()
        {
            Dispose(false);
        }
        #endregion ctor/dtor/finalizer

        #region properties
        public ail.net.parser.LRParser.State StartState
        {
            get
            {
                return StartStateAttr;
            }

            set
            {
                StartStateAttr = value;
            }
        }

        public ArrayList States
        {
            get
            {
                return StatesAttr;
            }
        }

        public ArrayList CanonicalSet
        {
            get
            {
                return CanonicalSetAttr;
            }
        }

        public ArrayList CoreItemTable
        {
            get
            {
                return CoreItemTableAttr;
            }

            set
            {
                CoreItemTableAttr = value;
            }
        }

        public Hashtable PredictTable
        {
            get
            {
                return PredictTableAttr;
            }
        }

        public bool [] PredictedNonTerminals
        {
            get
            {
                return PredictedNonTerminalsAttr;
            }
        }

        public bool [] PredictedNonTerminalsZeroizer
        {
            get
            {
                return PredictedNonTerminalsZeroizerAttr;
            }
        }

        public ail.net.parser.Semantics Semantics
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

        public ail.net.parser.LRParser.ELRMode LRMode
        {
            get
            {
                return LRModeAttr;
            }

            set
            {
                LRModeAttr = value;
            }
        }

        public ail.net.parser.LRParser.ELRCompareMode LRCompareMode
        {
            get
            {
                return LRCompareModeAttr;
            }

            set
            {
                LRCompareModeAttr = value;
            }
        }

        public Hashtable ActionTable
        {
            get
            {
                return ActionTableAttr;
            }
        }

        public Hashtable GoToTable
        {
            get
            {
                return GoToTableAttr;
            }
        }
        #endregion // properties

        #region methods
        protected override void Dispose(bool xi_disposing)
        {
            if(xi_disposing)
            {
                // free managed objects
                StatesAttr                        = null;
                CoreItemTableAttr                 = null;
                PredictTableAttr                  = null;
                PredictedNonTerminalsAttr         = null;
                PredictedNonTerminalsZeroizerAttr = null;
            }

            // free unmanaged objects, including base class
            // set large fields to null (de-reference)
        }

        public virtual void Init()
        {
            // initialize
            PopulateCoreItemTable();
            PopulatePredictTable();
            Grammar.PopulateRulesMap();
        }

        public virtual void Parse()
        {
            // all stack elements are UINT
            Stack stack = new Stack();
            
            ail.net.parser.LRParser.TableKey key = new ail.net.parser.LRParser.TableKey();
            
            Lexer.NextLexeme();  // get first lexeme
            stack.Push((uint)0); // push initial state

            for(;;)
            {
                key.Id = Lexer.Token.Type;
                key.State = (int)((uint)stack.Peek() & ~(uint)ail.net.parser.LRParser.EFlags.eMarked);

                uint entry = ail.net.parser.LRParser.kErrorCode;

                object o_entry = ActionTableAttr[key];

                if(o_entry != null) // check if error slot was hit
                {
                    entry = (uint)o_entry;
                }

                if(entry == kAcceptCode)
                {
                    // accept
                    Status = ail.net.parser.Parser.EStatus.eRecognized;
                    Console.WriteLine("accepted: "+Grammar.DecorateRule(Grammar.StartRule));
                    Console.WriteLine(Environment.NewLine);
                    break;
                }
                else if(entry == kErrorCode)
                {
                    // error
                    Status = ail.net.parser.Parser.EStatus.eFailed;
                }
                if((entry & (uint)ail.net.parser.LRParser.EFlags.eMarked) != 0)
                {
                    // shift
                    stack.Push(Lexer.Token.Type);
                    stack.Push(entry);
                    Lexer.NextLexeme();
                    Console.WriteLine("shift: "+(Lexer.IsEndOfStream() ? "$" : Lexer.Lexeme));
                    Console.WriteLine(Environment.NewLine);
                }
                else if((entry & (uint)ail.net.parser.LRParser.EFlags.eMarked) == 0)
                {
                    // reduce
                    ail.net.parser.GrammarRule rule = (ail.net.parser.GrammarRule)Grammar.RulesMap[(int)entry];
                    ail.net.framework.Assert.NonNullReference(rule, "rule");

                    for(int i = 0, n = 2*(rule.IsEmptyRule() ? 0 : rule.Rhs.Count); i < n; i++)
                    {
                        stack.Pop();
                    }
                    
                    entry = ((uint)stack.Peek() & ~(uint)ail.net.parser.LRParser.EFlags.eMarked);
                    
                    stack.Push(((ail.net.parser.GrammarSymbol)rule.Lhs[0]).Id);
                    
                    key.Id = ((ail.net.parser.GrammarSymbol)rule.Lhs[0]).Id;
                    key.State = (int)entry;

                    entry = (uint)(int)GoToTableAttr[key];

                    stack.Push(entry);

                    Console.WriteLine("reduce: "+Grammar.DecorateRule(rule));
                    Console.WriteLine(Environment.NewLine);
                }
            }
        }
        
        protected void BuildActionTable()
        {
            if(LRModeAttr == ail.net.parser.LRParser.ELRMode.eLR0)
            {
                BuildActionTable0();
            }
            else if(LRModeAttr == ail.net.parser.LRParser.ELRMode.eLR1)
            {
                BuildActionTableK1();
            }
        }

        protected void BuildActionTable0()
        {
            // all table entries are UINT
            ActionTableAttr.Clear();

            foreach(ail.net.parser.LRParser.State state in StatesAttr)
            {
                foreach(ail.net.parser.LRParser.Item item in state.Items.Values)
                {
                    if(item.CoreItem.Dot < item.CoreItem.Rule.Rhs.Count && !item.CoreItem.Rule.IsEmptyRule() &&
                       ((ail.net.parser.GrammarSymbol)item.CoreItem.Rule.Rhs[item.CoreItem.Dot]).IsTerminal())
                    {
                        // [A -> a(lpha) * a b(eta)] belongs Ii and goto(Ii, a) = Ij => action[i, a] = shift J
                        ail.net.parser.GrammarSymbol symbol = (ail.net.parser.GrammarSymbol)item.CoreItem.Rule.Rhs[item.CoreItem.Dot];
                        ail.net.parser.LRParser.Transition transition = (ail.net.parser.LRParser.Transition)state.Transitions[symbol.Id];

                        if(transition != (object)null)
                        {
                            ail.net.parser.LRParser.TableKey key = new TableKey(symbol.Id, state.Id);

                            if(!ActionTableAttr.Contains(key))
                            {
                                ActionTableAttr.Add(key, (uint)transition.State.Id|(uint)ail.net.parser.LRParser.EFlags.eMarked);
                            }
                        }
                    }
                    else if((item.CoreItem.Dot == item.CoreItem.Rule.Rhs.Count || item.CoreItem.Rule.IsEmptyRule()) &&
                        ((ail.net.parser.GrammarSymbol)item.CoreItem.Rule.Lhs[0]).Id != Grammar.StartSymbolId)
                    {
                        // [A -> a(lpha) *] belongs Ii and A != S' => for all terminals add action[i, a] = reduce A -> a(lpha)
                        foreach(ail.net.parser.GrammarSymbol symbol in ail.net.parser.GrammarPool.Instance.Pool.Values)
                        {
                            if(symbol.IsTerminal())
                            {
                                ail.net.parser.LRParser.TableKey key = new TableKey(symbol.Id, state.Id);

                                if(!ActionTableAttr.Contains(key))
                                {
                                    ActionTableAttr.Add(key, (uint)item.CoreItem.Rule.Id);
                                }
                            }
                        }
                    }
                    else if((item.CoreItem.Dot == item.CoreItem.Rule.Rhs.Count || item.CoreItem.Rule.IsEmptyRule()) &&
                        ((ail.net.parser.GrammarSymbol)item.CoreItem.Rule.Lhs[0]).Id == Grammar.StartSymbolId)
                    {
                        // [S' -> S *] belongs Ii => action[i, $] = accept
                        ail.net.parser.LRParser.TableKey key = new TableKey((int)ail.net.parser.Token.EType.eEndOfStream, state.Id);

                        if(!ActionTableAttr.Contains(key))
                        {
                            ActionTableAttr.Add(key, (uint)ail.net.parser.LRParser.kAcceptCode);
                        }
                    }
                }
            }
        }

        protected void BuildActionTable1()
        {
            // all table entries are UINT
            ActionTableAttr.Clear();

            foreach(ail.net.parser.LRParser.State state in StatesAttr)
            {
                foreach(ail.net.parser.LRParser.Item item in state.Items.Values)
                {
                    if(item.CoreItem.Dot < item.CoreItem.Rule.Rhs.Count && !item.CoreItem.Rule.IsEmptyRule() &&
                       ((ail.net.parser.GrammarSymbol)item.CoreItem.Rule.Rhs[item.CoreItem.Dot]).IsTerminal())
                    {
                        // [A -> a(lpha) * a b(eta), b] belongs Ii and goto(Ii, a) = Ij => action[i, a] = shift J
                        ail.net.parser.GrammarSymbol symbol = (ail.net.parser.GrammarSymbol)item.CoreItem.Rule.Rhs[item.CoreItem.Dot];
                        ail.net.parser.LRParser.Transition transition = (ail.net.parser.LRParser.Transition)state.Transitions[symbol.Id];

                        if(transition != (object)null)
                        {
                            ail.net.parser.LRParser.TableKey key = new TableKey(symbol.Id, state.Id);

                            if(!ActionTableAttr.Contains(key))
                            {
                                ActionTableAttr.Add(key, (uint)transition.State.Id|(uint)ail.net.parser.LRParser.EFlags.eMarked);
                            }
                        }
                    }
                    else if((item.CoreItem.Dot == item.CoreItem.Rule.Rhs.Count || item.CoreItem.Rule.IsEmptyRule()) &&
                            ((ail.net.parser.GrammarSymbol)item.CoreItem.Rule.Lhs[0]).Id != Grammar.StartSymbolId)
                    {
                        // [A -> a(lpha) *, a] belongs Ii and A != S' => action[i, a] = reduce A -> a(lpha)
                        ail.net.framework.Assert.NonNullReference(item.Lookahead, "item.Lookahead");
                        ail.net.parser.LRParser.TableKey key = new TableKey(item.Lookahead.Id, state.Id);

                        if(!ActionTableAttr.Contains(key))
                        {
                            ActionTableAttr.Add(key, (uint)item.CoreItem.Rule.Id);
                        }
                    }
                    else if((item.CoreItem.Dot == item.CoreItem.Rule.Rhs.Count || item.CoreItem.Rule.IsEmptyRule()) &&
                            ((ail.net.parser.GrammarSymbol)item.CoreItem.Rule.Lhs[0]).Id == Grammar.StartSymbolId)
                    {
                        // [S' -> S *, $] belongs Ii => action[i, $] = accept
                        ail.net.framework.Assert.NonNullReference(item.Lookahead, "item.Lookahead");
                        ail.net.parser.LRParser.TableKey key = new TableKey(item.Lookahead.Id, state.Id);

                        if(!ActionTableAttr.Contains(key))
                        {
                            ActionTableAttr.Add(key, (uint)ail.net.parser.LRParser.kAcceptCode);
                        }
                    }
                }
            }
        }
        
        protected void BuildActionTableK1()
        {
            // all table entries are int:
            //  reduce actions are represented with negative numbers
            //  shift actions are represented with 0 and positive numbers
            //  error entries are undefined, meaning query that will return null
            ActionTableAttr.Clear();

            foreach(ail.net.parser.LRParser.State state in StatesAttr)
            {
                foreach(ail.net.parser.LRParser.Item item in state.Items.Values)
                {
                    ail.net.framework.Assert.NonNullReference(item.Lookahead, "item.Lookahead");

                    if(item.CoreItem.Dot < item.CoreItem.Rule.Rhs.Count)
                    {
                        // f(u) = shift, if exists [A -> b(eta)1 . b(eta)2, v] belongs to A,
                        // b(eta)2 != e(psilon) and u belongs to EFFk(b(eta)2 v)
                        ArrayList beta2v = new ArrayList();

                        for(int i = item.CoreItem.Dot; i < item.CoreItem.Rule.Rhs.Count; i++)
                        {
                            beta2v.Add(item.CoreItem.Rule.Rhs[i]);
                        }

                        beta2v.Add(item.Lookahead);

                        ArrayList eff = Grammar.BuildEFFirstKSet(beta2v, 1); // must be zero or one entry
                        
                        // u
                        foreach(ail.net.parser.GrammarSymbol symbol in ail.net.parser.GrammarPool.Instance.Pool.Values)
                        {
                            if(symbol.IsTerminal())
                            {
                                int u = symbol.Id;
                                
                                // check 'u belongs to EFFk(b(eta)2 v)'
                                bool contains = false;
                                
                                foreach(ArrayList list in eff)
                                {
                                    for(int i = 0; i < list.Count; i++)
                                    {
                                        if((int)list[i] == u)
                                        {
                                            contains = true;
                                            goto _break;
                                        }
                                    }
                                }
_break:                        
                                if(contains)
                                {
                                    ail.net.parser.GrammarSymbol transition_symbol = (ail.net.parser.GrammarSymbol)item.CoreItem.Rule.Rhs[item.CoreItem.Dot];
                                    ail.net.parser.LRParser.Transition transition = (ail.net.parser.LRParser.Transition)state.Transitions[transition_symbol.Id];

                                    if(transition != (object)null)
                                    {
                                        ail.net.parser.LRParser.TableKey key = new TableKey(transition_symbol.Id, state.Id);

                                        // we keep all possible entries of an action table slot in a list, but unique ones
                                        Hashtable action_table_entry = (Hashtable)ActionTableAttr[key];

                                        if(action_table_entry == null)
                                        {
                                            action_table_entry = new Hashtable();
                                            ActionTableAttr[key] = action_table_entry;
                                        }

                                        if(!action_table_entry.ContainsKey(transition.State.Id))
                                        {
                                            action_table_entry[transition.State.Id] = transition.State.Id;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        // f(u) = reduce i, [A -> b(eta) . , u] belongs to A, A -> b(eta) is ith rule in P (set of productions)
                        // f(u) = accept, if [S' -> S ., e(psilon)] belongs to A and u = e(psilon)
                        ail.net.parser.LRParser.TableKey key = new TableKey(item.Lookahead.Id, state.Id);

                        if(item.CoreItem.Rule.Id == 0) // always eS
                        {
                            if(item.Lookahead.Id == (int)ail.net.parser.Token.EType.eEpsilon)
                            {
                                Hashtable action_table_entry = (Hashtable)ActionTableAttr[key];

                                if(action_table_entry == null)
                                {
                                    action_table_entry = new Hashtable();
                                    ActionTableAttr[key] = action_table_entry;
                                }

                                if(!action_table_entry.ContainsKey(-kAcceptedCode))
                                {
                                    action_table_entry[-kAcceptedCode] = -kAcceptedCode; // must be only one per a key
                                }
                            }
                        }
                        else
                        {
                            // we keep all possible entries of an action table slot in a list, but unique ones
                            Hashtable action_table_entry = (Hashtable)ActionTableAttr[key];

                            if(action_table_entry == null)
                            {
                                action_table_entry = new Hashtable();
                                ActionTableAttr[key] = action_table_entry;
                            }

                            if(!action_table_entry.ContainsKey(-item.CoreItem.Rule.Id))
                            {
                                action_table_entry[-item.CoreItem.Rule.Id] = -item.CoreItem.Rule.Id;
                            }
                        }
                    }
                }
            }
        }

        protected void BuildGoToTable()
        {
            // all table entries are INT
            // goto(Ii, A)= Ij, goto[i, A] = j
            GoToTableAttr.Clear();

            foreach(ail.net.parser.LRParser.State state in StatesAttr)
            {
                foreach(ail.net.parser.GrammarSymbol symbol in ail.net.parser.GrammarPool.Instance.Pool.Values)
                {
                    if(symbol.IsNonTerminal())
                    {
                        ail.net.parser.LRParser.Transition transition = (ail.net.parser.LRParser.Transition)state.Transitions[symbol.Id];

                        if(transition != (object)null)
                        {
                            ail.net.parser.LRParser.TableKey key = new TableKey(symbol.Id, state.Id);

                            if(!GoToTableAttr.Contains(key))
                            {
                                GoToTableAttr.Add(key, transition.State.Id);
                            }
                        }
                    }
                }
            }
        }

        protected void BuildAutomaton()
        {
            // clear
            StatesAttr.Clear();

            // build automaton
            StartStateAttr = new ail.net.parser.LRParser.State();

            AddItem(StartStateAttr, (ail.net.parser.LRParser.CoreItem)CoreItemTableAttr[0],
                    (ail.net.parser.GrammarSymbol)(LRModeAttr == ail.net.parser.LRParser.ELRMode.eLR0 ? null :
                        ail.net.parser.GrammarPool.Instance.Pool[(int)ail.net.parser.Token.EType.eEpsilon]));

            if(LRModeAttr == ail.net.parser.LRParser.ELRMode.eLR0)
            {
                StartStateAttr = Closure0(StartStateAttr);
            }
            else if(LRModeAttr == ail.net.parser.LRParser.ELRMode.eLR1)
            {
                StartStateAttr = Closure1(StartStateAttr);
            }
            
            StatesAttr.Add(StartStateAttr);

            bool process;

            for(;;)
            {
                process = false;

                ArrayList states = new ArrayList(StatesAttr);

                foreach(ail.net.parser.LRParser.State state in states)
                {
                    if((state.Flags & (uint)ail.net.parser.LRParser.EFlags.eMarked) != 0)
                    {
                        continue;
                    }

                    state.Flags |= (uint)ail.net.parser.LRParser.EFlags.eMarked;

                    foreach(ail.net.parser.GrammarSymbol symbol in ail.net.parser.GrammarPool.Instance.Pool.Values)
                    {
                        ail.net.parser.LRParser.State new_state = Goto(state, symbol);

                        if(new_state.Items.Count > 0)
                        {
                            ail.net.parser.LRParser.State existing_state = Contains(new_state, StatesAttr);
                            
                            if(existing_state != (object)null)
                            {
                                new_state = existing_state;
                            }
                            else
                            {
                                new_state.Id = StatesAttr.Count;
                                StatesAttr.Add(new_state);
                            }

                            // transition
                            ail.net.parser.LRParser.Transition transition = new ail.net.parser.LRParser.Transition();

                            transition.State  = new_state;
                            transition.Symbol = symbol;

                            state.Transitions.Add(symbol.Id, transition);

                            process = true;
                        }
                    }
                }

                if(!process)
                {
                    break;
                }
            }

            ResetMarkedStates();

            // set final sets
            foreach(ail.net.parser.LRParser.State state in StatesAttr)
            {
                foreach(ail.net.parser.LRParser.Item item in state.Items.Values)
                {
                    if(item.CoreItem.Dot == item.CoreItem.Rule.Rhs.Count)
                    {
                        // marked as final state
                        state.Flags |= (uint)ail.net.parser.LRParser.EFlags.eFinalState;
                        break;
                    }
                }
            }
        }

        protected void BuildCanonicalSet()
        {
            CanonicalSetAttr.Clear();

            ail.net.parser.LRParser.State start_set = new ail.net.parser.LRParser.State();

            AddItem(start_set, (ail.net.parser.LRParser.CoreItem)CoreItemTableAttr[0],
                    (ail.net.parser.GrammarSymbol)(LRModeAttr == ail.net.parser.LRParser.ELRMode.eLR0 ? null :
                        ail.net.parser.GrammarPool.Instance.Pool[(int)ail.net.parser.Token.EType.eEpsilon]));

            if(LRModeAttr == ail.net.parser.LRParser.ELRMode.eLR0)
            {
                start_set = Closure0(start_set);
            }
            else if(LRModeAttr == ail.net.parser.LRParser.ELRMode.eLR1)
            {
                start_set = Closure1(start_set);
            }

            CanonicalSetAttr.Add(start_set);

            bool process;

            for(;;)
            {
                process = false;

                ArrayList states = new ArrayList(CanonicalSetAttr);

                foreach(ail.net.parser.LRParser.State state in states)
                {
                    foreach(ail.net.parser.GrammarSymbol symbol in ail.net.parser.GrammarPool.Instance.Pool.Values)
                    {
                        ail.net.parser.LRParser.State new_state = Goto(state, symbol);

                        if(new_state.Items.Count > 0 && Contains(new_state, CanonicalSetAttr) == (object)null)
                        {
                            new_state.Id = CanonicalSetAttr.Count;

                            CanonicalSetAttr.Add(new_state);

                            System.Threading.Thread.Sleep(100); // yield

                            process = true;
                        }
                    }
                }

                if(!process)
                {
                    break;
                }
            }
        }

        protected void CheckConflicts()
        {
            if(LRModeAttr == ail.net.parser.LRParser.ELRMode.eLR0)
            {
                // LR(0) conflicts:
                //  (a) it contains two reduce items [N -> b(eta)1 *] and [M -> b(eta)2 *] - reduce/reduce
                //  (b) it contains reduce item [N -> b(eta)1 *] and a shift item [M -> b(eta)2 * x b(eta)2] - shift/reduce
                foreach(ail.net.parser.LRParser.State state in CanonicalSetAttr)
                {
                    // a
                    foreach(ail.net.parser.LRParser.Item anchor_item in state.Items.Values)
                    {
                        bool lhs_empty = anchor_item.CoreItem.Dot == anchor_item.CoreItem.Rule.Rhs.Count || anchor_item.CoreItem.Rule.IsEmptyRule();

                        if(lhs_empty)
                        {
                            foreach(ail.net.parser.LRParser.Item item in state.Items.Values)
                            {
                                if((object)item != (object)anchor_item)
                                {
                                    bool rhs_empty = item.CoreItem.Dot == item.CoreItem.Rule.Rhs.Count || item.CoreItem.Rule.IsEmptyRule();

                                    if(lhs_empty && rhs_empty)
                                    {
                                        // reduce/reduce
                                        string error = DecorateError(state, anchor_item, item, ail.net.parser.LRParser.ELRConflict.eReduceReduce);
                                        Errors.Add(error);
                                    }
                                }
                            }
                        }
                    }

                    // b
                    foreach(ail.net.parser.LRParser.Item anchor_item in state.Items.Values)
                    {
                        foreach(ail.net.parser.LRParser.Item item in state.Items.Values)
                        {
                            if((object)item != (object)anchor_item)
                            {
                                bool reduce = item.CoreItem.Dot == item.CoreItem.Rule.Rhs.Count               ||
                                              item.CoreItem.Rule.IsEmptyRule()                                ||
                                              anchor_item.CoreItem.Dot == anchor_item.CoreItem.Rule.Rhs.Count ||
                                              anchor_item.CoreItem.Rule.IsEmptyRule();

                                bool shift = (item.CoreItem.Dot < item.CoreItem.Rule.Rhs.Count && ((ail.net.parser.GrammarSymbol)item.CoreItem.Rule.Rhs[item.CoreItem.Dot]).IsTerminal()) ||
                                             (anchor_item.CoreItem.Dot < anchor_item.CoreItem.Rule.Rhs.Count && ((ail.net.parser.GrammarSymbol)anchor_item.CoreItem.Rule.Rhs[anchor_item.CoreItem.Dot]).IsTerminal());

                                if(shift && reduce)
                                {
                                    // shift/reduce
                                    string error = DecorateError(state, anchor_item, item, ail.net.parser.LRParser.ELRConflict.eShiftReduce);
                                    Errors.Add(error);
                                }
                            }
                        }
                    }
                }

                // LR(0) conflicts for SLR(1):
                //  (a) it contains two reduce items [N -> b(eta)1 *] and [M -> b(eta)2 *] such that the intersection
                //      of FOLLOW(N) and FOLLOW(M) is non-empty, or
                //  (b) it contains reduce item [N -> b(eta)1 *] and a shift item [M -> b(eta)2 * x b(eta)2] such that
                //      x belongs to FOLLOW(N)
            }
            else if(LRModeAttr == ail.net.parser.LRParser.ELRMode.eLR1)
            {
                // LR(1) conflicts:
                //  set of LR(1) items contains conflict if it contains a reduce item of the form
                //  [N -> b(eta)1 *, x] and either another reduce item of the form [M -> b(eta)2 *, x]
                //  or a shift item of the form [M -> a(lpha) * x b(eta)2, y]
                //  in other words,
                //  shift-reduce conflict – for any item [A -> a(lpha) * x b(eta), y] in a state with x a terminal,
                //  there is no item in a state of the from [B -> a(lpha) *, x]
                //  reduce-reduce conflict – there are no two items in a state of the form [A -> a(lpha) *, x]
                //  and [B -> b(eta), x]
                foreach(ail.net.parser.LRParser.State state in CanonicalSetAttr)
                {
                    foreach(ail.net.parser.LRParser.Item anchor_item in state.Items.Values)
                    {
                        ail.net.parser.GrammarSymbol a_terminal = // if == null means [N -> b(eta)1 *, x], otherwise [M -> a(lpha) * x b(eta)2, y]
                                anchor_item.CoreItem.Dot < anchor_item.CoreItem.Rule.Rhs.Count ? (ail.net.parser.GrammarSymbol)anchor_item.CoreItem.Rule.Rhs[anchor_item.CoreItem.Dot] : null;

                        // e(psilon) rule
                        if(anchor_item.CoreItem.Rule.IsEmptyRule())
                        {
                            a_terminal = null;
                        }

                        if(a_terminal == (object)null || a_terminal.IsTerminal())
                        {
                            foreach(ail.net.parser.LRParser.Item item in state.Items.Values)
                            {
                                if((object)item != (object)anchor_item)
                                {
                                    ail.net.parser.GrammarSymbol terminal =
                                        item.CoreItem.Dot < item.CoreItem.Rule.Rhs.Count ? (ail.net.parser.GrammarSymbol)item.CoreItem.Rule.Rhs[item.CoreItem.Dot] : null;

                                    // e(psilon) rule
                                    if(item.CoreItem.Rule.IsEmptyRule())
                                    {
                                        terminal = null;
                                    }

                                    if(a_terminal == (object)null && terminal == (object)null)
                                    {
                                        // [N -> b(eta)1 *, x] and [M -> b(eta)2 *, x]
                                        ail.net.framework.Assert.NonNullReference(item.Lookahead, "item.Lookahead");
                                        ail.net.framework.Assert.NonNullReference(anchor_item.Lookahead, "anchor_item.Lookahead");

                                        if(item.Lookahead.Id == anchor_item.Lookahead.Id)
                                        {
                                            // reduce/reduce conflict
                                            string error = DecorateError(state, anchor_item, item, ail.net.parser.LRParser.ELRConflict.eReduceReduce);
                                            Errors.Add(error);
                                        }
                                    }
                                    else if(a_terminal == (object)null && terminal != (object)null)
                                    {
                                        // [N -> b(eta)1 *, x] and [M -> a(lpha) * x b(eta)2, y]
                                        ail.net.framework.Assert.NonNullReference(anchor_item.Lookahead, "anchor_item.Lookahead");

                                        if(anchor_item.Lookahead.Id == terminal.Id)
                                        {
                                            // shift/reduce conflict
                                            string error = DecorateError(state, anchor_item, item, ail.net.parser.LRParser.ELRConflict.eShiftReduce);
                                            Errors.Add(error);
                                        }
                                    }
                                    else if(a_terminal != (object)null && terminal == (object)null)
                                    {
                                        // [M -> a(lpha) * x b(eta)2, y] and [N -> b(eta)1 *, x]
                                        ail.net.framework.Assert.NonNullReference(item.Lookahead, "item.Lookahead");

                                        if(a_terminal.Id == item.Lookahead.Id)
                                        {
                                            // shift/reduce conflict
                                            string error = DecorateError(state, anchor_item, item, ail.net.parser.LRParser.ELRConflict.eShiftReduce);
                                            Errors.Add(error);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        public bool IsLR1Grammar(out int xo_reduce_reduce_conflicts, out int xo_shift_reduce_conflicts)
        {
            // AU pp.442-443 (russian edition)
            bool result = false;

            // clean up
            xo_reduce_reduce_conflicts = xo_shift_reduce_conflicts = 0;

            Errors.Clear();

            // select sets with items with dot at the end
            ArrayList sets_to_check = new ArrayList();

            foreach(ail.net.parser.LRParser.State state in CanonicalSetAttr)
            {
                foreach(ail.net.parser.LRParser.Item item in state.Items.Values)
                {
                    if(item.CoreItem.Dot == item.CoreItem.Rule.Rhs.Count)
                    {
                        sets_to_check.Add(state);
                        break;
                    }
                }
            }

            Hashtable map = new Hashtable(); // checked items
            
            // iterate over selected sets
            foreach(ail.net.parser.LRParser.State state in sets_to_check)
            {
                map.Clear();

                foreach(ail.net.parser.LRParser.Item curr_item in state.Items.Values)
                {
                    bool is_completed = curr_item.CoreItem.Dot == curr_item.CoreItem.Rule.Rhs.Count;
                    
                    if(is_completed)
                    {
                        foreach(ail.net.parser.LRParser.Item item in state.Items.Values)
                        {
                            if((object)item != (object)curr_item) // check identity
                            {
                                if(map.ContainsKey(item))
                                {
                                    continue; // already checked
                                }

                                // [A -> b(eta)., u] and [B -> b(eta)1 . b(eta) 2, v], b(eta)2 can be empty
                                // u belongs EFFk (b(eta)2 v)
                                ail.net.parser.LRParser.ELRConflict conflict = // predpolagaemuy conflict
                                            item.CoreItem.Dot == item.CoreItem.Rule.Rhs.Count ?
                                                ail.net.parser.LRParser.ELRConflict.eReduceReduce :
                                                    ail.net.parser.LRParser.ELRConflict.eShiftReduce;

                                // u
                                ArrayList u = new ArrayList();
                                u.Add(curr_item.Lookahead.Id);

                                // EFFk (b(eta)2 v)
                                ArrayList t_eff = new ArrayList();

                                for(int i = item.CoreItem.Dot; i < item.CoreItem.Rule.Rhs.Count; i++)
                                {
                                    t_eff.Add(item.CoreItem.Rule.Rhs[i]);
                                }

                                t_eff.Add(item.Lookahead);

                                ArrayList eff = Grammar.BuildEFFirstKSet(t_eff, 1);

                                if(Grammar.HasEntry(eff, u))
                                {
                                    if(conflict == ail.net.parser.LRParser.ELRConflict.eReduceReduce)
                                    {
                                        xo_reduce_reduce_conflicts++;
                                    }
                                    else
                                    {
                                        xo_shift_reduce_conflicts++;
                                    }
                                    
                                    string error = DecorateError(state, curr_item, item, conflict);
                                    Errors.Add(error);
                                }

                                map[item] = 0; // marked as checked
                            }
                        }
                    }                    
                }
            }

            return result = Errors.Count == 0;
        }

        private ail.net.parser.LRParser.State Closure0(ail.net.parser.LRParser.State xi_state)
        {
            ail.net.framework.Assert.NonNullReference(xi_state, "xi_state");

            ail.net.parser.LRParser.State result = new ail.net.parser.LRParser.State();
            
            // initialize
            Array.Copy(PredictedNonTerminalsZeroizerAttr, PredictedNonTerminalsAttr, PredictedNonTerminalsZeroizerAttr.Length); // zero out

            // add all items from original state
            result.Items = new Hashtable(xi_state.Items);

            // add items as follows (similar to earley's predictor)
            bool changed;

            for(;;)
            {
                changed = false;

                Hashtable items = new Hashtable(result.Items);

                foreach(ail.net.parser.LRParser.Item item in items.Values)
                {
                    if(item.CoreItem.Dot < item.CoreItem.Rule.Rhs.Count) // dot inside rhs
                    {
                        ail.net.parser.GrammarSymbol symbol = (ail.net.parser.GrammarSymbol)item.CoreItem.Rule.Rhs[item.CoreItem.Dot]; // item.CoreItem.Dot is inside rhs.count

                        if(symbol.IsNonTerminal() && !PredictedNonTerminalsAttr[symbol.Id])
                        {
                            foreach(ail.net.parser.LRParser.CoreItem core_item in (ArrayList)PredictTableAttr[symbol.Id])
                            {
                                AddItem(result, core_item, null);
                            }

                            changed = true;

                            PredictedNonTerminalsAttr[symbol.Id] = true; // marked as predicted
                        }
                    }
                }

                if(!changed)
                {
                    break;
                }
            }

            // clean up
            Array.Copy(PredictedNonTerminalsZeroizerAttr, PredictedNonTerminalsAttr, PredictedNonTerminalsZeroizerAttr.Length); // zero out

            return result;
        }

        private ail.net.parser.LRParser.State Closure1(ail.net.parser.LRParser.State xi_state)
        {
            ail.net.framework.Assert.NonNullReference(xi_state, "xi_state");

            ail.net.parser.LRParser.State result = new ail.net.parser.LRParser.State();

            // add all items from original state
            result.Items = new Hashtable(xi_state.Items);

            // add items as follows (similar to earley's predictor)
            bool changed;

            for(;;)
            {
                changed = false;

                Hashtable items = new Hashtable(result.Items);

                foreach(ail.net.parser.LRParser.Item item in items.Values)
                {
                    if(item.CoreItem.Dot < item.CoreItem.Rule.Rhs.Count) // dot inside rhs
                    {
                        ail.net.parser.GrammarSymbol symbol = (ail.net.parser.GrammarSymbol)item.CoreItem.Rule.Rhs[item.CoreItem.Dot]; // item.CoreItem.Dot is inside rhs.count

                        if(symbol.IsNonTerminal()) // no optimization with PredictedNonTerminals
                                                   // because items can come in diff order with the same non-terminal
                        {
                            ArrayList first_set = new ArrayList(); // holds non-terminals and terminals
                            
                            for(int i = item.CoreItem.Dot+1; i < item.CoreItem.Rule.Rhs.Count; i++)
                            {
                                first_set.Add(item.CoreItem.Rule.Rhs[i]);
                            }

                            ail.net.framework.Assert.NonNullReference(item.Lookahead, "item.Lookahead");
                            first_set.Add(item.Lookahead);
#if FIRST_K1
                            first_set = Grammar.BuildFirstKSet(first_set); // but final first_set has only terminals
                            
                            foreach(ArrayList symbols in first_set)
                            {
                                int symbol_id = (int)symbols[0]; // first item as we have k=1

                                ail.net.parser.GrammarSymbol fs_symbol = (ail.net.parser.GrammarSymbol)ail.net.parser.GrammarPool.Instance.Pool[symbol_id];
                                ail.net.framework.Assert.NonNullReference(fs_symbol, "fs_symbol");

                                foreach(ail.net.parser.LRParser.CoreItem core_item in (ArrayList)PredictTableAttr[symbol.Id])
                                {
                                    if(!HasItem(result, core_item, fs_symbol))
                                    {
                                        changed = true;
                                        AddItem(result, core_item, fs_symbol);
                                    }
                                }
                            }
#else
                            first_set = Grammar.BuildFirstSet(first_set); // but final first_set has only terminals
                            
                            foreach(int symbol_id in first_set)
                            {
                                ail.net.parser.GrammarSymbol fs_symbol = (ail.net.parser.GrammarSymbol)ail.net.parser.GrammarPool.Instance.Pool[symbol_id];
                                ail.net.framework.Assert.NonNullReference(fs_symbol, "fs_symbol");

                                foreach(ail.net.parser.LRParser.CoreItem core_item in (ArrayList)PredictTableAttr[symbol.Id])
                                {
                                    if(!HasItem(result, core_item, fs_symbol))
                                    {
                                        changed = true;
                                        AddItem(result, core_item, fs_symbol);
                                    }
                                }
                            }
#endif
                        }
                    }
                }

                if(!changed)
                {
                    break;
                }
            }

            return result;
        }

        private ail.net.parser.LRParser.State Goto(ail.net.parser.LRParser.State xi_state, ail.net.parser.GrammarSymbol xi_symbol)
        {
            ail.net.framework.Assert.NonNullReference(xi_state, "xi_state");
            ail.net.framework.Assert.NonNullReference(xi_symbol, "xi_symbol");

            // add items as follows (similar to earley's scanner)
            ail.net.parser.LRParser.State result = new ail.net.parser.LRParser.State();

            foreach(ail.net.parser.LRParser.Item item in xi_state.Items.Values)
            {
                if(item.CoreItem.Dot < item.CoreItem.Rule.Rhs.Count) // dot inside rhs
                {
                    ail.net.parser.GrammarSymbol symbol = (ail.net.parser.GrammarSymbol)item.CoreItem.Rule.Rhs[item.CoreItem.Dot]; // item.CoreItem.Dot is inside rhs.count

                    if(symbol.Id == xi_symbol.Id)
                    {
                        AddItem(result, (ail.net.parser.LRParser.CoreItem)CoreItemTableAttr[item.CoreItem.Id+1], item.Lookahead);
                    }
                }
            }

            if(LRModeAttr == ail.net.parser.LRParser.ELRMode.eLR0)
            {
                result = Closure0(result);
            }
            else if(LRModeAttr == ail.net.parser.LRParser.ELRMode.eLR1)
            {
                result = Closure1(result);
            }

            return result;
        }

        private ail.net.parser.LRParser.State Contains(ail.net.parser.LRParser.State xi_state, ArrayList xi_states)
        {
            ail.net.framework.Assert.NonNullReference(xi_state, "xi_state");
            ail.net.framework.Assert.NonNullReference(xi_states, "xi_states");

            ail.net.parser.LRParser.State result = null;
            
            bool found = false;

            foreach(ail.net.parser.LRParser.State state in xi_states)
            {
                found = state.Items.Count == xi_state.Items.Count;

                if(found)
                {
                    foreach(ail.net.parser.LRParser.Item item in xi_state.Items.Values)
                    {
                        if(LRCompareModeAttr == ail.net.parser.LRParser.ELRCompareMode.eWithLookahead)
                        {
                            found = HasItem(state, item.CoreItem, item.Lookahead);
                        }
                        else
                        {
                            found = HasItem(state, item.CoreItem);
                        }
                    
                        if(!found)
                        {
                            break;
                        }
                    }
                }

                if(found)
                {
                    result = state;
                    break;
                }
            }

            return result;
        }

        private bool HasItem(ail.net.parser.LRParser.State xi_state, ail.net.parser.LRParser.CoreItem xi_core_item)
        {
            ail.net.framework.Assert.NonNullReference(xi_state, "xi_state");
            ail.net.framework.Assert.NonNullReference(xi_core_item, "xi_core_item");

            uint key = (uint)xi_core_item.Id;

            bool result = xi_state.Items.ContainsKey(key);

            return result;
        }

        private bool HasItem(ail.net.parser.LRParser.State xi_state, ail.net.parser.LRParser.CoreItem xi_core_item, ail.net.parser.GrammarSymbol xi_lookahead)
        {
            ail.net.framework.Assert.NonNullReference(xi_state, "xi_state");
            ail.net.framework.Assert.NonNullReference(xi_core_item, "xi_core_item");
            ail.net.framework.Assert.NonNullReference(xi_lookahead, "xi_lookahead");

            uint key = (uint)(((ushort)xi_core_item.Id << 16) | (ushort)xi_lookahead.Id);

            bool result = xi_state.Items.ContainsKey(key);

            return result;
        }

        private ail.net.parser.LRParser.Item AddItem(ail.net.parser.LRParser.State xi_state, ail.net.parser.LRParser.CoreItem xi_core_item, ail.net.parser.GrammarSymbol xi_lookahead)
        {
            ail.net.framework.Assert.NonNullReference(xi_state, "xi_state");
            ail.net.framework.Assert.NonNullReference(xi_core_item, "xi_core_item");

            ail.net.parser.LRParser.Item result = new ail.net.parser.LRParser.Item();
#if PRINT_STATS
            result.Id = xi_state.Items.Count;
#endif
            result.CoreItem  = xi_core_item;
            result.Lookahead = xi_lookahead;

            uint key = 0;

            if(xi_lookahead == (object)null)
            {
                key = (uint)xi_core_item.Id;
            }
            else
            {
                key = (uint)(((ushort)xi_core_item.Id << 16) | (ushort)xi_lookahead.Id);
            }

            xi_state.Items[key] = result;

            return result;
        }

        private void PopulateCoreItemTable()
        {
            // allocate
            CoreItemTableAttr = new ArrayList(Grammar.CalculateGrammarSize());

            // populate
            ail.net.parser.LRParser.CoreItem core_item = null;

            int index = 0;

            foreach(ail.net.parser.GrammarRule rule in Grammar.Rules)
            {
                int i = 0;

                // special case for empty rule, we always assume the dot is at the end
                if(rule.IsEmptyRule())
                {
                    core_item = new ail.net.parser.LRParser.CoreItem();

                    core_item.Id   = index++;
                    core_item.Rule = rule;
                    core_item.Dot  = rule.Rhs.Count;

                    CoreItemTableAttr.Add(core_item);
                }
                else
                {
                    for(; i < rule.Rhs.Count; i++)
                    {
                        core_item = new ail.net.parser.LRParser.CoreItem();

                        core_item.Id   = index++;
                        core_item.Rule = rule;
                        core_item.Dot  = i;

                        CoreItemTableAttr.Add(core_item);
                    }

                    // one extra for completed item
                    core_item = new ail.net.parser.LRParser.CoreItem();

                    core_item.Id   = index++;
                    core_item.Rule = rule;
                    core_item.Dot  = i;

                    CoreItemTableAttr.Add(core_item);
                }
            }
        }

        private void PopulatePredictTable()
        {
            ail.net.framework.Assert.Condition(Grammar.Rules.Count > 0, "ail.net.parser.LRParser.PopulatePredictTable: Grammar.Rules.Count > 0");

            PredictTableAttr = new Hashtable();

            foreach(ail.net.parser.GrammarSymbol symbol in GrammarPool.Instance.Pool.Values)
            {
                if(symbol.IsNonTerminal())
                {
                    ArrayList list = new ArrayList();
                    
                    PredictTableAttr[symbol.Id] = list;

                    for(int i = 0; i < CoreItemTableAttr.Count; i++)
                    {
                        ail.net.parser.GrammarRule rule = ((ail.net.parser.LRParser.CoreItem)CoreItemTableAttr[i]).Rule;

                        ail.net.parser.GrammarSymbol l_symbol = (ail.net.parser.GrammarSymbol)rule.Lhs[0];

                        if(l_symbol.Id == symbol.Id)
                        {
                            int dot = ((ail.net.parser.LRParser.CoreItem)CoreItemTableAttr[i]).Dot;

                            if(dot == 0 || rule.IsEmptyRule())
                            {
                                list.Add(CoreItemTableAttr[i]);
                            }
                        }
                    }
                }
            }

            PredictedNonTerminalsAttr = new bool[Lexer.Token.GetTokenSize()];
            PredictedNonTerminalsZeroizerAttr = new bool[Lexer.Token.GetTokenSize()];
        }

        private void ResetMarkedStates()
        {
            foreach(ail.net.parser.LRParser.State state in StatesAttr)
            {
                state.Flags &= ~(uint)ail.net.parser.LRParser.EFlags.eMarked;
            }
        }

        private ail.net.parser.Token NextLexeme()
        {
            ail.net.parser.Token result = null;

            if(LexerMode == ail.net.parser.LRParser.ELexerMode.eIgnoreWhitespace)
            {
                // skip whitespace
                do
                {
                    Lexer.NextLexeme();
                }
                while(Lexer.Token.Type == (int)ail.net.parser.Token.EType.eWhiteSpace);
            }
            else
            {
                Lexer.NextLexeme();
            }
            
            result = Lexer.Token;

            return result;
        }

        public bool LoadLR1Automaton(string xi_file)
        {
            ail.net.framework.Assert.NonNullReference(xi_file, "xi_file");

            StatesAttr.Clear();
            
            bool result = true;
            
            try
            {
                StreamReader reader = new StreamReader(xi_file);
                StringBuilder builder = new StringBuilder();

                // read in states
                Hashtable states = new Hashtable();

                for(;;)
                {
                    string line = reader.ReadLine();
                    
                    if(line == null)
                    {
                        break;
                    }

                    string [] state_data = line.Split(':');

                    // state
                    ail.net.parser.LRParser.State state = new ail.net.parser.LRParser.State();

                    state.Id = Convert.ToInt32(state_data[0].Substring(0, state_data[0].IndexOf('.')));
                    state.Flags |= (state_data[0].IndexOf('F') > 0) ? (uint)ail.net.parser.LRParser.EFlags.eFinalState : 0;

                    StatesAttr.Add(state);
                    states.Add(state.Id, state);
                }

                // add transitions
                reader.BaseStream.Position = 0;
                
                for(;;)
                {
                    string line = reader.ReadLine();
                    
                    if(line == null)
                    {
                        break;
                    }

                    string [] state_data = line.Split(':');

                    // state
                    int state_id = Convert.ToInt32(state_data[0].Substring(0, state_data[0].IndexOf('.')));
                    ail.net.parser.LRParser.State state = (ail.net.parser.LRParser.State)states[state_id];

                    // transitions
                    for(int i = 1; i < state_data.Length; i++)
                    {
                        string [] symbol_state = state_data[i].Split('.');

                        ail.net.parser.LRParser.Transition transition = new ail.net.parser.LRParser.Transition();

                        transition.Symbol = (ail.net.parser.GrammarSymbol)ail.net.parser.GrammarPool.Instance.Pool[(int)Convert.ToInt32(symbol_state[0])];
                        transition.State  = (ail.net.parser.LRParser.State)states[(int)Convert.ToInt32(symbol_state[1])];

                        state.Transitions.Add(transition.Symbol.Id, transition);
                    }
                }                    

                reader.Close();
            }
            catch(IOException)
            {
                result = false;
            }
            catch
            {
                result = false;
            }

            return result;
        }

        public bool SaveLR1Automaton(string xi_file)
        {
            ail.net.framework.Assert.NonNullReference(xi_file, "xi_file");
            
            bool result = true;
            
            try
            {
                StreamWriter writer = new StreamWriter(xi_file);
                StringBuilder builder = new StringBuilder();

                foreach(ail.net.parser.LRParser.State state in StatesAttr)
                {
                    builder.Length = 0;

                    builder.Append(state.Id.ToString());
                    builder.Append("."+(((state.Flags & (uint)ail.net.parser.LRParser.EFlags.eFinalState) != 0) ? 'F' : 'N'));

                    if(state.Transitions.Count > 0)
                    {
                        foreach(ail.net.parser.LRParser.Transition transition in state.Transitions.Values)
                        {
                            builder.Append(":"+transition.Symbol.Id.ToString()+"."+transition.State.Id.ToString());
                        }
                    }

                    writer.Write(builder.ToString());
                    writer.WriteLine();
                }

                writer.Flush();
                writer.Close();
            }
            catch(IOException)
            {
                result = false;
            }
            catch
            {
                result = false;
            }

            return result;
        }

        public bool LoadLR1ActionTable(string xi_file)
        {
            ail.net.framework.Assert.NonNullReference(xi_file, "xi_file");
            
            ActionTableAttr.Clear();

            bool result = true;
            
            try
            {
                StreamReader reader = new StreamReader(xi_file);
                StringBuilder builder = new StringBuilder();

                string line = reader.ReadToEnd();

                reader.Close();

                if(line != null)
                {
                    string [] table = line.Split(':');

                    for(int i = 0; i < table.Length; i++)
                    {
                        string [] kv = table[i].Split('.'); // must be 3 - TableKey+Value
                        
                        int key_symbol = Convert.ToInt32(kv[0]);
                        int key_state  = Convert.ToInt32(kv[1]);

                        Hashtable entries = new Hashtable();
                        
                        for(int k = 2; k < kv.Length; k++)
                        {
                            int value_entry = Convert.ToInt32(kv[k]);
                            entries[value_entry] = value_entry; // duplicated entries will be caugth and loading will be terminated
                        }

                        ail.net.parser.LRParser.TableKey key = new TableKey(key_symbol, key_state);

                        ActionTableAttr[key] = entries;
                    }
                }
            }
            catch(IOException)
            {
                result = false;
            }
            catch
            {
                result = false;
            }

            return result;
        }

        public bool SaveLR1ActionTable(string xi_file)
        {
            ail.net.framework.Assert.NonNullReference(xi_file, "xi_file");
            
            bool result = true;
            
            try
            {
                StreamWriter writer = new StreamWriter(xi_file);
                StringBuilder builder = new StringBuilder();

                IDictionaryEnumerator it = ActionTableAttr.GetEnumerator();

                while(it.MoveNext())
                {
                    ail.net.parser.LRParser.TableKey key = (ail.net.parser.LRParser.TableKey)it.Key;

                    builder.Append(key.Id.ToString()+'.'+key.State.ToString());

                    Hashtable entries = (Hashtable)it.Value;
                    
                    foreach(int value in entries.Values)
                    {
                        builder.Append('.'+value.ToString());
                    }

                    builder.Append(":");
                }

                string table = builder.ToString();
                table = table.Substring(0, table.Length-1);

                writer.Write(table);
                writer.Flush();
                writer.Close();
            }
            catch(IOException)
            {
                result = false;
            }
            catch
            {
                result = false;
            }

            return result;
        }

        public bool LoadLR1GoToTable(string xi_file)
        {
            ail.net.framework.Assert.NonNullReference(xi_file, "xi_file");
            
            GoToTableAttr.Clear();

            bool result = true;
            
            try
            {
                StreamReader reader = new StreamReader(xi_file);
                StringBuilder builder = new StringBuilder();

                string line = reader.ReadToEnd();

                reader.Close();

                if(line != null)
                {
                    string [] table = line.Split(':');

                    for(int i = 0; i < table.Length; i++)
                    {
                        string [] kv = table[i].Split('.'); // must be 3 - TableKey+Value
                        
                        int key_symbol_id  = Convert.ToInt32(kv[0]);
                        int key_state_id   = Convert.ToInt32(kv[1]);
                        int value_entry_id = Convert.ToInt32(kv[2]);

                        ail.net.parser.LRParser.TableKey key = new TableKey(key_symbol_id, key_state_id);

                        GoToTableAttr.Add(key, value_entry_id); // duplicated entries will be caugth and loading will be terminated
                    }
                }
            }
            catch(IOException)
            {
                result = false;
            }
            catch
            {
                result = false;
            }

            return result;
        }

        public bool SaveLR1GoToTable(string xi_file)
        {
            ail.net.framework.Assert.NonNullReference(xi_file, "xi_file");
            
            bool result = true;
            
            try
            {
                StreamWriter writer = new StreamWriter(xi_file);
                StringBuilder builder = new StringBuilder();

                IDictionaryEnumerator it = GoToTableAttr.GetEnumerator();

                while(it.MoveNext())
                {
                    ail.net.parser.LRParser.TableKey key = (ail.net.parser.LRParser.TableKey)it.Key;

                    int value = (int)it.Value;                

                    builder.Append(key.Id.ToString()+'.'+key.State.ToString()+'.'+value.ToString()+":");
                }

                string table = builder.ToString();
                table = table.Substring(0, table.Length-1);

                writer.Write(table);
                writer.Flush();
                writer.Close();
            }
            catch(IOException)
            {
                result = false;
            }
            catch
            {
                result = false;
            }

            return result;
        }

        private string DecorateItem(ail.net.parser.LRParser.Item xi_item)
        {
            ail.net.framework.Assert.NonNullReference(xi_item, "xi_item");

            StringBuilder result = new StringBuilder();
#if PRINT_STATS
            result.Append(xi_item.Id+"  ");
#endif
            foreach(ail.net.parser.GrammarSymbol symbol in xi_item.CoreItem.Rule.Lhs)
            {
                result.Append(symbol.Name+" ");
            }

            result.Append("->");

            int i = 0;

            foreach(ail.net.parser.GrammarSymbol symbol in xi_item.CoreItem.Rule.Rhs)
            {
                if(i++ == xi_item.CoreItem.Dot)
                {
                    result.Append(" .");
                }

                if(symbol.Id != (int)ail.net.parser.Token.EType.eEpsilon)
                {
                    result.Append(" "+symbol.Name);
                }
            }

            if(xi_item.CoreItem.Dot == xi_item.CoreItem.Rule.Rhs.Count) // dot at the end
            {
                result.Append(" .");
            }

            result.Append(", ");

            if(xi_item.Lookahead != (object)null)
            {
                result.Append(xi_item.Lookahead.Name);
            }
            else
            {
                result.Append("null");
            }

            return result.ToString();
        }

        private string DecorateState(ail.net.parser.LRParser.State xi_state)
        {
            ail.net.framework.Assert.NonNullReference(xi_state, "xi_state");

            StringBuilder result = new StringBuilder();

            ArrayList items = new ArrayList(xi_state.Items.Values);
            
            items.Sort(new ail.net.parser.LRParser.ItemComparer());
            
            foreach(ail.net.parser.LRParser.Item item in items)
            {
                result.Append("\t\t");
                result.Append(DecorateItem(item));
                result.Append(Environment.NewLine);
            }

            if(xi_state.Transitions.Count > 0)
            {
                result.Append("\t\t.............");
                result.Append(Environment.NewLine);
                result.Append("\t\t");

                foreach(ail.net.parser.LRParser.Transition transition in xi_state.Transitions.Values)
                {
                    result.Append(transition.State.Id);
                    result.Append(" : ");
                    
                    if(transition.Symbol.IsTerminal())
                    {
                        result.Append("'");
                    }

                    result.Append(transition.Symbol.Name);

                    if(transition.Symbol.IsTerminal())
                    {
                        result.Append("'");
                    }

                    result.Append("   ");
                }
            }

            return result.ToString();
        }

        public string DecorateStates()
        {
            StringBuilder result = new StringBuilder();

            ArrayList states = new ArrayList(StatesAttr);
            
            states.Sort(new ail.net.parser.LRParser.StateComparer());

            foreach(ail.net.parser.LRParser.State state in states)
            {
                result.Append("State["+state.Id+"]");

                if((state.Flags & (uint)ail.net.parser.LRParser.EFlags.eReduce) != 0)
                {
                    result.Append(" [reduce]");
                }
                
                if((state.Flags & (uint)ail.net.parser.LRParser.EFlags.eAccepted) != 0)
                {
                    result.Append(" [accepted]");
                }

                if((state.Flags & (uint)ail.net.parser.LRParser.EFlags.eFinalState) != 0)
                {
                    result.Append(" [final]");
                }

                result.Append(Environment.NewLine);
                result.Append(DecorateState(state));
                result.Append(Environment.NewLine);
                result.Append(Environment.NewLine);
            }

            return result.ToString();
        }

        public string DecorateStates(ArrayList xi_states)
        {
            ail.net.framework.Assert.NonNullReference(xi_states, "xi_states");

            StringBuilder result = new StringBuilder();

            ArrayList states = new ArrayList(xi_states);
            
            states.Sort(new ail.net.parser.LRParser.StateComparer());

            foreach(ail.net.parser.LRParser.State state in states)
            {
                result.Append("State["+state.Id+"]");
                result.Append(Environment.NewLine);
                result.Append(DecorateState(state));
                result.Append(Environment.NewLine);
                result.Append(Environment.NewLine);
            }

            return result.ToString();
        }

        private string DecorateError(ail.net.parser.LRParser.State xi_state,
                                     ail.net.parser.LRParser.Item xi_item1,
                                     ail.net.parser.LRParser.Item xi_item2,
                                     ail.net.parser.LRParser.ELRConflict xi_conflict_type)
        {
            ail.net.framework.Assert.NonNullReference(xi_state, "xi_state");
            ail.net.framework.Assert.NonNullReference(xi_item1, "xi_item1");
            ail.net.framework.Assert.NonNullReference(xi_item2, "xi_item2");

            StringBuilder result = new StringBuilder();
            
            result.Append("LRParser: ");

            if(xi_conflict_type == ail.net.parser.LRParser.ELRConflict.eShiftReduce)
            {
                result.Append("shift/reduce conflict ");
            }
            else if(xi_conflict_type == ail.net.parser.LRParser.ELRConflict.eReduceReduce)
            {
                result.Append("reduce/reduce conflict ");
            }

            result.Append("["+DecorateItem(xi_item1)+"] and ["+DecorateItem(xi_item2)+"] ");
            result.Append("state: "+xi_state.Id);

            return result.ToString();
        }

        public string DecorateTables()
        {
            StringBuilder result = new StringBuilder();
            
            result.Append(Environment.NewLine);
            result.Append(Environment.NewLine);
            result.Append("State  Action");
            result.Append(new string(' ', ail.net.parser.GrammarPool.Instance.TerminalCount*5));
            result.Append("GoTo");
            result.Append(new string(' ', ail.net.parser.GrammarPool.Instance.NonTerminalCount*5));
            result.Append(Environment.NewLine);
            result.Append(Environment.NewLine);
            
            result.Append("     ");

            ArrayList sym_array = new ArrayList(ail.net.parser.GrammarPool.Instance.Pool.Values);
            sym_array.Sort(new ail.net.parser.GrammarSymbol.SymbolNameComparer());

            foreach(ail.net.parser.GrammarSymbol symbol in sym_array)
            {
                if(symbol.IsTerminal())
                {
                    result.Append("  "+symbol.Name+"  ");
                }
            }

            result.Append("   ");

            foreach(ail.net.parser.GrammarSymbol symbol in sym_array)
            {
                if(symbol.IsNonTerminal())
                {
                    result.Append("  "+symbol.Name+"  ");
                }
            }

            result.Append(Environment.NewLine);
            result.Append(Environment.NewLine);

            for(int i = 0; i < StatesAttr.Count; i++)
            {
                result.Append(" "+i.ToString()+"    ");

                foreach(ail.net.parser.GrammarSymbol symbol in sym_array)
                {
                    if(symbol.IsTerminal())
                    {
                        ail.net.parser.LRParser.TableKey key = new TableKey(symbol.Id, i);
                        
                        if(ActionTableAttr.Contains(key))
                        {
                            uint e = (uint)ActionTableAttr[key];
                            
                            if(e == kAcceptCode)
                            {
                                // accept
                                result.Append(" acc ");
                            }
                            else if((e & (uint)ail.net.parser.LRParser.EFlags.eMarked) == 0)
                            {
                                // reduce
                                result.Append(" r"+e.ToString()+"  ");
                            }
                            else if((e & (uint)ail.net.parser.LRParser.EFlags.eMarked) != 0)
                            {
                                // shift
                                e = ((uint)e & ~(uint)ail.net.parser.LRParser.EFlags.eMarked);
                                result.Append(" s"+e.ToString()+"  ");
                            }
                        }
                        else
                        {
                            result.Append("     ");
                        }
                    }
                }

                result.Append("    ");

                foreach(ail.net.parser.GrammarSymbol symbol in sym_array)
                {
                    if(symbol.IsNonTerminal())
                    {
                        ail.net.parser.LRParser.TableKey key = new TableKey(symbol.Id, i);
                        
                        if(GoToTableAttr.Contains(key))
                        {
                            int e = (int)GoToTableAttr[key];
                            result.Append("  "+e.ToString()+"  ");
                        }
                        else
                        {
                            result.Append("     ");
                        }
                    }
                }

                result.Append(Environment.NewLine);
            }

            result.Append(Environment.NewLine);
            
            return result.ToString();
        }

        public string DecorateK1Tables()
        {
            StringBuilder result = new StringBuilder();
            
            result.Append(Environment.NewLine);
            result.Append(Environment.NewLine);
            result.Append("State  Action");
            result.Append(new string(' ', ail.net.parser.GrammarPool.Instance.TerminalCount*5));
            result.Append("GoTo");
            result.Append(new string(' ', ail.net.parser.GrammarPool.Instance.NonTerminalCount*5));
            result.Append(Environment.NewLine);
            result.Append(Environment.NewLine);
            
            result.Append("     ");

            ArrayList sym_array = new ArrayList(ail.net.parser.GrammarPool.Instance.Pool.Values);
            sym_array.Sort(new ail.net.parser.GrammarSymbol.SymbolNameComparer());

            foreach(ail.net.parser.GrammarSymbol symbol in sym_array)
            {
                if(symbol.IsTerminal())
                {
                    result.Append("  "+symbol.Name+"  ");
                }
            }

            result.Append("   ");

            foreach(ail.net.parser.GrammarSymbol symbol in sym_array)
            {
                result.Append("  "+symbol.Name+"  ");
            }

            result.Append(Environment.NewLine);
            result.Append(Environment.NewLine);

            for(int i = 0; i < StatesAttr.Count; i++)
            {
                result.Append(" "+i.ToString()+"    ");

                foreach(ail.net.parser.GrammarSymbol symbol in sym_array)
                {
                    if(symbol.IsTerminal())
                    {
                        ail.net.parser.LRParser.TableKey key = new TableKey(symbol.Id, i);
                        
                        Hashtable action_table_entry = (Hashtable)ActionTableAttr[key];
                        
                        if(action_table_entry != null)
                        {
                            ArrayList list = new ArrayList(action_table_entry.Values);

                            for(int k = 0; k < action_table_entry.Count; k++)
                            {
                                int e = (int)list[k];

                                if(e < 0)
                                {
                                    if(Math.Abs(e) == kAcceptedCode)
                                    {
                                        // accept
                                        result.Append(" acc ");
                                    }
                                    else
                                    {
                                        // reduce
                                        result.Append(" r"+Math.Abs(e).ToString()+"  ");
                                    }
                                }
                                else if(e >= 0)
                                {
                                    // shift
                                    result.Append(" s"+e.ToString()+"  ");
                                }

                                if(k < action_table_entry.Count-1)
                                {
                                    result.Append('/');
                                }
                            }
                        }
                        else
                        {
                            result.Append("     ");
                        }
                    }
                }

                result.Append("    ");

                foreach(ail.net.parser.GrammarSymbol symbol in sym_array)
                {
                    ail.net.parser.LRParser.TableKey key = new TableKey(symbol.Id, i);
                    
                    if(GoToTableAttr.Contains(key))
                    {
                        int e = (int)GoToTableAttr[key];
                        result.Append("   "+e.ToString()+"  ");
                    }
                    else
                    {
                        result.Append("      ");
                    }
                }

                result.Append(Environment.NewLine);
            }

            result.Append(Environment.NewLine);
            
            return result.ToString();
        }
        #endregion // methods
    }
}

#region epilog
#endregion
