using System;
using System.Collections;
using System.IO;
using System.Threading;
using System.Globalization;
using System.Resources;
using System.Reflection;

namespace test
{
	class Application
	{
        public static void TestRes()
        {
            ail.net.parser.Context context = new ail.net.parser.Context();
            
//            FileInfo fi = new FileInfo("c:\\tmp\\Simulation.xml");
//            StreamReader reader = new StreamReader("c:\\tmp\\Simulation.xml");
            StreamReader reader = new StreamReader("c:\\tmp\\e.txt");

			StringReader sreader = new StringReader("test");

			context.Load("test", ail.net.parser.Context.ELoadMedia.eMediaString);
            context.Load("c:\\tmp\\e.txt", ail.net.parser.Context.ELoadMedia.eMediaFile);
            
            int r = ail.net.framework.Functor.Align(131, 16);
            int n = ail.net.framework.Functor.GetNextSize(131);

            string assembly_name = Assembly.GetExecutingAssembly().GetName().Name;
            string base_name = string.Format( "{0}.BaseResources", assembly_name);
            string s1 = ail.net.application.res.StringManager.EmptyStringException("q", "f1", 10);
        
            try
            {
                ail.net.framework.Assert.NonNullReference(null, "s");
            }
            catch(Exception ex)
            {
                string m = ex.Message;
            }
            try
            {
                string s = "";
                ail.net.framework.Assert.NonEmptyString(s, "s");
            }
            catch(Exception ex)
            {
                string m = ex.Message;
            }
            try
            {
                string s = "";
                ail.net.framework.Assert.ExpectedType(s, "s", 5.GetType());
            }
            catch(Exception ex)
            {
                string m = ex.Message;
            }
        }

        public static void TestObjectFactory()
        {
            try
            {
//                object o = ail.net.framework.ObjectFactory.Instance.Create("ail.net.parser.FsaSymbol");
//                Console.WriteLine(o.ToString());
            }
            catch(Exception ex)
            {
                string m = ex.Message;
            }
        }

