/*  vim: set sw=4:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <sk/cppunit/TestRunner.h>
#include <sk/cppunit/SourcePath.h>

#include <iostream>

int main(int argc, const char* argv[])
{
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
    sk::cppunit::TestRunner runner;

    if(argc == 2) {
        sk::cppunit::SourcePath::setBase(argv[1]);
    }
    runner.addTest(registry.makeTest());
    return !runner.run();
}
