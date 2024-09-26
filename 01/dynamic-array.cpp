#include <iostream> 
#include <string>
#include <optional> 

using namespace std;

template <typename T>
class DynamicArray {
    public: 
        DynamicArray() {
            size = 0;
            capacity = 1;
            arr = new T[capacity];
        }

        void push(T val) {
            if(size == capacity) {
                auto *temp = new T[2 * capacity];
                for(int i = 0; i < capacity; i++) {
                    temp[i] = arr[i];
                }
                delete[] arr;
                capacity *= 2;
                arr = temp;
            }
            arr[size] = val;
            size++;
        }

        void pop() {
            if(size > 0) {
                size--;
            }
        }
        
        optional<T> get(int index) {
            if(index < size) {
                return arr[index];
            }
            return {};
        }

        int getSize() {
            return size;
        }
    private: 
        T *arr;
        int size;
        int capacity;
};

int main() {
    DynamicArray<string> foo;
    for(int i = 0; i < 10; ++i) foo.push("Toto");

    for(int i = 0; i < foo.getSize(); i++) {
        cout << foo.get(i).value() << ", ";
    }
    cout << "\n";
}