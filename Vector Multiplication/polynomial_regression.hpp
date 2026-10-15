#ifndef EF3D12CA_40AA_4A35_AA4B_BB2FF5A91C30
#define EF3D12CA_40AA_4A35_AA4B_BB2FF5A91C30

#include <stdexcept>
#include <utility>

namespace ols {

template <typename T>
class Vector
{
public:
    explicit Vector(int size = 0)
        : sz(size), elem(nullptr)
    {
        if (size < 0)
            throw std::invalid_argument("Vector size cannot be negative.");
        if (size > 0)
            elem = new T[size]();
    }

    Vector(const Vector& other)
        : sz(0), elem(nullptr)
    {
        T* tmp = other.sz > 0 ? new T[other.sz] : nullptr;
        try {
            for (int i = 0; i < other.sz; ++i)
                tmp[i] = other.elem[i];
        } catch (...) {
            delete[] tmp;
            throw;
        }
        elem = tmp;
        sz = other.sz;
    }

    Vector(Vector&& other) noexcept
        : sz(std::exchange(other.sz, 0)),
          elem(std::exchange(other.elem, nullptr)) {}

    ~Vector() { delete[] elem; }

    Vector& operator=(Vector other) noexcept
    {
        swap(other);
        return *this;
    }

    void swap(Vector& other) noexcept
    {
        std::swap(sz, other.sz);
        std::swap(elem, other.elem);
    }

    friend void swap(Vector& a, Vector& b) noexcept { a.swap(b); }

    int size() const { return sz; }
    T& get(int index) { return elem[index]; }
    const T& get(int index) const { return elem[index]; }
    void set(int index, const T& value) { elem[index] = value; }

private:
    int sz;
    T* elem;
};

Vector<Vector<double>> transpose(const Vector<Vector<double>>& a);
Vector<Vector<double>> multiply(const Vector<Vector<double>>& a,
   const Vector<Vector<double>>& b);
Vector<double>         multiply(const Vector<Vector<double>>& a,
       const Vector<double>& v);
Vector<Vector<double>> inverse(const Vector<Vector<double>>& a);
Vector<Vector<double>> computeNormalEquations(const Vector<Vector<double>>& x);
Vector<double>         computeXtY(const Vector<Vector<double>>& x,
 const Vector<double>& y);
Vector<double>         fitOLS(const Vector<Vector<double>>& x,
 const Vector<double>& y);
Vector<Vector<double>> makeDesignMatrix(const Vector<double>& t, int degree);
Vector<double>         fitPolynomial(const Vector<double>& t,
const Vector<double>& y, int degree);
double                 predict(const Vector<double>& beta, double t);

} // namespace ols

#endif /* EF3D12CA_40AA_4A35_AA4B_BB2FF5A91C30 */