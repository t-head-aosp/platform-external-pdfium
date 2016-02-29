// Copyright 2014 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef XFA_SRC_FXFA_SRC_FM2JS_XFA_SIMPLEEXPRESSION_H_
#define XFA_SRC_FXFA_SRC_FM2JS_XFA_SIMPLEEXPRESSION_H_

#include "core/include/fxcrt/fx_basic.h"
#include "xfa/src/fxfa/src/fm2js/xfa_lexer.h"

#define RUNTIMEFUNCTIONRETURNVALUE \
  (FX_WSTRC(L"foxit_xfa_formcalc_runtime_func_return_value"))
#define EXCLAMATION_IN_IDENTIFIER \
  (FX_WSTRC(L"foxit_xfa_formcalc__exclamation__"))

enum XFA_FM_SimpleExpressionType {
  ASSIGN,
  LOGICALOR,
  LOGICALAND,
  EQUALITY,
  NOTEQUALITY,
  LESS,
  LESSEQUAL,
  GREATER,
  GREATEREQUAL,
  PLUS,
  MINUS,
  MULTIPLE,
  DIVIDE,
  POSITIVE,
  NEGATIVE,
  NOT,
  CALL,
  DOT,
  DOTDOT,
  CONCATFMOBJECT,
  ISFMOBJECT,
  ISFMARRAY,
  GETFMVALUE,
  GETFMJSOBJ,
  VARFILTER
};

CFX_WideStringC XFA_FM_EXPTypeToString(
    XFA_FM_SimpleExpressionType simpleExpType);

enum XFA_FM_AccessorIndex {
  ACCESSOR_NO_INDEX,
  ACCESSOR_NO_RELATIVEINDEX,
  ACCESSOR_POSITIVE_INDEX,
  ACCESSOR_NEGATIVE_INDEX
};

class CXFA_FMSimpleExpression {
 public:
  CXFA_FMSimpleExpression(FX_DWORD line, XFA_FM_TOKEN op);
  virtual ~CXFA_FMSimpleExpression() {}
  virtual void ToJavaScript(CFX_WideTextBuf& javascript);
  virtual void ToImpliedReturnJS(CFX_WideTextBuf& javascript);

  XFA_FM_TOKEN GetOperatorToken() const;

 protected:
  FX_DWORD m_line;
  XFA_FM_TOKEN m_op;
};

class CXFA_FMNullExpression : public CXFA_FMSimpleExpression {
 public:
  explicit CXFA_FMNullExpression(FX_DWORD line);
  ~CXFA_FMNullExpression() override {}
  void ToJavaScript(CFX_WideTextBuf& javascript) override;
};

class CXFA_FMNumberExpression : public CXFA_FMSimpleExpression {
 public:
  CXFA_FMNumberExpression(FX_DWORD line, CFX_WideStringC wsNumber);
  ~CXFA_FMNumberExpression() override {}
  void ToJavaScript(CFX_WideTextBuf& javascript) override;

 private:
  CFX_WideStringC m_wsNumber;
};

class CXFA_FMStringExpression : public CXFA_FMSimpleExpression {
 public:
  CXFA_FMStringExpression(FX_DWORD line, CFX_WideStringC wsString);
  ~CXFA_FMStringExpression() override {}
  void ToJavaScript(CFX_WideTextBuf& javascript) override;

 private:
  CFX_WideStringC m_wsString;
};

class CXFA_FMIdentifierExpressionn : public CXFA_FMSimpleExpression {
 public:
  CXFA_FMIdentifierExpressionn(FX_DWORD line, CFX_WideStringC wsIdentifier);
  ~CXFA_FMIdentifierExpressionn() override {}
  void ToJavaScript(CFX_WideTextBuf& javascript) override;

 private:
  CFX_WideStringC m_wsIdentifier;
};

class CXFA_FMUnaryExpression : public CXFA_FMSimpleExpression {
 public:
  CXFA_FMUnaryExpression(FX_DWORD line,
                         XFA_FM_TOKEN op,
                         CXFA_FMSimpleExpression* pExp);
  ~CXFA_FMUnaryExpression() override;
  void ToJavaScript(CFX_WideTextBuf& javascript) override;

