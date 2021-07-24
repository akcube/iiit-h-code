# Input Format

### Q1

Program usage: `bash q1.sh input.txt`

Output to file: `q1_output.txt`

Example input: 

```
ZDKepyfG
FJZO
KROqdSd
bATO
ZVgnovA
DqqI
KhFvbAIB
yXuYpPlkn
UnA
I
```

Example output:

```
ZDKe####
FJZO
KROq###
bATO
ZVgn###
DqqI
KhFv####
yXuY#####
UnA
I
```

### Q2

Program usage: `bash q2.sh input.txt `

Output to file: `q2_output.txt`

Example input:

```
Akhill Sandeep 06/02/2003
```

Example output:

```
Akhill Sandeep 18
```

### Q3

Program usage: `bash q3.sh input.txt `

Output: `stdout` (Terminal)

Example input:

```
she asked the question even though she didn't really want to hear the answer. it was a no-win situation since she already knew. if he told the truth, she'd get confirmation of her worst fears. if he lied, she'd know that he wasn't who she thought he was which would be almost as bad. yet she asked the question anyway and waited for his answer.

he had done everything right. there had been no mistakes throughout the entire process. it had been perfection and he knew it without a doubt, but the results still stared back at him with the fact that he had lost.
```

Example output:

```
she,she,situation,since,she,she,she,she,she,still,stared
who,which
the,though,the,the,that,thought,the,there,throughout,the,the,the,that
asked,a,already,almost,as,asked,a,at
```

### Q4 

Program usage: `bash q4.sh input.txt stopwords.txt search_word`

Note: 

- Program must be case sensitive
- Length of sentence = number of words in sentence after removing the stopwords
- Punctuations are not to be considered as words 

Example input:

```
It had been her dream for years but Dana had failed to take any action toward making it come true
There had always been a good excuse to delay or prioritize another project
As she woke, she realized she was once again at a crossroads
Would it be another excuse or would she finally find the courage to pursue her dream? Dana rose and took her first step
Stranded. Yes, she was now the first person ever to land on Venus, but that was of little consequence. 
Her name would be read by millions in school as the first to land here, but that celebrity would never actually be seen by her.
She looked at the control panel and knew there was nothing that would ever get it back into working order. 
She was the first and it was not clear this would also be her last.
```

Stopwords.txt

```
is
the
on
can
```

Example output: (Keyword: she)

```
It had been her dream for years but Dana had failed to take any action toward making it come true, 0
There had always been a good excuse to delay or prioritize another project, 0
As she woke, she realized she was once again at a crossroads, 0.25
Would it be another excuse or would she finally find courage to pursue her dream? Dana rose and took her first step, 0.0454545
Stranded. Yes, she was now first person ever to land Venus, but that was of little consequence., 0.0588235
Her name would be read by millions in school as first to land here, but that celebrity would never actually be seen by her., 0
She looked at control panel and knew there was nothing that would ever get it back into working order., 0
She was first and it was not clear this would also be her last., 0
```

### Q5

Program usage: `bash q5.sh directory_path`

Note:
- If no path given, consider the present working directory by default