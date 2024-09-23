#include <stdio.h>

struct Password {
    void set_password(char *s);
    bool test(char *str); 
    private:
    char password[64];
};

class Password2 {
    char password[64];
public:
    void set_password(char *s);
    bool test(char *str); 
};

int main() {
    Password p;
    p.set_password("toto");

    printf("%s\n", p.password);
}