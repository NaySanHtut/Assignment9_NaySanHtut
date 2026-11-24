#include <iostream>
#include <stdexcept>

template <typename T>
class GenericArray {
    private:
        T *data; // dynamically allocated storage
        int length; // number of elements currently stored

    public:
        // Constructor: start with an empty array
        GenericArray() : data(nullptr), length(0) {}

        // Copy constructor (deep copy) so copies never share memory
        GenericArray(const GenericArray &other) : data(nullptr), length(other.length) {
            if (length > 0) {
                data = new T[length];
                for (int i = 0; i < length; i++) { data[i] = other.data[i]; }
            }
        }

        // Assignment operator (deep copy)
        GenericArray &operator=(const GenericArray &other) {
            if (this != &other) {
                delete[] data;
                length = other.length;
                data = nullptr;
                if (length > 0) {
                    data = new T[length];
                    for (int i = 0; i < length; i++) { data[i] = other.data[i]; }
                }
            }
            return *this;
        }

        // Destructor: release the dynamic memory
        ~GenericArray() {
            delete[] data;
        }

        // Add an element to the end: allocate a new, larger array, copy the old
        // elements over, append the new one, then delete the old array.
        void addElement(T value) {
            T *new_data = new T[length + 1];
            for (int i = 0; i < length; i++) { new_data[i] = data[i]; }
            new_data[length] = value;

            delete[] data;
            data = new_data;
            length++;
        }

        // Value at index (bounds checked)
        T at(int index) const {
            if (index < 0 || index >= length) {
                throw std::out_of_range("at(): index out of range");
            }
            return data[index];
        }

        // Number of elements
        int size() const {
            return length;
        }

        // Sum of all elements
        T sum() const {
            T total = T();
            for (int i = 0; i < length; i++)
                total += data[i];
            return total;
        }

        // Maximum element
        T max() const {
            if (length == 0) {
                throw std::out_of_range("max(): array is empty");
            }
            T result = data[0];
            for (int i = 1; i < length; i++) {
                if (data[i] > result) { result = data[i]; }
            }
            return result;
        }

        // Minimum element
        T min() const {
            if (length == 0) {
                throw std::out_of_range("min(): array is empty");
            }
            T result = data[0];
            for (int i = 1; i < length; i++) {
                if (data[i] < result) { result = data[i]; }
            }
            return result;
        }

        // Returns a NEW array holding elements begin..end inclusive.
        // The caller owns the result and must delete[] it.
        // Its length is (end - begin + 1).
        T *slice(int begin, int end) const {
            if (begin < 0 || end >= length || begin > end) {
                throw std::out_of_range("slice(): invalid bounds");
            }

            int n = end - begin + 1;
            T *result = new T[n];
            for (int i = 0; i < n; i++) {
                result[i] = data[begin + i];
            }
            return result;
        }
};

int main() {
    GenericArray<int> int_array;
    for (int i = 0; i < 15; i++) {
        int_array.addElement(i * 2);   // 0, 2, 4, ..., 28
    }
    std::cout << "size of array is " << int_array.size() << std::endl;
    std::cout << "sum of the array is " << int_array.sum() << std::endl;
    std::cout << "maximum and minimum of array is " << int_array.max()
              << "\t" << int_array.min() << std::endl;
    std::cout << "element at index 3 is " << int_array.at(3) << std::endl;

    int begin = 5, end = 10;
    int *sliced_array = int_array.slice(begin, end);
    std::cout << "slice(" << begin << "," << end << ") = ";
    for (int i = 0; i < end - begin + 1; i++)
        std::cout << sliced_array[i] << " ";
    std::cout << std::endl;
    delete[] sliced_array; // caller cleans up the slice

    // Bounds checking demo
    try {
        int *bad = int_array.slice(10, 20);
        delete[] bad;
    }
    catch (const std::out_of_range &e) {
        std::cout << "caught: " << e.what() << std::endl;
    }

    // Works with other numeric types too
    GenericArray<double> dbl_array;
    dbl_array.addElement(1.5);
    dbl_array.addElement(-2.25);
    dbl_array.addElement(4.0);
    std::cout << "double sum = " << dbl_array.sum()
              << ", max = " << dbl_array.max()
              << ", min = " << dbl_array.min() << std::endl;

    return 0;
}
