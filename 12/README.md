# Semaine 12/16

## STL 

Standard Template Library. 

La STL contient des classes et des fonctions qui permettent de manipuler des structures de données. Elle est principalement composée de templates, ce qui permet de créer des classes et des fonctions génériques. 

Elle se compose en grande partie de : 

- Les conteneurs : 
  - Séquentiels:
    - vecteurs, listes, piles, files
  - Associatifs: 
    - arbres, tables de hachage, etc.
- Les algorithmes : fonctions qui permettent de manipuler les conteneurs.

### Conteneurs 

| Conteneur   | index     | find      | push/pop    | shift/unshift | insert/erase |
| ----------- | --------- | --------- | ----------- | ------------- | ------------ |
| vecteur     | O(1)      | O(n)      | O(1)        | O(n)          | O(n)         |
| liste       | O(n)      | O(n)      | O(1)        | O(1)          | O(1)         |
| liste triée | O(1)      | O(log(n)) | O(n*log(n)) | O(n*log(n))   | -            |
| map (AVL)   | O(log(n)) | O(log(n)) | -           | -             | O(log(n))    |
| map (open)  | O(1)      | O(1)      | -           | -             | O(1)         |

### Algorithmes

#### For each

```cpp
std::vector<int> data;
std::for_each(data.begin(), data.end(), [](int& x) {
  x *= 2;
});
```

#### All values

```cpp
std::vector<int> data;
bool all_positive = std::all_of(data.begin(), data.end(), [](int x) {
  return x > 0;
});
```

#### All values with ranges library C++23

```cpp
std::vector<int> data;
bool all_positive = std::ranges::all_of(data, [](int x) {
  return x > 0;
});
```

#### Any value 

```cpp
std::vector<int> data;
bool any_positive = std::any_of(data.begin(), data.end(), [](int x) {
  return x > 0;
});
```

#### None of 

```cpp
std::vector<int> data;
bool none_positive = std::none_of(data.begin(), data.end(), [](int x) {
  return x > 0;
});
```

#### Find value

```cpp
std::vector<int> data;
auto it = std::find(data.begin(), data.end(), 42);
```

#### Equal 

```cpp 
std::vector<int> data1 = {1,2,3,4}, data2 = {1,2,3,4};
bool equal = std::equal(data1.begin(), data1.end(), data2.begin());
```

Or with ranges:

```cpp
std::vector<int> data1 = {1,2,3,4}, data2 = {1,2,3,4};
bool equal = std::ranges::equal(data1, data2);
```

## Termes objet

### Objet ?

Un objet est une instance d'une classe. Une instance c'est une variable qui contient des données et des méthodes c'est similaire au concept de structure en C mais avec des fonctions associées.

### Classe ? 

Une classe est un modèle pour créer des objets. Elle définit les données et les méthodes qui seront utilisées par les objets.

### Attribut ?

Un attribut est une variable qui est déclarée dans une classe. C'est une donnée qui caractérise un objet (variable d'instance, ou variable d'état).

### Méthode ? 

Une méthode est une fonction qui est déclarée dans une classe. C'est une fonction qui est associée à un objet et qui permet de manipuler les données de cet objet. On parle d'action sur l'instance.

### Encapsulation ? 

L'encapsulation est le fait de regrouper les données et les méthodes qui agissent sur ces données dans une même classe. Cela permet de protéger les données et de les manipuler uniquement à travers les méthodes de la classe.

### Constructeur ? 

Un constructeur est une méthode spéciale qui est appelée lors de la création d'un objet. Il permet d'initialiser les données de l'objet.

### Destructeur ?

Un destructeur est une méthode spéciale qui est appelée lors de la destruction d'un objet. Il permet de libérer les ressources allouées par l'objet.

### Héritage ?

L'héritage est un mécanisme qui permet de créer une nouvelle classe à partir d'une classe existante. La nouvelle classe hérite des attributs et des méthodes de la classe existante.

### Classe dérivée ?

Une classe dérivée est une classe qui hérite d'une autre classe. Elle peut ajouter de nouveaux attributs et de nouvelles méthodes à la classe de base.

### Classe de base ?

