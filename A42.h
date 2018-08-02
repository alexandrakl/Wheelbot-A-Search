#ifndef A42_H
#define A42_H

#include <stdio.h>
#include <vector>
#include <set>
#include <stack>
#include "Robot.h"
#include "Vector2D.h"
#include "Simulator.h"
#include <random>
#include <iostream>
#include "State.h"

/**
 * @class Project
 * @brief represents the project to be completed
 */

class A42 {
private:
    int x_, y_; // x, y coordinates current location
    Point2D target_;
    std::vector<State*> obstacles_; //obstacles updated with hidden ones each time
    State *solution; //final solution
    std::set<State*,comp> mypq_; //open list
    std::vector<State*> mystack_; //closed list

public:
    /*
    * Constructor with obstacles, simulator to get tagret, current location coordinates
    */
	A42(std::vector<Point2D> obstacles, Simulator sim, int x, int y);
    /*
    * main method to be called in project to implement A*
    */
    std::vector<State*> solve(std::vector<State*> updatedObstacles, Point2D location, Simulator sim);
    /*
    * destructor
    */
    ~A42() {
    }
   
   bool isinmypq(State& state); //returns true if is in my open list
   State* find(State& state); //return state
};

#endif
