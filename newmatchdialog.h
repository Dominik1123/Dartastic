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

#ifndef NEWMATCHDIALOG_H
#define NEWMATCHDIALOG_H

#include <QCheckBox>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

class NewMatchDialog : public QDialog
{
    Q_OBJECT

private:
    QLineEdit* nLegsToWinSetInput;
    QLineEdit* nSetsToWinMatchInput;
    QCheckBox* doubleOutInput;
    QPushButton* okButton;

public:
    explicit NewMatchDialog(QWidget *parent = 0);

    int getNLegsToWinSet();
    int getNSetsToWinMatch();
    bool getDoubleOut();

signals:

public slots:
    void toggleOkButton(QString);
};

#endif // NEWMATCHDIALOG_H