        public static void TestFsa()
        {
            try
            {
/*
                ail.net.parser.Fsa fsa = new ail.net.parser.Fsa();

                ail.net.parser.FsaState q0 = fsa.AddState();
                q0.Label = q0.Id.ToString();
                ail.net.parser.FsaState q1 = fsa.AddState();
                q1.Label = q1.Id.ToString();
                ail.net.parser.FsaState q2 = fsa.AddState();
                q2.Label = q2.Id.ToString();
                ail.net.parser.FsaState q3 = fsa.AddState();
                q3.Label = q3.Id.ToString();
                ail.net.parser.FsaState q4 = fsa.AddState();
                q4.Label = q4.Id.ToString();
                ail.net.parser.FsaState q5 = fsa.AddState();
                q5.Label = q5.Id.ToString();
                ail.net.parser.FsaState q6 = fsa.AddState();
                q6.Label = q6.Id.ToString();
                ail.net.parser.FsaState q7 = fsa.AddState();
                q7.Label = q7.Id.ToString();
                ail.net.parser.FsaState q8 = fsa.AddState();
                q8.Label = q8.Id.ToString();
                ail.net.parser.FsaState q9 = fsa.AddState();
                q9.Label = q9.Id.ToString();
                ail.net.parser.FsaState q10 = fsa.AddState();
                q10.Label = q10.Id.ToString();
                ail.net.parser.FsaState q11 = fsa.AddState();
                q11.Label = q11.Id.ToString();
                ail.net.parser.FsaState q12 = fsa.AddState();
                q12.Label = q12.Id.ToString();
                ail.net.parser.FsaState q13 = fsa.AddState();
                q13.Label = q13.Id.ToString();
                ail.net.parser.FsaState q14 = fsa.AddState();
                q14.Label = q14.Id.ToString();

                fsa.AddTransition(q0, q1, "IsCharLowerCaseI");
                fsa.AddTransition(q1, q2, "IsCharLowerCaseF");

                fsa.AddTransition(q0, q3, ail.net.parser.FsaTransition.kEpsilonPredicate);
                fsa.AddTransition(q3, q4, "IsCharLowerCaseA");
                fsa.AddTransition(q4, q7, ail.net.parser.FsaTransition.kEpsilonPredicate);
                fsa.AddTransition(q7, q5, ail.net.parser.FsaTransition.kEpsilonPredicate);
                fsa.AddTransition(q5, q6, "IsCharLowerCaseA");
                fsa.AddTransition(q5, q6, "IsCharDecimalZero");
                fsa.AddTransition(q6, q7, ail.net.parser.FsaTransition.kEpsilonPredicate);

                fsa.AddTransition(q0, q8, ail.net.parser.FsaTransition.kEpsilonPredicate);
                fsa.AddTransition(q8, q9, "IsCharDecimalZero");
                fsa.AddTransition(q9, q12, ail.net.parser.FsaTransition.kEpsilonPredicate);
                fsa.AddTransition(q12, q10, ail.net.parser.FsaTransition.kEpsilonPredicate);
                fsa.AddTransition(q10, q11, "IsCharDecimalZero");
                fsa.AddTransition(q11, q12, ail.net.parser.FsaTransition.kEpsilonPredicate);

                fsa.AddTransition(q0, q13, ail.net.parser.FsaTransition.kEpsilonPredicate);
                fsa.AddTransition(q13, q14, "IsWhiteSpaceChar");

//                fsa.AddFinalState(q2, (int)ail.net.parser.ReToken.EType.eBar);
//                fsa.AddFinalState(q7, (int)ail.net.parser.ReToken.EType.eChar);
//                fsa.AddFinalState(q12, (int)ail.net.parser.ReToken.EType.eInteger);
//                fsa.AddFinalState(q14, (int)ail.net.parser.ReToken.EType.eHexChar);

//                fsa.Print();
*/
/*                
                foreach(ail.net.parser.FsaState state in fsa.States.Values)
                {
                    ail.net.parser.FsaStateSet eclosure = fsa.CalculateStateEclosure(state);
                    
                    if(eclosure.States.Count > 0)
                    {
                        Console.WriteLine("state: {0}", state.Id);
                        eclosure.Print();
                        Console.WriteLine("");

                        ail.net.parser.FsaStateSet move = fsa.CalculateMove(eclosure, "IsCharLowerCaseA");
                        
                        if(move.States.Count > 0)
                        {
                            Console.WriteLine("state: {0}", state.Id);
                            move.Print();
                            Console.WriteLine("");
                        }
                    }
                }
*/
//                ail.net.parser.Fsa nfa = fsa.Nfa2Dfa();
                
//                nfa.Print();

                {
                    // aho
                    ail.net.parser.Fsa dfa = new ail.net.parser.Fsa();

                    ail.net.parser.FsaState q0 = dfa.AddState();
                    q0.Label = "A";
                    ail.net.parser.FsaState q1 = dfa.AddState();
                    q1.Label = "B";
                    ail.net.parser.FsaState q2 = dfa.AddState();
                    q2.Label = "C";
                    ail.net.parser.FsaState q3 = dfa.AddState();
                    q3.Label = "D";
                    ail.net.parser.FsaState q4 = dfa.AddState();
                    q4.Label = "E";
                
                    dfa.AddTransition(q0, q1, "a");
                    dfa.AddTransition(q0, q2, "b");

                    dfa.AddTransition(q1, q1, "a");
                    dfa.AddTransition(q1, q3, "b");

                    dfa.AddTransition(q2, q2, "b");
                    dfa.AddTransition(q2, q1, "a");

                    dfa.AddTransition(q3, q1, "a");
                    dfa.AddTransition(q3, q4, "b");

                    dfa.AddTransition(q4, q1, "a");
                    dfa.AddTransition(q4, q2, "b");

                    dfa.AddFinalState(q4, new ail.net.parser.CppToken((int)ail.net.parser.CppToken.EType.eIdentifier, 0));

//                    ail.net.parser.Fsa mfa = dfa.Minimize(ail.net.parser.Fsa.EMinimizationMode.eTable);
                }
                {
                    // minimize_dfa.pdf
                    ail.net.parser.Fsa dfa = new ail.net.parser.Fsa();

                    ail.net.parser.FsaState q0 = dfa.AddState();
                    q0.Label = "A";
                    ail.net.parser.FsaState q1 = dfa.AddState();
                    q1.Label = "B";
                    ail.net.parser.FsaState q2 = dfa.AddState();
                    q2.Label = "C";
//                    ail.net.parser.FsaState q3 = dfa.AddState();
//                    q3.Label = "D";
                    ail.net.parser.FsaState q4 = dfa.AddState();
                    q4.Label = "E";
                    ail.net.parser.FsaState q5 = dfa.AddState();
                    q5.Label = "F";
                    ail.net.parser.FsaState q6 = dfa.AddState();
                    q6.Label = "G";
                    ail.net.parser.FsaState q7 = dfa.AddState();
                    q7.Label = "H";

                    dfa.AddTransition(q0, q1, "0");
                    dfa.AddTransition(q0, q5, "1");

                    dfa.AddTransition(q1, q6, "0");
                    dfa.AddTransition(q1, q2, "1");

                    dfa.AddTransition(q2, q0, "0");
                    dfa.AddTransition(q2, q2, "1");

//                    dfa.AddTransition(q3, q2, "0");
//                    dfa.AddTransition(q3, q6, "1");

                    dfa.AddTransition(q4, q7, "0");
                    dfa.AddTransition(q4, q5, "1");

                    dfa.AddTransition(q5, q2, "0");
                    dfa.AddTransition(q5, q6, "1");

                    dfa.AddTransition(q6, q6, "0");
                    dfa.AddTransition(q6, q4, "1");

                    dfa.AddTransition(q7, q6, "0");
                    dfa.AddTransition(q7, q2, "1");

                    dfa.AddFinalState(q2, new ail.net.parser.CppToken((int)ail.net.parser.CppToken.EType.eIdentifier, 0));
                    
                    ail.net.parser.Fsa mfa = dfa.Minimize(ail.net.parser.Fsa.EMinimizationMode.ePartition);
                    
                    Console.WriteLine(mfa.States.Count);
                }
            }
            catch(Exception ex)
            {
                string m = ex.Message;
            }
        }

