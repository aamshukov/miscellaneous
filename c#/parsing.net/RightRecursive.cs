//......................................................................................
// This is a part of UI Soft Library. Copyright © 1989-2006 UI Soft Inc.               .
//......................................................................................
// THIS CODE MAY BE USED, COPIED, STORED, OR DISTRIBUTED ONLY IN ACCORDANCE WITH       .
// A WRITTEN LICENSE AGREEMENT AND WITH THE INCLUSION OF THIS COPYRIGHT NOTICE.        .
//......................................................................................

#region prolog
// file       : 
// description: RightRecursive
// package    : test
//
#endregion

#region import
using System;
using System.Collections;
#endregion

namespace ail.net.test
{
    public class RightRecursive
    {
        // S -> a S A A A
        // S -> e(psilon)
        // A -> a
        // A -> e(psilon)
        // .....................
        // a, aa, ..., aaaaaaaa
/*
        public static void Test()
        {
            // fsa
//          ail.net.test.RightRecursiveLexAnalyzer.GenerateCode(@"c:\tmp\RightRecursive.fsa.txt");
            
            // grammar
            ail.net.test.RightRecursiveGrammar grammar = new ail.net.test.RightRecursiveGrammar();
            
            grammar.Populate();
            Console.WriteLine(grammar.Decorate());

            // parser
            ArrayList errors = new ArrayList();

            ail.net.test.RightRecursiveLexAnalyzer lexer = new ail.net.test.RightRecursiveLexAnalyzer(new ail.net.test.RightRecursiveToken(), errors);
            lexer.Load("a", ail.net.parser.Context.ELoadMedia.eMediaString);
        
            ail.net.test.RightRecursiveEarleyParser parser = new ail.net.test.RightRecursiveEarleyParser(lexer, grammar, errors);
            
            parser.Semantics = new ail.net.test.RightRecursiveSemantics(lexer, errors);

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
