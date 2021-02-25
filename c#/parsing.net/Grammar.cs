//......................................................................................
// This is a part of UI Soft Library. Copyright © 1989-2006 UI Soft Inc.               .
//......................................................................................
// THIS CODE MAY BE USED, COPIED, STORED, OR DISTRIBUTED ONLY IN ACCORDANCE WITH       .
// A WRITTEN LICENSE AGREEMENT AND WITH THE INCLUSION OF THIS COPYRIGHT NOTICE.        .
//......................................................................................

#region prolog
// file       : 
// description: Grammar
// package    : ail.net.parser
//
#endregion

#region import
using System;
using System.Collections;
using System.IO;
using System.Text;
#endregion

namespace ail.net.parser
{
    /// <summary>
    /// summary description for Grammar
    /// </summary>
    public abstract class Grammar : IDisposable
    {
        #region constants
        #endregion // constants

        #region data members
        private int                         StartSymbolIdAttr;
        private ail.net.parser.GrammarRule  StartRuleAttr;
        private ArrayList                   RulesAttr  = new ArrayList();
        private Hashtable                   RulesMapAttr = new Hashtable();
        #endregion // data members

        #region ctor/dtor/finalizer
        public Grammar()
        {
        }

        ~Grammar()
        {
            Dispose(false);
        }
        #endregion ctor/dtor/finalizer

        #region properties
        public int StartSymbolId
        {
            get
            {
                return StartSymbolIdAttr;
            }

            set
            {
                StartSymbolIdAttr = value;
            }
        }

        public ail.net.parser.GrammarRule StartRule
        {
            get
            {
                return StartRuleAttr;
            }

            set
            {
                StartRuleAttr = value;
            }
        }

        public ArrayList Rules
        {
            get
            {
                return RulesAttr;
            }
        }

        public Hashtable RulesMap
        {
            get
            {
                return RulesMapAttr;
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
                RulesAttr = null;
            }

            // free unmanaged objects, including base class
            // set large fields to null (de-reference)
        }

        public virtual void Populate()
        {
            GrammarPool.Instance.Pool.Clear();
            GrammarPool.Instance.AddSymbol((int)ail.net.parser.Token.EType.eEndOfStream, ail.net.parser.GrammarSymbol.EType.eTerminal, ail.net.parser.GrammarSymbol.kEndOfStream);
        }

        public ail.net.parser.GrammarRule AddRule(int xi_id)
        {
            ail.net.parser.GrammarRule result = null;

            if(!RulesAttr.Contains(xi_id))
            {
                result = new ail.net.parser.GrammarRule(xi_id);

                RulesAttr.Add(result);

                if(StartRuleAttr == null)
                {
                    StartRuleAttr = result;
                }
            }

            ail.net.framework.Assert.NonNullReference(result, "result");
            return result;
        }

        public void RemoveRule(ail.net.parser.GrammarRule xi_rule)
        {
            ail.net.framework.Assert.NonNullReference(xi_rule, "xi_rule");
            ail.net.framework.Assert.Condition(RulesAttr.Contains(xi_rule.Id), "Rules.Contains(xi_rule.Id)");
            RulesAttr.Remove(xi_rule.Id);
        }

        public int GetMaxRhsSize()
        {
            int result = 0;

            foreach(ail.net.parser.GrammarRule rule in RulesAttr) 
            {
                if(result < rule.RhsNonTerminalCount+rule.RhsTerminalCount)
                {
                    result = rule.RhsNonTerminalCount+rule.RhsTerminalCount;
                }
            }

            return result;
        }

        public int CalculateGrammarSize()
        {
            // calculate grammar size, which is
            // sum of all (|a(lpha)|+1) for all A -> a(lpha), which are belonged to grammar G
            int result = 0;

            foreach(ail.net.parser.GrammarRule rule in RulesAttr)
            {
                result += rule.RhsNonTerminalCount+rule.RhsTerminalCount+1;
            }

            ail.net.framework.Assert.Condition(result > 0, "Grammar.CalculateGrammarSize: result > 0");
            return result;            
        }

        public abstract bool IsCycleFree();
        
        public void BuildNullabilitySet()
        {
            // The set of nullable non-terminals can be computed by the following algorithm:
            //  (a) Set "nullable" equal to the set of non-terminals appearing on the left side
            //      of productions of the form N -> e
            //  (b) Until doing so adds no new non-terminals to "nullable", examine each production
            //      in the grammar adding to "nullable" all left-hand-sides of productions whose
            //      right-hand-side consist entirely of symbols in "nullable"
            // a
            foreach(ail.net.parser.GrammarRule rule in RulesAttr)
            {
                if(rule.IsEmptyRule())
                {
                    ((ail.net.parser.GrammarSymbol)rule.Lhs[0]).Nullable = true;
                }
            }

            // b
            for(;;)
            {
                bool changed = false;

                foreach(ail.net.parser.GrammarRule rule in RulesAttr)
                {
                    ail.net.parser.GrammarSymbol l_symbol = (ail.net.parser.GrammarSymbol)rule.Lhs[0];

                    if(!l_symbol.Nullable)
                    {
                        bool nullable = true;

                        foreach(ail.net.parser.GrammarSymbol rhs_symbol in rule.Rhs)
                        {
                            if(!rhs_symbol.Nullable)
                            {
                                nullable = false;
                                break;
                            }
                        }

                        if(nullable)
                        {
                            l_symbol.Nullable = true;
                            changed = true;
                        }
                    }
                }

                if(!changed)
                {
                    break;
                }
            }
        }

