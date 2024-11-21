# Semaine 08/16 : Résumé

## Méthode virtuelle

```cpp
class Animal {
    int age;
    public:
    virtual void speak() { std::cout << "Animal\n"; }
};

class Dog : public Animal {
    public:
    void speak() override { std::cout << "Woof\n"; }
};

class Cat : public Animal {
    public:
    void speak() override { std::cout << "Meow\n"; }
};

int main() {
    Animal a;
    Dog d;
    Cat c;

    a.speak(); // Animal
    d.speak(); // Woof
    c.speak(); // Meow
}
```

## Interface 

Une interface est une classe abstraite qui ne contient que des méthodes virtuelles pures. 

Une classe abstraite ne définit pas toutes ses méthodes, et n'est par conséquent pas instanciable. 

Une méthode virtuelle c'est une méthode qui peut être redéfinie dans les classes dérivées. 

Une méthode virtuelle pure c'est une méthode qui doit être redéfinie dans les classes dérivées (`= 0`).

```cpp
class Base {
    virtual void foo() = 0;
    virtual void bar() = 0;
};

class Derived : public Base {
    void foo() override { std::cout << "foo\n"; }
    void bar() override { std::cout << "bar\n"; }
};

int main() {
    Base b; // Erreur car Base est abstraite.
}
```


## Surcharge paramétrique

C++ autorise la décalaration de fonctions avec le même nom mais des paramètres différents. C'est ce qu'on appelle la surcharge paramétrique. 

On peut avoir aussi des paramètres par défaut. 

Attention le type de la valeur de retour ne fait pas partie de la signature de la fonction. Autrement dit, on ne peut pas surcharger une fonction en se basant uniquement sur le type de retour. 

```cpp
int add(int a, int b) { return a + b; }
double add(double a, double b) { return a + b; }

// Attention c'est ambigü.
int add(int a, int b, int c = 0) { return a + b + c; }
```

Souvent en objet, les constructeurs sont surchargés. 

```cpp
class Foo {
    Foo() {} // Constructeur par défaut
    Foo(int a) {} // Constructeur avec un paramètre
    Foo(int a, int b) {} // Constructeur avec deux paramètres
    Foo(const Foo& other) {} // Constructeur de copie
    Foo(const Foo&& other) {} // Constructeur de déplacement (std::move)
    ~Foo() {} // Destructeur
}
```

## Surcharge des opérateurs

Dans la définition d'une classe, on peut modifier le comportement des opérations arithmétiques, de comparaison, etc. 

```cpp
class Foo {
    int value;
    auto operator+(const Foo& other) { return Foo(value + other.value); }
    auto operator-(const Foo& other) { return Foo(value - other.value); }
    auto operator*(const Foo& other) { return Foo(value * other.value); }
    auto operator/(const Foo& other) { return Foo(value / other.value); }
    auto operator%(const Foo& other) { return Foo(value % other.value); }

    auto operator==(const Foo& other) { return value == other.value; }
    auto operator!=(const Foo& other) { return value != other.value; }
    auto operator<(const Foo& other) { return value < other.value; }
    auto operator>(const Foo& other) { return value > other.value; }
    auto operator<=(const Foo& other) { return value <= other.value; }
    auto operator>=(const Foo& other) { return value >= other.value; }

    // Spaceship operator (C++20)
    auto operator<=>(const Foo& other) { 
        if (value < other.value) return -1;
        if (value > other.value) return 1;
        return 0;
    }

    // foo[42]
    auto operator[](int index) { return value; }

    // foo(42, 42)
    auto operator()(int a, int b) { return a + b; }

    // Cast operators
    operator char() {
        return value % 255;
    }
    operator double() {
        return std::static_cast<double>(value);
    }

    auto operator++() {  // ++foo
        value = value + 1;
        return Foo(value); 
    }
    auto operator++(int) {  // foo++
        auto tmp = Foo(value);
        value = value + 1;
        return tmp;
    }
    auto operator--() { return Foo(--value); }
    auto operator--(int) { return Foo(value--); }
    auto operator+=(const Foo& other) { value += other.value; return *this; }
    auto operator-=(const Foo& other) { value -= other.value; return *this; }
    auto operator*=(const Foo& other) { value *= other.value; return *this; }
    auto operator/=(const Foo& other) { value /= other.value; return *this; }
    auto operator%=(const Foo& other) { value %= other.value; return *this; }
    auto operator<<(std::ostream& os, const Foo& foo) { os << foo.value; return os; }
    auto operator>>(std::istream& is, Foo& foo) { is >> foo.value; return is; }

    auto operator[](int index) const { return value; }
};
```

