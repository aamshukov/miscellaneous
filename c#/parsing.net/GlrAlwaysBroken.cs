//......................................................................................
// This is a part of UI Soft Library. Copyright © 1989-2006 UI Soft Inc.               .
//......................................................................................
// THIS CODE MAY BE USED, COPIED, STORED, OR DISTRIBUTED ONLY IN ACCORDANCE WITH       .
// A WRITTEN LICENSE AGREEMENT AND WITH THE INCLUSION OF THIS COPYRIGHT NOTICE.        .
//......................................................................................

#region prolog
// file       : 
// description: GlrAlwaysBroken
// package    : test
//
#endregion

#region import
using System;
using System.Collections;
#endregion

namespace ail.net.test
{
    public class GlrAlwaysBrokenToken : ail.net.parser.Token
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

            eS,         // 4
            eA,         // 5
            eB,         // 6
            ea,         // 7
            eb,         // 8

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

            "eS",
            "eA",
            "eB",
            "ea",
            "eb"
        };
        #endregion // constants

        #region ctor/dtor/finalizer
        public GlrAlwaysBrokenToken()
        {
        }

        public GlrAlwaysBrokenToken(int xi_type, int xi_priority) : base(xi_type, xi_priority)
        {
        }
        #endregion ctor/dtor/finalizer

        #region methods
        public override object Clone()
        {
            GlrAlwaysBrokenToken result = new GlrAlwaysBrokenToken();

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
            const string name = "ail.net.test.GlrAlwaysBrokenToken";
            return name;
        }

        public override string GetTokenName(int xi_token_type)
        {
            return Names[xi_token_type];
        }

        public override int GetTokenSize()
        {
            return (int)ail.net.test.GlrAlwaysBrokenToken.EType.eSize;;
        }
        #endregion // methods
    }

    public class GlrAlwaysBrokenLexAnalyzer : ail.net.parser.LexAnalyzer
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
        public GlrAlwaysBrokenLexAnalyzer(ail.net.test.GlrAlwaysBrokenToken xi_token_class, ArrayList xi_errors) : base(xi_token_class, xi_errors)
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
                case 'b':
                    goto _q3;
            }


            goto _error;
_q2:
            token = (int)ail.net.test.GlrAlwaysBrokenToken.EType.ea;

            Next();

            goto _exit;
