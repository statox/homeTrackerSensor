Convention:

Each sensor file expose a function `float* readXXX()`

If the reading fails the first float of the returned result is non zero.
If the reading succeeds the first float is 0 and the other float are the results:

Results by index:

0. Success: 0 - true, Non 0 - false
1. Temperature in Celsius
2. Humidity in percent
3. Pressure in Pa
