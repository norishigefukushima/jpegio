jpegio
======

This code is a wrapper of libjpeg-turbo (http://www.libjpeg-turbo.org/) for opencv image IO
The used version of libjpeg-turbo is 2.0 for visual studio 2015 (64 bit) with AVX.
The used version of OpenCV is 3.3.1 for visual studio 2015 (64 bit).

If your CPU does not support AVX, please use libjpeg-turbo ver. 1.3 to copy the folder of jpegturbo1.3.
Default is jpegturbo2.0

Example of test results on core i7-6700K 4.0 GHz, Windows 10 64 bit with Visual Studio 2015 are as follows;

(Result of currect lib (ver. 2.0))
speed test
encode:
opencv:8.97745ms
jpegturbo(fastest,huffman):1.83012ms
jpegturbo(slowest,huffman):1.98872ms
jpegturbo(fastest,ac):9.57734ms
jpegturbo(slowest,ac):9.60081ms

decode:
opencv:4.33225ms
jpegturbo(fastest,huffman):1.70972ms
jpegturbo(slowest,huffman):1.69874ms
jpegturbo(fastest,ac):10.337ms
jpegturbo(slowest,ac):10.2784ms

(Result of old lib (ver. 1.3.0))
speed test
encode:
opencv:9.09152ms
jpegturbo(fastest,huffman):2.4142ms
jpegturbo(slowest,huffman):2.58792ms
jpegturbo(fastest,ac):9.86866ms
jpegturbo(slowest,ac):10.0639ms

decode:
opencv:4.33917ms
jpegturbo(fastest,huffman):1.99275ms
jpegturbo(slowest,huffman):1.9233ms
jpegturbo(fastest,ac):10.5472ms
jpegturbo(slowest,ac):10.4786ms

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

