//......................................................................................
// This is a part of UI Soft Library.  1989-2006 UI Soft Inc.               .
//......................................................................................
// THIS CODE MAY BE USED, COPIED, STORED, OR DISTRIBUTED ONLY IN ACCORDANCE WITH       .
// A WRITTEN LICENSE AGREEMENT AND WITH THE INCLUSION OF THIS COPYRIGHT NOTICE.        .
//......................................................................................

#define G5

#region prolog
// file       : 
// description: FirstFollowLaK
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
    public class EffSetToken : ail.net.parser.Token
    {
        // 0.
        // S' -> S
        // S  -> S a S b 
        // S  -> e(psilon)

        // 1.
        // S -> S a S b 
        // S -> e(psilon)

        // 2.
        // S -> A B
        // A -> B a
        // A -> e(psilon)
        // B -> C b
        // B -> C
        // C -> c
        // C -> e(psilon)

        // 3. (check for non-termination in build first!)
        // S -> A S
        // S -> b
        // A -> S A
        // A -> a

        // 4. (check first k=2)
        // S -> A # #
        // A -> a A d
        // A -> B C
        // B -> b B c
        // B -> e(psilon)
        // C -> a c C
        // C -> a d

        // 5.
        // S -> A B C a b c d
        // A -> a
        // A -> e(psilon)
        // B -> b
        // B -> e(psilon)
        // C -> c
        // C -> e(psilon)
        #region constants
        public new enum EType : int
        {
            // the following five (5) entries, MUST be the first entries in the enum
            eUnknown = 0,
            eEpsilon,
            eEndOfStream,
            eWhiteSpace,
            eEndMarker,
#if G0
            eS0,
            eS,
            ea,
            eb,
#elif G1
            eS,
            ea,
            eb,
#elif G2
            eS,
            eA,
            eB,
            eC,
            ea,
            eb,
            ec,
#elif G3
            eS,
            eA,
            eB,
            ea,
            eb,
#elif G4
            eS, // 5
            eA, // 6
            eB, // 7
            eC, // 8
            ea, // 9
            eb, // 10
            ec, // 11
            ed, // 12
            en, // 13 #
#elif G5
            eS, // 5
            eA, // 6
            eB, // 7
            eC, // 8
            ea, // 9
            eb, // 10
            ec, // 11
            ed, // 12
#endif
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
#if G0
            "eS0",
            "eS",
            "ea",
            "eb"
#elif G1
            "eS",
            "ea",
            "eb"
#elif G2
            "eS",
            "eA",
            "eB",
            "eC",
            "ea",
            "eb",
            "ec"
#elif G3
            "eS",
            "eA",
            "eB",
            "ea",
            "eb",
#elif G4
            "eS",
            "eA",
            "eB",
            "eC",
            "ea",
            "eb",
            "ec",
            "ed",
            "en", // #
#elif G5
            "eS",
            "eA",
            "eB",
            "eC",
            "ea",
            "eb",
            "ec",
            "ed",
#endif
        };
        #endregion // constants

        #region ctor/dtor/finalizer
        public EffSetToken()
        {
        }

        public EffSetToken(int xi_type, int xi_priority) : base(xi_type, xi_priority)
        {
        }
        #endregion ctor/dtor/finalizer

        #region methods
        public override object Clone()
        {
            EffSetToken result = new EffSetToken();

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
            const string name = "ail.net.test.EffSet";
            return name;
        }

        public override string GetTokenName(int xi_token_type)
        {
            return Names[xi_token_type];
        }

        public override int GetTokenSize()
        {
            return (int)ail.net.test.EffSetToken.EType.eSize;;
        }
        #endregion // methods
    }

    public class EffSetLexAnalyzer : ail.net.parser.LexAnalyzer
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
        public EffSetLexAnalyzer(ail.net.test.EffSetToken xi_token_class, ArrayList xi_errors) : base(xi_token_class, xi_errors)
        {
        }
        #endregion ctor/dtor/finalizer

        #region methods
        public override void NextLexemeImpl(int xi_context)
        {
            Prolog();
            // !!! -- generated code -- !!!
#if G0
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
            token = (int)ail.net.test.EffSetToken.EType.ea;

            Next();

            goto _exit;
_q3:
            token = (int)ail.net.test.EffSetToken.EType.eb;

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
#endif
            // !!! -- end of generated code -- !!!
            Epilog();
        }

        public ail.net.parser.Fsa BuildFsa()
        {
            ail.net.parser.Fsa result = new ail.net.parser.Fsa();

            result = result.Nfa2Dfa();
            result = result.Minimize(ail.net.parser.Fsa.EMinimizationMode.ePartition);

            return result;
        }

        public static void GenerateCode(string xi_filename)
        {
            ail.net.framework.Assert.NonEmptyString(xi_filename, "xi_filename");
            test.EffSetLexAnalyzer lexer = new test.EffSetLexAnalyzer(new ail.net.test.EffSetToken(), new ArrayList());
            lexer.GenerateCode(xi_filename, lexer.BuildFsa());
        }
        #endregion // methods
    }

    public class EffSetGrammar : ail.net.parser.Grammar
    {
        public enum EGrammar
        {
#if G0
            eS0_S,
            eS_SaSb,
            eS_e
#elif G1
            eS_SaSb,
            eS_e
#elif G2
            eS_AB,
            eA_Ba,
            eA_e,
            eB_Cb,
            eB_C,
            eC_c,
            eC_e
#elif G3
            eS_AS,
            eS_b,
            eA_SA,
            eA_a
#elif G4
            eS_Ann,
            eA_aAd,
            eA_BC,
            eB_bBc,
            eB_e,
            eC_acC,
            eC_ad
#elif G5
            eS_ABCabcd,
            eA_a,
            eA_e,
            eB_b,
            eB_e,
            eC_c,
            eC_e
#endif            
        }

        public EffSetGrammar()
        {
        }

        public override bool IsCycleFree()
        {
            return false;
        }

        public override void Populate()
        {
            base.Populate();

            StartSymbolId = (int)ail.net.test.EffSetToken.EType.eS;
#if G0
            // S0 -> S
            ail.net.parser.GrammarRule rule = AddRule((int)ail.net.test.EffSetGrammar.EGrammar.eS0_S);
            rule.AddLhsSymbol((int)ail.net.test.EffSetToken.EType.eS0, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "S'");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.eS, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "S");

            // S -> S a S b
            rule = AddRule((int)ail.net.test.EffSetGrammar.EGrammar.eS_SaSb);
            rule.AddLhsSymbol((int)ail.net.test.EffSetToken.EType.eS, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "S");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.eS, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "S");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.ea, ail.net.parser.GrammarSymbol.EType.eTerminal, "a");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.eS, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "S");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.eb, ail.net.parser.GrammarSymbol.EType.eTerminal, "b");

            // S -> e(psilon)
            rule = AddRule((int)ail.net.test.EffSetGrammar.EGrammar.eS_e);
            rule.AddLhsSymbol((int)ail.net.test.EffSetToken.EType.eS, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "S");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.eEpsilon, ail.net.parser.GrammarSymbol.EType.eTerminal, ail.net.parser.GrammarSymbol.kEpsilon);
