<h4>This is an implementation of a microprogrammed control unit according to Harvard architecture with cache memory system with didactic purpose</h4>

<h3>Motivation</h3>
<p>The memory access is slow, compared to the processor performance, so it is important to understand how the hardware works to make a good usage of it when developing software. This is mainly important for applications of critical performance.</p>

<h3>Project</h3>
Language: C11 Standard <br>
IDE: CLion 2017.2.2 <br>
Build: CMake

<h1>Part 1: Control Unit</h1>

<h2>Instructions Cycle</h2>

<h4>Fetch</h4>
<p>Fetches one instruction in memory according to program counter.</p>
<h4>Decode</h4>
<p>Decodes one instruction to identify the operation kind and the operands.</p>
<h4>Execute</h4>
<p>Executes the operation with the values of the operands update in decoding step.</p>
<h2>Memory</h2>

The memory is divided in two separated blocks: 
* Instructions Memory
* Data Memory

<h2>Registers</h2>

* **REG**: General Purpose Register

* **PC**: Program Counter

* **IR**: Instruction Register

* **MAR**: Memory Access Register

* **MBR**: Memory Buss Register

* **RC**: Comparison Register

<h2>Operations</h2>

<h4>LOAD</h4>
Load in the register the value from the address.<br>
The address can come from a constant value or a value of a register.<br>
Pattern: LOAD Rn CONSTANT<br>
Example: LOAD R1 100<br>
Pattern: LOAD Rn Rn<br>
Example: LOAD R1 R2<br>

<h4>MOVE</h4>

Moves to the first register the value of the right-side operand, which can be a register or a constant.<br>
Pattern 1: MOVE Rn CONSTANT<br>
Example 1: MOVE R1 2017<br>
Pattern 2: MOVE Rn Rn<br>
Example 2: MOVE R1 R2<br>

<h4>STORE</h4>

Store the value of the register in the address. The address can be a constant or a register value.<br>
Pattern: STORE Rn CONSTANT<br>
Example: STORE R1 100<br>
Pattern: STORE Rn Rn<br>
Example: STORE R1 R2<br>

<h4> ADD, MULTIPLY, SUBTRACT and DIVIDE</h4>

Do arithmetic with the two right-side operands and assign the result to the first register.<br>
Pattern: OPERATION Rn Rn Rn<br>
Example 1: ADD R1 R2 R3<br>
Example 2: DIVIDE R1 R2 R3 is equivalent to R1 = (R2 / R3)<br>

<h4>JUMP</h4>
<h5>CONDITIONAL JUMP</h5>

Decodes the instruction to jump to an index of the instruction memory.<br>
Compares the first constant value with the value in the comparison register and, if they are equal, jump condition is true.
Note that to update the register, Compare operation must be done before calling the Jump operation.<br>
Pattern: JUMPc CONSTANT INDEX<br>
Example: JUMPc 0 5<br>
It means: Jump, if the value in the comparison register is 0, to the instruction of index 5<br>

<h5>UNCONDITIONAL JUMP</h5>

Decodes unconditional jump operation.<br>
Pattern: JUMPu CONSTANT<br>
Example: JUMPu 10<br>
It means: Jump to instruction of index 10<br>

<h4>INCREMENT and DECREMENT</h4>

Decodes the instruction to increment or decrement 1 to the value of a register.<br>
Pattern 1: INCREMENT Rn<br>
Example 1: INCREMENT R1<br>
Pattern 2: DECREMENT Rn<br>
Example 2: DECREMENT R1<br>

<h4>COMPARE</h4>

Decodes the comparison of two operands and stores it in the comparison register.<br>
The comparison works according to arithmetic logic unit.<br>
The first operand must be a register and the second must be a register or a constant.<br>
Pattern: COMPARE Rn Rn<br>
Example: COMPARE R1 R2<br>
Pattern: COMPARE Rn CONSTANT<br>
Example: COMPARE R1 0<br>

<h2>Program Examples</h2>

These are some examples of developed programs with ths project's assembly language

<h4>Arithmetic operations</h4>
<h6>Instructions Memory</h6>

