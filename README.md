# dupfind

Tiny tool for finding similar files and directories (similar by names) in file tree.

Internally it uses simplified Damerau-Levenshtein 
distance (https://en.wikipedia.org/wiki/Damerau%E2%80%93Levenshtein_distance) 
algorithm to compare file/dir names

Usage:

    dupfind -h
    dupfind -ns -ef (?i).*\.jpe?g -f 0.98

