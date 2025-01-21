# Semaine 15/16

## Correction travail écrit

Déclarer un tableau dynamique de double et insérer la valeur 3.14. 

```cpp
std::vector<double> a;
a.push_back(3.14);
a.emplace_back(3.14); 

class Point {
    int x,y;
    Point(int x, int y) : x{x}, y{y} {}
};

std::vector<Point> points;
points.push_back(Point(2,3));
points.emplace_back(2, 3);

Point *p = &points[0]; // Dangereux !
int i = 0;  // Mais on peut sauvegarder l'indice. 
```

La classe Printer est construite avec en paramètre son adresse IP passée sous forme de chaîne de caractère littérale "192.168.1.2". Allouer sur le TAS (HEAP) son objet.

```cpp
Printer *p = new Printer("192.168.1.2");
auto *p = new Printer("192.168.1.2");
delete p;
```

En respectant le concept RAII, créer sur le tas (heap) un tableau statique de 10 entiers qui sera partagé plus tard par plusieurs instances. Lorsque toutes les références seront libérées, le tableau doit être détruit automatiquement.

```cpp
std::shared_ptr<std::array<int, 10>> p = 
std::make_shared<std::array<int, 10>>();
```

Déclarer une référence vers l'instance foo de la classe Foo;

```cpp
Foo &refFoo = foo;
```

Déclarer une interface Animal ayant une méthode virtuelle pure publique void speak()

```cpp
struct Animal {
    virtual void speak() = 0;
};

// Implémentation pas autorisée
void Animal::speak() {
    ...
}
```

La classe Point contient deux attributs publcs x et y dont le typ est spécifié pa r un template:

```cpp
template <typename T> 
struct Point {
    T x, y;
    Point(T x, T y) : x{x}, y{y} {}
}
```

Écrire une fonction add prenant jusqu'à 3 entiers en argument et retournant leur somme. Si moins de 3 arguments sont passés, les valeurs manquantes sont considéres comme nulles. 

```cpp
int add(int a=0, int b=0, int c=0) {
    return a + b + c;
}

add()
add(1)
add(1,2)
add(1,2,3)
```

La classe Triangle hérite de la classe Sahpe, son constructeur prend en paramètre sa base et sa hauteur. 

```cpp
struct Triangle : public Shape {
    int base, height; // ? 
    Triangle(double base, double height);
};
```

À quoi sert le CRTP 
Curiously Recurring Template Pattern

```cpp
template<class T, class Base>
struct Foo {
    T x;
    Foo() = default;
    Base& operator+(const Base &other) {
        return Foo(x + other.x);
    }
}

template<class T>
struct Bar : public Foo<T, Bar> {
    using Foo::Foo; // Utiliser les constructeurs par défaut de foo
}
```

Quels sont les constituants implicites d'une classe

```cpp
class Foo {
    int x, y;
    Foo() = default;
    Foo(const Foo &other) = default;
    Foo & operator=(const Foo &other) {
        x = other.x;
        y = other.y;
        return *this;
    }
    Foo & operator=(const Foo &&other) = default;
    
    ~Foo() = default;

    //Foo(int x, int y): x{x}, y{y} {}
};

Foo f1();
Foo f2 = {1,2};
Foo f3 = f2; // Constructeur par copie
Foo f4(f2);  // Constructeur par copie

f3 = f1; // Opérateur d'affectation

int a = 42; // int a(42);
int b = 23;
a = b;

a = std::move(b);

printf("%d", b = 42);
```

Héritage en diamant

```cpp
class A {};

class B: virtual public A {};
class C: virtual public A {};

class D: public B, public C {};

D d; // A B A C D ~D ~C ~A ~B ~A
```

Insertion dans un tableau dynamique complexité temporelle est de O(1) amortie.

capacity elements
1 1 (1)
2 2 (1)
4 3 (2)
4 4 
8 5 (4)
8 6
8 7 
8 8
16 9 (8)
16 10
16 11
16 12
16 13
16 14
16 15
16 16


```c
int foo(){
    int a, b c;
}

int main() {
    if (rand() % 2) {
        foo();
    }
}
```

Quelle structure de données utiliser pour implémenter une file d’attente dont les éléments sont
insérés en tête et retirés en queue ?

head 
tail

a->b->c->d

// Add
Node *e = new Node('e');
e->next = head;
head = e;

// Delete
while(node->next != tail) {
    node = node->next;
}
tail = node
node->next = nullptr;

```cpp
class Foo {
    const int x, y;
    Foo(int x, int y) : x{x}, y{y} {
        x = 42; // Interdit
    }
}



```cpp
{
    auto newsletter = std:: make_shared <Newsletter >();
    {
        auto alice = std:: make_shared <Subscriber >("Alice"); // Ref alice = 1
        newsletter ->subscribe(alice); // Ref alice = 2
    } // Ref alice = 1
} // Ref alice = 0 -> delete alice
```