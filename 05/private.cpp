#include <string>

class Admin;

class CheckPassword {
    public:
    friend class Admin;
    bool check(std::string password) {
        return password == this->password;
    }

    private:
    void change(std::string password) {
        this->password = password;
    }
    std::string password;
};

class Admin {
    CheckPassword & cp;
    public:
    Admin(CheckPassword &cp) : cp{cp} {
    }

    void changePassword(const std::string& newPassword) {
        cp.change(newPassword);
    }
};


class User {
    CheckPassword & cp;
    User(CheckPassword &cp) : cp{cp} {}

    void foo() {
        check.password
    }
}