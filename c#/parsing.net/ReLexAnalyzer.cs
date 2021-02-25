//......................................................................................
// This is a part of UI Soft Library. Copyright © 1989-2006 UI Soft Inc.               .
//......................................................................................
// THIS CODE MAY BE USED, COPIED, STORED, OR DISTRIBUTED ONLY IN ACCORDANCE WITH       .
// A WRITTEN LICENSE AGREEMENT AND WITH THE INCLUSION OF THIS COPYRIGHT NOTICE.        .
//......................................................................................

#region prolog
// file       : 
// description: ReLexAnalyzer
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
    /// summary description for ReLexAnalyzer
    /// </summary>
    public class ReLexAnalyzer : ail.net.parser.LexAnalyzer
    {
        #region constants
        public new enum EContext
        {
            // the following entry, MUST be the first entry in the enum
            eContextUnknown,
            eContextRepetition,
            eContextClassName
        };
        #endregion // constants

        #region data members
        #endregion // data members

        #region ctor/dtor/finalizer
        public ReLexAnalyzer(ail.net.parser.ReToken xi_token_class, ArrayList xi_errors) : base(xi_token_class, xi_errors)
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

        public static ail.net.parser.Fsa BuildFsa()
        {
            ail.net.parser.Fsa result = new ail.net.parser.Fsa();
            return result;
        }

        public void GenerateCode(string xi_filename)
        {
            ail.net.framework.Assert.NonEmptyString(xi_filename, "xi_filename");

            ail.net.parser.Fsa fsa = BuildFsa();

            GenerateCode(xi_filename, fsa);
        }

        static void Test(string xi_re)
        {
        }
        #endregion // methods
    };
}

#region epilog
#endregion
