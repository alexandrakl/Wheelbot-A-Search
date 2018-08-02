#include "A42.h"

A42::A42(std::vector<Point2D> obstacles, Simulator sim, int x, int y) 
    : target_(sim.getTarget()), x_(x), y_(y) {   
        solution = new State(sim.getTarget(), sim, NULL);
        for (std::vector<Point2D>::iterator it = obstacles.begin(); it != obstacles.end(); it++) {
            State* temp = new State(*it, sim, NULL);
            this->obstacles_.push_back(temp);
        }
    }

std::vector<State*> A42::solve(std::vector<State*> updatedObstacles, Point2D location, Simulator sim) {
    mystack_.clear();
    obstacles_ = updatedObstacles;
    State *startState = new State(location, 0, sim, NULL); //f = infinity
    mypq_.insert(startState); //starting node on the open list

    while (!mypq_.empty()) {
        State *current = *mypq_.begin();
        mypq_.erase(mypq_.begin());
        mystack_.push_back(current);

        if (current->isSolution()) {
            solution = current;
            break;
        }

        std::vector<State*> successors = current->generateSucessors(sim);

        for (auto stateS : successors) {
                
                bool isInClosed = false; //in closed list
                bool isInBlocked = false; //in blocked list

                //for loop to find if in closed list
                for (auto stack : mystack_ ) {
                    if ( (stack->getX()  == stateS->getX()) && (stack->getY()  == stateS->getY()) ) {
                       isInClosed = true;
                        break;
                    }
                }
                //for loop to find if in blocked list
                for (auto obstacle : obstacles_) {
                    if ( (stateS->getX() == obstacle->getX() ) && (stateS->getY() == obstacle->getY())) {
                       isInBlocked = true;
                        break;
                    }
                }

                if (!isInClosed && !isInBlocked) { //if it is not in closed list or in blocked list
                    bool isInOpen = false;
                    
                    if (isinmypq(*stateS)) {
                        isInOpen = true;
                        find(*stateS)->update(*stateS); //check is in function update
                        break;
                    }
                    
                    //if it not in open list, push back
                    if (!isInOpen) {
                        // new state
                        mypq_.insert(stateS);
                    }
                }      
            }
        }  

        if (solution != NULL) {
            mystack_.clear();
             mystack_.push_back(solution);
            State* temp = solution->getPredecessor();

            
          
            if (temp != NULL) {
                while (temp->getPredecessor()) {
                    mystack_.push_back(temp);
                     temp = temp->getPredecessor();
                }
            }      
    }

    return mystack_;

}

bool A42::isinmypq(State& state) {
	for (std::set<State*>::iterator it = mypq_.begin(); it != mypq_.end(); ++it) {
		if (*(*it) == state)
			return true;
	}
	return false;
}

State* A42::find(State& state) {
	std::set<State*>::iterator it = mypq_.end();
	for (std::set<State*>::iterator it1 = mypq_.begin(); it1 != mypq_.end(); ++it1) {
		if (*(*it1) == state) {
			it = it1;
			break;
		}
	}
	return *it;
}