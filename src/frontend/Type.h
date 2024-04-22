#pragma once

#include <string>
// #include <llvm-14/llvm/Support/Casting.h>

namespace rvlang {

class Type {
public:
  enum class Kind {
    Void,
    Integer,
    FloatPoint,
    Pointer,
    Array,
  };
  enum class Qualifier { Unqualified, Const, Volatile };

protected:
  // type name, int type ->"int"
  // function type : "int(int,bool)", "(int*)(char)"
  // struct type name is decl name
  const std::string m_name;
  // in bytes
  unsigned m_size;
  Kind m_kind;
  Qualifier m_qualifier;

public:
  Type(const std::string &name, int size, Kind s,
       Qualifier q = Qualifier::Unqualified)
      : m_name(name), m_size(size), m_kind(s), m_qualifier(q) {}
  virtual ~Type() {}

  const std::string &getName() const { return m_name; }

  unsigned getSize() const { return m_size; }
  Kind getKind() const { return m_kind; }
  Qualifier getQualifier() const { return m_qualifier; }
  void setQualifier(Qualifier qual) { m_qualifier = qual; }
};

class PointerType : public Type {
private:
  const Type *m_pointeeType;

public:
  PointerType(const std::string &name, const Type *pointeeType,
              Qualifier qual = Qualifier::Unqualified)
      : Type(name, 8, Kind::Pointer, qual), m_pointeeType(pointeeType) {}
  ~PointerType() {}

  const Type *getPointeeType() const { return m_pointeeType; }

  static bool classof(const Type *t) { return Kind::Pointer == t->getKind(); }
};

class VoidType : public Type {
public:
  VoidType() : Type("void", 0, Kind::Void) {}
  ~VoidType() {}
};

class IntegerType : public Type {
private:
  bool m_isSigned;

public:
  IntegerType(const std::string &name, unsigned size, bool isSigned,
              Qualifier qual = Qualifier::Unqualified)
      : Type(name, size, Kind::Integer, qual), m_isSigned(isSigned) {}
  ~IntegerType() {}

  bool isSigned() const { return m_isSigned; }

  void setIsSigned(bool isSigned) { m_isSigned = isSigned; }

  static bool classof(const Type *t) { return Kind::Integer == t->getKind(); }
};

class FloatPointType : public Type {
public:
  explicit FloatPointType(Qualifier qual = Qualifier::Unqualified)
      : Type("float", 8, Kind::FloatPoint, qual) {}
  ~FloatPointType() {}

  static bool classof(const Type *t) {
    return Kind::FloatPoint == t->getKind();
  }
};

class ArrayType : public Type {
private:
  int m_length;
  const Type *m_elementType;

public:
  ArrayType(const std::string &name, int length, const Type *elementType,
            Qualifier qual = Qualifier::Unqualified)
      : Type(name, 8, Kind::Array, qual), m_length(length),
        m_elementType(elementType) {
    m_size = m_length * m_elementType->getSize();
  }
  ~ArrayType() = default;

  const Type *getElementType() const { return m_elementType; }
  void setElementType(const Type *t) { m_elementType = t; }

  static bool classof(const Type *t) { return Kind::Array == t->getKind(); }
};
} // namespace rvlang