struct Base { 
  int base{1998};
};
 
struct Derived : Base { 
  int derived{2011};
};

void needB(Base b) {
    b.derived;
}
 
int main() {

  Derived d;
  Base b = d;  
  b.derived;

  Base b2(d);             
  b2.derived;
  needB(d);  

}