////////////////////////////////////////////////////////////////////////////////
//
// max heap implementation
//
////////////////////////////////////////////////////////////////////////////////

#include <cmath>
#include <vector>
#include <iostream>

// max heap
class Heap
{
private:
  std::vector<int> heap;

  int left(int parent);
  int right(int parent);
  int parent(int child);

  void trickle_up(int index);
  void trickle_down(int index);

public:
  Heap() {}
  void insert(int element);
  void remove();
  void display();
  int  size();
};

int Heap::size() {
  return heap.size();
}

void Heap::insert(int element) {
  heap.push_back(element);
  trickle_up(heap.size() - 1);
}

void Heap::remove() {
  heap[0] = heap.at(size() - 1);
  heap.pop_back();
  trickle_down(0);
}

void Heap::trickle_up(int index)
{
  if (index >= 0 &&
      parent(index) >= 0 &&
      heap[parent(index)] < heap[index])
  {
    std::swap(heap[index], heap[parent(index)]);
    trickle_up(parent(index));
  }
}

void Heap::trickle_down(int index)
{
  int l = left(index);
  int r = right(index);

  if (l >= 0 && r >= 0 && heap[l] < heap[r])
    l = r;

  if (l > 0)
  {
    std::swap(heap[index], heap[l]);
    trickle_down(l);
  }
}

int Heap::left(int parent) {
  int l = parent * 2 + 1;
  return (l < heap.size() ? l : -1);
}

int Heap::right(int parent) {
  int r = parent * 2 + 2;
  return (r < heap.size() ? r : -1);
}

int Heap::parent(int child) {
  int p = (child - 1) / 2;
  return (p >= 0 ? p : -1);
}

void Heap::display() {
  std::vector<int>::const_iterator it = heap.cbegin();

  int size = heap.size();
  int level = std::ceil(std::log2(size + 1));

  for (int i = 0; i < level; ++i)
  {
    int start = std::pow(2, i) - 1;
    int end = std::pow(2, i+1) -1;
    for (int j = start; j < end && j < size; ++j)
      std::cout << heap[j] << ' ';
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

int menu()
{
  int choice = 4;
  std::cout
    << "-----------------------\n"
    << "Operations on Heap\n"
    << "-----------------------\n"
    << "1. insert element\n"
    << "2. remove max\n"
    << "3. print heap\n"
    << "4. exit\n";
  std::cout << "your choice: ";
  std::cin >> choice;

  return choice;
}

void init(Heap& heap)
{
  heap.insert(100);
  heap.insert(80);
  heap.insert(70);
  heap.insert(50);
  heap.insert(40);
  heap.insert(20);
  heap.insert(30);
  heap.insert(110);
}

int main(int argc, char** argv)
{
  {
    Heap heap;
    int element;

    init(heap);

    while (true) {
      switch (menu()) {
      case 1:
        std::cout << "please enter element: ";
        std::cin >> element;
        heap.insert(element);
        std::cout << "insert successfully ...\n\n";
        break;
      case 2:
        heap.remove();
        std::cout << "remove successfully ...\n\n";
        break;
      case 3:
        heap.display();
        break;
      case 4:
        exit(1);
      default:
        break;
      }
    }
  }

  return 0;
}
