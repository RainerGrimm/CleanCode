template <typename T>
struct Container {
    virtual void virtualMember() {}
    void nonVirtualMember() {}
};

template <typename T>
struct Vector: Container<T> {};

int main() {
    
    Vector<int> vi;
    Vector<double> vd;

}
    
