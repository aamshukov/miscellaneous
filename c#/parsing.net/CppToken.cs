//......................................................................................
// This is a part of UI Soft Library.  1989-2006 UI Soft Inc.               .
//......................................................................................
// THIS CODE MAY BE USED, COPIED, STORED, OR DISTRIBUTED ONLY IN ACCORDANCE WITH       .
// A WRITTEN LICENSE AGREEMENT AND WITH THE INCLUSION OF THIS COPYRIGHT NOTICE.        .
//......................................................................................

#region prolog
// file       : 
// description: CppToken
// package    : ail.net.parser
//
#endregion

#region import
using System;
#endregion

namespace ail.net.parser
{
    /// <summary>
    /// summary description for CppToken
    /// </summary>
    public class CppToken : ail.net.parser.Token
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

            // preprocessor
            ePpIf,
            ePpIfdef,
            ePpIfndef,
            ePpElif,
            ePpElse,
            ePpEndif,
            ePpDefine,
            ePpUndef,
            ePpInclude,
            ePpLine,
            ePpError,
            ePpPragma,
            ePpDelimiter,
            ePpConcat,
            ePpNumberSign,
            ePpImport,
            ePpUsing,

            // comments
            eCComments,
            eCppComments,

            // literals
            eUniversalCharNameShort,    // \u0A5F
            eUniversalCharNameLong,     // \U0A5F2E6B
            eDecimalIntegerLiteral,     // 1234567890[L|l|U|u]
            eOctalIntegerLiteral,       // 01234567[L|l|U|u]
            eHexIntegerLiteral,         // 0x0123456789ABCDEF[L|l|U|u]
            eFloatLiteral,              // 56.768[E|e][+|-]1024[f|F|l|L]
            eCharLiteral,               // 'a' '\r\n' '\123' '\xFF' 
            eStringLiteral,             // "abc \t\n \123 \xFF"

            // identifier
            eIdentifier,

            // keywords
            eAuto,
            eBool,
            eBreak,
            eCase,
            eCatch,
            eChar,
            eClass,
            eConst,
            eConstCast,
            eContinue,
            eDefault,
            eDelete,
            eDeprecated,
            eDllexport,
            eDllimport,
            eDo,
            eDouble,
            eDynamicCast,
            eElse,
            eEnum,
            eExplicit,
            eExtern,
            eFalse,
            eFloat,
            eFor,
            eFriend,
            eGoto,
            eIf,
            eInline,
            eInt,
            eLong,
            eMutable,
            eNaked,
            eNamespace,
            eNew,
            eNoinline,
            eNoreturn,
            eNothrow,
            eNovtable,
            eOperator,
            ePrivate,
            eProperty,
            eProtected,
            ePublic,
            eRegister,
            eReinterpretCast,
            eReturn,
            eSelectany,
            eShort,
            eSigned,
            eSizeof,
            eStatic,
            eStaticCast,
            eStruct,
            eSwitch,
            eTemplate,
            eThis,
            eThread,
            eThrow,
            eTrue,
            eTry,
            eTypedef,
            eTypeid,
            eTypename,
            eUnion,
            eUnsigned,
            eUsing,
            eUuid,
            eVirtual,
            eVoid,
            eVolatile,
            eWchar,                     // wchar_t
            eWhile,