        public void BuildFirstSet()
        {
            // Set First(x) equal to {x} for all terminals.
            // Set First(x) to {e} for all nullable non-terminals and to {} for all other non-terminals.
            foreach(ail.net.parser.GrammarSymbol symbol in ail.net.parser.GrammarPool.Instance.Pool.Values)
            {
                if(symbol.IsTerminal())
                {
                    symbol.FirstSet.Add(symbol.Id);
                }
                else
                {
                    if(symbol.Nullable)
                    {
                        symbol.FirstSet.Add((int)ail.net.parser.Token.EType.eEpsilon);
                    }
                }
            }

            // Repeat the following process until no further changes occur:
            //  For each production
            //  N -> x1 x2 ... xk
            //    (a) Add (First(x1)-{e}) to First(N)
            //    (b) If e belongs to First(x1) then add (First(x1)-{e}) to First(N)
            //    (c) If e belongs to First(x1) and e belongs to First(x2) then also add (First(x2)-{e})
            //        to First(N)
            //    (d) If e belongs to First(x1) and e belongs to First(x2) and e belongs to First(x3)
            //        then also add (First(x3)-{e}) to First(N)
            //    (e) Continue in the same manner for x4, ... , xk
            //
            // either:
            //     repeat
            //         for each production X -> Y1Y2 ... Yn do
            //             if Y1 not nullable then
            //                 add FIRST(Y1) to FIRST(X)
            //             else if Y1 ... Yi-1 are all nullable (or if i = n) then
            //                 add FIRST(Y1) U ... U FIRST(Yi) to FIRST(X)
            //             end if
            //         end for
            //     until FIRST not changed in this iteration
            for(;;)
            {
                bool changed = false;

                foreach(ail.net.parser.GrammarRule rule in RulesAttr)
                {
                    ail.net.parser.GrammarSymbol non_terminal = (ail.net.parser.GrammarSymbol)rule.Lhs[0];

                    int count = non_terminal.FirstSet.Count;

                    foreach(ail.net.parser.GrammarSymbol r_symbol in rule.Rhs)
                    {
                        bool has_epsilon = false;

                        for(int i = 0, n = r_symbol.FirstSet.Count; i < n; i++)
                        {
                            int r_symbol_id = (int)r_symbol.FirstSet[i];

                            if(r_symbol_id != (int)ail.net.parser.Token.EType.eEpsilon)
                            {
                                if(!non_terminal.FirstSet.Contains(r_symbol_id))
                                {
                                    non_terminal.FirstSet.Add(r_symbol_id);
                                }
                            }
                            else
                            {
                                has_epsilon = true; // should be only one
                            }
                        }

                        if(!has_epsilon)
                        {
                            break;
                        }
                    }

                    changed = changed ? changed : count != non_terminal.FirstSet.Count;
                }

                if(!changed)
                {
                    break;
                }
            }
        }

        public ArrayList BuildFirstSet(ArrayList xi_symbols)
        {
            ail.net.framework.Assert.NonNullReference(xi_symbols, "xi_symbols");

            ArrayList result = new ArrayList();

            // To compute First(a(lpha)) for a string a(lpha) = x1 x2 ... xk, use the following algorithm:
            //  (a) Set First(a(lpha)) = First(x1)-{e}
            //  (b) If e belongs to First(x1), add (First(x2)-{e}) to First(a(lpha))
            //  (c) If e belongs to First(x1) and e belongs to First(x2), then add (First(x3)-{e}) to First(a(lpha))
            //  (d) Continue in the same manner for x3, x4, ... , xk
            //  (e) Finally, if e belongs to First(xi) for all i = 1 ... k, add e to First(a(lpha))
            foreach(ail.net.parser.GrammarSymbol symbol in xi_symbols)
            {
                bool has_epsilon = false;

                for(int i = 0, n = symbol.FirstSet.Count; i < n; i++)
                {
                    int symbol_id = (int)symbol.FirstSet[i];

                    if(symbol_id != (int)ail.net.parser.Token.EType.eEpsilon)
                    {
                        if(!result.Contains(symbol_id))
                        {
                            result.Add(symbol_id);
                        }
                    }
                    else
                    {
                        has_epsilon = true; // should be only one
                    }
                }

                if(!has_epsilon)
                {
                    break;
                }
            }

            bool nullable = true;

            foreach(ail.net.parser.GrammarSymbol symbol in xi_symbols)
            {
                if(symbol.Id != (int)ail.net.parser.Token.EType.eEpsilon)
                {
                    if(!symbol.Nullable)
                    {
                        nullable = false;
                        break;
                    }
                }
            }

            if(nullable)
            {
                result.Add(ail.net.parser.Token.EType.eEpsilon);
            }

            return result;
        }

