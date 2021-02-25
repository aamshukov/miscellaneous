//......................................................................................
// This is a part of UI Soft Library. Copyright © 1989-2006 UI Soft Inc.               .
//......................................................................................
// THIS CODE MAY BE USED, COPIED, STORED, OR DISTRIBUTED ONLY IN ACCORDANCE WITH       .
// A WRITTEN LICENSE AGREEMENT AND WITH THE INCLUSION OF THIS COPYRIGHT NOTICE.        .
//......................................................................................
#region prolog
// file       : 
// description: FirstKSudkamp
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
    public class FirstKSudkampToken : ail.net.parser.Token
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

            eS,
            eA,
            eB,
            eC,
            ea,
            eb,
            ec,
            ed,

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
            "eC",
            "ea",
            "eb",
            "ec",
            "ed"
    };
        #endregion // constants

        #region ctor/dtor/finalizer
        public FirstKSudkampToken()
        {
        }

        public FirstKSudkampToken(int xi_type, int xi_priority) : base(xi_type, xi_priority)
        {
        }
        #endregion ctor/dtor/finalizer

        #region methods
        public override object Clone()
        {
            FirstKSudkampToken result = new FirstKSudkampToken();

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
            const string name = "ail.net.test.FirstKSudkampToken";
            return name;
        }

        public override string GetTokenName(int xi_token_type)
        {
            return Names[xi_token_type];
        }

        public override int GetTokenSize()
        {
            return (int)ail.net.test.FirstKSudkampToken.EType.eSize;;
        }
        #endregion // methods
    }

    public class FirstKSudkampGrammar : ail.net.parser.Grammar
    {
        public enum EGrammar
        {
            eS_A,
            eA_aAd,
            eA_BC,
            eB_bBc,
            eB_e,
            eC_acC,
            eC_ad
        }

        public FirstKSudkampGrammar()
        {
        }

        public override bool IsCycleFree()
        {
            return false;
        }

        public override void Populate()
        {
            base.Populate();

            StartSymbolId = (int)ail.net.test.FirstKSudkampToken.EType.eS;

            // S -> A
            ail.net.parser.GrammarRule rule = AddRule((int)ail.net.test.FirstKSudkampGrammar.EGrammar.eS_A);
            rule.AddLhsSymbol((int)ail.net.test.FirstKSudkampToken.EType.eS, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "S");
            rule.AddRhsSymbol((int)ail.net.test.FirstKSudkampToken.EType.eA, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "A");
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");

            // A -> a A d
            rule = AddRule((int)ail.net.test.FirstKSudkampGrammar.EGrammar.eA_aAd);
            rule.AddLhsSymbol((int)ail.net.test.FirstKSudkampToken.EType.eA, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "A");
            rule.AddRhsSymbol((int)ail.net.test.FirstKSudkampToken.EType.ea, ail.net.parser.GrammarSymbol.EType.eTerminal, "a");
            rule.AddRhsSymbol((int)ail.net.test.FirstKSudkampToken.EType.eA, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "A");
            rule.AddRhsSymbol((int)ail.net.test.FirstKSudkampToken.EType.ed, ail.net.parser.GrammarSymbol.EType.eTerminal, "d");
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");
            
            // A -> B C
            rule = AddRule((int)ail.net.test.FirstKSudkampGrammar.EGrammar.eA_BC);
            rule.AddLhsSymbol((int)ail.net.test.FirstKSudkampToken.EType.eA, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "A");
            rule.AddRhsSymbol((int)ail.net.test.FirstKSudkampToken.EType.eB, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "B");
            rule.AddRhsSymbol((int)ail.net.test.FirstKSudkampToken.EType.eC, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "C");
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");

            // B -> b B c
            rule = AddRule((int)ail.net.test.FirstKSudkampGrammar.EGrammar.eB_bBc);
            rule.AddLhsSymbol((int)ail.net.test.FirstKSudkampToken.EType.eB, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "B");
            rule.AddRhsSymbol((int)ail.net.test.FirstKSudkampToken.EType.eb, ail.net.parser.GrammarSymbol.EType.eTerminal, "b");
            rule.AddRhsSymbol((int)ail.net.test.FirstKSudkampToken.EType.eB, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "B");
            rule.AddRhsSymbol((int)ail.net.test.FirstKSudkampToken.EType.ec, ail.net.parser.GrammarSymbol.EType.eTerminal, "c");
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");

            // B -> e
            rule = AddRule((int)ail.net.test.FirstKSudkampGrammar.EGrammar.eB_e);
            rule.AddLhsSymbol((int)ail.net.test.FirstKSudkampToken.EType.eB, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "B");
            rule.AddRhsSymbol((int)ail.net.test.EpsToken.EType.eEpsilon, ail.net.parser.GrammarSymbol.EType.eTerminal, ail.net.parser.GrammarSymbol.kEpsilon);

            // C -> a c C
            rule = AddRule((int)ail.net.test.FirstKSudkampGrammar.EGrammar.eC_acC);
            rule.AddLhsSymbol((int)ail.net.test.FirstKSudkampToken.EType.eC, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "C");
            rule.AddRhsSymbol((int)ail.net.test.FirstKSudkampToken.EType.ea, ail.net.parser.GrammarSymbol.EType.eTerminal, "a");
            rule.AddRhsSymbol((int)ail.net.test.FirstKSudkampToken.EType.ec, ail.net.parser.GrammarSymbol.EType.eTerminal, "c");
            rule.AddRhsSymbol((int)ail.net.test.FirstKSudkampToken.EType.eC, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "C");
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");

            // C -> a d
            rule = AddRule((int)ail.net.test.FirstKSudkampGrammar.EGrammar.eC_ad);
            rule.AddLhsSymbol((int)ail.net.test.FirstKSudkampToken.EType.eC, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "C");
            rule.AddRhsSymbol((int)ail.net.test.FirstKSudkampToken.EType.ea, ail.net.parser.GrammarSymbol.EType.eTerminal, "a");
            rule.AddRhsSymbol((int)ail.net.test.FirstKSudkampToken.EType.ed, ail.net.parser.GrammarSymbol.EType.eTerminal, "d");
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");

            BuildNullabilitySet();

            Console.WriteLine(ail.net.parser.GrammarPool.Instance.DecoratePool());
            Console.WriteLine(Decorate());

            ClearFirstSet();
            BuildFirstSet();
            string firstset = DecorateFirstSet();
            Console.WriteLine(firstset);

            ClearFirstSet();
            BuildFirstKSet(1);
            firstset = DecorateFirstKSet();
            Console.WriteLine(firstset);

            // S: ad; bc; aa; ab; bb; ac
            // A: ad; bc; aa; ab; bb; ac
            // B: e; bc; bb
            // C: ad; ac
            Console.WriteLine();
            Console.WriteLine();
            Console.WriteLine();
            Console.WriteLine();
            ClearFirstSet();
//            BuildFirstKSet(0);
//            firstset = DecorateFirstKSet();
            Console.WriteLine(firstset);
            Console.WriteLine();
            Console.WriteLine();
            Console.WriteLine();
            Console.WriteLine();
            ClearFirstSet();
            BuildFirstKSet(2);
            firstset = DecorateFirstKSet();
            Console.WriteLine(firstset);
            Console.WriteLine();
            Console.WriteLine();

            //
            Console.WriteLine();
            Console.WriteLine();
            Console.WriteLine();
            Console.WriteLine();
            ClearFollowSet();
            BuildFollowKSet(2);
            string followset = DecorateFollowKSet();
            Console.WriteLine("FOLLOW:");
            Console.WriteLine(followset);
            Console.WriteLine();
            Console.WriteLine();
        }
    }

    public class FirstKSudkamp
    {
        // S -> A
        // A -> a A d
        // A -> B C
        // B -> b B c
        // B -> e
        // C -> a c C
        // C -> a d
        public static void Test()
        {
            // grammar
            ail.net.test.FirstKSudkampGrammar grammar = new ail.net.test.FirstKSudkampGrammar();
            grammar.Populate();
        }
    }
}

#region epilog
#endregion
