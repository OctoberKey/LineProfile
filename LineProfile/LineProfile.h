#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LineProfile.h"

class LineProfile : public QMainWindow
{
    Q_OBJECT

public:
    LineProfile(QWidget *parent = Q_NULLPTR);

private:
    Ui::LineProfileClass ui;
};
