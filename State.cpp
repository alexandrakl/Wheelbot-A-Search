#include "State.h"


int State::computeEuclidianDistance(Point2D target) {
    this->h_ = sqrt( (pow(this->x_ - target.getX(), 2) )+ (pow(this->y_ - target.getY(),2) ));
    return h_;
}

bool State::isSolution() {
	return this->h_ == 0;
}

//get possible moves from current position
std::vector<State*> State::generateSucessors(Simulator sim) {
    successors.clear();
    // for (auto successor : successors) {
    //     successors.pop_back();
    // }

    if (this->x_ < sim.getWidth())
    {
        // std::cout << "INSIDE SUCESSORS X<9  X: " << x_ << "Y: " << y_ << std::endl;
        // std::cout << "G is : " << g_ << std::endl;
     
        successors.push_back(new State(*(new Point2D(x_+1, y_)), g_+1, sim, this));
        //successors.push_back(new State(new Point2D(x_+1, y_), target_, g_+ 1, instance_));
    }

    if (this->x_ > 0)
    {
        //  std::cout << "INSIDE SUCESSORS X>0  X: " << x_ << "Y: " << y_ << std::endl;
        //   std::cout << "G is : " << g_ << std::endl;
       
           successors.push_back(new State(*(new Point2D(x_-1, y_)), g_+1, sim, this));
        //successors.push_back(new State(new Point2D(x_-1, y_), target_, g_+1, instance_));
    }

    if (this->y_ > 0)
    {
        //  std::cout << "INSIDE SUCESSORS Y>0  X: " << x_ << "Y: " << y_ << std::endl;
        //   std::cout << "G is : " << g_ << std::endl;
          
           successors.push_back(new State(*(new Point2D(x_, y_-1)), g_+1, sim, this));
        //successors.push_back(new State(new Point2D(x_, y_-1), target_, g_+1, instance_));
    }

    if (this->y_ < sim.getHeight())
    {
        //  std::cout << "INSIDE SUCESSORS Y<9  X: " << x_ << "Y: " << y_ << std::endl;
        //   std::cout << "G is : " << g_ << std::endl;
        
           successors.push_back(new State(*(new Point2D(x_, y_+1)), g_+1, sim, this));
        //successors.push_back(new State(new Point2D(x_, y_+1), target_, g_+1, instance_));
    }
    return successors;
}

//check if smaller than f -> then update
void State::update(State &rhs) {
    if(rhs.f_ < this->f_) {
        this->f_ = rhs.f_;
        this->g_ = rhs.g_;
        this->h_ = rhs.h_;
        this->predecessor_ = rhs.predecessor_;
    }
}