Une classe de base est une classe dont une autre classe hérite. Elle peut être appelée classe parent ou super-classe.

### Interface ?

Une interface est une classe abstraite qui ne contient que des méthodes virtuelles pures. Elle permet de définir un contrat que les classes dérivées doivent respecter.

### Classe abstraite ?

C'est une classe qui ne peut pas être instanciée. Elle sert de modèle pour d'autres classes qui en héritent, elle contient au moins une méthode virtuelle pure.

### Polymorphisme ?

Le polymorphisme est la capacité d'un objet à prendre plusieurs formes. En C++, le polymorphisme peut être statique (surcharge de méthodes) ou dynamique (redéfinition de méthodes).

#### Surcharge paramétrique ?

La surcharge paramétrique est le fait de définir plusieurs méthodes avec le même nom mais des paramètres différents. Cela permet d'appeler la méthode en fonction des paramètres passés.

**statique**, **paramétrique** 

```cpp
void print(int x) {
  std::cout << x << std::endl;
}

void print(double x) {
  std::cout << x << std::endl;
}
```

#### Polymorphisme dynamique ?

Le polymorphisme dynamique est le fait de redéfinir une méthode dans une classe dérivée. Cela permet d'appeler la méthode de la classe dérivée à la place de la méthode de la classe de base.

- Des méthodes virtuelles 
- Stocker des pointeurs de la classe de base

```cpp
class Animal { virtual void speak() = 0; };
class Dog : public Animal { void speak() override { std::cout << "Woof!" << std::endl; } };
class Cat : public Animal { void speak() override { std::cout << "Meow!" << std::endl; } };

int main {
    std::vector<Animal*> animals = { new Dog(), new Cat() };
    std::ranges::for_each(animals, [](Animal* a) { a->speak(); });
}
```

### UML

Unified Modeling Language. C'est un langage de modélisation graphique qui permet de représenter les concepts et les relations entre les objets.

#### Diagramme de classes

On utilise le `+` pour les méthodes publiques et le `-` pour les attributs privés.
La syntaxe est la suivante `nom : type = valeur par défaut`. Pour indiquer le protected on utilise `#`.

```text 
+----------------------+
|     Rectangle        |
+----------------------+
| - width: double      |
| - height: double     |
| + area(): double     |
| + perimeter(): double|
+----------------------+
```

Le flèches: 

```text       
────────────────▷    Flèche vide pour l'héritage ("est un")
─ ─ ─ ─ ─ ─ ─ ─ ▷    Flèche pointillée pour la réalisation ("implémente un")
<───────────────◆    Losange plein pour la composition ("a un")
<───────────────◇    Losange vide pour l'agrégation ("a un")
```

Exemple: 

```text 

+----------------------+
|    << interface >>   |
|      Shape           |
+----------------------+
| - color: string      |
| + area(): double     |
| + perimeter(): double|
+----------------------+
          △
          +--------------------------------+
          |                                |
+----------------------+        +----------------------+              |-----------------|
|     Rectangle        |        |      Polygon         |              |     Edge        |
+----------------------+        +----------------------+            * +-----------------+
| - width: double      |        |                      |◆----------->| x : int          |
| - height: double     |        +----------------------+ -edges       | y : int          |
+----------------------+                                              +-----------------+
```

### Composition et aggrégation 

```cpp
class Student { ... };

class School {
  std::vector<Student> students; // Composition
  std::vector<Student*> students; // Aggregation
};
```

```cpp
School school;

school.addStudent(new Student("Alice")); // Aggregation
Student bob("Bob");
school.addStudent(bob); // Aggregation
```

```cpp
using wheel_ptr = std::unique_ptr<Wheel>;
class Wheel { ... };
class Car { 
    std::array<wheel_ptr, 4> wheels;
    Car(wheel_ptr w1, wheel_ptr w2, wheel_ptr w3, wheel_ptr w4) 
        : wheels{std::move(w1), std::move(w2), std::move(w3), std::move(w4)} { }
}; 

Car car(std::make_unique<Wheel>(), std::make_unique<Wheel>(), std::make_unique<Wheel>(), std::make_unique<Wheel>());
```
