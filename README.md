# dspeak
Encode an input string as binary within a carrier string, using capitals for '1' and lower case for '0'. E.g.:

```
$ dspeak "dork" "You're a really nice, considerate fella!"
  
[0]: yOU're A reaLLy NICE, cONSidEraTE fElLA!

d: 0x64, 0110 0100 yOU're A re
o: 0x6f, 0110 1111 aLLy NICE,
r: 0x72, 0111 0010 cONSidEr
k: 0x6b, 0110 1011 aTE fElLA!
```

Your carrier string must be at least eight times the length of the encoded string in terms of alphabetic characters only. Refer to the above example.
