#include "yaml.h"
#include <fstream>
#include <iostream>

int main(int argc, char **argv)
{
	std::ifstream fin;
	if(argc > 1)
		fin.open(argv[1]);

	std::istream& input = (argc > 1 ? fin : std::cin);
	try {
		SK_YAML::Parser parser(input);
		SK_YAML::Node doc;
		while(parser.GetNextDocument(doc)) {
			SK_YAML::Emitter emitter;
			emitter << doc;
			std::cout << emitter.c_str() << "\n";
		}
	} catch(const SK_YAML::Exception& e) {
		std::cerr << e.what() << "\n";
	}
	return 0;
}