#elif G1
            // S -> S a S b
            ail.net.parser.GrammarRule rule = AddRule((int)ail.net.test.EffSetGrammar.EGrammar.eS_SaSb);
            rule.AddLhsSymbol((int)ail.net.test.EffSetToken.EType.eS, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "S");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.eS, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "S");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.ea, ail.net.parser.GrammarSymbol.EType.eTerminal, "a");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.eS, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "S");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.eb, ail.net.parser.GrammarSymbol.EType.eTerminal, "b");

            // S -> e(psilon)
            rule = AddRule((int)ail.net.test.EffSetGrammar.EGrammar.eS_e);
            rule.AddLhsSymbol((int)ail.net.test.EffSetToken.EType.eS, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "S");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.eEpsilon, ail.net.parser.GrammarSymbol.EType.eTerminal, ail.net.parser.GrammarSymbol.kEpsilon);
#elif G2
            // S -> A B
            ail.net.parser.GrammarRule rule = AddRule((int)ail.net.test.EffSetGrammar.EGrammar.eS_AB);
            rule.AddLhsSymbol((int)ail.net.test.EffSetToken.EType.eS, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "S");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.eA, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "A");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.eB, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "B");

            // A -> B a
            rule = AddRule((int)ail.net.test.EffSetGrammar.EGrammar.eA_Ba);
            rule.AddLhsSymbol((int)ail.net.test.EffSetToken.EType.eA, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "A");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.eB, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "B");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.ea, ail.net.parser.GrammarSymbol.EType.eTerminal, "a");

            // A -> e(psilon)
            rule = AddRule((int)ail.net.test.EffSetGrammar.EGrammar.eA_e);
            rule.AddLhsSymbol((int)ail.net.test.EffSetToken.EType.eA, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "A");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.eEpsilon, ail.net.parser.GrammarSymbol.EType.eTerminal, ail.net.parser.GrammarSymbol.kEpsilon);

            // B -> C b
            rule = AddRule((int)ail.net.test.EffSetGrammar.EGrammar.eB_Cb);
            rule.AddLhsSymbol((int)ail.net.test.EffSetToken.EType.eB, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "B");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.eC, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "C");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.eb, ail.net.parser.GrammarSymbol.EType.eTerminal, "b");

            // B -> C
            rule = AddRule((int)ail.net.test.EffSetGrammar.EGrammar.eB_C);
            rule.AddLhsSymbol((int)ail.net.test.EffSetToken.EType.eB, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "B");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.eC, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "C");

            // C -> c
            rule = AddRule((int)ail.net.test.EffSetGrammar.EGrammar.eC_c);
            rule.AddLhsSymbol((int)ail.net.test.EffSetToken.EType.eC, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "C");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.ec, ail.net.parser.GrammarSymbol.EType.eTerminal, "c");

            // C -> e(psilon)
            rule = AddRule((int)ail.net.test.EffSetGrammar.EGrammar.eC_e);
            rule.AddLhsSymbol((int)ail.net.test.EffSetToken.EType.eC, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "C");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.eEpsilon, ail.net.parser.GrammarSymbol.EType.eTerminal, ail.net.parser.GrammarSymbol.kEpsilon);
