/*
  Copyright (c) 2009-2017 Dave Gamble and cJSON contributors

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

#ifndef cJSON__h
#define cJSON__h

#ifdef __cplusplus
extern "C"
{
#endif

#if !defined(__WINDOWS__) && (defined(WIN32) || defined(WIN64) || defined(_MSC_VER) || defined(_WIN32))
  #define __WINDOWS__
#endif

#ifdef __WINDOWS__
  #define CJSON_CDECL __cdecl
  #define CJSON_STDCALL __stdcall

  #if defined DLL_EXPORT
    #define CJSON_PUBLIC(type) __declspec(dllexport) type CJSON_STDCALL
  #elif defined  USE_CJSON_DLL
    #define CJSON_PUBLIC(type) __declspec(dllimport) type CJSON_STDCALL
  #else
    #define CJSON_PUBLIC(type) type CJSON_STDCALL
  #endif
#else
  #define CJSON_CDECL
  #define CJSON_STDCALL
  #define CJSON_PUBLIC(type) type
#endif

#define CJSON_VERSION_MAJOR 1
#define CJSON_VERSION_MINOR 7
#define CJSON_VERSION_PATCH 15

typedef struct cJSON
{
    struct cJSON *next;
    struct cJSON *prev;
    struct cJSON *child;
    int type;
    char *valuestring;
    double valuedouble;
    int valueint;
    int valuebool;
} cJSON;

typedef struct cJSON_Hooks
{
      void *(*allocate)(size_t size);
      void (*deallocate)(void *pointer);
} cJSON_Hooks;

typedef int cJSON_bool;

#define cJSON_Invalid (0)
#define cJSON_False  (1 << 0)
#define cJSON_True   (1 << 1)
#define cJSON_NULL   (1 << 2)
#define cJSON_Number (1 << 3)
#define cJSON_String (1 << 4)
#define cJSON_Array  (1 << 5)
#define cJSON_Object (1 << 6)
#define cJSON_Raw    (1 << 7)
#define cJSON_IsReference 256
#define cJSON_StringIsConst 512

#define cJSON_IsFalse(item) (((item) != NULL) && ((item)->type & cJSON_False))
#define cJSON_IsTrue(item) (((item) != NULL) && ((item)->type & cJSON_True))
#define cJSON_IsBool(item) (((item) != NULL) && (((item)->type & (cJSON_True | cJSON_False)) != 0))
#define cJSON_IsNull(item) (((item) != NULL) && ((item)->type & cJSON_NULL))
#define cJSON_IsNumber(item) (((item) != NULL) && ((item)->type & cJSON_Number))
#define cJSON_IsString(item) (((item) != NULL) && ((item)->type & cJSON_String))
#define cJSON_IsArray(item) (((item) != NULL) && ((item)->type & cJSON_Array))
#define cJSON_IsObject(item) (((item) != NULL) && ((item)->type & cJSON_Object))
#define cJSON_IsRaw(item) (((item) != NULL) && ((item)->type & cJSON_Raw))

CJSON_PUBLIC(const char*) cJSON_Version(void);
CJSON_PUBLIC(void) cJSON_InitHooks(cJSON_Hooks* hooks);
CJSON_PUBLIC(cJSON *) cJSON_Parse(const char *value);
CJSON_PUBLIC(cJSON *) cJSON_ParseWithLength(const char *value, size_t buffer_length);
CJSON_PUBLIC(cJSON *) cJSON_ParseWithLengthOpts(const char *value, size_t buffer_length, const char **return_parse_end, cJSON_bool require_null_terminated);
CJSON_PUBLIC(void) cJSON_Delete(cJSON *item);
CJSON_PUBLIC(int) cJSON_GetArraySize(const cJSON *array);
CJSON_PUBLIC(cJSON *) cJSON_GetArrayItem(const cJSON *array, int index);
CJSON_PUBLIC(cJSON *) cJSON_GetObjectItem(const cJSON * const object, const char * const string);
CJSON_PUBLIC(cJSON *) cJSON_GetObjectItemCaseSensitive(const cJSON * const object, const char * const string);
CJSON_PUBLIC(cJSON_bool) cJSON_HasObjectItem(const cJSON *object, const char *string);
CJSON_PUBLIC(const char *) cJSON_GetErrorPtr(void);
CJSON_PUBLIC(char *) cJSON_GetStringValue(cJSON * const item);
CJSON_PUBLIC(double) cJSON_GetNumberValue(cJSON * const item);
CJSON_PUBLIC(cJSON *) cJSON_CreateNull(void);
CJSON_PUBLIC(cJSON *) cJSON_CreateTrue(void);
CJSON_PUBLIC(cJSON *) cJSON_CreateFalse(void);
CJSON_PUBLIC(cJSON *) cJSON_CreateBool(cJSON_bool boolean);
CJSON_PUBLIC(cJSON *) cJSON_CreateNumber(double num);
CJSON_PUBLIC(cJSON *) cJSON_CreateString(const char *string);
CJSON_PUBLIC(cJSON *) cJSON_CreateStringReference(const char *string);
CJSON_PUBLIC(cJSON *) cJSON_CreateObjectReference(cJSON *child);
CJSON_PUBLIC(cJSON *) cJSON_CreateArrayReference(cJSON *child);
CJSON_PUBLIC(cJSON *) cJSON_CreateRaw(const char *raw);
CJSON_PUBLIC(cJSON *) cJSON_CreateArray(void);
CJSON_PUBLIC(cJSON *) cJSON_CreateObject(void);
CJSON_PUBLIC(char *) cJSON_Print(cJSON *item);
CJSON_PUBLIC(char *) cJSON_PrintUnformatted(cJSON *item);
CJSON_PUBLIC(char *) cJSON_PrintBuffered(cJSON *item, int prebuffer, cJSON_bool fmt);
CJSON_PUBLIC(cJSON_bool) cJSON_PrintPreallocated(cJSON *item, char *buf, const int len, const cJSON_bool fmt);
CJSON_PUBLIC(void) cJSON_Minify(char *json);
CJSON_PUBLIC(cJSON *) cJSON_AddNullToObject(cJSON * const object, const char * const name);
CJSON_PUBLIC(cJSON *) cJSON_AddTrueToObject(cJSON * const object, const char * const name);
CJSON_PUBLIC(cJSON *) cJSON_AddFalseToObject(cJSON * const object, const char * const name);
CJSON_PUBLIC(cJSON *) cJSON_AddBoolToObject(cJSON * const object, const char * const name, cJSON_bool b);
CJSON_PUBLIC(cJSON *) cJSON_AddNumberToObject(cJSON * const object, const char * const name, double num);
CJSON_PUBLIC(cJSON *) cJSON_AddStringToObject(cJSON * const object, const char * const name, const char * const string);
CJSON_PUBLIC(cJSON *) cJSON_AddRawToObject(cJSON * const object, const char * const name, const char * const raw);
CJSON_PUBLIC(cJSON *) cJSON_AddObjectToObject(cJSON * const object, const char * const name);
CJSON_PUBLIC(cJSON *) cJSON_AddArrayToObject(cJSON * const object, const char * const name);
CJSON_PUBLIC(cJSON *) cJSON_InsertItemInArray(cJSON *array, int which, cJSON *newitem);
CJSON_PUBLIC(cJSON_bool) cJSON_ReplaceItemViaPointer(cJSON * const parent, cJSON * const item, cJSON * replacement);
CJSON_PUBLIC(cJSON_bool) cJSON_ReplaceItemInArray(cJSON *array, int which, cJSON *newitem);
CJSON_PUBLIC(cJSON_bool) cJSON_ReplaceItemInObject(cJSON *object, const char *string, cJSON *newitem);
CJSON_PUBLIC(cJSON_bool) cJSON_ReplaceItemInObjectCaseSensitive(cJSON *object, const char *string, cJSON *newitem);
CJSON_PUBLIC(cJSON *) cJSON_DetachItemViaPointer(cJSON * const parent, cJSON * const item);
CJSON_PUBLIC(cJSON *) cJSON_DetachItemFromArray(cJSON *array, int which);
CJSON_PUBLIC(void) cJSON_DeleteItemFromArray(cJSON *array, int which);
CJSON_PUBLIC(cJSON_bool) cJSON_DeleteItemFromObject(cJSON *object, const char *string);
CJSON_PUBLIC(cJSON_bool) cJSON_DeleteItemFromObjectCaseSensitive(cJSON *object, const char *string);
CJSON_PUBLIC(void) cJSON_InsertItemInObject(cJSON *object, const char *string, cJSON *item);
CJSON_PUBLIC(cJSON_bool) cJSON_InsertItemInArray(cJSON *array, int which, cJSON *newitem);
CJSON_PUBLIC(cJSON *) cJSON_AppendItemToObject(cJSON *object, const char *string, cJSON *item);
CJSON_PUBLIC(cJSON *) cJSON_AppendItemToArray(cJSON *array, cJSON *item);
CJSON_PUBLIC(cJSON *) cJSON_Duplicate(const cJSON *item, cJSON_bool recurse);
CJSON_PUBLIC(void) cJSON_Minify(char *json);
CJSON_PUBLIC(cJSON_bool) cJSON_IsInvalid(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsFalse(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsTrue(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsBool(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsNull(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsNumber(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsString(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsArray(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsObject(const cJSON * const item);
CJSON_PUBLIC(cJSON_bool) cJSON_IsRaw(const cJSON * const item);

#ifdef __cplusplus
}
#endif

#endif
