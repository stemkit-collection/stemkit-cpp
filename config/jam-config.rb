
require 'tsc/jam/config.rb'

class JamConfig < TSC::Jam::Config
  def options
    export_build_resource
    super
  end

  def config_path
    __FILE__
  end
end
