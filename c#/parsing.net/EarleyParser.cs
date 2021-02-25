//......................................................................................
// This is a part of UI Soft Library. Copyright © 1989-2006 UI Soft Inc.               .
//......................................................................................
// THIS CODE MAY BE USED, COPIED, STORED, OR DISTRIBUTED ONLY IN ACCORDANCE WITH       .
// A WRITTEN LICENSE AGREEMENT AND WITH THE INCLUSION OF THIS COPYRIGHT NOTICE.        .
//......................................................................................
#region defines
#define PRINT_STATS
#endregion // defines

#region prolog
// file       : 
// description: EarleyParser
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
    /// summary description for EarleyParser
    /// </summary>
    public abstract class EarleyParser : ail.net.parser.Parser
    {
        #region constants
        [FlagsAttribute]
        private enum EFlags : uint
        {
            eInitAction   = 0x00000001, // .
            eScanner      = 0x00000002, //  .
            ePredictor    = 0x00000004, //   . which action introduced item
            eCompleter    = 0x00000008, //  .
            eErrorScanner = 0x00000010, // .
            eErrorMask    = 0x07000000,
            eMarked       = 0x00000080
        };

        public enum EParserMode
        {
            eRecognizer,
            eParser
        };

        public const int kMaxErrorCost = 5;
        #endregion // constants

        #region data types
        public class CoreItem
        {
            public int                        Id;   // unique id
            public ail.net.parser.GrammarRule Rule; // production (rule)
            public int                        Dot;  // dot - position in rhs,
                                                    // if Dot = rhs.count it means it points to the end of the rhs
        };

        public class Item
        {
#if PRINT_STATS
            public int                                  Id;            // unique id
#endif
            public ail.net.parser.EarleyParser.CoreItem CoreItem;      // pointer to static core item
            public ail.net.parser.EarleyParser.Chart    OriginalChart; // pointer to the orinal set/chart
            public ail.net.parser.EarleyParser.Chart    MasterChart;   // chart it belongs to
            public ail.net.parser.EarleyParser.Item     Lptr;          // pointer to left brother
            public Hashtable                            Rptrs;         // rightmost child(s), if grammar is ambiguous
            public uint                                 Flags;         // action (predictor, completer, scanner, errorscanner), error cost
        }

        protected struct ItemKey
        {
            public ail.net.parser.EarleyParser.CoreItem CoreItem;      // pointer to static core item
            public ail.net.parser.EarleyParser.Chart    OriginalChart; // pointer to the orinal set/chart
            public ail.net.parser.EarleyParser.Item     Lptr;          // pointer to left brother

            public static bool operator == (ItemKey xi_lhs, ItemKey xi_rhs)
            {
                // no args assertion!!!
                bool result = (object)xi_lhs.CoreItem == (object)xi_rhs.CoreItem           &&
                              (object)xi_lhs.OriginalChart == (object)xi_rhs.OriginalChart &&
                              (object)xi_lhs.Lptr == (object)xi_rhs.Lptr;

                return result;
            }

            public static bool operator != (ItemKey xi_lhs, ItemKey xi_rhs)
            {
                // no args assertion!!!
                return !(xi_lhs == xi_rhs);
            }

            public override bool Equals(object xi_rhs)
            {
                // no args assertion!!!
                return this == ((ItemKey)xi_rhs);
            }

            public override int GetHashCode()
            {
                // no args assertion!!!
                return ail.net.framework.Functor.DualIntHash(CoreItem.Id, OriginalChart.Id);
            }
        }

#if PRINT_STATS
        protected struct ItemComparer : IComparer
        {
            public int Compare(object xi_i1, object xi_i2)
            {
                ail.net.parser.EarleyParser.Item i1 = (ail.net.parser.EarleyParser.Item)xi_i1;
                ail.net.parser.EarleyParser.Item i2 = (ail.net.parser.EarleyParser.Item)xi_i2;

                int result = 0;

                if(i1.Id < i2.Id)
                {
                    result = -1;
                }
                else if(i1.Id > i2.Id)
                {
                    result = 1;
                }

                return result;
            }
        }
#endif
        public class Chart
        {
            public int                  Id;             // unique id
            public Hashtable            Items;          // list of items
            public ArrayList            PredictorItems; // items in predictor list
            public int                  PredictedK;     // optimization
            public ArrayList            CompleterItems; // items in completer list
            public int                  CompletedK;     // optimization
            public ArrayList            ScannerItems;   // items in scanner list
            public ail.net.parser.Token Token;          // context link
        };
        #endregion // data types

        #region data members
        private ArrayList                               ChartsAttr = new ArrayList();       // list of sets/charts
        private ArrayList                               CoreItemTableAttr;                  // prebuild core items table

        private Hashtable                               PredictTableAttr;                   // prediction table, [non-terminal][list of core items]
        private bool []                                 PredictedNonTerminalsAttr;          // vector of predicted non-terminals for set
        private bool []                                 PredictedNonTerminalsZeroizerAttr;  // predefined vector of 'false' values for quick clean up

        private ail.net.parser.EarleyParser.EParserMode ParserModeAttr;                     // recognize or parse

        private bool                                    ExecutePredictorAttr;               // flag indicates if predictor should proceed
        private bool                                    ExecuteCompleterAttr;               // flag indicates if completer should proceed

        private ail.net.parser.Semantics                SemanticsAttr;                      // semantics interface
        #endregion // data members

        #region ctor/dtor/finalizer
        public EarleyParser(ail.net.parser.LexAnalyzer xi_lexer, ail.net.parser.Grammar xi_grammar, ArrayList xi_errors)
            : base(xi_lexer, xi_grammar, xi_errors)
        {
            ParserModeAttr = ail.net.parser.EarleyParser.EParserMode.eRecognizer;
        }

       ~EarleyParser()
        {
            Dispose(false);
        }
        #endregion ctor/dtor/finalizer

        #region properties
        public ArrayList Charts
        {
            get
            {
                return ChartsAttr;
            }
        }

        public ArrayList CoreItemTable
        {
            get
            {
                return CoreItemTableAttr;
            }
        }
        
        public Hashtable PredictTable
        {
            get
            {
                return PredictTableAttr;
            }
        }

        public bool [] PredictedNonTerminals
        {
            get
            {
                return PredictedNonTerminalsAttr;
            }
        }

        public bool [] PredictedNonTerminalsZeroizer
        {
            get
            {
                return PredictedNonTerminalsZeroizerAttr;
            }
        }

        public ail.net.parser.EarleyParser.EParserMode ParserMode
        {
            get
            {
                return ParserModeAttr;
            }

            set
            {
                ParserModeAttr = value;
            }
        }

        public bool ExecutePredictor
        {
            get
            {
                return ExecutePredictorAttr;
            }

            set
            {
                ExecutePredictorAttr = value;
            }
        }

        public bool ExecuteCompleter
        {
            get
            {
                return ExecuteCompleterAttr;
            }

            set
            {
                ExecuteCompleterAttr = value;
            }
        }

        public ail.net.parser.Semantics Semantics
        {
            get
            {
                return SemanticsAttr;
            }

            set
            {
                SemanticsAttr = value;
            }
        }
        #endregion // properties

        #region methods
        protected override void Dispose(bool xi_disposing)
        {
            if(xi_disposing)
            {
                // free managed objects
                ChartsAttr                        = null;
                CoreItemTableAttr                 = null;
                PredictTableAttr                  = null;
                PredictedNonTerminalsAttr         = null;
                PredictedNonTerminalsZeroizerAttr = null;
            }

            // free unmanaged objects, including base class
            // set large fields to null (de-reference)
        }

        public ail.net.parser.AstNode Parse()
        {
            ail.net.framework.Assert.NonNullReference(Semantics, "Semantics");
            ail.net.parser.AstNode result = null;

            if(BuildChartList())
            {
                if(ParserMode == ail.net.parser.EarleyParser.EParserMode.eParser)
                {
                    result = BuildAst();
                }
            }

            return result;
        }

        private bool BuildChartList()
        {
            // build initial set
            bool result = false;

            ail.net.parser.EarleyParser.Chart chart = BuildInitialSet();

            if(chart != (object)null)
            {
                Closure(chart);

                result = true;

                // build list of sets (fixed point)
                for(;;)
                {
                    ail.net.parser.EarleyParser.Chart prev_chart = chart;

                    if(LexerMode == ail.net.parser.EarleyParser.ELexerMode.eIgnoreWhitespace)
                    {
                        // skip whitespace
                        do
                        {
                            Lexer.NextLexeme();
                        }
                        while(Lexer.Token.Type == (int)ail.net.parser.Token.EType.eWhiteSpace);
                    }
                    else
                    {
                        Lexer.NextLexeme();
                    }

                    if(Lexer.Token.Type == (int)ail.net.parser.Token.EType.eEndOfStream)
                    {
                        if(IsChartCompleted(chart))
                        {
                            Status = ail.net.parser.Parser.EStatus.eRecognized;
                        }
                        else
                        {
                            result = false;

                            Status = ail.net.parser.Parser.EStatus.eFailed;

                            chart = ErrorScan(prev_chart);

                            Closure(chart);
                        }

                        break;
                    }

                    chart = Scan(chart);

                    if(chart == null)
                    {
                        result = false;

                        Status = ail.net.parser.Parser.EStatus.eFailed;

                        chart = ErrorScan(prev_chart);

                        if(chart == null)
                        {
                            break;
                        }
                    }

                    Closure(chart);
                }
            }

#if PRINT_STATS
            if(Charts.Count < 16)
            {
                Console.WriteLine(DecorateCharts());
            }
            else
            {
                Console.WriteLine(DecorateChart((ail.net.parser.EarleyParser.Chart)Charts[Charts.Count-1]));
            }
#endif
            return result;
        }

        private ail.net.parser.AstNode BuildAst()
        {
            ail.net.framework.Assert.Condition(Charts.Count > 0, "ail.net.parser.EareyParser.BuildAst: Charts.Count > 0");

            ail.net.parser.AstNode result = null;

            foreach(ail.net.parser.EarleyParser.Item start_item in ((ail.net.parser.EarleyParser.Chart)Charts[Charts.Count-1]).Items.Values)
            {
                if(IsRecognizedItem(start_item))
                {
                    result = Semantics.Start(start_item);

                    if(result != (object)null)
                    {
                        start_item.Flags |= (uint)ail.net.parser.EarleyParser.EFlags.eMarked;

                        BuildAstLevel(start_item, result);

                        start_item.Flags &= ~(uint)ail.net.parser.EarleyParser.EFlags.eMarked;
         
                        break;
                    }
                }
            }

            ail.net.framework.Assert.NonNullReference(result, "result");

            Status = ail.net.parser.Parser.EStatus.eParsed;

            return result;
        }

        private void BuildAstLevel(ail.net.parser.EarleyParser.Item xi_item, ail.net.parser.AstNode xi_root_node)
        {
            ail.net.framework.Assert.NonNullReference(xi_item, "xi_item");
            ail.net.framework.Assert.NonNullReference(xi_root_node, "xi_root_node");

            // populate a rhs stack with items of the current level
            Stack rhs_stack = new Stack();

            PopulateRhsStack(rhs_stack, xi_item);

            // processing all nodes(items) of the level
            while(rhs_stack.Count > 0)
            {
                ail.net.parser.EarleyParser.Item curr_item = (ail.net.parser.EarleyParser.Item)rhs_stack.Pop();
                
                ail.net.parser.GrammarSymbol symbol = (ail.net.parser.GrammarSymbol)curr_item.CoreItem.Rule.Rhs[curr_item.CoreItem.Dot-1]; // 'dot-1', because we pushed  items with 'dot' > 0

                if(symbol.IsTerminal())
                {
                    // handle terminal
                    Semantics.HandleTerminal(xi_root_node, curr_item.MasterChart.Token);
                }
                else if(symbol.IsNonTerminal())
                {
                    // handle non-terminal
                    if(curr_item.Rptrs.Count <= 1)
                    {
                        // r-ptr has exactly one element
                        ail.net.framework.Assert.Condition(curr_item.Rptrs.Count == 1,
                                                           "ail.net.parser.EarleyParser.BuildAstLevel: curr_item.Rptrs.Count == 1");

                        ail.net.parser.EarleyParser.Item r_ptr_item = (ail.net.parser.EarleyParser.Item)curr_item.Rptrs[0];

                        ail.net.parser.AstNode new_node = Semantics.HandleNonTerminalBefore(xi_root_node, r_ptr_item);

                        if(new_node != (object)null)
                        {
                            r_ptr_item.Flags |= (uint)ail.net.parser.EarleyParser.EFlags.eMarked;

                            BuildAstLevel(r_ptr_item, new_node);

                            r_ptr_item.Flags &= ~(uint)ail.net.parser.EarleyParser.EFlags.eMarked;
                        }

                        Semantics.HandleNonTerminalAfter(xi_root_node, r_ptr_item);
                    }
                    else
                    {
                        // r-ptr has more than one elements, ambiguity
                        foreach(ail.net.parser.EarleyParser.Item r_ptr_item in curr_item.Rptrs.Values)
                        {
                            if((r_ptr_item.Flags & (uint)ail.net.parser.EarleyParser.EFlags.eMarked) == 0)
                            {
                                ail.net.parser.AstNode new_node = Semantics.HandleNonTerminalBefore(xi_root_node, r_ptr_item);

                                if(new_node != (object)null)
                                {
                                    r_ptr_item.Flags |= (uint)ail.net.parser.EarleyParser.EFlags.eMarked;

                                    BuildAstLevel(r_ptr_item, new_node);

                                    r_ptr_item.Flags &= ~(uint)ail.net.parser.EarleyParser.EFlags.eMarked;

                                    Semantics.HandleNonTerminalAfter(xi_root_node, r_ptr_item);

                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }

        private void PopulateRhsStack(Stack xi_stack, ail.net.parser.EarleyParser.Item xi_item)
        {
            // no check for args!!!
            ail.net.parser.EarleyParser.Item item = xi_item;

            for(;;)
            {
                if(item == (object)null || item.CoreItem.Dot == 0)
                {
                    break;
                }
                
                xi_stack.Push(item);

                item = item.Lptr;
            }
        }

        private ail.net.parser.EarleyParser.Chart BuildInitialSet()
        {
            // initial set S0 contains item [S' -> • S, 0]
            ail.net.parser.EarleyParser.Chart result = AddChart();

            ArrayList core_items = (ArrayList)PredictTable[Grammar.StartSymbolId];
            ail.net.framework.Assert.NonNullReference(core_items, "core_items");

            foreach(ail.net.parser.EarleyParser.CoreItem core_item in core_items)
            {
                AddItem(core_item,
                        result,
                        result,
                        null,
                        ail.net.parser.EarleyParser.EFlags.eInitAction,
                        0,
                        true);
			}

            return result;
        }

        private void Closure(ail.net.parser.EarleyParser.Chart xi_chart)
        {
            // no args assertion!!!
            if(xi_chart != (object)null)
            {
                ExecutePredictor = ExecuteCompleter = true;

                for(;;)
                {
                    int count = xi_chart.Items.Count;

                    if(ExecutePredictor)
                    {
                        Predict(xi_chart);
                    }

                    if(ExecuteCompleter)
                    {
                        Complete(xi_chart);
                    }

                    if(xi_chart.Items.Count == count)
                    {
                        break;
                    }
                }
            }
        }

        private void Predict(ail.net.parser.EarleyParser.Chart xi_chart)
        {
            // PREDICTOR:
            //  if [A -> ... • B ..., j] is in S(i), add [B -> • a(lpha), i] to S(i) for all rules B -> a(lpha)
            // no args assertion!!!
            if(xi_chart != (object)null)
            {
                for(int i = xi_chart.PredictedK; i < xi_chart.PredictorItems.Count; i++, xi_chart.PredictedK++)
                {
                    ail.net.parser.EarleyParser.Item item = (ail.net.parser.EarleyParser.Item)xi_chart.PredictorItems[i];

                    ail.net.parser.GrammarSymbol symbol = (ail.net.parser.GrammarSymbol)item.CoreItem.Rule.Rhs[item.CoreItem.Dot]; // item.CoreItem.Dot is inside rhs.count

                    if(symbol.IsNonTerminal() && !PredictedNonTerminals[symbol.Id])
                    {
                        foreach(ail.net.parser.EarleyParser.CoreItem core_item in (ArrayList)PredictTable[symbol.Id])
                        {
                            AddItem(core_item,
                                    xi_chart,
                                    xi_chart,
                                    null,
                                    ail.net.parser.EarleyParser.EFlags.ePredictor,
                                    GetErrorCost(item),
                                    Charts.Count == 1); // only check for initial chart, because items were introduced
                                                        // by pseudo-prediction in BuildInitialSet
                        }

                        PredictedNonTerminals[symbol.Id] = true; // marked as predicted
                    }
                }
            }
        }

        private void Complete(ail.net.parser.EarleyParser.Chart xi_chart)
        {
            // COMPLETER:
            //  if [A -> ... •, j] is in S(i), add [B -> ... A • ..., k] to S(i) for all items [B -> ... • A ..., k] in S(j)
            // no args assertion!!!
            if(xi_chart != (object)null)
            {
                for(int i = xi_chart.CompletedK; i < xi_chart.CompleterItems.Count; i++, xi_chart.CompletedK++)
                {
                    ail.net.parser.EarleyParser.Item completer_item = (ail.net.parser.EarleyParser.Item)xi_chart.CompleterItems[i];
                    
                    ail.net.parser.GrammarSymbol l_symbol = (ail.net.parser.GrammarSymbol)completer_item.CoreItem.Rule.Lhs[0];

                    ail.net.parser.EarleyParser.Chart chart = completer_item.OriginalChart;

                    for(int k = 0; k < chart.PredictorItems.Count; k++)
                    {
                        ail.net.parser.EarleyParser.Item preditor_item = (ail.net.parser.EarleyParser.Item)chart.PredictorItems[k];

                        ail.net.parser.GrammarSymbol r_symbol = (ail.net.parser.GrammarSymbol)preditor_item.CoreItem.Rule.Rhs[preditor_item.CoreItem.Dot]; // preditor_item.CoreItem.Dot is inside rhs.count
                        
                        if(r_symbol.Id == l_symbol.Id)
                        {
                            ail.net.parser.EarleyParser.Item item = AddItem((ail.net.parser.EarleyParser.CoreItem)CoreItemTable[preditor_item.CoreItem.Id+1],
                                                                            preditor_item.OriginalChart,
                                                                            xi_chart,
                                                                            preditor_item,
                                                                            ail.net.parser.EarleyParser.EFlags.eCompleter,
                                                                            GetErrorCost(preditor_item),
                                                                            true);
                            SetRptr(item, completer_item);

                            // if dot is before non-terminal and that non-terminal is nullable
                            // also add item with dot after that non-terminal
                            while(item.CoreItem.Dot < item.CoreItem.Rule.Rhs.Count && 
                                ((ail.net.parser.GrammarSymbol)item.CoreItem.Rule.Rhs[item.CoreItem.Dot]).Nullable)
                            {
                                item = AddItem((ail.net.parser.EarleyParser.CoreItem)CoreItemTable[item.CoreItem.Id+1],
                                                item.OriginalChart,
                                                xi_chart,
                                                item,
                                                ail.net.parser.EarleyParser.EFlags.eCompleter,
                                                GetErrorCost(item),
                                                true);
                                SetRptr(item, completer_item);
                            }
                        }
                    }
                }
            }
        }

        private ail.net.parser.EarleyParser.Chart Scan(ail.net.parser.EarleyParser.Chart xi_chart)
        {
            // SCANNER:
            //  if [A -> ... • a ..., j] is in S(i) and a = x(i)+1, add [A -> ... a • ..., j] to S(i+1)
            // no args assertion!!!
            ail.net.parser.EarleyParser.Chart result = null;

            if(xi_chart != (object)null)
            {
                for(int i = 0; i < xi_chart.ScannerItems.Count; i++)
                {
                    ail.net.parser.EarleyParser.Item item = (ail.net.parser.EarleyParser.Item)xi_chart.ScannerItems[i];

                    ail.net.parser.GrammarSymbol symbol = (ail.net.parser.GrammarSymbol)item.CoreItem.Rule.Rhs[item.CoreItem.Dot]; // item.CoreItem.Dot is inside rhs.count

                    if(symbol.Id == Lexer.Token.Type)
                    {
                        if(result == (object)null)
                        {
                            result = AddChart();
                        }

                        AddItem((ail.net.parser.EarleyParser.CoreItem)CoreItemTable[item.CoreItem.Id+1],
                                item.OriginalChart,
                                result,
                                item,
                                ail.net.parser.EarleyParser.EFlags.eScanner,
                                GetErrorCost(item),
                                true);
                    }
                }
            }

            return result;
        }

        private ail.net.parser.EarleyParser.Chart ErrorScan(ail.net.parser.EarleyParser.Chart xi_chart)
        {
            // error case:
            //  if there is no any item with sybmol after dot equals to input symbol
            //  add to the next Set of items the following:
            //      for each item [A -> a(lpha) * a b(eta), ..., error_num] add to the next set
            //      [A -> a(lpha) * a b(eta), ..., error_num+1] and [A -> a(lpha) a * b(eta), ..., error_num+1],
            //      but only if error_num+1 <= MaxErrorValue
            // no args assertion!!!
            ail.net.parser.EarleyParser.Chart result = null;

            if(xi_chart != (object)null)
            {
                int [] error_costs = new int[xi_chart.Items.Count]; // reserve space for all items in set

                ail.net.framework.Assert.NonNullReference(Semantics, "Semantics");
                Semantics.HandleError(xi_chart, Lexer.Token, error_costs);

                int i = 0;

                for(int k = 0; k < xi_chart.ScannerItems.Count; k++)
                {
                    ail.net.parser.EarleyParser.Item item = (ail.net.parser.EarleyParser.Item)xi_chart.ScannerItems[k];

                    int error_cost  = GetErrorCost(item);
                        error_cost += error_costs[i++];

                    // if the error value is less then maximum error value
                    if(error_cost <= ail.net.parser.EarleyParser.kMaxErrorCost)
                    {
                        if(result == (object)null)
                        {
                            result = AddChart();
                        }

                        // deletion of the current input symbol
                        if(result.Token.Type != (int)ail.net.parser.Token.EType.eEndOfStream)
                        {
                            AddItem((ail.net.parser.EarleyParser.CoreItem)CoreItemTable[item.CoreItem.Id],
                                    item.OriginalChart,
                                    result,
                                    item,
                                    ail.net.parser.EarleyParser.EFlags.eErrorScanner,
                                    error_cost,
                                    true);
                        }

                        // insertion of the terminal symbol after the dot to the input string,
                        // it is also changing input operation for other terminal symbols
                        AddItem((ail.net.parser.EarleyParser.CoreItem)CoreItemTable[item.CoreItem.Id+1],
                                item.OriginalChart,
                                result,
                                item,
                                ail.net.parser.EarleyParser.EFlags.eErrorScanner,
                                error_cost,
                                true);
                    }
                }
            }

            return result;
        }

        private ail.net.parser.EarleyParser.Item AddItem(ail.net.parser.EarleyParser.CoreItem xi_core_item, // core_item
                                                         ail.net.parser.EarleyParser.Chart xi_orig_chart,   // original chart recognition started
                                                         ail.net.parser.EarleyParser.Chart xi_master_chart, // chart to add to
                                                         ail.net.parser.EarleyParser.Item xi_lptr_item,     // l-ptr
                                                         ail.net.parser.EarleyParser.EFlags xi_action,      // action introduced this item
                                                         int xi_error_cost,                                 // error cost
                                                         bool xi_check_existence)
        {
            // no args assertion!!!
            ItemKey key;

            key.CoreItem      = xi_core_item;
            key.OriginalChart = xi_orig_chart;
            key.Lptr          = xi_lptr_item;

            ail.net.parser.EarleyParser.Item result = xi_check_existence ? (ail.net.parser.EarleyParser.Item)xi_master_chart.Items[key] : null;

            if(result == (object)null)
            {
                result = new ail.net.parser.EarleyParser.Item();
#if PRINT_STATS
                result.Id            = xi_master_chart.Items.Count;
#endif
                result.CoreItem      = xi_core_item;
                result.OriginalChart = xi_orig_chart;
                result.MasterChart   = xi_master_chart;
                result.Lptr          = xi_lptr_item;
                result.Rptrs         = new Hashtable();
                result.Flags         = (uint)xi_action;

                xi_master_chart.Items.Add(key, result);

                // update optimization lists
                if(result.CoreItem.Dot == result.CoreItem.Rule.Rhs.Count ||
                    ((ail.net.parser.GrammarSymbol)result.CoreItem.Rule.Rhs[0]).Id == (int)ail.net.parser.Token.EType.eEpsilon)
                {
                    result.MasterChart.CompleterItems.Add(result);
                    ExecuteCompleter = (xi_action & ail.net.parser.EarleyParser.EFlags.ePredictor) != 0 || (xi_action & ail.net.parser.EarleyParser.EFlags.eScanner) != 0;
                }
                else // if(result.CoreItem.Dot < result.CoreItem.Rule.Rhs.Count)
                {
                    if(((ail.net.parser.GrammarSymbol)result.CoreItem.Rule.Rhs[result.CoreItem.Dot]).IsNonTerminal())
                    {
                        if(!PredictedNonTerminals[((ail.net.parser.GrammarSymbol)result.CoreItem.Rule.Rhs[result.CoreItem.Dot]).Id])
                        {
                            result.MasterChart.PredictorItems.Add(result);
                        }

                        ExecutePredictor = (xi_action & ail.net.parser.EarleyParser.EFlags.eCompleter) != 0 || (xi_action & ail.net.parser.EarleyParser.EFlags.eScanner) != 0;
                    }
                    else
                    {
                        result.MasterChart.ScannerItems.Add(result);
                    }
                }
            }

            ail.net.framework.Assert.NonNullReference(result, "result");
            return result;
        }

        private ail.net.parser.EarleyParser.Chart AddChart()
        {
            // create
            ail.net.parser.EarleyParser.Chart result = new ail.net.parser.EarleyParser.Chart();

            result.Id             = Charts.Count;
            result.Items          = new Hashtable();
            result.PredictorItems = new ArrayList(); // items in predictor list
            result.CompleterItems = new ArrayList(); // items in completer list
            result.ScannerItems   = new ArrayList();   // items in scanner list
            result.Token          = (ail.net.parser.Token)Lexer.Token.Clone();

            Charts.Add(result);

            // initialize
            Array.Copy(PredictedNonTerminalsZeroizer, PredictedNonTerminals, PredictedNonTerminalsZeroizer.Length); // zero out

            ail.net.framework.Assert.NonNullReference(result, "result");
            return result;
        }

        private void SetRptr(ail.net.parser.EarleyParser.Item xi_item, ail.net.parser.EarleyParser.Item xi_rptr_item)
        {
            // no check for args!!!
            // check if item already has this rptr
            if(!xi_item.Rptrs.Contains(xi_rptr_item))
            {
                xi_item.Rptrs[xi_rptr_item] = xi_rptr_item; //!!!
            }
        }

        private bool IsRecognizedItem(ail.net.parser.EarleyParser.Item xi_item)
        {
            ail.net.framework.Assert.NonNullReference(xi_item, "xi_item");

            bool result = false;

            if(xi_item.CoreItem.Rule.Lhs.Count > 0 && xi_item.OriginalChart != (object)null)
            {
                ail.net.parser.GrammarSymbol lhs_symbol = (ail.net.parser.GrammarSymbol)xi_item.CoreItem.Rule.Lhs[0];

                result = xi_item.CoreItem.Dot == xi_item.CoreItem.Rule.Rhs.Count && // dot at the end
                         lhs_symbol.Id == Grammar.StartSymbolId                  &&
                         xi_item.OriginalChart.Id == 0;
            }

            return result;
        }

        private bool IsChartCompleted(ail.net.parser.EarleyParser.Chart xi_chart)
        {
            ail.net.framework.Assert.NonNullReference(xi_chart, "xi_chart");

            bool result = false;

            foreach(ail.net.parser.EarleyParser.Item item in xi_chart.Items.Values)
            {
                if(IsRecognizedItem(item))
                {
                    result = true;
                    break;
                }
            }

            return result;
        }

        protected void BuildTables()
        {
            PopulateCoreItemTable();
            PopulatePredictTable();
        }

        private void PopulateCoreItemTable()
        {
            // allocate
            CoreItemTableAttr = new ArrayList(Grammar.CalculateGrammarSize());

            // populate
            ail.net.parser.EarleyParser.CoreItem core_item = null;

            int index = 0;

            foreach(ail.net.parser.GrammarRule rule in Grammar.Rules)
            {
                int i = 0;

                // special case for empty rule, we always assume the dot is at the end
                if(rule.Rhs.Count == 1 && ((ail.net.parser.GrammarSymbol)rule.Rhs[0]).Id == (int)ail.net.parser.Token.EType.eEpsilon)
                {
                    core_item = new ail.net.parser.EarleyParser.CoreItem();

                    core_item.Id   = index++;
                    core_item.Rule = rule;
                    core_item.Dot  = rule.Rhs.Count;

                    CoreItemTableAttr.Add(core_item);
                }
                else
                {
                    for(; i < rule.Rhs.Count; i++)
                    {
                        core_item = new ail.net.parser.EarleyParser.CoreItem();

                        core_item.Id   = index++;
                        core_item.Rule = rule;
                        core_item.Dot  = i;

                        CoreItemTable.Add(core_item);
                    }

                    // one extra for completed item
                    core_item = new ail.net.parser.EarleyParser.CoreItem();

                    core_item.Id   = index++;
                    core_item.Rule = rule;
                    core_item.Dot  = i;

                    CoreItemTable.Add(core_item);
                }
            }
        }

        private void PopulatePredictTable()
        {
            ail.net.framework.Assert.Condition(Grammar.Rules.Count > 0, "ail.net.parser.EarleyParser.PopulatePredictTable: Grammar.Rules.Count > 0");

            PredictTableAttr = new Hashtable();

            foreach(ail.net.parser.GrammarSymbol symbol in GrammarPool.Instance.Pool.Values)
            {
                if(symbol.IsNonTerminal())
                {
                    ArrayList list = new ArrayList();
                    
                    PredictTable[symbol.Id] = list;

                    for(int i = 0; i < CoreItemTable.Count; i++)
                    {
                        ail.net.parser.GrammarRule rule = ((ail.net.parser.EarleyParser.CoreItem)CoreItemTable[i]).Rule;
                        ail.net.parser.GrammarSymbol l_symbol = (ail.net.parser.GrammarSymbol)rule.Lhs[0];
                        int dot = ((ail.net.parser.EarleyParser.CoreItem)CoreItemTable[i]).Dot;

                        if(l_symbol.Id == symbol.Id && dot == 0)
                        {
                            list.Add(CoreItemTable[i]);
                        }
                    }
                }
            }

            PredictedNonTerminalsAttr = new bool[Lexer.Token.GetTokenSize()];
            PredictedNonTerminalsZeroizerAttr = new bool[Lexer.Token.GetTokenSize()];
        }

        private int GetErrorCost(ail.net.parser.EarleyParser.Item xi_item)
        {
            // no args assertion!!!
            return (int)((((xi_item.Flags & (uint)ail.net.parser.EarleyParser.EFlags.eErrorMask)) >> 24) & 0x00000007);
        }

        private int AddErrorCost(ail.net.parser.EarleyParser.Item xi_item, int xi_value)
        {
            // no args assertion!!!
            return SetErrorCost(xi_item, GetErrorCost(xi_item)+xi_value);
        }

        private int SetErrorCost(ail.net.parser.EarleyParser.Item xi_item, int xi_value)
        {
            // no args assertion!!!
            ail.net.framework.Assert.Condition(xi_value <= ail.net.parser.EarleyParser.kMaxErrorCost, "ail.net.parser.EarleyParser.SetErrorCost: xi_value <= ail.net.parser.EarleyParser.kMaxErrorCost");

            uint result = (((uint)xi_value) << 24) & (uint)ail.net.parser.EarleyParser.EFlags.eErrorMask;

            xi_item.Flags &= ~(uint)ail.net.parser.EarleyParser.EFlags.eErrorMask;
            xi_item.Flags |= result;

            return (int)result;
        }

        private string DecorateItem(ail.net.parser.EarleyParser.Item xi_item)
        {
            ail.net.framework.Assert.NonNullReference(xi_item, "xi_item");

            StringBuilder result = new StringBuilder();
#if PRINT_STATS
            result.Append(xi_item.Id+"  ");

            foreach(ail.net.parser.GrammarSymbol symbol in xi_item.CoreItem.Rule.Lhs)
            {
                result.Append(symbol.Name+" ");
            }

            result.Append("->");

            int i = 0;

            foreach(ail.net.parser.GrammarSymbol symbol in xi_item.CoreItem.Rule.Rhs)
            {
                if(i++ == xi_item.CoreItem.Dot)
                {
                    result.Append(" .");
                }

                if(symbol.Id != (int)ail.net.parser.Token.EType.eEpsilon)
                {
                    result.Append(" "+symbol.Name);
                }
            }

            if(xi_item.CoreItem.Dot == xi_item.CoreItem.Rule.Rhs.Count) // dot at the end
            {
                result.Append(" .");
            }

            result.Append(", ["+xi_item.OriginalChart.Id+"], ");

            if(xi_item.Lptr != (object)null && xi_item.Lptr.OriginalChart != (object)null)
            {
                result.Append(xi_item.Lptr.MasterChart.Id+"."+xi_item.Lptr.Id+", ");
            }
            else
            {
                result.Append("null, ");
            }

            result.Append("<");

            if(xi_item.Rptrs.Count > 0)
            {
                ArrayList rptrs = new ArrayList(xi_item.Rptrs.Values);

                rptrs.Sort(new ail.net.parser.EarleyParser.ItemComparer());
                
                StringBuilder str = new StringBuilder();
                
                foreach(ail.net.parser.EarleyParser.Item item in rptrs)
                {
                    str.Append(item.MasterChart.Id+"."+item.Id+", ");
                }
                
                result.Append(str.ToString().Substring(0, str.Length-2));
            }
            else
            {
                result.Append("null");
            }

            result.Append(">, ");
            
            if((xi_item.Flags & (uint)ail.net.parser.EarleyParser.EFlags.eInitAction) != 0)
            {
                result.Append("[i]");
            }
            else if((xi_item.Flags & (uint)ail.net.parser.EarleyParser.EFlags.ePredictor) != 0)
            {
                result.Append("[p]");
            }
            else if((xi_item.Flags & (uint)ail.net.parser.EarleyParser.EFlags.eCompleter) != 0)
            {
                result.Append("[c]");
            }
            else if((xi_item.Flags & (uint)ail.net.parser.EarleyParser.EFlags.eScanner) != 0)
            {
                result.Append("[s]");
            }
            else if((xi_item.Flags & (uint)ail.net.parser.EarleyParser.EFlags.eErrorScanner) != 0)
            {
                result.Append("[e]");
            }
#endif            
            return result.ToString();
        }

        private string DecorateChart(ail.net.parser.EarleyParser.Chart xi_chart)
        {
            ail.net.framework.Assert.NonNullReference(xi_chart, "xi_chart");

            StringBuilder result = new StringBuilder();
#if PRINT_STATS
            ArrayList items = new ArrayList(xi_chart.Items.Values);
            
            items.Sort(new ail.net.parser.EarleyParser.ItemComparer());
            
            foreach(ail.net.parser.EarleyParser.Item item in items)
            {
                result.Append("\t");
                result.Append(DecorateItem(item));
                result.Append(Environment.NewLine);
            }
#endif            
            return result.ToString();
        }

        public string DecorateCharts()
        {
            StringBuilder result = new StringBuilder();

            foreach(ail.net.parser.EarleyParser.Chart chart in Charts)
            {
                result.Append("Set["+chart.Id+"]");
				result.Append(Environment.NewLine);
				result.Append(DecorateChart(chart));
                result.Append(Environment.NewLine);
                result.Append(Environment.NewLine);
            }

            return result.ToString();
        }

        public string DecorateTree(ail.net.parser.AstNode xi_ast_node)
        {
            ail.net.framework.Assert.NonNullReference(xi_ast_node, "xi_ast_node");
            StringBuilder result = DecorateTreeVisitor(0, xi_ast_node);
            return result.ToString();
        }

        public StringBuilder DecorateTreeVisitor(int xi_level, ail.net.parser.AstNode xi_ast_node)
        {
            ail.net.framework.Assert.NonNullReference(xi_ast_node, "xi_ast_node");

            StringBuilder result = new StringBuilder();

            for(ail.net.parser.AstNode node = xi_ast_node; node != (object)null; node = node.Brother)
            {
                ail.net.parser.GrammarSymbol symbol = (ail.net.parser.GrammarSymbol)GrammarPool.Instance.Pool[(int)node.Token.Type];

                if(symbol != (object)null)
                {
                    for(int i = 0; i < xi_level; i++)
                    {
                        result.Append("    ");
                    }

        		    result.Append(symbol.Name);
                    result.Append(Environment.NewLine);
                }

                if(node.Child != (object)null)
                {
                    result.Append(DecorateTreeVisitor(xi_level+1, node.Child));
                }
            }

            return result;
        }
        #endregion // methods
    }
}

#region epilog
#endregion
