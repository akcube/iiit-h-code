# Q1 

`./q1/src/q1.html` => Contains code for generating q1 part 1
`./q1/src/q2.html` => Contains code for generating q1 part 2
`./q1/src/q3.html` => Contains code for generating q1 part 3
`./q1/src/q4.html` => Contains code for generating q1 part 4

# Q2 

## Part 1

Consider the simple production rule `F = F[-F]F[+F]F`, with axiom `++++F` and angle `45deg`. 
We begin with this. This generates a tree but now we need to cutoff the branching at the bottom and remove some intersections.
We can create a new variable say, `A` and use it to cutoff the branching on one end.
Now, after some playing around I came up with the final result:

Axiom: `++++F`
Angle: `45 deg`
Production rule(s): 
1. `F=A[+F]F[-F]AF`
2. `A = AA`

A detail here is that for getting the lengths just right we pick `A = AA`.

## Part 2

The idea is to basically notice that we have a single line with a triangle in the middle. Just building off this simple construction we can easily get the final result:

Axiom: `F`
Angle: `72 deg`
Production rule(s):
1. `F = F-F++F-F`

One extra minor detail is the 72 angle degree. Notice that we are forming pentagons at multiple turning junctions. The internal angle of a pentagon is 108 degrees. From this we can deduct the outside angle to simply be 180-108 = 72 degrees.