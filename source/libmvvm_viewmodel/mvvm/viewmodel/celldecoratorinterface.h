// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_CELLDECORATORINTERFACE_H
#define MVVM_VIEWMODEL_CELLDECORATORINTERFACE_H

#include <mvvm/core/export.h>
#include <string>

class QModelIndex;
class QStyleOptionViewItem;

namespace ModelView
{

//! Interface class to generate cell decorations (i.e. text) in Qt trees and tables.

class CORE_EXPORT CellDecoratorInterface
{
public:
    virtual ~CellDecoratorInterface() = default;

    virtual bool hasCustomDecoration(const QModelIndex& index) const = 0;
    virtual void initStyleOption(QStyleOptionViewItem* option, const QModelIndex& index) = 0;
};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_CELLDECORATORINTERFACE_H
