//......................................................................................
// This is a part of UI Soft Library.  1989-2006 UI Soft Inc.               .
//......................................................................................
// THIS CODE MAY BE USED, COPIED, STORED, OR DISTRIBUTED ONLY IN ACCORDANCE WITH       .
// A WRITTEN LICENSE AGREEMENT AND WITH THE INCLUSION OF THIS COPYRIGHT NOTICE.        .
//......................................................................................

#region prolog
// file       : 
// description: SAaBbLR1e
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
    public class SAaBbLR1eToken : ail.net.parser.Token
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
            eB,
            ea,
            eb,

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
            "eB",
            "ea",
            "eb"
        };
        #endregion // constants

        #region ctor/dtor/finalizer
        public SAaBbLR1eToken()
        {
        }

        public SAaBbLR1eToken(int xi_type, int xi_priority) : base(xi_type, xi_priority)
        {
        }
        #endregion ctor/dtor/finalizer

        #region methods
        public override object Clone()
        {
            SAaBbLR1eToken result = new SAaBbLR1eToken();

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
            const string name = "ail.net.test.SAaBbLR1eToken";
            return name;
        }

        public override string GetTokenName(int xi_token_type)
        {
            return Names[xi_token_type];
        }

        public override int GetTokenSize()
        {
            return (int)ail.net.test.SAaBbLR1eToken.EType.eSize;;
        }
        #endregion // methods
    }

    public class SAaBbLR1eLexAnalyzer : ail.net.parser.LexAnalyzer
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
        public SAaBbLR1eLexAnalyzer(ail.net.test.SAaBbLR1eToken xi_token_class, ArrayList xi_errors) : base(xi_token_class, xi_errors)
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
            token = (int)ail.net.test.SAaBbLR1eToken.EType.ea;

            Next();

            goto _exit;