            // keywords [microsoft specific]
            eMS_Abstract,               //__abstract
            eMS_Alignof,                // __alignof
            eMS_Asm,                    // __asm
            eMS_Assume,                 // __assume
            eMS_Based,                  // __based
            eMS_Box,                    // __box
            eMS_Cdecl,                  // __cdecl
            eMS_Declspec,               // __declspec
            eMS_Delegate,               // __delegate
            eMS_Event,                  // __event
            eMS_Except,                 // __except
            eMS_Fastcall,               // __fastcall
            eMS_Finally,                // __finally
            eMS_Forceinline,            // __forceinline
            eMS_Gc,                     // __gc
            eMS_Hook,                   // __hook
            eMS_Identifier,             // __identifier
            eMS_If_exists,              // __if_exists
            eMS_If_not_exists,          // __if_not_exists
            eMS_Inline,                 // __inline
            eMS_Int8,                   // __int8
            eMS_Int16,                  // __int16
            eMS_Int32,                  // __int32
            eMS_Int64,                  // __int64
            eMS_Interface,              // __interface
            eMS_Leave,                  // __leave
            eMS_M64,                    // __m64
            eMS_M128,                   // __m128
            eMS_M128d,                  // __m128d
            eMS_M128i,                  // __m128i
            eMS_MultipleInheritance,    // __multiple_inheritance
            eMS_Nogc,                   // __nogc
            eMS_Noop,                   // __noop
            eMS_Pin,                    // __pin
            eMS_Property,               // __property
            eMS_Raise,                  // __raise
            eMS_Sealed,                 // __sealed
            eMS_SingleInheritance,      // __single_inheritance
            eMS_Stdcall,                // __stdcall
            eMS_Super,                  // __super
            eMS_Trycast,                // __try_cast
            eMS_Try,                    // __try
            eMS_Unhook,                 // __unhook
            eMS_Uuidof,                 // __uuidof
            eMS_Value,                  // __value
            eMS_Virtual_inheritance,    // __virtual_inheritance
            eMS_W64,                    // __w64
            eMS_Wchar,                  // __wchar_t

            // operators
            eAddition,                  // +
            eAdditionAssignment,        // +=
            eIncrement,                 // ++
            eSubtraction,               // -
            eSubtractionAssignment,     // -=
            eDecrement,                 // --
            eMultiplication,            // *
            eMultiplicationAssignment,  // *=
            eDivision,                  // /
            eDivisionAssignment,        // /=
            eModulus,                   // %
            eModulusAssignment,         // %=

            eLogicalNegotian,           // !
            eBitwiseAnd,                // &
            eBitwiseAndAssignment,      // &=
            eBitwiseOr,                 // |
            eBitwiseOrAssignment,       // |=
            eBitwiseXor,                // ^
            eBitwiseXorAssignment,      // ^=
            eComplement,                // ~

            eAssignment,                // =
            eEquality,                  // ==
            eNotEqual,                  // !=
            eLessThan,                  // <
            eLessThanOrEqual,           // <=
            eGreaterThan,               // >
            eGreaterThanOrEqual,        // >=

            eLogicalAnd,                // &&
            eLogicalOr,                 // ||
            eConditional,               // ?

            eLeftShift,                 // <<
            eLeftShiftAssignment,       // <<=
            eRightShift,                // >>
            eRightShiftAssignment,      // <<=

            eLeftParens,                // (
            eRightParens,               // )
            eLeftBrace,                 // {
            eRightBrace,                // }
            eLeftBracket,               // [
            eRightBracket,              // ]

            eBackSlash,                 // '\'
            eSemicolon,                 // ;
            eSingleQuote,               // '
            eColon,                     // :
            eDoubleQuote,               // "
            eComma,                     // ,
            eMemberAccessDot,           // .
            eNumberSign,                // #
            eScopeResolution,           // ::
            eMemberAccessArrow,         // ->
            ePtrTomemberDot,            // .*
            ePtrTomemberArrow,          // ->*
            eEllipses,                  // ...

            // digraphs
            eDigraphLeftBrace,
            eDigraphRightBrace,
            eDigraphLeftBracket,
            eDigraphRightBracket,
            eDigraphNumberSign,
            eDigraphNumberSign2,

            // trigraphs
            eTrigraphNumberSign,
            eTrigraphBackSlash,
            eTrigraphCircum,
            eTrigraphLeftBracket,
            eTrigraphRightBracket,
            eTrigraphBar,
            eTrigraphLeftBrace,
            eTrigraphRightBrace,
            eTrigraphTilda,

            // alternatives
            eAltBitAnd,
            eAltAnd,
            eAltAndEq,
            eAltBitOr,
            eAltOr,
            eAltOrEq,
            eAltXor,
            eAltXorEq,
            eAltNot,
            eAltNotEq,
            eAltComplement,

