#include <stdio.h>

typedef struct {
  int code;
  const char *tag;
  const char *msg;
} ErrorDesc;

typedef enum {
  ERROR_NoError = 0,
  ERROR_InvalidHandle,
  ERROR_401Unauthorized,
  ERROR_404StreamNotFound,
  ERROR_Num
} ErrorCode;

#define ERROR_TAG(tag) ERROR_##tag, #tag
static const ErrorDesc ErrorDescEntries[] = {
  { ERROR_TAG(NoError),           "No Error"             },
  { ERROR_TAG(InvalidHandle),     "Invalid Handle Value" },
  { ERROR_TAG(401Unauthorized),   "401 Unauthorized"     },
  { ERROR_TAG(404StreamNotFound), "404 Stream Not Found" },
  { ERROR_Num, NULL, NULL }
};

const char* GetErrorMsg(int code) {
  const ErrorDesc* found = NULL;

  for (int i = 0; i < ERROR_Num; ++i) {
    if (code == ErrorDescEntries[i].code) {
      found = &ErrorDescEntries[i];
      break;
    }
  }

  if (found) {
    return found->msg;
  } else {
    return "Unknow Errror";
  }
}

int main(int argc, char *argv[])
{
  printf("Error: %s\n", GetErrorMsg(2));
  printf("Error: %s\n", GetErrorMsg(0));

  return 0;
}
