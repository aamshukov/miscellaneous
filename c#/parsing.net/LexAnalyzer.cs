//......................................................................................
// This is a part of UI Soft Library. Copyright © 1989-2006 UI Soft Inc.               .
//......................................................................................
// THIS CODE MAY BE USED, COPIED, STORED, OR DISTRIBUTED ONLY IN ACCORDANCE WITH       .
// A WRITTEN LICENSE AGREEMENT AND WITH THE INCLUSION OF THIS COPYRIGHT NOTICE.        .
//......................................................................................
#region defines
#define GENERATE_SWITCHED_CODE
#endregion // defines

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
using System.IO;
#endregion

namespace ail.net.parser
{
    /// <summary>
    /// summary description for LexAnalyzer
    /// </summary>
    public abstract class LexAnalyzer : IDisposable
    {
        #region constants
        public enum EContext
        {
            // the following entry, MUST be the first entry in the enum
            eContextUnknown = 0
        };

        public enum ELexemeMode
        {
            eCurrent = 0,
            eLookAhead
        };

        protected const int kDefaultTokenPriority = 10;
        protected const int kEscapeTokenPriority  = 5;
        protected const string kTab3              = "            ";
        protected const string kTab4              = "                ";
        protected const string kTab5              = "                    ";
        #endregion // constants

        #region data members
        private int                                     PositionAttr;                                       // current position in context
        private int                                     LineNumberAttr;                                     // current line number
        private int                                     LinePositionAttr;                                   // position in line
        private ail.net.parser.Token                    TokenAttr;                                          // current lexeme
        private ail.net.parser.Token                    CachedTokenAttr;                                    // cached lexeme
        private int                                     PrevTokenTypeAttr;                                  // cached previous token type
        private ail.net.parser.Context                  ContextAttr = new ail.net.parser.Context();         // context
        private ail.net.parser.LexAnalyzer.ELexemeMode  LexemeModeAttr;                                     // lexeme mode calculation
        private ArrayList                               ErrorsAttr;                                         // list of errors
        private char                                    CurrentAttr = ail.net.parser.Context.kEndOfStream;  // current cached char in context
        protected ail.net.framework.ObjectFactory       FactoryAttr = new ail.net.framework.ObjectFactory();// token factory

        private int                                     TmpPositionAttr;        // \
        private int                                     TmpLineNumberAttr;      //  \
        private int                                     TmpLinePositionAttr;    //   - for backtracking Push/PopState()
        private int                                     TmpTokenLengthAttr;     //  /
        private int                                     TmpTokenIdAttr;         // /

        private Hashtable                               NoBacktrackingTokensAttr;
        private bool                                    HasBacktrackingAttr;
        #endregion // data members

        #region ctor/dtor/finalizer
        public LexAnalyzer(ail.net.parser.Token xi_token_class, ArrayList xi_errors)
        {
            ail.net.framework.Assert.NonNullReference(xi_token_class, "xi_token_class");
            ail.net.framework.Assert.NonNullReference(xi_errors, "xi_errors");

            TokenAttr           = xi_token_class;
            LexemeModeAttr      = ail.net.parser.LexAnalyzer.ELexemeMode.eCurrent;
            ErrorsAttr          = xi_errors;
            TmpTokenIdAttr      = (int)ail.net.parser.Token.EType.eUnknown;
            HasBacktrackingAttr = true;
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

            set
            {
                TokenAttr = value;
            }
        }

        public ail.net.parser.Token CachedToken
        {
            get
            {
                return CachedTokenAttr;
            }

            set
            {
                CachedTokenAttr = value;
            }
        }

        public int PrevTokenType
        {
            get
            {
                return PrevTokenTypeAttr;
            }

            set
            {
                PrevTokenTypeAttr = value;
            }
        }

        public ail.net.parser.Context Context
        {
            get
            {
                return ContextAttr;
            }
        }

