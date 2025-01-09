# Semaine 09/16

<<<<<<< HEAD
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
=======
## Héritage en diamant

L'héritage en diamant est une situation où une classe dérivée hérite de deux classes de base qui elles-mêmes héritent d'une même classe de base. Par exemple, considérons les classes suivantes:

```cpp
class A {
public:
    void foo() {
        std::cout << "A" << std::endl;
    }
};

class B : public A {
public:
    void foo() {
        std::cout << "B" << std::endl;
    }
};

class C : public A {
public:
    void foo() {
        std::cout << "C" << std::endl;
    }
};

class D : public B, public C {

};
```

## Mots clés

- `constexpr`
- `final`
- `override`
- `noexcept`
- `friend`

## Spécialisation

La spécialisation des templates permet de définir une version spécifique d'un template pour un type donné. Par exemple, on peut définir une version spécifique d'un template pour le type `int`:

```cpp
template <typename T>
struct Foo {
    static void print() {
        std::cout << "Generic" << std::endl;
    }
};

template <>
struct Foo<int> {
    static void print() {
        std::cout << "Int" << std::endl;
    }
};
```

## CRTP

Le patron de conception CRTP (Curiously Recurring Template Pattern) est un modèle de programmation qui utilise des templates pour implémenter l'héritage statique. Il est utilisé pour ajouter des fonctionnalités à une classe de base en utilisant une classe dérivée. Le CRTP repose sur une technique un peu "curieuse" : une classe dérivée se passe comme paramètre à une classe de base template. Cette structure est à la fois puissante et subtile.

```cpp
#include <iostream>

// La "Base" est un moule template
template <typename Derived>
class Base {
public:
    void interface() {
        // On appelle une méthode spécifique de la classe dérivée !
        static_cast<Derived*>(this)->implementation();
    }
};

// La classe dérivée dit à "Base" : "Je suis Derived !"
class Derived : public Base<Derived> {
public:
    void implementation() {
        std::cout << "Je suis Derived, appelée via Base !" << std::endl;
    }
};

int main() {
    Derived obj;
    obj.interface(); // Appelle Derived::implementation via Base
}
```

## Variadic templates

Le terme "variadic" signifie "pouvant varier". Les templates variadiques sont des templates qui acceptent un nombre variable d'arguments. Ils sont utilisés pour définir des fonctions et des classes qui peuvent accepter un nombre variable d'arguments. Prenons l'exemple d'une fonction add générique qui peut accepter un nombre variable d'arguments:

```cpp
add(1, 2);
add(1, 2, 3);
add(1, 2, 3, 4);
...
```

Pour définir une fonction add qui accepte un nombre variable d'arguments, on utilise un template variadique:

```cpp
template<typename... Args>
auto add(Args... args) {
    return (args + ...);
}
```

Bien entendu en C classique on peut également définir une fonction add qui accepte un nombre variable d'arguments en utilisant la fonction `va_arg`. Néanmoins cette implémentation est dynamique et moins efficace que l'implémentation statique avec les templates variadiques.

```cpp
#include <cstdarg>

int add(int count, ...) {
    va_list args;
    va_start(args, count);
    int sum = 0;
    for (int i = 0; i < count; ++i) {
        sum += va_arg(args, int);
    }
    va_end(args);
    return sum;
}
```

Par exemple prenons le cas d'une classe conteneur qui peut contenir un nombre variable d'éléments:

```cpp
template <typename T, size_t N>
class Container {
  protected:
    std::array<T, N> data;
  public:
    template <typename... Args>
    requires (sizeof...(Args) == N && std::conjunction_v<std::is_convertible<Args, T>...>)
    constexpr Container(Args... args) : coords{ static_cast<T>(args)... } {}
};
```

Ici, on utilise un concept pour vérifier que le nombre d'arguments passés au constructeur est égal à `N` et que tous les arguments sont convertibles en `T`.

## Concepts

### Traits

