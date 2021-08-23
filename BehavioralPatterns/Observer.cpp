#include <iostream>
#include <string>
#include <list>

/**
 * The observer pattern is a software design pattern in which an object, 
 * named the subject, maintains a list of its dependents, called observers, 
 * and notifies them automatically of any state changes, usually by calling one of their methods.
 * from: https://en.wikipedia.org/wiki/Observer_pattern
 */

/**
 * Observer interface
 */
class IObserver {
public:
    virtual ~IObserver() { }
    virtual void update(const std::string& state) = 0;
};

/**
 * Subject interface
 */
class ISubject {
public:
    virtual ~ISubject() { }
    virtual void attach(IObserver* observer) = 0;
    virtual void detach(IObserver* observer) = 0;
    virtual void notify() = 0;
};


class Subject : public ISubject {
public:
    virtual ~Subject() {
        std::cout << "Running subject destructor." << std::endl;
    }

    void attach(IObserver* observer) override {
        listObserver_.push_back(observer);
    }

    void detach(IObserver* observer) override {
        listObserver_.remove(observer);
    }

    void notify() override {
        std::list<IObserver*>::iterator observerItr = listObserver_.begin();
        while (observerItr != listObserver_.end()) {
            (*observerItr)->update(state_);
            ++observerItr;
        }
    }

    void setState(std::string state="State 0") {
        state_ = state;
        notify();
    }

    void numOfObservers() {
        std::cout << "There are " << listObserver_.size() << " observer in the list." << std::endl;
    }

private:
    std::list<IObserver*> listObserver_;
    std::string state_;
};


class Observer : public IObserver {
public:
    Observer(Subject* subject) : subject_(subject) {
        subject_->attach(this);
        std::cout << "This is the Observer " << ++Observer::staticNum_ << std::endl;
        observerID_ = Observer::staticNum_;
    }

    virtual ~Observer() {
        std::cout << "Destructor of the Observer" << observerID_ << " called\n";
    }

    void update(const std::string& observedState) override {
        observedState_ = observedState;
        std::cout << "Observed state changed." << std::endl;
        std::cout << "Observer ID: " << observerID_ << std::endl;
    }

    void remove() {
        subject_->detach(this);
        std::cout << "Observer " << observerID_ << " removed from the list.\n";
    }

    void printState() {
        std::cout << "The current state is " << observedState_ << std::endl;
    }

private:
    std::string observedState_;
    Subject* subject_;
    static int staticNum_;
    int observerID_;
};


int Observer::staticNum_ = 0;


int main() {
    Subject* subject = new Subject;
    Observer* observer1 = new Observer(subject);
    Observer* observer2 = new Observer(subject);
    Observer* observer3 = new Observer(subject);

    subject->setState("State 1");
    observer1->remove();

    observer3->printState();

    subject->setState("State 2");
    Observer* observer4 = new Observer(subject);

    subject->setState("State 3");
    Observer* observer5 = new Observer(subject);

    observer2->remove();
    observer3->remove();

    delete observer1;
    delete observer2;
    delete observer3;
    delete observer4;
    delete observer5;
    delete subject;

    return 0;
};