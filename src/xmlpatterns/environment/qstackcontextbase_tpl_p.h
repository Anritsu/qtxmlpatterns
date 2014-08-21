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

/**
 * @file
 * @short This file is included by qstackcontextbase_p.h.
 * If you need includes in this file, put them in qstackcontextbase_p.h, outside of the namespace.
 */

template<typename TSuperClass>
StackContextBase<TSuperClass>::StackContextBase() : m_rangeVariables(10),
                                                    m_expressionVariables(10),
                                                    m_positionIterators(5),
                                                    m_itemCacheCells(5),
                                                    m_itemSequenceCacheCells(5)
{
    /* The m_* containers are initialized with default sizes. Estimated guesses on usage patterns. */
}

template<typename TSuperClass>
StackContextBase<TSuperClass>::StackContextBase(const DynamicContext::Ptr &prevContext)
                                                : TSuperClass(prevContext),
                                                  m_rangeVariables(10),
                                                  m_expressionVariables(10),
                                                  m_positionIterators(5),
                                                  m_itemCacheCells(5),
                                                  m_itemSequenceCacheCells(5)
{
    Q_ASSERT(prevContext);
}

template<typename TSuperClass>
ItemCacheCell &StackContextBase<TSuperClass>::itemCacheCell(const VariableSlotID slot)
{
    if(slot >= m_itemCacheCells.size())
        m_itemCacheCells.resize(qMax(slot + 1, m_itemCacheCells.size()));

    return m_itemCacheCells[slot];
}

template<typename TSuperClass>
ItemSequenceCacheCell::Vector &StackContextBase<TSuperClass>::itemSequenceCacheCells(const VariableSlotID slot)
{
    if(slot >= m_itemSequenceCacheCells.size())
        m_itemSequenceCacheCells.resize(qMax(slot + 1, m_itemSequenceCacheCells.size()));

    return m_itemSequenceCacheCells;
}

template<typename TSuperClass>
Item StackContextBase<TSuperClass>::rangeVariable(const VariableSlotID slot) const
{
    Q_ASSERT(slot < m_rangeVariables.size());
    Q_ASSERT(m_rangeVariables.at(slot));
    return m_rangeVariables.at(slot);
}

template<typename TSuperClass>
Expression::Ptr StackContextBase<TSuperClass>::expressionVariable(const VariableSlotID slot) const
{
    Q_ASSERT(slot < m_expressionVariables.size());
    Q_ASSERT(m_expressionVariables.at(slot));
    return m_expressionVariables.at(slot);
}

template<typename TSuperClass>
Item::Iterator::Ptr StackContextBase<TSuperClass>::positionIterator(const VariableSlotID slot) const
{
    Q_ASSERT(slot < m_positionIterators.size());
    return m_positionIterators.at(slot);
}

template<typename TSuperClass>
template<typename VectorType, typename UnitType>
inline
void StackContextBase<TSuperClass>::setSlotVariable(const VariableSlotID slot,
                                                    const UnitType &newValue,
                                                    VectorType &container) const
{
    if(slot < container.size())
        container.replace(slot, newValue);
    else
    {
        container.resize(slot + 1);
        container.replace(slot, newValue);
    }
}

template<typename TSuperClass>
void StackContextBase<TSuperClass>::setRangeVariable(const VariableSlotID slot,
                                                     const Item &newValue)
{
    setSlotVariable(slot, newValue, m_rangeVariables);
}

template<typename TSuperClass>
void StackContextBase<TSuperClass>::setExpressionVariable(const VariableSlotID slot,
                                                          const Expression::Ptr &newValue)
{
    setSlotVariable(slot, newValue, m_expressionVariables);
}

template<typename TSuperClass>
void StackContextBase<TSuperClass>::setPositionIterator(const VariableSlotID slot,
                                                        const Item::Iterator::Ptr &newValue)
{
    setSlotVariable(slot, newValue, m_positionIterators);
}

template<typename TSuperClass>
DynamicContext::TemplateParameterHash &StackContextBase<TSuperClass>::templateParameterStore()
{
    return m_templateParameterStore;
}

