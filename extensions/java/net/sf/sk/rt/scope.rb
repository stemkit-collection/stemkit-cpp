# vim: set sw=2:
=begin
  Copyright (c) 2008, Gennady Bystritsky <bystr@mac.com>
  
  Distributed under the MIT Licence.
  This is free software. See 'LICENSE' for details.
  You must read and accept the license prior to use.
=end

class Java::net::sf::sk::rt::Scope
  private :logger
  alias_method :property, :getProperty
  alias_method :property?, :hasProperty

  def fatal(*args, &block)
    error(*args, &block)
  end

  def warn(*args, &block)
    warning(*args, &block)
  end

  def method_missing(name, *args, &block)
    if adaptor.respond_to?(name)
      adaptor.warning "#{name}: Unsupported invocation with a block" if block
      
      make_singleton_method(name) { |*args|
        catch :break do
          foreach_line_in args do |_line|
            adaptor.send(name, _line) or throw :break, false
          end

          true
        end
      }
      send(name, *args) or make_singleton_method(name) { |*args| 
      }
    else
      adaptor.error "#{name}: #{args.inspect} (block=#{block.inspect})"
    end
  end

  private
  #######

  def adaptor
    @adaptor ||= logger
  end

  def foreach_line_in(*args)
    args.flatten.each do |_item|
      _item.to_s.each do |_line|
        yield _line.chomp
      end
    end
  end

  def singleton_class
    class << self
      self
    end
  end

  def make_singleton_method(*args, &block)
    singleton_class.send :define_method, *args, &block
  end
  
end

