#ifndef MACRO_UTIL_H_
#define MACRO_UTIL_H_

#define TO_STRING(x) (#x)
#define JOIN(x, y) x##y
#define JOIN_1(x, y) JOIN(x, y)
#define JOIN_2(x, y) JOIN_1(x, y)

#ifndef _MSC_VER
#define TMP_VARIABLE(x) JOIN_2(JOIN_1(tmp_variable_, __LINE__), x)
#else //_MSC_VER
#if _MSC_VER == 1200 //VC 6 bug: "__LINE__" sometimes cannot be used with "##" !
#define TMP_VARIABLE(x) JOIN_2(JOIN_1(tmp_variable_, iamsorryforvc6user), x)
#else //_MSC_VER != 1200
#define TMP_VARIABLE(x) JOIN_2(JOIN_1(tmp_variable_, __LINE__), x)
#endif
#endif //_MSC_VER

#define MAC_ARG(mac, index) TMP_VARIABLE(JOIN_1(mac, index))

#define IF_ERROR(testnum) (((int)(testnum))/((int)(testnum)))
#define STATIC_ASSERT(testnum) typedef char JOIN_1(error,__LINE__)[IF_ERROR(testnum)]

#define CONST_VALUE(value, type) (type const)(value)

#endif
