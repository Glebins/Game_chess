#include <iostream>

#include "Tools/Figures.h"

template <typename T>
concept str_printable = std::is_convertible_v<T, std::string>;

template <typename T>
concept ptr_printable = std::is_pointer<T>::value && !std::is_convertible_v<T, std::string>;

template <typename T>
concept container_printable = requires (T c) {
    c.cbegin();
    c.cend();
    typename T::value_type;
};

template <typename T>
class Printer {
    std::ostream& out;

public:
    Printer(std::ostream& out) : out(out) { };
    void operator() (const T& val) {
        out << val << std::endl;
    }
};

template <ptr_printable T>
class Printer<T> {
    Printer<std::remove_pointer_t<T>> val_printer;

public:
    Printer(std::ostream& out) : val_printer(out) { };
    void operator() (const T& val) {
        val_printer(*val);
    }
};

template <container_printable T>
class Printer<T> {
    Printer<typename T::value_type> val_printer;

public:
    Printer(std::ostream& out) : val_printer(out) { };
    void operator() (const T& val) {
        for (const auto &i : val)
            val_printer(i);
    }
};

template <str_printable T>
class Printer<T> {
    std::ostream &out;

public:
    Printer(std::ostream& out) : out(out) {}
    void operator() (const T& val) {
        out << std::string(val) << std::endl;
    }
};

int main()
{
    int x = 0xA;
    std::cout << x;

    Pawn p;

    std::cout << std::endl << p.get_name_of_figure() << std::endl;

    return 0;
}
