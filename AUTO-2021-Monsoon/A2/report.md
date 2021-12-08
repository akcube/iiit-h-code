# Q3 - DFA minimization

My code for Q3 is a straightforward implementation of the Hopcroft DFA minimization algorithm. It uses the equivalence theorem. We keep iteratively dividing the set of {{accept states}, {other states}} based on their 1-equivalence with the previous iteration. This process eventually comes to an end. DFA nodes sharing the same state can be reduced into one node. Our DFA is reduced if possible. 

# Q4 - Regex => NFA

We begin by converting the infix regex expression to postfix. Because concatenation is not explicitly stated as an operator, we explicitly insert the '.' operator wherever required. Once this is done, we can build the NFA in an elegant manner. We build it according to the following rules:

1. If we read a new alphabet 'c', we represent it by it's own NFA i => i+1 with the transition being the alphabet. (i, i+1, 'c'). This is pushed onto a stack. 

2. If we read a '+' operator, we create two new states s' and t'. Because all these operators are binary we must have read at least two operands. Pop the last 2 operands off the stack. Note that these 2 "operands" are NFAs themselves. We connect s' to the start states of both these NFAs via epsilon transitions and the end states of these NFAs to t' via epsilon transitions again. This new NFA s' => t' is pushed onto the stack.

3. If we read a '.' operator, we again pop the last 2 NFAs (say A and B) off the stack. Now the end state of A is connected via an epsilon transition to the start state of B. This is pushed onto the stack. 

4. If we read a `*`  operator, we create a new state i. Link the last NFA from the stack to it via epsilon transitions and from i back to the NFA via an epsilon transition. This new state `i` is now pushed back onto the stack. We push `i` on the stack so that we can also account for empty strings. This is pushed onto the stack. 

Each NFA will have its own accept state. When applying any of the operators we keep propagating the global NFA accept state along. 
