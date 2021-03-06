/*  vim: set sw=2:
 *  Copyright (c) 2009, Gennady Bystritsky <bystr@mac.com>
 *
 *  Distributed under the MIT Licence.
 *  This is free software. See 'LICENSE' for details.
 *  You must read and accept the license prior to use.
 *
 *  Author: Gennady Bystritsky
*/

#ifndef _SK_C_HANDLE_H_
#define _SK_C_HANDLE_H_

struct sk_c_handle;

#if defined(__cplusplus)
extern "C" {
#endif

int sk_c_handle_isError(const struct sk_c_handle* handle);

const char* sk_c_handle_errorType(const struct sk_c_handle* handle, char* buffer, int size);
const char* sk_c_handle_errorMessage(const struct sk_c_handle* handle, char* buffer, int size);

#if defined(__cplusplus)
}

#include <sk/util/Object.h>
#include <sk/util/String.h>
#include <vector>

class sk_c_handle
{
  public:
    struct runnable : public virtual sk::util::Object {
      virtual void run() const = 0;
    };
    sk_c_handle();
    virtual ~sk_c_handle();

    bool isError() const;

    const sk::util::String& errorType() const;
    const sk::util::String& errorMessage() const;

    void execute(const sk_c_handle::runnable& runnable) const;

    static char* copy(const std::string& s, char* buffer, int size);
    static char* copy(const std::vector<char>& data, char* buffer, int size);
    static void ensure_proper(const struct sk_c_handle* handle);
    static void ensure_not_null(const struct sk_c_handle* handle);

  protected:
    virtual bool hasObject() const = 0;

  private:
    bool isValid(const struct sk_c_handle* handle) const;
    static void ensure_valid(const struct sk_c_handle* handle);

    mutable bool _error;
    mutable sk::util::String _errorType;
    mutable sk::util::String _errorMessage;
    sk_c_handle* _self;
    char _label[10];
};

#endif

#endif /* _SK_C_HANDLE_H_ */
