# Semaine 16/16

## Design Pattern 

- Singleton
- Observateur
- Visiteur
- Abstract Factory (method)

## Visiteur

Le visiteur est un patron de conception comportemental qui permet de séparer un algorithme de traitement de données de la structure de données sur laquelle il opère. Cela permet de définir de nouvelles opérations sur une structure de données sans avoir à modifier cette dernière.

Les cas d'utilisation du visiteur sont les suivants :

- Lorsque vous avez besoin d'effectuer une opération sur des objets d'une structure de données complexe (par exemple, un arbre composite).
- Lorsque vous avez besoin d'effectuer des opérations sur des objets de différentes classes qui ne partagent pas d'interface commune.
- Lorsque vous avez besoin d'effectuer des opérations sur une structure de données sans modifier ses classes.
- Lorsque vous avez besoin d'effectuer des opérations sur une structure de données et que vous ne voulez pas que ces opérations soient réparties dans les classes de cette structure.

## S.O.L.I.D

- Single Responsibility Principle
- Open/Closed Principle
- Liskov Substitution Principle
- Interface Segregation Principle
- Dependency Inversion Principle

### Single Responsibility Principle

Ce principe stipule qu'une classe ne doit avoir qu'une seule raison de changer. En d'autres termes, une classe ne doit avoir qu'une seule responsabilité.

Par exemple : une classe qui traite des données ne s'occupe pas de l'affichage des données. Il est préférable d'avoir une classe qui traite les données et une autre qui s'occupe de l'affichage.

### Open/Closed Principle

Ouvert à l'extension mais fermé à la modification. Autrement dit, une classe doit être ouverte à l'ajout de nouvelles fonctionnalités mais fermée à la modification de son code source.

```c 
void display(FILE* fp) {
    fprintf(fp, "Hello, World!");
}
```

### Liskov Substitution Principle

En une phrase, ce principe stipule que les objets d'une classe dérivée doivent pouvoir remplacer les objets de la classe de base sans affecter le comportement du programme.

