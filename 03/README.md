# Semaine 03/16

- [x] Résumé des flux
    - [x] Hiérarchie de clases (std::ios, std::istream, std::ostream)
    - [x] Les flux de fichiers sont identifié par des numéros (0,1,2,...)
    - [x] Un fichier ouvert ou un flux ouvert : c'est pareil
    - [x] On peut configurer les nombres dans un flux avec <iomanip>
- [x] Polymorphisme statique
    - [x] Surcharge paramétrique (même nom, mais pas le même nombre/type de paramètres)
    - [x] Définir des valeurs par défaut (attention aux conflits)
- [x] Allocation dynamique
    - [x] Opérateurs `new` et `delete`
    - [x] Attention à bien libérer la mémoire après utilisation (comme en C)
- [x] Méthodes par défaut
    - [x] Constructeur par défaut
    - [x] Constructeur de copie
    - [x] Destructeur
    - [x] Opérateur d'affectation

## Un programme

- input, stdin, std::cin, 0 (pas seekable)
- output, stdout, std::cout, 1
- erreur, stderr, std::cerr, 2

- `<<` redirection de l'entrée
- `>>` redirection de la sortie

```c++
#include <iostream>
#include <ofstream>
#include <string>

int main() {
    std::string filename("output.txt");
    std::ofstream file;
    if (filename.size() > 0) {
        file = std::ofstream(filename);
    else 
        file = std::cout;

    file << "Hello";
}
```

## Configuration des nombres dans un flux

```c
printf("%10.4f", 3.14159265358979323846);
```

```c++
#include <iomanip>

std::cout << std::setw(10) << std::setprecision(4) << 3.14159265358979323846;
// Alignement à droite
std::cout << std::right << std::setw(10) << 3.14159265358979323846;
```

## Polymorphisme statique 

Surcharge paramétrique. Si y'a un conflit, le compilateur va se plaindre.

```c++
int add(int a, int b) { return a + b; }
int add(int a, int b, int c) { return a + b + c; }
float add(float a, float b) { return a + b; }
double add(double a, double b) { return a + b; }

int add(float a, float b) { return a + b; } // Erreur : même signature

// Définir des valeurs par défaut
namespace prout {
int add(int a, int b, int c = 42) { return a + b + c; } 
}
int main() {
    add(1, 2);
    add(1, 2, 3);
    add(1.0f, 2.0f);
    add(1.0, 2.0);
    add(1.0, 42); // Erreur : je ne sais pas comment deviner... 
    prout::add(1, 2); // 45 (valeurs par défaut)
}
```

## Allocation dynamique

```c
#include <stdlib.h>

int* a = (int*)malloc(sizeof(int));
*a = 42;
free(a);
```

```c++
int *a = new int(42);
delete a;
```

## Methodes par défaut

Une classe en C++ a toujours : 

- un constructeur par défaut
- un constructeur de copie
- un destructeur
- un opérateur d'affectation
- un constructeur de déplacement (advanced *move semantics*)

```c++
class A {
    public:
    A() {}
    A(const A& a) {}
    ~A() {}
    A& operator=(const A& a) {}
};

int main() { A a;}
```