## Lambda

Une fonction lambda c'est une fonction **annonyme** que l'on appelle aussi une *closure*.
On peut déclarer une fonction annonyme n'importe où, elle n'a pas besoin d'être déclarée en dehors des fonctions comme en C. 

```cpp
[] /* Contexte */
() /* Les paramètres d'appel */
{} /* Le corps de la fonction */
```

```cpp
// Exemple d'une fonction annonyme prenant un entier en entrée et retournant un entier.
auto f = [](int u){ return 42 + u; };

// Accès au contexte local en lecture seule
int u = 42;
auto g = [=](){ return u; } // return u++ pas autorisé

// Accès au contexte local en lecture/écriture
int counter = 0;
auto h = [&]() { return ++counter; }

std::cout << f(2) << "\n";
```

Le contexte est: 

1. `[]` Rien du tout.
2. `[=]` Tout le contexte local en lecture seule.
3. `[&]` Tout le contexte local par référence (lecture/écriture).
4. `[toto, &tata]` accès à toto par copie et tata par référence.

```cpp
double div2(double u) { 
    // a pas accessible
    return u / 2.; 
}

class Foo {
    int counter = 0;
    public:
    double div2(double u) {
        counter++;
        return u / 2;
    }
};

int main() {
    double a = 42;
    double b = div2(a);

    // Peu d'intérêt mais possible
    auto r = [](double u){ return u / 2.; }(33); 
}
```

Une fonction lambda est généralement utilisées pour: 

1. Les algorithmes de la STL (std::sort, std::find_if, std::transform, etc.)
2. Les fonctions de callback (évènements à chaque itération d'une boucle, etc.)

Dans un jeu de démineur, lorsque l'on clique sur une case, on va progressivement étendre le terrain de jeu jusqu'aux frontières avec des bombres. On pourrait imaginer une animation, et on déclanche un évènement à chaque fois que l'on découvre une case. 

```cpp
class Board {
    /* ... */
    void expandBlanks(coord_t coord, std::function<void(Cell&)> callback = [](Cell&){}) {
        auto cell = (*this)[coord];
        if (cell.revealed || cell.flagged) return;
        cell.revealed = true;
        callback(cell);
        cell.flagged = false;
        --leftToReveal;
        if (cell.neighborBombCount == 0)
            for (auto coords : getNeighborsCoords(coord)) 
                expandBlanks(coords, callback);
    }
};

int main() {
    Board board(10, 10);
    board.expandBlanks({5, 5});
    board.expandBlanks({5, 5}, [](Cell& cell) { 
        std::cout << "Cell at " << cell.coord << " revealed\n"; });
}
```

### Utilisation avec les algorithmes de la STL

```cpp
struct Point { int x, y; };
std::vector<Point> v = { {1, 2}, {3, 4}, {5, 6} };
std::sort(v.begin(), v.end(), [](Point a, Point b) { return a.x > b.x; });
```

Transformer des éléments d'un vecteur:

```cpp
std::vector<int> v = {1, 2, 3, 4, 5};
std::transform(v.begin(), v.end(), [](int u) { return u * 2; });
```

Transformer via une vue:

```cpp
std::vector<int> v = {1, 2, 3, 4, 5};
auto view = v | 
    std::views::transform([](int u) { return u * 2; }) | 
    std::views::take(30) | 
    std::views::reverse() | 
    std::views::filter([](int u) { return u % 2 == 0; });

for (auto u : view) std::cout << u << " ";
```