#include <pch.hpp>
#include <semantics.hpp>
#include <cpptoken.hpp>
#include <cpplexanalyser.hpp>
#include <earley.hpp>
#include <cppparser.hpp>
#include <exceltoken.hpp>
#include <excelgrammar.hpp>
#include <excellexanalyser.hpp>
#include <excelast.hpp>
#include <excelsemantics.hpp>
#include <excelparser.hpp>

#define __aho__     0
#define __aAa__     0
#define __SSx__     0
#define __SSaeps__  1

__BEGIN_NAMESPACE__

class TestToken : public Token
{
	public:

	enum EType
	{
        // the following five (5) entries, MUST be the first entries in the enum
        eUnknown = 0,
        eEpsilon,
        eEndOfStream,
        eStartSymbol,
        eWhiteSpace,

        S, S0, S1, A, A0, B, B1, C, D, D0, E, E0, L, E1, P, R, R0, F, F0, Q, T, T1, a, b, c, d, e, g, f, h, j, i, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z,
        //                                    10                                20                             30                            40                47
        eSize
    };

	const wchar* GetTokenName(int _token) const
	{
		static const wchar* names[] =
		{
			L"eUnknown",
			L"eEpsilon",
			L"eEndOfStream",
			L"eStartSymbol",
			L"eWhiteSpace",

			L"S", L"S0", L"S1", L"A", L"A0", L"B", L"B1", L"C", L"D", L"D0", L"E", L"E0", L"L", L"E1", L"P", L"R", L"R0", L"F", L"F0", L"Q", L"T", L"T1", L"a", L"b", L"c", L"d", L"e", L"g", L"f", L"h", L"j", L"i", L"k", L"l", L"m", L"n", L"o", L"p", L"q", L"r", L"s", L"t", L"u", L"v", L"w", L"x", L"y", L"z",
		};
		return names[_token];
	}

    enum EContext
    {
		eContextUnknown,
    };

	public:
        TestToken::TestToken()
        {
        }

};

class TestLexAnalyser : public LexAnalyser
{
    private:
		TestToken	Token;
		int			Index;
    public:
        TestLexAnalyser(_Context& _context, _Errors& _errors)
            : LexAnalyser(_context, Token, _errors),
              Index(0)
        {
        }

       ~TestLexAnalyser()
        {
        }

        bool NextLexeme(int = TestToken::eContextUnknown)
        {
            PROLOG(TestToken)

            if(CURRENT == '(')
            {
                NEXT
                TOKEN(TestToken::l);
                goto _exit;
            }
            else if(CURRENT == ')')
            {
                NEXT
                TOKEN(TestToken::r);
                goto _exit;
            }
            else if(CURRENT == 'n')
            {
                NEXT
                TOKEN(TestToken::n);
                goto _exit;
            }
            else if(CURRENT == 'a')
            {
                NEXT
                TOKEN(TestToken::a);
                goto _exit;
            }
            else if(CURRENT == 'x')
            {
                NEXT
                TOKEN(TestToken::x);
                goto _exit;
            }
            else if(CURRENT == 'b')
            {
                NEXT
                TOKEN(TestToken::b);
                goto _exit;
            }
            else if(CURRENT == '+')
            {
                NEXT
                TOKEN(TestToken::p);
                goto _exit;
            }
            else if(CURRENT == '*')
            {
                NEXT
                TOKEN(TestToken::m);
                goto _exit;
            }

            EPILOG(TestToken)
//            return *Pointer != 0;
        }
};

class TestGrammar : public Grammar
{
    enum ERule
    {		
        eRuleSS,
		eRuleSa,
		eRuleSepsilon
	};

	public:
        TestGrammar()
        {
        }

       ~TestGrammar()
        {
        }

