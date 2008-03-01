/*  Copyright (c) 2007, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#include "PipeProcessLeftoverTest.h"
#include <logger/PipeDestination.h>
#include <logger/TrashDestination.h>
#include <sk/util/Holder.cxx>
#include <signal.h>

CPPUNIT_TEST_SUITE_REGISTRATION(sk::rt::logger::test::PipeProcessLeftoverTest);

sk::rt::logger::test::PipeProcessLeftoverTest::
PipeProcessLeftoverTest()
{
}

sk::rt::logger::test::PipeProcessLeftoverTest::
~PipeProcessLeftoverTest()
{
}

void
sk::rt::logger::test::PipeProcessLeftoverTest::
setUp()
{
}

void
sk::rt::logger::test::PipeProcessLeftoverTest::
tearDown()
{
}

namespace {
  struct ProbeDestination : public virtual sk::rt::logger::Destination {
    ProbeDestination(int readfd, int writefd)
      : _readfd(readfd), _writefd(writefd) {}

    void dispatch(const char* buffer, int size) {
      makeReady();
    }

    void makeReady() {
      if(_readfd < 0) {
        return;
      }
      close(1);
      dup(_readfd);

      ::close(_readfd);
      ::close(_writefd);

      _readfd = -1;
      _writefd = -1;
    }

    ProbeDestination* clone() const {
      return new ProbeDestination(*this);
    }
    int _readfd;
    int _writefd;
  };
}

void
sk::rt::logger::test::PipeProcessLeftoverTest::
testNoLeftovers()
{
  signal(SIGPIPE, SIG_IGN);

  int descriptors[2];
  CPPUNIT_ASSERT_EQUAL(0, pipe(descriptors));

  ProbeDestination probe(descriptors[0], descriptors[1]);
  sk::util::Holder<logger::PipeDestination> holder(new logger::PipeDestination(probe));

  holder.get().makeReady();
  ::close(descriptors[0]);

  CPPUNIT_ASSERT_EQUAL(3, (int)::write(descriptors[1], "aaa", 3));

  logger::TrashDestination trash;
  logger::PipeDestination destination(trash);
  destination.makeReady();
  holder.clear();

  CPPUNIT_ASSERT_EQUAL(-1, (int)::write(descriptors[1], "aaa", 3));
}
