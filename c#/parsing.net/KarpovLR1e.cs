//......................................................................................
// This is a part of UI Soft Library. Copyright © 1989-2006 UI Soft Inc.               .
//......................................................................................
// THIS CODE MAY BE USED, COPIED, STORED, OR DISTRIBUTED ONLY IN ACCORDANCE WITH       .
// A WRITTEN LICENSE AGREEMENT AND WITH THE INCLUSION OF THIS COPYRIGHT NOTICE.        .
//......................................................................................

#region prolog
// file       : 
// description: KarpovLR1e
// package    : test
//
#endregion

#region import
using System;
using System.Collections;
using System.Text;
#endregion

namespace ail.net.test
{
    public class KarpovLR1eToken : ail.net.parser.Token
    {
        #region constants
        public new enum EType : int
        {
            // the following five (5) entries, MUST be the first entries in the enum
            eUnknown = 0,
            eEpsilon,
            eEndOfStream,
            eWhiteSpace,
            eEndMarker,

            eS0,    // 5
            eS,     // 6
            es,     // 7 #
            ea,     // 8
            ec,     // 9

            //
            eSize
        };

        private static new string [] Names = new string []
        {
            "eUnknown",
            "eEpsilon",
            "eEndOfStream",
            "eWhiteSpace",
            "eEndMarker",

            "eS0",
            "eS",
            "es", // #
            "ea",
            "ec"
        };
        #endregion // constants

        #region ctor/dtor/finalizer
        public KarpovLR1eToken()
        {
        }

        public KarpovLR1eToken(int xi_type, int xi_priority) : base(xi_type, xi_priority)
        {
        }
        #endregion ctor/dtor/finalizer

        #region methods
        public override object Clone()
        {
            KarpovLR1eToken result = new KarpovLR1eToken();

            result.Type       = Type;
            result.Offset     = Offset;
            result.Length     = Length;
            result.Position   = Position;
            result.LineNumber = LineNumber;
            result.Priority   = Priority;

            return result;
        }

        public override string GetClassName()
        {
            const string name = "ail.net.test.KarpovLR1eToken";
            return name;
        }

        public override string GetTokenName(int xi_token_type)
        {
            return Names[xi_token_type];
        }

        public override int GetTokenSize()
        {
            return (int)ail.net.test.KarpovLR1eToken.EType.eSize;;
        }
        #endregion // methods
    }

    public class KarpovLR1eLexAnalyzer : ail.net.parser.LexAnalyzer
    {
        #region constants
        public new enum EContext
        {
            // the following entry, MUST be the first entry in the enum
            eContextUnknown
        };
        #endregion // constants

        #region data members
        #endregion // data members

        #region ctor/dtor/finalizer
        public KarpovLR1eLexAnalyzer(ail.net.test.KarpovLR1eToken xi_token_class, ArrayList xi_errors) : base(xi_token_class, xi_errors)
        {
        }
        #endregion ctor/dtor/finalizer

        #region methods
        public override void NextLexemeImpl(int xi_context)
        {
            Prolog();
            // !!! -- generated code -- !!!
            int token = (int)ail.net.parser.Token.EType.eUnknown;

            Next();

            if(Current == ail.net.parser.Context.kEndOfStream)
            {
                goto _eos;
            }

            switch(Current)
            {
                case 'a':
                    goto _q2;
                case 'c':
                    goto _q3;
                case '#':
                    goto _q4;
            }


            goto _error;
_q2:
            token = (int)ail.net.test.KarpovLR1eToken.EType.ea;

            Next();

            goto _exit;
_q3:
            token = (int)ail.net.test.KarpovLR1eToken.EType.ec;

            Next();

            goto _exit;
_q4:
            token = (int)ail.net.test.KarpovLR1eToken.EType.es;

            Next();

            goto _exit;
_error:
            if(Current != ail.net.parser.Context.kEndOfStream)
            {
                Next();
            }
            Final((int)ail.net.parser.Token.EType.eUnknown);
            goto _epilog;
_eos:
            Final((int)ail.net.parser.Token.EType.eEndOfStream);
            goto _epilog;
_exit:
            Final(token);
_epilog:
            // !!! -- end of generated code -- !!!
            Epilog();
        }

