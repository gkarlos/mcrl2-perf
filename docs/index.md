## Benchmarks
- [lps2lts_time_memory](#benchmark-lps2lts_time_memory)
- [lps2lts_allocators](#benchmark-lps2lts_allocators)
- [aterm_creation_fixed_nesting_variable_arity](#aterm_creation_fixed_nesting_variable_arity)
- [aterm_creation_variable_nesting_variable_arity](#aterm_creation_variable_nesting_variable_arity)

___

<span id="benchmark-lps2lts_time_memory"></span>

### lps2lts raw time and max heap

In this benchmark we measure raw time and max heap usage for the **lps2lts** tool on various inputs and run with different flags.

Max heap usage is measure with valgrind massif.

![benchmark-lps2lts_time_memory-small-plot](https://raw.githubusercontent.com/gkarlos/mcrl2-perf/master/docs/images/plots/time-memory-small.png)

![benchmark-lps2lts_time_memory-medium-plot](https://raw.githubusercontent.com/gkarlos/mcrl2-perf/master/docs/images/plots/time-memory-medium.png)


<span id="benchmark-lps2lts_allocators"></span>

### lps2lts allocators

In this benchmark we measure raw time for the **lps2lts** tool on different inputs and flags using three different memory allocators:
- [glibc malloc](https://sourceware.org/glibc/wiki/MallocInternals)
- [TCmalloc](http://goog-perftools.sourceforge.net/doc/tcmalloc.html)
- [JEmalloc](http://jemalloc.net/)

TCmalloc and JEmalloc shared libraries are preloaded with the `LD_PRELOAD` mechanism.

![benchmark-lps2lts_allocators-small-plot](https://raw.githubusercontent.com/gkarlos/mcrl2-perf/master/docs/images/plots/allocators-small.png)

![benchmark-lps2lps2lts_allocators-medium-plot](https://raw.githubusercontent.com/gkarlos/mcrl2-perf/master/docs/images/plots/allocators-medium.png)

<span id="aterm_creation_fixed_nesting_variable_arity"></span>

### Creation of terms with depth 1 and variable arity

We create terms of depth/nesting 1. That is, terms whose arguments are constants.
We test two cases. One where each argument is unique, e.g f(), f(a), f(b,c), f(d, e, f), etc,
and one where the same argument term is reused, e.g f(a), f(a, a), f(a, a, a) etc.

Only the time time to create the term itself is measured, i.e `aterm_appl appl_term( ...);`, meaning that argument creation is left out. Mean values are reported.

![term_creation_depth_1_variable_arity](https://raw.githubusercontent.com/gkarlos/mcrl2-perf/master/docs/images/plots/term_creation_depth_1_variable_arity.png)

<span id="aterm_creation_variable_nesting_variable_arity"></span>

### Creation of term with variable depth and variable arity
![aterm_creation_variable_nesting_variable_arity](https://raw.githubusercontent.com/gkarlos/mcrl2-perf/master/docs/images/plots/atermpp_term_creation_unique_heatmap.png)
