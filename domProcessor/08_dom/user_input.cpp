#include <iostream>
#include <string>
#include <cctype>

class TextInput
{
public:
    virtual void add(char c)
    {
       value_ = value_ + c;

    }
    virtual std::string getValue() { return value_; }
private:
   std::string value_;
};


class NumericInput : public TextInput
{
public:
    virtual void add(char c)
    {
     if (isdigit(c)) {
       value_ = value_ + c;
     }
    }
    virtual std::string getValue() { return value_; }

private:
 std::string value_;
};

int main()
{
    TextInput* input = new NumericInput();
    input->add('1');
    input->add('a');
    input->add('0');
    std::cout << input->getValue()<<std::endl;
}
