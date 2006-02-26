
require 'etc'

class JamConfig
  def options
    [ 
      '-s', "JAMCONFIG_PRODUCT_NAME=stem-cpp", 
      '-s', "JAMCONFIG_PRODUCT_RELEASE=1.0", 
      '-s', "JAMCONFIG_PRODUCT_BUILD=0", 
      '-s', "JAMCONFIG_PRODUCT_PLATFORM=macos-ppc",

      '-s', "JAMCONFIG_LIBRARY_PREFIX=", 
      '-s', "JAMCONFIG_LIBRARY_MAJOR=1", 

      '-s', "JAMCONFIG_USER=#{Etc.getpwuid.name}" 
    ]
  end
end
