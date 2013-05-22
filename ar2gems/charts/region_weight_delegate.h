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



#ifndef REGION_WEIGHT_DELEGATE_H
#define REGION_WEIGHT_DELEGATE_H

#include <qtplugins/region_weight_proxy_model.h>
#include <charts/common.h>

#include <QStyledItemDelegate>
#include <QStyleOptionViewItem>
#include <QPainter>
#include <QModelIndex>

class CHARTS_DECL Region_weight_delegate : public QStyledItemDelegate
{
  Q_OBJECT

public:
    Region_weight_delegate( QObject *parent =0 );
    ~Region_weight_delegate();

     virtual void paint(QPainter *painter, const QStyleOptionViewItem &option,
                const QModelIndex &index) const;
     virtual QSize sizeHint(const QStyleOptionViewItem &option,
                    const QModelIndex &index) const;
     virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                           const QModelIndex &index) const;

     virtual void	setEditorData ( QWidget * editor, const QModelIndex & index ) const;
     virtual void	setModelData ( QWidget * editor, QAbstractItemModel * model, const QModelIndex & index ) const;
     virtual void updateEditorGeometry(QWidget *editor,
                                  const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:

  Region_weight_proxy_model* model_;
    
};

#endif // REGION_WEIGHT_DELEGATE_H
