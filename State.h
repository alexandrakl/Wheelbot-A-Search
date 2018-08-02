#ifndef STATE_H
#define STATE_H

#include <stdio.h>
#include <vector>
#include <queue>
#include <stack>
#include "Robot.h"
#include "Vector2D.h"
#include "Simulator.h"
#include <random>
#include <iostream>
#include <utility>
#include <math.h>
/**
 * @class Project
 * @brief represents the project to be completed
 */

class State {
private:
    float g_, h_, f_;
    int x_, y_;
    State *predecessor_;
    //State *instance_;
    Point2D target_;
    std::vector<State*> successors;

public:
    /**
     * @brief default constructor
     */
     State(Point2D point, Simulator sim, State* predecessor) : g_(HUGE_VALF), h_(HUGE_VALF), f_(HUGE_VALF), predecessor_(predecessor){
        target_.setX(sim.getTarget().getX());
        target_.setY(sim.getTarget().getY());
        x_ = point.getX();
        y_ = point.getY();
        //instance_ = this;
    }

     State(Point2D point, float g, Simulator sim, State* predecessor) : g_(g), predecessor_(predecessor){
        target_.setX(sim.getTarget().getX());
        target_.setY(sim.getTarget().getY());
        x_ = point.getX();
        y_ = point.getY();
        h_ = computeEuclidianDistance(sim.getTarget());
        f_ = g_ + h_;
    }

    ~State() {}

    State *getPredecessor() { return predecessor_; }
    int getH() {return h_;}
    int getG() {return g_;}
    int getF() {return f_;}
    int getX() {return x_;}
    int getY() {return y_;}

    void setH(float h) {h_ = h;}
    void setG(float g) {g_ = g;}
    void setF(float f) {f_ = f;}

    bool isSolution(); //returns true if found solution
    void update(State &rhs); //checks if f smaller, if so updates f, g and h
    int computeEuclidianDistance(Point2D target);  //computes h  
    std::vector<State*> generateSucessors(Simulator sim); //generates possible next moves


// comparing two states
bool operator==(State &other) {
	if (x_ == other.getX() && y_ == other.getY())
		return true;
	return false;
}

};
//makes sure the the open list is always sorted so that at the top is the state with the lowest f score
struct comp {
	bool operator()(State* lhs, State* rhs) {
		if (lhs->getF() == rhs->getF()) {
			if (lhs->getG() > rhs->getG())
				return lhs->getG() > rhs->getG();
			return true;
		}
		return lhs->getF() < rhs->getF(); 
	}
};

#endif