        void Populate()
        {
            // S1 -> E
            // E  -> E + E
            // E  -> n
/*
            SetStartSymbolId(TestToken::S1);

            Grammar::Rule* newrule = AddRule();
            (*newrule).AddLhsSymbol(TestToken::S1, String(L"S'"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::E, String(L"E"), Grammar::eNonTerminal);

            newrule = AddRule();
            (*newrule).AddLhsSymbol(TestToken::E, String(L"E"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::E, String(L"E"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::p, String(L"+"), Grammar::eTerminal);
            (*newrule).AddRhsSymbol(TestToken::E, String(L"E"), Grammar::eNonTerminal);

            newrule = AddRule();
            (*newrule).AddLhsSymbol(TestToken::E, String(L"E"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::n, String(L"n"), Grammar::eTerminal);
*/
            // S1 -> E
            // E -> T + E
            // E -> T
            // T -> F * T
            // T -> F
            // F -> ( E )
            // F -> a
#if __aho__ == 1
            SetStartSymbolId(TestToken::E);

            Grammar::Rule* newrule = AddRule();
            (*newrule).AddLhsSymbol(TestToken::E, String(L"E"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::T, String(L"T"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::p, String(L"+"), Grammar::eTerminal);
            (*newrule).AddRhsSymbol(TestToken::E, String(L"E"), Grammar::eNonTerminal);

            newrule = AddRule();
            (*newrule).AddLhsSymbol(TestToken::E, String(L"E"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::T, String(L"T"), Grammar::eNonTerminal);

            newrule = AddRule();
            (*newrule).AddLhsSymbol(TestToken::T, String(L"T"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::F, String(L"F"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::m, String(L"*"), Grammar::eTerminal);
            (*newrule).AddRhsSymbol(TestToken::T, String(L"T"), Grammar::eNonTerminal);

            newrule = AddRule();
            (*newrule).AddLhsSymbol(TestToken::T, String(L"T"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::F, String(L"F"), Grammar::eNonTerminal);

            newrule = AddRule();
            (*newrule).AddLhsSymbol(TestToken::F, String(L"F"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::l, String(L"("), Grammar::eTerminal);
            (*newrule).AddRhsSymbol(TestToken::E, String(L"E"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::r, String(L")"), Grammar::eTerminal);

            newrule = AddRule();
            (*newrule).AddLhsSymbol(TestToken::F, String(L"F"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::a, String(L"a"), Grammar::eTerminal);
#endif
            // S1 -> S
            // S -> A A A A
            // A -> a
            // A -> E
            // E -> e
/*
            SetStartSymbolId(TestToken::S1);

            Grammar::Rule* newrule = AddRule();
            (*newrule).AddLhsSymbol(TestToken::S1, String(L"S'"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::S, String(L"S"), Grammar::eNonTerminal);

            newrule = AddRule();
            (*newrule).AddLhsSymbol(TestToken::S, String(L"S"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::A, String(L"A"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::A, String(L"A"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::A, String(L"A"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::A, String(L"A"), Grammar::eNonTerminal);

            newrule = AddRule();
            (*newrule).AddLhsSymbol(TestToken::A, String(L"A"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::a, String(L"a"), Grammar::eTerminal);

            newrule = AddRule();
            (*newrule).AddLhsSymbol(TestToken::A, String(L"A"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::E, String(L"E"), Grammar::eNonTerminal);

            newrule = AddRule();
            (*newrule).AddLhsSymbol(TestToken::E, String(L"E"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::eEpsilon, Grammar::Epsilon(), Grammar::eTerminal);
*/
            // S1 -> S
            // S -> a
            // S -> SS
/*
            SetStartSymbolId(TestToken::S1);

            Grammar::Rule* newrule = AddRule();
            (*newrule).AddLhsSymbol(TestToken::S1, String(L"S'"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::S, String(L"S"), Grammar::eNonTerminal);

            newrule = AddRule();
            (*newrule).AddLhsSymbol(TestToken::S, String(L"S"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::a, String(L"a"), Grammar::eTerminal);

            newrule = AddRule();
            (*newrule).AddLhsSymbol(TestToken::S, String(L"S"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::S, String(L"S"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::S, String(L"S"), Grammar::eNonTerminal);
*/
            // S -> Sa
            // S -> b
/*
            SetStartSymbolId(TestToken::S);

            Grammar::Rule* newrule = AddRule();
            (*newrule).AddLhsSymbol(TestToken::S, String(L"S"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::S, String(L"S"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::a, String(L"a"), Grammar::eTerminal);

            newrule = AddRule();
            (*newrule).AddLhsSymbol(TestToken::S, String(L"S"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::b, String(L"b"), Grammar::eTerminal);
*/
            // right grammar
            // E -> T
            // E -> T + E
            // T -> F
            // T -> F * T
            // F -> i --- identifier
            //
            // left grammar
            // E -> T
            // E -> E + T
            // T -> F
            // T -> T * F
            // F -> i --- identifier
/*
            SetStartSymbolId(TestToken::E);

            Grammar::Rule* newrule = AddRule();
            (*newrule).AddLhsSymbol(TestToken::E, String(L"E"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::T, String(L"T"), Grammar::eNonTerminal);

            newrule = AddRule();
            (*newrule).AddLhsSymbol(TestToken::E, String(L"E"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::T, String(L"T"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::p, String(L"+"), Grammar::eTerminal);
            (*newrule).AddRhsSymbol(TestToken::E, String(L"E"), Grammar::eNonTerminal);

            newrule = AddRule();
            (*newrule).AddLhsSymbol(TestToken::T, String(L"T"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::F, String(L"F"), Grammar::eNonTerminal);

            newrule = AddRule();
            (*newrule).AddLhsSymbol(TestToken::T, String(L"T"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::F, String(L"F"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::m, String(L"*"), Grammar::eTerminal);
            (*newrule).AddRhsSymbol(TestToken::T, String(L"T"), Grammar::eNonTerminal);

            newrule = AddRule();
            (*newrule).AddLhsSymbol(TestToken::F, String(L"F"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::a, String(L"a"), Grammar::eTerminal);
*/
            // left
/*
            Grammar::Rule* newrule = AddRule();
            (*newrule).AddLhsSymbol(TestToken::E, String(L"E"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::T, String(L"T"), Grammar::eNonTerminal);

            newrule = AddRule();
            (*newrule).AddLhsSymbol(TestToken::E, String(L"E"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::E, String(L"E"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::p, String(L"+"), Grammar::eTerminal);
            (*newrule).AddRhsSymbol(TestToken::T, String(L"T"), Grammar::eNonTerminal);

            newrule = AddRule();
            (*newrule).AddLhsSymbol(TestToken::T, String(L"T"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::F, String(L"F"), Grammar::eNonTerminal);

            newrule = AddRule();
            (*newrule).AddLhsSymbol(TestToken::T, String(L"T"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::T, String(L"T"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::m, String(L"*"), Grammar::eTerminal);
            (*newrule).AddRhsSymbol(TestToken::F, String(L"F"), Grammar::eNonTerminal);

            newrule = AddRule();
            (*newrule).AddLhsSymbol(TestToken::F, String(L"F"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::a, String(L"a"), Grammar::eTerminal);
*/
            // S -> SS
            // S -> x
#if __SSx__ == 1
            SetStartSymbolId(TestToken::S);

            Grammar::Rule* newrule = AddRule();
            (*newrule).AddLhsSymbol(TestToken::S, String(L"S"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::S, String(L"S"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::S, String(L"S"), Grammar::eNonTerminal);

            newrule = AddRule();
            (*newrule).AddLhsSymbol(TestToken::S, String(L"S"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::a, String(L"a"), Grammar::eTerminal);
#endif
            // A -> a A a
            // A -> L 
            // L -> a
            // L -> e
#if __aAa__ == 1
            SetStartSymbolId(TestToken::A);

            Grammar::Rule* newrule = AddRule();
            (*newrule).AddLhsSymbol(TestToken::A, String(L"A"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::a, String(L"a"), Grammar::eTerminal);
            (*newrule).AddRhsSymbol(TestToken::A, String(L"A"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::a, String(L"a"), Grammar::eTerminal);

            newrule = AddRule();
            (*newrule).AddLhsSymbol(TestToken::A, String(L"A"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::L, String(L"L"), Grammar::eNonTerminal);

            newrule = AddRule();
            (*newrule).AddLhsSymbol(TestToken::L, String(L"L"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::a, String(L"a"), Grammar::eTerminal);

            newrule = AddRule();
            (*newrule).AddLhsSymbol(TestToken::L, String(L"L"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::eEpsilon, Grammar::Epsilon(), Grammar::eTerminal);
#endif
			// S -> S
			// S -> a 
			// S -> epsilon 
#if __SSaeps__ == 1
			SetStartSymbolId(TestToken::S);

			Grammar::Rule* newrule = AddRule(eRuleSS);
			(*newrule).AddLhsSymbol(TestToken::S, String(L"S"), Grammar::eNonTerminal);
			(*newrule).AddRhsSymbol(TestToken::S, String(L"S"), Grammar::eNonTerminal);

			newrule = AddRule(eRuleSa);
			(*newrule).AddLhsSymbol(TestToken::S, String(L"S"), Grammar::eNonTerminal);
			(*newrule).AddRhsSymbol(TestToken::a, String(L"a"), Grammar::eTerminal);
			
			newrule = AddRule(eRuleSepsilon);
			(*newrule).AddLhsSymbol(TestToken::S, String(L"S"), Grammar::eNonTerminal);
			(*newrule).AddRhsSymbol(TestToken::eEpsilon, Grammar::Epsilon(), Grammar::eTerminal);
#endif
        }
};

class TestEarleyParser : public EarleyParser
{
    typedef TestLexAnalyser _Lexer;
    typedef TestGrammar     _Grammar;
    typedef TestToken       _Token;

    private:
       _Context Context;
       _Lexer   Lexer;
       _Token   Token;
       _Grammar Grammar;
       _Errors  Errors;
    public:
		TestEarleyParser() : EarleyParser(Context, Lexer, Grammar, Token, Errors),
		                     Lexer(Context, Errors)
		{
//            String text(L"n+n");
#if __aho__ == 1
            StringBuilder btext(L"(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a");
/*
            btext += L"*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a";
            btext += L"*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a";
            btext += L"*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a";
            btext += L"*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a";
            btext += L"*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a";
            btext += L"*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a";
            btext += L"*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a";
            btext += L"*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a";
            btext += L"*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a";
            btext += L"*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a*(a+a)*a";
*/
            String text(btext.ToString());
#endif
//            String text(btext.ToString());
//            int l = text.GetLength();
//            String text(L"a");
//              String text(L"aaa");
//            String text(L"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
/*
            StringBuilder itext(L"a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a");
            itext += L"+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a";
            itext += L"+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a";
            itext += L"+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a";
            itext += L"+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a";
            itext += L"+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a";
            itext += L"+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a";
            itext += L"+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a";
            itext += L"+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a";
            itext += L"+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a";
            itext += L"+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a+a*a+a";
            String text(itext.ToString());
            int len = text.GetLength();
*/
//            String text(L"xxx");
#if __aAa__ == 1
            String text(L"aa");
#endif
#if __SSx__ == 1
            String text(L"aaa");
#endif
#if __SSaeps__ == 1
            String text(L"a");
#endif
            Context.Allocate(text.GetLength());
            wcscpy(Context.GetData(), text.Cstr());
            Lexer.Reset();
		}

        void Initialize()
        {
            Grammar.Populate();
            Grammar.BuildNullabilitySet();
            Grammar.Print();
        }

        void Parse()
        {
            EarleyParser::Parse();
            EarleyParser::PrintTrees();
        }

        int GetTokenElementNumber() const
        {
            return TestToken::eSize;
        }
};
/*
class Grammar1 : public Grammar
	{
	public:
		Grammar1()
			{
			}

		~Grammar1()
			{
			}

		void Populate()
		{
			// A -> B
			// B -> C 
			// B -> D
			// C -> a
			// D -> a
			
			SetStartSymbolId(TestToken::A);

			Grammar::Rule* newrule = AddRule();
			(*newrule).AddLhsSymbol(TestToken::A, String(L"A"), Grammar::eNonTerminal);
			(*newrule).AddRhsSymbol(TestToken::B, String(L"B"), Grammar::eNonTerminal);

			newrule = AddRule();
			(*newrule).AddLhsSymbol(TestToken::B, String(L"B"), Grammar::eNonTerminal);
			(*newrule).AddRhsSymbol(TestToken::C, String(L"C"), Grammar::eNonTerminal);

			newrule = AddRule();
			(*newrule).AddLhsSymbol(TestToken::B, String(L"B"), Grammar::eNonTerminal);
			(*newrule).AddRhsSymbol(TestToken::D, String(L"D"), Grammar::eNonTerminal);

			newrule = AddRule();
			(*newrule).AddLhsSymbol(TestToken::C, String(L"C"), Grammar::eNonTerminal);
			(*newrule).AddRhsSymbol(TestToken::a, String(L"a"), Grammar::eTerminal);
			
			newrule = AddRule();
			(*newrule).AddLhsSymbol(TestToken::D, String(L"D"), Grammar::eNonTerminal);
			(*newrule).AddRhsSymbol(TestToken::a, String(L"a"), Grammar::eTerminal);
		}
	};

class Parser1 : public EarleyParser, public EarleyParser::ISemantic
{
	typedef TestLexAnalyser _Lexer;
	typedef Grammar1     _Grammar;
	typedef TestToken       _Token;

	private:
		_Context Context;
		_Lexer   Lexer;
		_Token   Token;
		_Grammar Grammar;
		_Errors  Errors;
	public:
		Parser1() : EarleyParser(Context, Lexer, Grammar, Token, Errors),
			Lexer(Context, Errors)
			{

				SetSemantics(this);

			String text(L"a");

			Context.Allocate(text.GetLength());
			wcscpy(Context.GetData(), text.Cstr());
			Lexer.Reset();
			}

		void Initialize()
			{
			Grammar.Populate();
			Grammar.BuildNullabilitySet();
			Grammar.Print();
			}

		void Parse()
			{
			EarleyParser::ParseAst();
			}

		int GetTokenElementNumber() const
			{
			return TestToken::eSize;
			}


		// the termianl action
		void HandleTerminal(EarleyParser::_Ast&, EarleyParser::_AstNode*&, EarleyParser::_Token&)
		{
			
		}

		// the nonterminal action
		bool HandleNonterminal(EarleyParser::_Ast&, EarleyParser::_AstNode*&, EarleyParser::_Item* _item)
		{
			PrintItem(*_item);
			return true;
		}

		EarleyParser::_AstNode* Start(EarleyParser::_Ast&, EarleyParser::_Item* _item)
		{
			wprintf( L"start\n" );
			PrintItem( *_item );

			return (EarleyParser::_AstNode*)1;
		}
		
		void End(EarleyParser::_Ast& _ast)
		{
		
		}
};
*/


class Grammar1 : public Grammar
	{
        enum ERule
        {
            eRuleEEE,
            eRuleEa
        };
	public:
		Grammar1()
			{
			}

		~Grammar1()
			{
			}

		void Populate()
		{
			// E -> E + E
			// E -> a 
			
			SetStartSymbolId(TestToken::E);

			Grammar::Rule* newrule = AddRule(eRuleEEE);
			(*newrule).AddLhsSymbol(TestToken::E, String(L"E"), Grammar::eNonTerminal);
			(*newrule).AddRhsSymbol(TestToken::E, String(L"E"), Grammar::eNonTerminal);
            (*newrule).AddRhsSymbol(TestToken::p, String(L"+"), Grammar::eTerminal);
			(*newrule).AddRhsSymbol(TestToken::E, String(L"E"), Grammar::eNonTerminal);

			newrule = AddRule(eRuleEa);
			(*newrule).AddLhsSymbol(TestToken::E, String(L"E"), Grammar::eNonTerminal);
			(*newrule).AddRhsSymbol(TestToken::a, String(L"a"), Grammar::eTerminal);
		}
	};
	
struct TestAstNode : public AstNode
{
	TestAstNode(int _type, _ContextLink& _contextlink) : AstNode(_type, _contextlink) {}

	TestAstNode* GetLeftChild(){return (TestAstNode*)GetFirstNode();}
	TestAstNode* GetRightChild()
	{
		if( (TestToken::EType)GetType() == TestToken::p )
			return (TestAstNode*)GetLastNode();
		return 0;
	}

	void Print()
	{
		if( GetType() == TestToken::p ) wprintf( L"+" );
		else wprintf( L"a" );
		wprintf( L"\n" );

	}
};

struct TestAst : public Ast
{
	TestAst() {}
	~TestAst() {}

	void Print()
	{
		if( GetRoot() != null ) Print( 0, (TestAstNode*)GetRoot() );
	}

	void Print( int level, TestAstNode* node )
	{
		if( node )
		{
			Print( level + 1, node->GetRightChild() );
			for( int i = 0; i < level; ++ i ) wprintf( L"    " );
			node->Print();
			Print( level + 1, node->GetLeftChild() );
		}
	}
};

struct TestSemantics : public Semantics
{
		TestAst& Ast;

        TestSemantics(TestAst& _ast) : Ast(_ast)
        {
        }

		// the terminal action
		void HandleTerminal( AstNode* ast_node, Token& token)
		{
			// do nothing. Obviously, we must assign the terminal value here as
			// the parent node is already signed by this terminal.

			int i = 90;
		}

		// the nonterminal action
		TestAstNode* HandleNonterminal( AstNode* ast_node, void* _item, bool ambiguty)
		{
            EarleyParser::Item* item((EarleyParser::Item*)_item);

			TestAstNode* new_node = 0;

			switch( item->Core->Rule->GetId() )
			{
			// we have rule E --> E + E
			case 0:
			{
				// parent as E --> !E! + E
				if( ast_node->GetChildCount() == 0 )
				{
					new_node = new TestAstNode((*(*item).Lptr).Token.GetType(), 
					                    ContextLink((*(*item).Lptr).Token.GetOffset(), 
					                                (*(*item).Lptr).Token.GetLength(), 
					                                (*(*item).Lptr).Token.GetPosition(), 
					                                (*(*item).Lptr).Token.GetLineNumber()));
					ast_node->AddNode( new_node );
				}
			}
			break;
			// we have rule E --> a
			case 1:
			{
				// parent as E --> !E! + E
				if( ast_node->GetChildCount() == 0 )
				{
					if( ambiguty ) return 0;
					new_node = new TestAstNode((*item).Token.GetType(), 
					                    ContextLink((*item).Token.GetOffset(), 
					                                (*item).Token.GetLength(), 
					                                (*item).Token.GetPosition(), 
					                                (*item).Token.GetLineNumber()));
					ast_node->AddNode( new_node );
				}
				// parent as E --> E + !E!
				else
				{
					new_node = new TestAstNode((*item).Token.GetType(), 
					                    ContextLink((*item).Token.GetOffset(), 
					                                (*item).Token.GetLength(), 
					                                (*item).Token.GetPosition(), 
					                                (*item).Token.GetLineNumber()));
					ast_node->AddNode( new_node );
				}
			}
			break;
			}

			return new_node;
		}

		TestAstNode* Start(void* _item)
		{
            EarleyParser::Item* item((EarleyParser::Item*)_item);
			TestAstNode* res = 0;

			switch( item->Core->Rule->GetId() )
			{
				// we have rule E --> E + E
				case 0:
				{
					EarleyParser::Item* child_item = item->Rptr;
					if(child_item->Core->Rule->GetId() == 0) return 0;
					
					res = new TestAstNode((*(*item).Lptr).Token.GetType(), 
					                    ContextLink((*(*item).Lptr).Token.GetOffset(), 
					                                (*(*item).Lptr).Token.GetLength(), 
					                                (*(*item).Lptr).Token.GetPosition(), 
					                                (*(*item).Lptr).Token.GetLineNumber()));
					Ast.GetRoot()= res;
				}
				break;
				
				// we have rule E --> a
				case 1:
				{
					Ast.GetRoot() = new TestAstNode((*(*item).Rptr).Token.GetType(), 
					                    ContextLink((*(*item).Rptr).Token.GetOffset(), 
					                                (*(*item).Rptr).Token.GetLength(), 
					                                (*(*item).Rptr).Token.GetPosition(), 
					                                (*(*item).Rptr).Token.GetLineNumber()));
				}
				break;
			}

			return res;
		}
		
		void End()
		{
		
		}
};

class Parser1 : public EarleyParser
{
	typedef TestLexAnalyser _Lexer;
	typedef Grammar1     _Grammar;
	typedef TestToken       _Token;

	private:
		_Context Context;
		_Lexer   Lexer;
		_Token   Token;
		_Grammar Grammar;
		_Errors  Errors;

		TestSemantics Semantics;
		TestAst Ast;
	public:
		Parser1() : EarleyParser(Context, Lexer, Grammar, Token, Errors),
			Lexer(Context, Errors), Semantics(Ast)
			{
				SetSemantics(&Semantics);

			String text(L"a+a+a+a");

			Context.Allocate(text.GetLength());
			wcscpy(Context.GetData(), text.Cstr());
			Lexer.Reset();
			}

		void Initialize()
			{
			Grammar.Populate();
			Grammar.BuildNullabilitySet();
			Grammar.Print();
			}

		void Parse()
			{
			EarleyParser::ParseAst();
			Ast.Print();
			}

		int GetTokenElementNumber() const
			{
			return TestToken::eSize;
			}

        const TestAst& GetAst() const
        {
            return Ast;
        }
};
	
void test()
{
	Parser1 parser;
	
	parser.Initialize();
	parser.Parse();

	parser.PrintTrees();
}

void test_earley_parser()
{
    time_t t1 = time(0);

    TestEarleyParser parser;

    parser.Initialize();
    parser.Parse();

//    parser.PrintTrees();
    
//    TestEarleyParser::TreeNode* tree;
//    parser.CloneTree(parser.GetTrees()[0], tree);
//    parser.PrintTree(tree);

    time_t t2 = time(0);
    
    std::cout << t2-t1 << std::endl;
}

__END_NAMESPACE__

int _tmain(int argc, _TCHAR* argv[])
{
	USINGNAMESPACE;

//    test();
//	test_earley_parser();

//	CppLexAnalyser::GenerateFSA();
//	CppLexAnalyser::Test("full.test.cpp");

//	ExcelLexAnalyser::GenerateFSA();

//    String formula(L"=@SUM");
//    String formula(L"=@SUM()");
//    String formula(L"=@SUM(,)");
//    String formula(L"=@SUM(1,2)");
//    String formula(L"=@SUM(,,,1,,2,)");
//    String formula(L"=@SUM(,,3.78, 4,6,)+56-34");
//    String formula(L"=@SUM(1,2, @SUM(7,8))");

//    String formula(L"={}+{,}+{1}+{1,2}+{1,2,3}+{,2}+{1,}+{1,3}+{,,}+{1,,}+{,,3}-{}+{;}+{1}+{1;2}+{1;2;3}+{;2}+{1;}+{1;3}+{;;}+{1;;}+{;;3}*{1,3,45;\"a\",\"b\",\"c\", ,\"e\",}");
//    String formula(L"='C:\\[sample.xls]'Sheet1!$A$1");
//      String formula(L"='C:\\[sample.xls]Sheet1'!A1");

//    String formula(L"=SUM(12+5 2 3 4,1,)");

//    String formula(L"=@SUM(A1,,sheet!$A$23&TODAY(), IF(1,3,8),$A$2+500)*sheet!zopa*{}+{,}+{1}+{1,2}+{1,2,3}+{,2}+{1,}+{1,3}+{,,}+{1,,}+{,,3}-{}+{;}+{1}+{1;2}+{1;2;3}+{;2}+{1;}+{1;3}+{;;}+{1;;}+{;;3}*{1,3,45;\"a\",\"b\",\"c\", ,\"e\",}&{}+{,}+{1}+{1,2}+{1,2,3}+{,2}+{1,}+{1,3}+{,,}+{1,,}+{,,3}-{}+{;}+{1}+{1;2}+{1;2;3}+{;2}+{1;}+{1;3}+{;;}+{1;;}+{;;3}*{1,3,45;\"a\",\"b\",\"c\", ,\"e\",}");
//    String formula(L"=@SUM(1)");
//    String formula(L"=IF(\"a\"={\"a\",\"b\";\"c\",#N/A;-1,TRUE}, \"yes\", \"no\") &   \"  more \"\"test\"\" text\""); // error

    String formula(L"='C:\\[sample.xls]Sheet1'!$A$1 'C:\\[sample.xls]Sheet1'!octroi Sheet1:Sheet3!A1:B3");

//    String formula(L"=R, R1, R[23], R[-45], R[+945], C, C1, C[23],C[-45],C[+145],RC, R1C, R[24]C, R[-24]C,R[+124]C,RC1, RC[24], RC[-24], RC[+524], R11C12, R[+345]C[-8]");
//    String formula(L"=RC RC1 RC[-1] R1C1 R1C1:R3C2 R23C56 R C R[-2]C R[-2]C1 R[2]C[3] R[-1] RCC R1CCCC R3435C232C67");

//    String formula(L"=1+2");

	std::wcout << std::endl << formula.Cstr() << std::endl;

//    ExcelLexAnalyser::Test(formula.Cstr(), ExcelToken::eA1);
/*
    {
        ExcelEarleyParser parser(ExcelToken::eA1);
//        ExcelEarleyParser parser(ExcelToken::eR1C1);

        parser.Parse(formula);

        int n = parser.GetTrees().GetSize();
		std::wcout << L"Trees: " << n << std::endl;
    }        
    {
        ExcelEarleyParser parser(ExcelToken::eA1);
//        ExcelEarleyParser parser(ExcelToken::eR1C1);
        parser.ParseAst(formula);

        String xmlstr;
        parser.AstToXml(xmlstr);
        
        std::wcout << xmlstr.Cstr() << std::endl;

        parser.AstToXmlFile(String(L"c:\\tmp\\excel.ast.xml"));
    }
*/
/*
    {
        ExcelEarleyParser parser(ExcelToken::eA1);

        parser.Initialize();

        parser.Parse(formula);
		std::wcout << L"Trees: " << parser.GetTrees().GetSize() << std::endl;
		parser.Reset();

        parser.ParseAst(formula);

        String xmlstr;
        parser.AstToXml(xmlstr);
		parser.Reset();
        
        std::wcout << xmlstr.Cstr() << std::endl;
    }        
*/
    std::wcout << std::endl << std::endl << L"A1 mode" << std::endl;
    time_t t1 = time(0);
    ExcelEarleyParser::Test(String(L"excel.formula.A1.txt"), String(L"c:\\tmp\\excel.A1.txt"), ExcelToken::eA1);
    time_t t2 = time(0);
    std::wcout << "time: " << (int)(t2-t1) << std::endl;

    std::wcout << std::endl << std::endl << L"R1C1 mode" << std::endl;
    t1 = time(0);
    ExcelEarleyParser::Test(String(L"excel.formula.R1C1.txt"), String(L"c:\\tmp\\excel.R1C1.txt"), ExcelToken::eR1C1);
    t2 = time(0);
    std::wcout << "time: " << (int)(t2-t1) << std::endl;

    return 0;
}


// debug    87/12 secs
// release  18/3
