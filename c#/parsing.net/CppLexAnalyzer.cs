//......................................................................................
// This is a part of UI Soft Library.  1989-2006 UI Soft Inc.               .
//......................................................................................
// THIS CODE MAY BE USED, COPIED, STORED, OR DISTRIBUTED ONLY IN ACCORDANCE WITH       .
// A WRITTEN LICENSE AGREEMENT AND WITH THE INCLUSION OF THIS COPYRIGHT NOTICE.        .
//......................................................................................

#region prolog
// file       : 
// description: CppLexAnalyzer
// package    : ail.net.parser
//
#endregion

#region import
using System;
using System.Collections;
#endregion

namespace ail.net.parser
{
    /// <summary>
    /// summary description for CppLexAnalyzer
    /// </summary>
    public class CppLexAnalyzer : ail.net.parser.LexAnalyzer
    {
        #region constants
        private const int kIdentifierCharRank = 1;

        public new enum EContext
        {
            // the following entry, MUST be the first entry in the enum
            eContextUnknown
        };
        #endregion // constants

        #region data members
        #endregion // data members

        #region ctor/dtor/finalizer
        public CppLexAnalyzer(ail.net.parser.CppToken xi_token_class, ArrayList xi_errors) : base(xi_token_class, xi_errors)
        {
        }
        #endregion ctor/dtor/finalizer

        #region methods
        public bool FinalizeLexemeType(int xi_token)
        {
            bool result = true;
            return result;
        }

        public override void NextLexemeImpl(int xi_context)
        {
            Prolog();
            // !!! -- generated code -- !!!
            // !!! -- end of generated code -- !!!
            Epilog();
        }

