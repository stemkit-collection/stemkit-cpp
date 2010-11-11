# vim: sw=2:

require 'tsc/jam/config.rb'

class JamConfig < TSC::Jam::Config
  def options
    export_build_resource
    super
  end

  def config_path
    __FILE__
  end

  def add_platform_parameter
    # Relying on stardard platform determination.
  end
end
