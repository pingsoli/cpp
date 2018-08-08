
### Description
Boost property_tree library provides operations about json, ini, xml files.

NOTE: ini files is prevalent in windows platform, but now it's deprecated.

### Summary
the configure files is abstracted as a property tree.

take the json file as example.  
key-value: the key is a string.  
the vlaue can be boolean, string, integer, float, list, objet.  

```
{
  "name": "pingsoli",
  "age": 50,
  "height": 170.0,
  "single": false,
  "phones": [ "123456789", "12345667", "12345666" ],
  "addresses": {
    "location": "xxxx-xxx-xx",
    "floor": "203",
  }
}
```

### Pitfalls
1) no operator[] operations on a tree node. It's not so much convenient.
2) not support the json standard. Boolean, Integer, float will wrapped with double
quote when writing to json file. like this:
```
{
  "age": "50",
  "height": "170.0",
  "single": "false"
}
```
You can hijack boost source file to adjust your situation, more detail:
https://stackoverflow.com/questions/2855741/why-boost-property-tree-write-json-saves-everything-as-string-is-it-possible-to
It's still an issue for 1.67.
