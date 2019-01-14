#include <node_api.h>
#include "../tokenizer/tokenizer.h"
#include "../common/string_list.h"

napi_value napiTokenize(napi_env env, napi_callback_info info) {
  napi_status status;
  size_t argc = 2;
  napi_value argv[2];
  status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Failed to parse arguments");
  }

  int tmp = -1;
  status = napi_get_value_int32(env, argv[0], &tmp);
  if (status != napi_ok) {
      napi_throw_error(env, NULL, "Invalid number was passed as input string length");
  }
  size_t inputStringLength = (size_t)tmp;

  char* inputString = calloc((size_t)inputStringLength+1, sizeof(char));
  size_t stringResultSize = 0;
  status = napi_get_value_string_utf8(env, argv[1], inputString, inputStringLength, &stringResultSize);
  if (status != napi_ok) {
      napi_throw_error(env, NULL, "Unable to parse input string");
  }

  StringList list;
  StringList* list_p = &list;
  string_list_init(list_p);

  tokenize(inputString, list_p);

  napi_value resNapiArray;
  status = napi_create_array_with_length(env, (size_t)list_p->size, &resNapiArray);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "An error occurred while creating result array");
  }

  for(int i = 0; i < list_p->size; i++) {
    napi_value napiStr;
    const char* str = list_p->data[i];
    const size_t strLength = strlen(str);
    status = napi_create_string_utf8(env, str, strLength, &napiStr);
    if (status != napi_ok) {
      napi_throw_error(env, NULL, "Unable to create napi string from result");
    }
    napi_set_element(env,resNapiArray,(uint32_t)i,napiStr);
  }

  string_list_free(list_p);

  return resNapiArray;
}

napi_value Init(napi_env env, napi_value exports) {
  napi_status status;
  napi_value fn;

  status = napi_create_function(env, NULL, 0, napiTokenize, NULL, &fn);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to wrap native function");
  }

  status = napi_set_named_property(env, exports, "napiTokenize", fn);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to populate exports");
  }

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