```
LOAD R1 100
MOVE R2 10
ADD R3 R1 R2
MOVE R2 2
MULTIPLY R1 R3 R2
DIVIDE R3 R1 R2
MOVE R2 20
SUBTRACT R1 R3 R2
STORE R1 101
```

<h6>Data Memory</h6>

```
100 10
```

<h4>Fibonacci Series</h4>
<h6>Instructions Memory</h6>

```
LOAD R9 100
MOVE R8 103
MOVE R2 1
MOVE R3 1
STORE R2 101
STORE R3 102
MOVE R7 2
COMPARE R9 R7
JUMPc 1 10
JUMPu 99
MOVE R1 R3
ADD R3 R2 R3
MOVE R2 R1
STORE R3 R8
INCREMENT R8
DECREMENT R9
JUMPu 6
```

<h6>Data Memory</h6>

```
100 20
```

<h4>Bubble Sort</h4>

<h6>Instructions Memory</h6>

```
LOAD R9 100
MOVE R8 0
MOVE R1 0
COMPARE R1 R9
JUMPc -1 6
JUMPu 99
MOVE R2 R9
COMPARE R2 -1
JUMPc 1 10
JUMPu 23
INCREMENT R8
MOVE R4 R2
MOVE R3 R4
DECREMENT R3
LOAD R6 R4
LOAD R5 R3
COMPARE R6 R5
JUMPc -1 19
JUMPu 21
STORE R6 R3
STORE R5 R4
DECREMENT R2
JUMPu 7
INCREMENT R1
JUMPu 3
```

<h6>Data Memory</h6>

```
100 10
1 2
2 12
3 2
4 9
5 35
6 8
7 0
8 88
9 1
10 3
```

<h1>Part 2: Cache Memory System</h1>

<h3>Memory Access</h3>

![alt tag](https://github.com/claudiomarpda/control_unit/blob/master/images/memory-access.png)

<h3>Memory Access Decision Flow</h3>

![alt tag](https://github.com/claudiomarpda/control_unit/blob/master/images/memory-access-flow.png)

<h2>Mapping Functions</h2>
<p>Only one cache level is used. The user can choose one of the two mapping functions below and check the cache hit and cache miss performance.</p>

<h4>Direct Mapping</h4>
<p>Each block of main memory is mapped to only one block line of the cache. The main memory is larger than the cache, so the mapping always takes care to make the address of the main memory to fit in cache.</p>

<h4>Associative Mapping</h4>
<p>One block of the main memory can be loaded in any line of the cache. The tag identifies one block unically and all of them must be verified to fetch a block, until find it or end the lines. The replacement algorithm is FIFO.</p>

<h3>Matrix Loading Program</h3>
<p>A program to stimulate the memory access so the cache system can be tested.</p>

<h6>Instructions Memory</h6>

```
LOAD R9 100
MOVE R8 101
MOVE R1 0
COMPARE R1 R9
JUMPc -1 6
JUMPu 99
INCREMENT R1
MOVE R2 0
COMPARE R2 R9
JUMPc -1 11
JUMPu 3
INCREMENT R2
LOAD R3 R8
INCREMENT R8
JUMPu 8
```

<h6>Data Memory</h6>

```
100 5
101 1
102 2
103 3
104 4
105 5
106 6
107 7
108 8
109 9
110 10
111 11
112 12
113 13
114 14
115 15
116 16
117 17
118 18
119 19
120 20
121 21
122 22
123 23
124 24
125 25
```

<h2>Cache Memory System Trending</h2>
<p>These results were obtained with the above program executed several times without clearing the cache with different cache sizes. We can see that as the cache size increses, the cache hit tend to go up and the cache miss tend to go down, but it gets to a point that even though the cache size is increased, they tend to stabilize.</p>

<h4>Direct Mapping</h4>

![alt tag](https://github.com/claudiomarpda/control_unit/blob/master/images/direct-chart.png)

<h4>Associative Mapping</h4>

![alt tag](https://github.com/claudiomarpda/control_unit/blob/master/images/associative-chart.png)
