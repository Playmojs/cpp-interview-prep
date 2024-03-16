#include <memory>

template <class T>
class myVector
{
    private:
    size_t _alloc;
    size_t _size;
    std::unique_ptr<T> _vec;
    public:
    myVector()
    {
        _vec = new T[16];
        _size = 0;
        _alloc = 16;
    }
    T operator[](size_t index){}




    void increment_alloc()
    {
        _alloc = 2 * _alloc;
        std::unique_ptr<T> vec = new T[_alloc];
        for(size_t i = 0; i < _size; i++)
        {
            vec[i] = _vec[i];
        }
        delete (_vec);
        _vec = vec;
    }
    void append(T value)
    {
        if(_size == _alloc){increment_alloc();}
        _vec[_size] = value;
        _size ++;
    }
};



int main() {

  return 0;
}
