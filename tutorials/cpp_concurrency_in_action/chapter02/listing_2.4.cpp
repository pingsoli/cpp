///////////////////////////////////////////////////////////////////////////////
//
// Detaching a thread to handle other documents
//
///////////////////////////////////////////////////////////////////////////////

#include <thread>
#include <string>

void open_document_and_display_gui(const std::string& filename)
{}

bool done_editing()
{
  return true;
}

enum command_type {
  open_new_document
};

struct user_command
{
  command_type type;

  user_command() :
    type(open_new_document)
  {}
};

user_command get_user_input()
{
  return user_command();
}

std::string get_filename_from_user()
{
  return "foo.doc";
}

void process_user_input(user_command const& cmd)
{}

void edit_document(const std::string& filename)
{
  open_document_and_display_gui(filename);

  while (!done_editing())
  {
    user_command cmd = get_user_input();
    if (cmd.type == open_new_document)
    {
      std::string const new_name = get_filename_from_user();
      std::thread t(edit_document, new_name);
      t.detach();
    }
    else
    {
      process_user_input(cmd);
    }
  }
}

int main(int argc, char** argv)
{
  edit_document("bar.doc");

  return 0;
}
