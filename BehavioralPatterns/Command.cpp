#include <iostream>
#include <string>
#include <vector>


/**
 * Class Order is a command interface.
 */
class Order {
public:
    virtual void execute() const = 0;
};


class Stock {
public:
    Stock(std::string name, int quantity)
        : name_(name), quantity_(quantity) {

    }

    void buy() {
        std::cout << "Stock: [" << name_ << ", " << quantity_ << "] bought.\n";
    }

    void sell() {
        std::cout << "Stock: [" << name_ << ", " << quantity_ << "] sold.\n";
    }

private:
    std::string name_;
    int quantity_;
};


/**
 * Concrete command classes
 */
class BuyStock : public Order {
public:
    BuyStock(Stock* stock) : stock_(stock) {

    }

    void execute() const override {
        stock_->buy();
    }

private:
    Stock* stock_;
};


class SellStock : public Order {
public:
    SellStock(Stock* stock) : stock_(stock) {

    }

    void execute() const override {
        stock_->sell();
    }
private:
    Stock* stock_;
};


/**
 * Class Broker is the invoker class.
 */
class Broker {
public:
    void takeOrder(Order* order) {
        orders_.push_back(order);
    }

    void placeOrders() {
        for (Order* order : orders_) {
            order->execute();
        }

        orders_.clear();
    }

private:
    std::vector<Order*> orders_;
};


int main() {
    Stock* stock = new Stock("Stock1", 10);

    BuyStock* buyStock = new BuyStock(stock);
    SellStock* sellStock = new SellStock(stock);

    Broker* broker = new Broker;
    broker->takeOrder(buyStock);
    broker->takeOrder(sellStock);
    broker->placeOrders();

    return 0;
}