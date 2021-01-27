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

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef Patternist_DelegatingDynamicContext_H
#define Patternist_DelegatingDynamicContext_H

#include <private/qdynamiccontext_p.h>
#include <private/qexpression_p.h>

QT_BEGIN_NAMESPACE

namespace QPatternist
{
    /**
     * @short Base class for dynamic contexts that are
     * created from an existing one.
     *
     * In some cases multiple DynamicContext instances must be used in
     * order to maintain somekind of scope. This class delegates
     * the DynamicContext interface onto another DynamicContext instance,
     * allowing the sub-class to only implement what it needs to.
     *
     * @author Frans Englich <frans.englich@nokia.com>
     */
    class DelegatingDynamicContext : public DynamicContext
    {
    public:
        virtual xsInteger contextPosition() const;
        virtual Item contextItem() const;
        virtual xsInteger contextSize();

        virtual ItemCacheCell &itemCacheCell(const VariableSlotID slot);
        virtual ItemSequenceCacheCell::Vector &itemSequenceCacheCells(const VariableSlotID slot);

        virtual void setRangeVariable(const VariableSlotID slotNumber,
                                      const Item &newValue);
        virtual Item rangeVariable(const VariableSlotID slotNumber) const;

        virtual void setExpressionVariable(const VariableSlotID slotNumber,
                                           const Expression::Ptr &newValue);
        virtual Expression::Ptr expressionVariable(const VariableSlotID slotNumber) const;

        virtual void setFocusIterator(const Item::Iterator::Ptr &it);
        virtual Item::Iterator::Ptr focusIterator() const;

        virtual Item::Iterator::Ptr positionIterator(const VariableSlotID slot) const;
        virtual void setPositionIterator(const VariableSlotID slot,
                                         const Item::Iterator::Ptr &newValue);

        virtual QAbstractMessageHandler * messageHandler() const;
        virtual QExplicitlySharedDataPointer<DayTimeDuration> implicitTimezone() const;
        virtual QDateTime currentDateTime() const;
        virtual QAbstractXmlReceiver *outputReceiver() const;
        virtual NodeBuilder::Ptr nodeBuilder(const QUrl &baseURI) const;
        virtual ResourceLoader::Ptr resourceLoader() const;
        virtual ExternalVariableLoader::Ptr externalVariableLoader() const;
        virtual NamePool::Ptr namePool() const;
        virtual QSourceLocation locationFor(const SourceLocationReflection *const reflection) const;
        virtual void addNodeModel(const QAbstractXmlNodeModel::Ptr &nm);
        virtual const QAbstractUriResolver *uriResolver() const;
        virtual ItemCacheCell &globalItemCacheCell(const VariableSlotID slot);
        virtual ItemSequenceCacheCell::Vector &globalItemSequenceCacheCells(const VariableSlotID slot);
        virtual Item currentItem() const;
        virtual TemplateParameterHash &templateParameterStore();

        virtual DynamicContext::Ptr previousContext() const;
        virtual QExplicitlySharedDataPointer<TemplateMode> currentTemplateMode() const;

    protected:
        DelegatingDynamicContext(const DynamicContext::Ptr &prevContext);

        const DynamicContext::Ptr m_prevContext;
    };
}

QT_END_NAMESPACE

#endif
