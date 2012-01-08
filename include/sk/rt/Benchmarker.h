/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#ifndef _SK_RT_BENCHMARKER_H_
#define _SK_RT_BENCHMARKER_H_

#include <sk/util/Object.h>
#include <sk/util/String.h>
#include <sk/util/ArrayList.hxx>
#include <sk/rt/Runnable.h>
#include <sk/rt/Benchmarkable.h>
#include <sk/rt/bm/Runner.h>
#include <sk/rt/Scope.h>

namespace sk {
  namespace rt {
    class Benchmarker
      : public virtual sk::rt::bm::Runner
    {
      typedef void (function_t)(void);

      public:
        Benchmarker(const sk::util::String& title);
        virtual ~Benchmarker();

        void add(const sk::util::String& title, sk::rt::Benchmarkable* code);
        void add(const sk::util::String& title, sk::rt::Runnable* code);
        void add(const sk::util::String& title, function_t* code);
        void add(sk::rt::bm::Runner* code);
        void add(sk::rt::bm::Runner& code);

        // sk::rt::Benchmarkerable implementation
        void init();
        void start() throw();
        void report(int indent, std::ostream& stream) const;

        // sk::util::Object re-implementation.
        const sk::util::Class getClass() const;

      protected:
        virtual void setUp();

      private:
        Benchmarker(const Benchmarker& other);
        Benchmarker& operator = (const Benchmarker& other);

        sk::rt::Scope _scope;
        const sk::util::String _title;
        sk::util::ArrayList<sk::rt::bm::Runner> _runners;
        int _maxTitleSize;
    };
  }
}

#endif /* _SK_RT_BENCHMARKER_H_ */
