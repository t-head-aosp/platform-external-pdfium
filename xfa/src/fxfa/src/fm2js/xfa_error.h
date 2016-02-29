// Copyright 2014 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef XFA_SRC_FXFA_SRC_FM2JS_XFA_ERROR_H_
#define XFA_SRC_FXFA_SRC_FM2JS_XFA_ERROR_H_

#include "core/include/fxcrt/fx_string.h"
#include "core/include/fxcrt/fx_system.h"

enum XFA_FM_ERRMSG {
  FMERR_UNSUPPORTED_CHAR,
  FMERR_BAD_SUFFIX_NUMBER,
  FMERR_INVALIDATE_CHAR,
  FMERR_EXPECTED_IDENTIFIER,
  FMERR_EXPECTED_TOKEN,
  FMERR_EXPECTED_IFEND,
  FMERR_UNEXPECTED_EXPRESSION,
  FMERR_EXPTECTED_OPERATOR,
  FMERR_MAXIMUM
};

class CXFA_FMErrorInfo {
 public:
  CXFA_FMErrorInfo() : linenum(0){};
  ~CXFA_FMErrorInfo(){};
  FX_DWORD linenum;
  CFX_WideString message;
};
const FX_WCHAR* XFA_FM_ErrorMsg(XFA_FM_ERRMSG msg);

#endif  // XFA_SRC_FXFA_SRC_FM2JS_XFA_ERROR_H_
