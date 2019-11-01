// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "items.h"
#include "comboproperty.h"
#include "externalproperty.h"
#include "item_constants.h"
#include <QColor>

using namespace ModelView;

DemoPropertiesItem::DemoPropertiesItem() : CompoundItem(::Constants::DemoPropertiesType)
{
    addProperty(P_BOOL_PROPERTY, true)->setDisplayName("Bool");
    addProperty(P_INTEGER_PROPERTY, 42)->setDisplayName("Integer");
    addProperty(P_STRING_PROPERTY, "abc")->setDisplayName("String");
    addProperty(P_DOUBLE_PROPERTY, 42.1)->setDisplayName("Double");
    addProperty(P_COLOR_PROPERTY, QColor(Qt::green))->setDisplayName("Color");

    auto combo = ComboProperty::createFrom({"option 1", "option 2", "option 3"});
    addProperty(P_COMBO_PROPERTY, combo)->setDisplayName("Combo");

    ExternalProperty ext_prop("Gold", QColor(Qt::darkYellow), "some id");
    addProperty(P_EXTERNAL_PROPERTY, ext_prop)->setDisplayName("External");
}
