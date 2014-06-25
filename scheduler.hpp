#pragma once
#include<map>
#include<list>
#include<string>
#include<iostream>

typedef int t_capacity;
typedef int t_node_id;
typedef int t_job_id; 
typedef int t_time; 

class Resource {
  t_capacity capacity;
public:
  Resource(t_capacity capacity):
    capacity(capacity)
  {}
};

class Node {
  t_node_id id;
public:
  Node(t_node_id id):
    id(id)
  {}
};

class Need {
public:
  Need(t_capacity capacity, t_time duration) :
    capacity(capacity),
    duration(duration) {}
  t_capacity capacity;
  t_time duration;
};

class Available {
public:
  Available(t_node_id node, t_capacity capacity) :
    node(node),
    capacity(capacity) {}

  t_node_id node;
  t_capacity capacity;
};

class Scheduler {
protected:

public:
  // public api

  /*
    Node N has capacity of C is available at time t. It might be available later as well.
  */
  virtual void available(t_node_id node, t_capacity capacity, t_time time)=0;
  // it was available at time given
  // if it will be available again afterwards, 
  // then it will be called again with the availablity.
  

  /*
     Job needs resource of capacity C for time of N at the time t
   */
  virtual void need(t_capacity capacity, t_time duration, t_time time) =0;
  // it is needed at the time passed
  // see if there is any resource available
  // assign to the one with the lowest load    
  // find the smallest node that we can fit it on.

  virtual void report ()=0;
  // print out the utilization of the nodes
  // print out the wait time.

  /*
    we assign a node to a job for a certain time,
    if it will be freed, then we get another notification
  */
  void assign(t_node_id node, t_capacity capacity, t_time duration)    
  {
    std::cout << "assignment of " 
              << node
              << " with capacity of "
              << capacity 
              << " for time " 
              << duration
              << std::endl;
  }

};
