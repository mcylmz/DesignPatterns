#include <iostream>
#include <string>
#include <algorithm>


class  Inorder {
public:
    virtual std::string inorderString() const {
        return "Inorder string.";
    }

    virtual ~Inorder() = default;
};


class Reverse {
public:
    std::string reverseString() const {
        return ".gnirts esrever a si sihT";
    }
};


/**
 * The Adapter makes the Reverse's(Adaptee) interface compatible with the Inorder's
 * interface. So the client can utilize the Reverse interface with the help of the
 * Adapter.
 */
class Adapter : public Inorder {
public:
    Adapter(Reverse* reverse) : reverse_(reverse) {

    }

    std::string inorderString() const override {
        std::string stringToReverse = this->reverse_->reverseString();
        std::reverse(stringToReverse.begin(), stringToReverse.end());
        return "Inordered by adapter: " + stringToReverse;
    }

private:
    Reverse* reverse_;
};


void client(const Inorder* inorder) {
    std::cout << inorder->inorderString() << std::endl;
}

int main() {
    std::cout << "Client working with Inorder objects:" << std::endl;
    Inorder *inorder = new Inorder;
    client(inorder);
    std::cout << "\n";

    Reverse* reverse = new Reverse;
    std::cout <<  "Reverse(Adaptee class) interface produces hard to read string: " << std::endl;
    std::cout << reverse->reverseString();
    std::cout << "\n\n";

    std::cout << "But adapter can solve this problem:" << std::endl;
    Adapter* adapter = new Adapter(reverse);
    client(adapter);
    std::cout << "\n\n";

    delete inorder;
    delete reverse;
    delete adapter;

    return 0;
}