        public void BuildFirstKSet(int xi_k)
        {
            // builds FIRSTk and EFFk sets for the given grammar
            // Sudkump p. 498
            //  1. for each a belongs to T do F'(a) = {a}
            //  2. for each A belongs to N do F(A) = {e(psilon)} if A is nullable or empty otherwise
            //  3. repeat
            //      3.1 for each A belongs to N do F'(A) = F(A)
            //      3.2 for each rule A -> w = u1u2...un with n > 0 do
            //              F(A) = F(A) U TRUNKk(F'(u1)F'(u2)...F'(un))
            //          until F(A) = F'(A) for all A belongs to N
            //  4. FIRSTk(A) = F(A)
            // FIRST set is list of lists for every non-terminal in grammar, size of "lists" is K
            //    ( )
            //     | \
            //     |   --- 
            //     |      |
            // (0,1..K) (0,1..K)
            //
            // Opredelim mnozhestvo EFFk(x), sostoyashee iz vseh elementov mnozhestva FIRSTk(x),
            // pri vivode kotorih neterminal na levom konce x (esli on est') ne zamenyaetsya na pustuu zepochku
            //
            // The epsilon-free first k derived symbols, EFFk(), are found by computing FIRST as above,
            // but tagging all symbols which are derived using epsilon productions of the form,
            // as non-epsilon free, and keeping only the epsilon-free derived terminals. 
            //?? ail.net.framework.Assert.Condition(xi_k > 0, "ail.net.parser.Grammar.BuildFirstSet: xi_k > 0");

            // 1. for each a belongs to T do F'(a) = {a}
            // 2. for each A belongs to N do F(A) = {e(psilon)} if A is nullable or empty otherwise
            foreach(ail.net.parser.GrammarSymbol symbol in ail.net.parser.GrammarPool.Instance.Pool.Values)
            {
                if(symbol.IsTerminal())
                {
                    ArrayList e = new ArrayList();
                    e.Add(symbol.Id);
                    symbol.FirstSet.Add(e);

                    e = new ArrayList();
                    e.Add(symbol.Id);
                    symbol.EFFirstSet.Add(e);
                }
                else
                {
                    if(symbol.Nullable)
                    {
                        ArrayList e = new ArrayList();
                        e.Add((int)ail.net.parser.Token.EType.eEpsilon);
                        symbol.FirstSet.Add(e);
                    }
                }
            }

            // 3. repeat
            for(;;)
            {
                bool changed = false; // fixed point

                foreach(ail.net.parser.GrammarRule rule in Rules)
                {
                    // non-terminal work with
                    ail.net.parser.GrammarSymbol non_terminal = (ail.net.parser.GrammarSymbol)rule.Lhs[0];

                    int count = non_terminal.FirstSet.Count;

                    // check if we have any empty sets
                    bool has_empty_sets = false;
                    
                    foreach(ail.net.parser.GrammarSymbol symbol in rule.Rhs)
                    {
                        if(symbol.FirstSet.Count == 0)
                        {
                            has_empty_sets = true;
                            break;
                        }
                    }

                    if(has_empty_sets)
                    {
                        // concatanation of the empty set with any set yields the empty set
                        continue;
                    }

                    // 3.2 for each rule A -> w = u1u2...un with n > 0 do
                    //          F(A) = F(A) U TRUNKk(F'(u1)F'(u2)...F'(un))
                    //     until F(A) = F'(A) for all A belongs to N
                    ArrayList entry = new ArrayList();
                    ArrayList eff_entry = new ArrayList();

                    for(int i = rule.Rhs.Count-1; i >= 0; i--) // as operator (+) is associative
                    {                                          // it can be applied from back to the front
                        // (+) ... (+)
                        entry = OperatorInfixK(((ail.net.parser.GrammarSymbol)rule.Rhs[i]).FirstSet, entry, xi_k);

                        if(!rule.IsEmptyRule())
                        {
                            eff_entry = OperatorInfixK(((ail.net.parser.GrammarSymbol)rule.Rhs[i]).EFFirstSet, eff_entry, xi_k);
                        }
                    }

                    // check existence
                    if(entry != null && entry.Count > 0)
                    {
                        foreach(ArrayList subset in entry)
                        {
                            if(!HasEntry(non_terminal.FirstSet, subset))
                            {
                                non_terminal.FirstSet.Add(subset);
                            }
                        }
                    }

                    if(eff_entry != (object)null && eff_entry.Count > 0)
                    {
                        foreach(ArrayList subset in eff_entry)
                        {
                            if(!HasEntry(non_terminal.EFFirstSet, subset))
                            {
                                non_terminal.EFFirstSet.Add(subset);
                            }
                        }
                    }

                    changed = changed ? changed : count != non_terminal.FirstSet.Count;
                }

                if(!changed)
                {
                    break;
                }
            }
        }

