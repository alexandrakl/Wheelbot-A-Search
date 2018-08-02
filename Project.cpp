#include "Project.h"

/**< random device */
std::random_device Project::rd;
/**< random number generator */
std::mt19937 Project::rng;

/**
* @brief default constructor
* @param sim simulator pointer
*/
Project::Project(Simulator &sim) {
    this->simulator = sim;
    rng = std::mt19937(rd());

    Point2D point = this->simulator.getRobot()->getPosition(); //gets robot position
    this->myObstaclesVector = this->simulator.getObstacleLocations(); //gets known obstacles
  
    for (auto obstaclePoint : myObstaclesVector) {
        myObstaclesStateVector.push_back(new State(obstaclePoint, sim, NULL));
       //std::cout << "X obstacle Location at " << i << " is: " << myObstaclesVector[i].getX() << std::endl;
       // std::cout << "Y obstacle Location at " << i << " is: " << myObstaclesVector[i].getY() << std::endl;
    }
    this->a42 = new A42(myObstaclesVector, sim, point.getX(), point.getY()); 
    this->mystack = this->a42->solve(myObstaclesStateVector, sim.getRobot()->getPosition(), sim); //calls A*
}

RobotAction Project::getOptimalAction() {
    int tx = this->simulator.getTarget().getX();
    int ty = this->simulator.getTarget().getY();
    int h = this->simulator.getTargetDistance();
   
   //vector for hidden obstacles
    std::vector<Point2D> currentObstaclesVector = this->simulator.getCurrentLocalObstacleLocations();
    for (int i=0; i< currentObstaclesVector.size(); i++) {
      //  std::cout << "X Current obstacle Location at " << i << " is: " << currentObstaclesVector[i].getX() << std::endl;
       // std::cout << "Y Current obstacle Location at " << i << " is: " << currentObstaclesVector[i].getY() << std::endl;
    }
    if (!currentObstaclesVector.empty()) {
        for (auto obstacle : currentObstaclesVector) {
            myObstaclesStateVector.push_back(new State(obstacle, this->simulator, NULL));
        }
        this->mystack = this->a42->solve(myObstaclesStateVector, this->simulator.getRobot()->getPosition(), this->simulator);
    }
    
  if (mystack.back() != NULL) {
    State *nextState = mystack.back();
    mystack.pop_back();
    int moveX = nextState->getX();
    int moveY = nextState->getY(); 
    //std::cout << "MY NEXT MOVE IS X: " << moveX << " Y: " << moveY << std::endl;
    
    if (moveX - this->simulator.getRobot()->getPosition().getX() == 1) {
        //std::cout << "My position: " << this->simulator.getRobot()->getPosition().getX() <<std::endl;
        return MOVE_DOWN;
    } 
 
    if (moveX - this->simulator.getRobot()->getPosition().getX() == -1) {
        //std::cout << "My position: " << this->simulator.getRobot()->getPosition().getX() <<std::endl;
        return MOVE_UP;
    }
 
    if (moveY - this->simulator.getRobot()->getPosition().getY() == 1) {
       // std::cout << "My position: " << this->simulator.getRobot()->getPosition().getY() <<std::endl;
        return MOVE_RIGHT;
    } 
    
    if (moveY - this->simulator.getRobot()->getPosition().getY() == -1) {
        //std::cout << "My position: " << this->simulator.getRobot()->getPosition().getY() <<std::endl;
        return MOVE_LEFT;
    }

  } else {
          std::cout << "NO SOLUTION " << std::endl;
          return STOP;
  }
 //std::cout << "NO SOLUTION " << std::endl;
   return STOP;
}
