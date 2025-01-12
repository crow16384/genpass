# Simple password generator written in C++

```
genpass [options] format

                  options:
                    -n [ --number ]  number of passwords (default =3)

                    
                  'format' is required
                  where:
                    W - uppercase word
                    w - lowercase word
                    d - digit
                    s - special symbol

                    
                  This is a template for generation with type and number of characters
                  
                  For example:

                    genpass W4s2w3d5

                    
                  will produce 3 (default, see --number) passwords
                  like: 'Cyvi!:wof90943'
```
