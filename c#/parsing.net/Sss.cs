//......................................................................................
// This is a part of UI Soft Library. Copyright © 1989-2006 UI Soft Inc.               .
//......................................................................................
// THIS CODE MAY BE USED, COPIED, STORED, OR DISTRIBUTED ONLY IN ACCORDANCE WITH       .
// A WRITTEN LICENSE AGREEMENT AND WITH THE INCLUSION OF THIS COPYRIGHT NOTICE.        .
//......................................................................................

#region prolog
// file       : 
// description: Sss
// package    : test
//
#endregion

#region import
using System;
using System.Collections;
#endregion

namespace ail.net.test
{
    public class SssToken : ail.net.parser.Token
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

            eS,        // 4
            eN,        // 5
            ePlus,     // 6

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
            "eN",
            "ePlus",
        };
        #endregion // constants

        #region ctor/dtor/finalizer
        public SssToken()
        {
        }

        public SssToken(int xi_type, int xi_priority) : base(xi_type, xi_priority)
        {
        }
        #endregion ctor/dtor/finalizer

        #region methods
        public override object Clone()
        {
            SssToken result = new SssToken();

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
            const string name = "ail.net.test.SssToken";
            return name;
        }

        public override string GetTokenName(int xi_token_type)
        {
            return Names[xi_token_type];
        }

        public override int GetTokenSize()
        {
            return (int)ail.net.test.SssToken.EType.eSize;;
        }
        #endregion // methods
    }

    public class SssLexAnalyzer : ail.net.parser.LexAnalyzer
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
        public SssLexAnalyzer(ail.net.test.SssToken xi_token_class, ArrayList xi_errors) : base(xi_token_class, xi_errors)
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
                case '+':
                    goto _q2;
                case 'n':
                    goto _q3;
            }

            goto _error;
_q2:
            token = (int)ail.net.test.SssToken.EType.ePlus;

            Next();

            goto _exit;
