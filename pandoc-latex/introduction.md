---
title: Spectre Meltdown
subtitle: Boiled up 
author: Felix C. Koch
---

# Outline

+ Tech Background
    - Branch Prediction
    - Speculative Execution
    - Memory Hierarchy
    - Return-Oriented Programming
+ Attack Overview
+ Exploiting Conditional Branch Misprediction
+ Poisoning Indirect Branches
+ Mitigations
+ Future Work
+ Demo POC on x86_64@i5-7500 (Windows [7SP1]/ Linux (4.13 kernel))


# Dynamic Branch Prediction - The gap in the pipeline

\begin{figure}
\resizebox{1.0\textwidth}{!}{
    \centering
    \input{resources/pipeline.tikz}
}
\end{figure}

\begin{equation*}
\boxed{
\Delta T_{wasted} \sim t_{exec}-t_{fetch}
}
\end{equation*}

# Dynamic Branch Prediction - Parallel execution

- The branch prediction can increase the linear part (instr. between 2 branches).

\begin{figure}
\centering
\resizebox{1.0\textwidth}{!}{
    \input{resources/lin_predict.tikz}
}
\end{figure}

# Dynamic Branch Prediction - Saturation counter
- Two bit counter / Four states
- Improvement: Loop closing cond. jump is mispredicted once rather than twice.

\begin{figure}
\centering
\resizebox{1.0\textwidth}{!}{
    \input{resources/saturation.tikz}
}
\end{figure}

# Dynamic Branch Prediction - Two-level predictor
- Disadvantage Sat. Count.: Mispredicts patterns i.e. jump is taken every 3rd time.
- Uses **2-bit shift register**

Example Pattern: $001001001\ldots$ ($0$-NT, $1$-T)

\begin{table}
\begin{tabular}{|c|c|}
\hline
\rowcolor{black}
2-bit pattern & Sat. counter state \\\hline 
\rowcolor{black!80}
00 & ST \\\hline
\rowcolor{black!80}
01 & SNT \\\hline
\rowcolor{black!80}
10 & SNT \\\hline
\rowcolor{black!80}
00 & $\perp$ \\\hline
\end{tabular}
\end{table}

# Dynamic Branch Prediction - Local/Global Predictors
- **Local Predictors:** 
    - Separate history buffer for each cond. jump.

- **Global Predictors:**
    - History buffer shared between cond. jumps. (*correlation*)

# Dynamic Branch Prediction - Target Prediction
- Modern processors try to guess rather target than **taken-or-not**
- Branch-Target-Buffer (BTB) as part of instruction cache

# Speculative Execution
- **Case**: Out-of-order execution @ conditional branch instruction
    - Direction depends on preceding instructions
    - Checkpoint saved containing current register state
    - Prediction is in progress
    - *Speculative* execute instr. along path

# Speculative Execution - Correct Case
- If prediction **correct**: saved state abandoned
- Instr. retired in program execution order

# Speculative Execution - False Case
- If prediction **not correct**: All pending instruction abandoned 
- Saved state gets reloaded
- Execution resumes correct path

# Memory Hierarchy - Cache structure
- Intel 2016 Kaby Lake Microarchitechture

\begin{figure}
    \centering
    \input{resources/cache.tikz}
\end{figure}

# Memory Hierarchy - Hit & Miss 
- Cache chunked in *lines* 64/128 bytes
1. Check L1 cache
    - Cache hit: Retrieve from L1.
    - Cache miss: Retrieve from next cache level.
2. If not already hit: Store in L1 cache

# Return Oriented Programming (ROP)

- Technique for exploiting buffer overflow vulns
- Attack buffer is constructed by chaining *gadgets*  
\lstinputlisting{resources/rop_snippet.txt}

# Attack Overview - 2 Methods
- Leverage conditional branch misprediction
- Leverage misprediction of targets within indirect branches

# Attack Overview - Setup 1st Method / Phase 1
1. Mistrain Processor to make erroneous spec. prediction.
2. For that: Performing targeted memory reads.
    - Processor evicts value (target) from cache.
3. Setup side-channel for extracting information.
    - flush | flush+reload | evict+reload

# Attack Overview - Setup 1st Method / Phase 2
1. Processor delivers info info into side-channel.
2. Trigger eviction out of side-channel (syscall, socket, file, etc.).

# Attack Overview - Setup 1st Method / Phase 3
1. Sensitive data gets recovered
    - Measuring time of reads within cache lines

# Attack Overview - diff Meltdown
- Can only read memory within victims process.
- **Without** triggering page fault or exception.
- Also works for CPU's preventing user based out-of-order executions reading memory.

#Exploiting Conditional Branch Misprediction - 1
1. uint x from untrusted source
2. Access to array1[array1_size] & array2[64 KB]

\lstinputlisting[language=c,linewidth=1.0\textwidth]{resources/cond_branch1.c}

\resizebox{1.0\textwidth}{!}{\fcolorbox{red}{black}{\\Conditional branch for bounds checking can follow incorrect path}}

#Exploiting Conditional Branch Misprediction - 2
1. Value of x chosen out of bounds (secret byte $k$)
2. array1_size and array2 not in cache
3. $k$ is cached
4. Previous ops received valid x
5. Branch predictor will asume **if**


#Exploiting Conditional Branch Misprediction - 3
- How to achieve cache configuration?
    1. fill cache with unrelated values.
    2. having kernel use secret key in legitimate op.

- We know even better:
    1. e.g. x86 **clflush**

#Exploiting Conditional Branch Misprediction - 3
1. Reading array1_size -> Cache miss.
    - Delay until delivered from DRAM.
2. Branch Prediction assumes **if**.
3. Speculative Exec: &array1 + x.
4. Cache hit: $k$ gets returned.
5. Speculative exec: Computing array2[$k$*256]
6. Request for reading -> cache miss.
7. Time by: array1_size receives from DRAM
8. Erroneous assumption: Rewind register state.

# End

\begin{figure}
    \centering
    \input{resources/array2.tikz}
\end{figure}

