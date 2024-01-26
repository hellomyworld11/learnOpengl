#pragma once

#include <QtWidgets/QWidget>
#include "ui_HelloOpenGl.h"

class HelloOpenGl : public QWidget
{
    Q_OBJECT

public:
    HelloOpenGl(QWidget *parent = Q_NULLPTR);

private:
    Ui::HelloOpenGlClass ui;
};
