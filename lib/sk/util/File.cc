/*  Copyright (c) 2008, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include <sk/util/StringArray.h>
#include <sk/util/File.h>
#include <unistd.h>

#include <sk/util/MissingResourceException.h>
#include <sk/util/IllegalStateException.h>

sk::util::File::
File(const sk::util::String& name) 
  : _name(name), _file(_name.getChars())
{
   if(_file.good() == false) {
     throw sk::util::MissingResourceException(name);
   }
}

const sk::util::String 
sk::util::File::
getLine() 
{
  sk::util::String depot;

  if(std::getline(_file, depot).good() == false) {
    throw sk::util::IllegalStateException("getLine():EOF");
  }
  return depot;
}

const sk::util::String 
sk::util::File::
getLines(int number) 
{
  sk::util::StringArray depot;
  while(number-- > 0) {
    depot << getLine();
  }
  return depot.inspect();
}

const sk::util::String 
sk::util::File::
getLines() 
{
  sk::util::StringArray depot;

  try {
    while(true) {
      depot << getLine();
    }
  }
  catch(const sk::util::IllegalStateException& exception) {
    return depot.join('\n');
  }
}

bool 
sk::util::File::
exists(const sk::util::String& name) 
{
  return std::ifstream(name.getChars()).good();
}

void
sk::util::File::
create(const sk::util::String& path)
{
  std::ofstream file(path.getChars(), std::ios::app);
  if(file.good() == false) {
    throw sk::util::MissingResourceException(path);
  }
}
