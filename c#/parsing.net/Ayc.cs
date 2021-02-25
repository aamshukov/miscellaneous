//......................................................................................
// This is a part of UI Soft Library.  1989-2006 UI Soft Inc.               .
//......................................................................................
// THIS CODE MAY BE USED, COPIED, STORED, OR DISTRIBUTED ONLY IN ACCORDANCE WITH       .
// A WRITTEN LICENSE AGREEMENT AND WITH THE INCLUSION OF THIS COPYRIGHT NOTICE.        .
//......................................................................................

#region prolog
// file       : 
// description: Ayc
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
    public class AycToken : ail.net.parser.Token
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

            eS0,
            eS,
            eA,
            ea,
            eE,

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
            "eA",
            "ea",
            "eE"
        };
        #endregion // constants

        #region ctor/dtor/finalizer
        public AycToken()
        {
        }

        public AycToken(int xi_type, int xi_priority) : base(xi_type, xi_priority)
        {
        }
        #endregion ctor/dtor/finalizer

        #region methods
        public override object Clone()
        {
            AycToken result = new AycToken();

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
            const string name = "ail.net.test.AycToken";
            return name;
        }

        public override string GetTokenName(int xi_token_type)
        {
            return Names[xi_token_type];
        }

        public override int GetTokenSize()
        {
            return (int)ail.net.test.AycToken.EType.eSize;;
        }
        #endregion // methods
    }

    public class AycLexAnalyzer : ail.net.parser.LexAnalyzer
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
        public AycLexAnalyzer(ail.net.test.AycToken xi_token_class, ArrayList xi_errors) : base(xi_token_class, xi_errors)
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
            }


            goto _error;
_q2:
            token = (int)ail.net.test.AycToken.EType.ea;

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

            AddToken(result, "a", (int)ail.net.test.AycToken.EType.ea);

            result = result.Nfa2Dfa();
            result = result.Minimize(ail.net.parser.Fsa.EMinimizationMode.ePartition);

            return result;
        }

        public static void GenerateCode(string xi_filename)
        {
            ail.net.framework.Assert.NonEmptyString(xi_filename, "xi_filename");
            test.AycLexAnalyzer lexer = new test.AycLexAnalyzer(new ail.net.test.AycToken(), new ArrayList());
            lexer.GenerateCode(xi_filename, lexer.BuildFsa());
        }
        #endregion // methods
    }

    public class AycGrammar : ail.net.parser.Grammar
    {
        public enum EGrammar
        {
            eS0_S,
            eS_AAAA,
            eA_a,
            eA_E,
            eE_e
        }

        public AycGrammar()
        {
        }

        public override bool IsCycleFree()
        {
            return false;
        }

        public override void Populate()
        {
            base.Populate();

            StartSymbolId = (int)ail.net.test.AycToken.EType.eS0;

            // S0 -> S
            ail.net.parser.GrammarRule rule = AddRule((int)ail.net.test.AycGrammar.EGrammar.eS0_S);
            rule.AddLhsSymbol((int)ail.net.test.AycToken.EType.eS0, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "S0");
            rule.AddRhsSymbol((int)ail.net.test.AycToken.EType.eS, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "S");
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");
            
            // S -> A A A A
            rule = AddRule((int)ail.net.test.AycGrammar.EGrammar.eS_AAAA);
            rule.AddLhsSymbol((int)ail.net.test.AycToken.EType.eS, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "S");
            rule.AddRhsSymbol((int)ail.net.test.AycToken.EType.eA, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "A");
            rule.AddRhsSymbol((int)ail.net.test.AycToken.EType.eA, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "A");
            rule.AddRhsSymbol((int)ail.net.test.AycToken.EType.eA, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "A");
            rule.AddRhsSymbol((int)ail.net.test.AycToken.EType.eA, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "A");
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");

            // A -> a
            rule = AddRule((int)ail.net.test.AycGrammar.EGrammar.eA_a);
            rule.AddLhsSymbol((int)ail.net.test.AycToken.EType.eA, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "A");
            rule.AddRhsSymbol((int)ail.net.test.AycToken.EType.ea, ail.net.parser.GrammarSymbol.EType.eTerminal, "a");
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");

            // A -> E
            rule = AddRule((int)ail.net.test.AycGrammar.EGrammar.eA_E);
            rule.AddLhsSymbol((int)ail.net.test.AycToken.EType.eA, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "A");
            rule.AddRhsSymbol((int)ail.net.test.AycToken.EType.eE, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "E");
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");

            // E -> e(psilon)
            rule = AddRule((int)ail.net.test.AycGrammar.EGrammar.eE_e);
            rule.AddLhsSymbol((int)ail.net.test.AycToken.EType.eE, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "E");
            rule.AddRhsSymbol((int)ail.net.test.EpsToken.EType.eEpsilon, ail.net.parser.GrammarSymbol.EType.eTerminal, ail.net.parser.GrammarSymbol.kEpsilon);
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");

            BuildNullabilitySet();
            Console.WriteLine(ail.net.parser.GrammarPool.Instance.DecoratePool());
        }
    }

    public class AycAstNode : ail.net.parser.AstNode
    {
        public enum EType
        {
            // the following one (1) entry, MUST be the first entry in the enum
            eUnknown, //                                              0

            // the following one (1) entry, MUST be the last entry in the enum
            eSize
        }

        public AycAstNode(int xi_type) : base(xi_type)
        {
        }
    }

    public class AycSemantics : ail.net.parser.Semantics
    {
        public AycSemantics(ail.net.parser.LexAnalyzer xi_lexer, ArrayList xi_errors)
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

    public class AycEarleyParser : ail.net.parser.EarleyParser
    {
        public AycEarleyParser(ail.net.parser.LexAnalyzer xi_lexer, ail.net.parser.Grammar xi_grammar, ArrayList xi_errors)
            : base(xi_lexer, xi_grammar, xi_errors)
        {
        }

        public new void Parse()
        {
            base.BuildTables();
            base.Parse();
        }
    }

    public class Ayc
    {
        // S0 -> S
        // S -> A A A A
        // A -> a
        // A -> E
        // E -> e(psilon)
        public static void Test()
        {
            // fsa
//          ail.net.test.AycLexAnalyzer.GenerateCode(@"c:\tmp\Ayc.fsa.txt");
            
            // grammar
            ail.net.test.AycGrammar grammar = new ail.net.test.AycGrammar();
            
            grammar.Populate();
            Console.WriteLine(grammar.Decorate());

            // parser
            ArrayList errors = new ArrayList();

            ail.net.test.AycLexAnalyzer lexer = new ail.net.test.AycLexAnalyzer(new ail.net.test.AycToken(), errors);

            lexer.Load("a", ail.net.parser.Context.ELoadMedia.eMediaString);

            ail.net.test.AycEarleyParser parser = new ail.net.test.AycEarleyParser(lexer, grammar, errors);

            parser.Semantics = new ail.net.test.AycSemantics(lexer, errors);

            parser.Parse();
        }
    }
}

#region epilog
#endregion
