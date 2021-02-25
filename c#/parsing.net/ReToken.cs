//......................................................................................
// This is a part of UI Soft Library. Copyright © 1989-2006 UI Soft Inc.               .
//......................................................................................
// THIS CODE MAY BE USED, COPIED, STORED, OR DISTRIBUTED ONLY IN ACCORDANCE WITH       .
// A WRITTEN LICENSE AGREEMENT AND WITH THE INCLUSION OF THIS COPYRIGHT NOTICE.        .
//......................................................................................

#region prolog
// file       : 
// description: ReToken
// package    : ail.net.parser
//
#endregion

#region import
using System;
#endregion

namespace ail.net.parser
{
    /// <summary>
    /// summary description for ReToken
    /// </summary>
    public class ReToken : ail.net.parser.Token
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

            eXor,               // 5
            eDollar,
            eDot,
            eMultiply,
            ePlus,
            eDash,
            eQuestionMark,
            eComma,
            eBar,
            eColon,
            eSlash,
            eBackSlash,
            eLeftParens,
            eRightParens,
            eLeftBrace,
            eRightBrace,        // 20
            eLeftBracket,
            eRightBracket,

            eLowerS,
            eUpperS,
            eLowerD,
            eUpperD,
            eLowerW,
            eUpperW,
            eHorTab,
            eVerTab,            // 30
            eCarRet,
            eNewLine,

            eAlnum,
            eAlpha,
            eBlank,
            eCntrl,
            eDigit,
            eLower,
            ePrint,
            ePunct,             // 40
            eSpace,
            eUpper,
            eGraph,
            eXdigit,

            eInteger,
            eChar,
            eHexChar,           // 47

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

            "eXor",
            "eDollar",
            "eDot",
            "eMultiply",
            "ePlus",
            "eDash",
            "eQuestionMark",
            "eComma",
            "eBar",
            "eColon",
            "eSlash",
            "eBackSlash",
            "eLeftParens",
            "eRightParens",
            "eLeftBrace",
            "eRightBrace",
            "eLeftBracket",
            "eRightBracket",

            "eLowerS",
            "eUpperS",
            "eLowerD",
            "eUpperD",
            "eLowerW",
            "eUpperW",
            "eHorTab",
            "eVerTab",
            "eCarRet",
            "eNewLine",

            "eAlnum",
            "eAlpha",
            "eBlank",
            "eCntrl",
            "eDigit",
            "eLower",
            "ePrint",
            "ePunct",
            "eSpace",
            "eUpper",
            "eGraph",
            "eXdigit",

            "eInteger",
            "eChar",
            "eHexChar"
        };
        #endregion // constants

        #region ctor/dtor/finalizer
        public ReToken()
        {
        }
        #endregion ctor/dtor/finalizer

        #region methods
        public override object Clone()
        {
            ReToken result = new ReToken();

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
            const string name = "ail.net.parser.ReToken";
            return name;
        }

        public override string GetTokenName(int xi_token_type)
        {
            return Names[xi_token_type];
        }
        #endregion // methods
    }
}

#region epilog
#endregion