            eTranslationUnit,
            eDeclSpecifierSeqOpt,
            eDeclSpecifierSeq,
            eDeclSpecifier,
            eDeclarator,
            eTypeSpecifier,
            eSimpleTypeSpecifier,
            eCvQualifierSeqOpt,
            eCvQualifierSeq,
            eCvQualifier,
            eClassName,
            ePtrOperator,
            eParameterDeclarationClause,
            eParameterDeclarationListOpt,
            eParameterDeclarationList,
            eParameterDeclaration,
            eEllipsesOpt,

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

            "ePpIf",
            "ePpIfdef",
            "ePpIfndef",
            "ePpElif",
            "ePpElse",
            "ePpEndif",
            "ePpDefine",
            "ePpUndef",
            "ePpInclude",
            "ePpLine",
            "ePpError",
            "ePpPragma",
            "ePpDelimiter",
            "ePpConcat",
            "ePpNumberSign",
            "ePpImport",
            "ePpUsing",

            "eCComments",
            "eCppComments",

            "eUniversalCharNameShort",
            "eUniversalCharNameLong",
            "eDecimalIntegerLiteral",
            "eOctalIntegerLiteral",
            "eHexIntegerLiteral",
            "eFloatLiteral",
            "eCharLiteral",
            "eStringLiteral",
            "eIdentifier",

            "eAuto",
            "eBool",
            "eBreak",
            "eCase",
            "eCatch",
            "eChar",
            "eClass",
            "eConst",
            "eConstCast",
            "eContinue",
            "eDefault",
            "eDelete",
            "eDeprecated",
            "eDllexport",
            "eDllimport",
            "eDo",
            "eDouble",
            "eDynamicCast",
            "eElse",
            "eEnum",
            "eExplicit",
            "eExtern",
            "eFalse",
            "eFloat",
            "eFor",
            "eFriend",
            "eGoto",
            "eIf",
            "eInline",
            "eInt",
            "eLong",
            "eMutable",
            "eNaked",
            "eNamespace",
            "eNew",
            "eNoinline",
            "eNoreturn",
            "eNothrow",
            "eNovtable",
            "eOperator",
            "ePrivate",
            "eProperty",
            "eProtected",
            "ePublic",
            "eRegister",
            "eReinterpretCast",
            "eReturn",
            "eSelectany",
            "eShort",
            "eSigned",
            "eSizeof",
            "eStatic",
            "eStaticCast",
            "eStruct",
            "eSwitch",
            "eTemplate",
            "eThis",
            "eThread",
            "eThrow",
            "eTrue",
            "eTry",
            "eTypedef",
            "eTypeid",
            "eTypename",
            "eUnion",
            "eUnsigned",
            "eUsing",
            "eUuid",
            "eVirtual",
            "eVoid",
            "eVolatile",
            "eWchar",
            "eWhile",

            "eMS_Abstract",
            "eMS_Alignof",
            "eMS_Asm",
            "eMS_Assume",
            "eMS_Based",
            "eMS_Box",
            "eMS_Cdecl",
            "eMS_Declspec",
            "eMS_Delegate",
            "eMS_Event",
            "eMS_Except",
            "eMS_Fastcall",
            "eMS_Finally",
            "eMS_Forceinline",
            "eMS_Gc",
            "eMS_Hook",
            "eMS_Identifier",
            "eMS_If_exists",
            "eMS_If_not_exists",
            "eMS_Inline",
            "eMS_Int8",
            "eMS_Int16",
            "eMS_Int32",
            "eMS_Int64",
            "eMS_Interface",
            "eMS_Leave",
            "eMS_M64",
            "eMS_M128",
            "eMS_M128d",
            "eMS_M128i",
            "eMS_MultipleInheritance",
            "eMS_Nogc",
            "eMS_Noop",
            "eMS_Pin",
            "eMS_Property",
            "eMS_Raise",
            "eMS_Sealed",
            "eMS_SingleInheritance",
            "eMS_Stdcall",
            "eMS_Super",
            "eMS_Trycast",
            "eMS_Try",
            "eMS_Unhook",
            "eMS_Uuidof",
            "eMS_Value",
            "eMS_Virtual_inheritance",
            "eMS_W64",
            "eMS_Wchar",

