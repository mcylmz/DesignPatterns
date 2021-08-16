/**
 * Imlementation of Strategy design pattern. The analogy here is a
 * path planner.
 */

#include <iostream>
#include <string>
#include <vector>

/**
 * Planner class is an interface for the strategies.
 */
class Planner {
public:
    virtual ~Planner() { }

    virtual void plan(const std::vector<int>& start, const std::vector<int>& goal) const = 0;
};


/**
 * PRM(Probabilistic Roadmap) is the first path planning strategy.
 */
class PRM : public Planner {
public:
    void plan(const std::vector<int>& start, const std::vector<int>& goal) const override {
        std::cout << "PRM started:" << std::endl;
        std::cout << "\tStart State: (" << start.at(0) << ", " << start.at(1) << ")" << std::endl;
        std::cout << "\tGaol State: (" << goal.at(0) << ", " << goal.at(1) << ")" << std::endl;
    }
};


/**
 * RRT(Rapidly-exploring Random Tree) is the second path planning strategy.
 */
class RRT : public Planner {
public:
    void plan(const std::vector<int>& start, const std::vector<int>& goal) const override{
        std::cout << "RRT started:" << std::endl;
        std::cout << "\tStart State: (" << start.at(0) << ", " << start.at(1) << ")" << std::endl;
        std::cout << "\tGaol State: (" << goal.at(0) << ", " << goal.at(1) << ")" << std::endl;
    }
};


class PlanningContext {
public:
    PlanningContext(Planner* planner=nullptr) : planner_(planner) {

    }

    ~PlanningContext() {
        delete planner_;
    }

    void setPlanner(Planner* planner) {
        delete planner_;
        planner_ = planner;
    }

    void makePlan(const std::vector<int>& start, const std::vector<int>& goal) const {
        planner_->plan(start, goal);
    }

private:
    Planner* planner_; // Reference to any of the Planner(Strategy) objects
};

void client() {
    std::vector<int> start{1, 2};
    std::vector<int> goal{10, 7};
    PlanningContext* pc = new PlanningContext(new PRM);

    std::cout << "The first strategy:" << std::endl;
    pc->makePlan(start, goal);   
    std::cout << "\n\n";

    // Changing the strategy from PRM to RRT
    pc->setPlanner(new RRT);
    std::cout << "The second strategy:" << std::endl;
    pc->makePlan(start, goal);
    std::cout << "\n\n";
 
    delete pc;
}

int main() {
    client();

    return 0;
}