//......................................................................................
// This is a part of UI Soft Library. Copyright © 1989-2006 UI Soft Inc.               .
//......................................................................................
// THIS CODE MAY BE USED, COPIED, STORED, OR DISTRIBUTED ONLY IN ACCORDANCE WITH       .
// A WRITTEN LICENSE AGREEMENT AND WITH THE INCLUSION OF THIS COPYRIGHT NOTICE.        .
//......................................................................................

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
    public class FirstFollowLaKToken : ail.net.parser.Token
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
            ea,
            eb,
            ec,

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
            "eb",
            "ec"
        };
        #endregion // constants

        #region ctor/dtor/finalizer
        public FirstFollowLaKToken()
        {
        }

        public FirstFollowLaKToken(int xi_type, int xi_priority) : base(xi_type, xi_priority)
        {
        }
        #endregion ctor/dtor/finalizer

        #region methods
        public override object Clone()
        {
            FirstFollowLaKToken result = new FirstFollowLaKToken();

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
            const string name = "ail.net.test.FirstFollowLaKToken";
            return name;
        }

        public override string GetTokenName(int xi_token_type)
        {
            return Names[xi_token_type];
        }

        public override int GetTokenSize()
        {
            return (int)ail.net.test.FirstFollowLaKToken.EType.eSize;;
        }
        #endregion // methods
    }

    public class FirstFollowLaKGrammar : ail.net.parser.Grammar
    {
        public enum EGrammar
        {
            eS_Acc,
            eA_bBA, 
            eA_BcAa,
            eA_e,
            eB_acB,
            eB_b
        }

        public FirstFollowLaKGrammar()
        {
        }

        public override bool IsCycleFree()
        {
            return false;
        }

        public override void Populate()
        {
            base.Populate();

            StartSymbolId = (int)ail.net.test.FirstFollowLaKToken.EType.eS;

            // S -> A c c
            ail.net.parser.GrammarRule rule = AddRule((int)ail.net.test.FirstFollowLaKGrammar.EGrammar.eS_Acc);
            rule.AddLhsSymbol((int)ail.net.test.FirstFollowLaKToken.EType.eS, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "S");
            rule.AddRhsSymbol((int)ail.net.test.FirstFollowLaKToken.EType.eA, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "A");
            rule.AddRhsSymbol((int)ail.net.test.FirstFollowLaKToken.EType.ec, ail.net.parser.GrammarSymbol.EType.eTerminal, "c");
            rule.AddRhsSymbol((int)ail.net.test.FirstFollowLaKToken.EType.ec, ail.net.parser.GrammarSymbol.EType.eTerminal, "c");
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");

            // A -> b B A 
            rule = AddRule((int)ail.net.test.FirstFollowLaKGrammar.EGrammar.eA_bBA);
            rule.AddLhsSymbol((int)ail.net.test.FirstFollowLaKToken.EType.eA, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "A");
            rule.AddRhsSymbol((int)ail.net.test.FirstFollowLaKToken.EType.eb, ail.net.parser.GrammarSymbol.EType.eTerminal, "b");
            rule.AddRhsSymbol((int)ail.net.test.FirstFollowLaKToken.EType.eB, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "B");
            rule.AddRhsSymbol((int)ail.net.test.FirstFollowLaKToken.EType.eA, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "A");
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");
            
            // A -> B c A a
            rule = AddRule((int)ail.net.test.FirstFollowLaKGrammar.EGrammar.eA_BcAa);
            rule.AddLhsSymbol((int)ail.net.test.FirstFollowLaKToken.EType.eA, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "A");
            rule.AddRhsSymbol((int)ail.net.test.FirstFollowLaKToken.EType.eB, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "B");
            rule.AddRhsSymbol((int)ail.net.test.FirstFollowLaKToken.EType.ec, ail.net.parser.GrammarSymbol.EType.eTerminal, "c");
            rule.AddRhsSymbol((int)ail.net.test.FirstFollowLaKToken.EType.eA, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "A");
            rule.AddRhsSymbol((int)ail.net.test.FirstFollowLaKToken.EType.ea, ail.net.parser.GrammarSymbol.EType.eTerminal, "a");
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");

            // A -> e
            rule = AddRule((int)ail.net.test.FirstFollowLaKGrammar.EGrammar.eA_e);
            rule.AddLhsSymbol((int)ail.net.test.FirstFollowLaKToken.EType.eA, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "A");
            rule.AddRhsSymbol((int)ail.net.test.EpsToken.EType.eEpsilon, ail.net.parser.GrammarSymbol.EType.eTerminal, ail.net.parser.GrammarSymbol.kEpsilon);
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");


            // B -> a c B
            rule = AddRule((int)ail.net.test.FirstFollowLaKGrammar.EGrammar.eB_acB);
            rule.AddLhsSymbol((int)ail.net.test.FirstFollowLaKToken.EType.eB, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "B");
            rule.AddRhsSymbol((int)ail.net.test.FirstFollowLaKToken.EType.ea, ail.net.parser.GrammarSymbol.EType.eTerminal, "a");
            rule.AddRhsSymbol((int)ail.net.test.FirstFollowLaKToken.EType.ec, ail.net.parser.GrammarSymbol.EType.eTerminal, "c");
            rule.AddRhsSymbol((int)ail.net.test.FirstFollowLaKToken.EType.eB, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "B");
            ail.net.framework.Assert.NonNullReference(rule.Lhs[0], "rule.Lhs[0]");
            ail.net.framework.Assert.NonNullReference(rule.Rhs[0], "rule.Rhs[0]");

            // B -> b
            rule = AddRule((int)ail.net.test.FirstFollowLaKGrammar.EGrammar.eB_b);
            rule.AddLhsSymbol((int)ail.net.test.FirstFollowLaKToken.EType.eB, ail.net.parser.GrammarSymbol.EType.eNonTerminal, "B");
            rule.AddRhsSymbol((int)ail.net.test.FirstFollowLaKToken.EType.eb, ail.net.parser.GrammarSymbol.EType.eTerminal, "b");
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

            // S: cc; ba; bb; ac; bc
            // A: e; ac; ba; bb; bc
            // B: ac, b
            ClearFirstSet();
            BuildFirstKSet(2);
            firstset = DecorateFirstKSet();
            Console.WriteLine(firstset);
        }
    }

    public class FirstFollowLaK
    {
        // S -> A c c
        // A -> b B A 
        // A -> B c A a
        // A -> e
        // B -> a c B
        // B -> b
        public static void Test()
        {
            // grammar
            ail.net.test.FirstFollowLaKGrammar grammar = new ail.net.test.FirstFollowLaKGrammar();
            grammar.Populate();
        }
    }
}

#region epilog
#endregion
