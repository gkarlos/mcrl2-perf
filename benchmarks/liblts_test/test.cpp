#include <iostream>
#include <string>

#include "mcrl2/lts/lts.h"
#include "mcrl2/lts/lts_lts.h"
#include "mcrl2/lts/lts_type.h"

using namespace std;


void make_color_lts()
{
  using namespace mcrl2::lts;

  // Create the labelled transition system l.
  lts_lts_t l;
  // for ( int i = 0; i < 26; ++i)
  //   l.add_state( to_string(i));

  // // Add states 0 and 1. The state value is optional, but states must either
  // // all have state values, or not have state values at all.
  // l.add_state("Green");
  // l.add_state("Red");
  //
  // // Add an action label with index 0. The second (optional) argument
  // // indicates that this is not an internal label.
  // l.add_label("Become green",true);
  //
  // // Add a transition from state 1 to 0.
  // l.add_transition(transition(1,0,0));
  //
  // // Set the initial state (i.e., the red state)
  // l.set_initial_state(1);
  //
  // // Get the number of states, state values, action labels and transitions.
  // std::cout << "#states: "        << l.num_states() << "\n" <<
  //              "#state values: "  << l.num_state_values() << "\n" <<
  //              "#action labels: " << l.num_action_labels() << "\n"<<
  //              "#transitions: "   << l.num_transitions() << "\n" <<
  //              "#has state labels" << (l.has_state_info?" yes\n":" no\n");
  //
  // // Get the index of the initial state
  // std::cout << "Initial state is " << l.initial_state() << "\n";
  //
  // // Traverse and print the state labels.
  // for(unsigned int i=0; i<l.num_state_values(); ++i)
  // {
  //   std::cerr << "State " << i << " has value " << l.state_value(i) << "\n";
  // }
  //
  // // Traverse and print the values for action labels. Also print whether they are internal.
  // for(unsigned int i=0; i<l.num_action_labels(); ++i)
  // {
  //   std::cerr << "Action label " << i << " has value " << l.label_value(i) <<
  //                   (l.is_tau(i)?" (is internal)":"(is external)") << "\n";
  // }
  //
  // // Traverse and print the transitions
  // for(transition_const_range r=get_transitions; !r.empty(); r.advance_begin(1))
  // {
  //   const transition t=r.front();
  //   std::cerr << "Transition [" << r.from() << "," << r.label() << "," << r.to() << "]\n";
  // }
  //
  // // Finally, clear the transition system. Not really necessary, because this is also done
  // // by the destructor.
  // l.clear();
}

int main()
{
  make_color_lts();
  cout << "Hello" << endl;
  cout << "World" << endl;
  return 1;
}
