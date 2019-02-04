/*  vim: sw=4:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <iostream>
#include <sk/rt/Environment.h>
#include <sk/util/Strings.h>

int main(int argc, const char* const argv[])
{
    sk::util::Strings args;
    for(int index=1; index < argc; ++index) {
        args << sk::util::String(argv[index]).toLowerCase();
    }

    struct Printer : public virtual sk::util::BinaryProcessor<const sk::util::String, const sk::util::String> {
        Printer(const sk::util::Strings& args)
            : _args(args) {}

        void process(const sk::util::String& key, const sk::util::String& value) const {
            if(_args.isEmpty() == true || _args.contains(key.toLowerCase()) == true) {
                std::cout << key.inspect() << "=" << value.inspect() << std::endl;
            }
        }
        const sk::util::Strings& _args;
    };
    sk::rt::Environment().forEach(Printer(args));
    return 0;
}
