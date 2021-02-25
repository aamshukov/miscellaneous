//......................................................................................
// This is a part of UI Soft Library. Copyright © 1989-2006 UI Soft Inc.               .
//......................................................................................
// THIS CODE MAY BE USED, COPIED, STORED, OR DISTRIBUTED ONLY IN ACCORDANCE WITH       .
// A WRITTEN LICENSE AGREEMENT AND WITH THE INCLUSION OF THIS COPYRIGHT NOTICE.        .
//......................................................................................

#region prolog
// file       : 
// description: GlrBroken
// package    : test
//
#endregion

#region import
using System;
using System.Collections;
#endregion

namespace ail.net.test
{
    public class GlrBroken
    {
        // S -> a D a d
        // S -> B D a b
        // D -> a A B
        // A -> a B B
        // A -> e(psilon)
        // B -> e(psilon)
        // ..............
        // aaab
/*
        public static void Test()
        {
            // fsa
//          ail.net.test.GlrBrokenLexAnalyzer.GenerateCode(@"c:\tmp\GlrBroken.fsa.txt");
            
            // grammar
            ail.net.test.GlrBrokenGrammar grammar = new ail.net.test.GlrBrokenGrammar();
            
            grammar.Populate();
            Console.WriteLine(grammar.Decorate());

            // parser
            ArrayList errors = new ArrayList();

            ail.net.test.GlrBrokenLexAnalyzer lexer = new ail.net.test.GlrBrokenLexAnalyzer(new ail.net.test.GlrBrokenToken(), errors);
            lexer.Load("aaab", ail.net.parser.Context.ELoadMedia.eMediaString);
        
            ail.net.test.GlrBrokenEarleyParser parser = new ail.net.test.GlrBrokenEarleyParser(lexer, grammar, errors);
            
            parser.Semantics = new ail.net.test.GlrBrokenSemantics(lexer, errors);

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
