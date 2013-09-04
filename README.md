jpegio
======

This code is a wrapper of libjpeg-turbo for opencv image IO
http://www.libjpeg-turbo.org/
The used version of libjpeg-turbo is 1.3.0 for visual studio 2012(64 bit).

Exsample of test results on core i5-2450M 2.5GHz, Windows 7 64 bit with Visual Studio 2012 are as follows;

speed test
encode:
opencv:10.7853ms
jpegturbo(fastest,huffman):3.24866ms
jpegturbo(slowest,huffman):3.51242ms
jpegturbo(fastest,ac):9.79507ms
jpegturbo(slowest,ac):10.5221ms

RD test
quality: 100
opencv              271887byte, 44.4211dB
jpeg turbo(huffman) 265458byte, 44.4222dB
jpeg turbo(ac)      241395byte, 44.4222dB

quality: 90
opencv              77329byte, 39.6411dB
jpeg turbo(huffman) 76487byte, 39.6344dB
jpeg turbo(ac)      70669byte, 39.6344dB

quality: 80
opencv              48757byte, 37.7857dB
jpeg turbo(huffman) 48418byte, 37.7861dB
jpeg turbo(ac)      45036byte, 37.7861dB

quality: 70
opencv              37812byte, 36.6299dB
jpeg turbo(huffman) 37615byte, 36.6282dB
jpeg turbo(ac)      34477byte, 36.6282dB

quality: 60
opencv              31631byte, 35.7316dB
jpeg turbo(huffman) 31516byte, 35.7293dB
jpeg turbo(ac)      28390byte, 35.7293dB

quality: 50
opencv              27754byte, 35.0753dB
jpeg turbo(huffman) 27683byte, 35.0745dB
jpeg turbo(ac)      24486byte, 35.0745dB

quality: 40
opencv              24223byte, 34.3647dB
jpeg turbo(huffman) 24158byte, 34.3614dB
jpeg turbo(ac)      20858byte, 34.3614dB