        public ArrayList BuildFirstKSet(ArrayList xi_symbols)
        {
            ail.net.framework.Assert.NonNullReference(xi_symbols, "xi_symbols");

            ArrayList result = new ArrayList();

            // To compute First(a(lpha)) for a string a(lpha) = x1 x2 ... xk, use the following algorithm:
            //  (a) Set First(a(lpha)) = First(x1)-{e}
            //  (b) If e belongs to First(x1), add (First(x2)-{e}) to First(a(lpha))
            //  (c) If e belongs to First(x1) and e belongs to First(x2), then add (First(x3)-{e}) to First(a(lpha))
            //  (d) Continue in the same manner for x3, x4, ... , xk
            //  (e) Finally, if e belongs to First(xi) for all i = 1 ... k, add e to First(a(lpha))
            foreach(ail.net.parser.GrammarSymbol symbol in xi_symbols)
            {
                bool has_epsilon = false;

                for(int i = 0, n = symbol.FirstSet.Count; i < n; i++)
                {
                    bool is_epsilon = (int)(((ArrayList)symbol.FirstSet[i])[0]) == (int)ail.net.parser.Token.EType.eEpsilon;

                    if(!is_epsilon)
                    {
                        if(!HasEntry(result, (ArrayList)symbol.FirstSet[i]))
                        {
                            ArrayList wrapper = new ArrayList();
                            wrapper.AddRange((ArrayList)symbol.FirstSet[i]);
                            result.Add(wrapper);
                        }
                    }
                    else
                    {
                        has_epsilon = true; // should be only one
                    }
                }

                if(!has_epsilon)
                {
                    break;
                }
            }

            bool nullable = true;

            foreach(ail.net.parser.GrammarSymbol symbol in xi_symbols)
            {
                if(symbol.Id != (int)ail.net.parser.Token.EType.eEpsilon)
                {
                    if(!symbol.Nullable)
                    {
                        nullable = false;
                        break;
                    }
                }
            }

            if(nullable)
            {
                ArrayList wrapper = new ArrayList();
                wrapper.Add((int)ail.net.parser.Token.EType.eEpsilon);
                result.Add(wrapper);
            }

            return result;
        }

        public ArrayList BuildEFFirstKSet(ArrayList xi_symbols, int xi_k)
        {
            // Let's X belongs to N U T. EFFk(X a(lpha)) = EFFk(X) (+)k FIRSTk(a(lpha)).
            ail.net.framework.Assert.NonNullReference(xi_symbols, "xi_symbols");

            ArrayList result = null;

            ail.net.parser.GrammarSymbol x = (ail.net.parser.GrammarSymbol)xi_symbols[0];

            ArrayList alpha = new ArrayList(xi_symbols.Count-1); // reserve
            
            for(int i = 1; i < xi_symbols.Count; i++) // the first is 'x'
            {
                alpha.Add(xi_symbols[i]);
            }

            ArrayList x_eff = ((ail.net.parser.GrammarSymbol)ail.net.parser.GrammarPool.Instance.Pool[x.Id]).EFFirstSet;
            ArrayList alpha_first = BuildFirstKSet(alpha);

            result = OperatorInfixK(x_eff, alpha_first, xi_k);

            return result;
        }

        public void BuildFollowSet()
        {
            // go through the rules and for each rule we look at each non-terminal on the righthand
            // side. For example, we may have a rule X -> ... ABC ..., and let A be a non-terminal.
            // Calculate FIRST(BC...) and add all elements from this set, except 'e' to FOLLOW(A). If
            // 'e' is in FIRST(BC...), then we add all elements from FOLLOW(X) to FOLLOW(A). The
            // process is repeated until there are no more changes to the table for FOLLOW.
            //
            // The computation of Follow(A) depends of the First sets defined earlier. If B -> a(lpha)Ab(eta)
            // then Follow(A) must contains First(b(eta)). If 'e' belongs to First(b(eta)) (i.e., b(eta) is nullable),
            // or if b(eta) is empty, then Follow(A) must also contain Follow(B).
            ail.net.parser.GrammarSymbol symbol = (ail.net.parser.GrammarSymbol)ail.net.parser.GrammarPool.Instance.Pool[StartSymbolIdAttr];

            symbol.FollowSet.Add((int)ail.net.parser.Token.EType.eEpsilon);

            bool changed;

            for(;;)
            {
                changed = false;

                foreach(ail.net.parser.GrammarRule rule in RulesAttr)
                {
                    ail.net.parser.GrammarSymbol l_symbol = (ail.net.parser.GrammarSymbol)rule.Lhs[0];

                    for(int k = 0, m = rule.Rhs.Count; k < m; k++)
                    {
                        ail.net.parser.GrammarSymbol r_symbol = (ail.net.parser.GrammarSymbol)rule.Rhs[k];

                        if(r_symbol.IsNonTerminal())
                        {
                            int count = r_symbol.FollowSet.Count;

                            ArrayList first_set = new ArrayList();

                            if(k < m-1)
                            {
                                first_set.Add(rule.Rhs[k+1]); // temporary storage
                                first_set = BuildFirstSet(first_set);
                            }

                            for(int i = 0, n = first_set.Count; i < n; i++)
                            {
                                if((int)first_set[i] != (int)ail.net.parser.Token.EType.eEpsilon && !r_symbol.FollowSet.Contains(first_set[i]))
                                {
                                    r_symbol.FollowSet.Add(first_set[i]);
                                }
                            }

                            if(k == m-1 || first_set.Contains(ail.net.parser.Token.EType.eEpsilon))
                            {
                                for(int i = 0, n = l_symbol.FollowSet.Count; i < n; i++)
                                {
                                    if(!r_symbol.FollowSet.Contains(l_symbol.FollowSet[i]))
                                    {
                                        r_symbol.FollowSet.Add(l_symbol.FollowSet[i]);
                                    }
                                }
                            }

                            changed = changed ? changed : count != r_symbol.FollowSet.Count;
                        }
                    }
                }

                if(!changed)
                {
                    break;
                }
            }
        }

