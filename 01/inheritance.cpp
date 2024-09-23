

struct Animal {
    char name[32];
    void eat() {
        printf("L'animal mange\n");
    }
    void sleep() {
        printf("ZZZZ\n");
    }    
    void speak() {
        printf("L'animal parle\n");
    }
};

struct Cat : public Animal {
    void speak() {
        printf("Miaouuuu\n");
    }
};

int main() {
    Cat felix; 
    felix.sleep();
}