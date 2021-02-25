//......................................................................................
// This is a part of UI Soft Library. Copyright © 1989-2006 UI Soft Inc.               .
//......................................................................................
// THIS CODE MAY BE USED, COPIED, STORED, OR DISTRIBUTED ONLY IN ACCORDANCE WITH       .
// A WRITTEN LICENSE AGREEMENT AND WITH THE INCLUSION OF THIS COPYRIGHT NOTICE.        .
//......................................................................................

#region prolog
// file       :  
// description: LexAnalyzer 
// package    : ail.net.parser
//
#endregion

#region import
using System;
using System.Collections;
using System.Text;
#endregion

namespace ail.net.parser
{
    /// <summary>
    /// summary description for LexAnalyzer
    /// </summary>
    public /*abstract*/ class LexAnalyzer : IDisposable //??
    {
        #region constants
        public enum EContext
        {
            // the following entry, MUST be the first entry in the enum
            eContextUnknown = 0
        };
        #endregion // constants

        #region data members
        private int                     PositionAttr;                                       // current position in context
        private int                     LineNumberAttr;								        // current line number
        private int                     LinePositionAttr;							        // position in line
        private ail.net.parser.Token    TokenAttr   = new ail.net.parser.Token();           // current lexeme
        private ail.net.parser.Context  ContextAttr = new ail.net.parser.Context();         // context
        private ArrayList               ErrorsAttr  = new ArrayList();                      // list of errors
		private char					CurrentAttr = ail.net.parser.Context.kEndOfStream;  // current cached char in context
        #endregion // data members

        #region ctor/dtor/finalizer
        public LexAnalyzer()
        {
        }

        ~LexAnalyzer()
        {
            Dispose(false);
        }
        #endregion ctor/dtor/finalizer

        #region properties
        public int Position
        {
            get
            {
                return PositionAttr;
            }

            set
            {
                PositionAttr = value;
            }
        }

        public int LineNumber
        {
            get
            {
                return LineNumberAttr;
            }

            set
            {
                LineNumberAttr = value;
            }
        }
        
        public int LinePosition
        {
            get
            {
                return LinePositionAttr;
            }

            set
            {
                LinePositionAttr = value;
            }
        }

        public ail.net.parser.Token Token
        {
            get
            {
                return TokenAttr;
            }
        }

        public ail.net.parser.Context Context
        {
            get
            {
                return ContextAttr;
            }
        }

        public ArrayList Errors
        {
            get
            {
                return ErrorsAttr;
            }
        }

        public string Lexeme
        {
            get
            {
                ail.net.framework.Assert.Condition(Token.Type != (int)Token.EType.eEndOfStream &&
                                                   Token.Type != (int)Token.EType.eUnknown, "ail.net.parser.LexAnalyser.Lexeme");
                string result = new string(Context.Data, Token.Offset, Token.Length);
                return result;
            }
        }

		public char Current
		{
			get
			{
				return CurrentAttr;
			}

			set
			{
				CurrentAttr = value;
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

        public void Load(string xi_str, ail.net.parser.Context.ELoadMedia xi_media)
        {
            Errors.Clear();
            Context.Load(xi_str, xi_media);

            Position         = 0;
            LineNumber       = 0;
            LinePosition     = 0;
            Token.Type       = (int)ail.net.parser.Token.EType.eUnknown;
            Token.Offset     = 0;
            Token.Length     = 0;
            Token.LineNumber = 0;
            Token.Position   = 0;
            Current          = ail.net.parser.Context.kEndOfStream;
        }

        public void AddToken(ail.net.parser.Fsa xi_fsa, string xi_token, int xi_token_type, string xi_escape_pr, int xi_escape_token_type, string xi_context)
        {

//            foreach(char it in xi_token)
            {
            }
        }

        public virtual void NextLexeme(int xi_context)
        {
            Prolog();

            // !!! -- generated code -- !!!
            int token = (int)ail.net.parser.Token.EType.eUnknown;

            Next();

            if(Current == ail.net.parser.Context.kEndOfStream)
            {
                goto _eos;
            }
            else if(ail.net.framework.CharPredicate.IsCharLowerCaseF(Current))
            {
                goto _q1;
            }
            else
            {
                goto _error;
            }
_q1:
            token  = (int)ail.net.parser.Token.EType.eIdentifier;

            Next();
            
            if(ail.net.framework.CharPredicate.IsCharLowerCaseO(Current))
            {
                goto _q2;
            }
            else if(ail.net.framework.CharPredicate.IsIdentifierChar(Current))
            {
                goto _q6;
            }
            else
            {
                goto _exit;
            }
_q2:
            token  = (int)ail.net.parser.Token.EType.eIdentifier;

            Next();
            
            if(ail.net.framework.CharPredicate.IsCharLowerCaseR(Current))
            {
                goto _q3;
            }
            else if(ail.net.framework.CharPredicate.IsCharLowerCaseO(Current))
            {
                goto _q4;
            }
            else if(ail.net.framework.CharPredicate.IsIdentifierChar(Current))
            {
                goto _q6;
            }
            else
            {
                goto _exit;
            }
_q3:
            token  = (int)ail.net.parser.Token.EType.eFor;

            if(ail.net.framework.CharPredicate.IsIdentifierChar(Current))
            {
                goto _q6;
            }
            else
            {
                goto _exit;
            }
_q4:
            token  = (int)ail.net.parser.Token.EType.eIdentifier;

            Next();
            
            if(ail.net.framework.CharPredicate.IsCharLowerCaseL(Current))
            {
                goto _q5;
            }
            else if(ail.net.framework.CharPredicate.IsIdentifierChar(Current))
            {
                goto _q6;
            }
            else
            {
                goto _exit;
            }
_q5:
            token  = (int)ail.net.parser.Token.EType.eFool;

            if(ail.net.framework.CharPredicate.IsIdentifierChar(Current))
            {
                goto _q6;
            }
            else
            {
                goto _exit;
            }
_q6:
            token  = (int)ail.net.parser.Token.EType.eIdentifier;

            Next();
            
            if(ail.net.framework.CharPredicate.IsIdentifierChar(Current))
            {
                goto _q6;
            }
            else
            {
                goto _exit;
            }




/*
_q1:
            Next();

            if(ail.net.framework.CharPredicate.IsCharLowerCaseO(Current))
            {
                goto _q2;
            }
            else if(ail.net.framework.CharPredicate.IsIdentifierChar(Current))
            {
                goto _q4;
            }

            goto _exit;
_q2:
            Next();

            if(ail.net.framework.CharPredicate.IsCharLowerCaseR(Current))
            {
                goto _q3;
            }
            else
            {
                Final((int)ail.net.parser.Token.EType.eIdentifier);
            }
            goto _exit;
_q3:
            // final state, token id: [Token.eFor]
            Next();

            if(ail.net.framework.CharPredicate.IsIdentifierChar(Current))
            {
                goto _q4;
            }
            Final((int)ail.net.parser.Token.EType.eFor);
            goto _exit;

_q4:
            // final state, token id: [Token.eIdentifier]
            Next();

            if(ail.net.framework.CharPredicate.IsIdentifierChar(Current))
            {
                goto _q4;
            }
            Final((int)ail.net.parser.Token.EType.eIdentifier);
            goto _exit;

*/
_error:
            if(Current != ail.net.parser.Context.kEndOfStream)
            {
                Next();
            }
            Final((int)ail.net.parser.Token.EType.eUnknown);
            goto _exit;
_eos:
            Final((int)Token.EType.eEndOfStream);
_exit:
            Final(token);
            // !!! -- end of generated code -- !!!
            Epilog();
            return;
        }

        public virtual void NextLexemeNoWhitespace(int xi_context)
        {
            do
            {
                NextLexeme(xi_context);
            }
            while(Token.Type == (int)Token.EType.eWhiteSpace  &&
                  Token.Type != (int)Token.EType.eEndOfStream &&
                  Token.Type != (int)Token.EType.eUnknown);
        }

        public virtual void LookAheadLexeme(ref ail.net.parser.Token xo_token, int xi_lookahead, int xi_context)
        {
        }

        public virtual string GenerateCode(ail.net.parser.Fsa xi_xsa)
        {
            const string tab1 = "    ";
            const string tab2 = "        ";

            // Environment.NewLine;

            StringBuilder result = new StringBuilder();

            return result.ToString();
        }

        protected virtual void Prolog()
        {
            Token.Type       = (int)ail.net.parser.Token.EType.eUnknown;
            Token.Offset     = Position;
            Token.Length     = 0;
            Token.LineNumber = 0;
            Token.Position   = 0;
        }
        
        protected virtual void Epilog()
        {
        }

        private void Next()
        {
            Current = Context.Data[Position++];

            if(ail.net.framework.CharPredicate.IsCharEol(Current))
            {
                LineNumber  += 1;
                LinePosition = 0;
            }
            else
            {
                LinePosition += 1;
            }

            Token.Length++;
        }

        private void Final(int xi_token_type)
        {
            Token.Type       = xi_token_type;
            Token.LineNumber = LineNumber;
            Token.Position   = LinePosition;
        }
        #endregion // methods
    }
}

#region epilog
#endregion
