/*  Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
 *  
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
*/

#ifndef _SK_IO_FILESTREAMCOUPLER_
#define _SK_IO_FILESTREAMCOUPLER_

#include <sk/io/FileStreamCoupler.hxx>
#include <sk/util/Holder.cxx>

template<typename S>
sk::io::FileStreamCoupler<S>::
FileStreamCoupler(std::auto_ptr<sk::io::File> file_auto_ptr)
  : S(file_auto_ptr.get()->getFileDescriptor().getFileNumber()), _fileHolder(file_auto_ptr.release())
{
}

template<typename S>
sk::io::File&
sk::io::FileStreamCoupler<S>::
getFile() const
{
  return _fileHolder.getMutable();
}

#endif /* _SK_IO_FILESTREAMCOUPLER_ */
