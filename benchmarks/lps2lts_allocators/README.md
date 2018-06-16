The purpose of this benchmark is to measure the performance of the default
allocator compared to:

- [TCmalloc](http://goog-perftools.sourceforge.net/doc/tcmalloc.html)
- [jemalloc](http://jemalloc.net/)

We measure raw time and maximum heap usage of mCRL2 on a subset of inputs from
the mCRL2 performance measurements website ([link](https://www.mcrl2.org/web/developer_manual/performance/index.html))

The input files left out are the ones that require large amount of time (>= 30 minutes) for both
lps2lts and mcrl2lps tools.

Results are split in two categories; those for small and medium inputs.
In general, small inputs are considered those for which lps2lts without any flags
outperforms the JIT rewriters, and medium inputs those for which the JIT rewriters
perform better; both in terms of time. Large inputs are ignored (for now).

#### Notes

This benchmark currently takes approximately 7000 seconds to complete.
