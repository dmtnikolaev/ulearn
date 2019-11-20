#include <iostream>
#include <climits>
#include <string>
#include <sstream>

/*
Задание: 
1.  Вводится либо short int, либо float.
2.  Показать внутреннее строение в двоичной системе
3.  Произвести преобразование: инвертировать все биты кроме n введенных по
    индексу
*/

// unsigned int -- слишком длинно
using uint = unsigned int;

// Проверяем размер unsigned int.
static_assert(std::numeric_limits<uint>::digits == 32);

// Режимы работы программы
//
enum class AppMode {
    USE_SHORT_INT,
    USE_FLOAT,
    EXIT,
};

// Поддерживаемые программой типы.
//
enum class SupportedType {
    SHORT_INT,
    FLOAT,
};

// Базовый класс для работы с внутренним представлением числа.
//
class BinaryView {
    public:
        BinaryView(uint value) : bin_val(value) {

        }

        size_t GetBinValue() {
            return this->bin_val;
        }

        // Не делаем перегрузку оператора, т.к. код тогда раздуется еще сильнее.
        void XorMutable(unsigned int mask) {
            this->bin_val ^= mask;
        }

        virtual std::string ToString() = 0;
        virtual int GetBitCount() = 0;

        virtual ~BinaryView() {

        }

    protected:
        int bin_val; // И short int, и float вмещаются.
};

// Класс для работы с бинарным представлением short int.
//
class ShortIntBinaryView : public BinaryView {
    public:
        ShortIntBinaryView(short int s) : BinaryView(static_cast<uint>(s)) {

        }

        short int ToShortInt() {
            return static_cast<short int>(this->bin_val);
        }

        std::string ToString() override {
            // Не забываем о ' ' и '\0'.
            constexpr auto symbol_count = ShortIntBinaryView::BIT_COUNT + 1 + 1; 
            char repr[symbol_count];

            repr[symbol_count-1] = '\0';
            auto i = symbol_count-2;

            auto bin_val = this->bin_val;
            while (i >= 0) {
                if (i == 1) {
                    repr[i] = ' ';
                }
                else {
                    repr[i] = '0' + (bin_val & 0x1);
                    bin_val >>= 1;
                }
                i--;
            }
            return std::string(repr);
        }

        int GetBitCount() override {
            return  this->BIT_COUNT;
        }

    private:
        static constexpr int BIT_COUNT = CHAR_BIT*sizeof(short);
};

// Класс для работы с бинарным представлением float.
//
class FloatBinaryView : public BinaryView {
    public:
        FloatBinaryView(float f) : BinaryView(*reinterpret_cast<uint*>(&f)) {

        }

        float ToFloat() {
            return *reinterpret_cast<float*>(&this->bin_val);
        }

        std::string ToString() override {
            // Не забываем о двух ' ' и '\0'.
            constexpr auto symbol_count = FloatBinaryView::BIT_COUNT + 2 + 1;
            char repr[symbol_count];

            repr[symbol_count-1] = '\0';
            auto i = symbol_count-2;

            auto bin_val = this->bin_val;
            while (i >= 0) {
                if (i == 1 || i == 10) {
                    repr[i] = ' ';
                }
                else {
                    repr[i] = '0' + (bin_val & 0x1);
                    bin_val >>= 1;
                }
                i--;
            }
            return std::string(repr);
        }

        int GetBitCount() override {
            return this->BIT_COUNT;
        }

    private:
        static constexpr int BIT_COUNT = sizeof(float)*CHAR_BIT;
};

// Чтение переменной типа T из stdin и провека ее значение
//
template<typename T, typename Predicate>
T ReadInputChecked(std::string_view prompt, Predicate pred) {
    T a;
    std::istringstream iss;

    do {
        std::cout << prompt;

        std::string s;
        std::getline(std::cin, s);
        iss = std::istringstream(s);
        if (iss.rdbuf()->in_avail() == 0) {
            continue;
        }

        iss >> a;
    } while (!iss.eof() || !pred(a));

    return a;
}

