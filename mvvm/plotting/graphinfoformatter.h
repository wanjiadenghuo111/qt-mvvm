// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_GRAPHINFOFORMATTER_H
#define MVVM_GRAPHINFOFORMATTER_H

#include "statusstringformatterinterface.h"

class QCustomPlot;

namespace ModelView
{

/*!
@class GraphInfoFormatter
@brief Formats status string for current mouse position in QCustomPlot with QCPGraph's.
*/

class CORE_EXPORT GraphInfoFormatter : public StatusStringFormatterInterface
{
public:
    std::string status_string(QCustomPlot* custom_plot, double x, double y) const override;
};

} // namespace ModelView

#endif // MVVM_GRAPHINFOFORMATTER_H
