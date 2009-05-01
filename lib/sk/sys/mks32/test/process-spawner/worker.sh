#!/bin/ksh

sleep 1

(( ceiling = ${RANDOM} ))
(( counter = 0 ))

while [ "${counter}" -le "${ceiling}" ]; do
  echo P${1}-$$: ${counter}
  (( counter += 1 ))
done
