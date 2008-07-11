#!/bin/ksh

case "${1}" in
  test | specs)
    return 0
  ;;
esac

irb -I ${JAM_SRCDIR}/.. -I .. -r sk/rt/scope.rb
