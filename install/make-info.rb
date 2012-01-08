# Copyright (c) 2006, Gennady Bystritsky <bystr@mac.com>
#
# Distributed under the MIT Licence.
# This is free software. See 'LICENSE' for details.
# You must read and accept the license prior to use.

if defined? Installation::Generator
  class Generator < Installation::Generator
    def create(io)
      bindir = File.join(self.class.installation_tools, 'bin')
      [
        '#!/bin/sh',
        'exec ' + File.join(self.class.installation_tools, 'bin', 'tpm-info') + ' "${@}"'
      ]
    end
  end

  throw :generator, Generator
end
