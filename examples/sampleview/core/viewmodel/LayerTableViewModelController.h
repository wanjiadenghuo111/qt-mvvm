// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef LAYERTABLEVIEWMODELCONTROLLER_H
#define LAYERTABLEVIEWMODELCONTROLLER_H

#include <mvvm/viewmodel/viewmodelcontroller.h>

namespace ModelView
{
class ViewModel;
} // namespace ModelView

/*!
@class LayerTableViewModelController
@brief Controller for LayerTableViewModel to show MultiLayerItem in a tree with custom layout.

Will iterate through all top level items and creates rows with layer properties.
*/

class LayerTableViewModelController : public ModelView::ViewModelController
{
public:
    explicit LayerTableViewModelController(ModelView::SessionModel* model,
                                           ModelView::ViewModel* view_model = nullptr);
};

#endif //  LAYERTABLEVIEWMODELCONTROLLER_H
