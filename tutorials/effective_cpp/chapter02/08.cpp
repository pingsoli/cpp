///////////////////////////////////////////////////////////////////////////////
//
// Item 08: Prevent exception from leaving destructors.
//
// 1) Destructors should never emit exceptions. If functions called in a
// destructor may throw, the destructor should catch any exceptions, then
// swallow them or terminate the program.
//
// 2) If class clients need to be able to react to exceptions thrown during an
// operation, the class should provide a regular (i.e, non-destructor) function
// that performs the operation.
//
///////////////////////////////////////////////////////////////////////////////

class DBConnection
{
public:
  void close()
  {
    /* close the connection */
    // may throw exception
  }
};

class DBConn
{
public:
  ~DBConn()
  {
    if (!closed)
    {
      try
      {
        db.close();
        closed = true;
      }
      catch (...)
      {
        // deal with the exception situation
        // make a log entry that call to close failed.
        //
        // if closing fails, note that and terminate or swallow
      }
    }
  }

private:
  DBConnection db;
  bool         closed;
};

int main(int argc, char** argv)
{
  return 0;
}