#elif G3
            // S -> A S
            ail.net.parser.GrammarRule rule = AddRule((int)ail.net.test.EffSetGrammar.EGrammar.eS_AS);
            rule.AddLhsSymbol((int)ail.net.test.EffSetToken.EType.eS, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "S");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.eA, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "A");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.eS, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "S");

            // S -> b
            rule = AddRule((int)ail.net.test.EffSetGrammar.EGrammar.eS_b);
            rule.AddLhsSymbol((int)ail.net.test.EffSetToken.EType.eS, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "S");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.eb, ail.net.parser.GrammarSymbol.EType.eTerminal, "b");

            // A -> S A
            rule = AddRule((int)ail.net.test.EffSetGrammar.EGrammar.eA_SA);
            rule.AddLhsSymbol((int)ail.net.test.EffSetToken.EType.eA, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "A");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.eS, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "S");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.eA, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "A");

            // A -> a
            rule = AddRule((int)ail.net.test.EffSetGrammar.EGrammar.eA_a);
            rule.AddLhsSymbol((int)ail.net.test.EffSetToken.EType.eA, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "A");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.ea, ail.net.parser.GrammarSymbol.EType.eTerminal, "a");
#elif G4
            // S -> A # #
            ail.net.parser.GrammarRule rule = AddRule((int)ail.net.test.EffSetGrammar.EGrammar.eS_Ann);
            rule.AddLhsSymbol((int)ail.net.test.EffSetToken.EType.eS, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "S");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.eA, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "A");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.en, ail.net.parser.GrammarSymbol.EType.eTerminal, "#");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.en, ail.net.parser.GrammarSymbol.EType.eTerminal, "#");
            rule.Name = "S -> A # #";

            // A -> a A d
            rule = AddRule((int)ail.net.test.EffSetGrammar.EGrammar.eA_aAd);
            rule.AddLhsSymbol((int)ail.net.test.EffSetToken.EType.eA, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "A");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.ea, ail.net.parser.GrammarSymbol.EType.eTerminal, "a");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.eA, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "A");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.ed, ail.net.parser.GrammarSymbol.EType.eTerminal, "d");
            rule.Name = "A -> a A d";

            // A -> B C
            rule = AddRule((int)ail.net.test.EffSetGrammar.EGrammar.eA_BC);
            rule.AddLhsSymbol((int)ail.net.test.EffSetToken.EType.eA, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "A");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.eB, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "B");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.eC, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "C");
            rule.Name = "A -> B C";

            // B -> b B c
            rule = AddRule((int)ail.net.test.EffSetGrammar.EGrammar.eB_bBc);
            rule.AddLhsSymbol((int)ail.net.test.EffSetToken.EType.eB, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "B");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.eb, ail.net.parser.GrammarSymbol.EType.eTerminal, "b");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.eB, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "B");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.ec, ail.net.parser.GrammarSymbol.EType.eTerminal, "c");
            rule.Name = "B -> b B c";

            // B -> e(psilon)
            rule = AddRule((int)ail.net.test.EffSetGrammar.EGrammar.eB_e);
            rule.AddLhsSymbol((int)ail.net.test.EffSetToken.EType.eB, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "B");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.eEpsilon, ail.net.parser.GrammarSymbol.EType.eTerminal, ail.net.parser.GrammarSymbol.kEpsilon);
            rule.Name = "B -> e(psilon)";

            // C -> a c C
            rule = AddRule((int)ail.net.test.EffSetGrammar.EGrammar.eC_acC);
            rule.AddLhsSymbol((int)ail.net.test.EffSetToken.EType.eC, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "C");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.ea, ail.net.parser.GrammarSymbol.EType.eTerminal, "a");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.ec, ail.net.parser.GrammarSymbol.EType.eTerminal, "c");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.eC, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "C");
            rule.Name = "C -> a c C";

            // C -> a d
            rule = AddRule((int)ail.net.test.EffSetGrammar.EGrammar.eC_ad);
            rule.AddLhsSymbol((int)ail.net.test.EffSetToken.EType.eC, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "C");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.ea, ail.net.parser.GrammarSymbol.EType.eTerminal, "a");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.ed, ail.net.parser.GrammarSymbol.EType.eTerminal, "d");
            rule.Name = "C -> a d";
