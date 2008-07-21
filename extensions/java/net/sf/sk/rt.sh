#!/bin/ksh

case "${1}" in
  test | specs)
    return 0
  ;;
esac

JAM_BINDIR=`pwd`
cd "${JAM_SRCDIR}" && {
  export CLASSPATH="${JAM_BINDIR}"
  jruby -I "${JAM_SRCDIR}/../../.." -I ${JAM_BINDIR}/../../.. -r net/sf/sk/rt-java.rb ${@:--S jirb}
}
