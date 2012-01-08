#include <sk/util/ArrayList.cxx>
#include <sk/util/LinkedList.cxx>
#include <sk/util/String.h>

void print_list(const sk::util::List<sk::util::String>& list)
{
  std::cerr << list.inspect() << std::endl;
}

int main(int argc, const char* const argv[])
{
  sk::util::String s("  abcdefg");

  s.inspect(); // "abcdefg"
  s.trim().startsWith("abc"); // true
  s.toLowerCase().endsWith("efg"); // true

  sk::util::ArrayList<sk::util::String> array_list;
  array_list.add(s);
  array_list.add(new sk::util::String("zzz"));

  sk::util::LinkedList<sk::util::String> linked_list;
  linked_list.add(s);

  print_list(array_list);
  print_list(linked_list);
}
