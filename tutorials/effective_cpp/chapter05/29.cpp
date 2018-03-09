///////////////////////////////////////////////////////////////////////////////
//
// Item 29: Strive for exception-safe code.
//
///////////////////////////////////////////////////////////////////////////////
//
// void PrettyMenu::changeBackground(std::istream& imgSrc)
// {
//   lock(&mutex);                 // require mutex
//   delete bgImage;               // get rid of old background
//   ++imageChanges;               // upate image change count
//   bgImage = new Image(imgSrc);  // install new background
//   unlock(&mutex);               // release mutex
// }
//
// Two requirements for exception safety.
// 1) Leak no resources. "new Image(imgSrc)" expression yields an exception,
// the call to unlock never gets executed, and the mutex is held forever.
//
// 2) Don't allow data structures to become corrupted.
// if "new Image(imgSrc)" throw an exception, the 'bgImage' is deleted and
// cannot be recovered. We need two status: success or failure.
// if failed, the state recover to origin.
//
// better approach, but it's not best.
// void PrettyMenu::changeBackground(std::istream& imgSrc)
// {
//   Lock ml(&mutex);
//   delete bgImage;
//   ++imageChanges;
//   bgImage = new Image(imgSrc);
// }
//
// Things to remember:
// 1) Exception-safe functions leak no resources and allow no data structures
// to become corrupted, even when exceptions are thrown. Such functions offer
// the basic, strong, or nothrow guarantees.
//
// 2) The strong guarantee can often be implemented via copy-and-swap, but the
// strong guarantee is not pratical for all functions.
//
// 3) A function can usually offer a guarantee no stronger than the weakest
// guarantee of the functions it calls.
//
///////////////////////////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
  return 0;
}
