/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky (gennady.bystritsky@quest.com)
*/

#include <sk/util/Class.h>
#include <sk/util/String.h>
#include <sk/util/ArrayList.cxx>
#include <sk/util/Holder.cxx>

#include <sk/rt/Benchmark.h>
#include <sk/rt/Timer.h>

static const sk::util::String __className("sk::rt::Benchmark");

class sk::rt::Benchmark::Item : public virtual sk::util::Object {
  public:
    Item(const sk::rt::Scope& parent, const sk::util::String& title, sk::rt::Runnable* code)
      : _scope(parent.scope("Item")), _title(title), _codeHolder(code) {}

    void perform() {
      _scope.info(_title) << "START";
      try {
        sk::rt::Runnable& code = _codeHolder.get();

        _timer.start();
        code.run();
        _timer.stop();
      }
      catch(const std::exception& exception) {
        _timer.stop();
        _scope.error(_title) << exception.what();
      }
      _scope.info(_title) << "END: " << _timer.inspect();
    }

  private:
    sk::rt::Scope _scope;
    sk::util::Holder<sk::rt::Runnable> _codeHolder;
    sk::rt::Timer _timer;
    const sk::util::String _title;
};

sk::rt::Benchmark::
Benchmark(const sk::util::String& title)
  : _title(title), _scope(__className)
{
}

sk::rt::Benchmark::
~Benchmark()
{
}

const sk::util::Class
sk::rt::Benchmark::
getClass() const
{
  return sk::util::Class(__className);
}

void
sk::rt::Benchmark::
run()
{
  start();
}

void
sk::rt::Benchmark::
start()
{
  struct Performer : public virtual sk::util::Processor<Item> {
    void process(Item& item) const {
      item.perform();
    }
  };
  _scope.info(_title) << "START";
  _items.forEach(Performer());
  _scope.info(_title) << "END";
}

void
sk::rt::Benchmark::
add(const sk::util::String& name, sk::rt::Runnable* code)
{
  _items.add(new Item(_scope, name, code));
}
