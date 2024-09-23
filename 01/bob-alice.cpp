#include <stdio.h>

struct Person {
   char name[32];
   int age;

   unsigned int born_year(int today) {
       return today - age;
   }

   int operator+(const Person &other) {
      return age + other.age;
   }
};


int main() {
    struct Person bob = {"Bob", 23};
    struct Person alice = {"Alice", 42};
    printf("%s est né en %d\n", bob.name, bob.born_year(2024));

    int cumulated_age = bob + alice;
    printf("Age cumulé : %d\n", cumulated_age);
}