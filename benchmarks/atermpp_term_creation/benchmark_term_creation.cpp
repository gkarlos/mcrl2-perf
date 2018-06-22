#include <iostream>
#include <chrono>
#include <vector>
#include <ratio>
#include <ctime>
#include <cstdio>
#include <numeric>
#include <algorithm>

#include "mcrl2/atermpp/aterm_int.h"
#include "mcrl2/atermpp/aterm_appl.h"

using namespace std;
using namespace std::chrono;
using namespace atermpp;

#define N 1000000
#define MIN_ARITY 0
#define MAX_ARITY 10
#define MIN_NESTING 0
#define MAX_NESTING 10
#define FIX_ARITY 3
#define FIX_NESTING 3

double mean(std::vector<double>& v)
{
  return accumulate( v.begin(), v.end(), 0.0) / v.size();
}

double min(std::vector<double>& v)
{
  return *std::min_element(v.begin(), v.end());
}

double max(std::vector<double>& v)
{
  return *std::max_element(v.begin(), v.end());
}

double sd(std::vector<double>& v)
{
  double m = mean(v);

  std::vector<double> diff(v.size());

  std::transform(v.begin(), v.end(), diff.begin(), [m](double x) { return x - m; });

  double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);

  return std::sqrt(sq_sum / v.size());
}

void pp_results(vector<double>& ts)
{
  printf("min: %7d, max: %7d, mean: %7d, sd: %7d\n",\
    (int) min(ts), (int) max(ts), (int) mean(ts), (int) sd(ts)\
  );
}

std::string unique_symbol()
{
  static unsigned int i;
  return std::to_string(i++);
}

double time_term_creation(size_t arity, bool unique_args)
{
  double res;

  vector<aterm> args(arity);
  std::string id = unique_symbol();

  if ( unique_args)
  {
    /* Create the arguments */
    for( size_t i = 0; i < arity; ++i)
    {
      std::string arg_id = unique_symbol();
      function_symbol arg( arg_id, 0); // Each arg has arity 0
      aterm_appl arg_term(arg);
      args[i] = arg_term;
    }

    function_symbol f(id, arity);

    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    /* Create term here */

    aterm_appl appl_term(f, args.begin(), args.end());

    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    duration<double, std::nano> t = duration_cast<duration<double>>(t2 - t1);

    res = t.count();

    return res;
  }
  else
  {
    //std::string id = unique_symbol();
    std::string arg_id = unique_symbol();
    function_symbol arg( arg_id, 0);
    aterm_appl arg_term(arg);

    for( size_t i = 0; i < arity; ++i)
    {
      args[i] = arg_term;
    }

    function_symbol f( id, arity);

    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    /* Create term here */
    aterm_appl appl_term(f, args.begin(), args.end());

    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    duration<double, std::nano> t = duration_cast<duration<double>>(t2 - t1);

    res = t.count();
  }
  return res;
}


double sample_high_resolution_clock(unsigned int n)
{
  std::vector<double> ts;

  for ( unsigned int i = 0; i < n; ++i)
  {
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    /* Assume high_resolution_clock::now() always takes the same amount of time */
    duration<double, std::nano> t = duration_cast<duration<double>>(t2 - t1);
    ts.push_back( t.count() );
  }

  double sum = 0;

  for ( auto& t: ts)
    sum += t;

  return sum / ts.size();
}

double time_nested_term_creation(int nesting, int arity, bool unique_args)
{
  double res;
  vector<aterm> args(arity);
  std::string id = unique_symbol();

  if ( unique_args)
  {
    for ( int i = 0; i < arity; ++i)
    {
      //Create @arity number arguments of @nesting nesting
      std::string arg_id = unique_symbol();
      function_symbol arg( arg_id, 0);
      aterm_appl arg_term(arg);

      for ( int j = 0; j < nesting - 1; ++j)
      {
        std::string arg_arg_id = unique_symbol();
        function_symbol arg_arg( arg_arg_id, 1);
        arg_term = aterm_appl(arg_arg, arg_term);
      }

      args[i] = arg_term;
    }


    function_symbol f( id, arity);

    if ( arity)
    {
      high_resolution_clock::time_point t1 = high_resolution_clock::now();
      /* Create term here */
      aterm_appl appl_term(f, args.begin(), args.end());

      high_resolution_clock::time_point t2 = high_resolution_clock::now();

      duration<double, std::nano> t = duration_cast<duration<double>>(t2 - t1);

      res = t.count();
    }
    else
    {
      high_resolution_clock::time_point t1 = high_resolution_clock::now();
      /* Create term here */
      aterm_appl appl_term(f);

      high_resolution_clock::time_point t2 = high_resolution_clock::now();

      duration<double, std::nano> t = duration_cast<duration<double>>(t2 - t1);

      res = t.count();
    }

  }
  else
  {



    function_symbol f( id, arity);

    if ( arity)
    {
      std::string arg_id = unique_symbol();
      std::string arg_arg_id = unique_symbol();
      function_symbol arg( arg_id, 1);
      function_symbol arg_arg(arg_arg_id, 0);
      aterm_appl arg_arg_term(arg_arg);
      aterm_appl arg_term(arg, arg_arg_term);

      for ( int j = 0; j < nesting - 1; ++j) // Created a (@nesting - 1)-nested term
      {
        arg_term = aterm_appl(arg, arg_term);
      }

      for ( int i = 0; i < arity; ++i) // Use the same term as arg
      {
        //Create @arity number arguments of @nesting nesting
        args[i] = arg_term;
      }

      high_resolution_clock::time_point t1 = high_resolution_clock::now();
      /* Create term here */
      aterm_appl appl_term(f, args.begin(), args.end());

      high_resolution_clock::time_point t2 = high_resolution_clock::now();

      duration<double, std::nano> t = duration_cast<duration<double>>(t2 - t1);

      res = t.count();
    }
    else
    {
      high_resolution_clock::time_point t1 = high_resolution_clock::now();
      /* Create term here */
      aterm_appl appl_term(f);

      high_resolution_clock::time_point t2 = high_resolution_clock::now();

      duration<double, std::nano> t = duration_cast<duration<double>>(t2 - t1);

      res = t.count();
    }
  }

  return res;
}