| Nom                  | Définition                                                  |
| -------------------- | ----------------------------------------------------------- |
| DefaultConstructible | Un objet peut être construit sans arguments                 |
| CopyConstructible    | Un objet peut être construit par copie                      |
| MoveConstructible    | Un objet peut être construit par déplacement                |
| CopyAssignable       | Un objet peut être assigné par copie                        |
| MoveAssignable       | Un objet peut être assigné par déplacement                  |
| Destructible         | Un objet peut être détruit                                  |
| Swappable            | Un objet peut être échangé avec un autre objet de même type |
| EqualityComparable   | Un objet peut être comparé à un autre objet de même type    |
| Callable             | Un objet peut être appelé comme une fonction                |

Plus d'informations sur les concepts [ici](https://en.cppreference.com/w/cpp/named_req).

Certain de ces concepts peuvent être testés avec des fonctions de la bibliothèque standard. Par exemple, `std::is_default_constructible`, `std::is_copy_constructible`, `std::is_move_constructible`, `std::is_copy_assignable`, `std::is_move_assignable`, `std::is_destructible`, `std::is_swappable`, `std::is_equality_comparable`, `std::is_invocable`.

```cpp
#include <type_traits>

struct C {
    C() = default;
};

static_assert(std::is_default_constructible_v<C> == true);
```

### Concepts

Un concept est une spécification de type qui peut être utilisée pour restreindre les types qui peuvent être utilisés comme arguments de modèles de classes ou de fonctions. Un concept est défini avec le mot-clé `concept`.

Il s'agit d'une nouvelle fonctionnalité de C++20 qui s'utilise avec les templates. Imaginons que nous disposons d'une methode `print`:

```cpp
template <typename T>
void print(const T& message) {
    std::cout << message << std::endl;
}
```

L'ennui c'est que cette méthode ne fonctionne pas avec tous les types. Par exemple, si on essaye de l'utiliser avec un type `std::vector<int>`, on obtient une erreur de compilation et parfois un message d'erreur incompréhensible. On peut utiliser un concept pour restreindre les types acceptés par la méthode `print`:

```cpp
template <typename T>
concept Printable = requires(T t) {
    std::cout << t;
};
```

Dans l'implémentation de `requires` on peut mettre autant de conditions que l'on veut. Par exemple, on peut ajouter une condition pour vérifier si le type `T` dispose d'une méthode `size`:

```cpp
template <typename T>
concept Printable = requires(T t) {
    std::cout << t;
    t.size();
};
```

Notre méthode `print` peut maintenant être modifiée pour accepter uniquement les types qui satisfont le concept `Printable`:

```cpp
template <Printable T>
void print(const T& message) {
    std::cout << message << std::endl;
}
```

D'une manière plus générale, un objet `Printable` devrait pouvoir écrire sur n'importe quel flux de sortie. On peut donc définir un concept `Printable` de la manière suivante:

```cpp
template <typename T>
concept Printable = requires(std::ostream &os, const T& t) {
    { os << t } -> std::convertible_to<std::ostream&>;
};
```

Dans cet exemple, on vérifie que l'expression `os << t` est convertible en `std::ostream&`. Notez la présence d'accolades autour de l'expression `os << t`. Elles sont nécessaires lorsqu'une contrainte sur le type de retour est spécifiée. En pratique, pour accroître la robustesse de notre concept, il est préférable de toujours mettre des accolades :

```cpp
template <typename T>
concept Printable = requires(T t) {
    { std::cout << t } -> std::same_as<std::ostream&>;
    { t.size() } -> std::convertible_to<std::size_t>;
};
```

### Règles de cuisines

Type de retour identique au type source:

```cpp
template <typename T>
concept Incrementable = requires(T t) {
    { ++t } -> std::same_as<T&>;  // L'expression `++t` doit retourner `T&`
};
```

Type nombre:

```cpp
concept Arithmetic = std::integral<T> || std::floating_point<T>;
```

Composition de concepts:

```cpp
template <typename T>
concept PrintableAndSizeable = Printable<T> && requires(T t) {
    { t.size() } -> std::convertible_to<std::size_t>;
};
```

### Concepts inline

Il est possible de définir un concept inline:

```cpp
std::integral auto x = foo();
```

### Enable-if et static_assert

Avant C++20, on utilisait `std::enable_if` pour restreindre les types acceptés par une méthode. Par exemple, pour restreindre les types acceptés par la méthode `print`:

