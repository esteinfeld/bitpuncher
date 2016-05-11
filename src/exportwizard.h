/*
    bitpuncher - monochrome bitmap editor

    Copyright (C) 2016  OXullo Intersecans <x@brainrapers.org>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef EXPORTWIZARD_H
#define EXPORTWIZARD_H

#include <QWizard>
#include <QWizardPage>
#include <QLineEdit>
#include <QRadioButton>
#include <QCheckBox>
#include <QVector>
#include <QImage>

class FormatPage : public QWizardPage
{
    Q_OBJECT

public:
    FormatPage(QWidget *parent = 0);
};

class PathPage : public QWizardPage
{
    Q_OBJECT

public:
    PathPage(QWidget *parent = 0);
    virtual void initializePage();

private slots:
    void onBrowsePressed();

private:
    QLineEdit *path;
    QCheckBox *cbOverwrite;
};


class ExportWizard : public QWizard
{
    Q_OBJECT
public:
    explicit ExportWizard(QVector<QImage> &frames, int currentFrame, QWidget *parent = 0);

signals:

public slots:
    virtual void accept();

private:
    QVector<QImage> mFrames;
    int mCurrentFrame;

    void exportPng();
    void exportCHeader();
};

#endif // EXPORTWIZARD_H
