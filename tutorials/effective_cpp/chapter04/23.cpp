///////////////////////////////////////////////////////////////////////////////
//
// Item 23: Prefer non-member non-friend functions to member functions.
//
// Prefer non-member non-friend functions to member functions. Doing so
// increases encapsulation, packaging flexibility, and functional extensibility
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

class WebBrowser
{
public:

  void clearCache() { }
  void clearHistory() { }
  void removeCookies() { }

  // many will want to perform all these actions together.
  // but it's not good.
  void clearEverything()
  {
    clearCache();
    clearHistory();
    removeCookies();
  }
};

// It's a better way than member function.
void clearBrowser(WebBrowser& browser)
{
  browser.clearCache();
  browser.clearHistory();
  browser.removeCookies();
}

// now we found best approach
// make clearBrowser as non-member function in the same namespace as WebBrowser
namespace WebBrowserStuff {

  class WebBrowser
  {
  public:
    void clearCache() { }
    void clearHistory() { }
    void removeCookies() { }
  };

  void clearBrowser(WebBrowser& wb)
  {
    wb.clearCache();
    wb.clearHistory();
    wb.removeCookies();
  }

} // WebBrowser namespace

int main(int argc, char** argv)
{
  /////////////////////////////////////////////////////////////////////////////

  WebBrowser browser;

  browser.clearEverything();
  clearBrowser(browser);

  /////////////////////////////////////////////////////////////////////////////

  WebBrowserStuff::WebBrowser wb;

  WebBrowserStuff::clearBrowser(wb);

  return 0;
}
