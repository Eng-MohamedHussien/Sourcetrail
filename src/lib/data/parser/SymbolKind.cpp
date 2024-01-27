#include "SymbolKind.h"

SymbolKind intToSymbolKind(int v) {
  switch(v) {
  case SYMBOL_ANNOTATION:
    return SYMBOL_ANNOTATION;
  case SYMBOL_BUILTIN_TYPE:
    return SYMBOL_BUILTIN_TYPE;
  case SYMBOL_CLASS:
    return SYMBOL_CLASS;
  case SYMBOL_ENUM:
    return SYMBOL_ENUM;
  case SYMBOL_ENUM_CONSTANT:
    return SYMBOL_ENUM_CONSTANT;
  case SYMBOL_FIELD:
    return SYMBOL_FIELD;
  case SYMBOL_FUNCTION:
    return SYMBOL_FUNCTION;
  case SYMBOL_GLOBAL_VARIABLE:
    return SYMBOL_GLOBAL_VARIABLE;
  case SYMBOL_INTERFACE:
    return SYMBOL_INTERFACE;
  case SYMBOL_MACRO:
    return SYMBOL_MACRO;
  case SYMBOL_METHOD:
    return SYMBOL_METHOD;
  case SYMBOL_MODULE:
    return SYMBOL_MODULE;
  case SYMBOL_NAMESPACE:
    return SYMBOL_NAMESPACE;
  case SYMBOL_PACKAGE:
    return SYMBOL_PACKAGE;
  case SYMBOL_STRUCT:
    return SYMBOL_STRUCT;
  case SYMBOL_TYPEDEF:
    return SYMBOL_TYPEDEF;
  case SYMBOL_TYPE_PARAMETER:
    return SYMBOL_TYPE_PARAMETER;
  case SYMBOL_UNION:
    return SYMBOL_UNION;
  }
  return SYMBOL_KIND_MAX;
}

int symbolKindToInt(SymbolKind t) {
  return t;
}
