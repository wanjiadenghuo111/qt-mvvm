// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "CustomEditorFactory.h"
#include "ApplicationModels.h"
#include "MaterialModel.h"
#include <QModelIndex>
#include <mvvm/editors/externalpropertycomboeditor.h>
#include <mvvm/model/customvariants.h>
#include <mvvm/model/externalproperty.h>

using namespace ModelView;

CustomEditorFactory::~CustomEditorFactory() = default;

CustomEditorFactory::CustomEditorFactory(ApplicationModels* models) : m_models(models) {}

std::unique_ptr<CustomEditor> CustomEditorFactory::createEditor(const QModelIndex& index) const
{
    auto value = index.data(Qt::EditRole);
    if (Utils::IsExtPropertyVariant(value))
        return std::make_unique<ExternalPropertyComboEditor>(
            [this]() { return m_models->materialModel()->material_data(); });
    else
        return DefaultEditorFactory::createEditor(index);
}
