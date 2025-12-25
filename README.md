# Coun

## Overview

Coun is cli tool designed to count bytes, chars, words and lines.
I just want to redo wc tool from linux. Supports linux and don't 
support windows and mac.

## Examples

```
coun
```
```
coun -bwl file.txt
```
```
coun --help
```

## How Build

For build you need install cmake.  
Copy repo somewhere, then paste this command:  
```
cmake -B build && cmake --build build
```

## How Install

```
cmake -B build -DCMAKE_BUILD_TYPE=Release && sudo cmake --build build --target install
```
  
## Contribution

Contributions are welcome! If you have any suggestions,  
bug reports, or would like to contribute a new feature,  
please create an issue or submit a pull request.  

