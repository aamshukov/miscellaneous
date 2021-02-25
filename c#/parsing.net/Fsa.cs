//......................................................................................
// This is a part of UI Soft Library.  1989-2006 UI Soft Inc.               .
//......................................................................................
// THIS CODE MAY BE USED, COPIED, STORED, OR DISTRIBUTED ONLY IN ACCORDANCE WITH       .
// A WRITTEN LICENSE AGREEMENT AND WITH THE INCLUSION OF THIS COPYRIGHT NOTICE.        .
//......................................................................................
#region defines
#define USE_STATE_PREDICATE_SET
#endregion // defines

#region prolog
// file       : 
// description: Fsa
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
    /// summary description for Fsa
    /// </summary>
    public class Fsa : ICloneable, IDisposable
    {
        #region constants
        [FlagsAttribute]
        protected enum EFlags : ushort
        {
            eMarked = 0x0001 //!! not in use
        };

        public enum EMinimizationMode
        {
            eTable,
            ePartition
        };
        #endregion // constants

        #region data members
        private ail.net.parser.FsaState     StartStateAttr;
        private Hashtable                   StatesAttr            = new Hashtable();
        private ail.net.framework.Counter   StateCounterAttr      = new ail.net.framework.Counter();
        private ail.net.framework.Counter   GroupCounterAttr      = new ail.net.framework.Counter();
        private ail.net.framework.Counter   TransitionCounterAttr = new ail.net.framework.Counter();
        private Hashtable                   FinalStatesAttr       = new Hashtable();
        private ushort                      FlagsAttr;
        private Hashtable                   PredicatesAttr        = new Hashtable(); // holds all predicates of fsa, input alphabet
        protected ail.net.framework.ObjectFactory
                                            FactoryAttr           = new ail.net.framework.ObjectFactory(); // token factory
        #endregion // data members

        #region ctor/dtor/finalizer
        public Fsa()
        {
        }

       ~Fsa()
        {
            Dispose(false);
        }
        #endregion ctor/dtor/finalizer

        #region properties
        public ail.net.parser.FsaState StartState
        {
            get
            {
                return StartStateAttr;
            }

            set
            {
                StartStateAttr = value;
            }
        }
        
        public Hashtable States
        {
            get
            {
                return StatesAttr;
            }
        }

        public ail.net.framework.Counter StateCounter
        {
            get
            {
                return StateCounterAttr;
            }
        }

        public ail.net.framework.Counter GroupCounter
        {
            get
            {
                return GroupCounterAttr;
            }
        }

        public ail.net.framework.Counter TransitionCounter
        {
            get
            {
                return TransitionCounterAttr;
            }
        }

        public Hashtable FinalStates
        {
            get
            {
                return FinalStatesAttr;
            }
        }

        public ushort Flags
        {
            get
            {
                return FlagsAttr;
            }

            set
            {
                FlagsAttr = value;
            }
        }

        public Hashtable Predicates
        {
            get
            {
                return PredicatesAttr;
            }
        }

        public ail.net.framework.ObjectFactory Factory
        {
            get
            {
                return FactoryAttr;
            }
        }
        #endregion // properties

        #region methods
        public object Clone()
        {
            // deep clone
            Fsa result = new Fsa();
            result.AddFsa(this);
            return result;
        }

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

        public bool IsEmpty()
        {
            bool result = States.Count == 0;
            return result;
        }

        protected void ModifyFlags(EFlags xi_remove, EFlags xi_add)
        {
            Flags = (ushort)((Flags & ~(ushort)xi_remove) | (ushort)xi_add);
        }

        public bool IsStartState(ail.net.parser.FsaState xi_state)
        {
            ail.net.framework.Assert.NonNullReference(xi_state, "xi_state");
            return xi_state == StartState;
        }

        public ail.net.parser.FsaState AddState()
        {
            return AddState(StateCounter.Next());
        }

        public ail.net.parser.FsaState AddState(int xi_id)
        {
            ail.net.parser.FsaState result = null;

            if(!States.Contains(xi_id))
            {
                result = new ail.net.parser.FsaState(xi_id, this);

                States.Add(xi_id, result);

                if(StartState == (object)null) // avoid calling operator == ()
                {
                    StartState = result;
                }
            }

            return result;
        }

        public void RemoveState(ail.net.parser.FsaState xi_state)
        {
            ail.net.framework.Assert.NonNullReference(xi_state, "xi_state");
            ail.net.framework.Assert.Condition(States.Contains(xi_state.Id), "States.Contains(xi_state.Id)");

            FinalStates.Remove(xi_state.Id);
            States.Remove(xi_state.Id);
        }

        public bool IsFinalState(ail.net.parser.FsaState xi_state)
        {
            ail.net.framework.Assert.NonNullReference(xi_state, "xi_state");
            return FinalStates.Contains(xi_state.Id);
        }

        public void AddFinalState(ail.net.parser.FsaState xi_state, ail.net.parser.Token xi_token)
        {
            ail.net.framework.Assert.NonNullReference(xi_state, "xi_state");
            ail.net.framework.Assert.NonNullReference(xi_token, "xi_token");

            if(!FinalStates.Contains(xi_state.Id))
            {
                xi_state.Token = xi_token;
                FinalStates.Add(xi_state.Id, xi_state);
            }
        }

        public void RemoveFinalState(ail.net.parser.FsaState xi_state)
        {
            ail.net.framework.Assert.NonNullReference(xi_state, "xi_state");
            ail.net.framework.Assert.Condition(FinalStates.Contains(xi_state.Id), "FinalStates.Contains(xi_state.Id)");
            FinalStates.Remove(xi_state.Id);
        }

        public ail.net.parser.FsaTransition AddTransition(ail.net.parser.FsaState xi_start, ail.net.parser.FsaState xi_end, string xi_predicate)
        {
            ail.net.framework.Assert.NonNullReference(xi_start, "xi_start");
            ail.net.framework.Assert.NonNullReference(xi_end, "xi_end");
            ail.net.framework.Assert.NonEmptyString(xi_predicate, "xi_predicate");
            return AddTransition(xi_start.Id, xi_end.Id, xi_predicate, (char)0, "", 0);
        }

        public ail.net.parser.FsaTransition AddTransition(ail.net.parser.FsaState xi_start, ail.net.parser.FsaState xi_end, string xi_predicate, char xi_switch_char)
        {
            ail.net.framework.Assert.NonNullReference(xi_start, "xi_start");
            ail.net.framework.Assert.NonNullReference(xi_end, "xi_end");
            ail.net.framework.Assert.NonEmptyString(xi_predicate, "xi_predicate");
            return AddTransition(xi_start.Id, xi_end.Id, xi_predicate, xi_switch_char, "", 0);
        }

        public ail.net.parser.FsaTransition AddTransition(ail.net.parser.FsaState xi_start, ail.net.parser.FsaState xi_end, string xi_predicate, string xi_context)
        {
            ail.net.framework.Assert.NonNullReference(xi_start, "xi_start");
            ail.net.framework.Assert.NonNullReference(xi_end, "xi_end");
            ail.net.framework.Assert.NonEmptyString(xi_predicate, "xi_predicate");
            return AddTransition(xi_start.Id, xi_end.Id, xi_predicate, (char)0, xi_context, 0);
        }

        public ail.net.parser.FsaTransition AddTransition(ail.net.parser.FsaState xi_start, ail.net.parser.FsaState xi_end, string xi_predicate, int xi_rank)
        {
            ail.net.framework.Assert.NonNullReference(xi_start, "xi_start");
            ail.net.framework.Assert.NonNullReference(xi_end, "xi_end");
            ail.net.framework.Assert.NonEmptyString(xi_predicate, "xi_predicate");
            return AddTransition(xi_start.Id, xi_end.Id, xi_predicate, (char)0, "", xi_rank);
        }

        public ail.net.parser.FsaTransition AddTransition(ail.net.parser.FsaState xi_start, ail.net.parser.FsaState xi_end, string xi_predicate, string xi_context, int xi_rank)
        {
            ail.net.framework.Assert.NonNullReference(xi_start, "xi_start");
            ail.net.framework.Assert.NonNullReference(xi_end, "xi_end");
            ail.net.framework.Assert.NonEmptyString(xi_predicate, "xi_predicate");
            return AddTransition(xi_start.Id, xi_end.Id, xi_predicate, (char)0, xi_context, xi_rank);
        }

        public ail.net.parser.FsaTransition AddTransition(int xi_start, int xi_end, string xi_predicate, char xi_switch_char, string xi_context, int xi_rank)
        {
            ail.net.framework.Assert.NonEmptyString(xi_predicate, "xi_predicate");

            ail.net.parser.FsaTransition result = null;

            ail.net.parser.FsaState state = (ail.net.parser.FsaState)States[xi_start];
            ail.net.framework.Assert.NonNullReference(state, "state");

            int transition_id = TransitionCounter.Next();

            result = new ail.net.parser.FsaTransition(transition_id, xi_start, xi_end, xi_predicate, xi_switch_char, xi_context, xi_rank);

            state.Transitions.Add(transition_id, result);

            if(!Predicates.Contains(xi_predicate))
            {
                Predicates.Add(xi_predicate, result.Predicate);
            }

            return result;
        }

        public void RemoveTransition(ail.net.parser.FsaState xi_state, ail.net.parser.FsaTransition xi_transition)
        {
            ail.net.framework.Assert.NonNullReference(xi_state, "xi_state");
            ail.net.framework.Assert.NonNullReference(xi_transition, "xi_transition");
            ail.net.framework.Assert.Condition(States.Contains(xi_state.Id), "xi_state.Id");
            ail.net.framework.Assert.Condition(xi_state.Transitions.Contains(xi_transition.Id), "xi_state.Transitions.Contains(xi_transition.Id)");
            xi_state.Transitions.Remove(xi_transition.Id);
        }

        public void AddFsa(ail.net.parser.Fsa xi_fsa)
        {
            ail.net.framework.Assert.NonNullReference(xi_fsa, "xi_fsa");

            bool empty = IsEmpty();

            Hashtable map = new Hashtable(ail.net.framework.Functor.Align(xi_fsa.States.Count, ail.net.framework.Functor.kAlignValue));

            for(int i = 0; i < xi_fsa.StateCounter.Current; i++)
            {
                ail.net.parser.FsaState old_state = (ail.net.parser.FsaState)xi_fsa.States[i];
                ail.net.framework.Assert.NonNullReference(old_state, "old_state");

                ail.net.parser.FsaState new_state = AddState();
                ail.net.framework.Assert.NonNullReference(new_state, "new_state");

                new_state.Label = old_state.Label;
                new_state.Token = old_state.Token;
                
                if(xi_fsa.IsFinalState(old_state))
                {
                    AddFinalState(new_state, new_state.Token);
                }

                map[old_state.Id] = new_state.Id;
            }

            foreach(ail.net.parser.FsaState state in xi_fsa.States.Values)
            {
                foreach(ail.net.parser.FsaTransition transition in state.Transitions.Values)
                {
                    ail.net.parser.FsaState start_state = (ail.net.parser.FsaState)States[map[transition.Start]];
                    ail.net.parser.FsaState end_state = (ail.net.parser.FsaState)States[map[transition.End]];

                    ail.net.framework.Assert.NonNullReference(start_state, "start_state");
                    ail.net.framework.Assert.NonNullReference(end_state, "end_state");

                    AddTransition(start_state.Id,
                                  end_state.Id,
                                  transition.Predicate.Text,
                                  transition.Predicate.SwitchChar,
                                  transition.Predicate.Context,
                                  transition.Predicate.Rank);
                }
            }

            if(!empty)
            {
                if(xi_fsa.StartState != (object)null)
                {
                    AddTransition(StartState, (ail.net.parser.FsaState)States[map[xi_fsa.StartState.Id]], ail.net.parser.FsaTransition.kEpsilonPredicate);
                }
            }
        }

        public ail.net.parser.Fsa Nfa2Dfa()
        {
            // Conversion of an NFA into a DFA (subset construction)
            // .....................................................
            // Input: An NFA N.
            // Output: A DFA D accepting the same language.
            // Operations:
            //  e-closure(s) is the set of NFA states reachable from s on e-transitions alone.
            //  e-closure(T) is the union of e-closure(r) for all r in T.
            //  move(T, a) is the set of NFA states to which there is a transition on input a from some NFA state in T.
            //
            // set the start state to e-closure(s0) and unmark it.
            //  While there is an unmarked state T in Dstates do
            //      Mark T
            //      For each input symbol a do
            //          If U := e-closure(move(T, a));
            //          If U is not in Dstates then
            //              Add U as an unmarked state to Dstates;
            //          Dtran(T, a) := U;
            //      End;
            //  End;
            ail.net.parser.Fsa result = new ail.net.parser.Fsa();

            ArrayList dfa_states = new ArrayList();

            // build pseudo dfa
            ail.net.parser.FsaStateSet start_dfa_state = CalculateStateEclosure(StartState);

            start_dfa_state.Id = dfa_states.Count;
            start_dfa_state.Marked = false;

            dfa_states.Add(start_dfa_state);

            bool proceed = false;

            for(;;)
            {
                IEnumerator dfa_state_enum = dfa_states.GetEnumerator();
                
                while(dfa_state_enum.MoveNext())
                {
                    ail.net.parser.FsaStateSet dfa_state = (ail.net.parser.FsaStateSet)dfa_state_enum.Current;

                    if(!dfa_state.Marked)
                    {
                        dfa_state.Marked = true;

                        foreach(ail.net.parser.FsaTransitionPredicate predicate in Predicates.Values)
                        {
                            if(predicate.Text != ail.net.parser.FsaTransition.kEpsilonPredicate)
                            {
                                ail.net.parser.FsaStateSet move_set = CalculateMove(dfa_state, predicate.Text);
                                
                                if(move_set != (object)null)
                                {
                                    ail.net.parser.FsaStateSet pseudo_dfa_state = CalculateEClosureFromMove(move_set);

                                    if(pseudo_dfa_state != (object)null && pseudo_dfa_state.States.Count > 0)
                                    {
                                        ail.net.parser.FsaStateSet new_dfa_state = HasDfaCompoundState(dfa_states, pseudo_dfa_state);

                                        if(new_dfa_state == (object)null)
                                        {
                                            new_dfa_state = pseudo_dfa_state;
                                            new_dfa_state.Id = dfa_states.Count;
                                            new_dfa_state.Marked = false;

                                            dfa_states.Add(new_dfa_state);

                                            dfa_state_enum = dfa_states.GetEnumerator(); // reset iterator
                                        }

                                        if(!dfa_state.Transitions.Contains(dfa_state.Transitions.Count))
                                        {
                                            ail.net.parser.FsaTransition transition = new ail.net.parser.FsaTransition(dfa_state.Transitions.Count,
                                                                                                                       dfa_state.Id,
                                                                                                                       new_dfa_state.Id,
                                                                                                                       predicate.Text,
                                                                                                                       predicate.SwitchChar,
                                                                                                                       predicate.Context,
                                                                                                                       predicate.Rank);

                                            dfa_state.Transitions.Add(transition.Id, transition);
                                        }
                                    }
                                }
                            }
                        }

                        proceed = true;
                    }
                }

                if(!proceed)
                {
                    break;
                }

                proceed = false;
            }

            // populate states and final states
            foreach(ail.net.parser.FsaStateSet dfa_state in dfa_states)
            {
                ail.net.parser.FsaState state = result.AddState(dfa_state.Id);
                ail.net.framework.Assert.NonNullReference(state, "state");

                foreach(ail.net.parser.FsaTransition transition in dfa_state.Transitions.Values)
                {
                    result.AddTransition(transition.Start,
                                         transition.End,
                                         transition.Predicate.Text,
                                         transition.Predicate.SwitchChar,
                                         transition.Predicate.Context,
                                         transition.Predicate.Rank);
                }

                ail.net.parser.FsaState final_state = null;

                foreach(ail.net.parser.FsaState tmp_state in dfa_state.States.Values)
                {
                    if(FinalStates.Contains(tmp_state.Id))
                    {
                        ail.net.parser.FsaState org_state = (ail.net.parser.FsaState)States[tmp_state.Id];

                        ail.net.framework.Assert.NonNullReference(org_state, "org_state");

                        if(final_state == (object)null || org_state.Token.Priority > final_state.Token.Priority)
                        {
                            final_state = org_state;
                        }
                    }
                }

                if(final_state != (object)null)
                {
                    result.AddFinalState(state, final_state.Token);
                }
            }

            result.StateCounter.Reset(States.Count);

            return result;
        }

        public ail.net.parser.Fsa Minimize(ail.net.parser.Fsa.EMinimizationMode xi_mode)
        {
            ail.net.parser.Fsa result = new ail.net.parser.Fsa();

            // phase I (clean)
            RemoveUselessStates();

            // phase II (divide fsa into equivalent groups, each group will be new fsa state)
            Hashtable partition = new Hashtable();

            BuildPartition(ref partition, xi_mode);

            // phase III (compose fsa)
            foreach(ail.net.parser.FsaStateSet group in partition.Values)
            {
                ail.net.parser.FsaState new_state = result.AddState(group.Id);
                ail.net.parser.FsaState old_state = (ail.net.parser.FsaState)ail.net.framework.Functor.FirstElementOfCollection(group.States.Values);

                // check if group has start state
                foreach(ail.net.parser.FsaState state in group.States.Values)
                {
                    if(IsStartState(state))
                    {
                        result.StartState = new_state;
                        break;
                    }
                }

                // check if group final state
                foreach(ail.net.parser.FsaState state in group.States.Values)
                {
                    if(IsFinalState(state))
                    {
                        result.AddFinalState(new_state, state.Token);
                        break;
                    }
                }

                // add transitions
                foreach(ail.net.parser.FsaTransition transition in old_state.Transitions.Values)
                {
                    ail.net.parser.FsaStateSet transition_group = GetGroupFromState(transition.End, partition);

                    ail.net.framework.Assert.NonNullReference(transition_group, "transition_group");

                    result.AddTransition(new_state.Id,
                                         transition_group.Id,
                                         transition.Predicate.Text,
                                         transition.Predicate.SwitchChar,
                                         transition.Predicate.Context,
                                         transition.Predicate.Rank);
                }
            }

            // phase IV (clean)
            result.RemoveUselessStates();

            return result;
        }

        private void RemoveUselessStates()
        {
            // removes only states which are not accessible from start state
            // does not touch states which are not on the path for any input string
            ResetMarkedStates();

            Queue queue = new Queue();

            queue.Enqueue(StartState);

            while(queue.Count > 0)
            {
                ail.net.parser.FsaState state = (ail.net.parser.FsaState)queue.Dequeue();

                if(!state.Marked)
                {
                    state.Marked = true;

                    foreach(ail.net.parser.FsaTransition transition in state.Transitions.Values)
                    {
                        queue.Enqueue(States[transition.End]);
                    }
                }
            }

            ArrayList keys = new ArrayList();

            foreach(ail.net.parser.FsaState state in States.Values)
            {
                if(!state.Marked)
                {
                    keys.Add(state);
                }
            }

            foreach(ail.net.parser.FsaState key in keys)
            {
                RemoveState(key);
            }

            ResetMarkedStates();
        }

        public ail.net.parser.FsaStateSet CalculateStateEclosure(ail.net.parser.FsaState xi_state)
        {
            // Calculate e-closure:
            //  Push all states in T onto stack;
            //  Initialize e-closure(T) to T;
            //  While stack <> empty do
            //      Pop t;
            //      For each transition (t, u) in e-transition do
            //          If u is not in e-closure(T) then
            //              Add u to e-closure(T);
            //          Push u;
            //      End;
            //  End;
            ail.net.framework.Assert.NonNullReference(xi_state, "xi_state");

            ail.net.parser.FsaStateSet result = new ail.net.parser.FsaStateSet();

            ail.net.parser.FsaState state = xi_state;

            result.States.Add(state.Id, state);

            Stack stack = new Stack();

            for(;;)
            {
                int count = stack.Count;

                foreach(ail.net.parser.FsaTransition transition in state.Transitions.Values)
                {
                    if(transition.IsEpsilon())
                    {
                        if(!result.States.Contains(transition.End))
                        {
                            ail.net.parser.FsaState end_state = (ail.net.parser.FsaState)States[transition.End];
                            ail.net.framework.Assert.NonNullReference(end_state, "end_state");

                            result.States.Add(end_state.Id, end_state);
                            stack.Push(end_state);
                        }
                    }
                }

                if(stack.Count != count && !result.States.Contains(state.Id))
                {
                    result.States.Add(state.Id, state);
                }

                if(stack.Count == 0)
                {
                    break;
                }

                state = (ail.net.parser.FsaState)stack.Pop();
            }

            return result;
        }

        public ail.net.parser.FsaStateSet CalculateMove(ail.net.parser.FsaStateSet xi_state_set, string xi_predicate)
        {
            // Algorithm to compute T=Move(S,c)
            //  T = 0;
            //  for each state s in S
            //  {
            //      for each edge e from s to some s’
            //      {
            //          if(e is labelled with c)
            //          {
            //              T = T U closure({s’});
            //          }
            //      }
            //  }
            ail.net.framework.Assert.NonNullReference(xi_state_set, "xi_state_set");
            ail.net.framework.Assert.NonEmptyString(xi_predicate, "xi_predicate");

            ail.net.parser.FsaStateSet result = new ail.net.parser.FsaStateSet();

            foreach(ail.net.parser.FsaState state in xi_state_set.States.Values)
            {
                foreach(ail.net.parser.FsaTransition transition in state.Transitions.Values)
                {
                    if(transition.Predicate.Text == xi_predicate)
                    {
                        if(!result.States.Contains(transition.End))
                        {
                            ail.net.parser.FsaState end_state = (ail.net.parser.FsaState)States[transition.End];
                            ail.net.framework.Assert.NonNullReference(end_state, "end_state");
                            result.States.Add(end_state.Id, end_state);
                        }
                    }
                }
            }

            return result;
        }

        public ail.net.parser.FsaStateSet CalculateEClosureFromMove(ail.net.parser.FsaStateSet xi_state_set)
        {
            ail.net.framework.Assert.NonNullReference(xi_state_set, "xi_state_set");

            ail.net.parser.FsaStateSet result = new ail.net.parser.FsaStateSet();

            foreach(ail.net.parser.FsaState state in xi_state_set.States.Values)
            {
                if(!result.States.Contains(state.Id))
                {
                    result.States.Add(state.Id, state);

                    ail.net.parser.FsaStateSet eclosure = CalculateStateEclosure(state);

                    foreach(ail.net.parser.FsaState e_state in eclosure.States.Values)
                    {
                        if(!result.States.Contains(e_state.Id))
                        {
                            result.States.Add(e_state.Id, e_state);
                        }
                    }
                }
            }

            return result;
        }

        private ail.net.parser.FsaStateSet HasDfaCompoundState(ArrayList xi_dfa_states, ail.net.parser.FsaStateSet xi_dfa_state)
        {
            ail.net.framework.Assert.NonNullReference(xi_dfa_states, "xi_dfa_states");
            ail.net.framework.Assert.NonNullReference(xi_dfa_state, "xi_dfa_state");

            ail.net.parser.FsaStateSet result = null;

            foreach(ail.net.parser.FsaStateSet dfa_state in xi_dfa_states)
            {
                if(dfa_state == xi_dfa_state)
                {
                    result = dfa_state;
                    break;
                }
            }

            return result;
        }

        private void BuildPartition(ref Hashtable xio_partition, ail.net.parser.Fsa.EMinimizationMode xi_mode)
        {
            ail.net.framework.Assert.NonNullReference(xio_partition, "xio_partition");

            if(xi_mode == ail.net.parser.Fsa.EMinimizationMode.ePartition)
            {
                BuildPartition(ref xio_partition);
            }
            else if(xi_mode == ail.net.parser.Fsa.EMinimizationMode.eTable)
            {
                BuildTable(ref xio_partition);
            }
        }

        private void BuildPartition(ref Hashtable xio_partition)
        {
            ail.net.framework.Assert.NonNullReference(xio_partition, "xio_partition");

            BuildPrimaryPartition(ref xio_partition);

            for(;;)
            {
                bool process = false;

                ArrayList groups = new ArrayList(xio_partition.Values);

                for(int i = 0; i < groups.Count; i++)
                {
                    ail.net.parser.FsaStateSet group = (ail.net.parser.FsaStateSet)groups[i];
                    
                    if(group.States.Count > 1)
                    {
                        Hashtable partition = SplitGroup(group, xio_partition);

                        if(partition.Count > 1)
                        {
                            // substitute group with new set of subgroups
                            process = true;

                            xio_partition.Remove(group.Id);

                            foreach(ail.net.parser.FsaStateSet new_group in partition.Values)
                            {
                                xio_partition.Add(new_group.Id, new_group); // id is unique
                            }
                        }
                    }
                }

                if(!process)
                {
                    break;
                }
            }
        }

        private void BuildTable(ref Hashtable xio_partition)
        {
            //!! not implemented due to huge tables being built, postponed :(
            // Mark the distinguishable pairs of states.
            // To achieve this task, we first mark all pairs (p,q), where p belongs to F and
            // q does not belong to F as distinguishable. Then, we proceed as follows:
            //      repeat
            //          for all non-marked pairs {p,q} do
            //              for each letter 'a' do
            //                  if the pair {(s)igma(p,a), (s)igma(q,a)} is marked
            //                      then mark {p,q}
            //      until no new pairs are marked
            ail.net.framework.Assert.NonNullReference(xio_partition, "xio_partition");

            // initialization, this algorithm is sensitive to states organization            
            ResetMarkedStates();

            xio_partition.Clear();

            // table for 'A B C D E' states, cells in use marked with '*'
            //     0 A
            //     1 B *
            //     2 C * *
            //     3 D * * *
            //     4 E * * * *
            //         A B C D E
            //         0 1 2 3 4
            // access by (p, q) = table[ArithmeticProgressionSum(Math.Max(0, p_id-1)+q_id]

            // map[index][state]
            ArrayList map = new ArrayList(States.Values);

            Hashtable table = new Hashtable(CalculateTableSize());

            // create table of pairs, also mark all pairs of accept and non-accept states as non-equivalent
            // keep only one of pairs (p, q) or (q, p)
            ArrayList states = new ArrayList(States.Values);

            states.Sort(); // states must be numbered in sequence

            for(int i = 0; i < states.Count-1; i++)
            {
                for(int j = i+1; j < states.Count; j++)
                {
                    ail.net.parser.FsaState p_state = (ail.net.parser.FsaState)states[i];
                    ail.net.parser.FsaState q_state = (ail.net.parser.FsaState)states[j];
                    
                    ail.net.parser.FsaPair pair = new ail.net.parser.FsaPair(p_state, q_state);

                    table.Add(new ail.net.parser.FsaPairKey(p_state, q_state), pair);

                    bool p_final = IsFinalState(p_state);
                    bool q_final = IsFinalState(q_state);

                    bool mark = ((p_final && !q_final) || (!p_final && q_final));
                    
                    if(!mark && p_final && q_final)
                    {
                        mark = p_state.Token.Type != q_state.Token.Type;
                    }
                    
                    if(mark)
                    {
                        pair.Marked = true;
                    }
                }
            }

            // populate table
            for(;;)
            {
                bool process = false;

                foreach(ail.net.parser.FsaPair pair in table.Values)
                {
                    if(!pair.Marked)
                    {
                        Hashtable predicates = CombinePredicates(pair.PState, pair.QState);

                        foreach(ail.net.parser.FsaTransitionPredicate predicate in predicates.Values)
                        {
                            ail.net.parser.FsaTransition p_state_t = pair.PState.GetTransitionByPredicate(predicate);
                            ail.net.parser.FsaTransition q_state_t = pair.QState.GetTransitionByPredicate(predicate);

                            if((p_state_t == (object)null || q_state_t == (object)null))
                            {
                                continue;
                            }

                            ail.net.parser.FsaState p_state = (ail.net.parser.FsaState)States[p_state_t.End];
                            ail.net.parser.FsaState q_state = (ail.net.parser.FsaState)States[q_state_t.End];

                            if((object)p_state == (object)q_state) // pairs with same states are assumped unmarked
                            {
                                continue;
                            }
                            
                            ail.net.parser.FsaPair sigma_pair = GetPairFromStates(p_state, q_state, table);
                            
                            if(sigma_pair.Marked)
                            {
                                pair.Marked = true;
                                process = true;
                            }
                        }
                    }
                }

                if(!process)
                {
                    break;
                }
            }            

            ResetMarkedStates();

            // build partition
            foreach(ail.net.parser.FsaState state in states)
            {
                if(!state.Marked)
                {
                    // add equivalent groups, optimistic assumption
                    ail.net.parser.FsaStateSet group = new ail.net.parser.FsaStateSet(0);

                    for(int i = 0; i < state.Id; i++)
                    {
                        ail.net.parser.FsaPair pair = GetPairFromStates((ail.net.parser.FsaState)States[i], state, table);
                        
                        if(!pair.Marked)
                        {
                            if((object)pair.QState != (object)state)
                            {
                                if(!pair.QState.Marked)
                                {
                                    group.States.Add(pair.QState.Id, pair.QState);
                                }
                            }
                            else
                            {
                                if(!pair.PState.Marked)
                                {
                                    group.States.Add(pair.PState.Id, pair.PState);
                                }
                            }
                        }
                    }
                
                    if(group.States.Count > 0)
                    {
                        group.States.Add(state.Id, state);
                        group.Id = GroupCounter.Next(); // correct id

                        xio_partition.Add(group.Id, group);

                        foreach(ail.net.parser.FsaState group_state in group.States.Values)
                        {
                            group_state.Marked = true;
                        }
                    }
                }
            }

            foreach(ail.net.parser.FsaState state in states)
            {
                if(!state.Marked)
                {
                    // add non-equivalent groups
                    ail.net.parser.FsaStateSet group = new ail.net.parser.FsaStateSet(GroupCounter.Next());
                    group.States.Add(state.Id, state);
                    xio_partition.Add(group.Id, group);
                }
            }

            ResetMarkedStates();
        }

        private void BuildPrimaryPartition(ref Hashtable xio_partition)
        {
            // builds primary partition, which consist of two groups: {F} anf {Q-F}
            ail.net.framework.Assert.NonNullReference(xio_partition, "xio_partition");

            xio_partition.Clear();

            ail.net.parser.FsaStateSet nf_states = new ail.net.parser.FsaStateSet(GroupCounter.Next()); // non-final states
            ail.net.parser.FsaStateSet fn_states = new ail.net.parser.FsaStateSet(GroupCounter.Next()); // final states

            xio_partition.Add(nf_states.Id, nf_states); // final states will be split and add later

            foreach(ail.net.parser.FsaState state in States.Values)
            {
                if(IsFinalState(state))
                {
                    fn_states.States.Add(state.Id, state);
                }
                else
                {
                    nf_states.States.Add(state.Id, state);
                }
            }

            // also, for lexical analyzer we should separate final states by tokens into different groups
            Hashtable subgroups = new Hashtable();

            ail.net.parser.FsaStateSet group = new ail.net.parser.FsaStateSet(GroupCounter.Next());
            ail.net.parser.FsaState pin_state = (ail.net.parser.FsaState)ail.net.framework.Functor.FirstElementOfCollection(fn_states.States.Values);

            group.States.Add(pin_state.Id, pin_state);
            subgroups.Add(group.Id, group);
_start:
            foreach(ail.net.parser.FsaState state in fn_states.States.Values)
            {
                if(state.Marked)
                {
                    continue;
                }
                
                ail.net.parser.FsaStateSet subgroup_to_add = null;

                // find subgroup it may belong to
                foreach(ail.net.parser.FsaStateSet subgroup in subgroups.Values)
                {
                    foreach(ail.net.parser.FsaState subgroup_state in subgroup.States.Values)
                    {
                        if(state.Token.Type == subgroup_state.Token.Type)
                        {
                            subgroup_to_add = subgroup;
                            break;
                        }
                    }

                    if(subgroup_to_add != (object)null)
                    {
                        break;
                    }
                }

                if(subgroup_to_add == (object)null) // not found - split
                {
                    ail.net.parser.FsaStateSet new_group = new ail.net.parser.FsaStateSet(GroupCounter.Next());

                    new_group.States.Add(state.Id, state);
                    subgroups.Add(new_group.Id, new_group);
                    
                    state.Marked = true;

                    goto _start; // fortunately not so many final states :((
                }
                else
                {
                    if(!subgroup_to_add.States.Contains(state.Id))
                    {
                        subgroup_to_add.States.Add(state.Id, state);
                    }
                }
            }

            // clean up
_reset:
            foreach(ail.net.parser.FsaState state in fn_states.States.Values)
            {
                if(state.Marked)
                {
                    state.Marked = false;
                    fn_states.States.Remove(state.Id);
                    goto _reset;
                }
            }

            // insert subgroups
            foreach(ail.net.parser.FsaStateSet subgroup in subgroups.Values)
            {
                xio_partition.Add(subgroup.Id, subgroup);
            }
        }

        private Hashtable SplitGroup(ail.net.parser.FsaStateSet xi_group, Hashtable xi_partition)
        {
            ail.net.framework.Assert.NonNullReference(xi_group, "xi_group");
            ail.net.framework.Assert.Condition(xi_group.States.Count > 0, "xi_group.States.Count > 0");
            ail.net.framework.Assert.NonNullReference(xi_partition, "xi_partition");

            Hashtable result = new Hashtable();

            // first state introduces new subgroup
            ail.net.parser.FsaStateSet group = new ail.net.parser.FsaStateSet(GroupCounter.Next());

            result.Add(group.Id, group);

            group.States.Add(((ail.net.parser.FsaState)ail.net.framework.Functor.FirstElementOfCollection(xi_group.States.Values)).Id, 
                              (ail.net.parser.FsaState)ail.net.framework.Functor.FirstElementOfCollection(xi_group.States.Values));

            // go over states in the group
            foreach(ail.net.parser.FsaState state in xi_group.States.Values)
            {
                bool added = false;

                // check if state is not ortogonal to any subgroup
                foreach(ail.net.parser.FsaStateSet subgroup in result.Values)
                {
                    if(subgroup.States.Contains(state.Id)) // state == state
                    {
                        added = true;
                        break;
                    }

                    ail.net.parser.FsaState group_state = (ail.net.parser.FsaState)ail.net.framework.Functor.FirstElementOfCollection(subgroup.States.Values);

                    if(AreEqual(state, group_state, xi_partition))
                    {
                        subgroup.States.Add(state.Id, state);
                        added = true;
                        break;
                    }
                }

                // if state is ortogonal introduce a new group and add state to this new group
                if(!added)
                {
                    group = new ail.net.parser.FsaStateSet(GroupCounter.Next());
                    result.Add(group.Id, group);
                    group.States.Add(state.Id, state);
                }
            }

            return result;
        }

        private bool AreEqual(ail.net.parser.FsaState xi_state, ail.net.parser.FsaState xi_curr_state, Hashtable xi_partition)
        {
            ail.net.framework.Assert.NonNullReference(xi_state, "xi_state");
            ail.net.framework.Assert.NonNullReference(xi_curr_state, "xi_curr_state");
            ail.net.framework.Assert.NonNullReference(xi_partition, "xi_partition");

            bool result = false;

            // loop on all predicates relevant for these two states only,
            // as automaton is deterministic every state has at most one transition with given predicate
#if USE_STATE_PREDICATE_SET
            Hashtable predicates = CombinePredicates(xi_state, xi_curr_state);

            foreach(ail.net.parser.FsaTransitionPredicate predicate in predicates.Values)
#else
            foreach(ail.net.parser.FsaTransitionPredicate predicate in Predicates.Values) 
#endif
            {
                ail.net.parser.FsaTransition t1 = xi_state.GetTransitionByPredicate(predicate);
                ail.net.parser.FsaTransition t2 = xi_curr_state.GetTransitionByPredicate(predicate);
#if !USE_STATE_PREDICATE_SET
                if(t1 == (object)null && t2 == (object)null) // skip not relevant
                {
                    continue;
                }
#endif
                result = false; // reset

                if(t1 == (object)null || t2 == (object)null)
                {
                    break;
                }

                // attempt to find group with these two states
                foreach(ail.net.parser.FsaStateSet group in xi_partition.Values)
                {
                    if(group.States.Contains(t1.End) && group.States.Contains(t2.End))
                    {
                        result = true;
                        break;
                    }
                }

                if(!result)
                {
                    break;
                }
            }

            return result;
        }

        public void ResetMarkedStates()
        {
            foreach(ail.net.parser.FsaState state in States.Values)
            {
                state.Marked = false;
            }
        }

        private ail.net.parser.FsaStateSet GetGroupFromState(int xi_state_id, Hashtable xi_partition)
        {
            ail.net.framework.Assert.NonNullReference(xi_partition, "xi_partition");

            ail.net.parser.FsaStateSet result = null;

            foreach(ail.net.parser.FsaStateSet group in xi_partition.Values)
            {
                if(group.States.Contains(xi_state_id))
                {
                    result = group;
                    break;
                }
            }

            return result;
        }

        private int CalculateTableSize()
        {
            //          n-2
            // (n-1)^2 - E n
            //          i=1
            ail.net.framework.Assert.Condition(States.Count > 2, "ail.net.parser.Fsa.CalculateTableSize, n must be greater than 2");

            int result = (States.Count-1)*(States.Count-1);
            
            for(int i = States.Count-2; i > 0; i--)
            {
                result -= i;
            }

            return result;
        }

        private ail.net.parser.FsaPair GetPairFromStates(ail.net.parser.FsaState xi_p_state, ail.net.parser.FsaState xi_q_state, Hashtable xi_table)
        {
            ail.net.framework.Assert.NonNullReference(xi_p_state, "xi_p_state");
            ail.net.framework.Assert.NonNullReference(xi_q_state, "xi_q_state");
            ail.net.framework.Assert.NonNullReference(xi_table, "xi_table");

            ail.net.parser.FsaPair result = null;

            ail.net.parser.FsaPairKey key;

            key.PState = xi_p_state;
            key.QState = xi_q_state;
            
            result = (ail.net.parser.FsaPair)xi_table[key];
            
            if(result == (object)null)
            {
                key.PState = xi_q_state;
                key.QState = xi_p_state;

                result = (ail.net.parser.FsaPair)xi_table[key];
            }

            ail.net.framework.Assert.NonNullReference(result, "result");
            return result;
        }

        private Hashtable CombinePredicates(ail.net.parser.FsaState xi_state1, ail.net.parser.FsaState xi_state2)
        {
            ail.net.framework.Assert.NonNullReference(xi_state1, "xi_state1");
            ail.net.framework.Assert.NonNullReference(xi_state2, "xi_state2");

            Hashtable result = new Hashtable();

            foreach(ail.net.parser.FsaTransition transition in xi_state1.Transitions.Values)
            {
                result.Add(transition.Predicate.Text, transition.Predicate);
            }
            
            foreach(ail.net.parser.FsaTransition transition in xi_state2.Transitions.Values)
            {
                if(!result.Contains(transition.Predicate.Text))
                {
                    result.Add(transition.Predicate.Text, transition.Predicate);
                }
            }

            return result;
        }
        #endregion // methods
    }
}

#region epilog
#endregion
