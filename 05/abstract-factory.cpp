#include <regex>
#include <string>

struct Circle
{
    Circle(int x, int y, int r);

    Circle(std::string str) {}

    static Circle fromString(std::string str) {
    std::regex re("\\(\\s*(\\d+(?:\\.\\d+)?)\\s*,\\s*"
                  "(\\d+(?:\\.\\d+)?)\\s*,\\s*"
                  "(\\d+(?:\\.\\d+)?)\\s*\\)");
    std::smatch matches;

    if(!std::regex_search(str, matches, re) || (!matches.size() == 4))
        abort();

    int k = 1;
    double x = stod(matches[k++].str());
    double y = stod(matches[k++].str());
    double r = stod(matches[k++].str());

    return Circle(x,y,r);
}
};

int main() {
    Circle c("Circle(1,2,3)");
    Circle d()
    Circle e = Circle::fromString("Circle(7,8,9)");
}