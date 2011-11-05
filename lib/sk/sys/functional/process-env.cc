/*  vim: sw=4:
 *  Copyright (c) 2011, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include <sk/sys/Process.h>
#include <sk/sys/AbstractProcessListener.h>
#include <sk/sys/ProcessConfigurator.h>

#include <iostream>

namespace {
    struct Listener : public sk::sys::AbstractProcessListener {
        void processConfiguring(sk::sys::ProcessConfigurator& configurator) {
            configurator.setEnvironment("ORACLE_HOME", "D:\\oracle\\ora92");
            configurator.setEnvironment("ZZZZZ", "D:\\oracle\\ora92");
        }
    };
}

int main(int argc, const char* const argv[])
{
    sk::sys::Process::setup();

    Listener listener;
    try { 
        sk::sys::Process process("./print-env");
        process.join();
    }
    catch(const sk::util::Exception& exception) {
        std::cerr << "E: " << exception.getMessage() << std::endl;
    }
}
