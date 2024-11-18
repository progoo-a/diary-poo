#include <iostream>

template <typename... Args>
struct MakeSmartPointer {
    template <typename T>
    static auto make(Args&&... args) {
        return new T(std::forward<Args>(args)...);
    }
};

template <typename T>
struct SmartPointer
{
    T *ptr;
    int *counter;

    SmartPointer(int *ptr) : ptr(ptr), counter(new int(1)) {}

    SmartPointer(MakeSmartPointer<T> maker) : ptr(maker.make()), counter(new int(1)) {}

    // Constructeur de copie
    SmartPointer(const SmartPointer &other) : ptr(other.ptr), counter(other.counter)
    {
        (*counter)++;
    }

    // Opérateur d'affectation
    SmartPointer &operator=(const SmartPointer &other)
    {
        if (this == &other)
            return *this;

        // Libérer les ressources de l'objet actuel
        if (--(*counter) == 0)
        {
            delete ptr;
            delete counter;
        }

        // Copier les ressources de l'autre objet
        ptr = other.ptr;
        counter = other.counter;
        (*counter)++;
        return *this;
    }

    // Opérateur de déréférencement
    auto &operator*() const
    {
        return *ptr;
    }

    auto *operator->() const
    {
        return ptr;
    }

    size_t use_count() const
    {
        return *counter;
    }

    // Destructeur
    ~SmartPointer()
    {
        std::cout << "~SmartPointer" << std::endl;
        if (--(*counter) == 0)
        {
            std::cout << "delete ptr" << std::endl;
            delete ptr;
            delete counter;
        }
    }
};

int main()
{
    //SmartPointer<int> p(new int(42));
    auto p = SmartPointer<int>(MakeSmartPointer<int>(3));

    std::cout << "UC: " << p.use_count() << std::endl;
    {
        SmartPointer q(p);
        std::cout << "UC: " << p.use_count() << std::endl;
        std::cout << "UC: " << q.use_count() << std::endl;

        std::cout << *q << std::endl; // Affiche 42

    }
    std::cout << "UC: " << p.use_count() << std::endl;
    std::cout << *p << std::endl; // Affiche 42
}
