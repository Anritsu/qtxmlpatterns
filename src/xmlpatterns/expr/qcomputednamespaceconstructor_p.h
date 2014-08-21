/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtXmlPatterns module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia. For licensing terms and
** conditions see http://qt.digia.com/licensing. For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights. These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef Patternist_ComputedNamespaceConstructor_H
#define Patternist_ComputedNamespaceConstructor_H

#include <private/qpaircontainer_p.h>

QT_BEGIN_NAMESPACE

namespace QPatternist
{
    /**
     * @short Constructs a namespace on an element, and naturally only appears
     * as a child of ElementConstructor.
     *
     * @author Frans Englich <frans.englich@nokia.com>
     * @ingroup Patternist_expressions
     * @since 4.5
     */
    class ComputedNamespaceConstructor : public PairContainer
    {
    public:
        ComputedNamespaceConstructor(const Expression::Ptr &prefix,
                                     const Expression::Ptr &namespaceURI);

        virtual void evaluateToSequenceReceiver(const DynamicContext::Ptr &context) const;

        /**
         * @returns a list containing one CommonSequenceTypes::ExactlyOneString instance.
         */
        virtual SequenceType::List expectedOperandTypes() const;

        /**
         * The static type is exactly one attribute node. It's unclear what
         * affects the static type has, but specifying anything else could lead
         * to complications wrt. node order, XQTY0024. Of course, it's not
         * conceptually correct, since a namespace node isn't an attribute
         * node.
         */
        virtual SequenceType::Ptr staticType() const;

        virtual ExpressionVisitorResult::Ptr accept(const ExpressionVisitor::Ptr &visitor) const;
        virtual Expression::Properties properties() const;
    };
}

QT_END_NAMESPACE

#endif