```cpp
template <typename T>
std::enable_if_t<std::is_same_v<T, int>, void> print(const T& message) {
    std::cout << message << std::endl;
}
```

L'utilisation de `enable_if` est par conséquent destinée à être remplacée par les concepts.

De la même manière avant C++20 on utilisait `static_assert` pour vérifier si un type satisfait un concept:

```cpp
template <typename T>
void print(const T& message) {
    static_assert(std::is_same_v<T, int>, "T must be an int");
    std::cout << message << std::endl;
}
```

L'utilisation de `static_assert` est par conséquent destinée à être remplacée par les concepts, et dans sa version simplifiée. Voici le code avant et après:

```cpp
template <typename T>
void process(T value) {
    static_assert(std::is_integral<T>::value, "T must be integral");
    // ...
}
```

```cpp
template <std::integral T>
void process(T value) {
    // ...
}
```

### SFINAE

SFINAE (Substitution Failure Is Not An Error) est une technique utilisée pour éviter les erreurs de compilation lors de l'instanciation de templates.

Le principe de fonctionnement est le suivant : si une substitution échoue, le compilateur ne génère pas d'erreur de compilation, mais essaie de trouver une autre surcharge de la fonction qui correspond à l'appel.

Les templates sont vues comme des candidats potentiels pour la résolution de surcharge. Si une substitution échoue, le template est simplement éliminé de la liste des candidats, jusqu'à ce que le compilateur trouve une surcharge qui fonctionne.

### Limites

Les concepts ne peuvent pas exiger des exigences dynamiques comme la taille d'une collection ou les relations entre plusieurs valeurs d'un type. Par exemple, on ne peut pas définir un concept pour vérifier si un type est un conteneur de taille supérieure à 10.

Ils ne remplacent pas non plus les spécialisations classiques des templates.
### Résumé

Les concepts sont de plus en plus utilisés dans la STL, Boost et d'autres bibliothèques. Ils permettent de rendre le code plus lisible, plus robuste et plus facile à maintenir. Ils remplacent progressivement les techniques de SFINAE comme enable_if et static_assert et limitent généralement la taille des messages d'erreur de compilation.

D'autre part les concepts limitent le coût d'évaluation à la compilation car ils n'entraînent pas une instanciation complète du template pour vérifier les contraintes. Cela peut réduire significativement le temps de compilation pour les gros projets.

## Optional, Variant et Expected

### Variant

Le header `<optional>` fournit une alternative à l'utilisation des pointeurs nuls. Il permet de représenter une valeur optionnelle qui peut être absente. Par exemple, on peut utiliser `std::optional` pour représenter un entier optionnel:

```cpp
std::optional<double> value;
auto div(double a, double b) -> std::optional<double> {
    if (b == 0) return std::nullopt;
    return a / b;
}
```

Cette syntaxe moderne permet d'éviter d'utiliser un pointeur nulle ou une exception pour gérer les cas où la valeur est absente. C'est donc une approche élégante et plus sûre. Au niveau performance, `std::optional` est généralement aussi rapide qu'un pointeur nul mais elle consommé plus de mémoire. En effet, `std::optional` contient un booléen pour indiquer si la valeur est présente ou non.

Pour tester si une valeur est présente, on peut utiliser la méthode `has_value`:

```cpp
if (div(2,0).has_value()) {
    std::cout << value.value() << std::endl;
} else {
    std::cout << "Division par zéro" << std::endl;
}
```

### Variant

Le header `<variant>` fournit une alternative à l'utilisation des unions. Il permet de représenter un type qui peut être l'un de plusieurs types. Par exemple, on peut utiliser `std::variant` pour représenter un entier ou une chaîne de caractères:

```cpp
std::variant<int, std::string> value;
value = 42;
value = "Hello";
```

Pour tester le type actuel de la variable, on peut utiliser la méthode `index`:

```cpp
if (value.index() == 0) {
    std::cout << "Entier: " << std::get<int>(value) << std::endl;
} else {
    std::cout << "Chaîne: " << std::get<std::string>(value) << std::endl;
}
```
>>>>>>> 3184c85 (README 09)