        public ail.net.parser.Fsa BuildFsa()
        {
            ail.net.parser.Fsa result = new ail.net.parser.Fsa();

            AddToken(result, "#", (int)ail.net.test.KarpovLR1eToken.EType.es);
            AddToken(result, "a", (int)ail.net.test.KarpovLR1eToken.EType.ea);
            AddToken(result, "c", (int)ail.net.test.KarpovLR1eToken.EType.ec);

            result = result.Nfa2Dfa();
            result = result.Minimize(ail.net.parser.Fsa.EMinimizationMode.ePartition);

            return result;
        }

        public static void GenerateCode(string xi_filename)
        {
            ail.net.framework.Assert.NonEmptyString(xi_filename, "xi_filename");
            test.KarpovLR1eLexAnalyzer lexer = new test.KarpovLR1eLexAnalyzer(new ail.net.test.KarpovLR1eToken(), new ArrayList());
            lexer.GenerateCode(xi_filename, lexer.BuildFsa());
        }
        #endregion // methods
    }

    public class KarpovLR1eGrammar : ail.net.parser.Grammar
    {
        public enum EGrammar
        {
            eS0_sSs,
            eS_aSc,
            eS_e
        }

        public KarpovLR1eGrammar()
        {
        }

        public override bool IsCycleFree()
        {
            return false;
        }

        public override void Populate()
        {
            base.Populate();

            StartSymbolId = (int)ail.net.test.KarpovLR1eToken.EType.eS0;

            // S' -> # S # $
            ail.net.parser.GrammarRule rule = AddRule((int)ail.net.test.KarpovLR1eGrammar.EGrammar.eS0_sSs);
            rule.AddLhsSymbol((int)ail.net.test.KarpovLR1eToken.EType.eS0, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "S'");
            rule.AddRhsSymbol((int)ail.net.test.KarpovLR1eToken.EType.es, ail.net.parser.GrammarSymbol.EType.eTerminal, "#");
            rule.AddRhsSymbol((int)ail.net.test.KarpovLR1eToken.EType.eS, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "S");
            rule.AddRhsSymbol((int)ail.net.test.KarpovLR1eToken.EType.es, ail.net.parser.GrammarSymbol.EType.eTerminal, "#");
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");

            // S  -> a S c
            rule = AddRule((int)ail.net.test.KarpovLR1eGrammar.EGrammar.eS_aSc);
            rule.AddLhsSymbol((int)ail.net.test.KarpovLR1eToken.EType.eS, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "S");
            rule.AddRhsSymbol((int)ail.net.test.KarpovLR1eToken.EType.ea, ail.net.parser.GrammarSymbol.EType.eTerminal, "a");
            rule.AddRhsSymbol((int)ail.net.test.KarpovLR1eToken.EType.eS, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "S");
            rule.AddRhsSymbol((int)ail.net.test.KarpovLR1eToken.EType.ec, ail.net.parser.GrammarSymbol.EType.eTerminal, "c");
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");
            
            // S -> e(psilon)
            rule = AddRule((int)ail.net.test.AhoLR1eGrammar.EGrammar.eS_e);
            rule.AddLhsSymbol((int)ail.net.test.AhoLR1eToken.EType.eS, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "S");
            rule.AddRhsSymbol((int)ail.net.test.EpsToken.EType.eEpsilon, ail.net.parser.GrammarSymbol.EType.eTerminal, ail.net.parser.GrammarSymbol.kEpsilon);
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");

            BuildNullabilitySet();
//            BuildFirstSet();
//            BuildFollowSet();
            BuildFirstKSet(1);
            BuildFollowKSet(1);

            Console.WriteLine("Pool:\n"+ail.net.parser.GrammarPool.Instance.DecoratePool());

            string firstset = DecorateFirstKSet();
            string effset = DecorateEFFirstKSet();

            Console.WriteLine();
            Console.WriteLine(Decorate());
            Console.WriteLine();

            Console.WriteLine("First set: \n"+firstset);
            Console.WriteLine();
            Console.WriteLine();
            Console.WriteLine("EFF set: \n"+effset);
        }
    }