        public static void TestLexAnalyzer()
        {
            try
            {
                ail.net.parser.ReLexAnalyzer lexer = new ail.net.parser.ReLexAnalyzer(new ail.net.parser.ReToken(), new ArrayList());

//                string ss = lexer.Token.GetTokenName(10);
//                string sc = lexer.Token.GetClassName();

                ail.net.parser.Fsa fsa = new ail.net.parser.Fsa();

                ail.net.parser.FsaState q0 = fsa.AddState();
                ail.net.parser.FsaState q1 = fsa.AddState();
                ail.net.parser.FsaState q2 = fsa.AddState();
                ail.net.parser.FsaState q3 = fsa.AddState();
                ail.net.parser.FsaState q4 = fsa.AddState();
                ail.net.parser.FsaState q5 = fsa.AddState();
                ail.net.parser.FsaState q6 = fsa.AddState();

                fsa.AddTransition(q0, q1, "IsCharLowerCaseF");
                fsa.AddTransition(q1, q2, "IsCharLowerCaseO");
                fsa.AddTransition(q2, q3, "IsCharLowerCaseR");
                fsa.AddTransition(q2, q4, "IsCharLowerCaseO");
                fsa.AddTransition(q4, q5, "IsCharLowerCaseL");
                fsa.AddTransition(q2, q6, "IsIdentifierChar", 1);
                fsa.AddTransition(q6, q6, "IsIdentifierChar", 1);
/*
                fsa.AddFinalState(q1, (int)ail.net.parser.Token.EType.eWhiteSpace);//.eIdentifier);
                fsa.AddFinalState(q2, (int)ail.net.parser.Token.EType.eWhiteSpace);//.eIdentifier);
                fsa.AddFinalState(q3, (int)ail.net.parser.Token.EType.eWhiteSpace);//.eFor);
                fsa.AddFinalState(q4, (int)ail.net.parser.Token.EType.eWhiteSpace);//.eIdentifier);
                fsa.AddFinalState(q5, (int)ail.net.parser.Token.EType.eWhiteSpace);//.eFool);
                fsa.AddFinalState(q6, (int)ail.net.parser.Token.EType.eWhiteSpace);//.eIdentifier);
*/

//                lexer.AddToken(fsa, "while", (int)ail.net.parser.Token.EType.eWhiteSpace/*.eWhile*/, (int)ail.net.parser.Token.EType.eWhiteSpace);//.eIdentifier);

//                fsa.Print();

                ail.net.parser.Fsa cloned_fsa = (ail.net.parser.Fsa)fsa.Clone();

//                fsa.Print();
                
                lexer.Load("forfool", ail.net.parser.Context.ELoadMedia.eMediaString);

                lexer.NextLexeme();
//                Console.WriteLine(lexer.Lexeme);

//                lexer.NextLexeme();
//                Console.WriteLine(lexer.Lexeme);
                
//                string code = lexer.GenerateCode(fsa);
//                Console.WriteLine(code);
                lexer.GenerateCode("c:\\tmp\\fsa.txt", fsa);
            }
            catch(Exception ex)
            {
                string m = ex.Message;
            }
        }

        [STAThread]
        static void Main(string[] args)
        {
//            ail.net.test.First3KSudkamp.Test();
//            ail.net.test.EffSet.Test();
            ail.net.test.FirstKSudkamp.Test();
            ail.net.test.KarpovLR1e.Test();



//            ail.net.parser.cs.CSharp.GenerateFsaCode();
            ail.net.parser.cs.CSharp.TestLexAnalyser();

//            ail.net.parser.cs.CSharpGrammar grammar = new ail.net.parser.cs.CSharpGrammar();
//            grammar.Generate(@"ss", @"c:\projects\ail.net\doc\cs.grammar.txt", @"c:\tmp\cs.grammar.gen.txt");


//            TestRes();
//            TestObjectFactory();
//            TestFsa();
//            TestLexAnalyzer();
//            ail.net.parser.CppLexAnalyzer.Test();
/*
            ail.net.test.FirstFollowLaK.Test();
            ail.net.test.FirstKSudkamp.Test();
            ail.net.test.First3KSudkamp.Test();
            ail.net.test.AhoLR0.Test();
            ail.net.test.SAaBbLR1e.Test();
            ail.net.test.AhoLR1e.Test();
            ail.net.test.KarpovLR1e.Test();
            ail.net.test.AhoLR1.Test();
            ail.net.test.AhoLR1conflicts.Test();
            ail.net.test.Ayc.Test();
            ail.net.test.GlrAlwaysBroken.Test();
            ail.net.test.Sss.Test();
            ail.net.test.Aho.Test();
            ail.net.test.Eps.Test();
 */ 
        }
	}
}
