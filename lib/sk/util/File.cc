/*  Copyright (c) 2008, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

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