void benchmark_aterm_creation(void)
{
  int n = 10000000;
  double clock_avg;
  cout << "[+] Sampling high_resolution_clock\n" << endl;
  clock_avg = sample_high_resolution_clock(n);
  cout << "    high_resolution_clock::now() average t: " << clock_avg << "ns ("<< n << " samples)\n" << endl;

  printf("[+] Running benchmark: nesting_1_arity_%d_%d_unique_args\n\n", MIN_ARITY, MAX_ARITY);

  // cout << "[+] Running benchmark: fixed_nesting_2_variable_arity " << endl;
  // for ( size_t arity = MIN_ARITY; arity <= MAX_ARITY; ++arity )
  // {
  //   vector<double> ts(N);
  //
  //   for ( size_t i = 0; i < N; ++i )
  //   {
  //     double t = time_term_creation(arity, true) - clock_avg;
  //     ts[i] = t;
  //   }
  //
  //   printf( "    Arity %2zu | ", arity);
  //   pp_results(ts);
  // }

  printf("\n[+] Running benchmark: nesting_1_arity_%d_%d_fixed_args\n\n", MIN_ARITY, MAX_ARITY);

  // for ( size_t arity = MIN_ARITY; arity <= MAX_ARITY; ++arity )
  // {
  //   vector<double> ts(N);
  //
  //   for ( size_t i = 0; i < N; ++i )
  //   {
  //     double t = time_term_creation(arity, false) - clock_avg;
  //     ts[i] = t;
  //   }
  //
  //   printf( "    Arity %2zu | ", arity);
  //
  //   pp_results(ts);
  // }

  printf("\n[+] Running benchmark: nesting_%d_%d_arity_%d_%d_unique_args\n\n", MIN_NESTING, MAX_NESTING, MIN_ARITY, MAX_ARITY);

  for ( size_t arity = MIN_ARITY; arity <= MAX_ARITY; ++arity )
  {
    for ( size_t nesting = MIN_NESTING; nesting <= MAX_NESTING; ++nesting)
    {
      vector<double> ts(N);
      for ( size_t i = 0; i < N; ++i )
      {
        double t = time_nested_term_creation(nesting, arity, true) - clock_avg;
        ts[i] = t;

      }

      cout << (int) mean(ts) << ",";
    }

    cout << endl;
  }

  printf("\n[+] Running benchmark: nesting_%d_%d_arity_%d_%d_fixed_args\n\n", MIN_NESTING, MAX_NESTING, MIN_ARITY, MAX_ARITY);

  for ( size_t arity = MIN_ARITY; arity <= MAX_ARITY; ++arity )
  {
    for ( size_t nesting = MIN_NESTING; nesting <= MAX_NESTING; ++nesting)
    {
      vector<double> ts(N);
      for ( size_t i = 0; i < N; ++i )
      {
        double t = time_nested_term_creation(nesting, arity, false) - clock_avg;
        ts[i] = t;

      }

      cout << (int) mean(ts) << ",";
    }

    cout << endl;
  }

  // 1. same symbol / different arguments
  // 2. same arguments / different symbol
  // 3. different arguments / different symbol
  // 4. nesting 0 arguments of type function symbol and int
  // 5. nesting 1 - 5, arity 1 to 20
  // 6. arity 1 - 5, nesting 1 to 20

  // for ( int n = 0; n < 10; ++n ) // For each nesting level
  // {
  //   for ( int a = 0; a < 10; ++a ) // For each arity
  //   {
  //     cout << unique_symbol() << endl;
  //   }
  //   //cout << endl << "                    ";
  // }

  cout << endl;
}

int main()
{
  /* Create term on the stack */
  benchmark_aterm_creation();

  cout << endl;
  // cout << "Created an aterm_int: " << anint << endl;
  return 0;
}
