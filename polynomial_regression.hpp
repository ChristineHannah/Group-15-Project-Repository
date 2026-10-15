#ifndef EF3D12CA_40AA_4A35_AA4B_BB2FF5A91C30
#define EF3D12CA_40AA_4A35_AA4B_BB2FF5A91C30

#include <stdexcept>
#include <utility>

template <typename T>
class Vector
{
public:
    Vector(int size = 0)
        : sz(size), elem(size > 0 ? new T[size]() : nullptr)
    {
        if (size < 0)
            throw std::invalid_argument("Vector size cannot be negative.");
    }

    Vector(const Vector& other)
        : sz(other.sz), elem(sz > 0 ? new T[sz] : nullptr)
    {
        for (int i = 0; i < sz; ++i)
            elem[i] = other.elem[i];
    }

    ~Vector() { delete[] elem; }

    Vector& operator=(Vector other)
    {
        std::swap(sz, other.sz);
        std::swap(elem, other.elem);
        return *this;
    }

    int size() const { return sz; }
    T& get(int index) { return elem[index]; }
    const T& get(int index) const { return elem[index]; }
    void set(int index, const T& value) { elem[index] = value; }

private:
    int sz;
    T* elem;
};

Vector<Vector<double>> computeNormalEquations(const Vector<Vector<double>>& x);
Vector<double> fitOLS(const Vector<Vector<double>>& x, const Vector<double>& y);

#endif /* EF3D12CA_40AA_4A35_AA4B_BB2FF5A91C30 */
