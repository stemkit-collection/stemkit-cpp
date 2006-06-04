
require 'etc'
require 'tsc/platform.rb'

class JamConfig
  def options
    [ 
      '-s', "JAMCONFIG_PRODUCT_NAME=stemkit-cpp", 
      '-s', "JAMCONFIG_PRODUCT_RELEASE=0.0.1", 
      '-s', "JAMCONFIG_PRODUCT_BUILD=0", 
      '-s', "JAMCONFIG_PRODUCT_PLATFORM=#{TSC::Platform.current.name}",
      '-s', "JAMCONFIG_LIBRARY_PREFIX=", 
      '-s', "JAMCONFIG_LIBRARY_MAJOR=1", 

      '-s', "JAMCONFIG_USER=#{Etc.getpwuid.name}" 
    ]
  end
end