        public void BuildFollowKSet(int xi_k)
        {
            // Sudkump p. 501
            //  1. FL(S) = {e(psilon)}
            //  2. for each A belongs to N-{S} do FL(A) = empty
            //  3. repeat
            //      3.1 for each A belongs to N do FL'(A) = FL(A)
            //      3.2 for each rule A -> w = u1u2...un with w != T* do
            //          3.2.1 L = FL'(A)
            //          3.2.2 if un belongs to N then FL(un) = FL(un) U L
            //          3.2.3 for i = n-1 to 1 do
            //                  3.2.3.1 L = TRUNCk(FIRSTk(ui+1)L)
            //                  3.2.3.2 if ui belongs to N then FL(ui) = FL(ui) U L
            //                end for
            //          end for
            //     until FL(A) = FL'(A) for every A belongs to N
            //  4. FOLLOWk(A) = FL(A)
            // FOLLOW set is list of lists for every non-terminal in grammar, size of "lists" is K
            //    ( )
            //     | \
            //     |   --- 
            //     |      |
            // (0,1..K) (0,1..K)
            ail.net.framework.Assert.Condition(xi_k > 0, "ail.net.parser.Grammar.BuildFirstSet: xi_k > 0");

            // collect all non-terminals to deal with
            Hashtable nonterminals = new Hashtable();
            
            foreach(ail.net.parser.GrammarSymbol symbol in ail.net.parser.GrammarPool.Instance.Pool.Values)
            {
                if(symbol.IsNonTerminal())
                {
                    nonterminals[symbol.Id] = symbol;
                }
            }

            // 1. FL(S) = {e(psilon)}
            ArrayList fl = ((ail.net.parser.GrammarSymbol)nonterminals[StartSymbolId]).FollowSet; // trigger initialization

            ArrayList fl_e = new ArrayList(); // follow set element
            fl_e.Add((int)ail.net.parser.Token.EType.eEpsilon);
            
            fl.Add(fl_e);

            // 2. for each A belongs to N-{S} do FL(A) = empty
            foreach(ail.net.parser.GrammarSymbol symbol in nonterminals.Values)
            {
                ArrayList dummy = symbol.FollowSet; // trigger initialization
            }

            // 3. repeat
            for(;;)
            {
                bool changed = false;

                // 3.2 for each rule A -> w = u1u2...un with w != T* do
                foreach(ail.net.parser.GrammarRule rule in RulesAttr)
                {
                    // w != T*
                    if(rule.RhsNonTerminalCount > 0)
                    {
                        // 3.2.1 L = FL'(A)
                        ail.net.parser.GrammarSymbol a = (ail.net.parser.GrammarSymbol)rule.Lhs[0];
                        
                        ArrayList l = a.FollowSet;

                        // 3.2.2 if un belongs to N then FL(un) = FL(un) U L
                        ail.net.parser.GrammarSymbol un = (ail.net.parser.GrammarSymbol)rule.Rhs[rule.Rhs.Count-1];

                        if(un.IsNonTerminal())
                        {
                            fl = ((ail.net.parser.GrammarSymbol)nonterminals[un.Id]).FollowSet;

                            foreach(ArrayList e in l)
                            {
                                if(!HasEntry(fl, e))
                                {
                                    fl.Add(e);
                                    changed = true;
                                }
                            }
                        }

                        //  3.2.3 for i = n-1 to 1 do
                        //      3.2.3.1 L = TRUNCk(FIRSTk(ui+1)L)
                        //      3.2.3.2 if ui belongs to N then FL(ui) = FL(ui) U L
                        //  end for
                        for(int i = rule.Rhs.Count-2; i >= 0; i--)
                        {
                            l = OperatorInfixK(((ail.net.parser.GrammarSymbol)rule.Rhs[i+1]).FirstSet, l, xi_k);

                            if(((ail.net.parser.GrammarSymbol)rule.Rhs[i]).IsNonTerminal())
                            {
                                fl = ((ail.net.parser.GrammarSymbol)nonterminals[((ail.net.parser.GrammarSymbol)rule.Rhs[i]).Id]).FollowSet;

                                foreach(ArrayList e in l)
                                {
                                    if(!HasEntry(fl, e))
                                    {
                                        fl.Add(e);
                                        changed = true;
                                    }
                                }
                            }
                        }
                    }
                }

                if(!changed)
                {
                    break;
                }
            }
        }

        public void BuildErroneousSet()
        {
            foreach(ail.net.parser.GrammarRule rule in RulesAttr)
            {
                if(rule.IsErroneousRule())
                {
                    ((ail.net.parser.GrammarSymbol)rule.Lhs[0]).Erroneous = true;
                }
            }
        }

