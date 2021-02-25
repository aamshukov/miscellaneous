//......................................................................................
// This is a part of UI Soft Library.  1989-2006 UI Soft Inc.               .
//......................................................................................
// THIS CODE MAY BE USED, COPIED, STORED, OR DISTRIBUTED ONLY IN ACCORDANCE WITH       .
// A WRITTEN LICENSE AGREEMENT AND WITH THE INCLUSION OF THIS COPYRIGHT NOTICE.        .
//......................................................................................

#region prolog
// file       : 
// description: Eps
// package    : test
//
#endregion

#region import
using System;
using System.Collections;
#endregion

namespace ail.net.test
{
    public class EpsToken : ail.net.parser.Token
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

            eA,
            ea,
            eL,

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

            "eA",
            "ea",
            "eL"
        };
        #endregion // constants

        #region ctor/dtor/finalizer
        public EpsToken()
        {
        }

        public EpsToken(int xi_type, int xi_priority) : base(xi_type, xi_priority)
        {
        }
        #endregion ctor/dtor/finalizer

        #region methods
        public override object Clone()
        {
            EpsToken result = new EpsToken();

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
            const string name = "ail.net.test.EpsToken";
            return name;
        }

        public override string GetTokenName(int xi_token_type)
        {
            return Names[xi_token_type];
        }

        public override int GetTokenSize()
        {
            return (int)ail.net.test.EpsToken.EType.eSize;;
        }
        #endregion // methods
    }

    public class EpsLexAnalyzer : ail.net.parser.LexAnalyzer
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
        public EpsLexAnalyzer(ail.net.test.EpsToken xi_token_class, ArrayList xi_errors) : base(xi_token_class, xi_errors)
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
                case 'A':
                    goto _q3;
                case 'L':
                    goto _q4;
            }


            goto _error;
_q2:
            token = (int)ail.net.test.EpsToken.EType.ea;

            Next();

            goto _exit;
_q3:
            token = (int)ail.net.test.EpsToken.EType.eA;

            Next();

            goto _exit;
_q4:
            token = (int)ail.net.test.EpsToken.EType.eL;

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

            AddToken(result, "A", (int)ail.net.test.EpsToken.EType.eA);
            AddToken(result, "a", (int)ail.net.test.EpsToken.EType.ea);
            AddToken(result, "L", (int)ail.net.test.EpsToken.EType.eL);

            result = result.Nfa2Dfa();
            result = result.Minimize(ail.net.parser.Fsa.EMinimizationMode.ePartition);

            return result;
        }

        public static void GenerateCode(string xi_filename)
        {
            ail.net.framework.Assert.NonEmptyString(xi_filename, "xi_filename");
            test.EpsLexAnalyzer lexer = new test.EpsLexAnalyzer(new ail.net.test.EpsToken(), new ArrayList());
            lexer.GenerateCode(xi_filename, lexer.BuildFsa());
        }
        #endregion // methods
    }

    public class EpsGrammar : ail.net.parser.Grammar
    {
        public enum EGrammar
        {
            eAaAa,
            eAL,
            eLa,
            eLe
        }

        public EpsGrammar()
        {
        }

        public override bool IsCycleFree()
        {
            return false;
        }

        public override void Populate()
        {
            base.Populate();

            StartSymbolId = (int)ail.net.test.EpsToken.EType.eA;
            
            // A -> a A a
            ail.net.parser.GrammarRule rule = AddRule((int)ail.net.test.EpsGrammar.EGrammar.eAaAa);
            rule.AddLhsSymbol((int)ail.net.test.EpsToken.EType.eA, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "A");
            rule.AddRhsSymbol((int)ail.net.test.EpsToken.EType.ea, ail.net.parser.GrammarSymbol.EType.eTerminal, "a");
            rule.AddRhsSymbol((int)ail.net.test.EpsToken.EType.eA, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "A");
            rule.AddRhsSymbol((int)ail.net.test.EpsToken.EType.ea, ail.net.parser.GrammarSymbol.EType.eTerminal, "a");
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");
            
            // A -> L 
            rule = AddRule((int)ail.net.test.EpsGrammar.EGrammar.eAL);
            rule.AddLhsSymbol((int)ail.net.test.EpsToken.EType.eA, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "A");
            rule.AddRhsSymbol((int)ail.net.test.EpsToken.EType.eL, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "L");
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");

            // L -> a
            rule = AddRule((int)ail.net.test.EpsGrammar.EGrammar.eLa);
            rule.AddLhsSymbol((int)ail.net.test.EpsToken.EType.eL, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "L");
            rule.AddRhsSymbol((int)ail.net.test.EpsToken.EType.ea, ail.net.parser.GrammarSymbol.EType.eTerminal, "a");
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");

            // L -> e(psilon)
            rule = AddRule((int)ail.net.test.EpsGrammar.EGrammar.eLe);
            rule.AddLhsSymbol((int)ail.net.test.EpsToken.EType.eL, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "L");
            rule.AddRhsSymbol((int)ail.net.test.EpsToken.EType.eEpsilon, ail.net.parser.GrammarSymbol.EType.eTerminal, ail.net.parser.GrammarSymbol.kEpsilon);
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");

            BuildNullabilitySet();
            Console.WriteLine(ail.net.parser.GrammarPool.Instance.DecoratePool());
        }
    }

    public class EpsAstNode : ail.net.parser.AstNode
    {
        public enum EType
        {
            // the following one (1) entry, MUST be the first entry in the enum
            eUnknown, //                                              0

            // the following one (1) entry, MUST be the last entry in the enum
            eSize
        }

        public EpsAstNode(int xi_type) : base(xi_type)
        {
        }
    }

    public class EpsSemantics : ail.net.parser.Semantics
    {
        public EpsSemantics(ail.net.parser.LexAnalyzer xi_lexer, ArrayList xi_errors)
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

    public class EpsEarleyParser : ail.net.parser.EarleyParser
    {
        public EpsEarleyParser(ail.net.parser.LexAnalyzer xi_lexer, ail.net.parser.Grammar xi_grammar, ArrayList xi_errors)
            : base(xi_lexer, xi_grammar, xi_errors)
        {
        }

        public new void Parse()
        {
            base.BuildTables();
            base.Parse();
        }
    }

    public class Eps
    {
        // A -> a A a
        // A -> L 
        // L -> a
        // L -> e(psilon)
        public static void Test()
        {
            // fsa
//          ail.net.test.EpsLexAnalyzer.GenerateCode(@"c:\tmp\eps.fsa.txt");
            
            // grammar
            ail.net.test.EpsGrammar grammar = new ail.net.test.EpsGrammar();
            
            grammar.Populate();
            Console.WriteLine(grammar.Decorate());

            // parser
            ArrayList errors = new ArrayList();

            ail.net.test.EpsLexAnalyzer lexer = new ail.net.test.EpsLexAnalyzer(new ail.net.test.EpsToken(), errors);
            lexer.Load("aa", ail.net.parser.Context.ELoadMedia.eMediaString);
        
            ail.net.test.EpsEarleyParser parser = new ail.net.test.EpsEarleyParser(lexer, grammar, errors);

            parser.Semantics = new ail.net.test.EpsSemantics(lexer, errors);

            parser.Parse();
        }
    }
}

#region epilog
#endregion
