#include <sk/rt/Scope.h>
#include <sk/rt/config/InlineLocator.h>
#include <sk/rt/config/CwdUprootLocator.h>

int main(int argc, const char* const argv[])
{
  sk::rt::Scope::controller().loadXmlConfig(
    sk::rt::config::InlineLocator(
      "<scope>\n"
      "  <log destination='std::cerr' level='notice' show-thread='true' show-time='true'>\n"
      "    <file location='/tmp/demo.log' size='10M' chunks='3' />\n"
      "  </log>\n"
      "  <scope name='child'>\n"
      "    <property name='item' value='table' />\n"
      "  </scope>\n"
      "</scope>\n",
      sk::rt::config::CwdUprootLocator("config/spo.conf")
    )
  );
  sk::rt::Scope scope("main");
  sk::rt::Scope child = scope.scope("child");

  scope.info() << "Top property: " << scope.getProperty("item", "none").inspect();
  child.notice() << "Child property: " << child.getProperty("item", "none").inspect();
  scope.detail() << "No output";
}