        private ArrayList OperatorInfixK(ArrayList xi_firstset1, ArrayList xi_firstset2, int xi_k)
        {
            // L1 (+)k L2
            // L1 = { e, abb }
            // L2 = { b, bab }
            // L1 (+)2 L2 = { b, ba, ab }
            // AU: p.348
            //??ail.net.framework.Assert.NonNullReference(xi_firstset1, "xi_firstset1");
            //??ail.net.framework.Assert.Condition(xi_k > 0, "ail.net.parser.Grammar.OperatorInfixFirst: xi_k > 0");

            ArrayList result = new ArrayList();

            if(xi_firstset2 == (object)null || xi_firstset2.Count == 0)
            {
                foreach(ArrayList fset_entry1 in xi_firstset1)
                {
                    if(fset_entry1.Count > 0 && (int)fset_entry1[0] != (int)ail.net.parser.Token.EType.eEpsilon)
                    {
                        foreach(ArrayList entry in xi_firstset1)
                        {
                            if(!HasEntry(result, entry))
                            {
                                result.Add(entry);
                            }
                        }
                    }
                }
            }
            else
            {
                foreach(ArrayList fset_entry1 in xi_firstset1)
                {
                    int j = 0;
_set2:
                    ArrayList entry = new ArrayList();

                    if(fset_entry1.Count > 0 && (int)fset_entry1[0] != (int)ail.net.parser.Token.EType.eEpsilon)
                    {
                        entry.AddRange(fset_entry1);
                    }

                    if((int)((ArrayList)xi_firstset2[j])[0] != (int)ail.net.parser.Token.EType.eEpsilon)
                    {
                        entry.AddRange((ArrayList)xi_firstset2[j]);
                    }

                    // keep only up to xi_k symbols
                    if(entry.Count > xi_k)
                    {
                        entry.RemoveRange(xi_k, entry.Count-xi_k);
                    }

                    if(entry.Count > 0)
                    {
                        if(!HasEntry(result, entry))
                        {
                            result.Add(entry);
                        }
                    }

                    if(++j < xi_firstset2.Count)
                    {
                        goto _set2;
                    }
                }
            }

            return result;
        }

        public bool HasEntry(ArrayList xi_set, ArrayList xi_entry)
        {
            ail.net.framework.Assert.NonNullReference(xi_set, "xi_set");
            ail.net.framework.Assert.NonNullReference(xi_entry, "xi_entry");

            bool result = false;

            foreach(ArrayList entry in xi_set)
            {
                result = entry.Count == xi_entry.Count;

                if(result)
                {
                    int i = 0;

                    for(; i < entry.Count; i++)
                    {
                        if((int)entry[i] != (int)xi_entry[i])
                        {
                            result = false;
                            break;
                        }
                    }

                    if(result)
                    {
                        break;
                    }
                }
            }

            return result;
        }

        public void ClearFirstSet()
        {
            foreach(ail.net.parser.GrammarSymbol symbol in ail.net.parser.GrammarPool.Instance.Pool.Values)
            {
                symbol.FirstSet.Clear();
            }
        }

        public void ClearEffSet()
        {
            foreach(ail.net.parser.GrammarSymbol symbol in ail.net.parser.GrammarPool.Instance.Pool.Values)
            {
                symbol.EFFirstSet.Clear();
            }
        }

        public void ClearFollowSet()
        {
            foreach(ail.net.parser.GrammarSymbol symbol in ail.net.parser.GrammarPool.Instance.Pool.Values)
            {
                if(symbol.IsNonTerminal())
                {
                    symbol.FollowSet.Clear();
                }
            }
        }

        public void PopulateRulesMap()
        {
            RulesMapAttr.Clear();

            foreach(ail.net.parser.GrammarRule rule in RulesAttr)
            {
                RulesMapAttr.Add(rule.Id, rule);
            }
        }

        public string DecorateRule(ail.net.parser.GrammarRule xi_rule)
        {
            ail.net.framework.Assert.NonNullReference(xi_rule, "xi_rule");

            StringBuilder result = new StringBuilder();
                        
            foreach(ail.net.parser.GrammarSymbol symbol in xi_rule.Lhs)
            {
                result.Append(symbol.Name);
            }

            result.Append(@" : ");

            foreach(ail.net.parser.GrammarSymbol symbol in xi_rule.Rhs)
            {
                if(symbol.IsTerminal())
                {
                    result.Append(@"'");
                }
                
                result.Append(symbol.Name);

                if(symbol.IsTerminal())
                {
                    result.Append(@"'");
                }

                result.Append(@" ");
            }

            return result.ToString();
        }

        public string Decorate()
        {
            StringBuilder result = new StringBuilder();
                        
            foreach(ail.net.parser.GrammarRule rule in RulesAttr)
            {
                result.Append(DecorateRule(rule));
                result.Append(Environment.NewLine);
            }

            return result.ToString();
        }

        public string DecorateFirstSet()
        {
            StringBuilder result = new StringBuilder();

            foreach(ail.net.parser.GrammarSymbol symbol in ail.net.parser.GrammarPool.Instance.Pool.Values)
            {
                result.Append(symbol.Name+": ");
                result.Append(Environment.NewLine);
                result.Append("\t");

                for(int i = 0; i < symbol.FirstSet.Count; i++)
                {
                    result.Append(((ail.net.parser.GrammarSymbol)ail.net.parser.GrammarPool.Instance.Pool[symbol.FirstSet[i]]).Name+" ");
                }

                result.Append(Environment.NewLine);
            }

            return result.ToString();
        }

        public string DecorateFirstKSet()
        {
            StringBuilder result = new StringBuilder();

            foreach(ail.net.parser.GrammarSymbol symbol in ail.net.parser.GrammarPool.Instance.Pool.Values)
            {
                result.Append(symbol.Name+": ");
                result.Append(Environment.NewLine);
                result.Append("\t");

                foreach(ArrayList fset_entry in symbol.FirstSet)
                {
                    for(int i = 0; i < fset_entry.Count; i++)
                    {
                        result.Append(((ail.net.parser.GrammarSymbol)ail.net.parser.GrammarPool.Instance.Pool[fset_entry[i]]).Name+" ");
                    }

                    result.Append("   ");
                }

                result.Append(Environment.NewLine);
            }

            return result.ToString();
        }

