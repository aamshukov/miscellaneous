//......................................................................................
// This is a part of UI Soft Library.  1989-2006 UI Soft Inc.               .
//......................................................................................
// THIS CODE MAY BE USED, COPIED, STORED, OR DISTRIBUTED ONLY IN ACCORDANCE WITH       .
// A WRITTEN LICENSE AGREEMENT AND WITH THE INCLUSION OF THIS COPYRIGHT NOTICE.        .
//......................................................................................

#region prolog
// file       : 
// description: Aho
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
    public class AhoToken : ail.net.parser.Token
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

            eE,
            eT,
            eF,
            eA,
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

            "eE",
            "eT",
            "eF",
            "eA",
            "ePlus",
            "eMult",
            "eLeftParens",
            "eRightParens"
        };
        #endregion // constants

        #region ctor/dtor/finalizer
        public AhoToken()
        {
        }

        public AhoToken(int xi_type, int xi_priority) : base(xi_type, xi_priority)
        {
        }
        #endregion ctor/dtor/finalizer

        #region methods
        public override object Clone()
        {
            AhoToken result = new AhoToken();

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
            const string name = "ail.net.test.AhoToken";
            return name;
        }

        public override string GetTokenName(int xi_token_type)
        {
            return Names[xi_token_type];
        }

        public override int GetTokenSize()
        {
            return (int)ail.net.test.AhoToken.EType.eSize;;
        }
        #endregion // methods
    }

    public class AhoLexAnalyzer : ail.net.parser.LexAnalyzer
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
        public AhoLexAnalyzer(ail.net.test.AhoToken xi_token_class, ArrayList xi_errors) : base(xi_token_class, xi_errors)
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
                case ')':
                    goto _q3;
                case 'E':
                    goto _q4;
                case '(':
                    goto _q5;
                case '*':
                    goto _q6;
                case 'F':
                    goto _q7;
                case '+':
                    goto _q8;
                case 'T':
                    goto _q9;
            }


            goto _error;
_q2:
            token = (int)ail.net.test.AhoToken.EType.eA;

            Next();

            goto _exit;
_q3:
            token = (int)ail.net.test.AhoToken.EType.eRightParens;

            Next();

            goto _exit;
_q4:
            token = (int)ail.net.test.AhoToken.EType.eE;

            Next();

            goto _exit;
_q5:
            token = (int)ail.net.test.AhoToken.EType.eLeftParens;

            Next();

            goto _exit;
_q6:
            token = (int)ail.net.test.AhoToken.EType.eMult;

            Next();

            goto _exit;
_q7:
            token = (int)ail.net.test.AhoToken.EType.eF;

            Next();

            goto _exit;
_q8:
            token = (int)ail.net.test.AhoToken.EType.ePlus;

            Next();

            goto _exit;
