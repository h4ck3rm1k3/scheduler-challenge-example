/*
  optimal look ahead scheduler
*/

#include "scheduler.hpp"
#include <cfloat>

class Optimal : public Scheduler
{

  typedef std::list<Available>  t_available;// this capacity available right now
  typedef std::list<Need>       t_needs;// these jobs are waiting for resources

  /*
    what capacities are available to what nodes, currently. 
    Optimal list of tuples
  */
  t_available availability;

  /*
    what jobs are not scheduled yet
   */
  t_needs needs;

  virtual void  need(t_capacity capacity, t_time duration, t_time time){
    //  optimal first come first serve

    bool found = 0;
    t_available::iterator best;
    float least_waste = FLT_MAX ;

    for (t_available::iterator i = availability.begin(); i != availability.end(); i++) {
      float waste  = i->capacity / capacity;

      //DEBUG 
      //std::cout << "need compare need " << capacity << " with capacity of " << i->capacity << " with waste of " <<  waste << std::endl;

      if (capacity > i->capacity ) {
        if ((found && least_waste > waste ) 
            || 
            (!found)){
          best = i;
          least_waste= waste;
          found = 1;
        }

      }
    }
    
    if (found) {
      assign(best->node,capacity,duration);
      // now just remove the availability record
      availability.erase(best);
    } else {
      // could not find a resource
      //DEBUG: std::cout << "could not find capacity of " <<  capacity << " with duration " <<  duration << std::endl;
      Need need(capacity, duration);
      needs.push_back(need);
    }
  };

  virtual void available(t_node_id node, t_capacity capacity, t_time time){

    //  optimal look for least waste
    bool found = 0;
    t_needs::iterator best;
    float least_waste = FLT_MAX ;
    
    for (t_needs::iterator i = needs.begin(); i != needs.end(); i++) {

      // check the waste 
      float waste  = capacity / i->capacity;

      //DEBUG 
      //std::cout << "compare capacity of " << capacity << " with need of " << i->capacity << " with waste of " <<  waste << std::endl;

      if (capacity  >= i->capacity ) {        
        if ((found && least_waste > waste ) 
            || 
            (!found)){
          // DEBUG
          // std::cout << "found best " << capacity << " with need of " << i->capacity << " with waste of " <<  waste << std::endl;

          best = i;
          least_waste= waste;
          found = 1;
        }
      }
    }
    
    if (found) {
      assign(node,best->capacity,best->duration);
      // now just remove the availability record
      needs.erase(best);
    } else {
      Available available(node,capacity);
      availability.push_back(available);
    }
  }

public:

  Optimal() {
    std::cout << "Created Optimal scheduler" << std::endl;
  }

  virtual void report () {

    std::cout << "Final Report for optimal scheduler" << std::endl;

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
