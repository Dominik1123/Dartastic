/***************************************************************************************
 *
 * This program helps you to manage your scores at darts.
 * Copyright (C) 2016  Dominik Vilsmeier
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 ***************************************************************************************/

#include "newmatchdialog.h"
#include <QIntValidator>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QString>

NewMatchDialog::NewMatchDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("New Match");

    nLegsToWinSetInput = new QLineEdit(this);
    nSetsToWinMatchInput = new QLineEdit(this);
    doubleOutInput = new QCheckBox(this);
    doubleOutInput->setChecked(true);

    nLegsToWinSetInput->setValidator(new QIntValidator(0, 100, this));
    nSetsToWinMatchInput->setValidator(new QIntValidator(0, 100, this));

    QVBoxLayout* vLayout = new QVBoxLayout;

    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->addWidget(new QLabel("# of legs to win a set: ", this));
    hLayout->addWidget(nLegsToWinSetInput);
    vLayout->addLayout(hLayout);

    hLayout = new QHBoxLayout;
    hLayout->addWidget(new QLabel("# of sets to win the match: ", this));
    hLayout->addWidget(nSetsToWinMatchInput);
    vLayout->addLayout(hLayout);

    hLayout = new QHBoxLayout;
    hLayout->addWidget(new QLabel("double out: ", this));
    hLayout->addWidget(doubleOutInput);
    vLayout->addLayout(hLayout);

    hLayout = new QHBoxLayout;
    okButton = new QPushButton("ok", this);
    okButton->setEnabled(false);
    hLayout->addWidget(okButton);
    QPushButton* cancelButton = new QPushButton("cancel", this);
    hLayout->addWidget(cancelButton);
    vLayout->addLayout(hLayout);

    setLayout(vLayout);

    connect(nLegsToWinSetInput, SIGNAL(textChanged(QString)), this, SLOT(toggleOkButton(QString)));
    connect(nSetsToWinMatchInput, SIGNAL(textChanged(QString)), this, SLOT(toggleOkButton(QString)));
    connect(okButton, SIGNAL(pressed()), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(pressed()), this, SLOT(reject()));
}

int NewMatchDialog::getNLegsToWinSet()
{
    return nLegsToWinSetInput->text().toInt();
}

int NewMatchDialog::getNSetsToWinMatch()
{
    return nSetsToWinMatchInput->text().toInt();
}

bool NewMatchDialog::getDoubleOut()
{
    return doubleOutInput->isChecked();
}

void NewMatchDialog::toggleOkButton(QString)
{
    if(!nLegsToWinSetInput->text().isEmpty() && !nSetsToWinMatchInput->text().isEmpty()) {
        okButton->setEnabled(true);
    }
}
