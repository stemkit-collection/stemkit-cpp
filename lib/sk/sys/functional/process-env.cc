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

namespace {
    struct Listener : public sk::sys::AbstractProcessListener {
        void processConfiguring(sk::sys::ProcessConfigurator& configurator) {
            configurator.setEnvironment("ORACLE", "he-he-he");
        }
    };
}

int main(int argc, const char* const argv[])
{
    Listener listener;
    sk::sys::Process process(sk::util::Strings() + "ruby" + "-e" + "p *ENV", listener);
    process.join();
}
