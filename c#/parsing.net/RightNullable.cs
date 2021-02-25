//......................................................................................
// This is a part of UI Soft Library. Copyright © 1989-2006 UI Soft Inc.               .
//......................................................................................
// THIS CODE MAY BE USED, COPIED, STORED, OR DISTRIBUTED ONLY IN ACCORDANCE WITH       .
// A WRITTEN LICENSE AGREEMENT AND WITH THE INCLUSION OF THIS COPYRIGHT NOTICE.        .
//......................................................................................

#region prolog
// file       : 
// description: RightNullable
// package    : test
//
#endregion

#region import
using System;
using System.Collections;
#endregion

namespace ail.net.test
{
    public class RightNullable
    {
        // S -> a A A A
        // S -> e(psilon)
        // A -> a
        // A -> e(psilon)
        // ..............
        // a, aa, aaa, aaaa
/*
        public static void Test()
        {
            // fsa
//          ail.net.test.RightNullableLexAnalyzer.GenerateCode(@"c:\tmp\RightNullable.fsa.txt");
            
            // grammar
            ail.net.test.RightNullableGrammar grammar = new ail.net.test.RightNullableGrammar();
            
            grammar.Populate();
            Console.WriteLine(grammar.Decorate());

            // parser
            ArrayList errors = new ArrayList();

            ail.net.test.RightNullableLexAnalyzer lexer = new ail.net.test.RightNullableLexAnalyzer(new ail.net.test.RightNullableToken(), errors);
            lexer.Load("a", ail.net.parser.Context.ELoadMedia.eMediaString);
        
            ail.net.test.RightNullableEarleyParser parser = new ail.net.test.RightNullableEarleyParser(lexer, grammar, errors);
            
            parser.Semantics = new ail.net.test.RightNullableSemantics(lexer, errors);

            ail.net.parser.AstNode ast = parser.Parse();

            if(ast != (object)null)
            {
                Console.WriteLine(parser.DecorateTree(ast));
            }
        }
*/
    }
}

#region epilog
#endregion
