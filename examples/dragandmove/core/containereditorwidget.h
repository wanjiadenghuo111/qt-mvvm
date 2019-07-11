// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef CONTAINEREDITORWIDGET_H
#define CONTAINEREDITORWIDGET_H

#include <QWidget>
#include <memory>

class SampleModel;
class QTreeView;

namespace ModelView
{
class AbstractViewModel;
class ViewModelDelegate;
} // namespace ModelView

/*!
@class ContainerEditor
@brief Shows content of container and provide functionality to add, copy and move items.
*/

class ContainerEditorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ContainerEditorWidget(QWidget* parent = nullptr);
    ~ContainerEditorWidget();

    void setModel(SampleModel* model);

private:
    QTreeView* m_treeView;
    std::unique_ptr<ModelView::AbstractViewModel> m_viewModel;
    std::unique_ptr<ModelView::ViewModelDelegate> m_delegate;
};

#endif // CONTAINEREDITORWIDGET_H