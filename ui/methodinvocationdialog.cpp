/*
  methodinvocationdialog.cpp

  This file is part of GammaRay, the Qt application inspection and
  manipulation tool.

  Copyright (C) 2010-2022 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Volker Krause <volker.krause@kdab.com>

  Licensees holding valid commercial KDAB GammaRay licenses may use this file in
  accordance with GammaRay Commercial License Agreement provided with the Software.

  Contact info@kdab.com if any conditions of this licensing are not clear to you.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "methodinvocationdialog.h"
#include "ui_methodinvocationdialog.h"

#include <common/metatypedeclarations.h>

#include <QPushButton>

using namespace GammaRay;

MethodInvocationDialog::MethodInvocationDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MethodInvocationDialog)
    , m_stateManager(this)
{
    ui->setupUi(this);

    ui->argumentView->header()->setObjectName("argumentViewHeader");
    ui->argumentView->setDeferredResizeMode(0, QHeaderView::ResizeToContents);
    ui->argumentView->setDeferredResizeMode(1, QHeaderView::Stretch);
    ui->argumentView->setDeferredResizeMode(2, QHeaderView::ResizeToContents);

    ui->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Invoke"));
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    ui->connectionTypeComboBox->addItem(tr("Auto"), QVariant::fromValue(Qt::AutoConnection));
    ui->connectionTypeComboBox->addItem(tr("Direct"), QVariant::fromValue(Qt::DirectConnection));
    ui->connectionTypeComboBox->addItem(tr("Queued"), QVariant::fromValue(Qt::QueuedConnection));
}

MethodInvocationDialog::~MethodInvocationDialog() = default;

Qt::ConnectionType MethodInvocationDialog::connectionType() const
{
    return ui->connectionTypeComboBox->itemData(ui->connectionTypeComboBox->currentIndex()).value<Qt
                                                                                                  ::
                                                                                                  ConnectionType>();
}

void MethodInvocationDialog::setArgumentModel(QAbstractItemModel *model)
{
    ui->argumentView->setModel(model);
}
