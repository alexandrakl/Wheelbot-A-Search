#ifndef Project_hpp
#define Project_hpp

#include <stdio.h>
#include <vector>
#include <queue>
#include <stack>
#include "Robot.h"
#include "Vector2D.h"
#include "Simulator.h"
#include "State.h"
#include "A42.h"
#include <iostream>
#include <set>

/**
 * @class Project
 * @brief represents the project to be completed
 */
class Project {
private:
    /**< random device */
    static std::random_device rd;
    /**< random number generator */
    static std::mt19937 rng;
    /**< simulator instance */
    Simulator simulator;
    A42* a42;
    std::vector<Point2D> myObstaclesVector;
    std::vector<State*> mystack;
    std::vector<State*> myObstaclesStateVector;

public:
    /**
     * @brief default constructor
     * @param sim simulator pointer
     */
    Project(Simulator &sim);

    /**
     * @brief get optimal action
     * @return optimal action (the one the robot should take
     */
    RobotAction getOptimalAction();
};

#endif
