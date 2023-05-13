// See specs for complete description of what you need to implement in this file.

// Don't forget documentation: a file header is required; every function and type that you
// define must have appropriate documentation

#include <iostream>
#include <exception>

namespace hlp2
{
    class division_by_zero : public std::exception
    {
    public:
        division_by_zero(int numerator) : num(numerator)
        { }
        const char* what() const noexcept override
        {
            std::ostringstream oss;
            oss << "division by zero: " << num << " / 0";
            return oss.str().c_str();
        }
    private:
        int num;
    };

    class invalid_input : public std::exception
    {
    public:
        const char* what() const noexcept override
        {
            return "Invalid input!";
        }
    };

    class stream_wrapper : public std::exception
    {
    public:
        std::istream& stream;
        int           n, d0, d1, d2, d3, d4;

        stream_wrapper(std::istream& s) : stream(s) 
        {
            if(!stream)
            {
                throw hlp2::invalid_input();
            }
        }

        stream_wrapper& operator>>(int& value)
        {
            stream >> value;
            return *this;
        }

        stream_wrapper& operator>>(stream_wrapper& sw)
        {
            sw.stream >> sw.n >> sw.d0 >> sw.d1 >> sw.d2 >> sw.d3 >> sw.d4;
            return sw;
        }
    };

    template <typename F>
    void test1(int n, int d0, F transformer)
    {
        int& result;
        F success = transformer(n, d0, result);
        if(success)
        {
            std::cout << "result: " << n << std::endl;
        }
    }

    template <typename F>
    void test2(int n, int d1, F transformer)
    {
        std::pair<bool, int> result = transformer(n, d1);
        std::cout << "result: " << n << std::endl;
    }

    template <typename F>
    void test3(int n, int d2, F transformer)
    {

    }

    template <typename F>
    void test4(int n, int d3, F transformer);

    template <typename F>
    void test5(int n, int d4, F transformer);
}