_q3:
            token = (int)ail.net.test.GlrAlwaysBrokenToken.EType.eb;

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

            AddToken(result, "a", (int)ail.net.test.GlrAlwaysBrokenToken.EType.ea);
            AddToken(result, "b", (int)ail.net.test.GlrAlwaysBrokenToken.EType.eb);

            result = result.Nfa2Dfa();
            result = result.Minimize(ail.net.parser.Fsa.EMinimizationMode.ePartition);

            return result;
        }

        public static void GenerateCode(string xi_filename)
        {
            ail.net.framework.Assert.NonEmptyString(xi_filename, "xi_filename");
            test.GlrAlwaysBrokenLexAnalyzer lexer = new test.GlrAlwaysBrokenLexAnalyzer(new ail.net.test.GlrAlwaysBrokenToken(), new ArrayList());
            lexer.GenerateCode(xi_filename, lexer.BuildFsa());
        }
        #endregion // methods
    }

    public class GlrAlwaysBrokenGrammar : ail.net.parser.Grammar
    {
        public enum EGrammar
        {
            eS_bA,
            eA_aAB,
            eA_e,
            eB_e
        }

        public GlrAlwaysBrokenGrammar()
        {
        }

        public override bool IsCycleFree()
        {
            return false;
        }

        public override void Populate()
        {
            base.Populate();
            
            StartSymbolId = (int)ail.net.test.GlrAlwaysBrokenToken.EType.eS;

            // S -> b A
            ail.net.parser.GrammarRule rule = AddRule((int)ail.net.test.GlrAlwaysBrokenGrammar.EGrammar.eS_bA);
            rule.AddLhsSymbol((int)ail.net.test.GlrAlwaysBrokenToken.EType.eS, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "S");
            rule.AddRhsSymbol((int)ail.net.test.GlrAlwaysBrokenToken.EType.eb, ail.net.parser.GrammarSymbol.EType.eTerminal, "b");
            rule.AddRhsSymbol((int)ail.net.test.GlrAlwaysBrokenToken.EType.eA, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "A");
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");
            
            // A -> a A B
            rule = AddRule((int)ail.net.test.GlrAlwaysBrokenGrammar.EGrammar.eA_aAB);
            rule.AddLhsSymbol((int)ail.net.test.GlrAlwaysBrokenToken.EType.eA, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "A");
            rule.AddRhsSymbol((int)ail.net.test.GlrAlwaysBrokenToken.EType.ea, ail.net.parser.GrammarSymbol.EType.eTerminal, "a");
            rule.AddRhsSymbol((int)ail.net.test.GlrAlwaysBrokenToken.EType.eA, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "A");
            rule.AddRhsSymbol((int)ail.net.test.GlrAlwaysBrokenToken.EType.eB, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "B");
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");

            // A -> e(psilon)
            rule = AddRule((int)ail.net.test.GlrAlwaysBrokenGrammar.EGrammar.eA_e);
            rule.AddLhsSymbol((int)ail.net.test.GlrAlwaysBrokenToken.EType.eA, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "A");
            rule.AddRhsSymbol((int)ail.net.test.EpsToken.EType.eEpsilon, ail.net.parser.GrammarSymbol.EType.eTerminal, ail.net.parser.GrammarSymbol.kEpsilon);
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");

            // B -> e(psilon)
            rule = AddRule((int)ail.net.test.GlrAlwaysBrokenGrammar.EGrammar.eB_e);
            rule.AddLhsSymbol((int)ail.net.test.GlrAlwaysBrokenToken.EType.eB, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "B");
            rule.AddRhsSymbol((int)ail.net.test.EpsToken.EType.eEpsilon, ail.net.parser.GrammarSymbol.EType.eTerminal, ail.net.parser.GrammarSymbol.kEpsilon);
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");

            BuildNullabilitySet();
            Console.WriteLine(ail.net.parser.GrammarPool.Instance.DecoratePool());
        }
    }

    public class GlrAlwaysBrokenAstNode : ail.net.parser.AstNode
    {
        public enum EType
        {
            // the following one (1) entry, MUST be the first entry in the enum
            eUnknown, //                                              0


            // the following one (1) entry, MUST be the last entry in the enum
            eSize
        }

        public GlrAlwaysBrokenAstNode(int xi_type) : base(xi_type)
        {
        }
    }

    public class GlrAlwaysBrokenSemantics : ail.net.parser.Semantics
    {
        public GlrAlwaysBrokenSemantics(ail.net.parser.LexAnalyzer xi_lexer, ArrayList xi_errors)
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

    public class GlrAlwaysBrokenEarleyParser : ail.net.parser.EarleyParser
    {
        public GlrAlwaysBrokenEarleyParser(ail.net.parser.LexAnalyzer xi_lexer, ail.net.parser.Grammar xi_grammar, ArrayList xi_errors)
            : base(xi_lexer, xi_grammar, xi_errors)
        {
        }

        public new ail.net.parser.AstNode Parse()
        {
            base.BuildTables();
            return base.Parse();
        }
    }

    public class GlrAlwaysBroken
    {
        // S -> b A
        // A -> a A B
        // A -> e(psilon)
        // B -> e(psilon)
        // ..............
        // baa
        public static void Test()
        {
            // fsa
//          ail.net.test.GlrAlwaysBrokenLexAnalyzer.GenerateCode(@"c:\tmp\GlrAlwaysBroken.fsa.txt");
            
            // grammar
            ail.net.test.GlrAlwaysBrokenGrammar grammar = new ail.net.test.GlrAlwaysBrokenGrammar();
            
            grammar.Populate();
            Console.WriteLine(grammar.Decorate());

            // parser
            ArrayList errors = new ArrayList();

            ail.net.test.GlrAlwaysBrokenLexAnalyzer lexer = new ail.net.test.GlrAlwaysBrokenLexAnalyzer(new ail.net.test.GlrAlwaysBrokenToken(), errors);
            lexer.Load("baa", ail.net.parser.Context.ELoadMedia.eMediaString);
        
            ail.net.test.GlrAlwaysBrokenEarleyParser parser = new ail.net.test.GlrAlwaysBrokenEarleyParser(lexer, grammar, errors);
            
            parser.Semantics = new ail.net.test.GlrAlwaysBrokenSemantics(lexer, errors);

            ail.net.parser.AstNode ast = parser.Parse();

            if(ast != (object)null)
            {
                Console.WriteLine(parser.DecorateTree(ast));
            }
        }
    }
}

#region epilog
#endregion
