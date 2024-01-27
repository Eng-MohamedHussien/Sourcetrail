#pragma once

enum SymbolKind {    // these values need to be the same as SymbolKind in Java code
  SYMBOL_ANNOTATION = 1,
  SYMBOL_BUILTIN_TYPE = 2,
  SYMBOL_CLASS = 3,
  SYMBOL_ENUM = 4,
  SYMBOL_ENUM_CONSTANT = 5,
  SYMBOL_FIELD = 6,
  SYMBOL_FUNCTION = 7,
  SYMBOL_GLOBAL_VARIABLE = 8,
  SYMBOL_INTERFACE = 9,
  SYMBOL_MACRO = 10,
  SYMBOL_METHOD = 11,
  SYMBOL_MODULE = 12,
  SYMBOL_NAMESPACE = 13,
  SYMBOL_PACKAGE = 14,
  SYMBOL_STRUCT = 15,
  SYMBOL_TYPEDEF = 16,
  SYMBOL_TYPE_PARAMETER = 17,
  SYMBOL_UNION = 18,
  SYMBOL_KIND_MAX = 19
};

SymbolKind intToSymbolKind(int v);

int symbolKindToInt(SymbolKind t);