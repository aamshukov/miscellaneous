//......................................................................................
// This is a part of UI Soft Library.  1989-2006 UI Soft Inc.               .
//......................................................................................
// THIS CODE MAY BE USED, COPIED, STORED, OR DISTRIBUTED ONLY IN ACCORDANCE WITH       .
// A WRITTEN LICENSE AGREEMENT AND WITH THE INCLUSION OF THIS COPYRIGHT NOTICE.        .
//......................................................................................

#region prolog
// file       :  
// description: Parser 
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
    /// summary description for Parser
    /// </summary>
    public abstract class Parser : IDisposable
    {
        #region constants
        public enum ELexerMode
        {
            eIgnoreWhitespace = 1,  // ignore ws
            eProcessWhitespace      // process ws
        };

        public enum EStatus
        {
            eUnknown = 1,
            eRecognized,
            eParsed,
            eFailed
        };
        #endregion // constants

        #region data members
        protected ail.net.parser.LexAnalyzer        LexerAttr;
        protected ail.net.parser.Parser.ELexerMode  LexerModeAttr;  // whitespace mode
        protected ail.net.parser.Grammar            GrammarAttr;
        protected ArrayList                         ErrorsAttr;
        protected ail.net.parser.Parser.EStatus     StatusAttr;     // result
        #endregion // data members

        #region ctor/dtor/finalizer
        public Parser(ail.net.parser.LexAnalyzer xi_lexer, ail.net.parser.Grammar xi_grammar, ArrayList xi_errors)
        {
            ail.net.framework.Assert.NonNullReference(xi_lexer, "xi_lexer");
            ail.net.framework.Assert.NonNullReference(xi_grammar, "xi_grammar");
            ail.net.framework.Assert.NonNullReference(xi_errors, "xi_errors");

            LexerAttr     = xi_lexer;
            LexerModeAttr = ail.net.parser.Parser.ELexerMode.eIgnoreWhitespace;
            GrammarAttr   = xi_grammar;
            ErrorsAttr    = xi_errors;
            StatusAttr    = ail.net.parser.Parser.EStatus.eUnknown;
        }

        ~Parser()
        {
            Dispose(false);
        }
        #endregion ctor/dtor/finalizer

        #region properties
        public ail.net.parser.LexAnalyzer Lexer
        {
            get
            {
                return LexerAttr;
            }
        }

        public ail.net.parser.Parser.ELexerMode LexerMode
        {
            get
            {
                return LexerModeAttr;
            }

            set
            {
                LexerModeAttr = value;
            }
        }

        public ail.net.parser.Grammar Grammar
        {
            get
            {
                return GrammarAttr;
            }
        }

        public ArrayList Errors
        {
            get
            {
                return ErrorsAttr;
            }
        }

        public ail.net.parser.Parser.EStatus Status
        {
            get
            {
                return StatusAttr;
            }

            set
            {
                StatusAttr = value;
            }
        }
        #endregion // properties

        #region methods
        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this); 
        }

        protected virtual void Dispose(bool xi_disposing)
        {
            if(xi_disposing)
            {
                // free managed objects
            }

            // free unmanaged objects, including base class
            // set large fields to null (de-reference)
        }
        #endregion // methods
    }
}

#region epilog
#endregion