        public string DecorateEFFirstKSet()
        {
            StringBuilder result = new StringBuilder();

            foreach(ail.net.parser.GrammarSymbol symbol in ail.net.parser.GrammarPool.Instance.Pool.Values)
            {
                result.Append(symbol.Name+": ");
                result.Append(Environment.NewLine);
                result.Append("\t");

                foreach(ArrayList effset_entry in symbol.EFFirstSet)
                {
                    for(int i = 0; i < effset_entry.Count; i++)
                    {
                        result.Append(((ail.net.parser.GrammarSymbol)ail.net.parser.GrammarPool.Instance.Pool[effset_entry[i]]).Name+" ");
                    }

                    result.Append("   ");
                }

                result.Append(Environment.NewLine);
            }

            return result.ToString();
        }

        public string DecorateEFFirstKSet(ArrayList xi_eff)
        {
            ail.net.framework.Assert.NonNullReference(xi_eff, "xi_eff");

            StringBuilder result = new StringBuilder();

            foreach(ArrayList eff in xi_eff)
            {
                result.Append("EFF: ");
                result.Append(Environment.NewLine);
                result.Append("\t");

                for(int i = 0; i < eff.Count; i++)
                {
                    result.Append(((ail.net.parser.GrammarSymbol)ail.net.parser.GrammarPool.Instance.Pool[eff[i]]).Name+" ");
                    result.Append("   ");
                }

                result.Append(Environment.NewLine);
            }

            return result.ToString();
        }

        public string DecorateFollowSet()
        {
            StringBuilder result = new StringBuilder();

            foreach(ail.net.parser.GrammarSymbol symbol in ail.net.parser.GrammarPool.Instance.Pool.Values)
            {
                result.Append(symbol.Name+": ");
                result.Append(Environment.NewLine);
                result.Append("\t");

                for(int i = 0; i < symbol.FollowSet.Count; i++)
                {
                    result.Append(((ail.net.parser.GrammarSymbol)ail.net.parser.GrammarPool.Instance.Pool[symbol.FollowSet[i]]).Name+" ");
                }

                result.Append(Environment.NewLine);
            }

            return result.ToString();
        }

        public string DecorateFollowKSet()
        {
            StringBuilder result = new StringBuilder();

            foreach(ail.net.parser.GrammarSymbol symbol in ail.net.parser.GrammarPool.Instance.Pool.Values)
            {
                if(symbol.IsNonTerminal())
                {
                    result.Append(symbol.Name+": ");
                    result.Append(Environment.NewLine);
                    result.Append("\t");

                    foreach(ArrayList fset_entry in symbol.FollowSet)
                    {
                        for(int i = 0; i < fset_entry.Count; i++)
                        {
                            result.Append(((ail.net.parser.GrammarSymbol)ail.net.parser.GrammarPool.Instance.Pool[fset_entry[i]]).Name+" ");
                        }

                        result.Append("   ");
                    }

                    result.Append(Environment.NewLine);
                }
            }

            return result.ToString();
        }

