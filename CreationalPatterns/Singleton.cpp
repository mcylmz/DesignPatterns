#include <iostream>
#include <string>


class Singleton {
public:
    Singleton(const Singleton& other) = delete;

    Singleton& operator=(const Singleton& other) = delete;

    static Singleton* create(const std::string& str);

    void otherProcedures() {

    }

    std::string getStr() const {
        return str_;
    }

private:
    Singleton(const std::string& str) : str_(str) {

    }

    static Singleton* singleton_;
    std::string str_;
};

Singleton* Singleton::singleton_ = nullptr;

Singleton* Singleton::create(const std::string& str) {
    if (singleton_ == nullptr) {
        singleton_ = new Singleton(str);
    }

    return singleton_;
}

int main() {
    Singleton* singleton1 = Singleton::create("singleton1");
    Singleton* singleton2 = Singleton::create("singleton2");

    // Both lines print the same string "singleton1"
    std::cout << singleton1->getStr() << std::endl;
    std::cout << singleton2->getStr() << std::endl;

    return 0;
}