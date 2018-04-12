// Copyright 2017 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef CORE_FXCRT_XML_CFX_XMLDOC_H_
#define CORE_FXCRT_XML_CFX_XMLDOC_H_

#include <memory>

#include "core/fxcrt/cfx_seekablestreamproxy.h"
#include "core/fxcrt/retain_ptr.h"
#include "core/fxcrt/xml/cfx_xmlnode.h"
#include "core/fxcrt/xml/cfx_xmlparser.h"

class CFX_XMLDoc {
 public:
  explicit CFX_XMLDoc(const RetainPtr<CFX_SeekableStreamProxy>& pStream);
  ~CFX_XMLDoc();

  int32_t Load();
  void CloseXML();

  CFX_XMLNode* GetRoot() const { return m_pRoot.get(); }
  CFX_XMLParser* GetParser() const { return m_pXMLParser.get(); }

 private:
  std::unique_ptr<CFX_XMLNode> m_pRoot;
  std::unique_ptr<CFX_XMLParser> m_pXMLParser;
};

#endif  // CORE_FXCRT_XML_CFX_XMLDOC_H_
