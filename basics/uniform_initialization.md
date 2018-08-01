## Uniform Initializaion

What's the advantage of uniform intialization ?
1) Minimizes redundant typenames.

```
vec3 GetValue()
{
  return vec3(x, y, z);
}

now you can write as the following code:

vec3 GetValue()
{
  return {x, y, z};
}

```

2) Never get the most vexing parse.
```
class Bar;

void func()
{
  int foo(Bar()); // it's a function declaration.
}

void func()
{
  int foo{Bar{}}; // it's a assignment operation.
}
```

// vector has a element, it's value is 100.
std::vector<int> vi{100};