 protected:
  CXFA_FMSimpleExpression* m_pExp;
};

class CXFA_FMBinExpression : public CXFA_FMSimpleExpression {
 public:
  CXFA_FMBinExpression(FX_DWORD line,
                       XFA_FM_TOKEN op,
                       CXFA_FMSimpleExpression* pExp1,
                       CXFA_FMSimpleExpression* pExp2);
  ~CXFA_FMBinExpression() override;
  void ToJavaScript(CFX_WideTextBuf& javascript) override;

 protected:
  CXFA_FMSimpleExpression* m_pExp1;
  CXFA_FMSimpleExpression* m_pExp2;
};

class CXFA_FMAssignExpression : public CXFA_FMBinExpression {
 public:
  CXFA_FMAssignExpression(FX_DWORD line,
                          XFA_FM_TOKEN op,
                          CXFA_FMSimpleExpression* pExp1,
                          CXFA_FMSimpleExpression* pExp2);
  ~CXFA_FMAssignExpression() override {}
  void ToJavaScript(CFX_WideTextBuf& javascript) override;
  void ToImpliedReturnJS(CFX_WideTextBuf& javascript) override;
};

class CXFA_FMLogicalOrExpression : public CXFA_FMBinExpression {
 public:
  CXFA_FMLogicalOrExpression(FX_DWORD line,
                             XFA_FM_TOKEN op,
                             CXFA_FMSimpleExpression* pExp1,
                             CXFA_FMSimpleExpression* pExp2);
  ~CXFA_FMLogicalOrExpression() override {}
  void ToJavaScript(CFX_WideTextBuf& javascript) override;
};

class CXFA_FMLogicalAndExpression : public CXFA_FMBinExpression {
 public:
  CXFA_FMLogicalAndExpression(FX_DWORD line,
                              XFA_FM_TOKEN op,
                              CXFA_FMSimpleExpression* pExp1,
                              CXFA_FMSimpleExpression* pExp2);
  ~CXFA_FMLogicalAndExpression() override {}
  void ToJavaScript(CFX_WideTextBuf& javascript) override;
};

class CXFA_FMEqualityExpression : public CXFA_FMBinExpression {
 public:
  CXFA_FMEqualityExpression(FX_DWORD line,
                            XFA_FM_TOKEN op,
                            CXFA_FMSimpleExpression* pExp1,
                            CXFA_FMSimpleExpression* pExp2);
  ~CXFA_FMEqualityExpression() override {}
  void ToJavaScript(CFX_WideTextBuf& javascript) override;
};

class CXFA_FMRelationalExpression : public CXFA_FMBinExpression {
 public:
  CXFA_FMRelationalExpression(FX_DWORD line,
                              XFA_FM_TOKEN op,
                              CXFA_FMSimpleExpression* pExp1,
                              CXFA_FMSimpleExpression* pExp2);
  ~CXFA_FMRelationalExpression() override {}
  void ToJavaScript(CFX_WideTextBuf& javascript) override;
};

class CXFA_FMAdditiveExpression : public CXFA_FMBinExpression {
 public:
  CXFA_FMAdditiveExpression(FX_DWORD line,
                            XFA_FM_TOKEN op,
                            CXFA_FMSimpleExpression* pExp1,
                            CXFA_FMSimpleExpression* pExp2);
  ~CXFA_FMAdditiveExpression() override {}
  void ToJavaScript(CFX_WideTextBuf& javascript) override;
};

class CXFA_FMMultiplicativeExpression : public CXFA_FMBinExpression {
 public:
  CXFA_FMMultiplicativeExpression(FX_DWORD line,
                                  XFA_FM_TOKEN op,
                                  CXFA_FMSimpleExpression* pExp1,
                                  CXFA_FMSimpleExpression* pExp2);
  ~CXFA_FMMultiplicativeExpression() override {}
  void ToJavaScript(CFX_WideTextBuf& javascript) override;
};

