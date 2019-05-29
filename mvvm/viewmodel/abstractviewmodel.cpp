// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "abstractviewmodel.h"
#include "modelmapper.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include "viewitems.h"
#include "viewmodelutils.h"
#include "childrenstrategyinterface.h"
#include "rowconstructorinterface.h"

namespace
{

//! Returns true if given SessionItem role is valid for view
bool isValidItemRole(const ModelView::ViewItem* view, int item_role)
{
    if (view->item_role() == item_role)
        return true;

    if (item_role == ModelView::ItemDataRole::APPEARANCE)
        return true;

    return false;
}
} // namespace

using namespace ModelView;

AbstractViewModel::AbstractViewModel(QObject* parent)
    : QStandardItemModel(parent), m_sessionModel(nullptr), m_rootItem(nullptr)
{
    setItemPrototype(new ViewEmptyItem);
}

AbstractViewModel::~AbstractViewModel()
{
    if (m_sessionModel)
        m_sessionModel->mapper()->unsubscribe(this);
}

void AbstractViewModel::setSessionModel(SessionModel* model)
{
    if (m_sessionModel)
        m_sessionModel->mapper()->unsubscribe(this);

    m_sessionModel = model;

    if (m_sessionModel) {
        auto on_data_change = [this](SessionItem* item, int role) { onDataChange(item, role); };
        m_sessionModel->mapper()->setOnDataChange(on_data_change, this);

        auto on_row_inserted = [this](SessionItem* item, std::string tag, int row) {
            onRowInserted(item, tag, row);
        };
        m_sessionModel->mapper()->setOnRowInserted(on_row_inserted, this);

        auto on_row_removed = [this](SessionItem* item, std::string tag, int row) {
            onRowRemoved(item, tag, row);
        };
        m_sessionModel->mapper()->setOnRowRemoved(on_row_removed, this);

        auto on_model_destroyed = [this](SessionModel*) { m_sessionModel = nullptr; clear();};
        m_sessionModel->mapper()->setOnModelDestroyed(on_model_destroyed, this);

        auto on_model_reset = [this](SessionModel*) { clear(); m_rootItem = nullptr; onModelReset(); };
        m_sessionModel->mapper()->setOnModelReset(on_model_reset, this);

        init_view_model();
    }
}

//! Returns root item of the model. Can be different from model's root item when the intention is
//! to show only part of the model.

SessionItem* AbstractViewModel::rootSessionItem() const
{
    return m_rootItem ? m_rootItem : m_sessionModel->rootItem();
}

//! Returns QStandardItem associated with top level item (rootSessionItem).

QStandardItem* AbstractViewModel::rootViewItem() const
{
    return invisibleRootItem();
}

//! Returns vector of standard views used to display given SessionItem.

std::vector<QStandardItem*> AbstractViewModel::findStandardViews(const SessionItem* item) const
{
    if (item == rootSessionItem())
        return {rootViewItem()};

    std::vector<QStandardItem*> result;
    for (auto view : findViews(item))
        result.push_back(view);

    return result;
}

std::vector<ViewItem*> AbstractViewModel::findViews(const SessionItem* item) const
{
    return Utils::findViews(this, item, QModelIndex());
}

//! Returns SessionItem corresponding to givem QModelIndex.

SessionItem* AbstractViewModel::sessionItemFromIndex(const QModelIndex& index) const
{
    SessionItem* result(nullptr);
    if (!m_sessionModel)
        return result;

    if (index.isValid()) {
        if (auto viewItem = dynamic_cast<ViewItem*>(itemFromIndex(index)))
            result = viewItem->item();
    } else {
        result = rootSessionItem();
    }

    return result;
}

//! Returns list of QModelIndex'es related to given SessionItem.

QModelIndexList AbstractViewModel::indexOfSessionItem(const SessionItem* item) const
{
    QModelIndexList result;
    for (auto view : findStandardViews(item))
        result.push_back(indexFromItem(view));
    return result;
}

void AbstractViewModel::setRootSessionItem(SessionItem* item)
{
    if (item->model() != m_sessionModel)
        throw std::runtime_error(
            "ViewModel::setRootSessionItem()->Error. Item doesn't belong to a model.");

    m_rootItem = item;
    init_view_model();
}

//! Generates necessary notifications on SessionItem's data change.

void AbstractViewModel::onDataChange(SessionItem* item, int role)
{
    for (auto view : findViews(item)) {

        // inform corresponding LabelView and DataView
        if (isValidItemRole(view, role)) {
            auto index = indexFromItem(view);
            dataChanged(index, index, Utils::item_role_to_qt(role));
        }
    }
}

//! Insert views (QStandardItem's) when given SessionItem gets its new row.
// Important: simplified approach is used here. All children views are first removed and
// then whole branch regenerated from the scratch.

void AbstractViewModel::onRowInserted(SessionItem* parent, std::string, int)
{
    generate_children_views(parent);
}

//! Removes views (QStandardItem's) corresponding to given SessionItem and its row.
// Important: simplified approach is used here. All children views are removed and
// then whole branch rebuild from the scratch.

void AbstractViewModel::onRowRemoved(SessionItem* parent, std::string, int)
{
    generate_children_views(parent);
}

void AbstractViewModel::onModelReset()
{
    setColumnCount(m_row_constructor->columnCount());
    setHorizontalHeaderLabels(m_row_constructor->horizontalHeaderLabels());
}

void AbstractViewModel::setRowConstructor(std::unique_ptr<RowConstructorInterface> row_constructor)
{
    m_row_constructor = std::move(row_constructor);
}

void AbstractViewModel::setChildrenStrategy(std::unique_ptr<ChildrenStrategyInterface> children_strategy)
{
    m_children_strategy = std::move(children_strategy);
}

void AbstractViewModel::init_view_model()
{
    if (!m_row_constructor)
        throw std::runtime_error("AbstractViewModel::init_view_model() -> Error. Row constructor "
                                 "is not initialized.");

    if (!m_children_strategy)
        throw std::runtime_error("AbstractViewModel::init_view_model() -> Error. Children strategy "
                                 "is not initialized.");

    clear();
    setColumnCount(m_row_constructor->columnCount());
    setHorizontalHeaderLabels(m_row_constructor->horizontalHeaderLabels());
    update_model();
}

//! Regenerate all views of given parent.

void AbstractViewModel::generate_children_views(SessionItem* parent)
{
    auto views = findStandardViews(parent);
    for (auto view : views)
        view->removeRows(0, view->rowCount());

    if (views.size())
        iterate(parent, views.at(0));
}

void AbstractViewModel::update_model()
{
    iterate(rootSessionItem(), rootViewItem());
}

void AbstractViewModel::iterate(const SessionItem* item, QStandardItem* parent)
{
    QStandardItem* origParent(parent);
    for (auto child : item_children(item)) {

        auto row = m_row_constructor->constructRow(child);
        parent->appendRow(row);

        if (row.size())
            parent = row.at(0); // labelItem

        iterate(child, parent);
        parent = origParent;
    }
}

//! Returns (possibly filtered) vector of children of given item.

std::vector<SessionItem*> AbstractViewModel::item_children(const SessionItem* item) const
{
    return m_children_strategy->children(item);
}

