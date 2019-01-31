// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef TOYITEMS_H
#define TOYITEMS_H

#include "compounditem.h"
#include "sessionmodel.h"
#include "itemfactoryinterface.h"
#include <string>

//! Collection of toy items and models for testing purposes.

namespace ToyItems
{

class MultiLayer : public ModelView::CompoundItem
{
public:
    static const std::string T_LAYERS;
    MultiLayer();
};

// ----------------------------------------------------------------------------

class Layer : public ModelView::CompoundItem
{
public:
    static const std::string P_THICKNESS;
    static const std::string T_PARTICLES;
    Layer();
};

// ----------------------------------------------------------------------------

class Vector : public ModelView::CompoundItem
{
public:
    static const std::string P_X;
    static const std::string P_Y;
    static const std::string P_Z;
    Vector();
};

// ----------------------------------------------------------------------------

class Particle : public ModelView::CompoundItem
{
public:
    static const std::string P_POSITION;
    Particle();
};

} // ToyItems

#endif // TOYITEMS_H
