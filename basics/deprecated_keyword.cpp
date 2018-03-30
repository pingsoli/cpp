///////////////////////////////////////////////////////////////////////////////
//
// It's very useful when upgrading release product.
// No matter the function is invloked or not,
// compiler will give the warning with deprecated attribute, so we can renew
// the product version
//
///////////////////////////////////////////////////////////////////////////////

[[deprecated]] void deprecated_attr_test()
{
}

int main(int argc, char** argv)
{
  deprecated_attr_test();
  return 0;
}
