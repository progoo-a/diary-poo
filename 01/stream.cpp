#include <iostream>
using namespace std;

// struct StreamOut {
//     FILE *fp;
//     StreamOut(FILE *_fp) {
//         fp = _fp;
//     }

//     void operator<<(const int other) {
//         fprintf(fp, "%d", other)
//     }
//     void operator<<(const char* other) {
//         fprintf(fp, "%s", other)
//     }
// }

int main() {
    int i = 42;
    // printf("%d", i);

    // StreamOut s(stdout);
    // StreamOut k(stderr);
    cout << "Le nombre est " << i << "\n";
}