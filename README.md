crcbench
========

Benchmarking CRC routines to find a fast one.

I've taken CRC routines from:
* crc-brumme: http://create.stephan-brumme.com/crc32/
* crc-intel: http://www.intel.ie/content/www/ie/en/intelligent-systems/crc-iscsi-polynomial-crc32-instruction-paper.html
* crc-sse42: https://github.com/Voxer/sse4_crc32/blob/master/src/crc32c.c
* crc-mark-adler: http://stackoverflow.com/questions/17645167/implementing-sse-4-2s-crc32c-in-software?answertab=active#tab-top

Results
-------

Raw Results:
* [Intel Core i3 2330M @ 2.20GHz](./log.i3-2330M-2.20GHz.txt)

crc-mark-adler-hw is faster on longer buffers and slightly slower than crc-intel on smaller buffers. They are pretty much tied.

crc-intel I'd consider second place.

crc-sse42 is third place.

crc-brumme 8-bytes is the fourth place, but first place among the software
implementations. The 4 byte version is better on an AMD Thurion system though.

Pending tests
-------------

Still need to test the code from crcutil: http://code.google.com/p/crcutil/

Resources
---------

* [Software and Digital Systems Program - Data Integrity Techniques](http://users.ece.cmu.edu/~koopman/pubs/01oct2013_koopman_faa_final_presentation.pdf) (PDF) -- Discusses different CRC and checksum qualities in a quantitative form [source blog](http://checksumcrc.blogspot.co.il/)
