/* -----------------------------------------------------------------------------
** Copyright (c) 2012 Advanced Resources and Risk Technology, LLC
** All rights reserved.
**
** This file is part of Advanced Resources and Risk Technology, LLC (AR2TECH) 
** version of the open source software sgems.  It is a derivative work by 
** AR2TECH (THE LICENSOR) based on the x-free license granted in the original 
** version of the software (see notice below) and now sublicensed such that it 
** cannot be distributed or modified without the explicit and written permission 
** of AR2TECH.
**
** Only AR2TECH can modify, alter or revoke the licensing terms for this 
** file/software.
**
** This file cannot be modified or distributed without the explicit and written 
** consent of AR2TECH.
**
** Contact Dr. Alex Boucher (aboucher@ar2tech.com) for any questions regarding
** the licensing of this file/software
**
** The open-source version of sgems can be downloaded at 
** sourceforge.net/projects/sgems.
** ----------------------------------------------------------------------------*/



/**********************************************************************
** Author: Nicolas Remy
** Copyright (C) 2002-2004 The Board of Trustees of the Leland Stanford Junior
**   University
** All rights reserved.
**
** This file is part of the "extra" module of the Geostatistical Earth
** Modeling Software (GEMS)
**
** This file may be distributed and/or modified under the terms of the 
** license defined by the Stanford Center for Reservoir Forecasting and 
** appearing in the file LICENSE.XFREE included in the packaging of this file.
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** See http://www.gnu.org/copyleft/gpl.html for GPL licensing information.
**
** Contact the Stanford Center for Reservoir Forecasting, Stanford University
** if any conditions of this licensing are not clear to you.
**
**********************************************************************/

#ifndef KRIGING_TYPE_SELECTOR_BASE_H
#define KRIGING_TYPE_SELECTOR_BASE_H

#include <qtplugins/common.h>

#include <qvariant.h>
#include <qwidget.h>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>

class PropertySelector;
class QCheckBox;
class QComboBox;
class QGroupBox;
class QLabel;
class QLineEdit;

class QTPLUGINS_DECL  Kriging_type_selector_base : public QWidget
{ 
    Q_OBJECT

public:
    Kriging_type_selector_base( QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0 );
    ~Kriging_type_selector_base();

    QComboBox* kriging_type_;
    QGroupBox* sk_mean_box_;
    QLabel* TextLabel2_2;
    QLineEdit* sk_mean_edit_;
    QGroupBox* trend_components_box_;
    QCheckBox* y_;
    QCheckBox* z_;
    QCheckBox* xz_;
    QCheckBox* xy_;
    QCheckBox* z2_;
    QCheckBox* yz_;
    QCheckBox* y2_;
    QCheckBox* x2_;
    QCheckBox* x_;
    QGroupBox* local_mean_box_;
    QLabel* TextLabel4;
    PropertySelector* local_mean_property_;


protected:
    QVBoxLayout* Kriging_type_selector_baseLayout;
    QHBoxLayout* sk_mean_box_Layout;
    QGridLayout* trend_components_box_Layout;
    QVBoxLayout* local_mean_box_Layout;
    QHBoxLayout* Layout25;
};

#endif // KRIGING_TYPE_SELECTOR_BASE_H
