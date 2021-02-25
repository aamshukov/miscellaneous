//......................................................................................
// This is a part of UI Soft Library. Copyright © 1989-2006 UI Soft Inc.               .
//......................................................................................
// THIS CODE MAY BE USED, COPIED, STORED, OR DISTRIBUTED ONLY IN ACCORDANCE WITH       .
// A WRITTEN LICENSE AGREEMENT AND WITH THE INCLUSION OF THIS COPYRIGHT NOTICE.        .
//......................................................................................

#region prolog
// file       : 
// description: FsaTransitionPredicate
// package    : ail.net.parser
//
#endregion

#region import
using System;
#endregion

namespace ail.net.parser
{
    /// <summary>
    /// summary description for FsaTransitionPredicate
    /// </summary>
    public class FsaTransitionPredicate : ICloneable
    {
        #region data members
        private string  TextAttr      = "";         // predicate
        private char    SwitchCharAttr = (char)0;   // short text predicate, indicates if predicate has simple form,
                                                    // and can be used in switched code generation
        private string  ContextAttr   = "";         // context, if(xi_context == eXmlContextPEReference && IsCharPercent(CURRENT))
        private int     RankAttr;                   // rank is a special attribute of a transition and it is used only during generation
                                                    // of code when "goto"-driven lexical analyzer is produced, allowing to shift
                                                    // more common predicates down in "goto" statements, default value is 0 and
                                                    // a rank with bigger value is more advanced in a "goto" statement,
                                                    // for example recognition of identifiers uses more general predicate
                                                    // IsIdentifierChar() than recognition of a keyword "while", IsCharLowerCaseW()
        #endregion // data members

        #region properties
        public string Text
        {
            get
            {
                return TextAttr;
            }

            set
            {
                TextAttr = value;
            }
        }

        public char SwitchChar
        {
            get
            {
                return SwitchCharAttr;
            }

            set
            {
                SwitchCharAttr = value;
            }
        }
        
        public string Context
        {
            get
            {
                return ContextAttr;
            }

            set
            {
                ContextAttr = value;
            }
        }

        public int Rank
        {
            get
            {
                return RankAttr;
            }

            set
            {
                RankAttr = value;
                ail.net.framework.Assert.Condition(Rank <= ail.net.parser.FsaTransition.kMaxRankValue, "value");
            }
        }
        #endregion // properties

        #region ctor/dtor/finalizer
        public FsaTransitionPredicate()
        {
        }

        public FsaTransitionPredicate(string xi_text)
        {
            TextAttr = xi_text;
        }

        public FsaTransitionPredicate(string xi_text, string xi_context)
        {
            TextAttr    = xi_text;
            ContextAttr = xi_context;
        }

        public FsaTransitionPredicate(string xi_text, string xi_context, int xi_rank)
        {
            TextAttr    = xi_text;
            ContextAttr = xi_context;
            RankAttr    = xi_rank;

            ail.net.framework.Assert.Condition(RankAttr < ail.net.parser.FsaTransition.kMaxRankValue, "value");
        }

        public FsaTransitionPredicate(string xi_text, char xi_switch_char, string xi_context, int xi_rank)
        {
            TextAttr    = xi_text;
            SwitchChar  = xi_switch_char;
            ContextAttr = xi_context;
            RankAttr    = xi_rank;

            ail.net.framework.Assert.Condition(RankAttr < ail.net.parser.FsaTransition.kMaxRankValue, "value");
        }
        #endregion ctor/dtor/finalizer

        #region methods
        public object Clone()
        {
            FsaTransitionPredicate result = new FsaTransitionPredicate();

            result.Text    = Text;
            result.Context = Context;
            result.Rank    = Rank;

            return result;
        }
        #endregion // methods
    }
}

#region epilog
#endregion