#elif G5
            // S -> A B C a b c d
            ail.net.parser.GrammarRule rule = AddRule((int)ail.net.test.EffSetGrammar.EGrammar.eS_ABCabcd);
            rule.AddLhsSymbol((int)ail.net.test.EffSetToken.EType.eS, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "S");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.eA, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "A");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.eB, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "B");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.eC, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "C");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.ea, ail.net.parser.GrammarSymbol.EType.eTerminal, "a");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.eb, ail.net.parser.GrammarSymbol.EType.eTerminal, "b");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.ec, ail.net.parser.GrammarSymbol.EType.eTerminal, "c");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.ed, ail.net.parser.GrammarSymbol.EType.eTerminal, "d");
            rule.Name = "S -> A B C a b c d";

            // A -> a
            rule = AddRule((int)ail.net.test.EffSetGrammar.EGrammar.eA_a);
            rule.AddLhsSymbol((int)ail.net.test.EffSetToken.EType.eA, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "A");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.ea, ail.net.parser.GrammarSymbol.EType.eTerminal, "a");
            rule.Name = "A -> a";

            // A -> e(psilon)
            rule = AddRule((int)ail.net.test.EffSetGrammar.EGrammar.eA_e);
            rule.AddLhsSymbol((int)ail.net.test.EffSetToken.EType.eA, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "A");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.eEpsilon, ail.net.parser.GrammarSymbol.EType.eTerminal, ail.net.parser.GrammarSymbol.kEpsilon);
            rule.Name = "A -> e(psilon)";

            // B -> b
            rule = AddRule((int)ail.net.test.EffSetGrammar.EGrammar.eB_b);
            rule.AddLhsSymbol((int)ail.net.test.EffSetToken.EType.eB, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "B");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.eb, ail.net.parser.GrammarSymbol.EType.eTerminal, "b");
            rule.Name = "B -> b";

            // B -> e(psilon)
            rule = AddRule((int)ail.net.test.EffSetGrammar.EGrammar.eB_e);
            rule.AddLhsSymbol((int)ail.net.test.EffSetToken.EType.eB, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "B");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.eEpsilon, ail.net.parser.GrammarSymbol.EType.eTerminal, ail.net.parser.GrammarSymbol.kEpsilon);
            rule.Name = "B -> e(psilon)";

            // C -> c
            rule = AddRule((int)ail.net.test.EffSetGrammar.EGrammar.eC_c);
            rule.AddLhsSymbol((int)ail.net.test.EffSetToken.EType.eC, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "C");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.ec, ail.net.parser.GrammarSymbol.EType.eTerminal, "c");
            rule.Name = "C -> c";

            // C -> e(psilon)
            rule = AddRule((int)ail.net.test.EffSetGrammar.EGrammar.eC_e);
            rule.AddLhsSymbol((int)ail.net.test.EffSetToken.EType.eC, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "C");
            rule.AddRhsSymbol((int)ail.net.test.EffSetToken.EType.eEpsilon, ail.net.parser.GrammarSymbol.EType.eTerminal, ail.net.parser.GrammarSymbol.kEpsilon);
            rule.Name = "C -> e(psilon)";
