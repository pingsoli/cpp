# UUID

## UUID of Boost library
### Four uuid generator  
1) random_generator: generate a random uuid.  
2) nil_generator: generate a nil uuid.  
3) string_generator: check the uuid string.  
4) name_generator: generate uuid in specified namespace.  

### uuid class
Know the convertion between uuid object and string.  

## Description
UUID: Universally Unique Identifiers  
more detail about UUID, please see: RFC 4122.  
  
uuid size: 128 bits  
  
the consistance of UUID:  
  time-low "-" time-mid "-"  
  time-high-and-version "-"  
  clock-seq-and-reversed "-"  
  clock-seq-low "-" node  
  
the following is an example of the string representation of a UUID.  
uuid:f81d4fae-7dec-11d0-a765-00a0c91e6bf6  
  
UUID is 16 octets. 128 = 4 * 32 (characters)  
so, the representation of UUID is 32 characters (octet character).  

## UUID format
```
+---------------------------+-------------------------+---------+
|           Field           |        Data Type        |  Octet  |
+---------------------------+-------------------------+---------+
|         time-low          | unsigned 32 bit integer |  0 - 3  |
|         time-mid          | unsigned 16 bit integer |  4 - 5  |
|    time-hi-and-version    | unsigned 16 bit integer |  6 - 7  |
| clock-seq-hi-and-reserved | unsigned 8 bit integer  |    8    |
|       clock-seq-low       | unsigned 8 bit integer  |    9    |
|           node            | unsigned 48 bit integer | 10 - 15 |
+---------------------------+-------------------------+---------+

```

**What is UUID Version ?**
all kinds of standaration. more detail see RFC 4122.