        public ail.net.parser.LexAnalyzer.ELexemeMode LexemeMode
        {
            get
            {
                return LexemeModeAttr;
            }

            set
            {
                LexemeModeAttr = value;
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

        public ail.net.framework.ObjectFactory Factory
        {
            get
            {
                return FactoryAttr;
            }
        }

        public int TmpPosition
        {
            get
            {
                return TmpPositionAttr;
            }

            set
            {
                TmpPositionAttr = value;
            }
        }
        
        public int TmpLineNumber
        {
            get
            {
                return TmpLineNumberAttr;
            }

            set
            {
                TmpLineNumberAttr = value;
            }
        }

        public int TmpLinePosition
        {
            get
            {
                return TmpLinePositionAttr;
            }

            set
            {
                TmpLinePositionAttr = value;
            }
        }

        public int TmpTokenLength
        {
            get
            {
                return TmpTokenLengthAttr;
            }

            set
            {
                TmpTokenLengthAttr = value;
            }
        }

        public int TmpTokenId
        {
            get
            {
                return TmpTokenIdAttr;
            }

            set
            {
                TmpTokenIdAttr = value;
            }
        }

        public Hashtable NoBacktrackingTokens
        {
            get
            {
                // used only for generation, no need to create in run-time
                if(NoBacktrackingTokensAttr == null)
                {
                    NoBacktrackingTokensAttr = new Hashtable();
                }
                return NoBacktrackingTokensAttr;
            }
        }

        public bool HasBacktracking
        {
            get
            {
                return HasBacktrackingAttr;
            }

            set
            {
                HasBacktrackingAttr = value;
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
                ContextAttr = null;
                FactoryAttr = null;
            }

            // free unmanaged objects, including base class
            // set large fields to null (de-reference)
        }

        public bool IsEndOfStream()
        {
            return Current == ail.net.parser.Context.kEndOfStream;
        }

        public void Reset()
        {
            Position         = 0;
            LineNumber       = 0;
            LinePosition     = 0;
            Token.Type       = (int)ail.net.parser.Token.EType.eUnknown;
            Token.Offset     = 0;
            Token.Length     = 0;
            Token.LineNumber = 0;
            Token.Position   = 0;
            Token.Priority   = 0;
            CachedToken      = null;
            Current          = ail.net.parser.Context.kEndOfStream;
        }

        public virtual void Load(string xi_str, ail.net.parser.Context.ELoadMedia xi_media)
        {
            Errors.Clear();
            Context.Load(xi_str, xi_media);
            Reset();
        }

        public void AddToken(ail.net.parser.Fsa xi_fsa, string xi_token, int xi_token_type)
        {
            ail.net.framework.Assert.NonNullReference(xi_fsa, "xi_fsa");
            ail.net.framework.Assert.NonEmptyString(xi_token, "xi_token");

            AddToken(xi_fsa, xi_token, xi_token_type, ail.net.parser.Token.kUndefinedEscapeTokenType, "");
        }

        public void AddToken(ail.net.parser.Fsa xi_fsa, string xi_token, int xi_token_type, int xi_escape_token_type, string xi_escape_predicate)
        {
            ail.net.framework.Assert.NonNullReference(xi_fsa, "xi_fsa");
            ail.net.framework.Assert.NonEmptyString(xi_token, "xi_token");

            ail.net.parser.FsaState q1 = null;

            if(xi_fsa.StartState != (object)null)
            {
                q1 = xi_fsa.AddState();
                xi_fsa.AddTransition(xi_fsa.StartState, q1, ail.net.parser.FsaTransition.kEpsilonPredicate);
            }
            else
            {
                q1 = xi_fsa.AddState();
            }

            ail.net.parser.FsaState eq = null; // escape state

            if(xi_escape_token_type != ail.net.parser.Token.kUndefinedEscapeTokenType)
            {
                eq = xi_fsa.AddState();
                xi_fsa.AddTransition(eq, eq, xi_escape_predicate, ail.net.parser.FsaTransition.kMaxRankValue);

                ail.net.parser.Token token = (ail.net.parser.Token)Factory.Create(Token.GetType());

                token.Type = xi_escape_token_type;
                token.Priority = ail.net.parser.LexAnalyzer.kEscapeTokenPriority;

                xi_fsa.AddFinalState(eq, token);
            }

            ail.net.parser.FsaState q_prev = q1;
            ail.net.parser.FsaState q_curr = q1;

            for(int i = 0; i < xi_token.Length; i++)
            {
                q_curr = xi_fsa.AddState();

                ail.net.framework.Assert.NonNullReference(q_curr, "q_curr");

                xi_fsa.AddTransition(q_prev,
                                     q_curr,
                                     ail.net.framework.CharPredicate.BuildAsciiCharPredicate(xi_token[i]),
                                     (char)xi_token[i]);

                if(i == xi_token.Length-1)
                {
                    ail.net.parser.Token token = (ail.net.parser.Token)Factory.Create(Token.GetType());

                    token.Type = xi_token_type;
                    token.Priority = ail.net.parser.LexAnalyzer.kDefaultTokenPriority;

                    xi_fsa.AddFinalState(q_curr, token);
                }
                else if(xi_escape_token_type != ail.net.parser.Token.kUndefinedEscapeTokenType)
                {
                    ail.net.parser.Token token = (ail.net.parser.Token)Factory.Create(Token.GetType());

                    token.Type = xi_escape_token_type;
                    token.Priority = ail.net.parser.LexAnalyzer.kEscapeTokenPriority;

                    xi_fsa.AddFinalState(q_curr, token);
                }

                if(xi_escape_token_type != ail.net.parser.Token.kUndefinedEscapeTokenType)
                {
                    xi_fsa.AddTransition(q_curr, eq, xi_escape_predicate, ail.net.parser.FsaTransition.kMaxRankValue);
                }

                q_prev = q_curr;
            }
        }

        public ail.net.parser.Token BuildToken()
        {
            return (ail.net.parser.Token)Factory.Create(Token.GetType());
        }

        public ail.net.parser.Token BuildToken(object xi_token_type, int xi_priority)
        {
            ail.net.framework.Assert.CheckEnumItemRange(xi_token_type, "xi_token_type", xi_token_type.GetType());
            return (ail.net.parser.Token)Factory.Create(Token.GetType(), new object [] {xi_token_type, xi_priority});
        }

        public virtual void NextLexeme()
        {
            NextLexeme(0);
        }

        public virtual void NextLexeme(int xi_context)
        {
            PrevTokenType = (Token != (object)null) ? (int)Token.Type : (int)Token.EType.eUnknown;

            if(CachedToken != null)
            {
                Token = CachedToken;
                CachedToken = null;
            }
            else
            {
                NextLexemeImpl(xi_context);
            }
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

        public virtual void NextLexemeImpl(int xi_context)
        {
            Prolog();
            // !!! -- generated code -- !!!
            // !!! -- end of generated code -- !!!
            Epilog();
        }

        public virtual void LookAheadLexeme(int xi_context)
        {
            // create cached token
            CachedToken = BuildToken();

            // set look ahead mode
            LexemeMode = ail.net.parser.LexAnalyzer.ELexemeMode.eLookAhead;

            // get lexeme
            NextLexemeImpl(xi_context);

            // restore lexeme mode
            LexemeMode = ail.net.parser.LexAnalyzer.ELexemeMode.eCurrent;
        }

        public void DoNotBacktrack(int xi_token_type)
        {
            if(!NoBacktrackingTokens.Contains(xi_token_type))
            {
                NoBacktrackingTokens.Add(xi_token_type, xi_token_type);
            }
        }

        public void GenerateCode(string xi_filename, ail.net.parser.Fsa xi_fsa)
        {
            ail.net.framework.Assert.NonEmptyString(xi_filename, "xi_filename");
            ail.net.framework.Assert.NonNullReference(xi_fsa, "xi_fsa");

            string result = GenerateCode(xi_fsa);
            ail.net.framework.Assert.NonEmptyString(result, "result");

            StreamWriter writer = new StreamWriter(xi_filename);

            writer.Write(result);
            writer.Flush();
            writer.Close();
        }

        public string GenerateCode(ail.net.parser.Fsa xi_fsa)
        {
            ail.net.framework.Assert.NonNullReference(xi_fsa, "xi_fsa");

            xi_fsa.ResetMarkedStates();

            StringBuilder result = new StringBuilder();

            result.Append(kTab3);
            result.Append(@"Next();");
            result.Append(Environment.NewLine);
            
            result.Append(Environment.NewLine);
            result.Append(kTab3);
            result.Append(@"if(Current == ail.net.parser.Context.kEndOfStream)");
            result.Append(Environment.NewLine);
            result.Append(kTab3);
            result.Append(@"{");
            result.Append(Environment.NewLine);
            result.Append(kTab4);
            result.Append(@"goto _eos;");
            result.Append(Environment.NewLine);
            result.Append(kTab3);
            result.Append(@"}");
#if GENERATE_SWITCHED_CODE
            result.Append(GenerateStartStateSwitchCode(xi_fsa.StartState));
            result.Append(Environment.NewLine);
            result.Append(Environment.NewLine);
            result.Append(kTab3);
            result.Append(@"goto _error;");
#else
            result.Append(GenerateStartStateCode(xi_fsa.StartState));
            result.Append(Environment.NewLine);
            result.Append(kTab3);
            result.Append(@"else");
            result.Append(Environment.NewLine);
            result.Append(kTab3);
            result.Append(@"{");
            result.Append(Environment.NewLine);
            result.Append(kTab4);
            result.Append(@"goto _error;");
            result.Append(Environment.NewLine);
            result.Append(kTab3);
            result.Append(@"}");
#endif
            GenerateStateCodeWithBacktracking(xi_fsa, result);
            
            result.Append(Environment.NewLine);
            result.Append(@"_error:");
            result.Append(Environment.NewLine);
            result.Append(kTab3);
            result.Append(@"if(Current != ail.net.parser.Context.kEndOfStream)");
            result.Append(Environment.NewLine);
            result.Append(kTab3);
            result.Append(@"{");
            result.Append(Environment.NewLine);
            result.Append(kTab4);
            result.Append(@"Next();");
            result.Append(Environment.NewLine);
            result.Append(kTab3);
            result.Append(@"}");
            result.Append(Environment.NewLine);
            result.Append(kTab3);
            result.Append(@"Final((int)ail.net.parser.Token.EType.eUnknown);");
            result.Append(Environment.NewLine);
            result.Append(kTab3);
            result.Append(@"goto _epilog;");
            result.Append(Environment.NewLine);
            result.Append(@"_eos:");
            result.Append(Environment.NewLine);
            result.Append(kTab3);
            result.Append(@"Final((int)ail.net.parser.Token.EType.eEndOfStream);");
            result.Append(Environment.NewLine);
            result.Append(kTab3);
            result.Append(@"goto _epilog;");
            result.Append(Environment.NewLine);
            result.Append(@"_exit:");
            result.Append(Environment.NewLine);
            result.Append(kTab3);
            result.Append(@"Final(TmpTokenId);");
            result.Append(Environment.NewLine);
            result.Append(@"_epilog:");
            result.Append(Environment.NewLine);

            return result.ToString();
        }

        private static string GenerateStartStateCode(ail.net.parser.FsaState xi_state)
        {
            ail.net.framework.Assert.NonNullReference(xi_state, "xi_state");

            StringBuilder result = new StringBuilder();

            for(int rank = 0; ; rank++) // fix point
            {
                int length = result.Length;

                foreach(ail.net.parser.FsaTransition transition in xi_state.Transitions.Values)
                {
                    ail.net.framework.Assert.NonNullReference(transition, "transition");
                    
                    if(transition.Predicate.Rank == rank)
                    {
                        result.Append(Environment.NewLine);
                        result.Append(kTab3);
                        result.Append(@"else if(");

                        if(transition.Predicate.Context.Length != 0)
                        {
                            result.Append("xi_context == ");
                            result.Append(transition.Predicate.Context);
                            result.Append(" && ");
                        }

                        result.Append(transition.Predicate.Text);
                        result.Append(@"(Current))");
                        result.Append(Environment.NewLine);
                        result.Append(kTab3);
                        result.Append(@"{");
                        result.Append(Environment.NewLine);
                        result.Append(kTab4);
                        result.Append(@"goto _q");
                        result.Append(transition.End.ToString());
                        result.Append(@";");
                        result.Append(Environment.NewLine);
                        result.Append(kTab3);
                        result.Append(@"}");
                    }
                }

                if(result.Length == length && rank > ail.net.parser.FsaTransition.kMaxRankValue)
                {
                    break;
                }
            }

            return result.ToString();
        }

#if GENERATE_SWITCHED_CODE
        private static string GenerateStartStateSwitchCode(ail.net.parser.FsaState xi_state)
        {
            ail.net.framework.Assert.NonNullReference(xi_state, "xi_state");

            StringBuilder result = new StringBuilder();

            result.Append(Environment.NewLine);
            result.Append(Environment.NewLine);
            result.Append(kTab3);
            result.Append(@"switch(Current)");
            result.Append(Environment.NewLine);
            result.Append(kTab3);
            result.Append(@"{");

            for(int rank = 0;; rank++) // fix point
            {
                int length = result.Length;

                foreach(ail.net.parser.FsaTransition transition in xi_state.Transitions.Values)
                {
                    ail.net.framework.Assert.NonNullReference(transition, "transition");

                    if(transition.Predicate.Rank == rank && transition.Predicate.SwitchChar != (char)0 && transition.Predicate.Context.Length == 0)
                    {
                        result.Append(Environment.NewLine);
                        result.Append(kTab4);
                        result.Append(@"case '");
                        if(transition.Predicate.SwitchChar == '\\' || transition.Predicate.SwitchChar == '\'')
                        {
                            result.Append(@"\");
                        }
                        result.Append(transition.Predicate.SwitchChar);
                        result.Append(@"':");
                        result.Append(Environment.NewLine);
                        result.Append(kTab5);
                        result.Append(@"goto _q");
                        result.Append(transition.End.ToString());
                        result.Append(@";");
                    }
                }

                if(result.Length == length && rank > ail.net.parser.FsaTransition.kMaxRankValue)
                {
                    break;
                }
            }

            result.Append(Environment.NewLine);
            result.Append(kTab3);
            result.Append(@"}");
            result.Append(Environment.NewLine);

            for(int rank = 0, i = 0;; rank++) // fix point
            {
                int length = result.Length;

                foreach(ail.net.parser.FsaTransition transition in xi_state.Transitions.Values)
                {
                    ail.net.framework.Assert.NonNullReference(transition, "transition");
                    
                    if(transition.Predicate.Rank == rank && transition.Predicate.SwitchChar == (char)0)
                    {
                        result.Append(Environment.NewLine);
                        result.Append(kTab3);

                        if(i > 0)
                        {
                            result.Append(@"else ");
                        }
                        else
                        {
                            i++;
                        }

                        result.Append(@"if(");

                        if(transition.Predicate.Context.Length != 0)
                        {
                            result.Append("xi_context == ");
                            result.Append(transition.Predicate.Context);
                            result.Append(" && ");
                        }

                        result.Append(transition.Predicate.Text);
                        result.Append(@"(Current))");
                        result.Append(Environment.NewLine);
                        result.Append(kTab3);
                        result.Append(@"{");
                        result.Append(Environment.NewLine);
                        result.Append(kTab4);
                        result.Append(@"goto _q");
                        result.Append(transition.End.ToString());
                        result.Append(@";");
                        result.Append(Environment.NewLine);
                        result.Append(kTab3);
                        result.Append(@"}");
                    }
                }

                if(result.Length == length && rank > ail.net.parser.FsaTransition.kMaxRankValue)
                {
                    break;
                }
            }

            return result.ToString();
        }
#endif

        private string GenerateStateCode(ail.net.parser.FsaState xi_state)
        {
            ail.net.framework.Assert.NonNullReference(xi_state, "xi_state");

            StringBuilder result = new StringBuilder();

            result.Append(Environment.NewLine);
            result.Append(@"_q");
            result.Append(xi_state.Id.ToString());
            result.Append(@":");

            bool finalstate = xi_state.Papa.FinalStates.Contains(xi_state.Id);

            if(finalstate)
            {
                result.Append(Environment.NewLine);
                result.Append(kTab3);
                result.Append(@"PushState((int)");
                result.Append(Token.GetClassName());
                result.Append(@".EType.");
                result.Append(Token.GetTokenName(xi_state.Token.Type));
                result.Append(@"); // save accepted state for backtracking");
                result.Append(Environment.NewLine);
            }

            result.Append(Environment.NewLine);
            result.Append(kTab3);
            result.Append(@"Next();");
            result.Append(Environment.NewLine);

            for(int rank = 0, i = 0; ; rank++) // fix point
            {
                int length = result.Length;

                foreach(ail.net.parser.FsaTransition transition in xi_state.Transitions.Values)
                {
                    ail.net.framework.Assert.NonNullReference(transition, "transition");
                    
                    if(transition.Predicate.Rank == rank)
                    {
                        result.Append(Environment.NewLine);
                        result.Append(kTab3);

                        if(i > 0)
                        {
                            result.Append(@"else ");
                        }
                        else
                        {
                            i++;
                        }

                        result.Append(@"if(");

                        if(transition.Predicate.Context.Length != 0)
                        {
                            result.Append("xi_context == ");
                            result.Append(transition.Predicate.Context);
                            result.Append(" && ");
                        }

//                      result.Append(@"ail.net.framework.CharPredicate.");
                        result.Append(transition.Predicate.Text);
                        result.Append(@"(Current))");
                        result.Append(Environment.NewLine);
                        result.Append(kTab3);
                        result.Append(@"{");
                        result.Append(Environment.NewLine);
                        result.Append(kTab4);
                        result.Append(@"goto _q");
                        result.Append(transition.End.ToString());
                        result.Append(@";");
                        result.Append(Environment.NewLine);
                        result.Append(kTab3);
                        result.Append(@"}");
                    }
                }

                if(result.Length == length && rank > ail.net.parser.FsaTransition.kMaxRankValue)
                {
                    break;
                }
            }

            if(HasBacktracking && !finalstate)
            {
                if(xi_state.Transitions.Values.Count > 0)
                {
                    result.Append(Environment.NewLine);
                    result.Append(kTab3);
                    result.Append(@"else");
                    result.Append(Environment.NewLine);
                    result.Append(kTab3);
                    result.Append(@"{");
                    result.Append(Environment.NewLine);
                    result.Append(kTab4);
                }
                else
                {
                    result.Append(kTab3);
                }

                result.Append(@"PopState(); // restore the last accepted state, backtracking");

                if(xi_state.Transitions.Values.Count > 0)
                {
                    result.Append(Environment.NewLine);
                    result.Append(kTab3);
                    result.Append(@"}");
                }
            }

            result.Append(Environment.NewLine);
            result.Append(kTab3);
            result.Append(@"goto _exit;");

            return result.ToString();
        }

        private void GenerateStateCodeWithBacktracking(ail.net.parser.Fsa xi_fsa, StringBuilder xio_code)
        {
            ail.net.framework.Assert.NonNullReference(xi_fsa, "xi_fsa");
            ail.net.framework.Assert.NonNullReference(xi_fsa.StartState, "xi_fsa.StartState");

            GenerateStateCodeWalker(xi_fsa, xi_fsa.StartState, 0, xio_code);
        }

        private void GenerateStateCodeWalker(ail.net.parser.Fsa xi_fsa, ail.net.parser.FsaState xi_state, int xi_token_type, StringBuilder xio_code)
        {
            ail.net.framework.Assert.NonNullReference(xi_state, "xi_state");

            if(xi_state.Id != xi_fsa.StartState.Id) //  start state was generated earley with switch/case code
            {
                xi_state.Marked = true;

                xio_code.Append(Environment.NewLine);
                xio_code.Append(@"_q");
                xio_code.Append(xi_state.Id.ToString());
                xio_code.Append(@":");

                bool finalstate = xi_state.Papa.FinalStates.Contains(xi_state.Id);

                if(finalstate && xi_state.Token != (object)null)
                {
                    xio_code.Append(Environment.NewLine);
                    xio_code.Append(kTab3);
                    xio_code.Append(@"PushState((int)");
                    xio_code.Append(Token.GetClassName());
                    xio_code.Append(@".EType.");
                    xio_code.Append(Token.GetTokenName(xi_state.Token.Type));
                    xio_code.Append(@"); // save accepted state for backtracking");
                    xio_code.Append(Environment.NewLine);
                }

                xio_code.Append(Environment.NewLine);
                xio_code.Append(kTab3);
                xio_code.Append(@"Next();");
                xio_code.Append(Environment.NewLine);

                for(int rank = 0, i = 0; ; rank++) // fix point
                {
                    int length = xio_code.Length;

                    foreach(ail.net.parser.FsaTransition transition in xi_state.Transitions.Values)
                    {
                        ail.net.framework.Assert.NonNullReference(transition, "transition");
                        
                        if(transition.Predicate.Rank == rank)
                        {
                            xio_code.Append(Environment.NewLine);
                            xio_code.Append(kTab3);

                            if(i > 0)
                            {
                                xio_code.Append(@"else ");
                            }
                            else
                            {
                                i++;
                            }

                            xio_code.Append(@"if(");

                            if(transition.Predicate.Context.Length != 0)
                            {
                                xio_code.Append("xi_context == ");
                                xio_code.Append(transition.Predicate.Context);
                                xio_code.Append(" && ");
                            }

                            xio_code.Append(transition.Predicate.Text);
                            xio_code.Append(@"(Current))");
                            xio_code.Append(Environment.NewLine);
                            xio_code.Append(kTab3);
                            xio_code.Append(@"{");
                            xio_code.Append(Environment.NewLine);
                            xio_code.Append(kTab4);
                            xio_code.Append(@"goto _q");
                            xio_code.Append(transition.End.ToString());
                            xio_code.Append(@";");
                            xio_code.Append(Environment.NewLine);
                            xio_code.Append(kTab3);
                            xio_code.Append(@"}");
                        }
                    }

                    if(xio_code.Length == length && rank > ail.net.parser.FsaTransition.kMaxRankValue)
                    {
                        break;
                    }
                }

                if(!finalstate && HasBacktracking && !NoBacktrackingTokens.Contains(xi_token_type))
                {
                    if(xi_state.Transitions.Values.Count > 0)
                    {
                        xio_code.Append(Environment.NewLine);
                        xio_code.Append(kTab3);
                        xio_code.Append(@"else");
                        xio_code.Append(Environment.NewLine);
                        xio_code.Append(kTab3);
                        xio_code.Append(@"{");
                        xio_code.Append(Environment.NewLine);
                        xio_code.Append(kTab4);
                    }
                    else
                    {
                        xio_code.Append(kTab3);
                    }

                    xio_code.Append(@"PopState(); // restore the last accepted state, backtracking");

                    if(xi_state.Transitions.Values.Count > 0)
                    {
                        xio_code.Append(Environment.NewLine);
                        xio_code.Append(kTab3);
                        xio_code.Append(@"}");
                    }
                }

                xio_code.Append(Environment.NewLine);
                xio_code.Append(kTab3);
                xio_code.Append(@"goto _exit;");
            }

            int token_type = xi_token_type;

            if(xi_state.Token != (object)null)
            {
                token_type = xi_state.Token.Type;
            }

            foreach(ail.net.parser.FsaTransition transition in xi_state.Transitions.Values)
            {
                ail.net.framework.Assert.NonNullReference(transition, "transition");

                ail.net.parser.FsaState state = (ail.net.parser.FsaState)xi_fsa.States[transition.End];
                ail.net.framework.Assert.NonNullReference(state, "state");

                if(!state.Marked)
                {
                    GenerateStateCodeWalker(xi_fsa, state, token_type, xio_code);
                }
            }
        }

        protected virtual void Prolog()
        {
            if(LexemeMode == ail.net.parser.LexAnalyzer.ELexemeMode.eCurrent)
            {
                Token.Type       = (int)ail.net.parser.Token.EType.eUnknown;
                Token.Offset     = Position;
                Token.Length     = 0;
                Token.LineNumber = 0;
                Token.Position   = 0;
            }
            else // look ahead mode
            {
                CachedToken.Type       = (int)ail.net.parser.Token.EType.eUnknown;
                CachedToken.Offset     = Position;
                CachedToken.Length     = 0;
                CachedToken.LineNumber = 0;
                CachedToken.Position   = 0;
            }

            TmpPositionAttr     = 0;
            TmpLineNumberAttr   = 0;
            TmpLinePositionAttr = 0;
            TmpTokenLengthAttr  = 0;
            TmpTokenId          = (int)ail.net.parser.Token.EType.eUnknown;
        }
        
        protected virtual void Epilog()
        {
        }

        protected void Next()
        {
            Current = Context.Data[Position++];

            if(ail.net.framework.CharPredicate.IsCharNL(Current))
            {
                LineNumber  += 1;
                LinePosition = 0;
            }
            else
            {
                LinePosition += 1;
            }

            if(LexemeMode == ail.net.parser.LexAnalyzer.ELexemeMode.eCurrent)
            {
                Token.Length++;
            }
            else // look ahead mode
            {
                CachedToken.Length++;
            }
        }

        protected void PushState(int xi_token_type)
        {
            TmpPosition     = Position;
            TmpLineNumber   = LineNumber;
            TmpLinePosition = LinePosition;

            if(LexemeMode == ail.net.parser.LexAnalyzer.ELexemeMode.eCurrent)
            {
                TmpTokenLength = Token.Length;
            }
            else // look ahead mode
            {
                TmpTokenLength = CachedToken.Length;
            }

            TmpTokenId = xi_token_type;
        }

        protected void PopState()
        {
            Position     = TmpPosition+1;
            LineNumber   = TmpLineNumber;
            LinePosition = TmpLinePosition;

            if(LexemeMode == ail.net.parser.LexAnalyzer.ELexemeMode.eCurrent)
            {
                Token.Length = TmpTokenLength+1;
            }
            else // look ahead mode
            {
                CachedToken.Length = TmpTokenLength+1;
            }
        }

        protected void Final(int xi_token_type)
        {
            Position = Math.Max(0, --Position);

            if(ail.net.framework.CharPredicate.IsCharNL(Current))
            {
                LineNumber = Math.Max(0, --LineNumber);
                LinePosition = 0;
            }
            else
            {
                LinePosition = Math.Max(0, --LinePosition);
            }

            if(LexemeMode == ail.net.parser.LexAnalyzer.ELexemeMode.eCurrent)
            {
                Token.Type       = xi_token_type;
                Token.Length     = Token.Length-1;
                Token.LineNumber = LineNumber;
                Token.Position   = Math.Max(0, LinePosition-Token.Length);
            }
            else // look ahead mode
            {
                CachedToken.Type       = xi_token_type;
                CachedToken.Length     = CachedToken.Length-1;
                CachedToken.LineNumber = LineNumber;
                CachedToken.Position   = Math.Max(0, LinePosition-CachedToken.Length);
            }
        }

        public string DecorateLexeme()
        {
            StringBuilder result = new StringBuilder();

            result.Append(Lexeme.Length == 0 ? "[<<<NULL>>>]" : (Token.Type == (int)ail.net.parser.Token.EType.eWhiteSpace ? ".." : "\""+Lexeme+"\""));

            result.Append(" ["+Token.GetTokenName(Token.Type)+"], ["+Token.Type+"] offset: ");
            result.Append(Token.Offset);
            result.Append(", length: ");
            result.Append(Token.Length);
            result.Append(", position in line: ");
            result.Append(Token.Position);
            result.Append(", line: ");
            result.Append(Token.LineNumber);
            result.Append(Environment.NewLine);

            return result.ToString();
        }

        public void Print(ail.net.parser.Fsa xi_fsa)
        {
            ail.net.framework.Assert.NonNullReference(xi_fsa, "xi_fsa");

            Console.WriteLine("states: {0}{1}", xi_fsa.States.Count, '\n');

            ArrayList states = new ArrayList(xi_fsa.States.Values);
            states.Sort(); // states must be numbered in sequence

            foreach(ail.net.parser.FsaState state in states)
            {
                string text = string.Format("start state: [{0}]", state.Id);

                if(state.Label.Length > 0)
                {
                    text += string.Format(" \"{0}\"", state.Label);
                }
                
                if(xi_fsa.IsStartState(state))
                {
                    text += " [start]";
                }

                if(xi_fsa.IsFinalState(state))
                {
                    text += " [final: ";
                    text += Token.GetTokenName(state.Token.Type);
                    text += "]";
                }

                Console.WriteLine(text);

                foreach(ail.net.parser.FsaTransition it in state.Transitions.Values)
                {
                    text = string.Format("end state: [{0}] [{1}]", it.End, it.Predicate.Text);
                    Console.WriteLine(text);
                }

                Console.WriteLine("");
            }
        }
        #endregion // methods
    }
}

#region epilog
#endregion
