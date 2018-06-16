## Benchmarks
- [lps2lts_time_memory](#benchmark-lps2lts_time_memory)
- [lps2lts_allocators](#benchmark-lps2lts_allocators)

___


### lps2lts raw time and max heap
<span id="benchmark-lps2lts_time_memory"></span>

In this benchmark we measure raw time and max heap usage for the **lps2lts** tool on various inputs and run with different flags.

Max heap usage is measure with valgrind massif.

![benchmark-lps2lts_time_memory-small-plot](https://raw.githubusercontent.com/gkarlos/mcrl2-perf/master/docs/images/plots/time-memory-small.png)

![benchmark-lps2lts_time_memory-medium-plot](https://raw.githubusercontent.com/gkarlos/mcrl2-perf/master/docs/images/plots/time-memory-medium.png)

### lps2lts allocators
<span id="benchmark-lps2lts_allocators"></span>

In this benchmark we measure raw time for the **lps2lts** tool on different inputs and flags using three different memory allocators:
- glibc malloc
- TCmalloc
- JEmalloc

![benchmark-lps2lts_allocators-small-plot](https://raw.githubusercontent.com/gkarlos/mcrl2-perf/master/docs/images/plots/allocators-small.png)

![benchmark-lps2lps2lts_allocators-medium-plot](https://raw.githubusercontent.com/gkarlos/mcrl2-perf/master/docs/images/plots/allocators-medium.png)
