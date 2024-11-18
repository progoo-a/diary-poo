# Semaine 08/16 : Résumé

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

