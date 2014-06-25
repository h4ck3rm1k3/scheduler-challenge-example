/*
  Scheduler Simulator Example Code
*/

#include "simple.hpp"
#include <assert.h>

/*
  Schedule loader
*/

class Loader {
public:
  Scheduler * pSchedule;
  Loader(Scheduler * pSchedule) : pSchedule(pSchedule) {
    // load from file if we have time.
    // we assume that the lines are read in one by one, and we give them the line number as the time stamp.
    assert(pSchedule);
    
    pSchedule->available(2,3,1); // node 2 has 3 units available on line #1
    pSchedule->need(3,4,1); // need 3 units for time of 4, #1
    // assign job to 2 for 4 units

    pSchedule->available(7,1,2); // node 7 is available for one resource #2
    pSchedule->need(1,4,2); // need one unit for 4, #2
    // assign node 7 for one unit for time of 4

    pSchedule->need(4,7,3); // need 4 units for time of 7 #3
    pSchedule->available(1,23,3);// node one has 23 utils, #3
    // assign node 1? for 4 units with a waste? this is where we might want to wait.
    // dont assign yet.

    pSchedule->available(8,5,4); // node 8 has 5 resources available # 4
    // this is less waste. lets assign it
    // assign job 3 to node 8 for time of 7

    pSchedule->need(1,3,4); // need one unit for 3 # 4
    // lets put that on node 7
    // assign job 4 to node 7 for time of 3

    pSchedule->available(2,8,5);  // node two is back available, with a capacity of 8 #5
    // we assigned two at time one for four units so now at the fith line it is back, coincidence?
    // we wont interpret this as a second resource available at the same time, but at a later time. 
    // we wont assume that the nodes come back online until stated, they might fail
    
    pSchedule->need(5,4,5); // Job # 5
    // we can put that on node 2, 8 or node 1
    // node 2 has the least waste

    pSchedule->need(9,3,6); // Job # 6 needs 9 units
    // this can only fit on node 1
    //assign job 6 to node 1 for 3 time units.
  }

};


int main (int argc, char** argv) {

  Simple schedule;  
  Loader loader(&schedule);
  schedule.report();

  // now test the new scheduler
}
