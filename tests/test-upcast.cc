#include <iostream>
#include <exception>

class Object {
    public:
        virtual ~Object() {}
        virtual Object* clone() const = 0;
};

class Sample : public virtual Object {
    public:
        Sample() {
            std::cerr << "Sample::Sample(), this=" << this << std::endl;
        }
        virtual ~Sample() {
            std::cerr << "Sample::~Sample(), this=" << this << std::endl;
        }
        Object* clone() const {
            return new Sample();
        }
};

int main(const int argc, const char* const argv[])
{
    Sample sample;

    try {
        Sample* s = dynamic_cast<Sample*>(sample.clone());
        std::cerr << "Upcasted... s=" << s << std::endl;
        delete s;
        std::cerr << "Disposed... s=" << s << std::endl;
    }
    catch(const std::exception& exception) {
        std::cerr << exception.what() << std::endl;
        return 2;
    }
    return 0;
}