        public void Generate(string xi_grammar_type, string xi_grammar_filename, string xi_output_filename)
        {
            ail.net.framework.Assert.NonEmptyString(xi_grammar_type, "xi_grammar_type");
            ail.net.framework.Assert.NonEmptyString(xi_grammar_filename, "xi_grammar_filename");
            ail.net.framework.Assert.NonEmptyString(xi_output_filename, "xi_output_filename");

            try
            {
                StreamReader reader = new StreamReader(xi_grammar_filename);
                StreamWriter writer = File.CreateText(xi_output_filename);

                // init
                reader.BaseStream.Position = 0;

                // read rules
                ArrayList rules = ReadRules(reader);

                // generate enum EGrammar
                GenerateEnum(writer, rules);

                // generate Populate method
                GeneratePopulateMethod(writer, rules);

                // close
                writer.Flush();
                writer.Close();
                reader.Close();
            }
            catch(Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }

        private ArrayList ReadRules(StreamReader xi_reader)
        {
            ail.net.framework.Assert.NonNullReference(xi_reader, "xi_reader");
            
            ArrayList result = new ArrayList();

            for(;;)
            {
                ArrayList rule = new ArrayList();

                string line = xi_reader.ReadLine();

                if(line == null)
                {
                    break;
                }

                line = line.Trim();

                if(line.Length == 0 || line.IndexOf("//") == 0)
                {
                    continue;
                }

                rule.Add(line);

                for(;;)
                {
                    line = xi_reader.ReadLine();

                    if(line == null)
                    {
                        break;
                    }

                    line = line.Trim();

                    if(line.Length > 0)
                    {
                        if(line.IndexOf(";") == 0)
                        {
                            break;
                        }
                    }
                    else
                    {
                        continue;
                    }

                    rule.Add(line);
                }

                if(rule.Count > 0)
                {
                    result.Add(rule);
                }
            }

            return result;
        }

        private void GenerateEnum(StreamWriter xi_writer, ArrayList xi_rules)
        {
            ail.net.framework.Assert.NonNullReference(xi_writer, "xi_writer");

            const string tab2 = "        ";

            StringBuilder enum_str = new StringBuilder();
            
            enum_str.Append(tab2);
            enum_str.Append(@"public enum EGrammar : int");
            enum_str.Append(Environment.NewLine);
            enum_str.Append(tab2);
            enum_str.Append(@"{");
            enum_str.Append(Environment.NewLine);

            foreach(ArrayList rule in xi_rules)
            {
                string enum_entry = BuildEnumEntry(rule);
                
                if(enum_entry.Length > 0)
                {
                    enum_str.Append(enum_entry);
                }
            }

            enum_str.Append(tab2);
            enum_str.Append(@"}");
            enum_str.Append(Environment.NewLine);
            enum_str.Append(Environment.NewLine);
            enum_str.Append(Environment.NewLine);
            
            xi_writer.Write(enum_str);
            xi_writer.Flush();
        }

        private void GeneratePopulateMethod(StreamWriter xi_writer, ArrayList xi_rules)
        {
            ail.net.framework.Assert.NonNullReference(xi_writer, "xi_writer");
        }

        private string BuildEnumEntry(ArrayList xi_rule)
        {
            const string tab3 = "            ";

            ail.net.framework.Assert.NonNullReference(xi_rule, "xi_rule");

            StringBuilder result = new StringBuilder();
            
            if(xi_rule.Count > 0)
            {
                string lhs = BuildEnumString(((string)xi_rule[0]).Substring(0, ((string)xi_rule[0]).IndexOf(':')));

                if(lhs.Length > 0)
                {
                    for(int i = 0; i < xi_rule.Count; i++)
                    {
                        string rhs = BuildEnumString(((string)xi_rule[i]).Substring((((string)xi_rule[i]).IndexOf(i == 0 ? ':' : '|')+1)));

                        if(rhs.Length > 0)
                        {
                            result.Append(tab3);
                            result.Append("e"+lhs+"_"+rhs+",");
                            result.Append(Environment.NewLine);
                        }
                    }
                }
            }

            return result.ToString();
        }

        private string BuildEnumString(string xi_str)
        {
            ail.net.framework.Assert.NonEmptyString(xi_str, "xi_str");

            string result = "";

            string str = xi_str.Trim();
            ail.net.framework.Assert.NonEmptyString(str, "str");

            string [] str_parts;

            if(str == "'-'" || str == "'--'" || str == "'-='")
            {
                // exception, to avoid spliting minus
                str_parts = new string [] {str};
            }
            else
            {
                str_parts = str.Split(new char [] {'-', ' '});
            }

            foreach(string str_part in str_parts)
            {
                if(str_part.Length > 0)
                {
                    if(str_part[0] == '\'') // terminal
                    {
                        result += TerminalToString(str_part);
                    }
                    else
                    {
                        result += str_part[0]+str_part.Substring(1).ToLower();
                    }
                }
            }

            return result;
        }

        protected virtual string TerminalToString(string xi_str)
        {
            ail.net.framework.Assert.NonEmptyString(xi_str, "xi_str");

            string result = "";

            if(xi_str.Length > 2) // at least 'x'
            {
                result = xi_str.Substring(1, xi_str.Length-2);
                result.Trim();

                if(result == "!")
                {
                    result = "Exclam";
                }
                else if(result == "\"")
                {
                    result = "DoubleQuoute";
                }
                else if(result == "#")
                {
                    result = "NumberSign";
                }
                else if(result == "$")
                {
                    result = "Dollar";
                }
                else if(result == "%")
                {
                    result = "Percent";
                }
                else if(result == "&")
                {
                    result = "Ampersand";
                }
                else if(result == "'")
                {
                    result = "SingleQuoute";
                }
                else if(result == "(")
                {
                    result = "LeftParens";
                }
                else if(result == ")")
                {
                    result = "RightParens";
                }
                else if(result == "*")
                {
                    result = "Asterisk";
                }
                else if(result == "+")
                {
                    result = "Plus";
                }
                else if(result == ",")
                {
                    result = "Comma";
                }
                else if(result == "-")
                {
                    result = "Minus";
                }
                else if(result == ".")
                {
                    result = "Dot";
                }
                else if(result == "/")
                {
                    result = "Slash";
                }
                else if(result == ":")
                {
                    result = "Colon";
                }
                else if(result == ";")
                {
                    result = "Semicolon";
                }
                else if(result == "<")
                {
                    result = "LessThan";
                }
                else if(result == "=")
                {
                    result = "Equal";
                }
                else if(result == ">")
                {
                    result = "GreaterThan";
                }
                else if(result == "?")
                {
                    result = "Question";
                }
                else if(result == "[")
                {
                    result = "LeftBracket";
                }
                else if(result == "\\")
                {
                    result = "BackSlash";
                }
                else if(result == "]")
                {
                    result = "RightBracket";
                }
                else if(result == "^")
                {
                    result = "Circum";
                }
                else if(result == "_")
                {
                    result = "Underscore";
                }
                else if(result == "`")
                {
                    result = "Grave";
                }
                else if(result == "{")
                {
                    result = "LeftBrace";
                }
                else if(result == "|")
                {
                    result = "Bar";
                }
                else if(result == "@")
                {
                    result = "At";
                }
                else if(result == "}")
                {
                    result = "RightBrace";
                }
                else if(result == "~")
                {
                    result = "Tilde";
                }
                else
                {
                    result = result.Substring(0, 1).ToUpper()+result.Substring(1).ToLower();
                }
            }

            return result;
        }
        #endregion // methods
    }
}

#region epilog
#endregion
