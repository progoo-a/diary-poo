template <typename T>
struct Point {
    T x,y;
    Point(T x, T y) : x(x), y(y) {}
};

int main() {
    Point<int> p(1,2);
    Point<float> q(1.0,2.0);
    Point<double> r(1.0,2.0);
}