_q9:
            token = (int)ail.net.test.AhoToken.EType.eT;

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

            AddToken(result, "E", (int)ail.net.test.AhoToken.EType.eE);
            AddToken(result, "T", (int)ail.net.test.AhoToken.EType.eT);
            AddToken(result, "F", (int)ail.net.test.AhoToken.EType.eF);
            AddToken(result, "+", (int)ail.net.test.AhoToken.EType.ePlus);
            AddToken(result, "*", (int)ail.net.test.AhoToken.EType.eMult);
            AddToken(result, "(", (int)ail.net.test.AhoToken.EType.eLeftParens);
            AddToken(result, ")", (int)ail.net.test.AhoToken.EType.eRightParens);
            AddToken(result, "a", (int)ail.net.test.AhoToken.EType.eA);

            result = result.Nfa2Dfa();
            result = result.Minimize(ail.net.parser.Fsa.EMinimizationMode.ePartition);

            return result;
        }

        public static void GenerateCode(string xi_filename)
        {
            ail.net.framework.Assert.NonEmptyString(xi_filename, "xi_filename");
            test.AhoLexAnalyzer lexer = new test.AhoLexAnalyzer(new ail.net.test.AhoToken(), new ArrayList());
            lexer.GenerateCode(xi_filename, lexer.BuildFsa());
        }
        #endregion // methods
    }

    public class AhoGrammar : ail.net.parser.Grammar
    {
        public enum EGrammar
        {
            eETE,
            eET,
            eTFT,
            eTF,
            eFE,
            eFa
        }

        public AhoGrammar()
        {
        }

        public override bool IsCycleFree()
        {
            return false;
        }

        public override void Populate()
        {
            base.Populate();

            StartSymbolId = (int)ail.net.test.AhoToken.EType.eE;

            // E -> T + E
            ail.net.parser.GrammarRule rule = AddRule((int)ail.net.test.AhoGrammar.EGrammar.eETE);
            rule.AddLhsSymbol((int)ail.net.test.AhoToken.EType.eE, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "E");
            rule.AddRhsSymbol((int)ail.net.test.AhoToken.EType.eT, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "T");
            rule.AddRhsSymbol((int)ail.net.test.AhoToken.EType.ePlus, ail.net.parser.GrammarSymbol.EType.eTerminal, "+");
            rule.AddRhsSymbol((int)ail.net.test.AhoToken.EType.eE, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "E");
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");
            
            // E -> T
            rule = AddRule((int)ail.net.test.AhoGrammar.EGrammar.eET);
            rule.AddLhsSymbol((int)ail.net.test.AhoToken.EType.eE, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "E");
            rule.AddRhsSymbol((int)ail.net.test.AhoToken.EType.eT, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "T");
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");

            // T -> F * T
            rule = AddRule((int)ail.net.test.AhoGrammar.EGrammar.eTFT);
            rule.AddLhsSymbol((int)ail.net.test.AhoToken.EType.eT, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "T");
            rule.AddRhsSymbol((int)ail.net.test.AhoToken.EType.eF, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "F");
            rule.AddRhsSymbol((int)ail.net.test.AhoToken.EType.eMult, ail.net.parser.GrammarSymbol.EType.eTerminal, "*");
            rule.AddRhsSymbol((int)ail.net.test.AhoToken.EType.eT, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "T");
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");

            // T -> F
            rule = AddRule((int)ail.net.test.AhoGrammar.EGrammar.eTF);
            rule.AddLhsSymbol((int)ail.net.test.AhoToken.EType.eT, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "T");
            rule.AddRhsSymbol((int)ail.net.test.AhoToken.EType.eF, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "F");
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");

            // F -> ( E )
            rule = AddRule((int)ail.net.test.AhoGrammar.EGrammar.eFE);
            rule.AddLhsSymbol((int)ail.net.test.AhoToken.EType.eF, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "F");
            rule.AddRhsSymbol((int)ail.net.test.AhoToken.EType.eLeftParens, ail.net.parser.GrammarSymbol.EType.eTerminal, "(");
            rule.AddRhsSymbol((int)ail.net.test.AhoToken.EType.eE, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "E");
            rule.AddRhsSymbol((int)ail.net.test.AhoToken.EType.eRightParens, ail.net.parser.GrammarSymbol.EType.eTerminal, ")");
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");

            // F -> a
            rule = AddRule((int)ail.net.test.AhoGrammar.EGrammar.eFa);
            rule.AddLhsSymbol((int)ail.net.test.AhoToken.EType.eF, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "F");
            rule.AddRhsSymbol((int)ail.net.test.AhoToken.EType.eA, ail.net.parser.GrammarSymbol.EType.eTerminal, "a");
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");

            BuildNullabilitySet();
            Console.WriteLine(ail.net.parser.GrammarPool.Instance.DecoratePool());
        }
    }

    public class AhoAstNode : ail.net.parser.AstNode
    {
        public enum EType
        {
            // the following one (1) entry, MUST be the first entry in the enum
            eUnknown, //                                              0

            // the following one (1) entry, MUST be the last entry in the enum
            eSize
        }

        public AhoAstNode(int xi_type) : base(xi_type)
        {
        }
    }

    public class AhoSemantics : ail.net.parser.Semantics
    {
        public AhoSemantics(ail.net.parser.LexAnalyzer xi_lexer, ArrayList xi_errors)
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

    public class AhoEarleyParser : ail.net.parser.EarleyParser
    {
        public AhoEarleyParser(ail.net.parser.LexAnalyzer xi_lexer, ail.net.parser.Grammar xi_grammar, ArrayList xi_errors)
            : base(xi_lexer, xi_grammar, xi_errors)
        {
        }

        public new void Parse()
        {
            base.BuildTables();
            base.Parse();
        }
    }

    public class Aho
    {
        // E -> T + E
        // E -> T
        // T -> F * T
        // T -> F
        // F -> ( E )
        // F -> a
        public static void Test()
        {
            // fsa
//          ail.net.test.AhoLexAnalyzer.GenerateCode(@"c:\tmp\aho.fsa.txt");
            
            // grammar
            ail.net.test.AhoGrammar grammar = new ail.net.test.AhoGrammar();
            
            grammar.Populate();
            Console.WriteLine(grammar.Decorate());

            // parser
            ArrayList errors = new ArrayList();

            ail.net.test.AhoLexAnalyzer lexer = new ail.net.test.AhoLexAnalyzer(new ail.net.test.AhoToken(), errors);
            lexer.Load("(a+a)*a", ail.net.parser.Context.ELoadMedia.eMediaString);
/*
            StringBuilder longstr = new StringBuilder();
            longstr.Append("(a+a)*a+(a+a)*a+(a+a)*a+(a+a)*a+(a+a)*a+(a+a)*a+(a+a)*a+(a+a)*a+(a+a)*a+(a+a)*a");
            string str = longstr.ToString();
            lexer.Load(str.ToString(), ail.net.parser.Context.ELoadMedia.eMediaString);
*/
            ail.net.test.AhoEarleyParser parser = new ail.net.test.AhoEarleyParser(lexer, grammar, errors);

            parser.Semantics = new ail.net.test.AhoSemantics(lexer, errors);

            parser.Parse();
        }
    }
}

#region epilog
#endregion
