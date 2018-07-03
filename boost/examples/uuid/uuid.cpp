////////////////////////////////////////////////////////////////////////////////
// uuid library example
////////////////////////////////////////////////////////////////////////////////
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>

int main(int argc, char *argv[])
{
  using namespace boost::uuids;

  // random_generator generate a random_uuid.
  random_generator random_gen;
  uuid random_id = random_gen();
  std::cout << "randome uuid:" << random_id << std::endl;

  // print the uuid information.
  std::cout << random_id.size() << '\n'; // 16, the size the uuid in bytes.
  std::cout << std::boolalpha << random_id.is_nil() << '\n'; // false.
  std::cout << random_id.variant() << '\n'; // 1, means conforms to RFC 4122
  std::cout << random_id.version() << '\n'; // 4, created by random_generator.

  // nil_generator generate a nil uuid.
  nil_generator nil_gen;
  uuid nil_id = nil_gen();
  std::cout << std::boolalpha << nil_id.is_nil() << '\n'; // ture.

  // string_generator using existing UUID
  string_generator string_gen;
  uuid str_id = string_gen("CF77C981-F61B-7817-10FF-D916FCC3EAA4");
  std::cout << str_id.variant() << '\n';

  // namespace generator
  name_generator name_gen(random_id);
  std::cout << name_gen("pingsoli") << '\n';

  // converting the uuid to string
  // 1) to_string()
  std::string s = to_string(random_id);
  std::cout << s << '\n';

  // lexical_cast
  std::cout << boost::lexical_cast<std::string>(random_id) << '\n';

  return 0;
}
