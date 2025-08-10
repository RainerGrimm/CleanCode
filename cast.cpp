// Pablo Camacho 

#include <iostream>
#include <memory>
#include <vector>
#include <string>

// ==================== static_cast Examples ====================

// Example 1: Converting numeric types
void calculateAverage() {
    int totalScore = 256;
    int studentsCount = 3;
    double average = static_cast<double>(totalScore) / studentsCount;
    std::cout << "Average score: " << average << std::endl;  // 85.3333
}

// Example 2: Downcasting in inheritance hierarchy (compile-time)
class Animal { public: virtual ~Animal() { std::cout << "Animal object deleted.\n"; } };
class Dog : public Animal { public: void bark() { std::cout << "Woof!\n"; } };

void makeDogBark() {
    Animal* myAnimal = new Dog();
    Dog* myDog = static_cast<Dog*>(myAnimal);  // Safe because we know it's a Dog
    myDog->bark();
    delete myAnimal;
}

// ==================== const_cast Examples ====================

// Example 1: Removing const for function compatibility
void printMessage(char* message) {
    std::cout << "Message: " << message << std::endl;
}

void sendGreeting() {
    const char* greeting = "Hello, World!";
    printMessage(const_cast<char*>(greeting));  // Remove const to match function signature
}

// Example 2: Modifying a const member in a const method
class Counter {
    mutable int debugCount = 0;
    int value = 0;
public:
    void getValue() const {
        const_cast<Counter*>(this)->debugCount++;  // Modify non-mutable member in const method
        std::cout << "Value accessed " << debugCount << " times\n";
    }
};

// ==================== reinterpret_cast Examples ====================

// Example 1: Converting pointer to integer for hashing
void createPointerHash() {
    int* dataPtr = new int(42);
    uintptr_t hashValue = reinterpret_cast<uintptr_t>(dataPtr);
    std::cout << "Pointer hash: " << hashValue << std::endl;
    delete dataPtr;
}

// Example 2: Treating bytes as different type
void readFloatBytes() {
    float temperature = 98.6f;
    unsigned char* bytes = reinterpret_cast<unsigned char*>(&temperature);
    std::cout << "Float bytes: ";
    for (int i = 0; i < sizeof(float); ++i) {
        std::cout << static_cast<int>(bytes[i]) << " ";
    }
    std::cout << std::endl;
}

// ==================== dynamic_cast Examples ====================

// Example 1: Safe downcasting with runtime check
class Shape { public: virtual ~Shape() {} };
class Circle : public Shape { public: void drawCircle() { std::cout << "Drawing circle\n"; } };
class Square : public Shape { public: void drawSquare() { std::cout << "Drawing square\n"; } };

void processShape(Shape* shape) {
    if (Circle* circle = dynamic_cast<Circle*>(shape)) {
        circle->drawCircle();
    } else if (Square* square = dynamic_cast<Square*>(shape)) {
        square->drawSquare();
    }
}

// Example 2: Cross-casting in multiple inheritance
class Flyable { public: virtual void fly() = 0; virtual ~Flyable() {} };
class Swimmable { public: virtual void swim() = 0; virtual ~Swimmable() {} };
class Duck : public Flyable, public Swimmable {
public:
    void fly() override { std::cout << "Duck flying\n"; }
    void swim() override { std::cout << "Duck swimming\n"; }
};

void makeItSwim(Flyable* flyer) {
    if (Swimmable* swimmer = dynamic_cast<Swimmable*>(flyer)) {
        swimmer->swim();  // Cross-cast from Flyable to Swimmable
    }
}

// ==================== std::move Examples ====================

// Example 1: Transferring ownership of expensive resources
void processLargeData() {
    std::vector<int> sourceData(1'000'000, 42);
    std::vector<int> destinationData = std::move(sourceData);  // Transfer, don't copy
    std::cout << "Source size after move: " << sourceData.size() << std::endl;  // 0
    std::cout << "Destination size: " << destinationData.size() << std::endl;    // 1'000'000
}

// Example 2: Moving unique_ptr ownership
std::unique_ptr<std::string> createMessage() {
    auto message = std::make_unique<std::string>("Important data");
    return std::move(message);  // Transfer ownership to caller
}

void receiveMessage() {
    std::unique_ptr<std::string> myMessage = createMessage();
    std::cout << "Received: " << *myMessage << std::endl;
}

// ==================== std::forward Examples ====================

// Example 1: Perfect forwarding in template function
void sendToProcessor(const std::string& str);

template<typename T>
void processValue(T&& value) {
    sendToProcessor(std::forward<T>(value));  // Preserve value category
}

void sendToProcessor(const std::string& str) {
    std::cout << "Processing lvalue: " << str << std::endl;
}

void sendToProcessor(std::string&& str) {
    std::cout << "Processing rvalue: " << str << std::endl;
}

// Example 2: Factory function with perfect forwarding
class Widget {
    std::string name;
    int value;
public:
    Widget(std::string n, int v) : name(std::move(n)), value(v) {}
    void display() { std::cout << "Widget: " << name << ", " << value << std::endl; }
};

template<typename... Args>
std::unique_ptr<Widget> createWidget(Args&&... args) {
    return std::make_unique<Widget>(std::forward<Args>(args)...);  // Forward all arguments perfectly
}

// ==================== Main Function to Test Examples ====================

int main() {
    std::cout << "=== static_cast Examples ===\n";
    calculateAverage();
    makeDogBark();
    
    std::cout << "\n=== const_cast Examples ===\n";
    sendGreeting();
    Counter counter;
    counter.getValue();
    
    std::cout << "\n=== reinterpret_cast Examples ===\n";
    createPointerHash();
    readFloatBytes();
    
    std::cout << "\n=== dynamic_cast Examples ===\n";
    Circle circle;
    processShape(&circle);
    Duck duck;
    makeItSwim(&duck);
    
    std::cout << "\n=== std::move Examples ===\n";
    processLargeData();
    receiveMessage();
    
    std::cout << "\n=== std::forward Examples ===\n";
    std::string lvalueStr = "Hello";
    processValue(lvalueStr);                // Forward as lvalue
    processValue(std::string("World"));     // Forward as rvalue
    
    auto widget = createWidget("MyWidget", 42);
    widget->display();
    
    return 0;
}