//......................................................................................
// This is a part of UI Soft Library.  1989-2006 UI Soft Inc.               .
//......................................................................................
// THIS CODE MAY BE USED, COPIED, STORED, OR DISTRIBUTED ONLY IN ACCORDANCE WITH       .
// A WRITTEN LICENSE AGREEMENT AND WITH THE INCLUSION OF THIS COPYRIGHT NOTICE.        .
//......................................................................................

#region prolog
// file       : 
// description: Semantics
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
    /// summary description for Semantics
    /// </summary>
    public abstract class Semantics
    {
        #region data members
        protected ail.net.parser.LexAnalyzer  LexerAttr;
        protected ArrayList                   ErrorsAttr;
        #endregion // data members

        #region ctor/dtor/finalizer
        public Semantics(ail.net.parser.LexAnalyzer xi_lexer, ArrayList xi_errors)
        {
            ail.net.framework.Assert.NonNullReference(xi_lexer, "xi_lexer");
            ail.net.framework.Assert.NonNullReference(xi_errors, "xi_errors");

            LexerAttr  = xi_lexer;
            ErrorsAttr = xi_errors;
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

        public ArrayList Errors
        {
            get
            {
                return ErrorsAttr;
            }
        }
        #endregion // properties

        #region methods
        // called when the parsing is about to start
        public abstract ail.net.parser.AstNode Start(object xi_item);

        // called when the parsing is finished
        public abstract void End();

        // terminal action
        public abstract void HandleTerminal(ail.net.parser.AstNode xi_node, ail.net.parser.Token xi_token);

        // non-terminal actions
        public abstract ail.net.parser.AstNode HandleNonTerminalBefore(ail.net.parser.AstNode xi_node, object xi_item);
        public abstract ail.net.parser.AstNode HandleNonTerminalAfter(ail.net.parser.AstNode xi_node, object xi_item);

        // error recovery
        public abstract void HandleError(object xi_item, ail.net.parser.Token xi_token, int [] xi_error_costs);
        #endregion // methods
    }
}

#region epilog
#endregion