_q3:
            token = (int)ail.net.test.SAaBbLR1eToken.EType.eb;

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

            AddToken(result, "a", (int)ail.net.test.SAaBbLR1eToken.EType.ea);
            AddToken(result, "b", (int)ail.net.test.SAaBbLR1eToken.EType.eb);

            result = result.Nfa2Dfa();
            result = result.Minimize(ail.net.parser.Fsa.EMinimizationMode.ePartition);

            return result;
        }

        public static void GenerateCode(string xi_filename)
        {
            ail.net.framework.Assert.NonEmptyString(xi_filename, "xi_filename");
            test.SAaBbLR1eLexAnalyzer lexer = new test.SAaBbLR1eLexAnalyzer(new ail.net.test.SAaBbLR1eToken(), new ArrayList());
            lexer.GenerateCode(xi_filename, lexer.BuildFsa());
        }
        #endregion // methods
    }

    public class SAaBbLR1eGrammar : ail.net.parser.Grammar
    {
        public enum EGrammar
        {
            eS0_S,
            eS_AaAb,
            eS_BbBa,
            eA_e,
            eB_e
        }

        public SAaBbLR1eGrammar()
        {
        }

        public override bool IsCycleFree()
        {
            return false;
        }

        public override void Populate()
        {
            base.Populate();

            StartSymbolId = (int)ail.net.test.SAaBbLR1eToken.EType.eS0;

            // S' -> S
            ail.net.parser.GrammarRule rule = AddRule((int)ail.net.test.SAaBbLR1eGrammar.EGrammar.eS0_S);
            rule.AddLhsSymbol((int)ail.net.test.SAaBbLR1eToken.EType.eS0, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "S'");
            rule.AddRhsSymbol((int)ail.net.test.SAaBbLR1eToken.EType.eS, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "S");
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");

            // S  -> A a A b
            rule = AddRule((int)ail.net.test.SAaBbLR1eGrammar.EGrammar.eS_AaAb);
            rule.AddLhsSymbol((int)ail.net.test.SAaBbLR1eToken.EType.eS, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "S");
            rule.AddRhsSymbol((int)ail.net.test.SAaBbLR1eToken.EType.eA, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "A");
            rule.AddRhsSymbol((int)ail.net.test.SAaBbLR1eToken.EType.ea, ail.net.parser.GrammarSymbol.EType.eTerminal, "a");
            rule.AddRhsSymbol((int)ail.net.test.SAaBbLR1eToken.EType.eA, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "A");
            rule.AddRhsSymbol((int)ail.net.test.SAaBbLR1eToken.EType.eb, ail.net.parser.GrammarSymbol.EType.eTerminal, "b");
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");
            
            // S  -> B b B a
            rule = AddRule((int)ail.net.test.SAaBbLR1eGrammar.EGrammar.eS_BbBa);
            rule.AddLhsSymbol((int)ail.net.test.SAaBbLR1eToken.EType.eS, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "S");
            rule.AddRhsSymbol((int)ail.net.test.SAaBbLR1eToken.EType.eB, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "B");
            rule.AddRhsSymbol((int)ail.net.test.SAaBbLR1eToken.EType.eb, ail.net.parser.GrammarSymbol.EType.eTerminal, "b");
            rule.AddRhsSymbol((int)ail.net.test.SAaBbLR1eToken.EType.eB, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "B");
            rule.AddRhsSymbol((int)ail.net.test.SAaBbLR1eToken.EType.ea, ail.net.parser.GrammarSymbol.EType.eTerminal, "a");
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");

            // A  -> e(psilon)
            rule = AddRule((int)ail.net.test.SAaBbLR1eGrammar.EGrammar.eA_e);
            rule.AddLhsSymbol((int)ail.net.test.SAaBbLR1eToken.EType.eA, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "A");
            rule.AddRhsSymbol((int)ail.net.test.EpsToken.EType.eEpsilon, ail.net.parser.GrammarSymbol.EType.eTerminal, ail.net.parser.GrammarSymbol.kEpsilon);
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");

            // B  -> e(psilon)
            rule = AddRule((int)ail.net.test.SAaBbLR1eGrammar.EGrammar.eB_e);
            rule.AddLhsSymbol((int)ail.net.test.SAaBbLR1eToken.EType.eB, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "B");
            rule.AddRhsSymbol((int)ail.net.test.EpsToken.EType.eEpsilon, ail.net.parser.GrammarSymbol.EType.eTerminal, ail.net.parser.GrammarSymbol.kEpsilon);
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");

            BuildNullabilitySet();
            BuildFirstSet();
            BuildFollowSet();

            Console.WriteLine(ail.net.parser.GrammarPool.Instance.DecoratePool());
        }
    }

    public class SAaBbLR1eAstNode : ail.net.parser.AstNode
    {
        public enum EType
        {
            // the following one (1) entry, MUST be the first entry in the enum
            eUnknown, //                                              0

            // the following one (1) entry, MUST be the last entry in the enum
            eSize
        }

        public SAaBbLR1eAstNode(int xi_type) : base(xi_type)
        {
        }
    }

    public class SAaBbLR1eSemantics : ail.net.parser.Semantics
    {
        public SAaBbLR1eSemantics(ail.net.parser.LexAnalyzer xi_lexer, ArrayList xi_errors)
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

    public class SAaBbLR1eParser : ail.net.parser.LRParser
    {
        public SAaBbLR1eParser(ail.net.parser.LexAnalyzer xi_lexer, ail.net.parser.Grammar xi_grammar, ArrayList xi_errors)
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

            ((ail.net.parser.LRParser.State)States[0]).Id = 0;
            ((ail.net.parser.LRParser.State)States[1]).Id = 6;
            ((ail.net.parser.LRParser.State)States[2]).Id = 2;
            ((ail.net.parser.LRParser.State)States[3]).Id = 1;
            ((ail.net.parser.LRParser.State)States[4]).Id = 7;
            ((ail.net.parser.LRParser.State)States[5]).Id = 3;
            ((ail.net.parser.LRParser.State)States[6]).Id = 8;
            ((ail.net.parser.LRParser.State)States[7]).Id = 4;
            ((ail.net.parser.LRParser.State)States[8]).Id = 9;
            ((ail.net.parser.LRParser.State)States[9]).Id = 5;

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

    public class SAaBbLR1e
    {
        // S' -> S
        // S  -> A a A b
        // S  -> B b B a
        // A  -> e(psilon)
        // B  -> e(psilon)
        public static void Test()
        {
            // fsa
//          ail.net.test.SAaBbLR1eLexAnalyzer.GenerateCode(@"c:\tmp\SAaBbLR1e.fsa.txt");
            
            // grammar
            ail.net.test.SAaBbLR1eGrammar grammar = new ail.net.test.SAaBbLR1eGrammar();
            
            grammar.Populate();
            Console.WriteLine(grammar.Decorate());

            // parser
            ArrayList errors = new ArrayList();

            ail.net.test.SAaBbLR1eLexAnalyzer lexer = new ail.net.test.SAaBbLR1eLexAnalyzer(new ail.net.test.SAaBbLR1eToken(), errors);
            lexer.Load("ab", ail.net.parser.Context.ELoadMedia.eMediaString);

            ail.net.test.SAaBbLR1eParser parser = new ail.net.test.SAaBbLR1eParser(lexer, grammar, errors);

            parser.Semantics = new ail.net.test.SAaBbLR1eSemantics(lexer, errors);

            parser.Parse();
        }
    }
}

#region epilog
#endregion
