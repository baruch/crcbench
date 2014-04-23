crcbench
========

Benchmarking CRC routines to find a fast one.

I've taken CRC routines from:
* crc-brumme: http://create.stephan-brumme.com/crc32/
* crc-intel: http://www.intel.ie/content/www/ie/en/intelligent-systems/crc-iscsi-polynomial-crc32-instruction-paper.html
* crc-sse42: https://github.com/Voxer/sse4_crc32/blob/master/src/crc32c.c

Results
-------

crc-intel is by far the fastest, it uses hand optimized assembly with hardware acceleration.
crc-sse42 is the second best, it also uses hardware acceleration.
crc-brumme 8-bytes is the third place.

Pending tests
-------------

Still need to test the code from crcutil: http://code.google.com/p/crcutil/
