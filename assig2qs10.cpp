#include <iostream>
#include <string>
using namespace std;

struct Order {
    int orderID;
    string restaurantName;
    string customerAddress;
    string itemList;
    int preparationTime;
    string orderTime;
};

class FoodDeliveryQueue {
private:
    Order* arr;
    int capacity;
    int front;
    int rear;
    int size;

public:
    FoodDeliveryQueue(int cap) {
        capacity = cap;
        arr = new Order[capacity];
        front = -1;
        rear = 0;
        size = 0;
    }

    bool isempty() {
        return size == 0;
    }

    bool isfull() {
        return size == capacity;
    }

    void insertFront(Order o) {
        if (isfull()) {
            cout << "Queue is full" << endl;
            return;
        }
        if (front == -1) {
            front = 0;
            rear = 0;
        } else {
            front = (front - 1 + capacity) % capacity;
        }
        arr[front] = o;
        size++;
    }

    void insertRear(Order o) {
        if (isfull()) {
            cout << "Queue is full" << endl;
            return;
        }
        if (front == -1) {
            front = 0;
            rear = 0;
        } else {
            rear = (rear + 1) % capacity;
        }
        arr[rear] = o;
        size++;
    }

    void dispatchOrder() {
        if (isempty()) {
            cout << "No orders to dispatch" << endl;
            return;
        }
        cout << "Dispatched Order ID: " << arr[front].orderID << endl;
        front = (front + 1) % capacity;
        size--;
        if (isempty()) {
            front = -1;
            rear = 0;
        }
    }

    void viewNextOrder() {
        if (isempty()) {
            cout << "No orders available" << endl;
            return;
        }
        cout << "Next Order ID: " << arr[front].orderID
             << " Restaurant: " << arr[front].restaurantName
             << " Customer: " << arr[front].customerAddress
             << " Item: " << arr[front].itemList
             << " Prep Time: " << arr[front].preparationTime
             << " Order Time: " << arr[front].orderTime << endl;
    }

    void displayAllOrders() {
        if (isempty()) {
            cout << "No orders in the queue" << endl;
            return;
        }
        cout << "All Orders in Queue:" << endl;
        for (int i = 0; i < size; i++) {
            int index = (front + i) % capacity;
            cout << "Order ID: " << arr[index].orderID
                 << " Restaurant: " << arr[index].restaurantName
                 << "Customer: " << arr[index].customerAddress
                 << " Item: " << arr[index].itemList
                 << "Prep Time: " << arr[index].preparationTime
                 << "Order Time: " << arr[index].orderTime << endl;
        }
    }

    Order cancelOrder(int targetId) {
        if (isempty()) {
            cout << "No orders in the system" << endl;
            return {0, "", "", "", 0, ""};
        }

        int index = -1;
        for (int i = 0; i < size; i++) {
            int pos = (front + i) % capacity;
            if (arr[pos].orderID == targetId) {
                index = pos;
                break;
            }
        }

        if (index == -1) {
            cout << "Order not found" << endl;
            return {0, "", "", "", 0, ""};
        }

        Order cancelled = arr[index];
        for (int i = index; i != rear; i = (i + 1) % capacity) {
            int next = (i + 1) % capacity;
            arr[i] = arr[next];
        }

        rear = (rear - 1 + capacity) % capacity;
        size--;
        if (isempty()) {
            front = -1;
            rear = 0;
        }

        cout << "Cancelled Order ID: " << cancelled.orderID << endl;
        return cancelled;
    }

    void quickOrderCheck(Order o) {
        if (o.preparationTime <= 10)
            insertFront(o);
        else
            insertRear(o);
    }
};

int main() {
    FoodDeliveryQueue q(5);

    Order o1 = {101, "McDonalds", "Street 12", "Burger, Fries", 8, "10:00 AM"};
    Order o2 = {102, "KFC", "Street 7", "Zinger", 15, "10:05 AM"};
    Order o3 = {103, "Pizza Hut", "Street 9", "Pizza", 7, "10:10 AM"};

    q.quickOrderCheck(o1);
    q.quickOrderCheck(o2);
    q.quickOrderCheck(o3);

    q.displayAllOrders();

    q.viewNextOrder();

    q.dispatchOrder();

    q.cancelOrder(102);

    q.displayAllOrders();
}
