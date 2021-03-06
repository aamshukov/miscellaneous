//......................................................................................
// This is a part of UI Soft Library.  1989-2006 UI Soft Inc.               .
//......................................................................................
// THIS CODE MAY BE USED, COPIED, STORED, OR DISTRIBUTED ONLY IN ACCORDANCE WITH       .
// A WRITTEN LICENSE AGREEMENT AND WITH THE INCLUSION OF THIS COPYRIGHT NOTICE.        .
//......................................................................................

#region prolog
// file       : 
// description: AhoLR1conflicts
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
    public class AhoLR1conflictsToken : ail.net.parser.Token
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

            eE0,
            eE,
            ea,
            ePlus,
            eMult,
            eLeftParens,
            eRightParens,

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

            "eE0",
            "eE",
            "ea",
            "ePlus",
            "eMult",
            "eLeftParens",
            "eRightParens"
        };
        #endregion // constants

        #region ctor/dtor/finalizer
        public AhoLR1conflictsToken()
        {
        }

        public AhoLR1conflictsToken(int xi_type, int xi_priority) : base(xi_type, xi_priority)
        {
        }
        #endregion ctor/dtor/finalizer

        #region methods
        public override object Clone()
        {
            AhoLR1conflictsToken result = new AhoLR1conflictsToken();

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
            const string name = "ail.net.test.AhoLR1conflictsToken";
            return name;
        }

        public override string GetTokenName(int xi_token_type)
        {
            return Names[xi_token_type];
        }

        public override int GetTokenSize()
        {
            return (int)ail.net.test.AhoLR1conflictsToken.EType.eSize;;
        }
        #endregion // methods
    }

    public class AhoLR1conflictsLexAnalyzer : ail.net.parser.LexAnalyzer
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
        public AhoLR1conflictsLexAnalyzer(ail.net.test.AhoLR1conflictsToken xi_token_class, ArrayList xi_errors) : base(xi_token_class, xi_errors)
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
                case '+':
                    goto _q3;
                case ')':
                    goto _q4;
                case '(':
                    goto _q5;
                case '*':
                    goto _q6;
            }


            goto _error;
_q2:
            token = (int)ail.net.test.AhoLR1conflictsToken.EType.ea;

            Next();

            goto _exit;
_q3:
            token = (int)ail.net.test.AhoLR1conflictsToken.EType.ePlus;

            Next();

            goto _exit;
_q4:
            token = (int)ail.net.test.AhoLR1conflictsToken.EType.eRightParens;

            Next();

            goto _exit;
_q5:
            token = (int)ail.net.test.AhoLR1conflictsToken.EType.eLeftParens;

            Next();

            goto _exit;
