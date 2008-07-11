
Spec::Runner.configure do |config|
  config.mock_with :mocha
end

module SK
  module Rt
    class Scope
      def initialize(name)
        @name = name
      end

      def logger
      end
    end
  end
end

$" << 'sk/rt'
require 'sk/rt/scope.rb'

describe SK::Rt::Scope do
  before :each do
    @logger = mock('logger')
    @scope = SK::Rt::Scope.new('abc')
    @scope.expects(:logger).returns @logger
  end

  describe "when unknown log method used" do
    it "should call error with an appropriate message" do
      @logger.expects(:error).with { |_message| _message =~ %r{^info:} }
      @scope.info "abc"
    end
  end

  describe "when valid log message used" do
    describe "for outputting log level" do
      it "should not have a method then create and call several times" do
        @scope.should_not respond_to(:info)
        @logger.expects(:info).with("abc").returns true

        @scope.info "abc"
        @scope.should respond_to(:info)

        @logger.expects(:info).with("zzz").returns true
        @logger.expects(:info).with("uuu").returns true

        @scope.info "zzz"
        @scope.info "uuu"
      end
      
      it "should output whole multi line message" do
        @logger.expects(:info).with("aaa").returns true
        @logger.expects(:info).with("bbb").returns true
        @logger.expects(:info).with("ccc").returns true
        
        @scope.info "aaa\nbbb\nccc\n"
      end

      it "should output all arguments" do
        @logger.expects(:info).with("aaa").returns true
        @logger.expects(:info).with("bbb").returns true
        @logger.expects(:info).with("ccc").returns true
        
        @scope.info "aaa", "bbb", "ccc\n"
      end
    end

    describe "for non-outputting log level" do
      it "should not have a method then create empty" do
        @scope.should_not respond_to(:info)
        @logger.expects(:info).with("abc").returns false

        @scope.info "abc"
        @scope.should respond_to(:info)

        @logger.expects(:info).with("zzz").never
        @logger.expects(:info).with("uuu").never

        @scope.info "zzz"
        @scope.info "uuu"
      end

      it "should output only first line of a multi line message and nothing afterwards" do
        @logger.expects(:info).with("aaa").returns false
        @logger.expects(:info).with("bbb").never
        @logger.expects(:info).with("ccc").never
        @logger.expects(:info).with("uuu").never
        @logger.expects(:info).with("yyy").never
        
        @scope.info "aaa\nbbb\nccc\n"
        @scope.info "uuu", "yyy"
      end
    end
  end
end
