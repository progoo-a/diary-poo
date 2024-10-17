# Semaine 05/16

- [x] Factory Method
- [x] Introduction au Polymorphisme avec des tables virtuelles
- [x] Liste d'initialisation
- [x] Narrowing
- [x] Polymorphisme dynamique, notion de virtual tables

## Polymorphisme dynamique

Le polymorphisme dynamique est une technique de programmation qui permet de manipuler des objets de classes **dérivées** à travers des pointeurs ou des références de classes de base. Le polymorphisme dynamique est réalisé en utilisant des **méthodes virtuelles**.

Une classe dérivée c'est une classe qui hérite d'une autre classe. 

Une **méthode virtuelle** est une méthode qui peut être redéfinie dans une classe dérivée. Cela implique la création d'une table virtuelle (vtable) qui contient les adresses des méthodes virtuelles de la classe. La vtable est créée à la compilation. À l'appel de la méthode, le coût est un peu plus élevé car il faut accéder à la vtable pour obtenir l'adresse de la méthode.

Une méthode virtuelle peut être **pure** si elle n'a pas d'implémentation. Une classe qui contient une méthode virtuelle pure est une classe abstraite. Une classe abstraite ne peut pas être instanciée.

Une classe abstraite dont toutes les méthodes sont virtuelles pures est une interface.

Pour définir une méthode virtuelle, il suffit de la déclarer avec le mot-clé `virtual`. Pour définir une méthode virtuelle pure, il suffit de la déclarer avec le mot-clé `virtual` suivi de `= 0`.

Le mot clé `override` est utilisé dans les classes dérivées pour indiquer que la méthode redéfinit une méthode virtuelle de la classe de base. En pratique, le mot clé `override` n'est pas obligatoire, mais il est recommandé pour éviter les erreurs, car si `override` est utilisé et que la méthode de base n'est pas `virtuelle` une erreur de compilation sera générée.


## Most Vexing Parse

Le most vexing parse est une ambiguïté de syntaxe qui peut survenir lors de la déclaration d'un objet. Par exemple, la déclaration `Toto t();` est ambiguë. Elle peut être interprétée comme une déclaration d'une fonction `t` qui retourne un `Toto` ou comme une déclaration d'un objet `t` de type `Toto`. Pour résoudre cette ambiguïté, il suffit de retirer les parenthèses.

Quelques années plus tard, la syntaxe `Toto t();` a été dépréciée. Il est recommandé d'utiliser la syntaxe `Toto t;` pour déclarer un objet, ou d'utiliser les accolades pour l'initialisation.

Scott Meyers à découvert en 2001, soit 18 ans après la création du C++, que la syntaxe `Toto t();` est ambiguë. Il a écrit un article sur le sujet dans son livre "Effective C++".

```cpp
class Toto {};

Toto t() { return Toto(); }

int main() {
    Toto t(); // Soit 1. J'appelle le constructeur par défaut de Toto
              // Soit 2. Je déclare une fonction t qui retourne un Toto
};
```

Une correction apportée par le langage est les accolades. Mais comme c'est con d'ajouter une nouvelle syntaxe sans fonctionnalités, ils ont ajouté le narrowing.

## Narrowing

Le narrowing est une conversion implicite qui **peut causer** une perte de données. Par exemple, la conversion d'un `double` en `int` est un narrowing. Le narrowing est interdit dans les listes d'initialisation.

```cpp
long u = 489302;
short s{u};

int x(3.14); // narrowing est autorisé
int y{3.14}; // erreur: narrowing est interdit
```
## Liste d'initialisation

La liste d'initialisation est une syntaxe qui permet d'initialiser les membres d'une classe dans le constructeur. Elle est plus efficace que l'initialisation dans le corps du constructeur. Elle est obligatoire pour les membres constants et les références.

```cpp
class Point {
    int x;
    int y;
public:
    // Point(int x, int y) {
    //     this->x = x;
    //     this->y = y;
    // }
    Point(int x, int y) : x{x}, y{y} {}
};
```

## Factory Method

Une classe de fabrique est une classe qui contient une méthode static qui retourne une instance d'une classe. Cette méthode est appelée méthode de fabrique. La méthode de fabrique est utilisée parfois pour simplifier la lecture code, gérer les exceptions, ou pour créer des instances de classes dérivées.

```cpp
struct Circle {
    Circle fromXML(std::string xml);
    Circle fromJSON(std::string json);
    Circle fromCSV(std::string csv);
} 