        public ail.net.parser.Fsa BuildFsa()
        {
            ail.net.parser.Fsa result = new ail.net.parser.Fsa();

            // preprocessor
            AddToken(result, "if", (int)ail.net.parser.CppToken.EType.ePpIf, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
            AddToken(result, "ifdef", (int)ail.net.parser.CppToken.EType.ePpIfdef, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
            AddToken(result, "ifndef", (int)ail.net.parser.CppToken.EType.ePpIfndef, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
            AddToken(result, "elif", (int)ail.net.parser.CppToken.EType.ePpElif, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
            AddToken(result, "else", (int)ail.net.parser.CppToken.EType.ePpElse, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
            AddToken(result, "endif", (int)ail.net.parser.CppToken.EType.ePpEndif, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
            AddToken(result, "define", (int)ail.net.parser.CppToken.EType.ePpDefine, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
            AddToken(result, "undef", (int)ail.net.parser.CppToken.EType.ePpUndef, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
            AddToken(result, "undef", (int)ail.net.parser.CppToken.EType.ePpUndef, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
            AddToken(result, "include", (int)ail.net.parser.CppToken.EType.ePpInclude, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
            AddToken(result, "line", (int)ail.net.parser.CppToken.EType.ePpLine, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
            AddToken(result, "error", (int)ail.net.parser.CppToken.EType.ePpError, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
            AddToken(result, "pragma", (int)ail.net.parser.CppToken.EType.ePpPragma, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
            AddToken(result, "import", (int)ail.net.parser.CppToken.EType.ePpImport, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
            AddToken(result, "using", (int)ail.net.parser.CppToken.EType.ePpUsing, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
            AddToken(result, "\\", (int)ail.net.parser.CppToken.EType.ePpDelimiter, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
            AddToken(result, "using", (int)ail.net.parser.CppToken.EType.ePpUsing, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
            AddToken(result, "#", (int)ail.net.parser.CppToken.EType.ePpNumberSign);
            AddToken(result, "##", (int)ail.net.parser.CppToken.EType.ePpConcat);

            {
                // c comments
                ail.net.parser.Fsa fsa = new ail.net.parser.Fsa();

                ail.net.parser.FsaState q0 = fsa.AddState();
                ail.net.parser.FsaState q1 = fsa.AddState();
                ail.net.parser.FsaState q2 = fsa.AddState();
                ail.net.parser.FsaState q3 = fsa.AddState();
                ail.net.parser.FsaState q4 = fsa.AddState();

                fsa.AddTransition(q0, q1, "IsCharSlash");
                fsa.AddTransition(q1, q2, "IsCharAsterisk");
                fsa.AddTransition(q2, q2, "IsCCommentChar", ail.net.parser.CppLexAnalyzer.kIdentifierCharRank);
                fsa.AddTransition(q2, q3, "IsCharAsterisk");
                fsa.AddTransition(q3, q2, "IsCCommentChar", ail.net.parser.CppLexAnalyzer.kIdentifierCharRank);
                fsa.AddTransition(q3, q3, "IsCharAsterisk");
                fsa.AddTransition(q3, q4, "IsCharSlash");

                fsa.AddFinalState(q3, BuildToken(ail.net.parser.CppToken.EType.eCComments, ail.net.parser.LexAnalyzer.kDefaultTokenPriority));

                result.AddFsa(fsa);
            }
            {
                // c++ comments
                ail.net.parser.Fsa fsa = new ail.net.parser.Fsa();

                ail.net.parser.FsaState q0 = fsa.AddState();
                ail.net.parser.FsaState q1 = fsa.AddState();
                ail.net.parser.FsaState q2 = fsa.AddState();

                fsa.AddTransition(q0, q1, "IsCharSlash");
                fsa.AddTransition(q1, q2, "IsCharSlash");
                fsa.AddTransition(q2, q2, "IsCppCommentChar", ail.net.parser.CppLexAnalyzer.kIdentifierCharRank);

                fsa.AddFinalState(q2, BuildToken(ail.net.parser.CppToken.EType.eCppComments, ail.net.parser.LexAnalyzer.kDefaultTokenPriority));

                result.AddFsa(fsa);
            }
            {
                // decimal literal
                ail.net.parser.Fsa fsa = new ail.net.parser.Fsa();

                ail.net.parser.FsaState q0 = fsa.AddState();
                ail.net.parser.FsaState q1 = fsa.AddState();
                ail.net.parser.FsaState q2 = fsa.AddState();
                ail.net.parser.FsaState q3 = fsa.AddState();
                ail.net.parser.FsaState q4 = fsa.AddState();
                ail.net.parser.FsaState q5 = fsa.AddState();
                ail.net.parser.FsaState q6 = fsa.AddState();
                ail.net.parser.FsaState q7 = fsa.AddState();
                ail.net.parser.FsaState q8 = fsa.AddState();

                fsa.AddTransition(q0, q1, "IsNonZeroDigitChar", 1);
                fsa.AddTransition(q1, q1, "IsDecimalDigitChar", 2);
                fsa.AddTransition(q1, q2, "IsCharLowerCaseL");
                fsa.AddTransition(q1, q2, "IsCharUpperCaseL");
                fsa.AddTransition(q2, q3, "IsCharLowerCaseL");
                fsa.AddTransition(q2, q3, "IsCharUpperCaseL");
                fsa.AddTransition(q2, q5, "IsCharLowerCaseU");
                fsa.AddTransition(q2, q5, "IsCharUpperCaseU");
                fsa.AddTransition(q1, q4, "IsCharLowerCaseU");
                fsa.AddTransition(q1, q4, "IsCharUpperCaseU");
                fsa.AddTransition(q4, q5, "IsCharLowerCaseL");
                fsa.AddTransition(q4, q5, "IsCharUpperCaseL");
                fsa.AddTransition(q1, q6, "IsCharLowerCaseI");
                fsa.AddTransition(q1, q6, "IsCharUpperCaseI");
                fsa.AddTransition(q6, q7, "IsCharDigitSix");
                fsa.AddTransition(q7, q8, "IsCharDigitFour");

                fsa.AddFinalState(q1, BuildToken(ail.net.parser.CppToken.EType.eDecimalIntegerLiteral, ail.net.parser.LexAnalyzer.kDefaultTokenPriority));
                fsa.AddFinalState(q2, BuildToken(ail.net.parser.CppToken.EType.eDecimalIntegerLiteral, ail.net.parser.LexAnalyzer.kDefaultTokenPriority));
                fsa.AddFinalState(q3, BuildToken(ail.net.parser.CppToken.EType.eDecimalIntegerLiteral, ail.net.parser.LexAnalyzer.kDefaultTokenPriority));
                fsa.AddFinalState(q4, BuildToken(ail.net.parser.CppToken.EType.eDecimalIntegerLiteral, ail.net.parser.LexAnalyzer.kDefaultTokenPriority));
                fsa.AddFinalState(q5, BuildToken(ail.net.parser.CppToken.EType.eDecimalIntegerLiteral, ail.net.parser.LexAnalyzer.kDefaultTokenPriority));
                fsa.AddFinalState(q8, BuildToken(ail.net.parser.CppToken.EType.eDecimalIntegerLiteral, ail.net.parser.LexAnalyzer.kDefaultTokenPriority));

                result.AddFsa(fsa);
            }
            {
                // octal literal
                ail.net.parser.Fsa fsa = new ail.net.parser.Fsa();

                ail.net.parser.FsaState q0 = fsa.AddState();
                ail.net.parser.FsaState q1 = fsa.AddState();
                ail.net.parser.FsaState q2 = fsa.AddState();
                ail.net.parser.FsaState q3 = fsa.AddState();
                ail.net.parser.FsaState q4 = fsa.AddState();
                ail.net.parser.FsaState q5 = fsa.AddState();
                ail.net.parser.FsaState q6 = fsa.AddState();
                ail.net.parser.FsaState q7 = fsa.AddState();
                ail.net.parser.FsaState q8 = fsa.AddState();

                fsa.AddTransition(q0, q1, "IsCharDigitZero");
                fsa.AddTransition(q1, q1, "IsOctalDigitChar", 1);
                fsa.AddTransition(q1, q2, "IsCharLowerCaseL");
                fsa.AddTransition(q1, q2, "IsCharUpperCaseL");
                fsa.AddTransition(q2, q3, "IsCharLowerCaseL");
                fsa.AddTransition(q2, q3, "IsCharUpperCaseL");
                fsa.AddTransition(q2, q5, "IsCharLowerCaseU");
                fsa.AddTransition(q2, q5, "IsCharUpperCaseU");
                fsa.AddTransition(q1, q4, "IsCharLowerCaseU");
                fsa.AddTransition(q1, q4, "IsCharUpperCaseU");
                fsa.AddTransition(q4, q5, "IsCharLowerCaseL");
                fsa.AddTransition(q4, q5, "IsCharUpperCaseL");
                fsa.AddTransition(q1, q6, "IsCharLowerCaseI");
                fsa.AddTransition(q1, q6, "IsCharUpperCaseI");
                fsa.AddTransition(q6, q7, "IsCharDigitSix");
                fsa.AddTransition(q7, q8, "IsCharDigitFour");

                fsa.AddFinalState(q1, BuildToken(ail.net.parser.CppToken.EType.eOctalIntegerLiteral, ail.net.parser.LexAnalyzer.kDefaultTokenPriority));
                fsa.AddFinalState(q2, BuildToken(ail.net.parser.CppToken.EType.eOctalIntegerLiteral, ail.net.parser.LexAnalyzer.kDefaultTokenPriority));
                fsa.AddFinalState(q3, BuildToken(ail.net.parser.CppToken.EType.eOctalIntegerLiteral, ail.net.parser.LexAnalyzer.kDefaultTokenPriority));
                fsa.AddFinalState(q4, BuildToken(ail.net.parser.CppToken.EType.eOctalIntegerLiteral, ail.net.parser.LexAnalyzer.kDefaultTokenPriority));
                fsa.AddFinalState(q5, BuildToken(ail.net.parser.CppToken.EType.eOctalIntegerLiteral, ail.net.parser.LexAnalyzer.kDefaultTokenPriority));
                fsa.AddFinalState(q8, BuildToken(ail.net.parser.CppToken.EType.eOctalIntegerLiteral, ail.net.parser.LexAnalyzer.kDefaultTokenPriority));

                result.AddFsa(fsa);
            }
            {
                // hex literal
                ail.net.parser.Fsa fsa = new ail.net.parser.Fsa();

                ail.net.parser.FsaState q0 = fsa.AddState();
                ail.net.parser.FsaState q1 = fsa.AddState();
                ail.net.parser.FsaState q2 = fsa.AddState();
                ail.net.parser.FsaState q3 = fsa.AddState();
                ail.net.parser.FsaState q4 = fsa.AddState();
                ail.net.parser.FsaState q5 = fsa.AddState();
                ail.net.parser.FsaState q6 = fsa.AddState();
                ail.net.parser.FsaState q7 = fsa.AddState();
                ail.net.parser.FsaState q8 = fsa.AddState();
                ail.net.parser.FsaState q9 = fsa.AddState();
                ail.net.parser.FsaState q10= fsa.AddState();

                fsa.AddTransition(q0, q1, "IsCharDigitZero");
                fsa.AddTransition(q1, q2, "IsCharLowerCaseX");
                fsa.AddTransition(q1, q2, "IsCharUpperCaseX");
                fsa.AddTransition(q2, q3, "IsHexDigitChar", 3);
                fsa.AddTransition(q3, q3, "IsHexDigitChar", 3);
                fsa.AddTransition(q3, q4, "IsCharLowerCaseL");
                fsa.AddTransition(q3, q4, "IsCharUpperCaseL");
                fsa.AddTransition(q4, q5, "IsCharLowerCaseL");
                fsa.AddTransition(q4, q5, "IsCharUpperCaseL");
                fsa.AddTransition(q4, q7, "IsCharLowerCaseU");
                fsa.AddTransition(q4, q7, "IsCharUpperCaseU");
                fsa.AddTransition(q3, q6, "IsCharLowerCaseU");
                fsa.AddTransition(q3, q6, "IsCharUpperCaseU");
                fsa.AddTransition(q6, q7, "IsCharLowerCaseL");
                fsa.AddTransition(q6, q7, "IsCharUpperCaseL");
                fsa.AddTransition(q3, q8, "IsCharLowerCaseI");
                fsa.AddTransition(q3, q8, "IsCharUpperCaseI");
                fsa.AddTransition(q8, q9, "IsCharDigitSix");
                fsa.AddTransition(q9, q10,"IsCharDigitFour");

                fsa.AddFinalState(q3, BuildToken(ail.net.parser.CppToken.EType.eHexIntegerLiteral, ail.net.parser.LexAnalyzer.kDefaultTokenPriority));
                fsa.AddFinalState(q4, BuildToken(ail.net.parser.CppToken.EType.eHexIntegerLiteral, ail.net.parser.LexAnalyzer.kDefaultTokenPriority));
                fsa.AddFinalState(q5, BuildToken(ail.net.parser.CppToken.EType.eHexIntegerLiteral, ail.net.parser.LexAnalyzer.kDefaultTokenPriority));
                fsa.AddFinalState(q6, BuildToken(ail.net.parser.CppToken.EType.eHexIntegerLiteral, ail.net.parser.LexAnalyzer.kDefaultTokenPriority));
                fsa.AddFinalState(q7, BuildToken(ail.net.parser.CppToken.EType.eHexIntegerLiteral, ail.net.parser.LexAnalyzer.kDefaultTokenPriority));
                fsa.AddFinalState(q10, BuildToken(ail.net.parser.CppToken.EType.eHexIntegerLiteral, ail.net.parser.LexAnalyzer.kDefaultTokenPriority));

                result.AddFsa(fsa);
            }
            {
                // float literal
                ail.net.parser.Fsa fsa = new ail.net.parser.Fsa();

                ail.net.parser.FsaState q0  = fsa.AddState();
                ail.net.parser.FsaState q1  = fsa.AddState();
                ail.net.parser.FsaState q2  = fsa.AddState();
                ail.net.parser.FsaState q3  = fsa.AddState();
                ail.net.parser.FsaState q4  = fsa.AddState();
                ail.net.parser.FsaState q5  = fsa.AddState();
                ail.net.parser.FsaState q6  = fsa.AddState();
                ail.net.parser.FsaState q7  = fsa.AddState();
                ail.net.parser.FsaState q8  = fsa.AddState();
                ail.net.parser.FsaState q9  = fsa.AddState();
                ail.net.parser.FsaState q10 = fsa.AddState();
                ail.net.parser.FsaState q11 = fsa.AddState();
                ail.net.parser.FsaState q12 = fsa.AddState();
                ail.net.parser.FsaState q13 = fsa.AddState();
                ail.net.parser.FsaState q14 = fsa.AddState();
                ail.net.parser.FsaState q15 = fsa.AddState();

                fsa.AddTransition(q0, q1,   "IsCharDot");
                fsa.AddTransition(q0, q2,   "IsNonZeroDigitChar", 1);

                fsa.AddTransition(q1, q3,   "IsDecimalDigitChar", 2);

                fsa.AddTransition(q2, q2,   "IsDecimalDigitChar", 2);
                fsa.AddTransition(q2, q7,   "IsCharDot");
                fsa.AddTransition(q2, q4,   "IsCharLowerCaseF");
                fsa.AddTransition(q2, q4,   "IsCharUpperCaseF");
                fsa.AddTransition(q2, q5,   "IsCharLowerCaseE");
                fsa.AddTransition(q2, q5,   "IsCharUpperCaseE");
                fsa.AddTransition(q2, q6,   "IsCharLowerCaseL");
                fsa.AddTransition(q2, q6,   "IsCharUpperCaseL");

                fsa.AddTransition(q3, q3,   "IsDecimalDigitChar", 2);
                fsa.AddTransition(q3, q8,   "IsCharLowerCaseF");
                fsa.AddTransition(q3, q8,   "IsCharUpperCaseF");
                fsa.AddTransition(q3, q9,   "IsCharLowerCaseE");
                fsa.AddTransition(q3, q9,   "IsCharUpperCaseE");
                fsa.AddTransition(q3, q10,  "IsCharLowerCaseL");
                fsa.AddTransition(q3, q10,  "IsCharUpperCaseL");

                fsa.AddTransition(q5, q11,  "IsCharMinus");
                fsa.AddTransition(q5, q11,  "IsCharPlus");
                fsa.AddTransition(q5, q12,  "IsDecimalDigitChar", 2);

                fsa.AddTransition(q7, q3,   "IsDecimalDigitChar", 2);
                fsa.AddTransition(q7, q8,   "IsCharLowerCaseF");
                fsa.AddTransition(q7, q8,   "IsCharUpperCaseF");
                fsa.AddTransition(q7, q9,   "IsCharLowerCaseE");
                fsa.AddTransition(q7, q9,   "IsCharUpperCaseE");
                fsa.AddTransition(q7, q10,  "IsCharLowerCaseL");
                fsa.AddTransition(q7, q10,  "IsCharUpperCaseL");

                fsa.AddTransition(q9, q13,  "IsCharMinus");
                fsa.AddTransition(q9, q13,  "IsCharPlus");
                fsa.AddTransition(q9, q14,  "IsDecimalDigitChar", 2);

                fsa.AddTransition(q11, q12, "IsDecimalDigitChar", 2);

                fsa.AddTransition(q12, q12, "IsDecimalDigitChar", 2);
                fsa.AddTransition(q12, q4,  "IsCharLowerCaseF");
                fsa.AddTransition(q12, q4,  "IsCharUpperCaseF");
                fsa.AddTransition(q12, q6,  "IsCharLowerCaseL");
                fsa.AddTransition(q12, q6,  "IsCharUpperCaseL");

                fsa.AddTransition(q13, q14, "IsDecimalDigitChar", 2);

                fsa.AddTransition(q14, q14, "IsDecimalDigitChar", 2);
                fsa.AddTransition(q14, q8,  "IsCharLowerCaseF");
                fsa.AddTransition(q14, q8,  "IsCharUpperCaseF");
                fsa.AddTransition(q14, q10, "IsCharLowerCaseL");
                fsa.AddTransition(q14, q10, "IsCharUpperCaseL");

                fsa.AddTransition(q0, q15,  "IsCharDigitZero");
                fsa.AddTransition(q15, q9,  "IsCharDot");
                fsa.AddTransition(q15, q4,  "IsCharLowerCaseF");
                fsa.AddTransition(q15, q4,  "IsCharUpperCaseF");
                fsa.AddTransition(q15, q6,  "IsCharLowerCaseL");
                fsa.AddTransition(q15, q6,  "IsCharUpperCaseL");

                fsa.AddFinalState(q2, BuildToken(ail.net.parser.CppToken.EType.eDecimalIntegerLiteral, ail.net.parser.LexAnalyzer.kDefaultTokenPriority));
                fsa.AddFinalState(q3, BuildToken(ail.net.parser.CppToken.EType.eFloatLiteral, ail.net.parser.LexAnalyzer.kDefaultTokenPriority));
                fsa.AddFinalState(q4, BuildToken(ail.net.parser.CppToken.EType.eFloatLiteral, ail.net.parser.LexAnalyzer.kDefaultTokenPriority));
                fsa.AddFinalState(q6, BuildToken(ail.net.parser.CppToken.EType.eFloatLiteral, ail.net.parser.LexAnalyzer.kDefaultTokenPriority));
                fsa.AddFinalState(q7, BuildToken(ail.net.parser.CppToken.EType.eFloatLiteral, ail.net.parser.LexAnalyzer.kDefaultTokenPriority));
                fsa.AddFinalState(q8, BuildToken(ail.net.parser.CppToken.EType.eFloatLiteral, ail.net.parser.LexAnalyzer.kDefaultTokenPriority));
                fsa.AddFinalState(q10, BuildToken(ail.net.parser.CppToken.EType.eFloatLiteral, ail.net.parser.LexAnalyzer.kDefaultTokenPriority));
                fsa.AddFinalState(q12, BuildToken(ail.net.parser.CppToken.EType.eFloatLiteral, ail.net.parser.LexAnalyzer.kDefaultTokenPriority));
                fsa.AddFinalState(q14, BuildToken(ail.net.parser.CppToken.EType.eFloatLiteral, ail.net.parser.LexAnalyzer.kDefaultTokenPriority));
                fsa.AddFinalState(q15, BuildToken(ail.net.parser.CppToken.EType.eOctalIntegerLiteral, ail.net.parser.LexAnalyzer.kDefaultTokenPriority));

                result.AddFsa(fsa);
            }
            {
                // char literal
                ail.net.parser.Fsa fsa = new ail.net.parser.Fsa();

                ail.net.parser.FsaState q0 = fsa.AddState();
                ail.net.parser.FsaState q1 = fsa.AddState();
                ail.net.parser.FsaState q2 = fsa.AddState();
                ail.net.parser.FsaState q3 = fsa.AddState();
                ail.net.parser.FsaState q4 = fsa.AddState();

                fsa.AddTransition(q0, q1, "IsCharSingleQuote");
                fsa.AddTransition(q0, q2, "IsCharUpperCaseL");
                fsa.AddTransition(q2, q1, "IsCharSingleQuote");
                fsa.AddTransition(q2, q2, "IsIdentifierChar", ail.net.parser.CppLexAnalyzer.kIdentifierCharRank);
                fsa.AddTransition(q1, q1, "IsCharLiteral");
                fsa.AddTransition(q1, q3, "IsCharBackSlash");
                fsa.AddTransition(q3, q1, "IsCharBackSlash");
                fsa.AddTransition(q3, q1, "IsCharSingleQuote");
                fsa.AddTransition(q3, q1, "IsCharLiteral");
                fsa.AddTransition(q1, q4, "IsCharSingleQuote");

                fsa.AddFinalState(q4, BuildToken(ail.net.parser.CppToken.EType.eCharLiteral, ail.net.parser.LexAnalyzer.kDefaultTokenPriority));
                fsa.AddFinalState(q2, BuildToken(ail.net.parser.CppToken.EType.eIdentifier, ail.net.parser.LexAnalyzer.kDefaultTokenPriority));

                result.AddFsa(fsa);
            }
            {
                // string literal
                ail.net.parser.Fsa fsa = new ail.net.parser.Fsa();

                ail.net.parser.FsaState q0 = fsa.AddState();
                ail.net.parser.FsaState q1 = fsa.AddState();
                ail.net.parser.FsaState q2 = fsa.AddState();
                ail.net.parser.FsaState q3 = fsa.AddState();
                ail.net.parser.FsaState q4 = fsa.AddState();

                fsa.AddTransition(q0, q1, "IsCharDoubleQuote");
                fsa.AddTransition(q0, q2, "IsCharUpperCaseL");
                fsa.AddTransition(q2, q1, "IsCharDoubleQuote");
                fsa.AddTransition(q2, q2, "IsIdentifierChar", ail.net.parser.CppLexAnalyzer.kIdentifierCharRank);
                fsa.AddTransition(q1, q1, "IsStringLiteral");
                fsa.AddTransition(q1, q3, "IsCharBackSlash");
                fsa.AddTransition(q3, q1, "IsCharBackSlash");
                fsa.AddTransition(q3, q1, "IsCharDoubleQuote");
                fsa.AddTransition(q3, q1, "IsStringLiteral");
                fsa.AddTransition(q3, q1, "IsCharEol");
                fsa.AddTransition(q1, q4, "IsCharDoubleQuote");

                fsa.AddFinalState(q4, BuildToken(ail.net.parser.CppToken.EType.eStringLiteral, ail.net.parser.LexAnalyzer.kDefaultTokenPriority));
                fsa.AddFinalState(q2, BuildToken(ail.net.parser.CppToken.EType.eIdentifier, ail.net.parser.LexAnalyzer.kDefaultTokenPriority));

                result.AddFsa(fsa);
            }
            {
                // digraphs
                AddToken(result, @"<%"/*{*/, (int)ail.net.parser.CppToken.EType.eDigraphLeftBrace);
                AddToken(result, @"%>"/*}*/, (int)ail.net.parser.CppToken.EType.eDigraphRightBrace);
                AddToken(result, @"<:"/*[*/, (int)ail.net.parser.CppToken.EType.eDigraphLeftBracket);
                AddToken(result, @":>"/*]*/, (int)ail.net.parser.CppToken.EType.eDigraphRightBracket);
                AddToken(result, @"%:"/*#*/, (int)ail.net.parser.CppToken.EType.eDigraphNumberSign);
                AddToken(result, @"%:%:"/*##*/, (int)ail.net.parser.CppToken.EType.eDigraphNumberSign2);
            }
            {
                // trigraphs
                AddToken(result, @"\?\?="/*#*/,  (int)ail.net.parser.CppToken.EType.eTrigraphNumberSign);
                AddToken(result, @"\?\?/",       (int)ail.net.parser.CppToken.EType.eTrigraphBackSlash);
                AddToken(result, @"\?\?'"/*^*/,  (int)ail.net.parser.CppToken.EType.eTrigraphCircum);
                AddToken(result, @"\?\?("/*[*/,  (int)ail.net.parser.CppToken.EType.eTrigraphLeftBracket);
                AddToken(result, @"\?\?)"/*]*/,  (int)ail.net.parser.CppToken.EType.eTrigraphRightBracket);
                AddToken(result, @"\?\?!"/*|*/,  (int)ail.net.parser.CppToken.EType.eTrigraphBar);
                AddToken(result, @"\?\?<"/*{*/,  (int)ail.net.parser.CppToken.EType.eTrigraphLeftBrace);
                AddToken(result, @"\?\?>"/*}*/,  (int)ail.net.parser.CppToken.EType.eTrigraphRightBrace);
                AddToken(result, @"\?\?-"/*~*/,  (int)ail.net.parser.CppToken.EType.eTrigraphTilda);
            }
            {
                // alternatives
                AddToken(result, "bitand",/*&*/	(int)ail.net.parser.CppToken.EType.eAltBitAnd, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "and", /*&&*/ (int)ail.net.parser.CppToken.EType.eAltAnd, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "and_eq",/*&=*/ (int)ail.net.parser.CppToken.EType.eAltAndEq, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "bitor" /*|*/, (int)ail.net.parser.CppToken.EType.eAltBitOr, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "or" /*||*/, (int)ail.net.parser.CppToken.EType.eAltOr, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "or_eq" /*|=*/, (int)ail.net.parser.CppToken.EType.eAltOrEq, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "xor" /*^*/, (int)ail.net.parser.CppToken.EType.eAltXor, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "xor_eq" /*^=*/, (int)ail.net.parser.CppToken.EType.eAltXorEq, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "not" /*!*/, (int)ail.net.parser.CppToken.EType.eAltNot, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "not_eq" /*!=*/, (int)ail.net.parser.CppToken.EType.eAltNotEq, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "compl" /*~*/, (int)ail.net.parser.CppToken.EType.eAltComplement, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
            }
            {
                // white space
                ail.net.parser.Fsa fsa = new ail.net.parser.Fsa();

                ail.net.parser.FsaState q0 = fsa.AddState();
                ail.net.parser.FsaState q1 = fsa.AddState();

                fsa.AddTransition(q0, q1, "IsCharWhiteSpace");
                fsa.AddTransition(q1, q1, "IsCharWhiteSpace");

                fsa.AddFinalState(q1, BuildToken(ail.net.parser.CppToken.EType.eWhiteSpace, ail.net.parser.LexAnalyzer.kDefaultTokenPriority));

                result.AddFsa(fsa);
            }
            {
                // keywords
                AddToken(result, "__abstract", (int)ail.net.parser.CppToken.EType.eMS_Abstract, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__alignof", (int)ail.net.parser.CppToken.EType.eMS_Alignof, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__asm", (int)ail.net.parser.CppToken.EType.eMS_Asm, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__assume", (int)ail.net.parser.CppToken.EType.eMS_Assume, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__based", (int)ail.net.parser.CppToken.EType.eMS_Based, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__box", (int)ail.net.parser.CppToken.EType.eMS_Box, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__cdec", (int)ail.net.parser.CppToken.EType.eMS_Cdecl, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__declspec", (int)ail.net.parser.CppToken.EType.eMS_Declspec, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__delegate", (int)ail.net.parser.CppToken.EType.eMS_Delegate, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__event", (int)ail.net.parser.CppToken.EType.eMS_Event, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__except", (int)ail.net.parser.CppToken.EType.eMS_Except, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__fastcal", (int)ail.net.parser.CppToken.EType.eMS_Fastcall, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__finally", (int)ail.net.parser.CppToken.EType.eMS_Finally, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__forceinline", (int)ail.net.parser.CppToken.EType.eMS_Forceinline, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__gc", (int)ail.net.parser.CppToken.EType.eMS_Gc, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__hook", (int)ail.net.parser.CppToken.EType.eMS_Hook, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__identifier", (int)ail.net.parser.CppToken.EType.eMS_Identifier, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__if_exists", (int)ail.net.parser.CppToken.EType.eMS_If_exists, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__if_not_exists", (int)ail.net.parser.CppToken.EType.eMS_If_not_exists, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__inline", (int)ail.net.parser.CppToken.EType.eMS_Inline, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__int8", (int)ail.net.parser.CppToken.EType.eMS_Int8, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__int16", (int)ail.net.parser.CppToken.EType.eMS_Int16, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__int32", (int)ail.net.parser.CppToken.EType.eMS_Int32, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__int64", (int)ail.net.parser.CppToken.EType.eMS_Int64, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__interface", (int)ail.net.parser.CppToken.EType.eMS_Interface, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__leave", (int)ail.net.parser.CppToken.EType.eMS_Leave, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__m64", (int)ail.net.parser.CppToken.EType.eMS_M64, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__m128", (int)ail.net.parser.CppToken.EType.eMS_M128, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__m128d", (int)ail.net.parser.CppToken.EType.eMS_M128d, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__m128i", (int)ail.net.parser.CppToken.EType.eMS_M128i, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__multiple_inheritance", (int)ail.net.parser.CppToken.EType.eMS_MultipleInheritance, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__nogc", (int)ail.net.parser.CppToken.EType.eMS_Nogc, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__noop", (int)ail.net.parser.CppToken.EType.eMS_Noop, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__pin", (int)ail.net.parser.CppToken.EType.eMS_Pin, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__property", (int)ail.net.parser.CppToken.EType.eMS_Property, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__raise", (int)ail.net.parser.CppToken.EType.eMS_Raise, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__sealed", (int)ail.net.parser.CppToken.EType.eMS_Sealed, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__single_inheritance", (int)ail.net.parser.CppToken.EType.eMS_SingleInheritance, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__stdcal", (int)ail.net.parser.CppToken.EType.eMS_Stdcall, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__super", (int)ail.net.parser.CppToken.EType.eMS_Super, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__try_cast", (int)ail.net.parser.CppToken.EType.eMS_Trycast, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__try", (int)ail.net.parser.CppToken.EType.eMS_Try, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__unhook", (int)ail.net.parser.CppToken.EType.eMS_Unhook, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__uuidof", (int)ail.net.parser.CppToken.EType.eMS_Uuidof, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__value", (int)ail.net.parser.CppToken.EType.eMS_Value, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__virtual_inheritance", (int)ail.net.parser.CppToken.EType.eMS_Virtual_inheritance, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__w64", (int)ail.net.parser.CppToken.EType.eMS_W64, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "__wchar", (int)ail.net.parser.CppToken.EType.eMS_Wchar, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");

                AddToken(result, "auto", (int)ail.net.parser.CppToken.EType.eAuto, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "boo", (int)ail.net.parser.CppToken.EType.eBool, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "break", (int)ail.net.parser.CppToken.EType.eBreak, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "case", (int)ail.net.parser.CppToken.EType.eCase, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "catch", (int)ail.net.parser.CppToken.EType.eCatch, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "char", (int)ail.net.parser.CppToken.EType.eChar, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "class", (int)ail.net.parser.CppToken.EType.eClass, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "const", (int)ail.net.parser.CppToken.EType.eConst, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "const_cast", (int)ail.net.parser.CppToken.EType.eConstCast, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "continue", (int)ail.net.parser.CppToken.EType.eContinue, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "default", (int)ail.net.parser.CppToken.EType.eDefault, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "delete", (int)ail.net.parser.CppToken.EType.eDelete, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "deprecated", (int)ail.net.parser.CppToken.EType.eDeprecated, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "dllexport", (int)ail.net.parser.CppToken.EType.eDllexport, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "dllimport", (int)ail.net.parser.CppToken.EType.eDllimport, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "do", (int)ail.net.parser.CppToken.EType.eDo, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "double", (int)ail.net.parser.CppToken.EType.eDouble, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "dynamic_cast", (int)ail.net.parser.CppToken.EType.eDynamicCast, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "else", (int)ail.net.parser.CppToken.EType.eElse, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "enum", (int)ail.net.parser.CppToken.EType.eEnum, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "explicit", (int)ail.net.parser.CppToken.EType.eExplicit, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "extern", (int)ail.net.parser.CppToken.EType.eExtern, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "false", (int)ail.net.parser.CppToken.EType.eFalse, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "float", (int)ail.net.parser.CppToken.EType.eFloat, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "for", (int)ail.net.parser.CppToken.EType.eFor, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "friend", (int)ail.net.parser.CppToken.EType.eFriend, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "goto", (int)ail.net.parser.CppToken.EType.eGoto, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "if", (int)ail.net.parser.CppToken.EType.eIf, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "inline", (int)ail.net.parser.CppToken.EType.eInline, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "int", (int)ail.net.parser.CppToken.EType.eInt, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "long", (int)ail.net.parser.CppToken.EType.eLong, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "mutable", (int)ail.net.parser.CppToken.EType.eMutable, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "naked", (int)ail.net.parser.CppToken.EType.eNaked, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "namespace", (int)ail.net.parser.CppToken.EType.eNamespace, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "new", (int)ail.net.parser.CppToken.EType.eNew, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "noinline", (int)ail.net.parser.CppToken.EType.eNoinline, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "noreturn", (int)ail.net.parser.CppToken.EType.eNoreturn, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "nothrow", (int)ail.net.parser.CppToken.EType.eNothrow, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "novtable", (int)ail.net.parser.CppToken.EType.eNovtable, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "operator", (int)ail.net.parser.CppToken.EType.eOperator, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "private", (int)ail.net.parser.CppToken.EType.ePrivate, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "property", (int)ail.net.parser.CppToken.EType.eProperty, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "protected", (int)ail.net.parser.CppToken.EType.eProtected, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "public", (int)ail.net.parser.CppToken.EType.ePublic, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "register", (int)ail.net.parser.CppToken.EType.eRegister, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "reinterpret_cast", (int)ail.net.parser.CppToken.EType.eReinterpretCast, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "return", (int)ail.net.parser.CppToken.EType.eReturn, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "selectany", (int)ail.net.parser.CppToken.EType.eSelectany, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "short", (int)ail.net.parser.CppToken.EType.eShort, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "signed", (int)ail.net.parser.CppToken.EType.eSigned, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "sizeof", (int)ail.net.parser.CppToken.EType.eSizeof, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "static", (int)ail.net.parser.CppToken.EType.eStatic, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "static_cast", (int)ail.net.parser.CppToken.EType.eStaticCast, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "struct", (int)ail.net.parser.CppToken.EType.eStruct, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "switch", (int)ail.net.parser.CppToken.EType.eSwitch, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "template", (int)ail.net.parser.CppToken.EType.eTemplate, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "this", (int)ail.net.parser.CppToken.EType.eThis, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "thread", (int)ail.net.parser.CppToken.EType.eThread, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "throw", (int)ail.net.parser.CppToken.EType.eThrow, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "true", (int)ail.net.parser.CppToken.EType.eTrue, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "try", (int)ail.net.parser.CppToken.EType.eTry, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "typedef", (int)ail.net.parser.CppToken.EType.eTypedef, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "typeid", (int)ail.net.parser.CppToken.EType.eTypeid, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "typename", (int)ail.net.parser.CppToken.EType.eTypename, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "union", (int)ail.net.parser.CppToken.EType.eUnion, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "unsigned", (int)ail.net.parser.CppToken.EType.eUnsigned, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "using", (int)ail.net.parser.CppToken.EType.eUsing, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "uuid", (int)ail.net.parser.CppToken.EType.eUuid, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "virtual", (int)ail.net.parser.CppToken.EType.eVirtual, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "void", (int)ail.net.parser.CppToken.EType.eVoid, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "volatile", (int)ail.net.parser.CppToken.EType.eVolatile, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "wchar_t", (int)ail.net.parser.CppToken.EType.eWchar, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
                AddToken(result, "while", (int)ail.net.parser.CppToken.EType.eWhile, (int)ail.net.parser.CppToken.EType.eIdentifier, "IsIdentifierChar");
            }
            {
                // operators
                AddToken(result, @"+",   (int)ail.net.parser.CppToken.EType.eAddition);
                AddToken(result, @"+=",  (int)ail.net.parser.CppToken.EType.eAdditionAssignment);
                AddToken(result, @"++",  (int)ail.net.parser.CppToken.EType.eIncrement);
                AddToken(result, @"-",   (int)ail.net.parser.CppToken.EType.eSubtraction);
                AddToken(result, @"-=",  (int)ail.net.parser.CppToken.EType.eSubtractionAssignment);
                AddToken(result, @"--",  (int)ail.net.parser.CppToken.EType.eDecrement);
                AddToken(result, @"*",   (int)ail.net.parser.CppToken.EType.eMultiplication);
                AddToken(result, @"*=",  (int)ail.net.parser.CppToken.EType.eMultiplicationAssignment);
                AddToken(result, @"/",   (int)ail.net.parser.CppToken.EType.eDivision);
                AddToken(result, @"/=",  (int)ail.net.parser.CppToken.EType.eDivisionAssignment);
                AddToken(result, @"%",   (int)ail.net.parser.CppToken.EType.eModulus);
                AddToken(result, @"%=",  (int)ail.net.parser.CppToken.EType.eModulusAssignment);
                AddToken(result, @"!",   (int)ail.net.parser.CppToken.EType.eLogicalNegotian);
                AddToken(result, @"&",   (int)ail.net.parser.CppToken.EType.eBitwiseAnd);
                AddToken(result, @"&=",  (int)ail.net.parser.CppToken.EType.eBitwiseAndAssignment);
                AddToken(result, @"|",   (int)ail.net.parser.CppToken.EType.eBitwiseOr);
                AddToken(result, @"|=",  (int)ail.net.parser.CppToken.EType.eBitwiseOrAssignment);
                AddToken(result, @"^",   (int)ail.net.parser.CppToken.EType.eBitwiseXor);
                AddToken(result, @"^=",  (int)ail.net.parser.CppToken.EType.eBitwiseXorAssignment);
                AddToken(result, @"~",   (int)ail.net.parser.CppToken.EType.eComplement);
                AddToken(result, @"=",   (int)ail.net.parser.CppToken.EType.eAssignment);
                AddToken(result, @"==",  (int)ail.net.parser.CppToken.EType.eEquality);
                AddToken(result, @"!=",  (int)ail.net.parser.CppToken.EType.eNotEqual);
                AddToken(result, @"<",   (int)ail.net.parser.CppToken.EType.eLessThan);
                AddToken(result, @"<=",  (int)ail.net.parser.CppToken.EType.eLessThanOrEqual);
                AddToken(result, @">",   (int)ail.net.parser.CppToken.EType.eGreaterThan);
                AddToken(result, @">=",  (int)ail.net.parser.CppToken.EType.eGreaterThanOrEqual);
                AddToken(result, @"&&",  (int)ail.net.parser.CppToken.EType.eLogicalAnd);
                AddToken(result, @"||",  (int)ail.net.parser.CppToken.EType.eLogicalOr);
                AddToken(result, @"?",   (int)ail.net.parser.CppToken.EType.eConditional);
                AddToken(result, @"<<",  (int)ail.net.parser.CppToken.EType.eLeftShift);
                AddToken(result, @"<<=", (int)ail.net.parser.CppToken.EType.eLeftShiftAssignment);
                AddToken(result, @">>",  (int)ail.net.parser.CppToken.EType.eRightShift);
                AddToken(result, @"<<=", (int)ail.net.parser.CppToken.EType.eRightShiftAssignment);
                AddToken(result, @"::",  (int)ail.net.parser.CppToken.EType.eScopeResolution);
                AddToken(result, @"->",  (int)ail.net.parser.CppToken.EType.eMemberAccessArrow);
                AddToken(result, @".*",  (int)ail.net.parser.CppToken.EType.ePtrTomemberDot);
                AddToken(result, @"->*", (int)ail.net.parser.CppToken.EType.ePtrTomemberArrow);

                AddToken(result, @";",   (int)ail.net.parser.CppToken.EType.eSemicolon);
                AddToken(result, @":",   (int)ail.net.parser.CppToken.EType.eColon);
                AddToken(result, @",",   (int)ail.net.parser.CppToken.EType.eComma);
                AddToken(result, @".",   (int)ail.net.parser.CppToken.EType.eMemberAccessDot);
                AddToken(result, @"(",   (int)ail.net.parser.CppToken.EType.eLeftParens);
                AddToken(result, @")",   (int)ail.net.parser.CppToken.EType.eRightParens);
                AddToken(result, @"{",   (int)ail.net.parser.CppToken.EType.eLeftBrace);
                AddToken(result, @"}",   (int)ail.net.parser.CppToken.EType.eRightBrace);
                AddToken(result, @"[",   (int)ail.net.parser.CppToken.EType.eLeftBracket);
                AddToken(result, @"]",   (int)ail.net.parser.CppToken.EType.eRightBracket);

                AddToken(result, @"...", (int)ail.net.parser.CppToken.EType.eEllipses);
            }
            {
                // identifier
                ail.net.parser.Fsa fsa = new ail.net.parser.Fsa();

                ail.net.parser.FsaState q0 = fsa.AddState();
                ail.net.parser.FsaState q1 = fsa.AddState();
                ail.net.parser.FsaState q2 = fsa.AddState();

                fsa.AddTransition(q0, q1, "IsIdentifierNonDigitChar", ail.net.parser.CppLexAnalyzer.kIdentifierCharRank);
                fsa.AddTransition(q1, q1, "IsIdentifierChar", ail.net.parser.CppLexAnalyzer.kIdentifierCharRank);

                fsa.AddFinalState(q1, BuildToken(ail.net.parser.CppToken.EType.eIdentifier, ail.net.parser.LexAnalyzer.kDefaultTokenPriority));

                result.AddFsa(fsa);
            }

            result = result.Nfa2Dfa();
            result = result.Minimize(ail.net.parser.Fsa.EMinimizationMode.ePartition);

            return result;
        }

        public void GenerateCode(string xi_filename)
        {
            ail.net.framework.Assert.NonEmptyString(xi_filename, "xi_filename");
            ail.net.parser.Fsa fsa = BuildFsa();
            GenerateCode(xi_filename, fsa);
        }

        public static void Test()
        {
            ail.net.parser.CppLexAnalyzer lexer = new ail.net.parser.CppLexAnalyzer(new ail.net.parser.CppToken(), new ArrayList());

            try
            {
//                lexer.GenerateCode("c:\\tmp\\cppfsa.txt");

                lexer.Load("c:\\tmp\\cpptest.cpp", ail.net.parser.Context.ELoadMedia.eMediaFile);

                DateTime t1 = DateTime.Now;

                int count = 0;
                
                lexer.NextLexeme();
                count++;

                string lastlexeme = lexer.DecorateLexeme();
                
                while(lexer.Token.Type != (int)ail.net.parser.CppToken.EType.eEndOfStream)
                {
                    Console.WriteLine(lexer.DecorateLexeme());

                    lastlexeme = lexer.DecorateLexeme();

                    lexer.NextLexeme();

                    count++;

//                    Console.WriteLine("tokens: {0}, line: {1}, type: {2}", count, lexer.Token.LineNumber, lexer.Token.Type);
//                    System.Threading.Thread.Sleep(100);
                }

                Console.WriteLine(lastlexeme);

                DateTime t2 = DateTime.Now;
                Console.WriteLine("total count: {0}, time: {1}", count, t2-t1);
            }
            catch(Exception ex)
            {
                string m = ex.Message;
            }

            // statistics:
            //  cpp file with 1,931,233 lines
            //  FSA -> DFA
            //      total lexeme count: 11076805, time: 00:02:10.8781936
            //  FSA -> DFA -> MDFA (minimized fsa)
            //      total lexeme count: 11076805, time: 00:02:05.9010368
        }
        #endregion // methods
    };
}

#region epilog
#endregion
