/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtXmlPatterns module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
****************************************************************************/

#include "qcommonsequencetypes_p.h"
#include "qpatternistlocale_p.h"
#include "qnodebuilder_p.h"
#include "qqnamevalue_p.h"

#include "qprocessinginstructionconstructor_p.h"

QT_BEGIN_NAMESPACE

using namespace QPatternist;

ProcessingInstructionConstructor::
ProcessingInstructionConstructor(const Expression::Ptr &op1,
                                 const Expression::Ptr &op2) : PairContainer(op1, op2)
{
}

QString ProcessingInstructionConstructor::leftTrimmed(const QString &input)
{
    const int len = input.length();

    for(int i = 0; i < len; ++i)
    {
        if(!input.at(i).isSpace())
            return input.mid(i);
    }

    return QString(); /* input consists only of whitespace. All was trimmed. */
}

QString ProcessingInstructionConstructor::data(const DynamicContext::Ptr &context) const
{
    const Item name(m_operand1->evaluateSingleton(context));
    const Item dataArg(m_operand2->evaluateSingleton(context));

    if(dataArg)
    {
        /* Perform trimming before validation, to increase speed. */
        const QString value(leftTrimmed(dataArg.stringValue()));

        if(value.contains(QLatin1String("?>")))
        {
            context->error(QtXmlPatterns::tr("The data of a processing instruction cannot contain the string %1").arg(formatData("?>")),
                              ReportContext::XQDY0026, this);
            return QString();
        }
        else
            return value;
    }
    else
        return QString();
}

QXmlName ProcessingInstructionConstructor::evaluateTardata(const DynamicContext::Ptr &context) const
{
    const Item name(m_operand1->evaluateSingleton(context));
    return context->namePool()->allocateQName(QString(), name.stringValue());
}

Item ProcessingInstructionConstructor::evaluateSingleton(const DynamicContext::Ptr &context) const
{
    const NodeBuilder::Ptr nodeBuilder(context->nodeBuilder(QUrl()));

    nodeBuilder->processingInstruction(evaluateTardata(context), data(context));

    const QAbstractXmlNodeModel::Ptr nm(nodeBuilder->builtDocument());
    context->addNodeModel(nm);

    return nm->root(QXmlNodeModelIndex());
}

void ProcessingInstructionConstructor::evaluateToSequenceReceiver(const DynamicContext::Ptr &context) const
{
    QAbstractXmlReceiver *const receiver = context->outputReceiver();

    receiver->processingInstruction(evaluateTardata(context), data(context));
}

SequenceType::Ptr ProcessingInstructionConstructor::staticType() const
{
    return CommonSequenceTypes::ExactlyOneProcessingInstruction;
}

SequenceType::List ProcessingInstructionConstructor::expectedOperandTypes() const
{
    SequenceType::List result;
    result.append(CommonSequenceTypes::ExactlyOneString);
    result.append(CommonSequenceTypes::ZeroOrOneString);
    return result;
}

Expression::Properties ProcessingInstructionConstructor::properties() const
{
    return DisableElimination | IsNodeConstructor;
}

ExpressionVisitorResult::Ptr
ProcessingInstructionConstructor::accept(const ExpressionVisitor::Ptr &visitor) const
{
    return visitor->visit(this);
}

QT_END_NAMESPACE
