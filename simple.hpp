/*
  simple first come first serve scheduler
*/

#include "scheduler.hpp"

class Simple : public Scheduler
{

  typedef std::list<Available>  t_available;// this capacity available right now
  typedef std::list<Need>       t_needs;// these jobs are waiting for resources

  /*
    what capacities are available to what nodes, currently. 
    Simple list of tuples
  */
  t_available availability;

  /*
    what jobs are not scheduled yet
   */
  t_needs needs;

  virtual void  need(t_capacity capacity, t_time duration, t_time time){
    //  simple first come first serve

    for (t_available::iterator i = availability.begin(); i != availability.end(); i++) {
      if (capacity > i->capacity) {
        assign(i->node,capacity,duration);
        // now just remove the availability record
        availability.erase(i);
        return; 
      }
    }
    // could not find a resource
    //std::cout << "could not find capacity of " <<  capacity << " with duration " <<  duration << std::endl;
    Need need(capacity, duration);
    needs.push_back(need);

  };

  virtual void available(t_node_id node, t_capacity capacity, t_time time){

    //  simple first come first serve, look for the first matching job and assign it

    for (t_needs::iterator i = needs.begin(); i != needs.end(); i++) {

      //DEBUG std::cout << "compare " << capacity << " with " << i->capacity << std::endl;
      
      if (capacity >= i->capacity) {
        assign(node,i->capacity,i->duration);
        // now just remove the availability record
        needs.erase(i);
        return;
      }
    }

    Available available(node,capacity);
    availability.push_back(available);
  }

public:

  Simple() {
    std::cout << "Created Simple scheduler" << std::endl;
  }

  virtual void report () {

    std::cout << "Final Report for simple scheduler" << std::endl;

    for (t_available::iterator i = availability.begin(); i != availability.end(); i++){
      std::cout << "unused node "
                << i->node
                << " with capacity of "
                << i->capacity
                << std::endl;
    }

    for (t_needs::iterator i = needs.begin(); i != needs.end(); i++){
      std::cout << "unscheduled need for the capacity " << i->capacity
                << " with the duration of " << i->duration
                << std::endl;
    }
  }
};