    public class KarpovLR1eAstNode : ail.net.parser.AstNode
    {
        public enum EType
        {
            // the following one (1) entry, MUST be the first entry in the enum
            eUnknown, //                                              0

            // the following one (1) entry, MUST be the last entry in the enum
            eSize
        }

        public KarpovLR1eAstNode(int xi_type) : base(xi_type)
        {
        }
    }

    public class KarpovLR1eSemantics : ail.net.parser.Semantics
    {
        public KarpovLR1eSemantics(ail.net.parser.LexAnalyzer xi_lexer, ArrayList xi_errors)
            : base(xi_lexer, xi_errors)
        {
        }

        public override ail.net.parser.AstNode Start(object xi_item)
        {
            ail.net.parser.AstNode result = null;
            return result;
        }

        public override void End()
        {
        }

        public override void HandleTerminal(ail.net.parser.AstNode xi_node, ail.net.parser.Token xi_token)
        {
        }

        public override ail.net.parser.AstNode HandleNonTerminalBefore(ail.net.parser.AstNode xi_node, object xi_item)
        {
            ail.net.parser.AstNode result = null;
            return result;
        }
        
        public override ail.net.parser.AstNode HandleNonTerminalAfter(ail.net.parser.AstNode xi_node, object xi_item)
        {
            return null;
        }

        public override void HandleError(object xi_item, ail.net.parser.Token xi_token, int [] xi_error_costs)
        {
        }
    }

    public class KarpovLR1eParser : ail.net.parser.LRParser
    {
        public KarpovLR1eParser(ail.net.parser.LexAnalyzer xi_lexer, ail.net.parser.Grammar xi_grammar, ArrayList xi_errors)
            : base(xi_lexer, xi_grammar, xi_errors)
        {
        }

