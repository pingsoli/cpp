// if the json file format is wrong.
// boost read_json will throw exception, and point out the error place.
//
// references
// http://zenol.fr/blog/boost-property-tree/en.html

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <string>
#include <exception>
#include <vector>
#include <iostream>

int main(int argc, char *argv[])
{
  using namespace boost::property_tree::json_parser;
  using ptree = boost::property_tree::ptree;

  try {

    ptree pt;
    // load the json file in the ptree
    read_json("../test.json", pt);

    ////////////////////////////////////////////////////////////////////////////
    // Loading some values
    int height = pt.get<int>("height", 0);
    std::string msg = pt.get<std::string>("some.complex.path");
    std::cout << "height: " << height
              << ", message: " << msg << '\n';

    ////////////////////////////////////////////////////////////////////////////
    // browsing lists
    std::vector<std::pair<std::string, std::string>> animals;

    for (ptree::value_type &animal : pt.get_child("animals"))
    {
      std::string name = animal.first;
      std::string color = animal.second.data();
      std::cout << "name: " << name << ", color: " << color << '\n';
      animals.push_back(std::make_pair(name, color));
    }

    ////////////////////////////////////////////////////////////////////////////
    // matrix
    int matrix[3][3];
    int x = 0;
    for (ptree::value_type& row : pt.get_child("matrix"))
    {
      int y = 0;
      for (ptree::value_type& cell : row.second)
      {
        matrix[x][y] = cell.second.get_value<int>();
        std::cout << matrix[x][y] << '\t';
        y++;
      }
      std::cout << '\n';
      x++;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Add values and get values
    pt.put("pi", 3.14159);
    pt.put("some.complex.path", "bonjour");
    double pi = pt.get<double>("pi");
    std::cout << pi << '\n';


    // add a list of objects
    ptree animals_node;

    for (auto &animal : animals)
      animals_node.put(animal.first, animal.second);

    pt.add_child("animals", animals_node);


    // add many nodes with the same name
    ptree fish1_, fish2_;
    fish1_.put_value("blue");
    fish2_.put_value("yellow");

    // NOTE: use put will replace the exsiting node name
    pt.push_back(std::make_pair("fish", fish1_));
    pt.push_back(std::make_pair("fish", fish2_));


    // add a list
    ptree fish_node;
    ptree fish1, fish2, fish3;

    fish1.put("", "fish1");
    fish2.put("", "fish2");
    fish3.put("", "fish3");

    fish_node.push_back(std::make_pair("", fish1));
    fish_node.push_back(std::make_pair("", fish2));
    fish_node.push_back(std::make_pair("", fish3));

    pt.add_child("fish", fish_node);


    // add a matrix(a list contains a list)
    ptree matrix_node;

    for (int i = 0; i < 3; ++i)
    {
      ptree row;
      for (int j = 0; j < 3; ++j)
      {
        ptree cell;

        cell.put_value(matrix[i][j]);
        row.push_back(std::make_pair("", cell));
      }
      matrix_node.push_back(std::make_pair("", row));
    }

    pt.add_child("matrix", matrix_node);

    ////////////////////////////////////////////////////////////////////////////
    // write to another json file
    write_json("../new_test.json", pt);

  } catch (std::exception& e) {
    std::cout << "Exception: " << e.what() << '\n';
  } catch (...) {
   std::cout << "Unknown exception" << '\n';
  }

  return 0;
}
