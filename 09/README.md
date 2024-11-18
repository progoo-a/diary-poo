# Semaine 09/16

## CRTP (Curiously Recurring Template Pattern)

## Héritage en diamant 

L'héritage en diamant est une situation où une classe hérite de deux classes qui elles-mêmes héritent d'une même classe. 

C'est un concept qui est délicat à implémenter et qui selon le langage n'est pas autorisé. Le C# par exemple n'autorise pas l'hériatge multiple.

On résoud en C++ le problème en définissant des classes virtuelles. 

```cpp
class Base {};
class A : public virtual Base {};
class B : public virtual Base {};
class C : public A, public B {};
```

## Héritage multiple

L'héritage multiple est un sujet très controversé en programmaion orientée objet.
En effet, il est difficile de gérer les conflits de nommage et les ambiguités et cela rend souvent le code moins lisible.

Ce que l'on retrouve souvent, notament en Java et C# c'est de l'héritage multiple d'interface. Le terme utilisé dans ce cas c'est l'implémentation d'interface, symbolisé en UML par une flèche d'héritage en pointillé nommée "Réalise"