        public override void Parse()
        {
            base.Init();

            LRMode = ail.net.parser.LRParser.ELRMode.eLR1;
            LRCompareMode = ail.net.parser.LRParser.ELRCompareMode.eWithLookahead;
            
            BuildCanonicalSet();

            Console.WriteLine(DecorateStates(CanonicalSet));

            BuildAutomaton();

            Console.WriteLine("States: "+States.Count);
            Console.WriteLine();
            Console.WriteLine(DecorateStates());

            SaveLR1Automaton(@"c:\tmp\karpov.lr1.automaton.txt");

            if(LoadLR1Automaton(@"c:\tmp\karpov.lr1.automaton.txt"))
            {
                Console.WriteLine("States: "+States.Count);
                Console.WriteLine();
                Console.WriteLine(DecorateStates());
            }

            BuildAutomaton();

            Console.WriteLine("States: "+States.Count);
            Console.WriteLine();
            Console.WriteLine(DecorateStates());

            int reduce_reduce_conflicts;
            int shift_reduce_conflicts;
            
            bool is_lr1_grammar = IsLR1Grammar(out reduce_reduce_conflicts, out shift_reduce_conflicts);
            
            if(!is_lr1_grammar)
            {
                foreach(string error in Errors)
                {
                    Console.WriteLine(error);
                }
            }

            if(is_lr1_grammar || reduce_reduce_conflicts == 0)
            {
                base.BuildActionTableK1();
                base.BuildGoToTable();

                Console.WriteLine(DecorateK1Tables());
            }

            // all stack elements are int
            Stack stack = new Stack();
            
            ail.net.parser.LRParser.TableKey key = new ail.net.parser.LRParser.TableKey();
            
            Lexer.NextLexeme(); // get first lexeme
            Console.WriteLine(Lexer.DecorateLexeme());

            stack.Push(0); // push initial state

            for(;;)
            {
                key.Id = Lexer.Token.Type == (int)ail.net.test.KarpovLR1eToken.EType.eEndOfStream ? // see BuildCanonicalSet/BuildAutomaton the first AddItem
                                                (int)ail.net.test.KarpovLR1eToken.EType.eEpsilon : (int)Lexer.Token.Type;
                key.State = (int)stack.Peek();

                Hashtable action_table_entries = (Hashtable)ActionTable[key]; // fetch action table value(s)

                if(action_table_entries != null && action_table_entries.Count > 0)
                {
                    ArrayList action_table_entries_flat = new ArrayList(action_table_entries.Values);
                    
                    int action_table_value = (int)action_table_entries_flat[0];

                    // we have possible conflicts here:
                    //  shift/reduce - shift has higher prioriy
                    //  reduce/reduce - should be filtered out at earlier stages
                    for(int i = 1; i < action_table_entries_flat.Count; i++)
                    {
                        if((int)action_table_entries_flat[i] >= 0)
                        {
                            action_table_value = (int)action_table_entries_flat[i];
                        }
                    }
                    
                    if(action_table_entries_flat.Count > 1)
                    {
                        // report conflicts
                    }

                    if(action_table_value >= 0)
                    {
                        // shift
                        stack.Push(Lexer.Token.Type);
                        stack.Push(action_table_value);
                        Lexer.NextLexeme();
                        Console.WriteLine(Lexer.DecorateLexeme());
                    }
                    else
                    {
                        if(Math.Abs(action_table_value) == ail.net.parser.LRParser.kAcceptedCode)
                        {
                            // accept
                            Status = ail.net.parser.Parser.EStatus.eRecognized;
                            break;
                        }
                        else
                        {
                            // reduce
                            ail.net.parser.GrammarRule rule = (ail.net.parser.GrammarRule)Grammar.RulesMap[Math.Abs(action_table_value)];
                            ail.net.framework.Assert.NonNullReference(rule, "rule");

                            for(int i = 0, n = 2*(rule.IsEmptyRule() ? 0 : rule.Rhs.Count); i < n; i++)
                            {
                                stack.Pop();
                            }
                            
                            action_table_value = (int)stack.Peek();
                            
                            stack.Push(((ail.net.parser.GrammarSymbol)rule.Lhs[0]).Id);
                            
                            key.Id = ((ail.net.parser.GrammarSymbol)rule.Lhs[0]).Id;
                            key.State = action_table_value;

                            action_table_value = (int)GoToTable[key];

                            stack.Push(action_table_value);
                        }
                    }
                }
                else
                {
                    // error procedure
                    Console.WriteLine("error!");
                    break;
                    // HandleError(stack);
                }
            }
        }
    }

    public class KarpovLR1e
    {
        // S' -> # S #
        // S  -> a S c
        // S  -> e
        public static void Test()
        {
            // fsa
//          ail.net.test.KarpovLR1eLexAnalyzer.GenerateCode(@"c:\tmp\KarpovLR1e.fsa.txt");
            
            // grammar
            ail.net.test.KarpovLR1eGrammar grammar = new ail.net.test.KarpovLR1eGrammar();
            
            grammar.Populate();
            Console.WriteLine(grammar.Decorate());

            // parser
            ArrayList errors = new ArrayList();

            ail.net.test.KarpovLR1eLexAnalyzer lexer = new ail.net.test.KarpovLR1eLexAnalyzer(new ail.net.test.KarpovLR1eToken(), errors);
            lexer.Load("#aaaccc#", ail.net.parser.Context.ELoadMedia.eMediaString);

            ail.net.test.KarpovLR1eParser parser = new ail.net.test.KarpovLR1eParser(lexer, grammar, errors);

            parser.Semantics = new ail.net.test.KarpovLR1eSemantics(lexer, errors);

            parser.Parse();
        }
    }
}

#region epilog
#endregion