            "eAddition",
            "eAdditionAssignment",
            "eIncrement",
            "eSubtraction",
            "eSubtractionAssignment",
            "eDecrement",
            "eMultiplication",
            "eMultiplicationAssignment",
            "eDivision",
            "eDivisionAssignment",
            "eModulus",
            "eModulusAssignment",

            "eLogicalNegotian",
            "eBitwiseAnd",
            "eBitwiseAndAssignment",
            "eBitwiseOr",
            "eBitwiseOrAssignment",
            "eBitwiseXor",
            "eBitwiseXorAssignment",
            "eComplement",

            "eAssignment",
            "eEquality",
            "eNotEqual",
            "eLessThan",
            "eLessThanOrEqual",
            "eGreaterThan",
            "eGreaterThanOrEqual",

            "eLogicalAnd",
            "eLogicalOr",
            "eConditional",

            "eLeftShift",
            "eLeftShiftAssignment",
            "eRightShift",
            "eRightShiftAssignment",

            "eLeftParens",
            "eRightParens",
            "eLeftBrace",
            "eRightBrace",
            "eLeftBracket",
            "eRightBracket",

            "eBackSlash",
            "eSemicolon",
            "eSingleQuote",
            "eColon",
            "eDoubleQuote",
            "eComma",
            "eMemberAccessDot",
            "eNumberSign",
            "eScopeResolution",
            "eMemberAccessArrow",
            "ePtrTomemberDot",
            "ePtrTomemberArrow",
            "eEllipses",

            "eDigraphLeftBrace",
            "eDigraphRightBrace",
            "eDigraphLeftBracket",
            "eDigraphRightBracket",
            "eDigraphNumberSign",
            "eDigraphNumberSign2",

            "eTrigraphNumberSign",
            "eTrigraphBackSlash",
            "eTrigraphCircum",
            "eTrigraphLeftBracket",
            "eTrigraphRightBracket",
            "eTrigraphBar",
            "eTrigraphLeftBrace",
            "eTrigraphRightBrace",
            "eTrigraphTilda",

            "eAltBitAnd",
            "eAltAnd",
            "eAltAndEq",
            "eAltBitOr",
            "eAltOr",
            "eAltOrEq",
            "eAltXor",
            "eAltXorEq",
            "eAltNot",
            "eAltNotEq",
            "eAltComplement",

            "eTranslationUnit",
            "eDeclSpecifierSeqOpt",
            "eDeclSpecifierSeq",
            "eDeclSpecifier",
            "eDeclarator",
            "eTypeSpecifier",
            "eSimpleTypeSpecifier",
            "eCvQualifierSeqOpt",
            "eCvQualifierSeq",
            "eCvQualifier",
            "eClassName",
            "ePtrOperator",
            "eParameterDeclarationClause",
            "eParameterDeclarationListOpt",
            "eParameterDeclarationList",
            "eParameterDeclaration",
            "eEllipsesOpt"
        };
        #endregion // constants

        #region ctor/dtor/finalizer
        public CppToken()
        {
        }

        public CppToken(int xi_type, int xi_priority) : base(xi_type, xi_priority)
        {
        }
        #endregion ctor/dtor/finalizer

        #region methods
        public override object Clone()
        {
            CppToken result = new CppToken();

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
            const string name = "ail.net.parser.CppToken";
            return name;
        }

        public override string GetTokenName(int xi_token_type)
        {
            return Names[xi_token_type];
        }

        public override int GetTokenSize()
        {
            return (int)ail.net.parser.CppToken.EType.eSize;;
        }
        #endregion // methods
    }
}

#region epilog
#endregion