// Чтение значения из stdin в виде удобном для дальнейшей работы.
//
BinaryView* ReadBinaryView(SupportedType type) {
    auto prompt = "Enter value: ";
    auto always_true_pred = [](auto a) { return true; };

    switch (type)
    {
        case SupportedType::SHORT_INT: {
                auto shrt = ReadInputChecked<short int>(prompt, always_true_pred);
                return new ShortIntBinaryView(shrt);
            }

        case SupportedType::FLOAT: {
                auto flt = ReadInputChecked<float>(prompt, always_true_pred);
                return new FloatBinaryView(flt);
            }

        default:
            return nullptr;
    }
}

// Определение режима работы программы.
//
AppMode ReadMode() {
    std::cout << "Choose mode:" << std::endl
              << "1 - Use short int" << std::endl
              << "2 - Use float" << std::endl
              << "3 - Exit" << std::endl;

    auto i = ReadInputChecked<int>("[1/2/3]: ",
        [](int a) {
            return a == 1 || a == 2 || a == 3;
        });

    return static_cast<AppMode>(i - 1);
}

// Чтение количества позиций установленных битов в маске, которые будут
// вводиться в дальнейшем.
//
int ReadSetBitsCountInMask(int max_bit_count) {
    auto prompt =
        "Enter bit count [0, " +
        std::to_string(max_bit_count) +
        "]: ";
    auto checker =
        [max_bit_count](int b) { return b >= 0 && b <= max_bit_count; };

    return ReadInputChecked<int>(prompt, checker);
}

// Чтение одной позиции установленных битов в маске.
//
int ReadSetBitIndex(int index_of_index, int max_bit_count) {
    auto prompt = std::to_string(index_of_index) + ": ";
    auto checker =
        [max_bit_count](int b) { return b >= 0 && b < max_bit_count; };

    return ReadInputChecked<int>(prompt, checker);
}

// Чтение маски (используется в дальнейшем для "частичного" инвертирования).
//
uint ReadMask(int max_bit_count) {
    uint mask = 0;

    auto bit_count = ReadSetBitsCountInMask(max_bit_count);
    if (bit_count == 0) {
        return ~mask;
    }

    std::cout << "Enter bit indexes ([0, " << max_bit_count-1 << "]), "
                 "starts with high (from right to left):"
              << std::endl;

    for (auto i = 1; i <= bit_count; i++) {
        int bit_i_mask = 0;
        do {
            auto bit_i = ReadSetBitIndex(i, max_bit_count);
            bit_i_mask = 1 << (max_bit_count - bit_i - 1); 
        } while (mask & bit_i_mask);

        mask |= bit_i_mask;
    }

    return ~mask;
}

// Вывод значения в формате, определенном типом.
//
void PrintBinaryViewValue(BinaryView *bin_view, SupportedType type) {
    switch (type)
    {
        case SupportedType::SHORT_INT: {
            auto shrt_view = static_cast<ShortIntBinaryView*>(bin_view);
            std::cout << shrt_view->ToShortInt() << std::endl;
            break;
        }

        case SupportedType::FLOAT: {
            auto flt_view = static_cast<FloatBinaryView*>(bin_view);
            std::cout << flt_view->ToFloat() << std::endl;
            break;
        }
        
        default:
            break;
    }
}

// Вывод внутреннего представления значения.
//
void PrintBinaryView(BinaryView* bin_view) {
    auto bin_str = bin_view->ToString();
    std::cout << bin_str << std::endl;
}

int main() {
    while (true) {
        auto mode = ReadMode();
        SupportedType type = SupportedType::SHORT_INT;
        switch (mode) {
            case AppMode::EXIT:
                return 0;
            case AppMode::USE_SHORT_INT:
                type = SupportedType::SHORT_INT;
                break;
            case AppMode::USE_FLOAT:
                type = SupportedType::FLOAT;
                break;
        }
        auto bin_view = ReadBinaryView(type);

        std::cout << "Value binary representation: ";
        PrintBinaryView(bin_view);

        auto mask = ReadMask(bin_view->GetBitCount());
        bin_view->XorMutable(mask);

        std::cout << "Result: ";
        PrintBinaryViewValue(bin_view, type);
        std::cout << "Result binary representation: ";
        PrintBinaryView(bin_view);

        delete bin_view;
    }
}