_q3:
            token = (int)ail.net.test.SssToken.EType.eN;

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

            AddToken(result, "n", (int)ail.net.test.SssToken.EType.eN);
            AddToken(result, "+", (int)ail.net.test.SssToken.EType.ePlus);

            result = result.Nfa2Dfa();
            result = result.Minimize(ail.net.parser.Fsa.EMinimizationMode.ePartition);

            return result;
        }

        public static void GenerateCode(string xi_filename)
        {
            ail.net.framework.Assert.NonEmptyString(xi_filename, "xi_filename");
            test.SssLexAnalyzer lexer = new test.SssLexAnalyzer(new ail.net.test.SssToken(), new ArrayList());
            lexer.GenerateCode(xi_filename, lexer.BuildFsa());
        }
        #endregion // methods
    }

    public class SssGrammar : ail.net.parser.Grammar
    {
        public enum EGrammar
        {
            eSSS,
            eSS,
            eSn
        }

        public SssGrammar()
        {
        }

        public override bool IsCycleFree()
        {
            return false;
        }

        public override void Populate()
        {
            base.Populate();
            
            StartSymbolId = (int)ail.net.test.SssToken.EType.eS;
            
            // S -> S + S
            ail.net.parser.GrammarRule rule = AddRule((int)ail.net.test.SssGrammar.EGrammar.eSSS);
            rule.AddLhsSymbol((int)ail.net.test.SssToken.EType.eS, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "S");
            rule.AddRhsSymbol((int)ail.net.test.SssToken.EType.eS, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "S");
            rule.AddRhsSymbol((int)ail.net.test.SssToken.EType.ePlus, ail.net.parser.GrammarSymbol.EType.eTerminal, "+");
            rule.AddRhsSymbol((int)ail.net.test.SssToken.EType.eS, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "S");
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");
            
            // S -> S
            rule = AddRule((int)ail.net.test.SssGrammar.EGrammar.eSS);
            rule.AddLhsSymbol((int)ail.net.test.SssToken.EType.eS, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "S");
            rule.AddRhsSymbol((int)ail.net.test.SssToken.EType.eS, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "S");
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");

            // S -> n
            rule = AddRule((int)ail.net.test.SssGrammar.EGrammar.eSn);
            rule.AddLhsSymbol((int)ail.net.test.SssToken.EType.eS, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "S");
            rule.AddRhsSymbol((int)ail.net.test.SssToken.EType.eN, ail.net.parser.GrammarSymbol.EType.eTerminal, "n");
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");

            BuildNullabilitySet();
            Console.WriteLine(ail.net.parser.GrammarPool.Instance.DecoratePool());
        }
    }

    public class SssAstNode : ail.net.parser.AstNode
    {
        public enum EType
        {
            // the following one (1) entry, MUST be the first entry in the enum
            eUnknown, //                                              0

            eSSpS,    // compound root node S -> S + S                1
            eSS,      // compound root node S -> S                    2
            eSn,      // identifier n                                 3
            eSp,      // operation +                                  4

            // the following one (1) entry, MUST be the last entry in the enum
            eSize
        }

		public SssAstNode(int xi_type) : base(xi_type)
		{
		}
    }

    public class SssSemantics : ail.net.parser.Semantics
    {
        public SssSemantics(ail.net.parser.LexAnalyzer xi_lexer, ArrayList xi_errors)
            : base(xi_lexer, xi_errors)
        {
		}

        public override ail.net.parser.AstNode Start(object xi_item)
        {
            ail.net.parser.AstNode result = null;
            
            if(((ail.net.parser.EarleyParser.Item)xi_item).CoreItem.Rule.Id == (int)ail.net.test.SssGrammar.EGrammar.eSSS)
            {
				result = new ail.net.test.SssAstNode((int)ail.net.test.SssAstNode.EType.eSSpS);
				result.Token = (ail.net.test.SssToken)((ail.net.parser.EarleyParser.Item)xi_item).MasterChart.Token.Clone();
			}
			else if(((ail.net.parser.EarleyParser.Item)xi_item).CoreItem.Rule.Id == (int)ail.net.test.SssGrammar.EGrammar.eSS)
			{
//??				result = new ail.net.test.SssAstNode((int)ail.net.test.SssAstNode.EType.eSS);
			}

			return result;
        }

        public override void End()
        {
        }

        public override void HandleTerminal(ail.net.parser.AstNode xi_node, ail.net.parser.Token xi_token)
        {
            if(xi_token.Type == (int)ail.net.test.SssToken.EType.eN)
            {
                xi_node.Type  = (int)ail.net.test.SssAstNode.EType.eSn;
                xi_node.Token = xi_token;
            }
            else if(xi_token.Type == (int)ail.net.test.SssToken.EType.ePlus)
            {
                xi_node.Type  = (int)ail.net.test.SssAstNode.EType.eSp;
                xi_node.Token = xi_token;
            }
        }

        public override ail.net.parser.AstNode HandleNonTerminalBefore(ail.net.parser.AstNode xi_node, object xi_item)
        {
            ail.net.parser.AstNode result = null;
            
            if(((ail.net.parser.EarleyParser.Item)xi_item).CoreItem.Rule.Id == (int)ail.net.test.SssGrammar.EGrammar.eSSS)
            {
                result = new ail.net.test.SssAstNode((int)ail.net.test.SssAstNode.EType.eSn);
                xi_node.AddNode(result);
            }
            else if(((ail.net.parser.EarleyParser.Item)xi_item).CoreItem.Rule.Id == (int)ail.net.test.SssGrammar.EGrammar.eSS)
            {
                result = xi_node;
            }
            else if(((ail.net.parser.EarleyParser.Item)xi_item).CoreItem.Rule.Id == (int)ail.net.test.SssGrammar.EGrammar.eSn)
            {
                result = new ail.net.test.SssAstNode((int)ail.net.test.SssAstNode.EType.eSn);
                xi_node.AddNode(result);
            }

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

    public class SssEarleyParser : ail.net.parser.EarleyParser
    {
        public SssEarleyParser(ail.net.parser.LexAnalyzer xi_lexer, ail.net.parser.Grammar xi_grammar, ArrayList xi_errors)
            : base(xi_lexer, xi_grammar, xi_errors)
        {
        }

        public new ail.net.parser.AstNode Parse()
        {
            base.BuildTables();
            return base.Parse();
        }
    }

    public class Sss
    {
        // S -> S + S
        // S -> S
        // S -> n
        public static void Test()
        {
            // fsa
//          ail.net.test.SssLexAnalyzer.GenerateCode(@"c:\tmp\sss.fsa.txt");
            
            // grammar
            ail.net.test.SssGrammar grammar = new ail.net.test.SssGrammar();
            
            grammar.Populate();
            Console.WriteLine(grammar.Decorate());

            // parser
            ArrayList errors = new ArrayList();

            ail.net.test.SssLexAnalyzer lexer = new ail.net.test.SssLexAnalyzer(new ail.net.test.SssToken(), errors);
            lexer.Load("n+n+n+n+n+n", ail.net.parser.Context.ELoadMedia.eMediaString);
        
            ail.net.test.SssEarleyParser parser = new ail.net.test.SssEarleyParser(lexer, grammar, errors);
            
            parser.ParserMode = ail.net.parser.EarleyParser.EParserMode.eParser;
            parser.Semantics = new ail.net.test.SssSemantics(lexer, errors);

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