_q6:
            token = (int)ail.net.test.AhoLR1conflictsToken.EType.eMult;

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

            AddToken(result, "+", (int)ail.net.test.AhoLR1conflictsToken.EType.ePlus);
            AddToken(result, "*", (int)ail.net.test.AhoLR1conflictsToken.EType.eMult);
            AddToken(result, "(", (int)ail.net.test.AhoLR1conflictsToken.EType.eLeftParens);
            AddToken(result, ")", (int)ail.net.test.AhoLR1conflictsToken.EType.eRightParens);
            AddToken(result, "a", (int)ail.net.test.AhoLR1conflictsToken.EType.ea);

            result = result.Nfa2Dfa();
            result = result.Minimize(ail.net.parser.Fsa.EMinimizationMode.ePartition);

            return result;
        }

        public static void GenerateCode(string xi_filename)
        {
            ail.net.framework.Assert.NonEmptyString(xi_filename, "xi_filename");
            test.AhoLR1conflictsLexAnalyzer lexer = new test.AhoLR1conflictsLexAnalyzer(new ail.net.test.AhoLR1conflictsToken(), new ArrayList());
            lexer.GenerateCode(xi_filename, lexer.BuildFsa());
        }
        #endregion // methods
    }

    public class AhoLR1conflictsGrammar : ail.net.parser.Grammar
    {
        public enum EGrammar
        {
            eE0_E,
            eE_EpE,
            eE_EmE,
            eE_lEr,
            eE_a
        }

        public AhoLR1conflictsGrammar()
        {
        }

        public override bool IsCycleFree()
        {
            return false;
        }

        public override void Populate()
        {
            base.Populate();

            StartSymbolId = (int)ail.net.test.AhoLR1conflictsToken.EType.eE;

            // E0 -> E
            ail.net.parser.GrammarRule rule = AddRule((int)ail.net.test.AhoLR1conflictsGrammar.EGrammar.eE0_E);
            rule.AddLhsSymbol((int)ail.net.test.AhoLR1conflictsToken.EType.eE0, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "E'");
            rule.AddRhsSymbol((int)ail.net.test.AhoLR1conflictsToken.EType.eE, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "E");
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");

            // E -> E + E
            rule = AddRule((int)ail.net.test.AhoLR1conflictsGrammar.EGrammar.eE_EpE);
            rule.AddLhsSymbol((int)ail.net.test.AhoLR1conflictsToken.EType.eE, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "E");
            rule.AddRhsSymbol((int)ail.net.test.AhoLR1conflictsToken.EType.eE, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "E");
            rule.AddRhsSymbol((int)ail.net.test.AhoLR1conflictsToken.EType.ePlus, ail.net.parser.GrammarSymbol.EType.eTerminal, "+");
            rule.AddRhsSymbol((int)ail.net.test.AhoLR1conflictsToken.EType.eE, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "E");
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");
            
            // E -> E * E
            rule = AddRule((int)ail.net.test.AhoLR1conflictsGrammar.EGrammar.eE_EmE);
            rule.AddLhsSymbol((int)ail.net.test.AhoLR1conflictsToken.EType.eE, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "E");
            rule.AddRhsSymbol((int)ail.net.test.AhoLR1conflictsToken.EType.eE, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "E");
            rule.AddRhsSymbol((int)ail.net.test.AhoLR1conflictsToken.EType.eMult, ail.net.parser.GrammarSymbol.EType.eTerminal, "*");
            rule.AddRhsSymbol((int)ail.net.test.AhoLR1conflictsToken.EType.eE, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "E");
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");

            // E -> ( E )
            rule = AddRule((int)ail.net.test.AhoLR1conflictsGrammar.EGrammar.eE_lEr);
            rule.AddLhsSymbol((int)ail.net.test.AhoLR1conflictsToken.EType.eE, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "E");
            rule.AddRhsSymbol((int)ail.net.test.AhoLR1conflictsToken.EType.eLeftParens, ail.net.parser.GrammarSymbol.EType.eTerminal, "(");
            rule.AddRhsSymbol((int)ail.net.test.AhoLR1conflictsToken.EType.eE, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "E");
            rule.AddRhsSymbol((int)ail.net.test.AhoLR1conflictsToken.EType.eRightParens, ail.net.parser.GrammarSymbol.EType.eTerminal, ")");
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");

            // E -> a
            rule = AddRule((int)ail.net.test.AhoLR1conflictsGrammar.EGrammar.eE_a);
            rule.AddLhsSymbol((int)ail.net.test.AhoLR1conflictsToken.EType.eE, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "E");
            rule.AddRhsSymbol((int)ail.net.test.AhoLR1conflictsToken.EType.ea, ail.net.parser.GrammarSymbol.EType.eTerminal, "a");
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");

            BuildNullabilitySet();
            BuildFirstSet();

            Console.WriteLine(ail.net.parser.GrammarPool.Instance.DecoratePool());
        }
    }

    public class AhoLR1conflictsAstNode : ail.net.parser.AstNode
    {
        public enum EType
        {
            // the following one (1) entry, MUST be the first entry in the enum
            eUnknown, //                                              0

            // the following one (1) entry, MUST be the last entry in the enum
            eSize
        }

        public AhoLR1conflictsAstNode(int xi_type) : base(xi_type)
        {
        }
    }

    public class AhoLR1conflictsSemantics : ail.net.parser.Semantics
    {
        public AhoLR1conflictsSemantics(ail.net.parser.LexAnalyzer xi_lexer, ArrayList xi_errors)
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

    public class AhoLR1conflictsParser : ail.net.parser.LRParser
    {
        public AhoLR1conflictsParser(ail.net.parser.LexAnalyzer xi_lexer, ail.net.parser.Grammar xi_grammar, ArrayList xi_errors)
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
            Console.WriteLine(DecorateStates());

            CheckConflicts();

            foreach(string error in Errors)
            {
                Console.WriteLine(error);
            }

            if(Errors.Count == 0)
            {
                base.BuildActionTable();
                base.BuildGoToTable();

                Console.WriteLine(DecorateTables());
                
                base.Parse();
                Console.WriteLine(Status == ail.net.parser.Parser.EStatus.eFailed ? "Error..." : "Ok!");
            }
        }
    }

    public class AhoLR1conflicts
    {
        // E -> E + E
        // E -> E * E
        // E -> ( E )
        // E -> a
        public static void Test()
        {
            // fsa
//          ail.net.test.AhoLR1conflictsLexAnalyzer.GenerateCode(@"c:\tmp\AhoLR1conflicts.fsa.txt");
            
            // grammar
            ail.net.test.AhoLR1conflictsGrammar grammar = new ail.net.test.AhoLR1conflictsGrammar();
            
            grammar.Populate();
            Console.WriteLine(grammar.Decorate());

            // parser
            ArrayList errors = new ArrayList();

            ail.net.test.AhoLR1conflictsLexAnalyzer lexer = new ail.net.test.AhoLR1conflictsLexAnalyzer(new ail.net.test.AhoLR1conflictsToken(), errors);
            lexer.Load("(a+a)*a", ail.net.parser.Context.ELoadMedia.eMediaString);

            ail.net.test.AhoLR1conflictsParser parser = new ail.net.test.AhoLR1conflictsParser(lexer, grammar, errors);

            parser.Semantics = new ail.net.test.AhoLR1conflictsSemantics(lexer, errors);

            parser.Parse();
        }
    }
}

#region epilog
#endregion
