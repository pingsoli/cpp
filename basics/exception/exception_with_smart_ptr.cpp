#include <memory>
#include <iostream>

// consider the following code
processWidget(std::shared_ptr<Widget>(new Widget), // potential resource leak.
              computePriority());
// copmiler cannot make sure the order of parameter execution.
// so the following order may occur.
// 1. Perform "new Widget".
// 2. Execute computePriority.
// 3. Run std::shared_ptr constructor.
//
// if such code is generated and, at runtime, computePriority produces an
// exception, the dynamically allocated Widget from step 1 will be leaked,
// because it will never be stored in the std::shared_pr that's supposed to
// start managing it in step 3.

processWidget(std::make_shared<Widget>(), computePriority());

