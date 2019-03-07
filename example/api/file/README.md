# Example of reading topology file

* Format of topology file (each node will be created if not existed)
```
<first node name> <second node name> <capacity> <flow value>
```

* Example (draw a cycle):
```
a b 3 1
b c 3 1
c a 3 1
```
