/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_RT_BM_EXECUTOR_H_
#define _SK_RT_BM_EXECUTOR_H_

#include <sk/util/Holder.hxx>
#include <sk/rt/Scope.h>
#include <sk/rt/bm/Runner.h>
#include <sk/rt/Benchmarkable.h>

#include <vector>

namespace sk {
  namespace rt {
    namespace bm {
      class Executor
        : public virtual sk::rt::bm::Runner
      {
        public:
          Executor(const int& maxTitleSize, const sk::util::String& title, sk::rt::Benchmarkable* code);
          virtual ~Executor();

          // sk::rt::bt::Runner implementation.
          void init();
          void start() throw();
          void report(int indent, std::ostream& stream) const;

          // sk::util::Object re-implementation.
          const sk::util::Class getClass() const;

        private:
          Executor(const Executor& other);
          Executor& operator = (const Executor& other);

          sk::rt::Scope _scope;
          sk::util::Holder<sk::rt::Benchmarkable> _codeHolder;
          const sk::util::String _title;
          const int& _maxTitleSize;
          std::vector<uint64_t> _results;
      };
    }
  }
}

#endif /* _SK_RT_BM_EXECUTOR_H_ */
