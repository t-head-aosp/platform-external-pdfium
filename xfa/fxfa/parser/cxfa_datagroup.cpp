// Copyright 2017 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#include "xfa/fxfa/parser/cxfa_datagroup.h"

#include "fxjs/xfa/cjx_node.h"
#include "third_party/base/ptr_util.h"

namespace {

const CXFA_Node::AttributeData kDataGroupAttributeData[] = {
    {XFA_Attribute::Name, XFA_AttributeType::CData, nullptr},
};

}  // namespace

CXFA_DataGroup::CXFA_DataGroup(CXFA_Document* doc, XFA_PacketType packet)
    : CXFA_Node(doc,
                packet,
                XFA_XDPPACKET_Datasets,
                XFA_ObjectType::Node,
                XFA_Element::DataGroup,
                {},
                kDataGroupAttributeData,
                pdfium::MakeUnique<CJX_Node>(this)) {}

CXFA_DataGroup::~CXFA_DataGroup() = default;
