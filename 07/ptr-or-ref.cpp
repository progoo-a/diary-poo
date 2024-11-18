
struct Heavy {
    int data[1000];
};

void f(Heavy *h) {
    if (h == nullptr) return;
    h->data[0] = 0;
    // Do something with h
}

void f(Heavy &h) {
    h.data[0] = 0;
    // Do something with h
}

int main() {
    Heavy h;
    f(&h); // Adress of h
    f(h); // h itself
}