class CXFA_FMPosExpression : public CXFA_FMUnaryExpression {
 public:
  CXFA_FMPosExpression(FX_DWORD line, CXFA_FMSimpleExpression* pExp);
  ~CXFA_FMPosExpression() override {}
  void ToJavaScript(CFX_WideTextBuf& javascript) override;
};

class CXFA_FMNegExpression : public CXFA_FMUnaryExpression {
 public:
  CXFA_FMNegExpression(FX_DWORD line, CXFA_FMSimpleExpression* pExp);
  ~CXFA_FMNegExpression() override {}
  void ToJavaScript(CFX_WideTextBuf& javascript) override;
};

class CXFA_FMNotExpression : public CXFA_FMUnaryExpression {
 public:
  CXFA_FMNotExpression(FX_DWORD line, CXFA_FMSimpleExpression* pExp);
  ~CXFA_FMNotExpression() override {}
  void ToJavaScript(CFX_WideTextBuf& javascript) override;
};

class CXFA_FMCallExpression : public CXFA_FMUnaryExpression {
 public:
  CXFA_FMCallExpression(FX_DWORD line,
                        CXFA_FMSimpleExpression* pExp,
                        CFX_PtrArray* pArguments,
                        FX_BOOL bIsSomMethod);
  ~CXFA_FMCallExpression() override;
  bool IsBuildInFunc(CFX_WideTextBuf* funcName);
  FX_DWORD IsMethodWithObjParam(const CFX_WideStringC& methodName);
  void ToJavaScript(CFX_WideTextBuf& javascript) override;

 private:
  FX_BOOL m_bIsSomMethod;
  CFX_PtrArray* m_pArguments;
};

class CXFA_FMDotAccessorExpression : public CXFA_FMBinExpression {
 public:
  CXFA_FMDotAccessorExpression(FX_DWORD line,
                               CXFA_FMSimpleExpression* pAccessor,
                               XFA_FM_TOKEN op,
                               CFX_WideStringC wsIdentifier,
                               CXFA_FMSimpleExpression* pIndexExp);
  ~CXFA_FMDotAccessorExpression() override {}
  void ToJavaScript(CFX_WideTextBuf& javascript) override;

 private:
  CFX_WideStringC m_wsIdentifier;
};

class CXFA_FMIndexExpression : public CXFA_FMUnaryExpression {
 public:
  CXFA_FMIndexExpression(FX_DWORD line,
                         XFA_FM_AccessorIndex accessorIndex,
                         CXFA_FMSimpleExpression* pIndexExp,
                         FX_BOOL bIsStarIndex);
  ~CXFA_FMIndexExpression() override {}
  void ToJavaScript(CFX_WideTextBuf& javascript) override;

 private:
  XFA_FM_AccessorIndex m_accessorIndex;
  FX_BOOL m_bIsStarIndex;
};

class CXFA_FMDotDotAccessorExpression : public CXFA_FMBinExpression {
 public:
  CXFA_FMDotDotAccessorExpression(FX_DWORD line,
                                  CXFA_FMSimpleExpression* pAccessor,
                                  XFA_FM_TOKEN op,
                                  CFX_WideStringC wsIdentifier,
                                  CXFA_FMSimpleExpression* pIndexExp);
  ~CXFA_FMDotDotAccessorExpression() override {}
  void ToJavaScript(CFX_WideTextBuf& javascript) override;

 private:
  CFX_WideStringC m_wsIdentifier;
};

class CXFA_FMMethodCallExpression : public CXFA_FMBinExpression {
 public:
  CXFA_FMMethodCallExpression(FX_DWORD line,
                              CXFA_FMSimpleExpression* pAccessorExp1,
                              CXFA_FMSimpleExpression* pCallExp);
  ~CXFA_FMMethodCallExpression() override {}
  void ToJavaScript(CFX_WideTextBuf& javascript) override;
};

#endif  // XFA_SRC_FXFA_SRC_FM2JS_XFA_SIMPLEEXPRESSION_H_
