//......................................................................................
// This is a part of UI Soft Library. Copyright © 1989-2006 UI Soft Inc.               .
//......................................................................................
// THIS CODE MAY BE USED, COPIED, STORED, OR DISTRIBUTED ONLY IN ACCORDANCE WITH       .
// A WRITTEN LICENSE AGREEMENT AND WITH THE INCLUSION OF THIS COPYRIGHT NOTICE.        .
//......................................................................................

#region prolog
// file       : 
// description: First3KSudkamp
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
    public class First3KSudkampToken : ail.net.parser.Token
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
        public First3KSudkampToken()
        {
        }

        public First3KSudkampToken(int xi_type, int xi_priority) : base(xi_type, xi_priority)
        {
        }
        #endregion ctor/dtor/finalizer

        #region methods
        public override object Clone()
        {
            First3KSudkampToken result = new First3KSudkampToken();

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
            const string name = "ail.net.test.First3KSudkampToken";
            return name;
        }

        public override string GetTokenName(int xi_token_type)
        {
            return Names[xi_token_type];
        }

        public override int GetTokenSize()
        {
            return (int)ail.net.test.First3KSudkampToken.EType.eSize;;
        }
        #endregion // methods
    }

    public class First3KSudkampGrammar : ail.net.parser.Grammar
    {
        public enum EGrammar
        {
            eS_Aabd,
            eS_cAbcd,
            eA_a,
            eA_b,
            eA_e
        }

        public First3KSudkampGrammar()
        {
        }

        public override bool IsCycleFree()
        {
            return false;
        }

        public override void Populate()
        {
            base.Populate();

            StartSymbolId = (int)ail.net.test.First3KSudkampToken.EType.eS;

            // S -> A a b d
            ail.net.parser.GrammarRule rule = AddRule((int)ail.net.test.First3KSudkampGrammar.EGrammar.eS_Aabd);
            rule.AddLhsSymbol((int)ail.net.test.First3KSudkampToken.EType.eS, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "S");
            rule.AddRhsSymbol((int)ail.net.test.First3KSudkampToken.EType.eA, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "A");
            rule.AddRhsSymbol((int)ail.net.test.First3KSudkampToken.EType.ea, ail.net.parser.GrammarSymbol.EType.eTerminal, "a");
            rule.AddRhsSymbol((int)ail.net.test.First3KSudkampToken.EType.eb, ail.net.parser.GrammarSymbol.EType.eTerminal, "b");
            rule.AddRhsSymbol((int)ail.net.test.First3KSudkampToken.EType.ed, ail.net.parser.GrammarSymbol.EType.eTerminal, "d");
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");

            // S -> c A b c d
            rule = AddRule((int)ail.net.test.First3KSudkampGrammar.EGrammar.eS_cAbcd);
            rule.AddLhsSymbol((int)ail.net.test.First3KSudkampToken.EType.eS, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "S");
            rule.AddRhsSymbol((int)ail.net.test.First3KSudkampToken.EType.ec, ail.net.parser.GrammarSymbol.EType.eTerminal, "c");
            rule.AddRhsSymbol((int)ail.net.test.First3KSudkampToken.EType.eA, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "A");
            rule.AddRhsSymbol((int)ail.net.test.First3KSudkampToken.EType.eb, ail.net.parser.GrammarSymbol.EType.eTerminal, "b");
            rule.AddRhsSymbol((int)ail.net.test.First3KSudkampToken.EType.ec, ail.net.parser.GrammarSymbol.EType.eTerminal, "c");
            rule.AddRhsSymbol((int)ail.net.test.First3KSudkampToken.EType.ed, ail.net.parser.GrammarSymbol.EType.eTerminal, "d");
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");

            // A -> a
            rule = AddRule((int)ail.net.test.First3KSudkampGrammar.EGrammar.eA_a);
            rule.AddLhsSymbol((int)ail.net.test.First3KSudkampToken.EType.eA, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "A");
            rule.AddRhsSymbol((int)ail.net.test.First3KSudkampToken.EType.ea, ail.net.parser.GrammarSymbol.EType.eTerminal, "a");
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");

            // A -> b
            // A -> e
            rule = AddRule((int)ail.net.test.First3KSudkampGrammar.EGrammar.eA_b);
            rule.AddLhsSymbol((int)ail.net.test.First3KSudkampToken.EType.eA, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "A");
            rule.AddRhsSymbol((int)ail.net.test.First3KSudkampToken.EType.eb, ail.net.parser.GrammarSymbol.EType.eTerminal, "b");
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");

            // A -> e
            rule = AddRule((int)ail.net.test.First3KSudkampGrammar.EGrammar.eA_e);
            rule.AddLhsSymbol((int)ail.net.test.First3KSudkampToken.EType.eA, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "A");
            rule.AddRhsSymbol((int)ail.net.test.EpsToken.EType.eEpsilon, ail.net.parser.GrammarSymbol.EType.eTerminal, ail.net.parser.GrammarSymbol.kEpsilon);

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

            // S: aab; bab; abd; cab; cbb; cbc
            // A: e; a; b
        

            // FIRST:
            // d:
            //         d
            // c:
            //         c
            // b:
            //         b
            // a:
            //         a
            // A:
            //         ~e~    a    b
            // S:
            //         a b d    a a b    b a b    c b c    c a b    c b b
            // ~$~:
            //         ~$~
            // ~e~:
            //         ~e~

            // FOLLOW:
            // A:
            //         a b d    b c d
            // S:
            //         ~e~
            ClearFirstSet();
            ClearFollowSet();
            BuildFirstKSet(3);
            Console.WriteLine(DecorateFirstKSet());
            BuildFollowKSet(3);
            Console.WriteLine(DecorateFollowKSet());
        }
    }

    public class First3KSudkamp
    {
        // S -> A a b d
        // S -> c A b c d
        // A -> a
        // A -> b
        // A -> e
        public static void Test()
        {
            // grammar
            ail.net.test.First3KSudkampGrammar grammar = new ail.net.test.First3KSudkampGrammar();
            grammar.Populate();
        }
    }
}

#region epilog
#endregion
