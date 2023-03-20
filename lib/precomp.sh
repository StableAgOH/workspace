file="local.h"
std="c++20"

mkdir -p $file.gch
g++ $file -o $file.gch/$file-$std.gch -std=$std
g++ $file -o $file.gch/$file-$std-g.gch -std=$std -g
g++ $file -o $file.gch/$file-$std-O2.gch -std=$std -O2
g++ $file -o $file.gch/$file-$std-g-O2.gch -std=$std -g -O2
