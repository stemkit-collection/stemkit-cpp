/*  Copyright (c) 2008, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *  
 *  Author: Gennady Bystritsky
*/

#include "CyclerFactory.h"
#include "PointingCycler.h"
#include "StableHeadCycler.h"

#include <sk/util/Holder.cxx>

sk::rt::logger::CyclerFactory::
CyclerFactory()
{
}

sk::util::Holder<sk::rt::logger::Cycler>::Sharing
sk::rt::logger::CyclerFactory::
create(const sk::util::Pathname& pathname, const sk::util::String& policy)
{
  if(policy.equals("pointing") == true) {
    return sk::util::Holder<Cycler>::Sharing(new PointingCycler(pathname));
  }
  else {
    return sk::util::Holder<Cycler>::Sharing(new StableHeadCycler(pathname));
  }
}
