///////////////////////////////////////////////////////////////////////////////
//
// Item 15: Provide access to raw resources in resources managing classes.
//
// 1) APIs often require access to raw resources, so each RAII class should
// offer a way to get the resource it manages.
//
// 2) Access may be via explicit conversion or implicit conversion. In general,
// explicit conversion is safer, but implicit conversion is more convenient for
// clients.
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <memory>

class Investiment
{
public:
  Investiment(const std::string& name, int days_held, bool is_tax_free = false)
    : name_{name},
      days_held_{days_held},
      is_tax_free_{is_tax_free}
  { }

  int days_held() const {
    return days_held_;
  }

  bool is_tax_free() const {
    return is_tax_free_;
  }

private:
  std::string name_;
  int         days_held_;
  bool        is_tax_free_;
};

// just for test, make no sense
int daysHeld(const Investiment* pi)
{
  return pi->days_held();
}

int main(int argc, char** argv)
{
  std::shared_ptr<Investiment> invs(new Investiment("ADSKLKS", 120));

  // shared_ptr get raw pointer by get() function
  std::cout << daysHeld(invs.get()) << std::endl;

  return 0;
}