#endif
            BuildNullabilitySet();

            Console.WriteLine(ail.net.parser.GrammarPool.Instance.DecoratePool());
            Console.WriteLine(Decorate());

            string firstset = null;
            string effset = null;
            string followset = null;

            ClearFirstSet();
            BuildFirstSet();
            firstset = DecorateFirstSet();
            Console.WriteLine(firstset);

            ClearFirstSet();
            ClearFollowSet();
#if G0
            BuildFirstKSet(1);
            firstset = DecorateFirstKSet();
            effset = DecorateEFFirstKSet();
            BuildFollowKSet(1);
            followset = DecorateFollowKSet();
#elif G1
            BuildFirstKSet(1);
            firstset = DecorateFirstKSet();
            effset = DecorateEFFirstKSet();
            BuildFollowKSet(1);
            followset = DecorateFollowKSet();
#elif G2
            BuildFirstKSet(2);
            firstset = DecorateFirstKSet();
            effset = DecorateEFFirstKSet();
            BuildFollowKSet(1);
            followset = DecorateFollowKSet();
#elif G3
            BuildFirstKSet(1);
            firstset = DecorateFirstKSet();
            effset = DecorateEFFirstKSet();
            BuildFollowKSet(1);
            followset = DecorateFollowKSet();
#elif G4
            // FIRST:
            // #:
            //         #
            // d:
            //         d
            // c:
            //         c
            // b:
            //         b
            // a:
            //         a
            // C:
            //         a d    a c
            // B:
            //         ~e~    b c    b b
            // A:
            //         a d    b c    a a    a b    a c    b b
            // S:
            //         a d    b c    a a    a b    a c    b b
            // ~$~:
            //         ~$~
            // ~e~:
            //         ~e~
            // 
            // EFF:
            // #:
            //         #
            // d:
            //         d
            // c:
            //         c
            // b:
            //         b
            // a:
            //         a
            // C:
            //         a d    a c
            // B:
            //         b    b b
            // A:
            //         b a    a b    b b    a a
            // S:
            //         b a    a b    b b    a a
            // ~$~:
            //         ~$~
            // ~e~:
            //         ~e~
            // 
            // FOLLOW:
            // C:
            //         # #    d #    d d
            // B:
            //         a d    a c    c a    c c
            // A:
            //         # #    d #    d d
            // S:
            //         ~e~
            BuildFirstKSet(2);
            firstset = DecorateFirstKSet();
            effset = DecorateEFFirstKSet();
            BuildFollowKSet(2);
            followset = DecorateFollowKSet();
#elif G5
            // FIRST(k=1):                                      // FIRST(k=2):
            // d:                                               // d:
            //         d                                        //         d
            // c:                                               // c:
            //         c                                        //         c
            // b:                                               // b:
            //         b                                        //         b
            // a:                                               // a:
            //         a                                        //         a
            // C:                                               // C:
            //         ~e~    c                                 //         ~e~    c
            // B:                                               // B:
            //         ~e~    b                                 //         ~e~    b
            // A:                                               // A:
            //         ~e~    a                                 //         ~e~    a
            // S:                                               // S:
            //         a    c    b                              //         a b    c a    b a    b c    a a    a c
            // ~$~:                                             // ~$~:
            //         ~$~                                      //         ~$~
            // ~e~:                                             // ~e~:
            //         ~e~                                      //         ~e~
            //                                                  // 
            // EFF(k=1):                                        // EFF(k=2):
            // d:                                               // d:
            //         d                                        //         d
            // c:                                               // c:
            //         c                                        //         c
            // b:                                               // b:
            //         b                                        //         b
            // a:                                               // a:
            //         a                                        //         a
            // C:                                               // C:
            //         c                                        //         c
            // B:                                               // B:
            //         b                                        //         b
            // A:                                               // A:
            //         a                                        //         a
            // S:                                               // S:
            //         a                                        //         a b
            // ~$~:                                             // ~$~:
            //         ~$~                                      //         ~$~
            // ~e~:                                             // ~e~:
            //         ~e~                                      //         ~e~
            //                                                  // 
            // FOLLOW(k=1):                                     // FOLLOW(k=2):
            // C:                                               // C:
            //         a                                        //         a b
            // B:                                               // B:
            //         a    c                                   //         a b    c a
            // A:                                               // A:
            //         a    c    b                              //         a b    c a    b a    b c
            // S:                                               // S:
            //         ~e~                                      //         ~e~
            BuildFirstKSet(2);
            BuildFollowKSet(2);
            firstset  = DecorateFirstKSet();
            effset    = DecorateEFFirstKSet();
            followset = DecorateFollowKSet();
#endif            
            Console.WriteLine("FIRST:");
            Console.WriteLine(firstset);
            Console.WriteLine();
            Console.WriteLine();
            Console.WriteLine("EFF:");
            Console.WriteLine(effset);
            Console.WriteLine();
            Console.WriteLine();
            Console.WriteLine("FOLLOW:");
            Console.WriteLine(followset);
#if G1
            ArrayList symbols = new ArrayList();

            symbols.Add((ail.net.parser.GrammarSymbol)ail.net.parser.GrammarPool.Instance.Pool[(int)ail.net.test.EffSetToken.EType.eS]);
            symbols.Add((ail.net.parser.GrammarSymbol)ail.net.parser.GrammarPool.Instance.Pool[(int)ail.net.test.EffSetToken.EType.ea]);
            symbols.Add((ail.net.parser.GrammarSymbol)ail.net.parser.GrammarPool.Instance.Pool[(int)ail.net.test.EffSetToken.EType.eS]);
            symbols.Add((ail.net.parser.GrammarSymbol)ail.net.parser.GrammarPool.Instance.Pool[(int)ail.net.test.EffSetToken.EType.eb]);
            symbols.Add((ail.net.parser.GrammarSymbol)ail.net.parser.GrammarPool.Instance.Pool[(int)ail.net.test.EffSetToken.EType.eb]);
            symbols.Add((ail.net.parser.GrammarSymbol)ail.net.parser.GrammarPool.Instance.Pool[(int)ail.net.test.EffSetToken.EType.eEpsilon]);

            
            ArrayList eff = BuildEFFirstKSet(symbols, 1);

            effset = DecorateEFFirstKSet(eff);

            Console.WriteLine();
            Console.WriteLine();
            Console.WriteLine(effset);
#endif
        }
    }

    public class EffSetParser : ail.net.parser.LRParser
    {
        public EffSetParser(ail.net.parser.LexAnalyzer xi_lexer, ail.net.parser.Grammar xi_grammar, ArrayList xi_errors)
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

                if(!SaveLR1ActionTable(@"c:\tmp\eff.lr1.actiontable.txt"))
                {
                    Console.WriteLine("Unable save action table.");
                }

                if(!SaveLR1GoToTable(@"c:\tmp\eff.lr1.gototable.txt"))
                {
                    Console.WriteLine("Unable load action table.");
                }

                if(!LoadLR1ActionTable(@"c:\tmp\eff.lr1.actiontable.txt"))
                {
                    Console.WriteLine("Unable load action table.");
                }

                if(!LoadLR1GoToTable(@"c:\tmp\eff.lr1.gototable.txt"))
                {
                    Console.WriteLine("Unable load goto table.");
                }
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
                            
                            key.Id = ((ail.net.parser.GrammarSymbol)rule.Lhs[0]).Id;
                            key.State = (int)stack.Peek();

                            stack.Push(((ail.net.parser.GrammarSymbol)rule.Lhs[0]).Id);

                            action_table_value = (int)GoToTable[key];

                            stack.Push(action_table_value);
                        }
                    }
                }
                else
                {
                    // error procedure
                    Console.WriteLine("error!");
                    HandleError(stack);
                }
            }
        }

        protected void HandleError(Stack xi_stack)
        {
            // panic-mode recovery:
            //  scan down stack until a state 's' with a 'goto' on a particular nonterminal A is found
            //  discard input symbols until a token 'a' is found that can follow A
            //  stack state 'goto[a, A]' and resume normal parsing
            ail.net.framework.Assert.NonNullReference(xi_stack, "xi_stack");
        }
    }

    public class EffSet
    {
        // 0.
        // S' -> S
        // S  -> S a S b 
        // S  -> e(psilon)

        // 1.
        // S -> SaSb 
        // S -> e(psilon)

        // 2.
        // S -> AB
        // A -> Ba
        // A -> e(psilon)
        // B -> Cb
        // B -> C
        // C -> c
        // C -> e(psilon)

        // 3. (check for non-termination in build first!)
        // S -> A S
        // S -> b
        // A -> S A
        // A -> a
        public static void Test()
        {
            // grammar
            ail.net.test.EffSetGrammar grammar = new ail.net.test.EffSetGrammar();
            grammar.Populate();

            // parser
            ArrayList errors = new ArrayList();

            ail.net.test.EffSetLexAnalyzer lexer = new ail.net.test.EffSetLexAnalyzer(new ail.net.test.EffSetToken(), errors);
            lexer.Load("aabb", ail.net.parser.Context.ELoadMedia.eMediaString);

            ail.net.test.EffSetParser parser = new ail.net.test.EffSetParser(lexer, grammar, errors);

            parser.Parse();
        }
    }
}

#region epilog
#endregion

























































